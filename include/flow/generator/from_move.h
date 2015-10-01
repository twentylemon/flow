
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
 
#ifndef FLOW_GENERATOR_FROMMOVE_H
#define FLOW_GENERATOR_FROMMOVE_H

#include "cycle_move.h"

namespace flow {
    namespace generator {

/// <summary>
/// Creates a Stream over <paramref name="container"/>.
/// <para>This extends the lifetime of temporary containers that are passed to it. That is, it is
/// safe to use temporaries as long as they are moved in.</para>
/// </summary>
/// <param name="container">The container to create a stream from.</param>
/// <returns>A stream over <paramref name="container"/>.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto from_move(Container&& container) {
    return cycle_move(std::move(container), 1);
}

/// <summary>
/// Creates a Stream over <paramref name="container"/> in reverse order.
/// <para>This extends the lifetime of temporary containers that are passed to it. That is, it is
/// safe to use temporaries as long as they are moved in.</para>
/// </summary>
/// <param name="container">The container to create a stream from.</param>
/// <returns>A reversed stream over <paramref name="container"/>.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto rfrom_move(Container&& container) {
    return rcycle_move(std::move(container), 1);
}
    }
}
#endif
