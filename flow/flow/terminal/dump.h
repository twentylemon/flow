
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
 
#ifndef FLOW_TERMINAL_DUMP_H
#define FLOW_TERMINAL_DUMP_H

#include <string>
#include <iostream>
#include <iterator>

#include "copy.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Prints the stream elements to the <c>std::ostream</c> with the <paramref name="delimiter"/> printed between each element.
/// A reference to the output stream is returned.
/// </summary>
/// <param name="out">The output stream to print to.</param>
/// <param name="delimiter">The delimiter to add after each element, by default a single space is added.</param>
/// <returns>The detail::Terminal operation which print the stream elements to <paramref name="out"/>.</returns>
auto dump(std::ostream& out = std::cout, const std::string& delimiter = " ") {
    return detail::make_terminal([&out, &delimiter](auto&& stream) -> std::ostream& {
        stream | copy(std::ostream_iterator<typename std::remove_reference_t<decltype(stream)>::value_type>(out, delimiter.c_str()));
        return out;
    });
    
}
    }
}
#endif
