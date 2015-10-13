
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
 
#ifndef FLOW_PRINTTUPLE_H
#define FLOW_PRINTTUPLE_H

#include <tuple>
#include <iostream>

namespace flow {

    namespace detail {

/// <summary>
/// End recursive case for printing tuples.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="tuple">The tuple to display.</param>
template <std::size_t N, typename... T>
std::enable_if_t<N >= sizeof...(T)> print_tuple(std::ostream& out, const std::tuple<T...>& tuple) {
}

/// <summary>
/// The normal case for printing tuples. A comma is printed before the item.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="tuple">The tuple to display.</param>
template <std::size_t N, typename... T>
std::enable_if_t<(N > 0 && N < sizeof...(T))> print_tuple(std::ostream& out, const std::tuple<T...>& tuple) {
    out << ", " << std::get<N>(tuple);
    print_tuple<N + 1>(out, tuple);
}

/// <summary>
/// Start recursive case for printing tuples. No comma is printed before the item.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="tuple">The tuple to display.</param>
template <std::size_t N, typename... T>
std::enable_if_t<N == 0> print_tuple(std::ostream& out, const std::tuple<T...>& tuple) {
    out << std::get<N>(tuple);
    print_tuple<N + 1>(out, tuple);
}
    }
}

#ifndef FLOW_PRINTTUPLE_NO_STD
namespace std {
#else
namespace flow {
#endif

/// <summary>
/// Overload <c>operator&lt;&lt;</c> to display pair types.
/// <para>The pair is printed as <c>(first, second)</c>. Each item is displayed using <c>operator&lt;&lt;</c>.</para>
/// <para>This is defined in the <c>std</c> namespace to allow dump() to work correctly.
/// To exclude this function from being defined in the <c>std</c> namespace, <c>\#define FLOW_PRINTTUPLE_NO_STD</c>
/// will remove it and define it in the <c>flow</c> namespace instead.</para>
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="pair">The pair to display.</param>
/// <returns><paramref name="out"/></returns>
template <typename F, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<F, S>& pair) {
    return out << '(' << pair.first << ", " << pair.second << ')';
}

/// <summary>
/// Overload <c>operator&lt;&lt;</c> to display tuple types.
/// <para>The tuple is printed as <c>(item1, item2, ...)</c>. Each item is displayed using <c>operator&lt;&lt;</c>.</para>
/// <para>This is defined in the <c>std</c> namespace to allow dump() to work correctly.
/// To exclude this function from being defined in the <c>std</c> namespace, <c>\#define FLOW_PRINTTUPLE_NO_STD</c>
/// will remove it and define it in the <c>flow</c> namespace instead.</para>
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="tuple">The tuple to display.</param>
/// <returns><paramref name="out"/></returns>
template <typename... T>
std::ostream& operator<<(std::ostream& out, const std::tuple<T...>& tuple) {
    out << '(';
    flow::detail::print_tuple<0>(out, tuple);
    return out << ')';
}
}
#endif
