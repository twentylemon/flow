
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
#ifndef LEMON_FLOW_TERMINAL_FOLD_H
#define LEMON_FLOW_TERMINAL_FOLD_H

#include "Terminal.h"

namespace lemon {
    namespace flow {
        namespace terminal {

/// <summary>
/// Folds the stream using the given accumulator. Applying this operation is the same as doing:
/// <code>for (T e : stream) { init = accumulator(init, e); }</code>
/// </summary>
/// <param name="accumulator">The accumulator, the function through which the stream is folded.</param>
/// <param name="init">The initial value to start the folding operation at.</param>
/// <returns>The <see cref="Terminal{F}"/> operation which folds the stream.</returns>
template <typename Accumulator, typename T>
auto fold(Accumulator accumulator, T&& init) {
    return detail::make_terminal([accumulator, init](auto&& stream) mutable {
        while (stream.has_next()) {
            init = accumulator(std::move(init), std::move(stream.next()));
        }
        return std::move(init);
    });
}

/// <summary>
/// Folds the stream using the given accumulator. The first element of the stream is used for the inital
/// folding value.
/// </summary>
/// <param name="accumulator">The accumulator, the function through which the stream is folded.</param>
/// <returns>The <see cref="Terminal{F}"/> operation which folds the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
template <typename Accumulator>
auto fold(Accumulator accumulator) {
    return detail::make_terminal([accumulator](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::fold(Accumulator) expects a non-empty stream");
        }
        return stream | fold(accumulator, std::move(stream.next()));
    });
}

/// <summary>
/// Folds the stream using the given accumulator. The result of <c>initializer</c> applied to the first element
/// of the stream is used for the inital folding value.
/// </summary>
/// <param name="accumulator">The accumulator, the function through which the stream is folded.</param>
/// <param name="initializer">The initializer function to apply to the first element in the stream.</param>
/// <returns>The <see cref="Terminal{F}"/> operation which folds the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
template <typename Accumulator, typename UnaryFunction>
auto fold_id(Accumulator accumulator, UnaryFunction initializer) {
    return detail::make_terminal([accumulator, initializer](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::fold_id(Accumulator, UnaryFunction) expects a non-empty stream");
        }
        return stream | fold(accumulator, std::move(initializer(stream.next())));
    });
}

/// <summary>
/// Folds the stream using the given accumulator. The result of <c>initializer</c> applied to <c>init</c>
/// is used for the inital folding value.
/// </summary>
/// <param name="accumulator">The accumulator, the function through which the stream is folded.</param>
/// <param name="initializer">The initializer function to apply to the first element in the stream.</param>
/// <param name="init">The initial value to start the folding operation at.</param>
/// <returns>The <see cref="Terminal{F}"/> operation which folds the stream.</returns>
template <typename Accumulator, typename UnaryFunction, typename T>
auto fold_id(Accumulator accumulator, UnaryFunction initializer, T&& init) {
    return fold(accumulator, std::move(initializer(init)));
}
        }
    }
}
#endif
