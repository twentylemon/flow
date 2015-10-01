
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
const int maxit = 1000;
const int maxv = 500001;
#else
const int maxit = 1;
const int maxv = 11;
#endif

class Widget
{
public:
    Widget() : value(0) { }
    Widget(int v) : value(v) { }
    int get_value() const {
        return value;
    }
    void set_value(int v) { value = v; }
    bool operator<(const Widget& rhs) const { return value < rhs.value; }
    Widget operator*(const Widget& rhs) const { return Widget(value * rhs.value); }
    bool operator==(const Widget& rhs) const { return value == rhs.value; }
    Widget operator++() { return Widget(value + 1); }
    int value;
    std::array<int, 500> arry;
    /*
    Widget& operator=(const Widget& w) { value = w.value; std::cout << "copy assign" << std::endl; return *this; }
    Widget& operator=(Widget&& w) { value = std::move(w.value); std::cout << "move assign" << std::endl; return *this; }
    Widget(const Widget& w) : value(w.value) { std::cout << "copy" << std::endl; }
    Widget(Widget&& w) : value(std::move(w.value)) { std::cout << "move" << std::endl; }
    */
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


std::vector<int> vec(maxv);


void run_timer() {
    using T = int;
    std::vector<T> vec(10000000);
    std::generate(vec.begin(), vec.end(), std::rand);
    T vv(0);
    boost::timer tv;
    for (int i = 0; i < maxit; i++) {
        vv = vec | filter([](int i) { return i % 17 == 0; }) | reverse() | max();
    }
    std::cout << std::endl << "streamv: " << tv.elapsed() << "\t" << vv << std::endl;
    T v_(0);
    boost::timer t_;
    for (int i = 0; i < maxit; i++) {
        //v_ = vec | filter([](int i) { return i % 17 == 0; }) | reverse_() | max();
    }
    std::cout << std::endl << "stream_: " << t_.elapsed() << "\t" << v_ << std::endl;
}


int main(int argc, char** argv) {
    std::iota(vec.begin(), vec.end(), 0);
    using T = decltype(vec)::value_type;
    std::size_t inc = iota(0) | nth(50);
    std::cout << inc << '\t' << vec.size() << std::endl;
    auto endl = []() { std::cout << std::endl; };

    std::vector<int> cw{ 1, 2, 3 };

    cycle(cw, 4) | unique() | dump();
    endl();

    //cycle(cw, 1) | replace(1, 3) | dump();
    //range(0, 26, 5) | dump();
    cycle_move(std::move(cw), 4) | take_while([](int i) { return i == 1; }) | dump();

    boost::timer t1;
    std::pair<T, T> m1;
    for (int i = 0; i < maxit; i++) {
        m1 = vec | filter([](auto i) { return i % 2 == 0; }) | map([](auto i) { return i*i; }) | minmax();
        //m1 = vec | filter([](const auto& i) { return i.value % 2 == 0; }) | map([](const auto& i) { return i*i; }) | minmax();
    }
    std::cout << std::endl << "stream: " << t1.elapsed() << "\t" << m1.first << "\t" << m1.second << std::endl;

    boost::timer t2;
    std::pair<T, T> m2;
    T v2 = 0;
    for (int i = 0; i < maxit; i++) {
        v2 = vec.front() * vec.front();
        m2 = std::make_pair(v2, v2);
        for (auto it = vec.begin(), end = vec.end(); it != end; ++it) {
            if (*it % 2 == 0) {
            //if (it->value % 2 == 0) {
                T q = *it * *it;
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
    std::cout << std::endl << std::endl;
    //const std::vector<Widget> w = widgets;
    //std::cout << (from(widgets) | map(&Widget::get_value) | min()) << std::endl;
    //from(w) | map(&Widget::get_value) | each([](int i) { std::cout << i << " "; });

    std::cout << std::endl << std::endl;


    std::cout << std::endl;
    const auto v = vec | limit(10) | to_vector();
    vec | limit(1) | zip(v | zip(v)) | zip(vec, [](auto&& l, auto&& r) { return std::make_pair(l, r); }) | each([](auto&& t) {
    std::cout << typeid(t).name() << std::endl;
    });

    vec | zip(vec | zip(vec | zip(vec))) | limit(1) | each([](auto&& t) { std::cout << typeid(t).name() << std::endl; });
    */
    //run_timer();

    std::cout << std::endl;
    system("pause");
    return 0;
}
