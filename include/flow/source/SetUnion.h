
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
 
#ifndef FLOW_SOURCE_SETUNION_H
#define FLOW_SOURCE_SETUNION_H

#include "SetSource.h"

namespace flow {
    namespace source {

/// <summary>
/// The set operation which unions set-streams and maintains sorted order.
/// </summary>
class UnionOperation : public SetOperation
{
public:
    /// <summary>
    /// Action to perform when neither source is empty.
    /// <para>Assigns the next value of the set source to be the lower of the two possible values.
    /// If the two values are equal, then the duplicate value is ignored.</para>
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns><c>UpdateState::UpdateComplete</c> -- the operation always completes after one call.</returns>
    template <typename Source>
    UpdateState none_empty(Source& source) {
        if (source.compare_left_less()) {
            source.set_advance(AdvanceState::Left);
            source.set_next_to_left();
        }
        else if (source.compare_right_less()) {
            source.set_advance(AdvanceState::Right);
            source.set_next_to_right();
        }
        else {
            source.set_advance(AdvanceState::Both);
            source.set_next_to_left();
        }
        return UpdateState::UpdateComplete;
    }
};

/// <summary>
/// Alias the SetUnion source as a SetSource which uses the UnionOperation.
/// </summary>
template <typename LeftSource, typename RightSource, typename Compare>
using SetUnion = SetSource<LeftSource, RightSource, Compare, UnionOperation>;
    }
}
#endif
