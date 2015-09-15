
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
 
#ifndef FLOW_TERMINAL_MIN_H
#define FLOW_TERMINAL_MIN_H

#include <functional>

#include "fold.h"

namespace flow {
    namespace terminal {
            
/// <summary>
/// Returns the minimum element from the stream according to <paramref name="compare"/>. By default <c>operator&lt;</c>
/// is used for comparisons.
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>A detail::Terminal operation which gives the minimum element from the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
template <typename Compare = std::less<void>>
auto min(Compare compare = Compare()) {
    return fold([compare](auto&& lhs, auto&& rhs) {
        if (compare(lhs, rhs)) {
            return std::move(lhs);
        }
        return std::move(rhs);
    });
}
    }
}
#endif
