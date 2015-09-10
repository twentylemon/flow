
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
#ifndef LEMON_FLOW_SOURCE_UNIQUE_H
#define LEMON_FLOW_SOURCE_UNIQUE_H

#include <algorithm>

#include "Sort.h"

namespace lemon {
    namespace flow {
        namespace source {

/// <summary>
/// Stream source to sort the stream. Sorting is an eager operation, the entire stream up to this point
/// is evaluated and stored and finally sorted after.
/// </summary>
template <typename Source>
class Unique : public Sort<Source>
{
public:
    using value_type = typename Source::value_type;
    using parent_type = Sort<Source>;

    /// <summary>
    /// Initializes a new instance of the <see cref="Unique{Source}"/> class.
    /// </summary>
    /// <param name="source">The source stream to sort are take unique values from.</param>
    /// <param name="compare">The comparator to use in the sort.</param>
    template <typename Compare>
    Unique(Source&& source, Compare compare) : parent_type(std::forward<Source>(source), compare, false)
    {
        unique(compare);
    }

    /// <summary>
    /// Makes the sorted stream unique.
    /// </summary>
    /// <param name="compare">The comparator to used in the sort.</param>
    template <typename Compare>
    void unique(Compare compare) {
        parent_type::_end = parent_type::_stream.erase(
            std::unique(parent_type::_stream.begin(), parent_type::_stream.end(), [compare](auto&& lhs, auto&& rhs) {
                return !compare(lhs, rhs);  // they are sorted, they elements are equal while this is true
            }), parent_type::_stream.end());
    }
};
        }
    }
}
#endif
