
#include <iostream>
#include <fstream>
#include <array>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <chrono>

#include <boost/timer.hpp>
#include <complex>

#include <flow.h>
using namespace flow;

#ifndef _DEBUG
const int maxit = 100;
const int maxv = 25000000;
#else
const int maxit = 1;
const int maxv = 1001;
#endif

#include <tbb/pipeline.h>

int main(int argc, char** argv) {
	std::vector<int> vec(100000);
	std::generate(vec.begin(), vec.end(), std::rand);
	auto f = [](int i){
		auto d = std::sin(std::sin(std::sin(std::atan2(i, i)))) / std::pow(2, i);
		for (int i = 0; i < 500000; i++)
			d = std::sqrt(d);
		d = d * std::atan2(i, d);
		return std::cos(d) * std::sin(d) * std::pow(d, 1.0/d) + 1.0;
	};
	auto r = std::rand();
	boost::timer t1;
	auto s = vec | map(f) | sum();
	std::cout << t1.elapsed() << std::endl;
	
	boost::timer t2;
	auto current = vec.data();
	auto end = vec.data() + vec.size();
	double sum = 0.0;
	tbb::parallel_pipeline(2,
		tbb::make_filter<void, int*>(
			tbb::filter::serial,
			[&current,&end](tbb::flow_control& fc) -> int* {
				if (current < end) {
					return current++;
				}
				fc.stop();
				return nullptr;
			}
		) &
		tbb::make_filter<int*, int>(tbb::filter::parallel, [](int* i){ return *i; }) &
		tbb::make_filter<int, double>(
			tbb::filter::parallel,
			f
		) & 
		tbb::make_filter<double, void>(
			tbb::filter::serial,
			[&sum](double x){ sum += x; }
		)
	);
	std::cout << t2.elapsed() << std::endl;
	boost::timer t3;
	auto current2 = vec.data();
	auto end2 = vec.data() + vec.size();
	double sum2 = 0.0;
	tbb::parallel_pipeline(1,
		tbb::make_filter<void, int*>(
			tbb::filter::serial,
			[&current2,&end2](tbb::flow_control& fc) -> int* {
				if (current2 < end2) {
					return current2++;
				}
				fc.stop();
				return nullptr;
			}
		) &
		tbb::make_filter<int*, int>(tbb::filter::serial, [](int* i){ return *i; }) &
		tbb::make_filter<int, double>(
			tbb::filter::serial,
			f
		) & 
		tbb::make_filter<double, void>(
			tbb::filter::serial,
			[&sum2](double x){ sum2 += x; }
		)
	);
	std::cout << t3.elapsed() << std::endl;
	std::cout << s << "\t" << sum << "\t" << sum2 << std::endl;
    return 0;
}
