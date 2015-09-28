
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
 
#ifndef FLOW_GENERATOR_CLOSEDRANGE_H
#define FLOW_GENERATOR_CLOSEDRANGE_H

#include <functional>

#include "iota.h"
#include "../intermediate/take_while.h"

namespace flow {
    namespace generator {

/// <summary>
/// Produces a Stream containing the elements in the range <c>[lower, upper]</c>, including <paramref name="upper"/>.
/// <para>Stream elements are incremented using <c>operator++</c>, and the range is computed using <c>operator&lt;=</c>.
/// The stream ends once <c>element &lt;= upper</c> returns <c>false</c>. That is, the stream produced is equivalent to:</para>
/// <code>iota(lower) | take_while([upper](T e) { return e &lt;= upper; })</code>
/// </summary>
/// <param name="lower">The lower bound of the range of elements to appear in the stream, inclusive.</param>
/// <param name="upper">The upper bound of the range of elements to appear in the stream, inclusive.</param>
/// <returns>A Stream containing the elements in the range <c>[lower, upper]</c>.</returns>
/// <seealso cref="range()"/>
/// <seealso cref="iota()"/>
/// <seealso cref="take_while()"/>
template <typename T>
auto closed_range(T&& lower, T&& upper) {
    return iota(std::forward<T>(lower)) | intermediate::take_while(std::bind(std::less_equal<T>(), std::placeholders::_1, std::forward<T>(upper)));
}

/// <summary>
/// Produces a Stream containing the elements in the range <c>[lower, upper]</c>, including <paramref name="upper"/>
/// counting up by <paramref name="increment"/> each step.
/// <para>Stream elements are incremented using the function <c>operator+(T, U)</c>, and the range is computed using <c>operator&lt;=</c>.
/// The stream ends once <c>element &lt;= upper</c> returns <c>false</c>. That is, the stream produced is equivalent to:</para>
/// <code>iota(lower, increment) | take_while([upper](T e) { return e &lt;= upper; })</code>
/// </summary>
/// <param name="lower">The lower bound of the range of elements to appear in the stream, inclusive.</param>
/// <param name="upper">The upper bound of the range of elements to appear in the stream, inclusive.</param>
/// <param name="increment">The value by which to increment each step in the stream.</param>
/// <returns>A Stream containing the elements in the range <c>[lower, upper]</c> incremented using <c>operator+</c> <paramref name="increment"/>.</returns>
/// <seealso cref="range()"/>
/// <seealso cref="iota()"/>
/// <seealso cref="take_while()"/>
template <typename T, typename U>
auto closed_range(T&& lower, T&& upper, U&& increment) {
    return iota(std::forward<T>(lower), std::forward<U>(increment)) | intermediate::take_while(std::bind(std::less_equal<T>(), std::placeholders::_1, std::forward<T>(upper)));
}
    }
}
#endif
