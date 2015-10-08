
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
 
#ifndef FLOW_SOURCE_DROPWHILE_H
#define FLOW_SOURCE_DROPWHILE_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that drops elements from the stream until a predicate returns <c>false</c>. All elements
/// before the first <c>true</c> are discarded, the rest are kept.
/// </summary>
template <typename Source, typename UnaryPredicate>
class DropWhile : public IntermediateSource<Source>
{
public:
    using base = IntermediateSource<Source>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="DropWhile{Source, UnaryPredicate}" /> class.
    /// </summary>
    /// <param name="source">The source to drop elements from.</param>
    /// <param name="predicate">The predicate, drop stream elements until this returns <c>false</c>.</param>
    DropWhile(Source&& source, UnaryPredicate predicate) : base(std::move(source)), _predicate(predicate), _initial(true) { }

    DropWhile(const DropWhile<Source, UnaryPredicate>&) = delete;
    DropWhile(DropWhile<Source, UnaryPredicate>&&) = default;

    /// <summary>
    /// Returns <c>true</c> if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        if (_initial) {
            _initial = false;
            while (base::has_next()) {
                base::assign_current();
                if (!_predicate(base::raw_current())) {
                    return true;
                }
            }
            return false;
        }
        else {
            if (base::has_next()) {
                base::assign_current();
                return true;
            }
            return false;
        }
    }

private:
    UnaryPredicate _predicate;  // the mapping operation to apply to each element from the source
    bool _initial;              // true if we have not dropped stream values yet
};
    }
}
#endif
