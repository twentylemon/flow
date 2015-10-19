
#include <examples.h>   // defines vec1to4 = {1,2,3,4}, vec5to8 = {5,6,7,8}

void terminal_example() {
    std::cout << "flow::detail::Terminal" << std::endl;

    std::cout << "Terminal::then(F func): applies `func` to the result of this terminal operation." << std::endl;
    vec1to4 | any([](int i) { return i > 5; }).then(std::logical_not<bool>());  // true
    vec5to8 | sum(0).then([](int i) { return i*i; });   // (5+6+7+8)^2 = 26*26 = 676

    std::cout << "Terminal::value(): directly access the value of an optional return value." << std::endl;
    vec5to8 | sum().value();    // 26; no need to use operator* to get the value
    vec1to4 | map([](int i) { return 2 * i; }) | max(); // 8

    std::cout << "Terminal::value_or(T def): access the contained value of an optional, or use `def` if no value exists." << std::endl;
    vec1to4 | filter([](int i) { return i > 100; }) | sum().value_or(-1);   // -1; stream was empty so no value in sum
    vec1to4 | sum().value_or(-1);       // (1+2+3+4) = 10; there was a value

    std::cout << std::endl << std::endl;
}
