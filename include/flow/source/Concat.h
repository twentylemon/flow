
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
 
#ifndef FLOW_SOURCE_CONCAT_H
#define FLOW_SOURCE_CONCAT_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that concatenates two other streams together.
/// </summary>
template <typename Head, typename Tail>
class Concat : public IntermediateSource<Head>
{
public:
    using base = IntermediateSource<Head>;
    using value_type = typename base::value_type;
    static_assert(std::is_convertible<value_type, typename Tail::value_type>::value, "flow::concat tail element type must be convertible to the head element type");

    /// <summary>
    /// Initializes a new instance of the <see cref="Concat{Head, Tail}"/> class.
    /// </summary>
    /// <param name="head">The head stream source to start with.</param>
    /// <param name="tail">The stream source to concatenate onto the end of the head source.</param>
    Concat(Head&& head, Tail&& tail) : base(std::forward<Head>(head)), _tail(std::move(tail)), _from_head(true) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        if (_from_head && base::has_next()) {
            return true;
        }
        _from_head = false;
        return _tail.has_next();
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        if (_from_head) {
            return base::raw_next();
        }
        return _tail.next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        if (_from_head) {
            base::lazy_next();
        }
        else {
            _tail.lazy_next();
        }
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is an exact value.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return base::estimate_size() + _tail.estimate_size();
    }

private:
    // tail can instead be an IntermediateSource<Tail>, but this is good enough
    Tail _tail;         // the second source to pull values from after the head is empty
    bool _from_head;    // true if we are still pulling from the head
};
    }
}
#endif
