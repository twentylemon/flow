
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
 
#ifndef FLOW_SOURCE_REPEAT_H
#define FLOW_SOURCE_REPEAT_H

#include "Iterator.h"

namespace flow {
    namespace source {

template <typename Itr>
class Repeat : public Iterator<Itr>
{
public:
    using parent_type = Iterator<Itr>;
    using value_type = typename parent_type::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Repeat{Itr}"/> class.
    /// </summary>
    /// <param name="begin">The begin iterator.</param>
    /// <param name="end">The end iterator.</param>
    Repeat(Itr begin, Itr end) : parent_type(begin, end), _begin(begin) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    constexpr bool has_next() const {
        return true;
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type next() {
        cycle();
        return parent_type::next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        cycle();
        parent_type::lazy_next();
    }

    /// <summary>
    /// Returns the max value of <c>std::size_t</c>. This is an infinite stream.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return std::numeric_limits<std::size_t>::max();
    }

    /// <summary>
    /// Cycles the current iterator back to the beginning if it is at the end.
    /// </summary>
    void cycle() {
        if (parent_type::_current == parent_type::_end) {
            parent_type::_current = _begin;
        }
    }

protected:
    /// <summary>
    /// The beginning of the cycle.
    /// </summary>
    Itr _begin;
};
    }
}
#endif
