
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
 
#ifndef FLOW_TERMINAL_TERMINAL_H
#define FLOW_TERMINAL_TERMINAL_H

#include "../Compose.h"
#include "../Stream.h"

namespace flow {
    namespace terminal {
        namespace detail {

/// <summary>
/// A terminal operation for a Stream. Terminal operations finalize the stream by doing some operation
/// like looping or summing.
/// </summary>
template <typename F>
class Terminal
{
public:
    template <typename G> friend class intermediate::detail::Intermediate;

    /// <summary>
    /// Initializes a new instance of the Terminal class.
    /// </summary>
    /// <param name="operation">The operation.</param>
    Terminal(F&& operation) : _operation(std::forward<F>(operation)) { }

    /// <summary>
    /// Executes the operation on the stream given.
    /// </summary>
    /// <param name="stream">The stream.</param>
    /// <returns>The result of the operation.</returns>
    template <typename Source>
    std::result_of_t<F(Stream<Source>&&)> operator()(Stream<Source>&& stream) {
        return _operation(std::move(stream));
    }

    /// <summary>
    /// Composes this operation with another function.
    /// </summary>
    /// <param name="function">The function.</param>
    /// <returns>A terminal operation of this composes with the function given.</returns>
    template <typename G>
    Terminal<flow::detail::Compose<G, F>> then(G&& function) {
        return Terminal<flow::detail::Compose<G, F>>(flow::detail::Compose<G, F>(std::forward<G>(function), std::move(_operation)));
    }

    /// <summary>
    /// Returns a Terminal which returns the contained value of the optional returned by this instance.
    /// </summary>
    /// <returns>A Terminal which gives the contained value of an optional.</returns>
    auto value() {
        return then([](auto&& opt) { return *opt; });
    }

    /// <summary>
    /// Returns a Terminal which returns optional::value_or of the result of this instance.
    /// </summary>
    /// <param name="default_value">The value to return if there is no contained value in the optional.</param>
    /// <returns>A copy of the contained value if it exists, <paramref name="default_value" /> otherwise.</returns>
    template <typename U>
    auto value_or(U&& default_value) {
        return then([default_value = std::forward<U>(default_value)](auto&& opt) { return opt.value_or(std::move(default_value)); });
    }

private:
    F _operation;   // the terminal operation
};

/// <summary>
/// Constructs a Terminal object using the function given.
/// </summary>
/// <param name="function">The function.</param>
/// <returns>A Terminal operation wrapping the function.</returns>
template <typename Function>
Terminal<Function> make_terminal(Function&& function) {
    return Terminal<Function>(std::forward<Function>(function));
}
        }
    }
}
#endif
