
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
 
#ifndef FLOW_STREAM_H
#define FLOW_STREAM_H

#include "terminal/Terminal.h"
#include "intermediate/Intermediate.h"

namespace flow {

/// <summary>
/// <para>The stream class. Provides lazy evaluation and functional style transformations on data.
/// Streams support pipelining of multiple operations. Streams can be transformed using <c>operator|</c>
/// to create a new stream given a detail::Intermediate operation (anything from the flow::intermediate namespace)
/// or can return a value given a detail::Terminal operation (anything from the flow::terminal namespace).</para>
/// <para>While streams can be constructed, it is recommended that any stream created is done through the functions
/// in the flow::generator namespace, as all the stream operations are embedded in the potentially long template type.
/// This means you can't do operations like:</para>
/// <code>auto stream = Stream(...);<br/>
/// stream = stream | filter(); // not possible; types are not compatible</code>
/// <para>Instead, if you want a Stream object, write out the entire stream right away.</para>
/// <code>auto stream = Stream(...) | filter();<br/>
/// auto min = stream | min();</code>
/// </summary>
/// \todo flow::terminal::sample - take a random sample of n elements from a finite stream
/// \todo flow::terminal::reservoir - take a random sample of n elements from an infinite stream
/// \todo flow::intermediate::merge - combine two sorted streams while maintaining sorted order
/// \todo flow::intermediate::union - union two sorted/unique streams
/// \todo flow::intermediate::intersect - intersect two sorted/unique streams
/// \todo flow::intermediate::difference - compute the difference of two sorted/unique streams
/// \todo flow::intermediate::symmetric_difference - compute the symmetric difference of two sorted/unique streams
/// \todo flow::generator::random - generate stream values from a random number generator
/// \todo flow::generator::parallel_* - create a parallel version of other generators
/// \todo parallel pipelining of stream operations?
/// \todo allow iterator access via begin() and end()
template <typename Source>
class Stream
{
public:
    using source_type = Source;
    using value_type = typename Source::value_type;

    /// <summary>
    /// Initializes a new instance of the Stream class.
    /// </summary>
    /// <param name="...args">Arguments to forward to the Source constructor.</param>
    template <typename... Args>
    Stream(Args&&... args) : _source(std::forward<Args>(args)...) { }

    /// <summary>
    /// Returns the source of this stream.
    /// </summary>
    /// <returns>The source of this stream.</returns>
    Source& source() {
        return _source;
    }

    /// <summary>
    /// Returns true if this stream has more elements.
    /// </summary>
    /// <returns><c>true</c> if this stream has more elements.</returns>
    bool has_next() {
        return _source.has_next();
    }

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type next() {
        return _source.next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        _source.lazy_next();
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() {
        return _source.estimate_size();
    }

    /// <summary>
    /// Adds an additional operation to the stream pipeline, returning the new stream.
    /// </summary>
    /// <param name="op">The operation to add to the pipeline.</param>
    /// <returns>A new stream that is the composition of this stream and the operation given.</returns>
    template <typename F>
    std::result_of_t<intermediate::detail::Intermediate<F>(Stream<Source>&&)> operator|(intermediate::detail::Intermediate<F>&& op) {
        return op(std::move(*this));
    }

    /// <summary>
    /// Adds an additional operation to the stream pipeline, returning the new stream.
    /// </summary>
    /// <param name="op">The operation to add to the pipeline.</param>
    /// <returns>A new stream that is the composition of this stream and the operation given.</returns>
    template <typename F>
    std::result_of_t<terminal::detail::Terminal<F>(Stream<Source>&&)> operator|(terminal::detail::Terminal<F>&& op) {
        return op(std::move(*this));
    }

protected:
    /// <summary>
    /// The source of this stream, where values are pulled from, be it a container, an infinite generator
    /// or some other source.
    /// </summary>
    Source _source;
};
}
#endif
