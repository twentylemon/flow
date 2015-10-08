
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
 
#ifndef FLOW_SOURCE_PEEK_H
#define FLOW_SOURCE_PEEK_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that applies an action to each stream element. The elements are left unaltered.
/// </summary>
template <typename Source, typename Action>
class Peek : public IntermediateSource<Source>
{
public:
    using base = IntermediateSource<Source>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Peek{Source, Action}" /> class.
    /// </summary>
    /// <param name="source">The source to peek at the elements of.</param>
    /// <param name="action">The action to apply to each stream element.</param>
    Peek(Source&& source, Action action) : base(std::move(source)), _action(action) { }

    Peek(const Peek<Source, Action>&) = delete;
    Peek(Peek<Source, Action>&&) = default;

    /// <summary>
    /// Returns the next element from the stream. Also applies the peek action to the element.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        base::assign_current();
        _action(base::raw_current());
        return base::next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        next();
    }

private:
    Action _action; // the action to apply to the stream elements
};
    }
}
#endif
