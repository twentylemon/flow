
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
 
#ifndef FLOW_INTERMEDIATE_PEEK_H
#define FLOW_INTERMEDIATE_PEEK_H

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Peek.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Executes <paramref name="action"/> for each element in the stream.
/// <para>This does not explicitly change the elements in the stream. The <paramref name="action"/> is
/// performed, then the stream value is passed on to the next operation. The <paramref name="action"/> will
/// only be performed if the stream element is actually reached. For example,</para>
/// <code>ints | peek([](int i) { std::cout << i << " "; }) | filter(is_even) | ...;    // will display all elements<br>
/// ints | filter(is_even) | peek([](int i) { std::cout << i << " "; }) | ...;          // will only display even elements</code>
/// </summary>
/// <param name="action">The function to apply to each element of the stream.</param>
/// <returns>An intermediate operation that executes a function for each stream element.</returns>
/// <seealso cref="each()"/>
template <typename UnaryFunction>
auto peek(UnaryFunction action) {
    return detail::make_intermediate([action](auto&& stream) {
        return Stream<source::Peek<std::remove_reference_t<decltype(stream.source())>, UnaryFunction>>(std::move(stream.source()), action);
    });
}

/// <summary>
/// Executes <paramref name="member"/> for each element in the Stream.
/// <para>This does not explicitly change the elements in the stream. The <paramref name="member"/> is
/// called, then the stream value is passed on to the next operation. The <paramref name="member"/> will
/// only be called if the stream element is actually reached. For example,</para>
/// <code>things | peek([](Thing& i) { std::cout << i << " "; }) | filter(is_something) | ...;  // will display all elements<br>
/// things | filter(is_something) | peek([](Thing& i) { std::cout << i << " "; }) | ...;        // will only display "something" elements</code>
/// </summary>
/// <param name="member">The function to apply to each element of the stream.</param>
/// <returns>An intermediate operation that executes a function for each stream element.</returns>
/// <seealso cref="each()"/>
template <typename Ret, typename Class>
auto peek(Ret(Class::*member)()) {
    return peek(std::mem_fn(member));
}

/// <summary>
/// Executes <paramref name="member"/> for each element in the Stream.
/// <para>This does not explicitly change the elements in the stream. The <paramref name="member"/> is
/// called, then the stream value is passed on to the next operation. The <paramref name="member"/> will
/// only be called if the stream element is actually reached. For example,</para>
/// <code>things | peek([](Thing& i) { std::cout << i << " "; }) | filter(is_something) | ...;  // will display all elements<br>
/// things | filter(is_something) | peek([](Thing& i) { std::cout << i << " "; }) | ...;        // will only display "something" elements</code>
/// </summary>
/// <param name="member">The function to apply to each element of the stream.</param>
/// <returns>An intermediate operation that executes a function for each stream element.</returns>
/// <seealso cref="each()"/>
template <typename Ret, typename Class>
auto peek(Ret(Class::*member)() const) {
    return peek(std::mem_fn(member));
}
    }
}
#endif
