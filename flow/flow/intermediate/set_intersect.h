
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

#ifndef FLOW_INTERMEDIATE_SETINTERSECT_H
#define FLOW_INTERMEDIATE_SETINTERSECT_H

#include <functional>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/SetIntersect.h"
#include "../generator/from.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Intersects the <paramref name="right"/> stream into the operated (<paramref name="left"/>) stream while maintaining sorted order.
/// <para>The intersection operation combines both streams keeping only elements in both streams and maintains sorted order. Both the
/// <paramref name="left"/> and <paramref name="right"/> streams are assumed to already be sorted according to <paramref name="compare"/>.
/// If not, this operation produces undefined results. By default, <c>operator&lt;</c> is used as the comparator. Elements in the result
/// stream are only from the <paramref name="left"/> stream. If the source streams contain duplicate values, the result stream will
/// contain the minimum number of those elements that appear in both streams.</para>
/// </summary>
/// <param name="right">The right stream to intersect with the left stream while maintaining sorted order.</param>
/// <param name="compare">The compare function by which both streams are sorted.</param>
/// <returns>An intermediate operation that intersects the two streams while maintaining sorted order.</returns>
template <typename RightSource, typename Compare = std::less<void>>
auto set_intersect(Stream<RightSource>&& right, Compare compare = Compare()) {
    return detail::make_intermediate([right = std::move(right), compare](auto&& left) mutable {
        return Stream<source::SetIntersect<std::remove_reference_t<decltype(left.source())>, std::remove_reference_t<decltype(right.source())>, Compare>>(std::move(left.source()), std::move(right.source()), compare);
    });
}

/// <summary>
/// Intersects the iterator range into the operated (<paramref name="left"/>) stream while maintaining sorted order,
/// this is the same as <c>set_intersect(from(begin, end), compare)</c>.
/// <para>The intersection operation combines both streams keeping only elements in both streams and maintains sorted order. Both the
/// <paramref name="left"/> stream and iterator range are assumed to already be sorted according to <paramref name="compare"/>.
/// If not, this operation produces undefined results. By default, <c>operator&lt;</c> is used
/// as the comparator. Elements in the result stream are only from the <paramref name="left"/> stream. If the source streams contain
/// duplicate values, the result stream will contain the minimum number of those elements that appear in both streams.</para>
/// </summary>
/// <param name="begin">The beginning of the range to intersect.</param>
/// <param name="end">The end of the range to intersect.</param>
/// <param name="compare">The compare function by which both streams are sorted.</param>
/// <returns>An intermediate operation that intersects the two streams while maintaining sorted order.</returns>
/// <seealso cref="from()"/>
template <typename Itr, typename Compare = std::less<void>>
auto set_intersect(Itr begin, Itr end, Compare compare = Compare()) {
    return set_intersect(generator::from(begin, end), compare);
}

/// <summary>
/// Intersects <paramref name="container"/> into the operated (<paramref name="left"/>) stream while maintaining sorted order,
/// this is the same as <c>set_intersect(from(container), compare)</c>.
/// <para>The intersection operation combines both streams keeping only elements in both streams and maintains sorted order. Both the
/// <paramref name="left"/> stream and <paramref name="container"/> are assumed to already be sorted according to <paramref name="compare"/>.
/// If not, this operation produces undefined results. By default, <c>operator&lt;</c> is used
/// as the comparator. Elements in the result stream are only from the <paramref name="left"/> stream. If the source streams contain duplicate
/// values, the result stream will contain the minimum number of those elements that appear in both streams.</para>
/// </summary>
/// <param name="container">The container to intersect with the stream while maintaining sorted order.</param>
/// <param name="compare">The compare function by which both streams are sorted.</param>
/// <returns>An intermediate operation that intersects the two streams while maintaining sorted order.</returns>
/// <seealso cref="from()"/>
template <typename Container, typename Compare = std::less<void>, typename = std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto set_intersect(Container& container, Compare compare = Compare()) {
    return set_intersect(generator::from(container), compare);
}

/// <summary>
/// Intersects <paramref name="list"/> into the operated (<paramref name="left"/>) stream while maintaining sorted order,
/// this is the same as <c>set_intersect(from(list), compare)</c>.
/// <para>The intersection operation combines both streams keeping only elements in both streams and maintains sorted order. Both the
/// <paramref name="left"/> stream and <paramref name="list"/> are assumed to already be sorted according to <paramref name="compare"/>.
/// If not, this operation produces undefined results. By default, <c>operator&lt;</c> is used
/// as the comparator. Elements in the result stream are only from the <paramref name="left"/> stream. If the source streams contain
/// duplicate values, the result stream will contain the minimum number of those elements that appear in both streams.</para>
/// </summary>
/// <param name="list">The list to intersect with the stream while maintaining sorted order.</param>
/// <param name="compare">The compare function by which both streams are sorted.</param>
/// <returns>An intermediate operation that intersects the two streams while maintaining sorted order.</returns>
/// <seealso cref="from()"/>
template <typename T, typename Compare = std::less<void>>
auto set_intersect(std::initializer_list<T> list, Compare compare = Compare()) {
    return set_intersect(generator::from(list), compare);
}
    }
}
#endif
