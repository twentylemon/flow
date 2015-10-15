
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
 
#ifndef FLOW_GENERATOR_IOTA_H
#define FLOW_GENERATOR_IOTA_H

#include "iterate.h"

namespace flow {
    namespace generator {

/// <summary>
/// Creates an infinite stream of values by incrementing <paramref name="begin"/> using <c>operator++</c>.
/// </summary>
/// <param name="begin">The first element of the stream, later elements are calculated by applying <c>operator++</c>.</param>
/// <returns>A Stream of values starting at <paramref name="begin"/>, counting up using <c>operator++</c> each time.</returns>
/// <seealso cref="range()"/>
/// <seealso cref="closed_range()"/>
template <typename T>
auto iota(T&& begin) {
    return iterate([](T& val) -> T& { return ++val; }, std::forward<T>(begin));
}

/// <summary>
/// Creates an infinite stream of values by incrementing <paramref name="begin"/> by <paramref name="increment"/>
/// using <c>operator+=</c>.
/// <para>The stream elements are computed using the function <c>operator+=(T, U)</c>.</para>
/// </summary>
/// <param name="begin">The first element of the stream, later elements are calculated by applying <c>operator+=</c> by <paramref name="increment"/>.</param>
/// <param name="increment">The value by which to increment each step in the stream.</param>
/// <returns>A Stream of values starting at <paramref name="begin"/>, counting up using <c>operator+=</c> by <paramref name="increment"/> each time.</returns>
/// <seealso cref="range()"/>
/// <seealso cref="closed_range()"/>
template <typename T, typename U>
auto iota(T&& begin, U&& increment) {
    return iterate([increment = std::forward<U>(increment)](T& val) -> T& { return val += increment; }, std::forward<T>(begin));
}
    }
}
#endif
