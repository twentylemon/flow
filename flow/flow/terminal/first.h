
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
#ifndef LEMON_FLOW_TERMINAL_FIRST_H
#define LEMON_FLOW_TERMINAL_FIRST_H

#include "Terminal.h"

namespace lemon {
    namespace flow {
        namespace terminal {

/// <summary>
/// Returns the first element from the stream.
/// </summary>
/// <returns>The <see cref="Terminal{F}"/> operation which gives the first element from the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
auto first() {
    return detail::make_terminal([](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::first() expects a non-empty stream");
        }
        return std::move(stream.next());
    });
}
        }
    }
}
#endif
