
/**
 * \cond LICENSE
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Taras Mychaskiw
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * \endcond
 */
 
#ifndef FLOW_SOURCE_SETSOURCE_H
#define FLOW_SOURCE_SETSOURCE_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Which stream source to pull a new value from in a set operation.
/// <para>This is analogous to iterator incrementation in normal code,
/// ie <c>Left</c> will only incrememnt the left stream source.</para>
/// </summary>
enum class AdvanceState { None, Left, Right, Both };

/// <summary>
/// Which stream source is empty after an advance operation.
/// <para>This is analogous to checking for a base case in normal code,
/// ie having a call to <c>std::copy</c> once a range is empty.</para>
/// </summary>
enum class EmptyState { None, Left, Right, Both };

/// <summary>
/// Flag to indicate something analogous to copying the value in normal code.
/// <para>No value is copied, but a state of <c>UpdateComplete</c> means
/// a value was found and a call to next() should occur. <c>UpdateContinue</c>
/// means a value was not found, and further stream iteration should occur.
/// Finally, <c>EmptyStream</c> means both stream sources are empty.</para>
/// </summary>
enum class UpdateState { UpdateComplete, EmptyStream, UpdateContinue };

/// <summary>
/// Base class for set source operation wrappers. Provides simple default implementations for
/// all required methods.
/// </summary>
class SetOperation
{
public:
    /// <summary>
    /// Action to perform when neither source is empty. Default kills the stream.
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns>The update state after the operation is performed.</returns>
    template <typename Source>
    UpdateState none_empty(Source& source) {
        return UpdateState::EmptyStream;
    }

    /// <summary>
    /// Action to perform when only the left source is empty. Default pulls the value from the right source.
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns>The update state after the operation is performed.</returns>
    template <typename Source>
    UpdateState left_empty(Source& source) {
        source.set_next_to_right();
        return UpdateState::UpdateComplete;
    }

    /// <summary>
    /// Action to perform when only the right source is empty. Default pulls the value from the left source.
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns>The update state after the operation is performed.</returns>
    template <typename Source>
    UpdateState right_empty(Source& source) {
        source.set_next_to_left();
        return UpdateState::UpdateComplete;
    }
};


/// <summary>
/// An intermediate operation base class for set based operations -- where the streams must be sorted.
/// <para>The worker of this source lies in the implementation of <c>Operation</c>, which dictates
/// which source to pull from (left or right) and how to continue afterwards.</para>
/// </summary>
template <typename LeftSource, typename RightSource, typename Compare, typename Operation>
class SetSource : public IntermediateSource<LeftSource>
{
public:
    using base = IntermediateSource<LeftSource>;
    using value_type = typename base::value_type;
    static_assert(std::is_convertible<value_type, typename RightSource::value_type>::value, "flow::(set operation) left element type must be convertible to the right element type");

    /// <summary>
    /// Initializes a new instance of the <see cref="SetSource{LeftSource, RightSource, Compare, Operation}"/> class.
    /// </summary>
    /// <param name="left">The left stream source.</param>
    /// <param name="right">The right stream source.</param>
    /// <param name="compare">The compare function by which the sources are sorted.</param>
    SetSource(LeftSource&& left, RightSource&& right, Compare compare) : base(std::move(left)), _right(std::move(right)), _compare(compare),
        _operation(), _advance_state(AdvanceState::Both), _empty_state(EmptyState::None), _current(nullptr) { }

    SetSource(const SetSource<LeftSource, RightSource, Compare, Operation>&) = delete;
    SetSource(SetSource<LeftSource, RightSource, Compare, Operation>&&) = default;

    /// <summary>
    /// Sets the advance state.
    /// </summary>
    /// <param name="advance">The advance state to set.</param>
    void set_advance(AdvanceState advance) {
        _advance_state = advance;
    }

    /// <summary>
    /// Sets the next value to be returned by next() to the result from the left source.
    /// </summary>
    void set_next_to_left() {
        _current = base::_current;
    }

    /// <summary>
    /// Sets the next value to be returned by next() to the result from the right source.
    /// </summary>
    void set_next_to_right() {
        _current = _right._current;
    }

    /// <summary>
    /// Returns <c>true</c> if the left value compares less than the right value.
    /// </summary>
    /// <returns><c>true</c> if the left value compares less than the right value.</returns>
    bool compare_left_less() {
        return _compare(base::next(), _right.next());
    }

    /// <summary>
    /// Returns <c>true</c> if the right value compares less than the left value.
    /// </summary>
    /// <returns><c>true</c> if the right value compares less than the left value.</returns>
    bool compare_right_less() {
        return _compare(_right.next(), base::next());
    }

    /// <summary>
    /// Returns <c>true</c> if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        while (true) {
            advance();
            UpdateState update = UpdateState::EmptyStream;
            if (_empty_state == EmptyState::None) {
                update = _operation.none_empty(*this);
            }
            else if (_empty_state == EmptyState::Left) {
                update = _operation.left_empty(*this);
            }
            else if (_empty_state == EmptyState::Right) {
                update = _operation.right_empty(*this);
            }

            if (update == UpdateState::UpdateComplete) {
                return true;
            }
            else if (update == UpdateState::EmptyStream) {
                return false;
            }
            // else update == UpdateState::UpdateContinue; continue the loop
        }
        return false;
    }

    /// <summary>
    /// Returns the next element from the stream. The value is <em>moved</em>. Successive calls to next() will fail.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        return *_current;
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return base::estimate_size() + _right.estimate_size();
    }

private:
    /// <summary>
    /// Updates the empty and advance states after learning that a source stream is empty.
    /// </summary>
    /// <param name="empty">The empty state to set if neither source was empty, else <c>EmptyState::Both</c> is set.</param>
    /// <param name="advance">The advance state to set if neither stream was empty, else unchanged.</param>
    void update_state(EmptyState empty, AdvanceState advance) {
        if (_empty_state == EmptyState::None) {
            _empty_state = empty;
            _advance_state = advance;
        }
        else {
            _empty_state = EmptyState::Both;
        }
    }

    /// <summary>
    /// Returns <c>true</c> if <c>left.has_next()</c>. Updates the advance state if not.
    /// </summary>
    /// <returns><c>true</c> if the left source has more elements.</returns>
    void advance_left() {
        if (base::has_next()) {
            base::assign_current();
        }
        else {
            update_state(EmptyState::Left, AdvanceState::Right);
        }
    }

    /// <summary>
    /// Returns <c>true</c> if <c>right.has_next()</c>. Updates the advance state if not.
    /// </summary>
    /// <returns><c>true</c> if the right source has more elements.</returns>
    void advance_right() {
        if (_right.has_next()) {
            _right.assign_current();
        }
        else {
            update_state(EmptyState::Right, AdvanceState::Left);
        }
    }

    /// <summary>
    /// Asks the correct sources if they have more elements and returns <c>true</c> if they do.
    /// </summary>
    /// <returns><c>true</c> if the current advance state sources have more elements.</returns>
    void advance() {
        if (_advance_state == AdvanceState::Left) {
            advance_left();
        }
        else if (_advance_state == AdvanceState::Right) {
            advance_right();
        }
        else if (_advance_state == AdvanceState::Both) {
            advance_left();
            advance_right();
        }
    }

    IntermediateSource<RightSource> _right; // the right stream source
    Compare _compare;                       // the comparator by which the two streams are sorted
    Operation _operation;                   // the set operation
    AdvanceState _advance_state;            // which streams should be advanced in has_next
    EmptyState _empty_state;                // which streams are empty
    value_type* _current;                   // the next value of the stream
};
    }
}
#endif
