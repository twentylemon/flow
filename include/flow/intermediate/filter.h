
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
 
#ifndef FLOW_INTERMEDIATE_FILTER_H
#define FLOW_INTERMEDIATE_FILTER_H

#include <functional>

#include "../Stream.h"
#include "Intermediate.h"
#include "../source/Filter.h"

namespace flow {
    namespace intermediate {

/// <summary>
/// Removes elements from the Stream that return <c>false</c> for <paramref name="predicate"/>.
/// </summary>
/// <param name="predicate">The predicate used to filter stream elements.</param>
/// <returns>A detail::Intermediate operation that filters the stream elements.</returns>
template <typename UnaryPredicate>
auto filter(UnaryPredicate predicate) {
    return detail::make_intermediate([predicate](auto&& stream) {
        return Stream<source::Filter<typename std::remove_reference_t<decltype(stream)>::source_type, UnaryPredicate>>(std::move(stream.source()), predicate);
    });
}

/// <summary>
/// Removes elements from the Stream which are evaluated to <c>false</c>. This is an overload for streams
/// with types convertible to <c>bool</c>.
/// </summary>
/// <returns>A detail::Intermediate operation that filters the stream elements.</returns>
auto filter() {
    return filter([](const auto& ele) { return static_cast<bool>(ele); });
}

/// <summary>
/// Removes elements from the Stream that return <c>false</c> for <paramref name="member"/>.
/// </summary>
/// <param name="member">The class member function to use for filtering, the return type must be convertible to <c>bool</c>.</param>
/// <returns>A detail::Intermediate operation that filters the stream elements.</returns>
template <typename Ret, typename Class>
auto filter(Ret(Class::*member)()) {
    return filter(std::mem_fn(member));
}

/// <summary>
/// Removes elements from the Stream that return <c>false</c> for <paramref name="member"/>.
/// </summary>
/// <param name="member">The const class member function to use for filtering, the return type must be convertible to <c>bool</c>.</param>
/// <returns>A detail::Intermediate operation that filters the stream elements.</returns>
template <typename Ret, typename Class>
auto filter(Ret(Class::*member)() const) {
    return filter(std::mem_fn(member));
}
    }
}
#endif
