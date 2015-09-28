
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
 
#ifndef FLOW_GENERATOR_ITERATE_H
#define FLOW_GENERATOR_ITERATE_H

#include "../Stream.h"
#include "../source/IterateFunc.h"

namespace flow {
    namespace generator {

        namespace detail {

/// <summary>
/// Extracts the first type out of a parameter pack.
/// </summary>
template <typename Head, typename... Tail>
struct HeadType
{
    using type = Head;
};
        }

/// <summary>
/// Creates an infinite Stream where values are created using successive calls to
/// the <paramref name="function"/>, starting with the values given.
/// <para>For example, <c>iterate(std::plus&lt;int&gt;(), 0, 1)</c> would result in the stream
/// <c>0, 1, 1, 2, 3, 5, 8...</c>. <c>0</c> and <c>1</c> are given, then the rest
/// are calculated as <c>0+1=1</c>, <c>1+1=2</c>, <c>f_i = f_{i-2} + f_{i-1}</c>.</para>
/// </summary>
/// <param name="function">The iterating function.</param>
/// <param name="...initial">The first values the stream will contain, and initial values to send to the iterating function
/// to calculate further elements.</param>
/// <returns>An infinite stream that iterates the function given.</returns>
template <typename IteratingFunction, typename... Args>
auto iterate(IteratingFunction function, Args&&... initial) {
    using T = std::remove_reference_t<typename detail::HeadType<Args...>::type>;
    return Stream<source::IterateFunc<IteratingFunction, T, sizeof...(Args)>>(function, std::forward<Args>(initial)...);
}
    }
}
#endif
