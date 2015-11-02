
#include "main.h"

template <typename T, typename TimerFunc>
auto run_timer(const std::vector<T>& vec, std::size_t maxit, TimerFunc func) {
    std::pair<double, std::decay_t<decltype(func(vec))>> ret;
    boost::timer t;
    for (std::size_t i = 0; i < maxit; ++i) {
        ret.second = func(vec);
        PREVENT_CACHE += vec.size();
    }
    ret.first = t.elapsed();
    return ret;
}

template <typename T>
void find_min(std::size_t maxit) {
    std::vector<T> vec(VECTOR_SIZE);
    std::generate(vec.begin(), vec.end(), std::rand);

    std::cout << maxit << " iterations of get min with type = " << typeid(std::declval<T>()).name() << std::endl
        << "flow:   " << run_timer(vec, maxit, [](auto& v) { return v | flow::min().value(); }) << std::endl
        << "stl:    " << run_timer(vec, maxit, [](auto& v) { return *std::min_element(v.begin(), v.end()); }) << std::endl
        << "range:  " << run_timer(vec, maxit, [](auto& v) { return *boost::min_element(v); }) << std::endl
#ifdef INCLUDE_STREAMS
        << "stream: " << run_timer(vec, maxit, [](auto& v) { return stream::MakeStream::from(v) | stream::op::min(); }) << std::endl
#endif
        << std::endl;
}

template <typename T>
void random_count(std::size_t maxit) {
    std::vector<T> vec(VECTOR_SIZE);
    std::generate(vec.begin(), vec.end(), std::rand);
    auto m = [](const T& i) { return i*i / 2; };
    auto lt = [](const T& i) { return i < 1000; };
    auto even = [](const T& i) { return i % 2 == 0; };

    std::cout << maxit << " iterations of map(i*i/2) | filter(evens) | count_if(<1000) with type = " << typeid(std::declval<T>()).name() << std::endl
        << "flow:   " << run_timer(vec, maxit, [&m, &lt, &even](auto& v) {
        return v | flow::map(m) | flow::filter(even) | flow::count_if(lt);
    }) << std::endl
        << "stl:    " << run_timer(vec, maxit, [&m, &lt, &even](auto& v) {
        return std::count_if(v.begin(), v.end(), [&m, &lt, &even](const T& i) {
            T j = m(i);
            return even(j) && lt(j);
        });
    }) << std::endl
        << "range:  " << run_timer(vec, maxit, [&m, &lt, &even](auto& v) {
        return boost::count_if(v | boost::adaptors::transformed(m) | boost::adaptors::filtered(even), lt);
    }) << std::endl
#ifdef INCLUDE_STREAMS
        << "stream: " << run_timer(vec, maxit, [&m, &lt, &even](auto& v) {
        return stream::MakeStream::from(v) | stream::op::map_(m) | stream::op::filter(even) | stream::op::filter(lt) | stream::op::count();
    }) << std::endl
#endif
        << std::endl;
}

void collatz_length(std::size_t max) {
    std::size_t min = 1;
    std::size_t size;
    auto next = [](std::size_t i) { return i % 2 == 0 ? i / 2 : 3 * i + 1; };
    std::cout << "counting total collatz conjecture series lengths from 1 to " << max << std::endl;
    
    boost::timer t;
    size = flow::closed_range(min, max) | flow::flat_map([&next](std::size_t i) {
        return flow::iterate(next, i) | flow::take_while([](std::size_t v) { return v != 1; });
    }) | flow::count();
    std::cout << "flow:   " << std::make_pair(t.elapsed(), size) << std::endl;

    t.restart();
    size = 0;
    for (std::size_t i = min; i <= max; ++i) {
        size += flow::iterate(next, i) | flow::take_while([](std::size_t v) { return v != 1; }) | flow::count();
    }
    std::cout << "flow (no flat_map): " << std::make_pair(t.elapsed(), size) << std::endl;

    t.restart();
    size = 0;
    for (std::size_t i = min; i <= max; ++i) {
        std::size_t v = i;
        while (v != 1) {
            v = next(v);
            ++size;
        }
    }
    std::cout << "stl:    " << std::make_pair(t.elapsed(), size) << std::endl;

#ifdef INCLUDE_STREAMS
    t.restart();
    size = stream::MakeStream::closed_range(min, max) | stream::op::flat_map([&next](std::size_t i) {
        return stream::MakeStream::iterate(i, next) | stream::op::take_while([](std::size_t v) { return v != 1; });
    }) | stream::op::count();
    std::cout << "streams: " << std::make_pair(t.elapsed(), size) << std::endl;

    size = 0;
    for (std::size_t i = min; i <= max; ++i) {
        size += stream::MakeStream::iterate(i, next) | stream::op::take_while([](std::size_t v) { return v != 1; }) | stream::op::count();
    }
    std::cout << "streams (no flat_map): " << std::make_pair(t.elapsed(), size) << std::endl;
#endif
}

int main(int argc, char** argv) {
    
    find_min<int>(1000);
    find_min<DynInt>(1000);
    find_min<LargeClass>(1000);

    random_count<int>(1000);
    random_count<DynInt>(100);
    random_count<LargeClass>(1000);
    
    collatz_length(1000000);
    
    std::cout << std::endl << PREVENT_CACHE << std::endl;
    system("pause");
    return 0;
}
