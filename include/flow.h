
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
 
#ifndef FLOW_FLOW_H
#define FLOW_FLOW_H

#include "flow/uncurry.h"
#include "flow/print_tuple.h"
#include "flow/optional.h"

#include "flow/generator/from.h"
#include "flow/generator/from_move.h"
#include "flow/generator/repeat.h"
#include "flow/generator/cycle.h"
#include "flow/generator/cycle_move.h"
#include "flow/generator/empty.h"
#include "flow/generator/generate.h"
#include "flow/generator/iterate.h"
#include "flow/generator/iota.h"
#include "flow/generator/range.h"
#include "flow/generator/closed_range.h"
#include "flow/generator/random.h"

#include "flow/terminal/fold.h"
#include "flow/terminal/sum.h"
#include "flow/terminal/product.h"
#include "flow/terminal/count.h"
#include "flow/terminal/each.h"
#include "flow/terminal/first.h"
#include "flow/terminal/last.h"
#include "flow/terminal/nth.h"
#include "flow/terminal/min.h"
#include "flow/terminal/max.h"
#include "flow/terminal/minmax.h"
#include "flow/terminal/any.h"
#include "flow/terminal/all.h"
#include "flow/terminal/none.h"
#include "flow/terminal/contains.h"
#include "flow/terminal/copy.h"
#include "flow/terminal/dump.h"
#include "flow/terminal/to.h"
#include "flow/terminal/execute.h"
#include "flow/terminal/sample.h"
#include "flow/terminal/reservoir.h"
#include "flow/terminal/stats.h"
#include "flow/terminal/inner_product.h"

#include "flow/intermediate/map.h"
#include "flow/intermediate/flat_map.h"
#include "flow/intermediate/sort.h"
#include "flow/intermediate/filter.h"
#include "flow/intermediate/slice.h"
#include "flow/intermediate/skip.h"
#include "flow/intermediate/limit.h"
#include "flow/intermediate/take_while.h"
#include "flow/intermediate/drop_while.h"
#include "flow/intermediate/peek.h"
#include "flow/intermediate/replace.h"
#include "flow/intermediate/concat.h"
#include "flow/intermediate/reverse.h"
#include "flow/intermediate/unique.h"
#include "flow/intermediate/zip.h"
#include "flow/intermediate/merge.h"
#include "flow/intermediate/set_union.h"
#include "flow/intermediate/set_intersect.h"
#include "flow/intermediate/set_diff.h"
#include "flow/intermediate/set_sym_diff.h"
#include "flow/intermediate/shuffle.h"

namespace flow {
    using namespace generator;
    using namespace terminal;
    using namespace intermediate;
}
using flow::operator|;

#endif
