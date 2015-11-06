
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
 
#ifndef FLOW_INTERMEDIATE_SORT_H
#define FLOW_INTERMEDIATE_SORT_H

#include <functional>

#include "Intermediate.h"
#include "../terminal/to.h"
#include "../generator/from_move.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Sorts the stream using the given comparator, <c>operator&lt;</c> by default.
/// <para>Sorting is an <em>stateful</em> operation. On application of the <c>sort</c> operation, the entire stream
/// up to that point is evaluated and stored, then finally sorted before continuing with the sorted version
/// of the stream. Thus, the <c>sort</c> operation takes <c>O(n)</c> extra space and time to copy the stream,
/// and the additional <c>O(n logn)</c> to sort, where <c>n</c> is the size of the stream. For most applications,
/// it will be beneficial to sort the source of the stream beforehand if possible. For example, the following should
/// be <em>avoided</em>:</para>
/// <code>int min = my_vector | sort() | first(); // just an example</code>
/// <para>Instead, sorting the container in place beforehand will be more efficient as no additional copying takes place.</para>
/// <code>std::sort(my_vector.begin(), my_vector.end());<br/>
/// int min = my_vector | first();</code>
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>An intermediate operation that sorts the stream according to the compare function.</returns>
/// <seealso cref="stable_sort()"/>
template <typename Compare = std::less<void>>
auto sort(Compare compare = Compare()) {
    return detail::make_intermediate([compare](auto&& stream) {
        auto vec = stream | terminal::to_vector();
        std::sort(vec.begin(), vec.end(), compare);
        return generator::from_move(std::move(vec));
    });
}

/// <summary>
/// Sorts the stream preserving relative order of elements using the given comparator, <c>operator&lt;</c> by default.
/// <para>Sorting is an <em>stateful</em> operation. On application of the <c>stable_sort</c> operation, the entire stream
/// up to that point is evaluated and stored, then finally sorted before continuing with the sorted version
/// of the stream. Thus, the <c>stable_sort</c> operation takes <c>O(n)</c> extra space and time to copy the stream,
/// and the additional <c>O(n logn)</c> to sort, where <c>n</c> is the size of the stream. For most applications,
/// it will be beneficial to sort the source of the stream beforehand if possible. For example, the following should
/// be <em>avoided</em>:</para>
/// <code>int min = my_vector | stable_sort() | first(); // just an example</code>
/// <para>Instead, sorting the container in place beforehand will be more efficient as no additional copying takes place.</para>
/// <code>std::stable_sort(my_vector.begin(), my_vector.end());<br/>
/// int min = my_vector | first();</code>
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>An intermediate operation that stable sorts the stream according to the compare function.</returns>
/// <seealso cref="sort()"/>
template <typename Compare = std::less<void>>
auto stable_sort(Compare compare = Compare()) {
    return detail::make_intermediate([compare](auto&& stream) {
        auto vec = stream | terminal::to_vector();
        std::stable_sort(vec.begin(), vec.end(), compare);
        return generator::from_move(std::move(vec));
    });
}
    }
}
#endif
