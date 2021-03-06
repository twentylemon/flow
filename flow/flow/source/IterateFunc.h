
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
 
#ifndef FLOW_SOURCE_ITERATEFUNC_H
#define FLOW_SOURCE_ITERATEFUNC_H

#include <array>
#include <algorithm>

#include "../uncurry.h"
#include "GeneratorSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that generates an infinite stream using successive calls to an iterated function.
/// Initial values are given, then later values are calculated using previous values in the stream.
/// </summary>
template <typename IteratingFunction, typename T, std::size_t N>
class IterateFunc : public GeneratorSource<T>
{
public:
    using base = GeneratorSource<T>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the IterateFunc class.
    /// </summary>
    /// <param name="function">The function to iterate.</param>
    /// <param name="...initial">The initial arguments to pass to the function.</param>
    template <typename... Args>
    IterateFunc(IteratingFunction function, Args&&... initial) : base(), _function(uncurry(function)), _values({std::forward<Args>(initial)...}) { }

    IterateFunc(const IterateFunc<IteratingFunction, T, N>&) = delete;
    IterateFunc(IterateFunc<IteratingFunction, T, N>&&) = default;

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        base::assign_temp_current(_values[0]);  // copy the value
        _values[0] = _function(_values);        // destroy the first value
        std::rotate(_values.begin(), _values.begin() + 1, _values.end());
        return base::next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        next();
    }

private:
    flow::detail::uncurrier<IteratingFunction> _function;   // the function to iterate
    std::array<T, N> _values;                               // the current values to pass to the function
};

/// <summary>
/// Stream source that generates an infinite stream using successive calls to an iterated unary function.
/// The initial value is given, then later values are calculated using previous values in the stream.
/// </summary>
template <typename IteratingFunction, typename T>
class IterateFunc<IteratingFunction, T, 1> : public GeneratorSource<T>
{
public:
    using base = GeneratorSource<T>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the IterateFunc class.
    /// </summary>
    /// <param name="function">The function to iterate.</param>
    /// <param name="...initial">The initial arguments to pass to the function.</param>
    template <typename Arg>
    IterateFunc(IteratingFunction function, Arg&& initial) : base(), _function(function), _value(std::forward<Arg>(initial)) { }

    IterateFunc(const IterateFunc<IteratingFunction, T, 1>&) = delete;
    IterateFunc(IterateFunc<IteratingFunction, T, 1>&&) = default;

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        base::assign_temp_current(_value);
        _value = _function(_value);
        return base::next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        next();
    }

private:
    IteratingFunction _function;    // the function to iterate
    T _value;                       // the current value to pass to the function
};
    }
}
#endif
