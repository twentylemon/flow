
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
 
#ifndef FLOW_TERMINAL_MIN_H
#define FLOW_TERMINAL_MIN_H

#include <functional>

#include "fold.h"

namespace flow {
    namespace terminal {
            
/// <summary>
/// Returns the minimum element from the stream as an optional according to <paramref name="compare"/>, <c>operator&lt;</c> by default.
/// </summary>
/// <para>If there are multiple minimum elements, the first such element is returned.</para>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>A detail::Terminal operation which gives the minimum element from the stream.</returns>
/// <seealso cref="max()"/>
/// <seealso cref="minmax()"/>
/// <seealso cref="stats()"/>
/// <seealso cref="optional"/>
/// \todo benchmark non-fold implementation
template <typename Compare = std::less<void>>
auto min(Compare compare = Compare()) {
    return fold([compare](auto&& lhs, auto&& rhs) {
        if (compare(rhs, lhs)) {
            return rhs;
        }
        return lhs;
    });
}
template <typename Compare = std::less<void>>
auto min_(Compare compare = Compare()) {
    return detail::make_terminal([compare](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        if (!stream.has_next()) {
            return optional<T>();
        }
        optional<T> value(stream.next());
        while (stream.has_next()) {
            auto& next = stream.next();
            if (compare(next, *value)) {
                *value = next;
            }
        }
        return value;
    });
}
    }
}
#endif
