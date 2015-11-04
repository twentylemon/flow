
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
 
#ifndef FLOW_TERMINAL_STATS_H
#define FLOW_TERMINAL_STATS_H

#include "../Stats.h"
#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns a Stats object which contains several statistics of the stream values.
/// <para>The number of elements, mean, standard deviation, variance, sum and sum of squares are always calculated.</para>
/// <para>Some statistical values are calculated as <c>ResultType</c>, others are calculated as <c>T</c>, the type of elements
/// in the stream. Calculating statistics requires that both <c>T</c> and <c>ResultType</c> behave as arithmetic types
/// (such as <c>int</c>, <c>double</c> or <c>std::complex</c>).</para>
/// <para>The other template parameters indicate whether or not to calculate additional statistics, all of which are not
/// calculated by default. The behavior of each of them is as follows (<c>n</c> is the size of the stream):</para>
/// <ul>
///     <li><c>MinMax</c> - calculate the minimum and maximum value of the stream. The min and max are calculated as <c>T</c>.
///         This operation uses an additional <c>2n</c> time (slower than using minmax()).</li>
///     <li><c>MedianMode</c> - calculate the median, mode, and frequency of each element of the stream.
///         The median is calculated as <c>ResultType</c>, the modes as <c>std::vector&lt;T&gt;</c>, and the frequency table as
///         <c>std::map&lt;T, std::size_t&gt;</c>. If there is an even number of elements in the stream, the median is calculated
///         as the average of the two possible medians. This operation uses an additional <c>O(n logn)</c> time (<c>n</c> map insertions)
///         and <c>O(k)</c> space, where <c>k</c> is the number of distinct values in the stream.</li>
/// </ul>
/// </summary>
/// <returns>A terminal operation that calculates various statistical values of the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
/// <seealso cref="Stats"/>
/// <seealso cref="count()"/>
/// <seealso cref="sum()"/>
/// <seealso cref="minmax()"/>
/// <seealso cref="to_map()"/>
/// \todo make this return an optional?
template <typename ResultType = double, bool MinMax = false, bool MedianMode = false>
auto stats() {
    return detail::make_terminal([](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::stats expects a non-empty stream");
        }
        using T = std::decay_t<decltype(stream.next())>;
        Stats<T, ResultType, MinMax, MedianMode> stats(stream.next());
        while (stream.has_next()) {
            stats.next(stream.next());
        }
        stats.end();
        return stats;
    });
}
    }
}
#endif
