
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
#ifndef FLOW_FLOW_H
#define FLOW_FLOW_H

#include "generator/from.h"

#include "terminal/fold.h"
#include "terminal/sum.h"
#include "terminal/product.h"
#include "terminal/count.h"
#include "terminal/each.h"
#include "terminal/first.h"
#include "terminal/last.h"
#include "terminal/nth.h"
#include "terminal/min.h"
#include "terminal/max.h"
#include "terminal/minmax.h"
#include "terminal/any.h"
#include "terminal/all.h"
#include "terminal/none.h"
#include "terminal/contains.h"
#include "terminal/copy.h"
#include "terminal/dump.h"
#include "terminal/to.h"

#include "intermediate/map.h"
#include "intermediate/sort.h"
#include "intermediate/filter.h"
#include "intermediate/slice.h"
#include "intermediate/skip.h"
#include "intermediate/limit.h"
#include "intermediate/take_while.h"
#include "intermediate/drop_while.h"
#include "intermediate/peek.h"
#include "intermediate/replace.h"
#include "intermediate/concat.h"
#include "intermediate/reverse.h"
#include "intermediate/unique.h"

namespace flow {
    using namespace generator;
    using namespace terminal;
    using namespace intermediate;
}

#endif
