
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

#ifndef FLOW_INTERMEDIATE_CONCAT_H
#define FLOW_INTERMEDIATE_CONCAT_H

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Concat.h"
#include "../generator/from.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Concatenates the given stream onto the end of the operated stream. The <c>tail</c> stream elements
/// must be convertible to the same type of elements as the head stream.
/// </summary>
/// <param name="tail">The tail stream to put after the end of the operated stream.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that concatenates the streams.</returns>
template <typename Tail>
auto concat(Stream<Tail>&& tail) {
    return detail::make_intermediate([tail = std::move(tail)](auto&& head) mutable {
        return Stream<source::Concat<typename std::remove_reference_t<decltype(head)>::source_type, Tail>>(std::move(head.source()), std::move(tail.source()));
    });
}

/// <summary>
/// Concatenates the given container onto the end of the stream. This is the same as <c>concat(from(container))</c>.
/// The <c>tail</c> stream elements must be convertible to the same type of elements as the head stream.
/// </summary>
/// <param name="container">The container to concatenate onto the end of the stream.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that concatenates the container onto the stream.</returns>
template <typename Container>
auto concat(Container& container) {
    return concat(from(container));
}

/// <summary>
/// Concatenates the given container onto the end of the stream. This is the same as <c>concat(from(container))</c>.
/// The <c>tail</c> stream elements must be convertible to the same type of elements as the head stream.
/// </summary>
/// <param name="container">The container to concatenate onto the end of the stream.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that concatenates the container onto the stream.</returns>
template <typename Container>
auto concat(const Container& container) {
    return concat(from(container));
}
    }
}
#endif
