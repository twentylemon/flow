
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
 
#ifndef FLOW_SOURCE_INTERMEDIATESOURCE_H
#define FLOW_SOURCE_INTERMEDIATESOURCE_H

namespace flow {
    namespace source {

/// <summary>
/// Base class for intermediate operation sources. Provides default implementations
/// for basic methods, type aliases and common member variable definitions.
/// </summary>
template <typename Source, typename T = typename Source::value_type>
class IntermediateSource
{
public:
    using source_type = Source;
    using value_type = T;
    using decay_type = std::decay_t<value_type>;

    /// <summary>
    /// Initializes a new instance of the <see cref="IntermediateSource{Source, T}"/> class.
    /// </summary>
    /// <param name="source">The stream source to read elements from.</param>
    IntermediateSource(Source&& source) : _source(std::move(source)), _current(nullptr) { }

    /// <summary>
    /// Returns true if the source has more elements. Default implementation returns <c>_source.has_next()</c>.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    bool has_next() {
        return _source.has_next();
    }

    /// <summary>
    /// Returns the next element from the stream. The value is <em>moved</em>. Successive calls to next() will fail.
    /// Default implementation returns <c>std::move(*_current);</c>.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        return *_current;
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// Default implementation executes <c>_source.lazy_next()</c>.
    /// </summary>
    void lazy_next() {
        _source.lazy_next();
    }

    /// <summary>
    /// Returns the estimated size of the remainder of the stream.
    /// Default implementation returns <c>_source.estimate_size()</c>.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    std::size_t estimate_size() const {
        return _source.estimate_size();
    }

protected:
    /// <summary>
    /// Updates the current stream value pointer to be the next element from the source stream.
    /// </summary>
    void assign_current() {
        _current = &_source.next();
    }

    /// <summary>
    /// Updates the current stream value pointer to be the given element.
    /// </summary>
    /// <param name="current">The value to give to the current element.</param>
    void assign_current(value_type* current) {
        _current = current;
    }

    /// <summary>
    /// Updates the current stream value pointer to a temporary value. The lifetime of the
    /// temporary is extended so the pointer is valid.
    /// </summary>
    /// <param name="temp_current">The temp_current.</param>
    void assign_temp_current(decay_type&& temp_current) {
        _temp_current = std::forward<decay_type>(temp_current);
        _current = &_temp_current;
    }

    /// <summary>
    /// Returns the value inside the current stream value pointer. It is <em>not</em> moved.
    /// </summary>
    /// <returns>The stream value without moving it.</returns>
    value_type& raw_current() {
        return *_current;
    }

    /// <summary>
    /// Returns <c>_source.next()</c>.
    /// </summary>
    /// <returns><c>_source.next()</c></returns>
    typename Source::value_type& raw_next() {
        return _source.next();
    }

private:
    Source _source;             // the source of the stream
    value_type* _current;       // the current value from the stream
    decay_type _temp_current;   // the temporary value from the stream, if any
};
    }
}
#endif
