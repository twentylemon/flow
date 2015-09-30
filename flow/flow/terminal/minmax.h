
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
 
#ifndef FLOW_TERMINAL_MINMAX_H
#define FLOW_TERMINAL_MINMAX_H

#include <functional>

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns the minimum and maximum elements as a pair from the stream according to <paramref name="compare"/>.
/// The first element is the minimum and the second element is the maximum. By default <c>operator&lt;</c>
/// is used for comparisons.
/// <para>If there are multiple min/max elements, the <em>first</em> min element and the <em>last</em>
/// max element are returned.</para>
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>A detail::Terminal operation which gives the min and max elements from the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
template <typename Compare = std::less<void>>
auto minmax(Compare compare = Compare()) {
    return detail::make_terminal([compare](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::minmax(Compare) expects a non-empty stream");
        }
        auto min = stream.next();
        auto max = min;
        while (stream.has_next()) {
            auto& next = stream.next();
            if (!stream.has_next()) {
                if (compare(next, min)) { min = next; }
                else if (compare(max, next)) { max = next; }
                break;  // skip next has_next() call
            }
            else {
                auto& later = stream.next();
                if (compare(later, next)) {
                    if (compare(later, min)) { min = later; }
                    if (compare(max, next)) { max = next; }
                }
                else {
                    if (compare(next, min)) { min = next; }
                    if (compare(max, later)) { max = later; }
                }
            }
        }
        return std::make_pair(std::move(min), std::move(max));
    });
}
    }
}
#endif
