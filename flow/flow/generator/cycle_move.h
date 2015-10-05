
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
 
#ifndef FLOW_GENERATOR_CYCLEMOVE_H
#define FLOW_GENERATOR_CYCLEMOVE_H

#include <deque>

#include "from.h"
#include "generate.h"
#include "../intermediate/flat_map.h"

namespace flow {
    namespace generator {

/// <summary>
/// Creates an infinite stream which cycles <paramref name="container"/>.
/// <para>This extends the lifetime of temporary containers that are passed to it. That is, it is
/// safe to use temporaries as long as they are moved in.</para>
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <returns>An infinite stream which cycles <paramref name="container"/>.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto cycle_move(Container&& container) {
    return generate([container = std::move(container)](){ return std::make_pair(container.begin(), container.end()); })
        | intermediate::flat_map([](auto&& itr) { return from(itr.first, itr.second); });
}

/// <summary>
/// Creates a stream which cycles through <paramref name="container"/> <paramref name="n"/> times.
/// <para>This extends the lifetime of temporary containers that are passed to it. That is, it is
/// safe to use temporaries as long as they are moved in.</para>
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <param name="n">The number of times to repeat <paramref name="container"/>.</param>
/// <returns>A stream which cycles <paramref name="container"/> <paramref name="n"/> times.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto cycle_move(Container&& container, std::size_t n) {
    return generate([container = std::move(container)](){ return std::make_pair(container.begin(), container.end()); }, n)
        | intermediate::flat_map([](auto&& itr) { return from(itr.first, itr.second); });
}

/// <summary>
/// Creates an infinite stream which cycles <paramref name="list"/>.
/// <para>If the list is empty, this operation will crash via stack overflow. This can be
/// avoided by using cycle(std::initializer_list&lt;T&gt;,std::size_t).</para>
/// </summary>
/// <param name="list">The list to cycle through.</param>
/// <returns>An infinite stream which cycles <paramref name="list"/>.</returns>
template <typename T>
auto cycle(std::initializer_list<T> list) {
    return cycle_move(std::deque<T>(list));
}

/// <summary>
/// Creates a stream which cycles through <paramref name="list"/> <paramref name="n"/> times.
/// <para>To cycle a singleton list, use repeat().</para>
/// </summary>
/// <param name="list">The list to cycle through.</param>
/// <param name="n">The number of times to repeat <paramref name="list"/>.</param>
/// <returns>A stream which cycles <paramref name="list"/> <paramref name="n"/> times.</returns>
template <typename T>
auto cycle(std::initializer_list<T> list, std::size_t n) {
    return cycle_move(std::deque<T>(list), n);
}

/// <summary>
/// Creates an infinite stream which cycles <paramref name="container"/> in reverse order.
/// <para>This extends the lifetime of temporary containers that are passed to it. That is, it is
/// safe to use temporaries as long as they are moved in.</para>
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <returns>An infinite stream which cycles <paramref name="container"/>.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto rcycle_move(Container&& container) {
    return generate([container = std::move(container)](){ return std::make_pair(container.rbegin(), container.rend()); })
        | intermediate::flat_map([](auto&& itr) { return from(itr.first, itr.second); });
}

/// <summary>
/// Creates a stream which cycles through <paramref name="container"/> <paramref name="n"/> times in reverse order.
/// <para>This extends the lifetime of temporary containers that are passed to it. That is, it is
/// safe to use temporaries as long as they are moved in.</para>
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <param name="n">The number of times to repeat <paramref name="container"/>.</param>
/// <returns>A stream which cycles <paramref name="container"/> <paramref name="n"/> times.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto rcycle_move(Container&& container, std::size_t n) {
    return generate([container = std::move(container)](){ return std::make_pair(container.rbegin(), container.rend()); }, n)
        | intermediate::flat_map([](auto&& itr) { return from(itr.first, itr.second); });
}
    }
}
#endif
