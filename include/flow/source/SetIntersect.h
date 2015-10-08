
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
 
#ifndef FLOW_SOURCE_SETINTERSECT_H
#define FLOW_SOURCE_SETINTERSECT_H

#include "SetSource.h"

namespace flow {
    namespace source {

/// <summary>
/// The set operation which intersects set-streams and maintains sorted order.
/// </summary>
class IntersectOperation : public SetOperation
{
public:
    /// <summary>
    /// Action to perform when neither source is empty.
    /// <para>If the two elements are equal, one is kept and both streams advanced. Otherwise, the stream with the
    /// lower element is advanced and a continue state is returned.</para>
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns><c>UpdateState::UpdateContinue</c> if the elements are not equal, <c>UpdateState::UpdateComplete</c> otherwise.</returns>
    template <typename Source>
    UpdateState none_empty(Source& source) {
        if (source.compare_left_less()) {
            source.set_advance(AdvanceState::Left);
            return UpdateState::UpdateContinue;
        }
        else if (source.compare_right_less()) {
            source.set_advance(AdvanceState::Right);
            return UpdateState::UpdateContinue;
        }
        else {
            source.set_advance(AdvanceState::Both);
            source.set_next_to_left();
            return UpdateState::UpdateComplete;
        }
    }

    /// <summary>
    /// Action to perform when only the left source is empty.
    /// <para>No action, no more elements can be in the intersection once one source is empty.</para>
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns><c>UpdateState::EmptyStream</c> -- there cannot be any further elements.</returns>
    template <typename Source>
    UpdateState left_empty(Source& source) {
        return UpdateState::EmptyStream;
    }

    /// <summary>
    /// Action to perform when only the right source is empty.
    /// <para>No action, no more elements can be in the intersection once one source is empty.</para>
    /// </summary>
    /// <param name="source">The set source.</param>
    /// <returns><c>UpdateState::EmptyStream</c> -- there cannot be any further elements.</returns>
    template <typename Source>
    UpdateState right_empty(Source& source) {
        return UpdateState::EmptyStream;
    }
};

/// <summary>
/// Alias the SetIntersect source as a SetSource which uses the IntersectOperation.
/// </summary>
template <typename LeftSource, typename RightSource, typename Compare>
using SetIntersect = SetSource<LeftSource, RightSource, Compare, IntersectOperation>;
    }
}
#endif
