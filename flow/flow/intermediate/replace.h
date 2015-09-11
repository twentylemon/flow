
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
 
#ifndef FLOW_INTERMEDIATE_REPLACE_H
#define FLOW_INTERMEDIATE_REPLACE_H

#include <functional>

#include "map.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Maps stream elements to new values if the original value returns <c>true</c> for the given predicate.
/// </summary>
/// <param name="predicate">The predicate, stream elements that return <c>true</c> will be mapped through <c>mapper</c>.</param>
/// <param name="mapper">The mapping operation to apply to elements that return <c>true</c> for <c>predicate</c>.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that replaces stream elements.</returns>
template <typename UnaryPredicate, typename UnaryOperation>
auto replace_map(UnaryPredicate predicate, UnaryOperation mapper) {
    return map([mapper, predicate](auto&& ele) {
        if (predicate(ele)) {
            return mapper(std::move(ele));
        }
        return std::move(ele);
    });
}

/// <summary>
/// Replaces elements in the stream by a new element if the stream element returns <c>true</c> for the given predicate.
/// </summary>
/// <param name="predicate">The predicate, stream elements that return <c>true</c> will be replaced by <c>replace_by</c>.</param>
/// <param name="replace_by">The value to replace stream elements by when the predicate returns <c>true</c>.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that replaces stream elements.</returns>
template <typename UnaryPredicate, typename T>
auto replace(UnaryPredicate predicate, const T& replace_by) {
    return replace_map(predicate, [replace_by](auto&&) { return replace_by; });
}

/// <summary>
/// Replaces elements in the stream by <c>new_value</c> if they are equal to <c>old_value</c>. Equality is checked by using
/// <c>operator==</c> on the elements.
/// </summary>
/// <param name="old_value">The value to replace in the stream by <c>new_value</c>.</param>
/// <param name="new_value">The value to replace with.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that replaces stream elements.</returns>
template <typename T>
auto replace(const T& old_value, const T& new_value) {
    return replace(std::bind1st(std::equal_to<T>(), old_value), new_value);
}
    }
}
#endif
