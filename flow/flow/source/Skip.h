
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
 
#ifndef FLOW_SOURCE_SKIP_H
#define FLOW_SOURCE_SKIP_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that skips elements in a stream. That is, the first elements are removed from the stream,
/// after which only every nth element is kept.
/// </summary>
template <typename Source>
class Skip : public IntermediateSource<Source>
{
public:
    using base = IntermediateSource<Source>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Skip{Source}"/> class.
    /// </summary>
    /// <param name="source">The source to skip elements of.</param>
    /// <param name="begin">The index to skip to.</param>
    /// <param name="step_size">The step value, eg 2 will give every 2nd element after <paramref name="begin"/>.</param>
    Skip(Source&& source, std::size_t begin, std::size_t step_size) : base(std::forward<Source>(source)),
        _current(0), _step_size(step_size), _begin(begin), _initial(true) { }

    Skip(const Skip<Source>&) = delete;
    Skip(Skip<Source>&&) = default;

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        if (_initial) {
            step_to(_begin);
            _initial = false;
        }
        else {
            _current += _step_size;
            for (std::size_t i = 1; i < _step_size; ++i) {
                if (base::has_next()) {
                    base::lazy_next();
                }
                else {
                    return false;
                }
            }
        }
        return base::has_next();
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        return base::raw_next();
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is an exact value.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return base::estimate_size() / _step_size;
    }

    /// <summary>
    /// Steps the source stream to the index given.
    /// </summary>
    /// <param name="begin">The index to step to in the source stream.</param>
    void step_to(std::size_t begin) {
        while (_current < begin && base::has_next()) {
            ++_current;
            base::lazy_next();
        }
    }

protected:
    /// <summary>
    /// The current selected index in the stream.
    /// </summary>
    std::size_t _current;

    /// <summary>
    /// The number of elements to skip between giving stream elements.
    /// </summary>
    const std::size_t _step_size;

private:
    const std::size_t _begin;       // the start index
    bool _initial;                  // false once we have processed the first stream value
};
    }
}
#endif
