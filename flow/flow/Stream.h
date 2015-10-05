
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
 
#ifndef FLOW_STREAM_H
#define FLOW_STREAM_H

#include <iterator>

#include "terminal/Terminal.h"
#include "intermediate/Intermediate.h"

namespace flow {

/// <summary>
/// The stream class provides lazy evaluation and functional style transformations on ordered data.
///  <para>Streams support pipelining of multiple operations. Streams can be transformed using <c>operator|</c>
/// to create a new stream given a detail::Intermediate operation (anything from the flow::intermediate namespace)
/// or can return a value given a detail::Terminal operation (anything from the flow::terminal namespace).</para>
/// <para>Streams can be constructed using the functions in the flow::generator namespace.</para>
/// </summary>
/// \todo flow::intermediate::merge - combine two sorted streams while maintaining sorted order
/// \todo flow::intermediate::union - union two sorted/unique streams
/// \todo flow::intermediate::intersect - intersect two sorted/unique streams
/// \todo flow::intermediate::difference - compute the difference of two sorted/unique streams
/// \todo flow::intermediate::symmetric_difference - compute the symmetric difference of two sorted/unique streams
/// \todo flow::generator::random - generate stream values from a random number generator
/// \todo flow::generator::parallel_* - create a parallel version of other generators?
/// \todo flow::terminal::parallel_* - chunking parallelization of terminal operations
/// \todo parallel pipelining of stream operations?
template <typename Source>
class Stream
{
public:
    /// <summary>
    /// Initializes a new instance of the Stream class.
    /// </summary>
    /// <param name="...args">Arguments to forward to the Source constructor.</param>
    template <typename... Args>
    Stream(Args&&... args) : _source(std::forward<Args>(args)...) { }

    Stream(const Stream<Source>&) = delete;
    Stream(Stream<Source>&&) = default;

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
    auto& next() {
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
    std::size_t estimate_size() const {
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

    /// <summary>
    /// Allows STL-like iterator access to the stream. Stream iterators are forward and single-pass,
    /// once a stream has been iterated in any way (including terminal operations), the
    /// iterators are invalidated.
    /// <para>Additionally, only the first iterator ever used is valid. To extend the lifetime
    /// of a stream, use one of the to_container terminal operations.</para>
    /// </summary>
    class iterator : public std::iterator<std::forward_iterator_tag, typename Source::value_type>
    {
    public:
        using base = std::iterator<std::forward_iterator_tag, typename Source::value_type>;
        using value_type = typename base::value_type;
        using reference = typename base::reference;
        using pointer = typename base::pointer;
        using difference_type = typename base::difference_type;
        using iterator_category = typename base::iterator_category;

        iterator() : _current(nullptr), _stream(nullptr) { }
        iterator(Stream<Source>* stream) : _current(nullptr), _stream(stream) { operator++(); }
        bool operator==(const iterator& rhs) const { return _current == rhs._current; }
        bool operator!=(const iterator& rhs) const { return _current != rhs._current; }
        reference operator*() { return *_current; }
        pointer operator->() { return _current; }
        iterator& operator++() {
            if (_stream->has_next()) {
                _current = &_stream->next();
            }
            else {
                _current = nullptr;
            }
            return *this;
        }
        iterator operator++(int){
            iterator ret = *this;
            return ++ret;
        }
    private:
        pointer _current;           // the current stream element, null once off end
        Stream<Source>* _stream;    // the stream this iterator belongs to
    };

    /// <summary>
    /// Returns an iterator to the first element in the stream.
    /// </summary>
    /// <returns>An iterator to the first element in the stream.</returns>
    iterator begin() {
        return iterator(this);
    }

    /// <summary>
    /// Returns an iterator to the first off-end element of the stream.
    /// </summary>
    /// <returns>An iterator to the first off-end element of the stream.</returns>
    iterator end() {
        return iterator();
    }

private:
    Source _source; // the source of stream elements
};
}
#endif
