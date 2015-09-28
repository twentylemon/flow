
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
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>A detail::Terminal operation which gives the min and max elements from the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
/// \todo naive implementation that uses 2n - 2 comparisons; can this be improved to the 3n / 2 solution?
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
            if (compare(next, min)) {
                min = next;
            }
            else if (compare(max, next)) {
                max = next;
            }
        }
        return std::make_pair(min, max);
    });
    /*
    // this implementation is much slower; odd as min/max were faster as fold operations
    return fold_id([compare](auto&& pair, auto&& value) {
        if (compare(value, pair.first)) {
            pair.first = value;
        }
        else if (compare(pair.second, value)) {
            pair.second = value;
        }
        return pair;
    }, [](auto&& value) { return std::make_pair(value, value); });
    */
}
    }
}
#endif
