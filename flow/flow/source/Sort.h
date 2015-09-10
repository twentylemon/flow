
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
#ifndef FLOW_SOURCE_SORT_H
#define FLOW_SOURCE_SORT_H

#include <vector>
#include <algorithm>

namespace flow {
    namespace source {

/// <summary>
/// Stream source to sort the stream. Sorting is an eager operation, the entire stream up to this point
/// is evaluated and stored and finally sorted after.
/// </summary>
template <typename Source>
class Sort : public Iterator<typename std::vector<typename Source::value_type>::iterator>
{
public:
    using value_type = typename Source::value_type;
    using parent_type = Iterator<typename std::vector<value_type>::iterator>;

    /// <summary>
    /// Initializes a new instance of the <see cref="Sort{Source, Compare}" /> class.
    /// </summary>
    /// <param name="source">The source stream to sort.</param>
    /// <param name="compare">The comparator to use in the sort.</param>
    /// <param name="stable_sort"><c>true</c> to use <c>std::stable_sort</c>, otherwise <c>std::sort</c> is used.</param>
    template <typename Compare>
    Sort(Source&& source, Compare compare, bool stable_sort) : _source(std::forward<Source>(source)), _stream()
    {
        sort(compare, stable_sort); 
    }

    /// <summary>
    /// Pulls all the elements from the source stream and sorts them.
    /// </summary>
    /// <param name="compare">The comparator to use in the sort.</param>
    /// <param name="stable_sort"><c>true</c> to use <c>std::stable_sort</c>, otherwise <c>std::sort</c> is used.</param>
    template <typename Compare>
    void sort(Compare compare, bool stable_sort) {
        _stream.reserve(_source.estimate_size());
        while (_source.has_next()) {
            _stream.emplace_back(std::move(_source.next()));
        }
        if (stable_sort) {
            std::stable_sort(_stream.begin(), _stream.end(), compare);
        }
        else {
            std::sort(_stream.begin(), _stream.end(), compare);
        }
        parent_type::_current = _stream.begin();
        parent_type::_end = _stream.end();
    }

protected:
    Source _source;                     // the source to read from
    std::vector<value_type> _stream;    // the sorted stream
};
    }
}
#endif
