
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
 
#ifndef FLOW_TERMINAL_EACH_H
#define FLOW_TERMINAL_EACH_H

#include <functional>

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Executes a function for each element in the stream.
/// <para>The executed function is returned.</para>
/// </summary>
/// <param name="func">The function to apply to each element of the stream.</param>
/// <returns>A terminal operation that executes a function for each stream element.</returns>
/// <seealso cref="peek()"/>
template <typename UnaryFunction>
auto each(UnaryFunction func) {
    return detail::make_terminal([func](auto&& stream) {
        while (stream.has_next()) {
            func(stream.next());
        }
        return std::move(func);
    });
}

/// <summary>
/// Executes the member function for each element in the stream.
/// <para>The executed function is returned.</para>
/// </summary>
/// <param name="member">The class member function to use as the operation.</param>
/// <returns>A terminal operation that executes a member function for each stream element.</returns>
/// <seealso cref="peek()"/>
template <typename Ret, typename Class>
auto each(Ret(Class::*member)()) {
    return each(std::mem_fn(member));
}

/// <summary>
/// Executes the member function for each element in the stream.
/// <para>The executed function is returned.</para>
/// </summary>
/// <param name="member">The class member function to use as the operation.</param>
/// <returns>A terminal operation that executes a member function for each stream element.</returns>
/// <seealso cref="peek()"/>
template <typename Ret, typename Class>
auto each(Ret(Class::*member)() const) {
    return each(std::mem_fn(member));
}
    }
}
#endif
