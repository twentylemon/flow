
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <numeric>
#include <algorithm>

#include <boost/timer.hpp>

#include <flow.h>

#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>

//#define INCLUDE_STREAMS
#ifdef INCLUDE_STREAMS
#include "Streams/Stream.h" // http://jscheiny.github.io/Streams/
#endif

#include "LargeClass.h"
#include "DynInt.h"

constexpr std::size_t VECTOR_SIZE    = 100000;

std::size_t PREVENT_CACHE = 0;  // modify this to prevent cache optimizations

#endif
