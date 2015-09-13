
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
 
#ifndef FLOW_INTERMEDIATE_PEEK_H
#define FLOW_INTERMEDIATE_PEEK_H

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Peek.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Lazily executes <paramref name="action"/> for each element in the Stream as a detail::Intermediate operation.
/// This is an intermediate operation equivalent of each().
/// </summary>
/// <param name="action">The function to apply to each element of the stream.</param>
/// <returns>A detail::Intermediate operation that executes a function for each stream element.</returns>
/// <seealso cref="each()"/>
template <typename UnaryFunction>
auto peek(UnaryFunction action) {
    return detail::make_intermediate([action](auto&& stream) {
        return Stream<source::Peek<typename std::remove_reference_t<decltype(stream)>::source_type, UnaryFunction>>(std::move(stream.source()), action);
    });
}

/// <summary>
/// Lazily executes <paramref name="member"/> for each element in the Stream as a detail::Intermediate operation.
/// This is an intermediate operation equivalent of each().
/// </summary>
/// <param name="member">The function to apply to each element of the stream.</param>
/// <returns>A detail::Intermediate operation that executes a function for each stream element.</returns>
/// <seealso cref="each()"/>
template <typename Ret, typename Class>
auto peek(Ret(Class::*member)()) {
    return peek(std::mem_fn(member));
}

/// <summary>
/// Lazily executes <paramref name="member"/> for each element in the Stream as a detail::Intermediate operation.
/// This is an intermediate operation equivalent of each().
/// </summary>
/// <param name="member">The function to apply to each element of the stream.</param>
/// <returns>A detail::Intermediate operation that executes a function for each stream element.</returns>
/// <seealso cref="each()"/>
template <typename Ret, typename Class>
auto peek(Ret(Class::*member)() const) {
    return peek(std::mem_fn(member));
}
    }
}
#endif
