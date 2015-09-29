
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
 
#ifndef FLOW_INTERMEDIATE_ZIP_H
#define FLOW_INTERMEDIATE_ZIP_H

#include <tuple>
#include <functional>

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
    std::tuple<LeftType, RightType> operator()(const LeftType& left, const RightType& right) const {
        return std::make_tuple(left, right);
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
    std::tuple<LeftType, RightTypes...> operator()(const LeftType& left, std::tuple<RightTypes...>&& right) const {
        return std::tuple_cat(std::make_tuple(left), std::move(right));
    }

    /// <summary>
    /// Returns a concatenated tuple of the tuple and value.
    /// </summary>
    /// <param name="left">The left stream element.</param>
    /// <param name="right">The right tuple; already zipped.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two elements.</returns>
    std::tuple<LeftType, RightTypes...> operator()(const LeftType& left, const std::tuple<RightTypes...>& right) const {
        return std::tuple_cat(std::make_tuple(left), right);
    }
};

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture left-zips, the right parameter is a tuple.
/// </summary>
template <typename LeftType, typename... RightTypes>
struct tuple_zipper<LeftType, const std::tuple<RightTypes...>> : tuple_zipper<LeftType, std::tuple<RightTypes...>>
{ };

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
    std::tuple<LeftTypes..., RightType> operator()(std::tuple<LeftTypes...>&& left, const RightType& right) const {
        return std::tuple_cat(std::move(left), std::make_tuple(right));
    }

    /// <summary>
    /// Returns a concatenated tuple of the tuple and value.
    /// </summary>
    /// <param name="left">The left tuple; already zipped.</param>
    /// <param name="right">The right stream element.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two elements.</returns>
    std::tuple<LeftTypes..., RightType> operator()(const std::tuple<LeftTypes...>& left, const RightType& right) const {
        return std::tuple_cat(left, std::make_tuple(right));
    }
};

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture right-zips, the left parameter is a tuple.
/// </summary>
template <typename... LeftTypes, typename RightType>
struct tuple_zipper<const std::tuple<LeftTypes...>, RightType> : tuple_zipper<std::tuple<LeftTypes...>, RightType> 
{ };

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
    std::tuple<LeftTypes..., RightTypes...> operator()(std::tuple<LeftTypes...>&& left, std::tuple<RightTypes...>&& right) const {
        return std::tuple_cat(std::move(left), std::move(right));
    }

    /// <summary>
    /// Returns a concatenated tuple of the two tuples.
    /// </summary>
    /// <param name="left">The left tuple; already zipped.</param>
    /// <param name="right">The right tuple; already zipped.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two tuples.</returns>
    std::tuple<LeftTypes..., RightTypes...> operator()(const std::tuple<LeftTypes...>& left, std::tuple<RightTypes...>&& right) const {
        return std::tuple_cat(left, std::move(right));
    }

    /// <summary>
    /// Returns a concatenated tuple of the two tuples.
    /// </summary>
    /// <param name="left">The left tuple; already zipped.</param>
    /// <param name="right">The right tuple; already zipped.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two tuples.</returns>
    std::tuple<LeftTypes..., RightTypes...> operator()(std::tuple<LeftTypes...>&& left, const std::tuple<RightTypes...>& right) const {
        return std::tuple_cat(std::move(left), right);
    }

    /// <summary>
    /// Returns a concatenated tuple of the two tuples.
    /// </summary>
    /// <param name="left">The left tuple; already zipped.</param>
    /// <param name="right">The right tuple; already zipped.</param>
    /// <returns>A concatenated <c>std::tuple</c> of the two tuples.</returns>
    std::tuple<LeftTypes..., RightTypes...> operator()(const std::tuple<LeftTypes...>& left, const std::tuple<RightTypes...>& right) const {
        return std::tuple_cat(left, right);
    }
};

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture re-zips. Both parameters are tuples.
/// </summary>
template <typename... LeftTypes, typename... RightTypes>
struct tuple_zipper<const std::tuple<LeftTypes...>, std::tuple<RightTypes...>> : tuple_zipper<std::tuple<LeftTypes...>, std::tuple<RightTypes...>>
{ };

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture re-zips. Both parameters are tuples.
/// </summary>
template <typename... LeftTypes, typename... RightTypes>
struct tuple_zipper<std::tuple<LeftTypes...>, const std::tuple<RightTypes...>> : tuple_zipper<std::tuple<LeftTypes...>, std::tuple<RightTypes...>>
{ };

/// <summary>
/// Default zip operation which concatenates tuple elements.
/// Specialized to capture re-zips. Both parameters are tuples.
/// </summary>
template <typename... LeftTypes, typename... RightTypes>
struct tuple_zipper<const std::tuple<LeftTypes...>, const std::tuple<RightTypes...>> : tuple_zipper<std::tuple<LeftTypes...>, std::tuple<RightTypes...>>
{ };

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
/// a single output which is used for the resultant stream.</para>
/// </summary>
/// <param name="right">The right stream to zip together with the operated stream.</param>
/// <param name="zipper">The zipping operation that combines the two streams.</param>
/// <returns>A detail::Intermediate operation that zips the two streams.</returns>
template <typename RightSource, typename BinaryOperation>
auto zip(Stream<RightSource>&& right, BinaryOperation zipper) {
    return detail::make_intermediate([right = std::move(right), zipper](auto&& left) mutable {
        return Stream<source::Zip<std::remove_reference_t<decltype(left.source())>, RightSource, BinaryOperation>>(std::move(left.source()), std::move(right.source()), zipper);
    });
}

/// <summary>
/// Zips the two streams together using <paramref name="zipper"/> as the zipping operation.
/// This is the same as <c>zip(from(container), zipper)</c>.
/// <para>A zipping operation is any function that takes an element from either stream as input and produces
/// a single output.</para>
/// </summary>
/// <param name="container">The container to zip together with this stream.</param>
/// <param name="zipper">The zipping operation that combines the two streams.</param>
/// <returns>A detail::Intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
template <typename Container, typename BinaryOperation, typename = typename std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto zip(Container& container, BinaryOperation zipper) {
    return zip(generator::from(container), zipper);
}

/// <summary>
/// Zips the two streams together using the default zipping operation. The default zip operation
/// creates tuples of the stream elements like <c>std::tuple&lt;T1, T2&gt;</c>. Multiple
/// <c>zip</c> operations concatenates these tuples together rather than nesting them.
/// </summary>
/// <param name="right">The right stream to zip together with the operated stream.</param>
/// <returns>A detail::Intermediate operation that zips the two streams.</returns>
/// <seealso cref="uncurry()"/>
template <typename RightSource>
auto zip(Stream<RightSource>&& right) {
    return zip(std::move(right), detail::zipper);
}

/// <summary>
/// Zips the two streams together using the default zipping operation. The default zip
/// creates tuples of the stream elements like <c>std::tuple&lt;T1, T2&gt;</c>. Multiple
/// <c>zip</c> operations concatenates these tuples together rather than nesting them.
///  This is the same as <c>zip(from(container))</c>.
/// </summary>
/// <param name="container">The container to zip together with this stream.</param>
/// <returns>A detail::Intermediate operation that zips the two streams.</returns>
/// <seealso cref="from()"/>
/// <seealso cref="uncurry()"/>
template <typename Container, typename = typename std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto zip(Container& container) {
    return zip(generator::from(container));
}
    }
}
#endif
