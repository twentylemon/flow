
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

namespace flow {
    namespace source {

/// <summary>
/// Stream source that maps elements into new values.
/// </summary>
template <typename Source, typename UnaryOperation>
class Map
{
public:
    using value_type = typename std::result_of_t<UnaryOperation(typename Source::value_type)>;

    /// <summary>
    /// Initializes a new instance of the <see cref="Map{Source, UnaryOperation}"/> class.
    /// </summary>
    /// <param name="source">The source to map from.</param>
    /// <param name="operation">The mapping operation.</param>
    Map(Source&& source, UnaryOperation operation) : _source(std::forward<Source>(source)), _operation(operation) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        return _source.has_next();
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type next() {
        return std::move(_operation(std::move(_source.next())));
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        _source.lazy_next();
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This is an exact value.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() {
        return _source.estimate_size();
    }

private:
    Source _source;             // the source to read from
    UnaryOperation _operation;  // the mapping operation to apply to each element from the source
};
    }
}
#endif
