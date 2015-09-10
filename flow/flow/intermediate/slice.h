
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
#ifndef FLOW_INTERMEDIATE_SLICE_H
#define FLOW_INTERMEDIATE_SLICE_H

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Slice.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Slices the stream. Keeps only elements with index in the range <c>[begin..end)</c> in the stream, excluding
/// the <c>end</c> index. If <c>end</c> is out of bounds of the stream, the entire stream from <c>begin</c>
/// is kept. The operation will skip every <c>step_size</c> elements, for example a <c>step_size</c>
/// of 2 will keep only every other element in the range, eg <c>begin, begin+2, begin+4</c> etc.
/// </summary>
/// <param name="begin">The begin index to slice the stream at. The begin index element is kept.</param>
/// <param name="end">The end index to slice to stream to. The end idex element is not kept.</param>
/// <param name="step_size">The step size.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that slices the stream to the given range.</returns>
auto slice(std::size_t begin, std::size_t end, std::size_t step_size) {
    return detail::make_intermediate([begin, end, step_size](auto&& stream) {
        return Stream<source::Slice<typename std::remove_reference_t<decltype(stream)>::source_type>>(std::move(stream.source()), begin, end, step_size);
    });
}

/// <summary>
/// Slices the stream. Keeps only elements with index in the range <c>[begin..end)</c> in the stream, excluding
/// the <c>end</c> index. If <c>end</c> is out of bounds of the stream, the entire stream from <c>begin</c>
/// is kept.
/// </summary>
/// <param name="begin">The begin index to slice the stream at. The begin index element is kept.</param>
/// <param name="end">The end index to slice to stream to. The end idex element is not kept.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that slices the stream to the given range.</returns>
auto slice(std::size_t begin, std::size_t end) {
    return slice(begin, end, static_cast<std::size_t>(1));
}
    }
}
#endif
