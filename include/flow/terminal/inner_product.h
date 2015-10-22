
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
 
#ifndef FLOW_TERMINAL_INNERPRODUCT_H
#define FLOW_TERMINAL_INNERPRODUCT_H

#include <functional>

#include "Terminal.h"
#include "../generator/from.h"
#include "fold.h"
#include "../intermediate/zip.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns the inner product (also known as dot product) of the two streams.
/// <para>The inner product is the sum of products of the elements of the two streams. If the streams are not
/// the same length, the calculation stops once the shorter of the two streams is empty.</para>
/// <para>This operation is the same as performing</para>
/// <code>left | zip(right, times) | fold(plus, value);</code>
/// </summary>
/// <param name="right">The right stream to compute the inner product with.</param>
/// <param name="value">The starting value for the summation, defaults to <c>T()</c>.</param>
/// <param name="times">The multiplication operation, defaults to <c>operator*</c>.</param>
/// <param name="plus">The addition operation, defaults to <c>operator+</c>.</param>
/// <returns>The inner product between <paramref name="right"/> and the operated stream.</returns>
/// <seealso cref="zip()"/>
/// <seealso cref="fold()"/>
template <typename Source, typename T, typename ProductFunction = std::multiplies<void>, typename SumFunction = std::plus<T>>
auto inner_product(Stream<Source>&& right, T&& value, ProductFunction times = ProductFunction(), SumFunction plus = SumFunction()) {
    return detail::make_terminal([right = std::move(right), value = std::forward<T>(value), times, plus](auto&& left) mutable {
        return left | intermediate::zip(std::move(right), times) | fold(plus, std::forward<T>(value));
    });
}

/// <summary>
/// Returns the inner product (also known as dot product) of the stream and iterator range, this is the same
/// as <c>inner_product(from(begin, end), value, times, plus)</c>.
/// <para>The inner product is the sum of products of the elements of the stream and iterator range.
/// If they are not the same length, the calculation stops once the shorter of the two is empty.</para>
/// </summary>
/// <param name="begin">The beginning of the range to compute inner product with.</param>
/// <param name="end">The end of the range to compute inner product with.</param>
/// <param name="value">The starting value for the summation, defaults to <c>T()</c>.</param>
/// <param name="times">The multiplication operation, defaults to <c>operator*</c>.</param>
/// <param name="plus">The addition operation, defaults to <c>operator+</c>.</param>
/// <returns>The inner product between <c>[begin, end)</c> and the operated stream.</returns>
/// <seealso cref="zip()"/>
/// <seealso cref="fold()"/>
/// <seealso cref="from()"/>
template <typename Itr, typename T, typename ProductFunction = std::multiplies<void>, typename SumFunction = std::plus<T>>
auto inner_product(Itr begin, Itr end, T&& value, ProductFunction times = ProductFunction(), SumFunction plus = SumFunction()) {
    return inner_product(generator::from(begin, end), std::forward<T>(value), times, plus);
}

/// <summary>
/// Returns the inner product (also known as dot product) of the stream and <paramref name="container"/>, this is the same
/// as <c>inner_product(from(container), value, times, plus)</c>.
/// <para>The inner product is the sum of products of the elements of the stream and <paramref name="container"/>.
/// If they are not the same length, the calculation stops once the shorter of the two is empty.</para>
/// </summary>
/// <param name="container">The container to compute the inner product with.</param>
/// <param name="value">The starting value for the summation, defaults to <c>T()</c>.</param>
/// <param name="times">The multiplication operation, defaults to <c>operator*</c>.</param>
/// <param name="plus">The addition operation, defaults to <c>operator+</c>.</param>
/// <returns>The inner product between <paramref name="container"/> and the operated stream.</returns>
/// <seealso cref="zip()"/>
/// <seealso cref="fold()"/>
/// <seealso cref="from()"/>
template <typename Container, typename T, typename ProductFunction = std::multiplies<void>, typename SumFunction = std::plus<T>, typename = std::enable_if_t<generator::detail::has_const_iterator<Container>::value>>
auto inner_product(Container& container, T&& value, ProductFunction times = ProductFunction(), SumFunction plus = SumFunction()) {
    return inner_product(generator::from(container), std::forward<T>(value), times, plus);
}

/// <summary>
/// Returns the inner product (also known as dot product) of the stream and <paramref name="list"/>, this is the same
/// as <c>inner_product(from(list), value, times, plus)</c>.
/// <para>The inner product is the sum of products of the elements of the stream and <paramref name="list"/>.
/// If they are not the same length, the calculation stops once the shorter of the two is empty.</para>
/// </summary>
/// <param name="list">The list to compute the inner product with.</param>
/// <param name="value">The starting value for the summation, defaults to <c>T()</c>.</param>
/// <param name="times">The multiplication operation, defaults to <c>operator*</c>.</param>
/// <param name="plus">The addition operation, defaults to <c>operator+</c>.</param>
/// <returns>The inner product between <paramref name="list"/> and the operated stream.</returns>
/// <seealso cref="zip()"/>
/// <seealso cref="fold()"/>
/// <seealso cref="from()"/>
template <typename T, typename U, typename ProductFunction = std::multiplies<void>, typename SumFunction = std::plus<T>>
auto inner_product(std::initializer_list<T> list, U&& value, ProductFunction times = ProductFunction(), SumFunction plus = SumFunction()) {
    return inner_product(generator::from(list), std::forward<U>(value), times, plus);
}
    }
}
#endif
