
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
 
#ifndef FLOW_INTERMEDIATE_SORT_H
#define FLOW_INTERMEDIATE_SORT_H

#include <functional>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Sort.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Sorts the stream using the given comparator. By default, <c>operator&lt;</c> is used.
/// Sorting is an eager operation. On the creation of the <c>sort</c> operation, the entire stream
/// up to that point is evaluated and stored, then finally sorted before lazily continuing with the remainder
/// of the stream. Thus, the <c>sort</c> operation takes <c>O(n)</c> extra space and time, where <c>n</c>
/// is the size of the stream. For most applications, it will be beneficial to sort the source of the stream beforehand if possible.
/// For example, the following should be avoided:
/// <code>int min = my_vector | sort() | first(); // just an example</code><br/>
/// Instead, sorting the container in place beforehand will be more efficient as no copying takes place.<br/>
/// <code>std::sort(my_vector.begin(), my_vector.end());  int min = my_vector | first();</code>
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less{T}</c>.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that sorts the stream according to the compare function.</returns>
template <typename Compare = std::less<void>>
auto sort(Compare compare = Compare()) {
    return detail::make_intermediate([compare](auto&& stream) {
        return Stream<source::Sort<typename std::remove_reference_t<decltype(stream)>::source_type>>(std::move(stream.source()), compare, false);
    });
}

/// <summary>
/// Sorts the stream preserving relative order of elements using the given comparator. By default, <c>operator&lt;</c> is used.
/// Sorting is an eager operation. On the creation of the <c>sort</c> operation, the entire stream
/// up to that point is evaluated and stored, then finally sorted before lazily continuing with the remainder
/// of the stream. Thus, the <c>sort</c> operation takes <c>O(n)</c> extra space and time, where <c>n</c>
/// is the size of the stream. For most applications, it will be beneficial to sort the source of the stream beforehand if possible.
/// For example, the following should be avoided:<br>
/// <code>int min = my_vector | stable_sort() | first(); // just an example</code><br>
/// Instead, sorting the container in place beforehand will be more efficient as no copying takes place.<br>
/// <code>std::stable_sort(my_vector.begin(), my_vector.end());<br>int min = my_vector | first();</code>
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less{T}</c>.</param>
/// <returns>An <see cref="Intermediate{F}"/> operation that stable sorts the stream according to the compare function.</returns>
template <typename Compare = std::less<void>>
auto stable_sort(Compare compare = Compare()) {
    return detail::make_intermediate([compare](auto&& stream) {
        return Stream<source::Sort<typename std::remove_reference_t<decltype(stream)>::source_type>>(std::move(stream.source()), compare, true);
    });
}
    }
}
#endif
