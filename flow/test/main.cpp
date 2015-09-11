
#include <iostream>
#include <fstream>
#include <array>
#include <list>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <numeric>

#include <boost/timer.hpp>
#include <complex>

#include <flow/flow.h>
using namespace flow;

#ifndef _DEBUG
const int maxit = 100;
const int maxv = 25000000;
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
    bool operator<(const Widget& rhs) const { return value < rhs.value; }
    Widget operator*(const Widget& rhs) const { return Widget(value * rhs.value); }
    bool operator==(const Widget& rhs) const { return value == rhs.value; }
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


std::vector<int> vec(maxv);


void run_timer() {
    using T = int;
    std::vector<T> vec(2 * maxv);
    std::generate(vec.begin(), vec.end(), std::rand);
    auto gt = [](T i) { return i > 10; };
    T vv(0);
    boost::timer tv;
    for (int i = 0; i < maxit; i++) {
        vv = vec | replace(T(0), T(5)) | min();
    }
    std::cout << std::endl << "streamv: " << tv.elapsed() << "\t" << vv << std::endl;
    T v_(0);
    boost::timer t_;
    for (int i = 0; i < maxit; i++) {
        //v_ = vec | replace_(T(0), T(5)) | min();
    }
    std::cout << std::endl << "stream_: " << t_.elapsed() << "\t" << v_ << std::endl;
}


int main(int argc, char** argv) {
    std::iota(vec.begin(), vec.end(), 0);
    using T = decltype(vec)::value_type;
    std::size_t inc = vec | nth(50);
    std::cout << inc << std::endl;

    boost::timer t1;
    std::pair<T, T> m1;
    T v1 = 0;
    T vv = 0;
    for (int i = 0; i < maxit; i++) {
        v1 = 0;
        //v1 = vec | filter([](T i) { return i % 2 == 0; }) | map([](T i) { return i*i; }) | min();
        m1 = vec | filter([](T i) { return i % 2 == 0; }) | map([](T i) { return i*i; }) | minmax();
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
            if (*it % 2 == 0) {
                T q = *it * *it;
                //if (v2 < q) { v2 = q; }
                if (q < m2.first) { m2.first = q; }
                else if (m2.second < q) { m2.second = q; }
            }
        }
    }
    std::cout << std::endl << "stdlib: " << t2.elapsed() << "\t" << m2.first << "\t" << m2.second << std::endl;

    std::vector<Widget> widgets;
    for (int i = 0; i < 10; i++) {
        widgets.emplace_back(i);
    }
    const std::vector<Widget> w = widgets;
    from(widgets) | map(&Widget::get_value) | dump();
    from(widgets) | map(&Widget::get_value) | each([](int i) { std::cout << i << " "; });
    from(w) | map(&Widget::get_value) | each([](int i) { std::cout << i << " "; });

    std::cout << std::endl << std::endl;

    std::cout << (vec | count()) << std::endl;
    std::cout << (vec | contains(4)) << std::endl;
    std::cout << (vec | none([](int i) { return i == -1; })) << std::endl;

    vec | filter([](int i) { return i % 2 == 0; }) | limit(5) | reverse() | concat(vec | limit(10)) | concat(vec | limit(1)) | map([](auto i) { return i * 2; }) | dump();

    std::cout << std::endl;
    const std::vector<int> v = vec;
    vec | limit(1) | zip(from(v) | zip(from(v))) | zip(from(vec)) | each([](auto& t) {
        std::cout << typeid(t).name() << std::endl;
    });

    //run_timer();

    std::cout << std::endl;
    system("pause");
    return 0;
}
