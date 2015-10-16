
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

#include <set>
#include <map>
#include <iostream>

#include "Terminal.h"
#include "dump.h"

namespace flow {

/// <summary>
/// Class to wrap all the statistics returned by stats().
/// <para>The count, mean, standard deviation, variance, sum and sum of squares of the stream
/// elements are always calculated. Conditionally calculates additional statistics like
/// median and mode, etc. If those values are not calculated, using the <c>getter</c> methods
/// will result in a compiler error.</para>
/// </summary>
/// <seealso cref="stats()"/>
template <typename T, typename ResultType, bool MinMax, bool MedianMode>
class Stats
{
public:
    /// <summary>
    /// Initializes a new instance of the Stats class.
    /// </summary>
    /// <param name="ele"/>The first element from the stream.</param>
    Stats(const T& ele) : _min(ele), _max(ele), _mean(0), _median(0), _modes(), _stddev(0), _variance(0), _sum(ele), _sum_squares(ele * ele), _n(1), _freq({ { ele, 1 } }) { }
        
    Stats(const Stats<T, ResultType, MinMax, MedianMode>&) = default;
    Stats(Stats<T, ResultType, MinMax, MedianMode>&&) = default;
    Stats<T, ResultType, MinMax, MedianMode>& operator=(const Stats<T, ResultType, MinMax, MedianMode>&) = default;
    Stats<T, ResultType, MinMax, MedianMode>& operator=(Stats<T, ResultType, MinMax, MedianMode>&&) = default;
    
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
    template <bool B = MedianMode, typename = std::enable_if_t<B>>
    ResultType median() const {
        return _median;
    }

    /// <summary>
    /// Returns the minimum mode value calculated [conditionally compiled].
    /// </summary>
    /// <returns>The minimum mode value of the stream.</returns>
    template <bool B = MedianMode, typename = std::enable_if_t<B>>
    const T& mode() const {
        return _modes[0];
    }
    
    /// <summary>
    /// Returns the mode value(s) calculated [conditionally compiled].
    /// </summary>
    /// <returns>The mode value(s) of the stream.</returns>
    template <bool B = MedianMode, typename = std::enable_if_t<B>>
    const std::vector<T>& modes() const {
        return _modes;
    }

    /// <summary>
    /// Returns the frequency of which each element occurred in the stream [conditionally compiled].
    /// </summary>
    /// <returns>The mode value of the stream.</returns>
    template <bool B = MedianMode, typename = std::enable_if_t<B>>
    const std::map<T, std::size_t> frequency() const {
        return _freq;
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
    void next(const T& value) {
        ++_n;
        _sum += value;
        _sum_squares += value * value;
        if (MinMax) {
            update_minmax(value);
        }
        if (MedianMode) {
            update_medianmode(value);
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
        if (MedianMode) {
            end_medianmode();
        }
    }

private:
    /// <summary>
    /// Updates the min/max value.
    /// </summary>
    /// <param name="value"/>The next value in the stream.</param>
    void update_minmax(const T& value) {
        if (value < _min) {
            _min = value;
        }
        else if (_max < value) {
            _max = value;
        }
    }

    /// <summary>
    /// Updates the median and mode values.
    /// </summary>
    /// <param name="value"/>The next value in the stream.</param>
    void update_medianmode(const T& value) {
        auto lower = _freq.lower_bound(value);
        if (lower != _freq.end() && !(_freq.key_comp()(value, lower->first))) {
            ++lower->second;
        }
        else {
            _freq.insert(lower, std::make_pair(value, 1));
        }
    }

    /// <summary>
    /// Called once the stream is ended; finishes calculating the median and mode values.
    /// </summary>
    void end_medianmode() {
        std::size_t mode_count = 0;
        std::size_t count = 0;
        std::size_t median_at = (_n + 1) / 2;   // correct if n odd, if even, avg median_at+1 with it
        bool dead_on = false;
        bool median_found = false;
        for (auto it = _freq.begin(), end = _freq.end(); it != end; ++it) {
            if (mode_count < it->second) {
                _modes.clear();                 // new mode found
                _modes.push_back(it->first);
                mode_count = it->second;
            }
            else if (mode_count == it->second) {
                _modes.push_back(it->first);    // another mode found
            }
            if (!median_found) {
                count += it->second;
                if (dead_on) {
                    _median = (_median + static_cast<ResultType>(it->first)) / 2.0;
                    median_found = true;            // we need to average this and the previous value
                }
                else {
                    if (count > median_at) {
                        _median = static_cast<ResultType>(it->first);
                        median_found = true;        // we passed the median; it's this value regardless of n
                    }
                    else if (count == median_at) {  // dead on the expected location of the median
                        _median = static_cast<ResultType>(it->first);
                        if (_n % 2 == 0) {
                            dead_on = true;         // median is the average of this and the next number
                        }
                        else {
                            median_found = true;    // or it's just this number
                        }
                    }
                }
            }
        }
    }

    T _min;                         // conditionally include min value of the stream
    T _max;                         // conditionally included max value of the stream
    ResultType _mean;               // mean of the stream; to be updated at stream end
    ResultType _median;             // conditionally include the median of the stream
    std::vector<T> _modes;          // conditionally include the modes of the stream
    ResultType _stddev;             // standard deviation of the stream; to be updated at stream end
    ResultType _variance;           // variance of the stream; to be updated at stream end
    ResultType _sum;                // sum of the values
    ResultType _sum_squares;        // sum of squares of values
    std::size_t _n;                 // the number of elements in the stream
    std::map<T, std::size_t> _freq; // frequency of each value in the stream
};
    
    namespace detail {

/// <summary>
/// Wrapper to avoid the display of the min/max of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MedianMode>
void display_minmax(std::ostream& out, const Stats<T, R, false, MedianMode>& stats) {
}

/// <summary>
/// Wrapper to display of the min/max of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MedianMode>
void display_minmax(std::ostream& out, const Stats<T, R, true, MedianMode>& stats) {
    out << ", min = " << stats.min() << ", max = " << stats.max();
}

/// <summary>
/// Wrapper to avoid the display of the median of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MinMax>
void display_medianmode(std::ostream& out, const Stats<T, R, MinMax, false>& stats) {
}

/// <summary>
/// Wrapper to display of the median of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MinMax>
void display_medianmode(std::ostream& out, const Stats<T, R, MinMax, true>& stats) {
    out << ", median = " << stats.median() << ", mode = [ ";
    stats.modes() | terminal::dump(out);
    out << ']';
}
    }

/// <summary>
/// Overload <c>operator&lt;&lt;</c> to display Stats objects.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
/// <returns><paramref name="out"/></returns>
template <typename T, typename R, bool MinMax, bool MedianMode>
std::ostream& operator<<(std::ostream& out, const Stats<T, R, MinMax, MedianMode>& stats) {
    out << "n = " << stats.n() << ", mu = " << stats.mean() << ", stddev = " << stats.stddev();
    flow::detail::display_medianmode(out, stats);
    flow::detail::display_minmax(out, stats);
    return out;
}

    namespace terminal {

/// <summary>
/// Returns a Stats object which contains several statistics of the stream values.
/// <para>The number of elements, mean, standard deviation, variance, sum and sum of squares are always calculated.</para>
/// <para>Some statistical values are calculated as <c>ResultType</c>, others are calculated as <c>T</c>, the type of elements
/// in the stream. Calculating statistics requires that both <c>T</c> and <c>ResultType</c> behave as arithmetic types
/// (such as <c>int</c>, <c>double</c> or <c>std::complex</c>).</para>
/// <para>The other template parameters indicate whether or not to calculate additional statistics, all of which are not
/// calculated by default. The behavior of each of them is as follows (<c>n</c> is the size of the stream):</para>
/// <ul>
///     <li><c>MinMax</c> - calculate the minimum and maximum value of the stream. The min and max are calculated as <c>T</c>.
///         This operation uses an additional <c>2n</c> time (slower than using minmax()).</li>
///     <li><c>MedianMode</c> - calculate the median, mode, and frequency of each element of the stream.
///         The median is calculated as <c>ResultType</c>, the modes as <c>std::vector&lt;T&gt;</c>, and the frequency table as
///         <c>std::map&lt;T, std::size_t&gt;</c>. If there is an even number of elements in the stream, the median is calculated
///         as the average of the two possible medians. This operation uses an additional <c>O(n logn)</c> time (<c>n</c> map insertions)
///         and <c>O(k)</c> space, where <c>k</c> is the number of distinct values in the stream.</li>
/// </ul>
/// </summary>
/// <returns>A terminal operation that calculates various statistical values of the stream.</returns>
/// <seealso cref="Stats"/>
/// <seealso cref="count()"/>
/// <seealso cref="sum()"/>
/// <seealso cref="minmax()"/>
/// <seealso cref="to_map()"/>
template <typename ResultType = double, bool MinMax = false, bool MedianMode = false>
auto stats() {
    return detail::make_terminal([](auto&& stream) {
        if (!stream.has_next()) {
            throw std::out_of_range("flow::stats expects a non-empty stream");
        }
        using T = std::decay_t<decltype(stream.next())>;
        Stats<T, ResultType, MinMax, MedianMode> stats(stream.next());
        while (stream.has_next()) {
            stats.next(stream.next());
        }
        stats.end();
        return stats;
    });
}
    }
}
#endif
