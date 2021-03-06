
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
 
#ifndef FLOW_TERMINAL_NONE_H
#define FLOW_TERMINAL_NONE_H

#include <functional>

#include "any.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns <c>true</c> if none of the elements in the stream return <c>true</c> for <paramref name="predicate"/>.
/// <para>This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>true</c>.</para>
/// </summary>
/// <param name="predicate">The predicate to test each element with.</param>
/// <returns>A terminal operation which returns <c>true</c> if none of stream elements return <c>true</c> for <paramref name="predicate"/>.</returns>
/// <seealso cref="all()"/>
/// <seealso cref="any()"/>
template <typename UnaryPredicate>
auto none(UnaryPredicate predicate) {
    return any(predicate).then(std::logical_not<bool>());
}

/// <summary>
/// Returns <c>true</c> if none of the elements in the stream can be evaluated to <c>true</c>.
/// <para>This is an overload for streams with types convertible to <c>bool</c>.
/// This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>true</c>.</para>
/// </summary>
/// <returns>A terminal operation which returns <c>true</c> if none of the stream elements are <c>true</c>.</returns>
/// <seealso cref="all()"/>
/// <seealso cref="any()"/>
inline auto none() {
    return none([](const auto& ele) { return static_cast<bool>(ele); });
}

/// <summary>
/// Returns <c>true</c> if none of the elements in the stream return <c>true</c> for <paramref name="member"/>.
/// <para>This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>true</c>.</para>
/// </summary>
/// <param name="member">The class member function to use as the predicate.</param>
/// <returns>A terminal operation which returns <c>true</c> if none of the stream elements return <c>true</c> for <paramref name="member"/>.</returns>
/// <seealso cref="all()"/>
/// <seealso cref="any()"/>
template <typename Ret, typename Class>
auto none(Ret(Class::*member)()) {
    return none(std::mem_fn(member));
}

/// <summary>
/// Returns <c>true</c> if none of the elements in the stream return <c>true</c> for <paramref name="member"/>.
/// <para>This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>true</c>.</para>
/// </summary>
/// <param name="member">The class member function to use as the predicate.</param>
/// <returns>A terminal operation which returns <c>true</c> if none of the stream elements return <c>true</c> for <paramref name="member"/>.</returns>
/// <seealso cref="all()"/>
/// <seealso cref="any()"/>
template <typename Ret, typename Class>
auto none(Ret(Class::*member)() const) {
    return none(std::mem_fn(member));
}
    }
}
#endif
