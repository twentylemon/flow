
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
 
#ifndef FLOW_GENERATOR_FROM_H
#define FLOW_GENERATOR_FROM_H

#include <iterator>

#include "../Stream.h"
#include "../source/Iterator.h"

namespace flow {
    namespace generator {
        
        namespace detail {

/// <summary>
/// Type trait for a type having a member class <c>const_iterator</c>.
/// </summary>
template <typename T>
struct has_const_iterator
{
private:
    template <typename C> constexpr static std::true_type test(typename C::const_iterator*);
    template <typename C> constexpr static std::false_type test(...);
public:
    constexpr static bool value = decltype(test<T>(0))::value;
};
        }

/// <summary>
/// Creates a stream from the given iterator range.
/// </summary>
/// <param name="begin">The beginning of the range.</param>
/// <param name="end">The end of the range.</param>
/// <returns>A stream over the range.</returns>
template <typename Itr>
auto from(Itr begin, Itr end) {
    return Stream<source::Iterator<Itr>>(begin, end);
}

/// <summary>
/// Creates a stream over <paramref name="container"/>.
/// </summary>
/// <param name="container">The container to create a stream from.</param>
/// <returns>A stream over <paramref name="container"/>.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto from(Container& container) {
    return from(std::begin(container), std::end(container));
}

/// <summary>
/// Creates a stream over <paramref name="list"/>.
/// </summary>
/// <param name="list">The list to create a stream from.</param>
/// <returns>A stream over <paramref name="list"/>.</returns>
template <typename T>
auto from(std::initializer_list<T> list) {
    return from(std::begin(list), std::end(list));
}

/// <summary>
/// Creates a stream over <paramref name="container"/> in reverse order.
/// <para>The container requires bidirectional iterators.</para>
/// </summary>
/// <param name="container">The container to create a stream from.</param>
/// <returns>A reversed stream over <paramref name="container"/>.</returns>
template <typename Container, typename = std::enable_if_t<detail::has_const_iterator<Container>::value>>
auto rfrom(Container& container) {
    return from(std::rbegin(container), std::rend(container));
}
    }
}
#endif
