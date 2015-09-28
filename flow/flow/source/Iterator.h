
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
 
#ifndef FLOW_SOURCE_ITERATOR_H
#define FLOW_SOURCE_ITERATOR_H

#include <iterator>

#include "GeneratorSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source for a pair of iterators.
/// </summary>
template <typename Itr>
class Iterator : public GeneratorSource<std::remove_reference_t<typename std::iterator_traits<Itr>::reference>>
{
public:
    using base = GeneratorSource<std::remove_reference_t<typename std::iterator_traits<Itr>::reference>>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Iterator{Itr}"/> class.
    /// </summary>
    /// <param name="begin">The begin iterator.</param>
    /// <param name="end">The end iterator.</param>
    Iterator(Itr begin, Itr end) : base(), _current(begin), _end(end) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() const {
        return _current != _end;
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        return *_current++;
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        ++_current;
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is an exact value.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return std::distance(_current, _end);
    }

protected:
    /// <summary>
    /// Initializes an empty instance of the <see cref="Iterator{Itr}"/> class.
    /// </summary>
    Iterator() { }

    /// <summary>
    /// The current iterator.
    /// </summary>
    Itr _current;

    /// <summary>
    /// The off end iterator.
    /// </summary>
    Itr _end;
};
    }
}
#endif
