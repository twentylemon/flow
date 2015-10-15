
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
 
#ifndef FLOW_INTERMEDIATE_REPLACE_H
#define FLOW_INTERMEDIATE_REPLACE_H

#include <functional>

#include "map.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Maps stream elements to new values if the original element returns <c>true</c> for <paramref name="predicate"/>.
/// <para>Values that return <c>false</c> for <paramref name="predicate"/> are left unchanged.</para>
/// </summary>
/// <param name="predicate">Elements that return <c>true</c> will be mapped through <paramref name="mapper"/>.</param>
/// <param name="mapper">The mapping operation to apply to elements that return <c>true</c> for <paramref name="predicate"/>.</param>
/// <returns>An intermediate operation that replaces stream elements.</returns>
template <typename UnaryPredicate, typename UnaryOperation>
auto replace_map(UnaryPredicate predicate, UnaryOperation mapper) {
    return map([mapper, predicate](auto&& ele) {
        if (predicate(ele)) {
            return mapper(ele);
        }
        return ele;
    });
}

/// <summary>
/// Replaces elements in the stream by <paramref name="replace_by"/> if the stream element returns <c>true</c> for <paramref name="predicate"/>.
/// <para>Values that return <c>false</c> for <paramref name="predicate"/> are left unchanged.</para>
/// </summary>
/// <param name="predicate">The predicate, stream elements that return <c>true</c> will be replaced by <paramref name="replace_by"/>.</param>
/// <param name="replace_by">The value to replace stream elements by when <paramref name="predicate"/> returns <c>true</c>.</param>
/// <returns>An intermediate operation that replaces stream elements.</returns>
template <typename UnaryPredicate, typename T>
auto replace(UnaryPredicate predicate, T&& replace_by) {
    return replace_map(predicate, [replace_by = std::forward<T>(replace_by)](auto&&) { return replace_by; });
}

/// <summary>
/// Replaces elements in the stream by <paramref name="new_value"/> if they are equal to <paramref name="old_value"/>.
/// <para>Equality is checked by using <c>operator==</c> on the elements. Values not equal to <paramref name="old_value"/>
/// are left unchanged.</para>
/// </summary>
/// <param name="old_value">The value to replace in the stream by <paramref name="new_value"/>.</param>
/// <param name="new_value">The value to replace with.</param>
/// <returns>An intermediate operation that replaces stream elements.</returns>
template <typename T>
auto replace(T&& old_value, T&& new_value) {
    return replace(std::bind(std::equal_to<T>(), std::placeholders::_1, std::forward<T>(old_value)), std::forward<T>(new_value));
}
    }
}
#endif
