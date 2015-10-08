
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
 
#ifndef FLOW_INTERMEDIATE_MAP_H
#define FLOW_INTERMEDIATE_MAP_H

#include <functional>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Map.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Transforms each element in the stream using <paramref name="mapper"/>.
/// <para>Elements can be mapped to the same type as the source stream, or a new type.</para>
/// </summary>
/// <param name="mapper">The operation to apply to each element in the stream.</param>
/// <returns>An intermediate operation that maps the stream to new values.</returns>
template <typename UnaryOperation>
auto map(UnaryOperation mapper) {
    return detail::make_intermediate([mapper](auto&& stream) {
        return Stream<source::Map<std::remove_reference_t<decltype(stream.source())>, UnaryOperation>>(std::move(stream.source()), mapper);
    });
}

/// <summary>
/// Transforms each element in the stream to the return value of <paramref name="member"/> for each stream element.
/// </summary>
/// <param name="member">The class member function to use as the transformation.</param>
/// <returns>An intermediate operation that maps the stream to new values.</returns>
template <typename Ret, typename Class>
auto map(Ret(Class::*member)()) {
    return map(std::mem_fn(member));
}

/// <summary>
/// Transforms each element in the stream to the return value of <paramref name="member"/> for each stream element.
/// </summary>
/// <param name="member">The const class member function to use as the transformation.</param>
/// <returns>An intermediate operation that maps the stream to new values.</returns>
template <typename Ret, typename Class>
auto map(Ret(Class::*member)() const) {
    return map(std::mem_fn(member));
}
    }
}
#endif
