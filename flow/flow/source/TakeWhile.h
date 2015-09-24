
/**
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
 */
 
#ifndef FLOW_SOURCE_TAKEWHILE_H
#define FLOW_SOURCE_TAKEWHILE_H

namespace flow {
    namespace source {

/// <summary>
/// Stream source that takes elements from the stream until a predicate returns <c>false</c>. All elements
/// after and including the first <c>false</c> are discarded.
/// </summary>
template <typename Source, typename UnaryPredicate>
class TakeWhile
{
public:
    using value_type = typename Source::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="TakeWhile{Source, UnaryPredicate}" /> class.
    /// </summary>
    /// <param name="source">The source to take elements from.</param>
    /// <param name="predicate">The predicate, take stream elements until this returns <c>false</c>.</param>
    TakeWhile(Source&& source, UnaryPredicate predicate) : _source(std::move(source)), _predicate(predicate), _current(nullptr) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        while (_source.has_next()) {
            _current = &_source.next();
            if (_predicate(*_current)) {
                return true;
            }
            return false;
        }
        return false;
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    const value_type& next() {
        return std::move(*_current);
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is likely a vast overestimate.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return _source.estimate_size();
    }

private:
    Source _source;             // the source to read from
    UnaryPredicate _predicate;  // the mapping operation to apply to each element from the source
    const value_type* _current; // the current value
};
    }
}
#endif
