
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
 
#ifndef FLOW_INTERMEDIATE_SKIP_H
#define FLOW_INTERMEDIATE_SKIP_H

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Skip.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Skips the first elements of a stream, keeping only the elements with index <c>&gt;=</c> <paramref name="begin"/> in the stream.
/// <para>This operation will skip every <paramref name="step_size"/> elements after the initial jump to <paramref name="begin"/>.
/// For example a <paramref name="step_size"/> of 2 will keep only every other element, eg <c>begin, begin+2, begin+4</c> etc.
/// If <paramref name="begin"/> is out of bounds, then the result is an empty stream.</para>
/// </summary>
/// <param name="begin">The begin index to slice the stream at, inclusive.</param>
/// <param name="step_size">The step size, must be positive.</param>
/// <returns>An intermediate operation that slices the stream from <paramref name="begin"/> to the end
/// skipping every <paramref name="step_size"/> elements.</returns>
inline auto skip(std::size_t begin, std::size_t step_size) {
    return detail::make_intermediate([begin, step_size](auto&& stream) {
        return Stream<source::Skip<std::remove_reference_t<decltype(stream.source())>>>(std::move(stream.source()), begin, step_size);
    });
}

/// <summary>
/// Skips the first elements of a stream, keeping only the elements with index <c>&gt;=</c> <paramref name="begin"/> in the stream.
/// <para>If <paramref name="begin"/> is out of bounds, then the result is an empty stream.</para>
/// </summary>
/// <param name="begin">The begin index to slice the stream at, inclusive.</param>
/// <returns>An intermediate operation that slices the stream from <paramref name="begin"/> to the end.</returns>
inline auto skip(std::size_t begin) {
    return skip(begin, static_cast<std::size_t>(1));
}

/// <summary>
/// Skips every <paramref name="step_size"/> elements in the stream, keeping the first element.
/// <para>For example, a <paramref name="step_size"/> of 2 will only keep stream elements with index 0, 2, 4 etc.</para>
/// </summary>
/// <param name="step_size">The step size, must be positive.</param>
/// <returns>An intermediate operation that skips every <paramref name="step_size"/> elements.</returns>
inline auto skip_every(std::size_t step_size) {
    return skip(static_cast<std::size_t>(0), step_size);
}
    }
}
#endif
