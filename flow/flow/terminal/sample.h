
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
 
#ifndef FLOW_TERMINAL_SAMPLE_H
#define FLOW_TERMINAL_SAMPLE_H

#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#include "Terminal.h"
#include "../generator/from.h"
#include "../intermediate/map.h"
#include "to.h"

namespace flow {
    namespace terminal {

/// <summary>
/// Returns a random sample from the finite stream in a <c>std::vector</c>. This implementation uses a heap-sample method.
/// <para>The heap-sample method takes <c>O(N log n)</c> time where <c>N</c> is the number of elements in the stream and
/// <c>n</c> is the sample size parameter, <paramref name="n"/>. This method generates a random number <c>r</c> for each
/// stream element <c>e</c> and places the pair <c>(r, e)</c> into a heap ordered by <c>r</c>. If the heap has more
/// than <paramref name="n"/> elements, a remove operation is performed on the heap. Finally, the actual elements
/// from the heap are moved into a <c>std::vector</c>.</para>
/// <para>This method essentially assigns a random number to each element, and keeps the <paramref name="n"/>
/// elements with the smallest number. It should be used when the sample size you want to obtain is small
/// compared to the size of the container.</para>
/// </summary>
/// <param name="n">The number of elements to obtain from the stream. If the stream is smaller, all elements are returned.</param>
/// <returns>A detail::Terminal operation that returns a <c>std::vector</c> of <paramref name="n"/> random stream elements.</returns>
/// <seealso cref="sample()"/>
/// <seealso cref="reservoir()"/>
inline auto sample_heap(std::size_t n) {
    return detail::make_terminal([n](auto&& stream) {
        using flow::generator::operator|;
        using T = std::decay_t<decltype(stream.next())>;
        using U = typename std::default_random_engine::result_type;
        std::default_random_engine gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        auto comp = [](const std::pair<U, T>& lhs, const std::pair<U, T>& rhs) { return lhs.first < rhs.first; };
        std::vector<std::pair<U, T>> heap;
        heap.reserve(n + 1);
        while (stream.has_next()) {
            heap.push_back(std::make_pair(gen(), std::move(stream.next())));
            std::push_heap(heap.begin(), heap.end(), comp);
            if (heap.size() > n) {
                std::pop_heap(heap.begin(), heap.end(), comp);
                heap.pop_back();
            }
        }
        return heap | intermediate::map([](std::pair<U, T>& p) { return std::move(p.second); }) | to_vector();
    });
}

/// <summary>
/// Returns a random sample from the finite stream in a <c>std::vector</c>. This implementation uses a shuffle-sample method.
/// <para>The shuffle-sample method takes <c>O(N + n)</c> time where <c>N</c> is the number of elements in the stream and
/// <c>n</c> is the sample size parameter, <paramref name="n"/>. This method copies the entire stream into a vector,
/// shuffles it, then erases elements so that there are only <paramref name="n"/> elements. This method should be
/// used when the sample size is relatively large.</para>
/// </summary>
/// <param name="n">The number of elements to obtain from the stream. If the stream is smaller, all elements are returned.</param>
/// <returns>A detail::Terminal operation that returns a <c>std::vector</c> of <paramref name="n"/> random stream elements.</returns>
/// <seealso cref="sample()"/>
/// <seealso cref="reservoir()"/>
inline auto sample_shuffle(std::size_t n) {
    return detail::make_terminal([n](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::default_random_engine gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        auto results = stream | to_vector();
        if (results.size() > n) {
            std::shuffle(results.begin(), results.end(), gen);
            results.erase(results.begin() + n, results.end());
        }
        return results;
    });
}

/// <summary>
/// Returns a random sample from the finite stream in a <c>std::vector</c>. This method tries to pick the better
/// of sample_heap() and sample_shuffle() using the estimated size of the stream.
/// </summary>
/// <param name="n">The number of elements to obtain from the stream. If the stream is smaller, all elements are returned.</param>
/// <returns>A detail::Terminal operation that returns a <c>std::vector</c> of <paramref name="n"/> random stream elements.</returns>
/// <seealso cref="sample_heap()"/>
/// <seealso cref="sample_shuffle()"/>
/// <seealso cref="reservoir()"/>
inline auto sample(std::size_t n) {
    return detail::make_terminal([n](auto&& stream) {
        double N = static_cast<double>(stream.estimate_size());
        double s = static_cast<double>(n);
        if (2 * (N - s) * std::log2(s) + s < 3 * N - s) {
            return stream | sample_heap(n);
        }
        return stream | sample_shuffle(n);
    });
}
    }
}
#endif
