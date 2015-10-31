
#include <examples.h>

void terminal_example() {
    // Terminal::then(F func): applies `func` to the result of this terminal operation.
    // F is a function that takes the result of this terminal as it's only parameter and returns a new result (or void)
    from({ 1, 2, 3, 4 }) | any([](int i) { return i > 5; }).then(std::logical_not<bool>()); // true
    from({ 5, 6, 7, 8 }) | sum(0).then([](int i) { return i*i; });  // (5+6+7+8)^2 = 26*26 = 676

    // "Terminal::value(): directly access the value of an optional return value.
    // if there is no value in the optional, this leads to undefined results
    from({ 5, 6, 7, 8 }) | sum().value();    // 26; no need to use operator* to get the value
    from({ 1, 2, 3, 4 }) | map([](int i) { return 2 * i; }) | max().value();    // 8

    // Terminal::value_or(T def): access the contained value of an optional, or use `def` if no value exists.
    // as per optional::value_or, a copy of the value in the optional is returned
    from({ 1, 2, 3, 4 }) | filter([](int i) { return i > 100; }) | sum().value_or(-1);  // -1; stream was empty so no value in sum
    from({ 1, 2, 3, 4 }) | sum().value_or(-1);  // (1+2+3+4) = 10; there was a value

    // Terminal::if_then(F func, G other): applies `func` to the result if the optional has a value, `other` otherwise.
    // F is a function that takes the underlying type in the optional, ie optional<T> -> takes a T&; it's result is returned
    // G takes no parameters and it's result and returned
    from({ 1, 2, 3, 4 }) | sum().if_then([](int i) { std::cout << "sum = " << i << std::endl; });   // displays "sum = 10"

    empty<int>() | sum().if_then([](int i) { std::cout << "sum = " << std::endl; },
        []() { std::cout << "no sum!" << std::endl; }); // displays "no sum!"

    from({ 5, 6, 7, 8 }) | sum().if_then([](int i) { std::cout << i; }, []() { std::cout << "empty"; });    // displays 26

    int r = empty<int>() | sum().if_then([](int i) { return i*i; }, []() { return -1; });       // r = -1
    r = from({ 1, 2, 3, 4 }) | sum().if_then([](int i) { return i*i; }, []() { return -1; });   // r = 10*10 = 100
}
