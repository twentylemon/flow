
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
 
#ifndef FLOW_GENERATOR_CYCLE_H
#define FLOW_GENERATOR_CYCLE_H

#include "from.h"
#include "repeat.h"
#include "../intermediate/flat_map.h"

namespace flow {
    namespace generator {

 /// <summary>
 /// Creates an infinite stream which cycles the iterator range.
 /// </summary>
 /// <param name="begin">The beginning of the range.</param>
 /// <param name="end">The end of the range.</param>
 /// <returns>An infinite stream which cycles the range.</returns>
template <typename Itr>
auto cycle(Itr begin, Itr end) {
    return repeat(std::make_pair(begin, end)) | intermediate::flat_map([](const auto& pair) { return from(pair.first, pair.second); });
}

/// <summary>
/// Creates a stream which cycles the iterator range <paramref name="n"/> times.
/// </summary>
/// <param name="begin">The beginning of the range.</param>
/// <param name="end">The end of the range.</param>
/// <param name="n">The number of times to repeat the range.</param>
/// <returns>A stream which cycles the range <paramref name="n"/> times.</returns>
template <typename Itr>
auto cycle(Itr begin, Itr end, std::size_t n) {
    return repeat(std::make_pair(begin, end), n) | intermediate::flat_map([](const auto& itr) { return from(itr.first, itr.second); });
}

/// <summary>
/// Creates an infinite stream which cycles <paramref name="container"/>.
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <returns>An infinite stream which cycles <paramref name="container"/>.</returns>
template <typename Container, typename = typename std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto cycle(Container& container) {
    return cycle(container.begin(), container.end());
}

/// <summary>
/// Creates a stream which cycles through <paramref name="container"/> <paramref name="n"/> times.
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <param name="n">The number of times to repeat <paramref name="container"/>.</param>
/// <returns>A stream which cycles <paramref name="container"/> <paramref name="n"/> times.</returns>
template <typename Container, typename = typename std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto cycle(Container& container, std::size_t n) {
    return cycle(container.begin(), container.end(), n);
}

/// <summary>
/// Creates an infinite stream which cycles <paramref name="container"/> in reverse order.
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <returns>An infinite stream which cycles <paramref name="container"/>.</returns>
template <typename Container, typename = typename std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto rcycle(Container& container) {
    return cycle(container.rbegin(), container.rend());
}

/// <summary>
/// Creates a stream which cycles through <paramref name="container"/> <paramref name="n"/> times in reverse order.
/// </summary>
/// <param name="container">The container to cycle through.</param>
/// <param name="n">The number of times to repeat <paramref name="container"/>.</param>
/// <returns>A stream which cycles <paramref name="container"/> <paramref name="n"/> times.</returns>
template <typename Container, typename = typename std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto rcycle(Container& container, std::size_t n) {
    return cycle(container.rbegin(), container.rend(), n);
}
    }
}
#endif
