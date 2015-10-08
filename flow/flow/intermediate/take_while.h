
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
 
#ifndef FLOW_INTERMEDIATE_TAKEWHILE_H
#define FLOW_INTERMEDIATE_TAKEWHILE_H

#include <functional>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/TakeWhile.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Takes elements from the stream until <paramref name="predicate"/> returns <c>false</c> for an element.
/// <para>Elements after and including the first <c>false</c> are discarded, even if later elements would return
/// <c>true</c> for <paramref name="predicate"/>.</para>
/// </summary>
/// <param name="predicate">The predicate used to take stream elements.</param>
/// <returns>An intermediate operation that takes stream elements while <paramref name="predicate"/> returns <c>true</c>.</returns>
/// <seealso cref="drop_while()"/>
/// <seealso cref="filter()"/>
template <typename UnaryPredicate>
auto take_while(UnaryPredicate predicate) {
    return detail::make_intermediate([predicate](auto&& stream) {
        return Stream<source::TakeWhile<std::remove_reference_t<decltype(stream.source())>, UnaryPredicate>>(std::move(stream.source()), predicate);
    });
}

/// <summary>
/// Takes elements from the stream until an element is <c>false</c>.
/// <para>Elements after and including the first <c>false</c> are discarded, even if later elements are
/// <c>true</c>. This is an overload for streams with types convertible to <c>bool</c>.</para>
/// </summary>
/// <returns>An intermediate operation that takes stream elements while they are <c>true</c>.</returns>
/// <seealso cref="drop_while()"/>
/// <seealso cref="filter()"/>
inline auto take_while() {
    return take_while([](const auto& ele) { return static_cast<bool>(ele); });
}

/// <summary>
/// Takes elements from the stream until the <paramref name="member"/> returns <c>false</c>.
/// <para>Elements after and including the first <c>false</c> are discarded, even if later elements would return
/// <c>true</c> for <paramref name="member"/>.</para>
/// </summary>
/// <param name="member">The class member function used to take elements, the return type must be convertible to <c>bool</c>.</param>
/// <returns>An intermediate operation that takes stream elements while the <paramref name="member"/> is <c>true</c>.</returns>
/// <seealso cref="drop_while()"/>
/// <seealso cref="filter()"/>
template <typename Ret, typename Class>
auto take_while(Ret(Class::*member)()) {
    return take_while(std::mem_fn(member));
}

/// <summary>
/// Takes elements from the stream until the <paramref name="member"/> returns <c>false</c>.
/// <para>Elements after and including the first <c>false</c> are discarded, even if later elements would return
/// <c>true</c> for <paramref name="member"/>.</para>
/// </summary>
/// <param name="member">The const class member function used to take elements, the return type must be convertible to <c>bool</c>.</param>
/// <returns>An intermediate operation that takes stream elements while the <paramref name="member"/> is <c>true</c>.</returns>
/// <seealso cref="drop_while()"/>
/// <seealso cref="filter()"/>
template <typename Ret, typename Class>
auto take_while(Ret(Class::*member)() const) {
    return take_while(std::mem_fn(member));
}
    }
}
#endif
