
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
 
#ifndef FLOW_INTERMEDIATE_ZIP_H
#define FLOW_INTERMEDIATE_ZIP_H

#include <tuple>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Zip.h"
#include "../generator/from.h"

namespace flow {
    namespace intermediate {

        namespace detail {
/// <summary>
/// Default zip operation which creates a tuple of the elements.
/// </summary>
template <typename LeftType, typename RightType>
struct tuple_zipper
{
    /// <summary>
    /// Returns a tuple of the two elements.
    /// </summary>
    /// <param name="left">The left stream element.</param>
    /// <param name="right">The right stream element.</param>
    /// <returns>A <c>std::tuple</c> of the two elements.</returns>
    template <typename Left, typename Right>
    auto operator()(Left&& left, Right&& right) const {
        return std::make_tuple(std::forward<Left>(left), std::forward<Right>(right));
    }
};

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture left-zips, the right parameter is a tuple.
/// </summary>
template <typename LeftType, typename... RightTypes>
struct tuple_zipper<LeftType, std::tuple<RightTypes...>> 
{
    /// <summary>
    /// Returns a concatenated tuple of the tuple and value.
    /// </summary>
    /// <param name="left">The left stream element.</param>
    /// <param name="right">The right tuple; already zipped.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two elements.</returns>
    template <typename Left, typename Tuple>
    auto operator()(Left&& left, Tuple&& right) const {
        return std::tuple_cat(std::make_tuple(std::forward<Left>(left)), std::forward<Tuple>(right));
    }
};

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture right-zips, the left parameter is a tuple.
/// </summary>
template <typename... LeftTypes, typename RightType>
struct tuple_zipper<std::tuple<LeftTypes...>, RightType>
{
    /// <summary>
    /// Returns a concatenated tuple of the tuple and value.
    /// </summary>
    /// <param name="left">The left tuple; already zipped.</param>
    /// <param name="right">The right stream element.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two elements.</returns>
    template <typename Tuple, typename Right>
    auto operator()(Tuple&& left, Right&& right) const {
        return std::tuple_cat(std::forward<Tuple>(left), std::make_tuple(std::forward<Right>(right)));
    }
};

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture re-zips. Both parameters are tuples.
/// </summary>
template <typename... LeftTypes, typename... RightTypes>
struct tuple_zipper<std::tuple<LeftTypes...>, std::tuple<RightTypes...>>
{
    /// <summary>
    /// Returns a concatenated tuple of the two tuples.
    /// </summary>
    /// <param name="left">The left tuple; already zipped.</param>
    /// <param name="right">The right tuple; already zipped.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two tuples.</returns>
    template <typename Left, typename Right>
    auto operator()(Left&& left, Right&& right) const {
        return std::tuple_cat(std::forward<Left>(left), std::forward<Right>(right));
    }
};

/// <summary>
/// The default zipper wrapper function. Zips streams by concatenating them together as tuples.
/// </summary>
const auto zipper = [](auto&& left, auto&& right) {
    return tuple_zipper<std::remove_reference_t<decltype(left)>, std::remove_reference_t<decltype(right)>>()(left, right);
};
        }

/// <summary>
/// Zips the two streams together using <paramref name="zipper"/> as the zipping operation.
/// <para>A zipping operation is any function that takes the front element from both streams as input and produces
/// a single output which is used for the resultant stream. The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="right">The right stream to zip together with the operated stream.</param>
/// <param name="zipper">The zipping operation that combines the two streams.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
template <typename RightSource, typename BinaryOperation>
auto zip(Stream<RightSource>&& right, BinaryOperation zipper) {
    return detail::make_intermediate([right = std::move(right), zipper](auto&& left) mutable {
        return Stream<source::Zip<std::remove_reference_t<decltype(left.source())>, RightSource, BinaryOperation>>(std::move(left.source()), std::move(right.source()), zipper);
    });
}

/// <summary>
/// Zips the two streams together using <paramref name="zipper"/> as the zipping operation,
/// this is the same as <c>zip(from(begin, end), zipper)</c>.
/// <para>A zipping operation is any function that takes an element from either stream as input and produces
/// a single output which is used for the resultant stream. The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="begin">The beginning of the range to zip with this stream.</param>
/// <param name="end">The end of the range to zip with this stream.</param>
/// <param name="zipper">The zipping operation that combines the two streams.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
template <typename Itr, typename BinaryOperation>
auto zip(Itr begin, Itr end, BinaryOperation zipper) {
    return zip(generator::from(begin, end), zipper);
}

/// <summary>
/// Zips the two streams together using <paramref name="zipper"/> as the zipping operation,
/// this is the same as <c>zip(from(container), zipper)</c>.
/// <para>A zipping operation is any function that takes an element from either stream as input and produces
/// a single output which is used for the resultant stream. The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="container">The container to zip together with this stream.</param>
/// <param name="zipper">The zipping operation that combines the two streams.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
template <typename Container, typename BinaryOperation, typename = std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto zip(Container& container, BinaryOperation zipper) {
    return zip(generator::from(container), zipper);
}

/// <summary>
/// Zips the two streams together using <paramref name="zipper"/> as the zipping operation,
/// this is the same as <c>zip(from(list), zipper)</c>.
/// <para>A zipping operation is any function that takes an element from either stream as input and produces
/// a single output which is used for the resultant stream. The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="list">The list to zip together with this stream.</param>
/// <param name="zipper">The zipping operation that combines the two streams.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
template <typename T, typename BinaryOperation>
auto zip(std::initializer_list<T> list, BinaryOperation zipper) {
    return zip(generator::from(list), zipper);
}

/// <summary>
/// Zips the two streams together using the default zipping operation.
/// <para>The default zip operation creates tuples of the stream elements like <c>std::tuple&lt;T1, T2&gt;</c>.
/// Multiple <c>zip</c> operations concatenates these tuples together rather than nesting them.
/// When using the default zipper, the types being zipped together must be default constructible.</para>
/// <para>The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="right">The right stream to zip together with the operated stream.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="uncurry()"/>
template <typename RightSource>
auto zip(Stream<RightSource>&& right) {
    return zip(std::move(right), detail::zipper);
}

/// <summary>
/// Zips the two streams together using the default zipping operation,
/// this is the same as <c>zip(from(begin, end))</c>.
/// <para>The default zip operation creates tuples of the stream elements like <c>std::tuple&lt;T1, T2&gt;</c>.
/// Multiple <c>zip</c> operations concatenates these tuples together rather than nesting them.
/// When using the default zipper, the types being zipped together must be default constructible.</para>
/// <para>The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="begin">The beginning of the range to zip with this stream.</param>
/// <param name="end">The end of the range to zip with this stream.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
/// <seealso cref="uncurry()"/>
template <typename Itr>
auto zip(Itr begin, Itr end) {
    return zip(generator::from(begin, end));
}

/// <summary>
/// Zips the two streams together using the default zipping operation,
/// this is the same as <c>zip(from(container))</c>.
/// <para>The default zip operation creates tuples of the stream elements like <c>std::tuple&lt;T1, T2&gt;</c>.
/// Multiple <c>zip</c> operations concatenates these tuples together rather than nesting them.
/// When using the default zipper, the types being zipped together must be default constructible.</para>
/// <para>The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="container">The container to zip together with this stream.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
/// <seealso cref="uncurry()"/>
template <typename Container, typename = std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto zip(Container& container) {
    return zip(generator::from(container));
}

/// <summary>
/// Zips the two streams together using the default zipping operation,
/// this is the same as <c>zip(from(list))</c>.
/// <para>The default zip operation creates tuples of the stream elements like <c>std::tuple&lt;T1, T2&gt;</c>.
/// Multiple <c>zip</c> operations concatenates these tuples together rather than nesting them.
/// When using the default zipper, the types being zipped together must be default constructible.</para>
/// <para>The resultant stream is as long as the shortest input stream.</para>
/// </summary>
/// <param name="list">The list to zip together with this stream.</param>
/// <returns>An intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
/// <seealso cref="uncurry()"/>
template <typename T>
auto zip(std::initializer_list<T> list) {
    return zip(generator::from(list));
}
    }
}
#endif
