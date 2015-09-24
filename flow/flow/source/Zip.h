
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
 
#ifndef FLOW_SOURCE_ZIP_H
#define FLOW_SOURCE_ZIP_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that zips two streams together.
/// </summary>
template <typename LeftSource, typename RightSource, typename Zipper>
class Zip : public IntermediateSource<LeftSource, typename std::result_of_t<Zipper(typename LeftSource::value_type&&, typename RightSource::value_type&&)>>
{
public:
    using base = IntermediateSource<LeftSource, typename std::result_of_t<Zipper(typename LeftSource::value_type&&, typename RightSource::value_type&&)>>;

    /// <summary>
    /// Initializes a new instance of the <see cref="Zip{LeftSource, RightSource, Zipper}"/> class.
    /// </summary>
    /// <param name="left">The left stream source.</param>
    /// <param name="right">The right stream source.</param>
    /// <param name="zipper">The function used to zip the two streams together.</param>
    Zip(LeftSource&& left, RightSource&& right, Zipper zipper) : base(std::forward<LeftSource>(left)), _right(std::move(right)), _zipper(zipper) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        return base::has_next() && _right.has_next();
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type next() {
        base::assign_temp_current(_zipper(base::raw_next(), _right.next()));
        return base::next();
        //return _zipper(base::raw_next(), _right.next());
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        base::lazy_next();
        _right.lazy_next();
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is an exact value.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return std::min(base::estimate_size(), _right.estimate_size());
    }

private:
    RightSource _right; // the right stream source
    Zipper _zipper;     // the zipping operation to combine the left and right streams
};
    }
}
#endif
