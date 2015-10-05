
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
 
#ifndef FLOW_INTERMEDIATE_FLATMAP_H
#define FLOW_INTERMEDIATE_FLATMAP_H

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/FlatMap.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Transforms each element in the Stream using <paramref name="operation"/>.
/// Each element is transformed into a new stream. The resultant stream is a concatenation of all created streams.
/// </summary>
/// <param name="operation">The operation that creates a new stream from a stream element.</param>
/// <returns>A detail::Intermediate operation that creates new streams and concatenations them together.</returns>
template <typename UnaryOperation>
auto flat_map(UnaryOperation operation) {
    return detail::make_intermediate([operation](auto&& stream) {
        return Stream<source::FlatMap<std::remove_reference_t<decltype(stream.source())>, UnaryOperation>>(std::move(stream.source()), operation);
    });
}
    }
}
#endif
