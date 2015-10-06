
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
 
#ifndef FLOW_TERMINAL_PRODUCT_H
#define FLOW_TERMINAL_PRODUCT_H

#include <functional>

#include "fold.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Computes the product of all the elements in the stream using <c>operator*</c>.
/// </summary>
/// <returns>A terminal operation which multiplies the elements in the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
inline auto product() {
    return fold(std::multiplies<void>());
}

/// <summary>
/// Computes the product of all the elements in the stream using <c>operator*</c>, starting the
/// product at <paramref name="init"/>.
/// </summary>
/// <param name="init">The initial value to start the product at.</param>
/// <returns>A terminal operation which multiplies the elements in the stream.</returns>
template <typename T>
auto product(T&& init) {
    return fold(std::multiplies<T>(), std::forward<T>(init));
}
    }
}
#endif
