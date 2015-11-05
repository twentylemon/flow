
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
 
#ifndef FLOW_GENERATOR_CLOSEDRANGE_H
#define FLOW_GENERATOR_CLOSEDRANGE_H

#include "iota.h"
#include "../intermediate/take_while.h"

namespace flow {
    namespace generator {

/// <summary>
/// Creates a stream containing the elements in the range <c>[lower, upper]</c>, including <paramref name="upper"/>.
/// <para>The stream elements are incremented using <c>operator++</c>, and the range is computed using <c>operator&lt;=</c>.
/// The stream ends once <c>element &lt;= upper</c> returns <c>false</c>. That is, the stream produced is equivalent to:</para>
/// <code>iota(lower) | take_while([upper](T e) { return e &lt;= upper; })</code>
/// </summary>
/// <param name="lower">The lower bound of the range of elements to appear in the stream, inclusive.</param>
/// <param name="upper">The upper bound of the range of elements to appear in the stream, inclusive.</param>
/// <returns>A stream containing the elements in the range <c>[lower, upper]</c>.</returns>
/// <seealso cref="range()"/>
/// <seealso cref="iota()"/>
/// <seealso cref="take_while()"/>
template <typename T, typename U>
auto closed_range(T&& lower, U&& upper) {
    return iota(std::forward<T>(lower)) | intermediate::take_while([upper = std::forward<U>(upper)](auto&& ele) { return ele <= upper; });
}

/// <summary>
/// Creates a stream containing the elements in the range <c>[lower, upper]</c>, including <paramref name="upper"/>
/// counting up by <paramref name="increment"/> each step.
/// <para>The stream elements are incremented using the function <c>operator+(T, U)</c> with the <paramref name="increment"/> on the right
/// hand side of the operand, and the range is computed using <c>operator&lt;=</c>.
/// The stream ends once <c>element &lt;= upper</c> returns <c>false</c>. That is, the stream produced is equivalent to:</para>
/// <code>iota(lower, increment) | take_while([upper](T e) { return e &lt;= upper; })</code>
/// </summary>
/// <param name="lower">The lower bound of the range of elements to appear in the stream, inclusive.</param>
/// <param name="upper">The upper bound of the range of elements to appear in the stream, inclusive.</param>
/// <param name="increment">The value by which to increment each step in the stream.</param>
/// <returns>A stream containing the elements in the range <c>[lower, upper]</c> incremented using <c>operator+</c> <paramref name="increment"/>.</returns>
/// <seealso cref="range()"/>
/// <seealso cref="iota()"/>
/// <seealso cref="take_while()"/>
template <typename T, typename U, typename I>
auto closed_range(T&& lower, U&& upper, I&& increment) {
    return iota(std::forward<T>(lower), std::forward<I>(increment)) | intermediate::take_while([upper = std::forward<U>(upper)](auto&& ele) { return ele <= upper; });
}
    }
}
#endif
