
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
 
#ifndef FLOW_TERMINAL_EXECUTE_H
#define FLOW_TERMINAL_EXECUTE_H

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Forces the stream to be evaluated entirely.
/// <para>The stream will not normally be evaluated unless a terminal operation is applied, or an eager intermediate
/// operation is applied. This terminal forces evaluation of the entire stream. For example:</para>
/// <code>widgets | zip(iota(1), [](Widget& w, int i) { w.set_id(i); return i; });</code>
/// <para>The above stream assigns a unique id to each Widget, and the stream contains the ids. However, no terminal
/// operation is applied, no value is ever needed so none of the stream is ever evaluated. Appending <c> | execute()</c>
/// will force the stream to be evaluated, assigning the ids but ignoring the stream itself.</para>
/// </summary>
/// <returns>A detail::Terminal operation that evaluates the entire stream but ignores the elements.</returns>
inline auto execute() {
    return detail::make_terminal([](auto&& stream) {
        while (stream.has_next()) {
            stream.next();
        }
    });
}
    }
}
#endif
