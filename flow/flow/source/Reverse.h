
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
 
#ifndef FLOW_SOURCE_REVERSE_H
#define FLOW_SOURCE_REVERSE_H

#include <vector>

#include "Iterator.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source to reverse the stream. Reversing is an eager operation, the entire stream up to this point
/// is evaluated and stored.
/// </summary>
/// \todo make reversing a lazy operation instead; wait until the first has_next() or next() call
template <typename Source>
class Reverse : public Iterator<typename std::vector<typename Source::value_type>::reverse_iterator>
{
public:
    using parent_type = Iterator<typename std::vector<typename Source::value_type>::reverse_iterator>;
    using value_type = typename parent_type::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Reverse{Source}" /> class.
    /// </summary>
    /// <param name="source">The source stream to reverse.</param>
    Reverse(Source&& source) : _source(std::move(source)), _stream()
    {
        reverse();
    }

    /// <summary>
    /// Pulls all the elements from the source stream and reverses
    /// </summary>
    void reverse() {
        _stream.reserve(_source.estimate_size());
        while (_source.has_next()) {
            _stream.emplace_back(std::move(_source.next()));
        }
        parent_type::_current = _stream.rbegin();
        parent_type::_end = _stream.rend();
    }

private:
    Source _source;                     // the source to read from
    std::vector<value_type> _stream;    // the full stream
};
    }
}
#endif
