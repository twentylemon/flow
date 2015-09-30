
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
 
#ifndef FLOW_SOURCE_GENERATORSOURCE_H
#define FLOW_SOURCE_GENERATORSOURCE_H

#include <limits>
#include <vector>

namespace flow {
    namespace source {

/// <summary>
/// Base class for original stream sources; sources that initially create the stream.
/// Provides default implementations for infinite streams.
/// </summary>
template <typename T>
class GeneratorSourceBase
{
public:
    using value_type = T;
    using decay_type = std::decay_t<value_type>;

    /// <summary>
    /// Initializes a new instance of the <see cref="GeneratorSourceBase{T}"/> class.
    /// </summary>
    GeneratorSourceBase() : _current(nullptr) { }

    /// <summary>
    /// Returns true if this source has more elements.
    /// Default implementation returns <c>_source.has_next()</c>.
    /// </summary>
    /// <returns><c>true</c> if this source has more stream elements.</returns>
    constexpr bool has_next() const {
        return true;
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
    /// </summary>
    void lazy_next() {
    }

    /// <summary>
    /// Returns the max value of <c>std::size_t</c>. This is an infinite stream.
    /// Default implementation returns std::size_t max value.
    /// </summary>
    /// <returns>The estimated size of the remainder of the stream.</returns>
    constexpr std::size_t estimate_size() const {
        return std::numeric_limits<std::size_t>::max();
    }

protected:
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
        if (_temp.empty()) {
            _temp.push_back(std::forward<decay_type>(temp_current));
        }
        else {
            _temp[0] = std::forward<decay_type>(temp_current);
        }
        base::assign_current(_temp.data());
    }

    /// <summary>
    /// Returns the value inside the current stream value pointer. It is <em>not</em> moved.
    /// </summary>
    /// <returns>The stream value without moving it.</returns>
    value_type& raw_current() {
        return *_current;
    }

private:
    value_type* _current;           // the current value from the stream
    std::vector<decay_type> _temp;  // the temporary value from the stream, if any
};

/// <summary>
/// Base class for original stream sources without default constructible types.
/// </summary>
template <typename T>
class GeneratorSourceNoDefault : public GeneratorSourceBase<T>
{
public:
    using base = GeneratorSourceBase<T>;
    using value_type = typename base::value_type;
    using decay_type = typename base::decay_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="GeneratorSourceNoDefault{T}"/> class.
    /// </summary>
    GeneratorSourceNoDefault() : base(), _temp() { }

protected:
    /// <summary>
    /// Updates the current stream value pointer to a temporary value. The lifetime of the
    /// temporary is extended so the pointer is valid.
    /// </summary>
    /// <param name="temp_current">The temp_current.</param>
    void assign_temp_current(decay_type&& temp_current) {
        if (_temp.empty()) {
            _temp.push_back(std::forward<decay_type>(temp_current));
        }
        else {
            _temp[0] = std::forward<decay_type>(temp_current);
        }
        base::assign_current(_temp.data());
    }

private:
    std::vector<decay_type> _temp;  // the temporary value from the stream, if any
};

/// <summary>
/// Base class for original stream sources with default constructible types.
/// </summary>
template <typename T>
class GeneratorSourceDefault : public GeneratorSourceBase<T>
{
public:
    using base = GeneratorSourceBase<T>;
    using value_type = typename base::value_type;
    using decay_type = typename base::decay_type;

    /// <summary>
    /// Initializes a new instance of the <see cref="GeneratorSourceDefault{T}"/> class.
    /// </summary>
    GeneratorSourceDefault() : base(), _temp_current() { }

protected:
    /// <summary>
    /// Updates the current stream value pointer to a temporary value. The lifetime of the
    /// temporary is extended so the pointer is valid.
    /// </summary>
    /// <param name="temp_current">The temp_current.</param>
    void assign_temp_current(decay_type&& temp_current) {
        _temp_current = std::forward<decay_type>(temp_current);
        base::assign_current(&_temp_current);
    }

private:
    decay_type _temp_current;   // the temporary value from the stream, if any
};

template <typename T>
using GeneratorSource = std::conditional_t<
    std::is_default_constructible<T>::value,
    GeneratorSourceDefault<T>,
    GeneratorSourceNoDefault<T>
>;
    }
}

#endif
