
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
 
#ifndef FLOW_TERMINAL_CONTAINS_H
#define FLOW_TERMINAL_CONTAINS_H

#include <functional>

#include "any.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns <c>true</c> if an element in the stream compares equal to <c>val</c> by <paramref name="equals"/>.
/// By default, <c>operator==</c> is used for equality comparisons.
/// </summary>
/// <param name="val">The value to search for in the stream.</param>
/// <param name="equals">The equals predicate, by default <c>operator==</c> is used.</param>
/// <returns>The detail::Terminal operation which returns <c>true</c> if the stream contains <c>val</c>.</returns>
template <typename T, typename EqualPredicate = std::equal_to<T>>
auto contains(const T& val, EqualPredicate equals = EqualPredicate()) {
    return any(std::bind(equals, val, std::placeholders::_1));
}
    }
}
#endif