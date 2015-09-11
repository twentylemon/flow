
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
 
#ifndef FLOW_UNCURRY_H
#define FLOW_UNCURRY_H

#include <tuple>

namespace flow {
    namespace detail {

// this code adapted from Scott Prager's blog post: http://yapb-soc.blogspot.ca/2012/12/fun-with-tuples.html
// since c++14, std::integer_sequence exists, but still a very helpful post

/// <summary>
/// Applies the tuple to the curried function.
/// </summary>
/// <param name="">The index list.</param>
/// <param name="function">The curried function.</param>
/// <param name="tuple">The tuple to apply to the function.</param>
/// <returns>The return value of the function.</returns>
template <std::size_t... index, typename Function, typename Tuple>
constexpr auto apply(std::index_sequence<index...>, Function function, Tuple&& tuple) {
    return function(std::get<index>(std::forward<Tuple>(tuple))...);
}

/// <summary>
/// Wrapper for uncurrying functions.
/// </summary>
template <typename CurryFunction>
struct uncurrier
{
public:
    /// <summary>
    /// Initializes a new instance of the <see cref="uncurrier{CurryFunction}"/> struct.
    /// </summary>
    /// <param name="curry_function">The curry function to wrap.</param>
    uncurrier(CurryFunction curry_function) : _curry_function(curry_function) { }

    /// <summary>
    /// Applies the tuple to the stored curried function.
    /// </summary>
    /// <param name="tuple">The tuple to apply.</param>
    /// <returns>The return value of the curried function.</returns>
    template <typename... Types>
    constexpr auto operator()(std::tuple<Types...>&& tuple) const {
        return apply(std::make_index_sequence<sizeof...(Types)>(), _curry_function, std::forward<std::tuple<Types...>>(tuple));
    }

protected:
    CurryFunction _curry_function;  // the function to uncurry
};
    }

/// <summary>
/// Uncurries the specified function. Given a function which takes several parameters, converts that function
/// into a function which takes one <c>std::tuple</c> of those arguments instead.
/// </summary>
/// <param name="curry_function">The curried function to wrap.</param>
/// <returns>An object with an <c>operator()(std::tuple&lt;Types...&gt;)</c> which wraps <c>curry_function</c>.</returns>
template <typename CurryFunction>
auto uncurry(CurryFunction curry_function) {
    return flow::detail::uncurrier<CurryFunction>(curry_function);
}
}
#endif
