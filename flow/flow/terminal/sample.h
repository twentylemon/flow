
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
 
#ifndef FLOW_TERMINAL_SAMPLE_H
#define FLOW_TERMINAL_SAMPLE_H

#include "Terminal.h"
#include "to.h"

namespace flow {
    namespace terminal {

inline auto sample(std::size_t n) {
    return detail::make_terminal([n](auto&& stream) {
        auto results = stream | limit(n) | to_vector();
        stream | copy(std::back_inserter(results));
        return results;
        /*
        using T = std::decay_t<decltype(stream.next())>;
        std::size_t size = 0;
        std::vector<T> results;
        results.reserve(n);
        while (size < n && stream.has_next()) {
            results.push_back(std::move(stream.next()));
        }
        */
    });
}
    }
}
#endif
