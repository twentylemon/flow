
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
#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source to reverse the stream. Reversing is an eager operation, the entire stream up to this point
/// is evaluated and stored.
/// </summary>
/// \todo make reversing a lazy operation instead; wait until the first has_next() or next() call
template <typename Source>
class Reverse : public IntermediateSource<Source>, public Iterator<typename std::vector<typename Source::value_type*>::reverse_iterator>
{
public:
    using base = IntermediateSource<Source>;
    using parent_type = Iterator<typename std::vector<typename Source::value_type*>::reverse_iterator>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Reverse{Source}" /> class.
    /// </summary>
    /// <param name="source">The source stream to reverse.</param>
    Reverse(Source&& source) : base(std::forward<Source>(source)), _stream()
    {
        reverse();
    }

    /// <summary>
    /// Returns true if the source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        return parent_type::has_next();
    }

    /// <summary>
    /// Returns the next element from the stream. The value is <em>moved</em>. Successive calls to next() will fail.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        return *parent_type::next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        parent_type::lazy_next();
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return parent_type::estimate_size();
    }

    /// <summary>
    /// Pulls all the elements from the source stream and reverses
    /// </summary>
    void reverse() {
        _stream.reserve(base::estimate_size());
        while (base::has_next()) {
            _stream.push_back(&base::raw_next());
        }
        parent_type::_current = _stream.rbegin();
        parent_type::_end = _stream.rend();
    }

private:
    std::vector<value_type*> _stream;   // the full stream
};
    }
}
#endif
