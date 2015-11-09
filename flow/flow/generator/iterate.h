
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
 
#ifndef FLOW_GENERATOR_ITERATE_H
#define FLOW_GENERATOR_ITERATE_H

#include "../Stream.h"
#include "../source/IterateFunc.h"

namespace flow {
    namespace generator {

        namespace detail {

/// <summary>
/// Empty base case for logical and of terms.
/// </summary>
template <typename... T>
struct conjunction : std::true_type { };

/// <summary>
/// Singleton base case for logical and of terms.
/// </summary>
template <typename T>
struct conjunction<T> : T { };

/// <summary>
/// Recursive case for logical and of terms.
/// </summary>
template <typename T, typename... U>
struct conjunction<T, U...> : std::conditional_t<T::value, conjunction<U...>, T> { };
        }

/// <summary>
/// Creates an infinite stream where values are created using successive calls to  the <paramref name="function"/>, starting with the values given.
/// <para>The next stream element is computed using the previous <c>n</c> stream elements applied to <paramref name="function"/>,
/// where <c>n</c> is the number of parameters that <paramref name="function/> takes.</para>
/// <para>For example, <c>iterate(std::plus&lt;int&gt;(), 0, 1)</c> would result in the stream
/// <c>0, 1, 1, 2, 3, 5, 8...</c> (the Fibonacci numbers). <c>0</c> and <c>1</c> are given, then the rest
/// are calculated as <c>0+1=1</c>, <c>1+1=2</c>, <c>1+2=3</c>, and <c>f_i = f_{i-2} + f_{i-1}</c> in general.</para>
/// </summary>
/// <param name="function">The iterating function.</param>
/// <param name="first">The first value the stream will contain, and the initial value to send to <paramref name="function"/>.</param>
/// <param name="...initial">The first values the stream will contain, and initial values to send to <paramref name="function"/>
/// to calculate further elements.</param>
/// <returns> An infinite stream that iterates <paramref name="function"/>.</returns>
template <typename IteratingFunction, typename T, typename... Args, typename = std::enable_if_t<detail::conjunction<std::is_same<T, Args>...>::value>>
auto iterate(IteratingFunction function, T&& first, Args&&... initial) {
    return Stream<source::IterateFunc<IteratingFunction, std::remove_reference_t<T>, sizeof...(Args)+1>>(function, std::forward<T>(first), std::forward<Args>(initial)...);
}
    }
}
#endif
