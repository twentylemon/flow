
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
#ifndef LEMON_FLOW_TERMINAL_DUMP_H
#define LEMON_FLOW_TERMINAL_DUMP_H

#include <string>
#include <iostream>
#include <iterator>

#include "copy.h"

namespace lemon {
    namespace flow {
        namespace terminal {

/// <summary>
/// Prints the stream elements to the <c>ostream</c> with the given delimeter between each element.
/// The output stream is returned.
/// </summary>
/// <param name="out">The output stream to print to.</param>
/// <param name="delimeter">The delimeter to add after each element, by default a single space is added.</param>
/// <returns>The <see cref="Terminal{F}"/> operation which print the stream elements to the output stream given.</returns>
auto dump(std::ostream& out = std::cout, const std::string& delimeter = " ") {
    return detail::make_terminal([&out, &delimeter](auto&& stream) -> std::ostream& {
        stream | copy(std::ostream_iterator<typename std::remove_reference_t<decltype(stream)>::value_type>(out, delimeter.c_str()));
        return out;
    });
    
}
        }
    }
}
#endif
