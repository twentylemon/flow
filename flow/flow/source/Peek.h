
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
 
#ifndef FLOW_SOURCE_PEEK_H
#define FLOW_SOURCE_PEEK_H

namespace flow {
    namespace source {

/// <summary>
/// Stream source that applies an action to each stream element. The elements are left unaltered.
/// </summary>
template <typename Source, typename Action>
class Peek
{
public:
    using value_type = typename Source::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Peek{Source, Action}" /> class.
    /// </summary>
    /// <param name="source">The source to peek at the elements of.</param>
    /// <param name="predicate">The action to apply to each stream element.</param>
    Peek(Source&& source, Action action) : _source(std::forward<Source>(source)), _action(action) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        return _source.has_next();
    }

    /// <summary>
    /// Returns the next item from the stream. Also applies the peek action to the element.
    /// </summary>
    /// <returns>The next item in the stream.</returns>
    value_type next() {
        value_type current = std::move(_source.next());
        _action(current);
        return std::move(current);
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        //_source.lazy_next();
        _action(std::move(_source.next()));
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is likely an overestimate.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() {
        return _source.estimate_size();
    }

protected:
    Source _source; // the source to read from
    Action _action; // the action to apply to the stream elements
};
    }
}
#endif
