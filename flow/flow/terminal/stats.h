
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
 
#ifndef FLOW_TERMINAL_STATS_H
#define FLOW_TERMINAL_STATS_H

#include <iostream>

#include "Terminal.h"

namespace flow {

/// <summary>
/// Class to wrap all the statistics returned by stats().
/// <para>The count, mean, standard deviation, variance, sum and sum of squares of the stream
/// elements are always calculated. Conditionally calculates additional statistics like
/// median and mode, etc. If those values are not calculated, using the <c>getter</c> methods
/// will result in a compiler error.</para>
/// </summary>
/// <seealso cref="stats()"/>
/// \todo implement median, mode
template <typename T, typename ResultType, bool MinMax, bool Median, bool Mode>
class Stats
{
public:
    /// <summary>
    /// Initializes a new instance of the <see cref="Stats"/> class.
    /// </summary>
    /// <param name="ele"/>The first element from the stream.</param>
    Stats(T& ele) : _min(ele), _max(ele), _mean(0), _median(0), _mode(0), _stddev(0), _variance(0), _sum(ele), _sum_squares(ele * ele), _n(1) { }
        
    Stats(const Stats<T, ResultType, MinMax, Median, Mode>&) = default;
    Stats(Stats<T, ResultType, MinMax, Median, Mode>&&) = default;
    
    /// <summary>
    /// Returns the minimum value calculated [conditionally compiled].
    /// </summary>
    /// <returns>The minimum value of the stream.</returns>
    template <bool B = MinMax, typename = std::enable_if_t<B>>
    T min() const {
        return _min;
    }
    
    /// <summary>
    /// Returns the maximum value calculated [conditionally compiled].
    /// </summary>
    /// <returns>The maximum value of the stream.</returns>
    template <bool B = MinMax, typename = std::enable_if_t<B>>
    T max() const {
        return _max;
    }
    
    /// <summary>
    /// Returns the median value calculated [conditionally compiled].
    /// </summary>
    /// <returns>The median value of the stream.</returns>
    template <bool B = Median, typename = std::enable_if_t<B>>
    ResultType median() const {
        return _median;
    }
    
    /// <summary>
    /// Returns the mode value calculated [conditionally compiled].
    /// </summary>
    /// <returns>The mode value of the stream.</returns>
    template <bool B = Median, typename = std::enable_if_t<B>>
    T mode() const {
        return _mode;
    }
    
    /// <summary>
    /// Returns the mean value of the stream.
    /// </summary>
    /// <returns>The mean value of the stream.</returns>
    ResultType mean() const {
        return _mean;
    }
    
    /// <summary>
    /// Returns the standard deviation of the stream.
    /// </summary>
    /// <returns>The standard deviation of the stream.</returns>
    ResultType stddev() const {
        return _stddev;
    }
    
    /// <summary>
    /// Returns the variance of the stream.
    /// </summary>
    /// <returns>The variance of the stream.</returns>
    ResultType variance() const {
        return _variance;
    }
    
    /// <summary>
    /// Returns the sum of the values in the stream.
    /// </summary>
    /// <returns>The sum of the values in the stream.</returns>
    ResultType sum() const {
        return _sum;
    }
    
    /// <summary>
    /// Returns the sum of the squares of the values in the stream.
    /// </summary>
    /// <returns>The sum of the squares of the values in the stream.</returns>
    ResultType sum_squares() const {
        return _sum_squares;
    }
    
    /// <summary>
    /// Returns the number of elements in the stream.
    /// </summary>
    /// <returns>The number of elements in the stream.</returns>
    std::size_t n() const {
        return _n;
    }
    
    /// <summary>
    /// Updates the statistics values to account for the next <paramref name="value"/> seen.
    /// <para>This method is internal to the flow library; it <em>should</em> be private,
    /// but g++ cannot friend an auto return type.</para>
    /// </summary>
    /// <param name="value"/>The next value in the stream.</param>
    void next(T&& value) {
        ++_n;
        _sum = _sum + value;
        _sum_squares = _sum_squares + value * value;
        if (MinMax) {   // slow minmax
            if (value < _min) {
                _min = std::move(value);
            }
            else if (_max < value) {
                _max = std::move(value);
            }
        }
    }
    
    /// <summary>
    /// Called once the stream is ended; finishes calculating statistics values.
    /// <para>This method is internal to the flow library; it <em>should</em> be private,
    /// but g++ cannot friend an auto return type.</para>
    /// </summary>
    void end() {
        _mean = _sum / _n;
        _variance = (_sum_squares * _n - _sum * _sum) / (_n * _n);
        _stddev = std::sqrt(_variance);
    }

private:
    T _min;                     // conditionally include min value of the stream
    T _max;                     // conditionally included max value of the stream
    ResultType _mean;           // mean of the stream; to be updated at stream end
    ResultType _median;         // conditionally include the median of the stream
    T _mode;                    // conditionally include the mode of the stream
    ResultType _stddev;         // stddev of the stream; to be updated at stream end
    ResultType _variance;       // variance of the stream; to be updated at stream end
    ResultType _sum;            // sum of the values
    ResultType _sum_squares;    // sum of squares of values
    std::size_t _n;             // the number of elements in the stream
};
    
    namespace detail {

/// <summary>
/// Wrapper to avoid the display of the min/max of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool A, bool B>
void display_minmax(std::ostream& out, const Stats<T, R, false, A, B>& stats) { }

/// <summary>
/// Wrapper to display of the min/max of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool A, bool B>
void display_minmax(std::ostream& out, const Stats<T, R, true, A, B>& stats) {
    out << ", min = " << stats.min() << ", max = " << stats.max();
}

/// <summary>
/// Wrapper to avoid the display of the median of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool A, bool B>
void display_median(std::ostream& out, const Stats<T, R, A, false, B>& stats) { }

/// <summary>
/// Wrapper to display of the median of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool A, bool B>
void display_median(std::ostream& out, const Stats<T, R, A, true, B>& stats) {
    out << ", median = " << stats.median();
}

/// <summary>
/// Wrapper to avoid the display of the mode of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool A, bool B>
void display_mode(std::ostream& out, const Stats<T, R, A, B, false>& stats) { }

/// <summary>
/// Wrapper to display of the mode of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool A, bool B>
void display_mode(std::ostream& out, const Stats<T, R, A, B, true>& stats) {
    out << ", mode = " << stats.mode();
}
    }

/// <summary>
/// Overload <c>operator&lt;&lt;</c> to display Stats objects.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
/// <returns><paramref name="out"/></returns>
template <typename T, typename R, bool MinMax, bool Median, bool Mode>
std::ostream& operator<<(std::ostream& out, const Stats<T, R, MinMax, Median, Mode>& stats) {
    out << "n = " << stats.n() << ", mu = " << stats.mean() << ", stddev = " << stats.stddev();
    detail::display_median(out, stats);
    detail::display_mode(out, stats);
    detail::display_minmax(out, stats);
    return out;
}

    namespace terminal {

/// <summary>
/// Returns a Stats object which contains several statistics of the stream values.
/// <para>The number of elements, mean, standard deviation, variance, sum and sum of squares are always calculated.</para>
/// <para>Some statistical values are calculated as <c>ResultType</c>, <c>double</c> by default, others
/// are calculated as <c>T</c>, the type of elements in the stream. Calculating statistics requires that
/// both <c>T</c> and <c>ResultType</c> behave as arithmetic types.</para>
/// <para>The other template parameters indicate whether or not to calculate additional statistics.
/// The behavior of of each of them is as follows (<c>n</c> is the size of the stream):</para>
/// <ul>
///     <li><c>MinMax</c> - calculate the minimum and maximum value of the stream. Requires that
///         <c>T</c> has <c>operator&lt;</c> implemented. The min and max are calculated as <c>T</c>.
///         This operation uses an addition <c>2n</c> time.</li>
///     <li><c>Median</c> - calculate the median value of the stream. Requires that <c>T</c> has both
///         <c>operator&lt;</c> and <c>operator&gt;</c> implemented. The median is calculated as <c>ResultType</c>.
///         This operation uses an additional <c>O(n logn)</c> time and <c>O(n)</c> space.</li>
///     <li><c>Mode</c> - calculate the mode value of the stream. Requires that <c>T</c> has both
///         <c>std::hash</c> and <c>operator==</c> implemented. The mode is calculated as <c>T</c>.
///         This operation uses an addition <c>O(n)</c> time (hashes) and <c>O(k)</c> space, where <c>k</c>
///         is the number of distinct values in the stream.</li>
/// </ul>
/// </summary>
/// <returns>A terminal operation that calculates various statistical values of the stream.</returns>
/// <seealso cref="Stats"/>
template <typename ResultType = double, bool MinMax = false, bool Median = false, bool Mode = false>
auto stats() {
    return detail::make_terminal([](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::stats expects a non-empty stream");
        }
        using T = std::decay_t<decltype(stream.next())>;
        Stats<T, ResultType, MinMax, Median, Mode> stats(stream.next());
        while (stream.has_next()) {
            stats.next(std::move(stream.next()));
        }
        stats.end();
        return stats;
    });
}
    }
}
#endif
