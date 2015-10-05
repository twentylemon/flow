
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
 
#ifndef FLOW_GENERATOR_REPEAT_H
#define FLOW_GENERATOR_REPEAT_H

#include "generate.h"
#include "../intermediate/limit.h"

namespace flow {
    namespace generator {

/// <summary>
/// Creates an infinite stream containing <paramref name="value"/> repeated over and over.
/// </summary>
/// <param name="value">The value in the stream.</param>
/// <returns>An infinite stream containing only <paramref name="value"/>.</returns>
template <typename T>
auto repeat(T&& value) {
    return generate([value = std::forward<T>(value)](){ return value; });
}

/// <summary>
/// Creates a stream containing <paramref name="value"/> repeated <paramref name="n"/> times.
/// </summary>
/// <param name="value">The value in the stream.</param>
/// <param name="n">The number of times to repeat <paramref name="value"/>.</param>
/// <returns>A stream containing <paramref name="n"/> copies of <paramref name="value"/>.</returns>
template <typename T>
auto repeat(T&& value, std::size_t n) {
    return repeat(std::forward<T>(value)) | intermediate::limit(n);
}
    }
}
#endif
