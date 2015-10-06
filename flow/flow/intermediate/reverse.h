
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
 
#ifndef FLOW_INTERMEDIATE_REVERSE_H
#define FLOW_INTERMEDIATE_REVERSE_H

#include <algorithm>

#include "../generator/from_move.h"
#include "../terminal/to.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Reverses the elements in the Stream.
/// <para>Reversing is an eager operation. On application of the <c>reverse</c> operation,
/// the entire stream up to that point is evaluated and stored before continuing with the remainder of the stream.
/// Thus, the <c>reverse</c> operation takes <c>O(n)</c> extra space and time, where <c>n</c> is the size of the stream.
/// For most applications, it will be beneficial to reverse the stream beforehand by rfrom() or rcycle().</para>
/// </summary>
/// <returns>An intermediate operation that reverses the stream.</returns>
inline auto reverse() {
    return detail::make_intermediate([](auto&& stream) {
        return generator::rfrom_move(stream | terminal::to_vector());
    });
}
    }
}
#endif
