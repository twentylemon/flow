
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
 
#ifndef FLOW_TERMINAL_RESERVOIR_H
#define FLOW_TERMINAL_RESERVOIR_H

#include "Terminal.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns a random sample from the potentially infinite stream in a <c>std::vector</c>.
/// <para>For infinite streams, execution stops once <paramref name="execution_limit"/> stream elements have
/// been seen. For finite streams, execution stops once <paramref name="execution_limit"/> stream elements have
/// been seen or once the stream has ended, whichever comes first.</para>
/// <para>Each element in the stream has a <c>1 / min(stream_size, execution_limit)</c> chance to appear
/// in the returned sample.</para>
/// </summary>
/// <param name="n">The number of elements to obtain from the stream. If the stream is smaller, all elements are returned.</param>
/// <param name="execution_limit">Once this many stream elements have been seen, a sample is returned.</param>
/// <returns>A detail::Terminal operation that returns a <c>std::vector</c> of <paramref name="n"/> random stream elements.</returns>
/// <seealso cref="sample()"/>
inline auto reservoir(std::size_t n, std::size_t execution_limit) {
    return detail::make_terminal([n, execution_limit](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::default_random_engine gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        std::vector<T> results;
        results.reserve(n);
        std::size_t size = 0;
        while (size < n && stream.has_next()) {
            results.push_back(std::move(stream.next()));
            ++size;
        }
        while (stream.has_next() && size != execution_limit) {
            ++size;
            if (gen() % size < n) {
                results[gen() % n] = std::move(stream.next());
            }
            else {
                stream.lazy_next();
            }
        }
        return results;
    });
}

/// <summary>
/// Returns a random sample from the potentially infinite stream in a <c>std::vector</c>.
/// <para>For infinite streams, execution stops once 16,777,216 stream elements have
/// been seen. For finite streams, execution stops once the estimated number of stream elements have
/// been seen or once the stream has ended, whichever comes first. The estimated size can potentially
/// be an over- or underestimate. For known finite streams, sample() is a better option.</para>
/// <para>Each element in the stream has a <c>1 / min(stream_size, 16,777,216)</c> chance to appear
/// in the returned sample.</para>
/// </summary>
/// <param name="n">The number of elements to obtain from the stream. If the stream is smaller, all elements are returned.</param>
/// <returns>A detail::Terminal operation that returns a <c>std::vector</c> of <paramref name="n"/> random stream elements.</returns>
/// <seealso cref="sample()"/>
inline auto reservoir(std::size_t n) {
    return detail::make_terminal([n](auto&& stream) {
        return stream | reservoir(n, stream.estimate_size());
    });
}
    }
}
#endif
