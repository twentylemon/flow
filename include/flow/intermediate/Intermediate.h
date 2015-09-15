
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
 
#ifndef FLOW_INTERMEDIATE_INTERMEDIATE_H
#define FLOW_INTERMEDIATE_INTERMEDIATE_H

#include "../Compose.h"
#include "../terminal/Terminal.h"
#include "../Stream.h"

namespace flow {
    namespace intermediate {
        namespace detail {

/// <summary>
/// An intermediate stream operation. Takes over the stream and applies some
/// transformation to the stream elements or the stream itself.
/// Intermediate operations are streams, they have no value without a Terminal operation.
/// </summary>
template <typename F>
class Intermediate
{
public:
    /// <summary>
    /// Initializes a new instance of the Intermediate class.
    /// </summary>
    /// <param name="operation">The operation.</param>
    Intermediate(F&& operation) : _operation(std::forward<F>(operation)) { }

    /// <summary>
    /// Transforms the stream into another stream using the operation.
    /// </summary>
    /// <param name="stream">The stream.</param>
    /// <returns>A new stream with this operation applied to it.</returns>
    template <typename Source>
    std::result_of_t<F(Stream<Source>&&)> operator()(Stream<Source>&& stream) {
        return _operation(std::move(stream));
    }

    /// <summary>
    /// Pipes the Intermediate operation into this stream. The result is a composition
    /// of this and rhs' operations on the stream.
    /// </summary>
    /// <param name="rhs">The Intermediate operation to pipe into the stream.</param>
    /// <returns>The composition of this and rhs as A detail::Intermediate operation.</returns>
    template <typename G>
    Intermediate<flow::detail::Compose<G, F>> operator|(Intermediate<G>&& rhs) {
        return Intermediate<flow::detail::Compose<G, F>>(flow::detail::Compose<G, F>(std::move(rhs._operation), std::move(_operation)));
    }

    /// <summary>
    /// Pipes the Terminal operation onto the end of this stream. The result is a
    /// composition  of this and rhs' operations on the stream.
    /// </summary>
    /// <param name="rhs">The terminal::detail::Terminal operation to pipe onto the end of the stream.</param>
    /// <returns>The composition of this and rhs as a Terminal operation.</returns>
    template <typename G>
    terminal::detail::Terminal<flow::detail::Compose<G, F>> operator|(terminal::detail::Terminal<G>&& rhs) {
        return terminal::detail::Terminal<flow::detail::Compose<G, F>>(flow::detail::Compose<G, F>(std::move(rhs._operation), std::move(_operation)));
    }

private:
    F _operation;   // the stream operation
};

/// <summary>
/// Constructs An Intermediate object using the function given.
/// </summary>
/// <param name="function">The function.</param>
/// <returns>A detail::Intermediate operation wrapping the function.</returns>
template <typename Function>
Intermediate<Function> make_intermediate(Function&& function) {
    return Intermediate<Function>(std::forward<Function>(function));
}
        }
    }
}
#endif
