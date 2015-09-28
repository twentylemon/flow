
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
 
#ifndef FLOW_TERMINAL_ALL_H
#define FLOW_TERMINAL_ALL_H

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns <c>true</c> if all of the elements in the Stream return <c>true</c> for <paramref name="predicate" />.
/// This operation is short circuited and will stop executing once any <c>false</c> value is found.
/// If the stream is empty, this will return <c>true</c>.
/// </summary>
/// <param name="predicate">The predicate to test each element with.</param>
/// <returns>The detail::Terminal operation which returns <c>true</c> if all stream elements return <c>true</c> for <paramref name="predicate" />.</returns>
template <typename UnaryPredicate>
auto all(UnaryPredicate predicate) {
    return detail::make_terminal([predicate](auto&& stream) {
        while (stream.has_next()) {
            if (!predicate(stream.next())) {
                return false;
            }
        }
        return true;
    });
}

/// <summary>
/// Returns <c>true</c> if all elements in the Stream can be evaluated to <c>true</c>.
/// This is an overload for streams with types convertible to <c>bool</c>.
/// This operation is short circuited and will stop executing once any <c>false</c> value is found.
/// If the stream is empty, this will return <c>true</c>.
/// </summary>
/// <returns>The detail::Terminal operation which returns <c>true</c> if all stream elements are <c>true</c>.</returns>
inline auto all() {
    return all([](const auto& ele) { return static_cast<bool>(ele); });
}

/// <summary>
/// Returns <c>true</c> if all of the elements in the stream return <c>true</c> for the predicate given.
/// This operation is short circuited and will stop executing once any <c>false</c> value is found.
/// If the stream is empty, this will return <c>true</c>.
/// </summary>
/// <param name="member">The class member function to use as the predicate.</param>
/// <returns>The detail::Terminal operation which returns <c>true</c> if all stream element returns <c>true</c> for the given predicate.</returns>
template <typename Ret, typename Class>
auto all(Ret(Class::*member)()) {
    return all(std::mem_fn(member));
}

/// <summary>
/// Returns <c>true</c> if all of the elements in the stream return <c>true</c> for the predicate given.
/// This operation is short circuited and will stop executing once any <c>false</c> value is found.
/// If the stream is empty, this will return <c>true</c>.
/// </summary>
/// <param name="member">The const class member function to use as the predicate.</param>
/// <returns>The detail::Terminal operation which returns <c>true</c> if all stream element returns <c>true</c> for the given predicate.</returns>
template <typename Ret, typename Class>
auto all(Ret(Class::*member)() const) {
    return all(std::mem_fn(member));
}
    }
}
#endif
