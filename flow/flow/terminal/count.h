
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
 
#ifndef FLOW_TERMINAL_COUNT_H
#define FLOW_TERMINAL_COUNT_H

#include "Terminal.h"
#include "../intermediate/filter.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns the number of elements in the stream as <c>std::size_t</c>.
/// </summary>
/// <returns>A terminal operation which counts the number of elements in the stream.</returns>
/// <seealso cref="count_if()"/>
inline auto count() {
    return detail::make_terminal([](auto&& stream) {
        std::size_t size = 0;
        while (stream.has_next()) {
            stream.lazy_next();
            ++size;
        }
        return size;
    });
}

/// <summary>
/// Returns the number of elements in the stream that return <c>true</c>
/// for <paramref name="predicate"/> as <c>std::size_t</c>.
/// </summary>
/// <returns>A terminal operation which counts the number of elements in the stream that return <c>true</c> for <paramref name="predicate"/>.</returns>
/// <seealso cref="count()"/>
/// <seealso cref="filter()"/>
template <typename UnaryPredicate>
auto count_if(UnaryPredicate predicate) {
    return intermediate::filter(predicate) | count();
}

/// <summary>
/// Returns the number of the occurrences of <paramref name="value"/> in the stream as <c>std::size_t</c>.
/// <para>Equality is checking using <c>operator==</c>.</para>
/// </summary>
/// <returns>A terminal operation which counts of the occurrences of <paramref name="value"/> in the stream.</returns>
/// <seealso cref="count_if()"/>
/// <seealso cref="filter()"/>
/// <seealso cref="contains()"/>
template <typename T>
auto count(T&& value) {
    return count_if([value = std::forward<T>(value)](auto&& ele) { return ele == value; });
}
    }
}
#endif
