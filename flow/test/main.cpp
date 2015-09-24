
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
const int maxv = 750000;
#else
const int maxit = 1;
const int maxv = 1001;
#endif

class Widget
{
public:
    Widget() : value(0) { }
    Widget(int v) : value(v) { }
    int get_value() const {
        return value;
    }
    //Widget(const Widget& w) : value(w.value) { std::cout << "copy" << std::endl; }
    //Widget(Widget&& w) : value(std::move(w.value)) { std::cout << "move" << std::endl; }
    bool operator<(const Widget& rhs) const { return value < rhs.value; }
    Widget operator*(const Widget& rhs) const { return Widget(value * rhs.value); }
    bool operator==(const Widget& rhs) const { return value == rhs.value; }
    //Widget& operator=(const Widget& w) { value = w.value; std::cout << "copy assign" << std::endl; return *this; }
    //Widget& operator=(Widget&& w) { value = std::move(w.value); std::cout << "move assign" << std::endl; return *this; }
    int value;
    std::array<int, 500> arry;
};
std::ostream& operator<<(std::ostream& o, const Widget& w) {
    o << w.value;
    return o;
}

template <typename Container>
std::ostream& print(std::ostream& out, const Container& container) {
    std::copy(container.begin(), container.end(), std::ostream_iterator<typename Container::value_type>(out, " "));
    return out;
}


std::vector<Widget> vec(maxv);


void run_timer() {
    using T = int;
    std::vector<T> vec(maxv);
    std::generate(vec.begin(), vec.end(), std::rand);
    auto gt = [](T i) { return i > 10; };
    T vv(0);
    boost::timer tv;
    for (int i = 0; i < maxit; i++) {
        vv = iota(0, 5) | limit(vec.size()) | max();
    }
    std::cout << std::endl << "streamv: " << tv.elapsed() << "\t" << vv << std::endl;
    T v_(0);
    boost::timer t_;
    for (int i = 0; i < maxit; i++) {
        v_ = iterate(std::bind(std::plus<T>(), 5, std::placeholders::_1), 0) | limit(vec.size()) | max();
    }
    std::cout << std::endl << "stream_: " << t_.elapsed() << "\t" << v_ << std::endl;
}


int main(int argc, char** argv) {
    std::iota(vec.begin(), vec.end(), 0);
    using T = decltype(vec)::value_type;
    std::size_t inc = iota(0) | nth(50);
    std::cout << inc << '\t' << vec.size() << std::endl;

    boost::timer t1;
    std::pair<T, T> m1;
    T v1 = 0;
    T vv = 0;
    for (int i = 0; i < maxit; i++) {
        v1 = 0;
        //v1 = vec | filter([](T i) { return i % 2 == 0; }) | map([](T i) { return i*i; }) | min();
        m1 = vec | filter([](const auto& i) { return i.value % 2 == 0; }) | map([](const auto& i) { return i*i; }) | minmax();
    }
    std::cout << std::endl << "stream: " << t1.elapsed() << "\t" << m1.first << "\t" << m1.second << std::endl;
    
    boost::timer t2;
    std::pair<T, T> m2;
    T v2 = 0;
    for (int i = 0; i < maxit; i++) {
        v2 = vec.front() * vec.front();
        m2 = std::make_pair(v2, v2);
        std::size_t s = 0;
        for (auto it = vec.begin(), end = vec.end(); it != end; ++it) {
            if (it->value % 2 == 0) {
                T q = *it * *it;
                //if (v2 < q) { v2 = q; }
                if (q < m2.first) { m2.first = q; }
                else if (m2.second < q) { m2.second = q; }
            }
        }
    }
    std::cout << std::endl << "stdlib: " << t2.elapsed() << "\t" << m2.first << "\t" << m2.second << std::endl;
    /*
    std::vector<Widget> widgets;
    for (int i = 0; i < 10; i++) {
        widgets.emplace_back(i);
    }
    const std::vector<Widget> w = widgets;
    std::cout << (from(widgets) | map(&Widget::get_value) | min()) << std::endl;
    from(widgets) | map(&Widget::get_value) | each([](int i) { std::cout << i << " "; });
    from(w) | map(&Widget::get_value) | each([](int i) { std::cout << i << " "; });
    
    std::cout << std::endl << std::endl;

    std::cout << (vec | count()) << std::endl;
    std::cout << (vec | contains(4)) << std::endl;
    std::cout << (vec | none([](int i) { return i == -1; })) << std::endl;
    
    vec | limit(5) | reverse() | concat(vec | limit(10)) | concat(vec | limit(1)) | dump();
    
    std::cout << std::endl;
    const std::vector<int> v = vec;
    vec | limit(1) | zip(v | zip(v)) | zip(vec, [](auto&& l, auto&& r) { return std::make_pair(l, r); }) | each([](auto&& t) {
        std::cout << typeid(t).name() << std::endl;
    });
    
    //run_timer();

    auto c = uncurry([](int i, int j, int k) { return i * j * k; });
    auto c2 = uncurry(std::multiplies<int>());
    std::cout << c(std::make_tuple(4, 5, 2)) << std::endl;
    std::cout << c2(std::make_tuple(4, 1)) << std::endl;

    iterate(std::bind(std::plus<int>(), 1, std::placeholders::_1), 1) | limit(10) | dump();
    iterate(std::plus<int>(), 0, 1) | limit(10) | dump();
    
    empty<int>() | dump();
    
    from(widgets) | filter([](const Widget& w){ return w.value > 5; }) | dump();
    */
    std::cout << std::endl;
    system("pause");
    return 0;
}
