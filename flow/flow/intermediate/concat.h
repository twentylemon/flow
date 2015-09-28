
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
/// Concatenates the given Stream onto the end of the operated stream. The <paramref name="tail"/> stream elements
/// must be convertible to the same type of elements as the head stream.
/// </summary>
/// <param name="tail">The tail stream to put after the end of the operated head stream.</param>
/// <returns>A detail::Intermediate operation that concatenates the two Stream objects.</returns>
template <typename Tail>
auto concat(Stream<Tail>&& tail) {
    return detail::make_intermediate([tail = std::move(tail)](auto&& head) mutable {
        return Stream<source::Concat<typename std::remove_reference_t<decltype(head)>::source_type, Tail>>(std::move(head.source()), std::move(tail.source()));
    });
}

/// <summary>
/// Concatenates the given iterator range onto the end of the Stream. This is the same as <c>concat(from(begin, end))</c>.
/// The <paramref name="tail"/> stream elements must be convertible to the same type of elements as the head stream.
/// </summary>
/// <param name="begin">The beginning of the range to concat.</param>
/// <param name="end">The end of the range to concat.</param>
/// <returns>A detail::Intermediate operation that concatenates the container onto the stream.</returns>
/// <seealso cref="from()"/>
template <typename Itr>
auto concat(Itr begin, Itr end) {
    return concat(generator::from(begin, end));
}

/// <summary>
/// Concatenates <paramref name="container"/> onto the end of the Stream. This is the same as <c>concat(from(container))</c>.
/// The <paramref name="tail"/> stream elements must be convertible to the same type of elements as the head stream.
/// </summary>
/// <param name="container">The container to concatenate onto the end of the stream.</param>
/// <returns>A detail::Intermediate operation that concatenates the container onto the stream.</returns>
/// <seealso cref="from()"/>
template <typename Container, typename = typename std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto concat(Container& container) {
    return concat(generator::from(container));
}
    }
}
#endif
