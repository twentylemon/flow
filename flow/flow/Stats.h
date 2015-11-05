
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
 
#ifndef FLOW_STATS_H
#define FLOW_STATS_H

#include <map>
#include <iostream>

#include "terminal/dump.h"

namespace flow {

template <typename T, typename ResultType, bool MinMax, bool MedianMode>
class Stats;

    namespace detail {

        namespace minmax {
/// <summary>
/// Updates the min/max values held by <paramref name="stats"/>.
/// </summary>
/// <param name="value">The next value in the stream.</param>
/// <param name="stats">The Stats object to update.</param>
template <typename T, typename ResultType, bool MedianMode>
void update(const T& value, Stats<T, ResultType, true, MedianMode>& stats) {
    if (value < stats._min) {
        stats._min = value;
    }
    else if (stats._max < value) {
        stats._max = value;
    }
}

/// <summary>
/// Ignores updating the min/max for <paramref name="stats"/> since it is not enabled.
/// </summary>
/// <param name="value">The next value in the stream.</param>
/// <param name="stats">The Stats object, ignored.</param>
template <typename T, typename ResultType, bool MedianMode>
void update(const T& value, Stats<T, ResultType, false, MedianMode>& stats) {
}

/// <summary>
/// Wrapper to display of the min/max of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MedianMode>
void display(std::ostream& out, const Stats<T, R, true, MedianMode>& stats) {
    out << ", min = " << stats.min() << ", max = " << stats.max();
}

/// <summary>
/// Wrapper to avoid the display of the min/max of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MedianMode>
void display(std::ostream& out, const Stats<T, R, false, MedianMode>& stats) {
}
        }

        namespace medianmode {
/// <summary>
/// Updates the median/mode values held by <paramref name="stats"/>.
/// </summary>
/// <param name="value">The next value in the stream.</param>
/// <param name="stats">The Stats object to update.</param>
template <typename T, typename ResultType, bool MinMax>
void update(const T& value, Stats<T, ResultType, MinMax, true>& stats) {
    auto lower = stats._freq.lower_bound(value);
    if (lower != stats._freq.end() && !(stats._freq.key_comp()(value, lower->first))) {
        ++lower->second;
    }
    else {
        stats._freq.insert(lower, std::make_pair(value, 1));
    }
}

/// <summary>
/// Ignores updating the median/mode for <paramref name="stats"/> since it is not enabled.
/// </summary>
/// <param name="value">The next value in the stream.</param>
/// <param name="stats">The Stats object, ignored.</param>
template <typename T, typename ResultType, bool MinMax>
void update(const T& value, Stats<T, ResultType, MinMax, false>& stats) {
}

/// <summary>
/// Finishes calculating the median/mode for <paramref name="stats"/>.
/// </summary>
/// <param name="stats">The Stats object to finalize.</param>
template <typename T, typename ResultType, bool MinMax>
void end(Stats<T, ResultType, MinMax, true>& stats) {
    std::size_t mode_count = 0;
    std::size_t count = 0;
    std::size_t median_at = (stats._n + 1) / 2; // correct if n odd, if even, avg median_at+1 with it
    bool dead_on = false;
    bool median_found = false;
    for (auto it = stats._freq.begin(), end = stats._freq.end(); it != end; ++it) {
        if (mode_count < it->second) {
            stats._modes.clear();               // new mode found
            stats._modes.push_back(it->first);
            mode_count = it->second;
        }
        else if (mode_count == it->second) {
            stats._modes.push_back(it->first);  // another mode found
        }
        if (!median_found) {
            count += it->second;
            if (dead_on) {
                stats._median = (stats._median + static_cast<ResultType>(it->first)) / static_cast<ResultType>(2.0);
                median_found = true;            // we need to average this and the previous value
            }
            else {
                if (count > median_at) {
                    stats._median = static_cast<ResultType>(it->first);
                    median_found = true;        // we passed the median; it's this value regardless of n
                }
                else if (count == median_at) {  // dead on the expected location of the median
                    stats._median = static_cast<ResultType>(it->first);
                    if (stats._n % 2 == 0) {
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

/// <summary>
/// Ignored finalizing the median/mode of <paramref name="stats"/> since it is not enabled.
/// </summary>
/// <param name="stats">The Stats object, ignored.</param>
template <typename T, typename ResultType, bool MinMax>
void end(Stats<T, ResultType, MinMax, false>& stats) {
}

/// <summary>
/// Wrapper to avoid the display of the median of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MinMax>
void display(std::ostream& out, const Stats<T, R, MinMax, false>& stats) {
}

/// <summary>
/// Wrapper to display of the median of a Stats object.
/// </summary>
/// <param name="out"/>The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
template <typename T, typename R, bool MinMax>
void display(std::ostream& out, const Stats<T, R, MinMax, true>& stats) {
    out << ", median = " << stats.median() << ", mode = [ ";
    stats.modes() | terminal::dump(out);
    out << ']';
}
        }
    }

/// <summary>
/// Class to wrap all the statistics returned by stats().
/// <para>The count, mean, standard deviation, variance, sum and sum of squares of the stream
/// elements are always calculated. Conditionally calculates additional statistics indicated
/// by the template parameters. If those values are not calculated, using the <c>getter</c> methods
/// will result in a compiler error.</para>
/// </summary>
/// <seealso cref="stats()"/>
template <typename T, typename ResultType, bool MinMax, bool MedianMode>
class Stats
{
public:
    /// <summary>
    /// <c>std::true_type</c> if <c>MinMax</c> is <c>true</c>, <c>std::false_type</c> otherwise.
    /// </summary>  
    using minmax = std::conditional_t<MinMax, std::true_type, std::false_type>;

    /// <summary>
    /// <c>std::true_type</c> if <c>MedianMode</c> is <c>true</c>, <c>std::false_type</c> otherwise.
    /// </summary>  
    using medianmode = std::conditional_t<MedianMode, std::true_type, std::false_type>;

    /// <summary>
    /// Initializes a new instance of the Stats class.
    /// </summary>
    /// <param name="ele"/>The first element from the stream.</param>
    Stats(const T& ele) : _min(ele), _max(ele), _mean(0), _median(0), _modes(), _stddev(0), _variance(0),
        _sum(static_cast<ResultType>(ele)), _sum_squares(static_cast<ResultType>(ele * ele)), _n(1), _freq({ { ele, 1 } }) { }

    Stats(const Stats<T, ResultType, MinMax, MedianMode>&) = default;
    Stats(Stats<T, ResultType, MinMax, MedianMode>&&) = default;
    Stats<T, ResultType, MinMax, MedianMode>& operator=(const Stats<T, ResultType, MinMax, MedianMode>&) = default;
    Stats<T, ResultType, MinMax, MedianMode>& operator=(Stats<T, ResultType, MinMax, MedianMode>&&) = default;

    /// <summary>
    /// Returns <c>true</c> if the min/max values have been calculated.
    /// </summary>
    /// <returns><c>MinMax</c> template argument.</returns>
    constexpr bool has_minmax() const {
        return MinMax;
    }
    /// <summary>
    /// Returns <c>true</c> if the median/mode values have been calculated.
    /// </summary>
    /// <returns><c>MedianMode</c> template argument.</returns>
    constexpr bool has_medianmode() const {
        return MedianMode;
    }

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
    T& mode() {
        return _modes[0];
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
    std::vector<T>& modes() {
        return _modes;
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
    std::map<T, std::size_t>& frequency() {
        return _freq;
    }

    /// <summary>
    /// Returns the frequency of which each element occurred in the stream [conditionally compiled].
    /// </summary>
    /// <returns>The mode value of the stream.</returns>
    template <bool B = MedianMode, typename = std::enable_if_t<B>>
    const std::map<T, std::size_t>& frequency() const {
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
        flow::detail::minmax::update(value, *this);
        flow::detail::medianmode::update(value, *this);
    }

    /// <summary>
    /// Called once the stream is ended; finishes calculating statistics values.
    /// <para>This method is internal to the flow library; it <em>should</em> be private,
    /// but g++ cannot friend an auto return type.</para>
    /// </summary>
    void end() {
        ResultType n = static_cast<ResultType>(_n);
        _mean = _sum / n;
        _variance = (_sum_squares * n - _sum * _sum) / (n * n);
        _stddev = std::sqrt(_variance);
        flow::detail::medianmode::end(*this);
    }

private:
    template <typename V, typename R, bool B>
    friend void flow::detail::minmax::update(const V&, Stats<V, R, true, B>&);

    template <typename V, typename R, bool B>
    friend void flow::detail::medianmode::update(const V&, Stats<V, R, B, true>&);
    template <typename V, typename R, bool B>
    friend void flow::detail::medianmode::end(Stats<V, R, B, true>&);

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

/// <summary>
/// Overload <c>operator&lt;&lt;</c> to display Stats objects.
/// </summary>
/// <param name="out">The out stream.</param>
/// <param name="stats"/>The statistics to display.</param>
/// <returns><paramref name="out"/></returns>
template <typename T, typename R, bool MinMax, bool MedianMode>
std::ostream& operator<<(std::ostream& out, const Stats<T, R, MinMax, MedianMode>& stats) {
    out << "n = " << stats.n() << ", mu = " << stats.mean() << ", stddev = " << stats.stddev();
    flow::detail::medianmode::display(out, stats);
    flow::detail::minmax::display(out, stats);
    return out;
}
}
#endif
