
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
#ifndef FLOW_TERMINAL_COPY_H
#define FLOW_TERMINAL_COPY_H

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Copies the elements in the stream into the range beginning at <c>result</c>. An iterator to the end
/// of the destination range is returned, pointing to the element after the last element copied.
/// </summary>
/// <param name="result">The output iterator to the initial position in the destination range.</param>
/// <returns>The <see cref="Terminal{F}"/> operation which copies the stream into the <c>result</c> range.</returns>
template <typename OutputIterator>
auto copy(OutputIterator result) {
    return detail::make_terminal([result](auto&& stream) mutable {
        while (stream.has_next()) {
            *result = std::move(stream.next());
            ++result;
        }
        return result;
    });
}
    }
}
#endif
