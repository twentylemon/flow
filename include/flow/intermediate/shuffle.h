
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
 
#ifndef FLOW_INTERMEDIATE_SHUFFLE_H
#define FLOW_INTERMEDIATE_SHUFFLE_H

#include <random>
#include <algorithm>

#include "Intermediate.h"
#include "../terminal/to.h"
#include "../generator/from_move.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Shuffles the stream using <paramref name="rng"/> as the source of randomness.
/// <para>By default, a <c>std::default_random_engine</c> with the default seed is used.</para>
/// <para>Shuffling is an eager operation. On application of the <c>shuffle</c> operation,
/// the entire stream up to that point is evaluated and stored before continuing with the remainder of the stream.
/// Thus, the <c>shuffle</c> operation takes <c>O(n)</c> extra space and time, where <c>n</c> is the size of the stream..</para>
/// </summary>
/// <param name="rng">The random number generator engine, from the <c>&lt;random&gt;</c> header.</param>
/// <returns>An intermediate operation which shuffles the stream.</returns>
template <typename Engine = std::default_random_engine>
auto shuffle(Engine rng = Engine()) {
    return detail::make_intermediate([rng](auto&& stream) mutable {
        auto vec = stream | terminal::to_vector();
        std::shuffle(vec.begin(), vec.end(), rng);
        return generator::from_move(std::move(vec));
    });
}
    }
}
#endif
