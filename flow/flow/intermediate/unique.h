
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
 
#ifndef FLOW_INTERMEDIATE_UNIQUE_H
#define FLOW_INTERMEDIATE_UNIQUE_H

#include <functional>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Unique.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Sorts and extracts only unique elements from the Stream. By default, <c>operator&lt;</c> is used for comparisons
/// and equality. As with sorting, this operation is eager, the entire stream up to this operation's creation
/// is evaluated and stored. Thus, the <c>unique</c> operation takes <c>O(n)</c> extra space and time, where <c>n</c>
/// is the size of the stream.
/// </summary>
/// <param name="compare">The compare function, by default <c>std::less&lt;void&gt;</c>.</param>
/// <returns>A detail::Intermediate operation that sorts the Stream according to the compare function and keeps only unique elements.</returns>
template <typename Compare = std::less<void>>
auto unique(Compare compare = Compare()) {
    return detail::make_intermediate([compare](auto&& stream) {
        return Stream<source::Unique<typename std::remove_reference_t<decltype(stream)>::source_type>>(std::move(stream.source()), compare);
    });
}
    }
}
#endif
