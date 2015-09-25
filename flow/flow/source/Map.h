
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
 
#ifndef FLOW_SOURCE_MAP_H
#define FLOW_SOURCE_MAP_H

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that maps elements into new values.
/// </summary>
template <typename Source, typename UnaryOperation>
class Map : public IntermediateSource<Source, std::result_of_t<UnaryOperation(typename Source::value_type)>>
{
public:
    using base = IntermediateSource<Source, std::result_of_t<UnaryOperation(typename Source::value_type)>>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="Map{Source, UnaryOperation}"/> class.
    /// </summary>
    /// <param name="source">The source to map from.</param>
    /// <param name="operation">The mapping operation.</param>
    Map(Source&& source, UnaryOperation operation) : base(std::forward<Source>(source)), _operation(operation) { }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    const value_type& next() {
        base::assign_temp_current(_operation(base::raw_next()));
        return base::next();
    }

private:
    UnaryOperation _operation;  // the mapping operation to apply to each element from the source
};
    }
}
#endif
