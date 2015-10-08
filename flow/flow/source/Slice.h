
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
 
#ifndef FLOW_SOURCE_SLICE_H
#define FLOW_SOURCE_SLICE_H

#include "Skip.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that slices a stream. That is, a range of elements from the stream is kept, optionally allowing
/// for only nth element from that range to be kept.
/// </summary>
template <typename Source>
class Slice : public Skip<Source>
{
public:
    using parent_type = Skip<Source>;

    /// <summary>
    /// Initializes a new instance of the <see cref="Slice{Source}"/> class.
    /// </summary>
    /// <param name="source">The source to slice.</param>
    /// <param name="begin">The begin index to slice from.</param>
    /// <param name="end">The end index to slice to.</param>
    /// <param name="step_size">The step value, eg 2 will give every 2nd element in the range.</param>
    Slice(Source&& source, std::size_t begin, std::size_t end, std::size_t step_size) :
        parent_type(std::move(source), begin, step_size), _end(end) { }

    Slice(const Slice<Source>&) = delete;
    Slice(Slice<Source>&&) = default;

    /// <summary>
    /// Returns <c>true</c> if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        return parent_type::has_next() && parent_type::_current < _end;
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// If this does not go to the end of the stream, this value is exact. Otherwise,
    /// the estimate depends on the source estimate.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return (_end - parent_type::_current) / parent_type::_step_size;
    }

private:
    const std::size_t _end; // the ending index
};
    }
}
#endif
