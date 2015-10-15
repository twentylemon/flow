
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
 
#ifndef FLOW_TERMINAL_ANY_H
#define FLOW_TERMINAL_ANY_H

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns <c>true</c> if any of the elements in the stream return <c>true</c> for <paramref name="predicate"/>.
/// <para>This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>false</c>.</para>
/// </summary>
/// <param name="predicate">The predicate to test each element with.</param>
/// <returns>A terminal operation which returns <c>true</c> if any stream element returns <c>true</c> for <paramref name="predicate" />.</returns>
template <typename UnaryPredicate>
auto any(UnaryPredicate predicate) {
    return detail::make_terminal([predicate](auto&& stream) {
        while (stream.has_next()) {
            if (predicate(stream.next())) {
                return true;
            }
        }
        return false;
    });
}

/// <summary>
/// Returns <c>true</c> if any element in the stream can be evaluated to <c>true</c>.
/// <para>This is an overload for streams with types convertible to <c>bool</c>.
/// This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>false</c>.</para>
/// </summary>
/// <returns>A terminal operation which returns <c>true</c> if any stream element is <c>true</c>.</returns>
inline auto any() {
    return any([](const auto& ele) { return static_cast<bool>(ele); });
}

/// <summary>
/// Returns <c>true</c> if any of the elements in the stream return <c>true</c> for <paramref name="member"/>.
/// <para>This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>false</c>.</para>
/// </summary>
/// <param name="member">The class member function to use as the predicate.</param>
/// <returns>A terminal operation which returns <c>true</c> if any stream element returns <c>true</c> for the given predicate.</returns>
template <typename Ret, typename Class>
auto any(Ret(Class::*member)()) {
    return any(std::mem_fn(member));
}

/// <summary>
/// Returns <c>true</c> if any of the elements in the stream return <c>true</c> for <paramref name="member"/>.
/// <para>This operation is short circuited and will stop executing once any <c>true</c> value is found.
/// If the stream is empty, this will return <c>false</c>.</para>
/// </summary>
/// <param name="member">The class member function to use as the predicate.</param>
/// <returns>A terminal operation which returns <c>true</c> if any stream element returns <c>true</c> for the given predicate.</returns>
template <typename Ret, typename Class>
auto any(Ret(Class::*member)() const) {
    return any(std::mem_fn(member));
}
    }
}
#endif
