

#include "test.h"

BOOST_AUTO_TEST_SUITE(flow_core)
#include "iterator.h"
#include "uncurry.h"
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(flow_generator)
#include "generator/closed_range.h"
#include "generator/cycle.h"
#include "generator/cycle_move.h"
#include "generator/empty.h"
#include "generator/from.h"
#include "generator/from_move.h"
#include "generator/generate.h"
#include "generator/iota.h"
#include "generator/iterate.h"
#include "generator/range.h"
#include "generator/repeat.h"
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(flow_intermediate)
#include "intermediate/concat.h"
#include "intermediate/drop_while.h"
#include "intermediate/filter.h"
#include "intermediate/flat_map.h"
#include "intermediate/limit.h"
#include "intermediate/map.h"
#include "intermediate/peek.h"
#include "intermediate/replace.h"
#include "intermediate/reverse.h"
#include "intermediate/skip.h"
#include "intermediate/slice.h"
#include "intermediate/sort.h"
#include "intermediate/take_while.h"
#include "intermediate/unique.h"
#include "intermediate/zip.h"
#include "intermediate/merge.h"
#include "intermediate/set_union.h"
#include "intermediate/set_intersect.h"
#include "intermediate/set_diff.h"
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(flow_terminal)
#include "terminal/all.h"
#include "terminal/any.h"
#include "terminal/contains.h"
#include "terminal/copy.h"
#include "terminal/count.h"
#include "terminal/dump.h"
#include "terminal/each.h"
#include "terminal/execute.h"
#include "terminal/first.h"
#include "terminal/fold.h"
#include "terminal/last.h"
#include "terminal/max.h"
#include "terminal/min.h"
#include "terminal/minmax.h"
#include "terminal/none.h"
#include "terminal/nth.h"
#include "terminal/product.h"
#include "terminal/sum.h"
#include "terminal/to.h"
#include "terminal/sample.h"
#include "terminal/reservoir.h"
BOOST_AUTO_TEST_SUITE_END()
