
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
 
#ifndef FLOW_TERMINAL_FOLD_H
#define FLOW_TERMINAL_FOLD_H

#include "Terminal.h"
#include "../optional.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Folds the stream using the <paramref name="accumulator"/>.
/// <para>Applying this operation is equivalent to</para>
/// <code>for (T e : stream) { init = accumulator(init, e); }</code>
/// </summary>
/// <param name="accumulator">The function through which the stream is folded.</param>
/// <param name="init">The initial value to start the folding operation at.</param>
/// <returns>A terminal operation which folds the stream.</returns>
template <typename Accumulator, typename T>
auto fold(Accumulator accumulator, T&& init) {
    return detail::make_terminal([accumulator, init = std::forward<T>(init)](auto&& stream) mutable {
        while (stream.has_next()) {
            init = accumulator(init, stream.next());
        }
        return init;
    });
}

/// <summary>
/// Folds the stream using <paramref name="accumulator"/>.
/// <para>The result of <paramref name="initializer"/> applied to <paramref name="init"/> is used for
/// the initial folding value.</para>
/// </summary>
/// <param name="accumulator">The accumulator, the function through which the stream is folded.</param>
/// <param name="initializer">The initializer function to apply to the first element in the stream.</param>
/// <param name="init">The initial value to start the folding operation at.</param>
/// <returns>A terminal operation which folds the stream.</returns>
template <typename Accumulator, typename UnaryFunction, typename T>
auto fold_id(Accumulator accumulator, UnaryFunction initializer, T&& init) {
    return fold(accumulator, initializer(std::forward<T>(init)));
}

/// <summary>
/// Folds the stream using <paramref name="accumulator"/>.
/// <para>The first element of the stream is used for the initial folding value.</para>
/// </summary>
/// <param name="accumulator">The function through which the stream is folded.</param>
/// <returns>A terminal operation which folds the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
/// <seealso cref="opt::fold()"/>
template <typename Accumulator>
auto fold(Accumulator accumulator) {
    return detail::make_terminal([accumulator](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::fold(Accumulator) expects a non-empty stream");
        }
        return stream | terminal::fold(accumulator, stream.next());
    });
}

/// <summary>
/// Folds the stream using <paramref name="accumulator"/>.
/// <para>The result of <paramref name="initializer"/> applied to the first element of the stream is used
/// for the initial folding value.</para>
/// </summary>
/// <param name="accumulator">The function through which the stream is folded.</param>
/// <param name="initializer">The initializer function to apply to the first element in the stream.</param>
/// <returns>A terminal operation which folds the stream.</returns>
/// <exception cref="std::out_of_range">Thrown when the stream is empty.</exception>
template <typename Accumulator, typename UnaryFunction>
auto fold_id(Accumulator accumulator, UnaryFunction initializer) {
    return detail::make_terminal([accumulator, initializer](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::fold_id(Accumulator, UnaryFunction) expects a non-empty stream");
        }
        return stream | terminal::fold(accumulator, initializer(stream.next()));
    });
}

        namespace opt {

/// <summary>
/// Folds the stream using <paramref name="accumulator"/>, returning the result in an \ref optional object.
/// <para>The first element of the stream is used for the initial folding value.</para>
/// <para>This version does not throw an exception if the stream is empty, rather the returned optional
/// will not have a contained value. Otherwise, the optional contains the result of folding the stream.</para>
/// </summary>
/// <param name="accumulator">The function through which the stream is folded.</param>
/// <returns>A terminal operation which folds the stream.</returns>
/// <seealso cref="terminal::fold()"/>
/// <seealso cref="optional"/>
template <typename Accumulator>
auto fold(Accumulator accumulator) {
    return detail::make_terminal([accumulator](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        if (!stream.has_next()) {
            return optional<T>();
        }
        return stream | terminal::fold([accumulator](optional<T>& val, auto&& ele) { *val = accumulator(*val, ele); return val; }, optional<T>(stream.next()));
    });
}

/// <summary>
/// Folds the stream using <paramref name="accumulator"/>, returning the result in an \ref optional object.
/// <para>The result of <paramref name="initializer"/> applied to the first element of the stream is used
/// for the initial folding value.</para>
/// <para>This version does not throw an exception if the stream is empty, rather the returned optional
/// will not have a contained value. Otherwise, the optional contains the result of folding the stream.</para>
/// </summary>
/// <param name="accumulator">The function through which the stream is folded.</param>
/// <param name="initializer">The initializer function to apply to the first element in the stream.</param>
/// <returns>A terminal operation which folds the stream.</returns>
/// <seealso cref="terminal::fold_id()"/>
/// <seealso cref="optional"/>
template <typename Accumulator, typename UnaryFunction>
auto fold_id(Accumulator accumulator, UnaryFunction initializer) {
    return detail::make_terminal([accumulator, initializer](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        if (!stream.has_next()) {
            return optional<T>();
        }
        return stream | terminal::fold([accumulator](optional<T>& val, auto&& ele) { *val = accumulator(*val, ele); return val; }, optional<T>(initializer(stream.next())));
    });
}
        }
    }
}
#endif
