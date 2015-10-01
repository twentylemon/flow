
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
 
#ifndef FLOW_SOURCE_FLATMAP_H
#define FLOW_SOURCE_FLATMAP_H

#include <memory>

#include "IntermediateSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that maps elements into new streams. The resultant stream is the concatenation
/// of all the created streams.
/// </summary>
template <typename Source, typename UnaryOperation>
class FlatMap : public IntermediateSource<Source, std::remove_reference_t<decltype(std::declval<std::result_of_t<UnaryOperation(typename Source::value_type)>>().next())>>
{
public:
    using base = IntermediateSource<Source, std::remove_reference_t<decltype(std::declval<std::result_of_t<UnaryOperation(typename Source::value_type)>>().next())>>;
    using stream_type = std::result_of_t<UnaryOperation(typename Source::value_type)>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="FlatMap{Source, UnaryOperation}"/> class.
    /// </summary>
    /// <param name="source">The source to map from.</param>
    /// <param name="operation">The mapping operation.</param>
    FlatMap(Source&& source, UnaryOperation operation) : base(std::forward<Source>(source)), _operation(operation), _stream(nullptr) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        if (_stream != nullptr && _stream->has_next()) {
            base::assign_current(&_stream->next());
            return true;
        }
        else if (base::has_next()) {
            _stream = std::make_unique<stream_type>(_operation(base::raw_next()));
            return has_next();  // step the stream or step the original source again
        }
        return false;
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// This value cannot be accurately estimated. We assume that each stream created
    /// is the same size as the number of remaining elements in this stream,
    /// making the estimate <c>_source.estimate_size() * _current_stream.estimate_size()</c>.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        if (_stream == nullptr) {
            return 128; // to_vector can crash; just return something
        }
        return base::estimate_size() * _stream->estimate_size();
    }

private:
    UnaryOperation _operation;              // the mapping operation to apply to each element from the source
    std::unique_ptr<stream_type> _stream;   // the current stream we are reading values from
};
    }
}
#endif
