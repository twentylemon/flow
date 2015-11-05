
sick flow, bro
==============

Inspired by Java 8 [Streams](http://www.oracle.com/technetwork/articles/java/ma14-java-se-8-streams-2177646.html),
flow is a C++14 library that provides lazy evaluation and functional transformations on data. It's like Haskell for C++.
The library provides many common data transformations, such as map, filter and fold, as well as other commonly used
operations like computing the sum, min and max or simply counting the number or elements. And all of it is packaged
in a nice, easy to read and understand syntax. To use, simply `#include <flow.h>` in your C++14 program. With fully
optimized code, flow offers minimal performance penalties so there's no reason not to love.

 * [Documentation](http://twentylemon.github.io/flow/doxy/index.html)


What is a Sick Flow?
--------------------
A flow is usually called a stream. But if I called the library "Stream" I couldn't say "sick flow" all the time.
I'll use flow and stream interchangeably, just know that a stream is a forward, single-pass source of data, data
that would want to do things with.

Creating a Sick Flow
--------------------
The `flow::generator` namespace contains several factory methods for creating a Stream object. Probably the most
common generator used is `from()`, which creates a Stream from an iterator range or a container.

```C++
auto stream = from(my_vector); // a stream over the entire vector in the same order
```

Since it's very common, the pipe operator is overloaded for container types as a shorthand for `from()`. So the following
statements create and process the same stream.

```C++
from(my_vector) | each(process);    // process each vector element
my_vector | each(process);          // shorthand, the same operation as above
```

Other common stream generators are `iota()`, which counts up from a value, and `repeat()`, which repeats a value.
Several others are included in the [flow::generator](http://twentylemon.github.io/flow/doxy/de/d3f/namespaceflow_1_1generator.html) namespace.

Manipulating a Sick Flow
------------------------
Operations are applied using `operator|`. Above, we wrote `my_vector | each(process)` -- this is applying the `each`
operation to the stream created from `my_vector`. Intermediate operations can be chained together by applying `operator|`
again. We'll get into that after a quick example.

Say you have a list of numbers, and you want to do something with at most 10 of the even values. Say you want
to `process` their square. How would you do that in normal C++? Probably something like

```C++
int count = 0;
for (auto it = list.begin(), end = list.end(); it != end && count < 10; ++it) {
    if (*it % 2 == 0) {
        ++count;
        process(*it * *it);
    }
}
```

Not bad, but it's not quickly clear what is going on. The same operation can be done as a sick flow instead:

```C++
list
    | filter([](int i) { return i % 2 == 0; })
    | map([](int i) { return i*i; })
    | limit(10)
    | each(process);
```

Reading the flow aloud, it's obvious what is happening. Take the list, keep even values, map the elements to their square,
limit it to 10 elements, and then process each of those. Fun. This is just a trivial example, there many other
stream operations available to be used.

Stream operations are broken down into two main types: Intermediate and Terminal operations. Intermediate operations
transform a stream into another stream. We saw three examples above in `filter`, `limit` and `map`. Intermediate
operations are meaningless without some sort of Terminal operation, such as `each` or `count`. Terminal operations
do something with the final stream data, be it summing, counting, calling a function, finding the min, and so on.
Additional information can be found in the [documentation](http://twentylemon.github.io/flow/doxy/d9/de2/namespaceflow.html).

Intermediate operations are all inside the [flow::intermediate](http://twentylemon.github.io/flow/doxy/dc/d09/namespaceflow_1_1intermediate.html) namespace.

Terminal operations are all inside the [flow::terminal](http://twentylemon.github.io/flow/doxy/d1/d6c/namespaceflow_1_1terminal.html) namespace.

### A Word on the flow namespace
All of the functions in `flow::generator`, `flow::intermediate` and `flow::terminal` are aliased to also be in the `flow` namespace.
For your program, if you do `using namespace flow;` (if you want), you get access to all the core parts of the flow library.
If not, you can still just write `flow::map` instead of `flow::intermediate::map`.

### Documentation at a Glance
The best way to view all available functions, use the [Namespace Members](http://twentylemon.github.io/flow/doxy/namespacemembers_func.html) page. It lists
every function and the namespace it sits in, indicating whether it is a generator, or an intermediate or terminal operation.

Examples
--------
### Basic Iteration
```C++
my_vector | each([](auto& ele) {
    fancy_things(ele);
    more_fancy_things(ele);
});
```

### Display Streams
```C++
people | map(&Person::name) | dump();       // display names to std::cout
// or, if Person::operator<< exists
people | dump(why_not_into_a_file, "\n");   // with a new line between each one
```

### Basic Statistics
```C++
auto male_age_stats = people
    | filter([](Person& p) { return p.sex() == Person::Sex::Male; })
    | map(&Person::age)
    | stats();  // gets mean, standard deviation; can optionally get min/max, median/mode

// get frequency of each age in the group
auto age_distribution = people | map(&Person::age) | to_map();  // or to_unordered_map()
```

### Infinite Streams
```C++
using boost::multiprecision::cpp_int;
auto nth_fibonacci = iterate(std::plus<cpp_int>(), cpp_int(0), cpp_int(1)) | nth(1000); // some huge number

iota(1) | filter([](int i) { return i % 2 == 0; }); // a stream containing all even values
iota(2, 2); // or, this is the same, start from 2 counting up by 2

random_engine(std::mt19937());  // infinite stream of randomly generated values
random_ints(0, 10);             // random ints in the range [0,10]
generate(std::rand);            // even more randoms!
```

### Assign IDs to Objects
```C++
widgets | zip(iota(1), [](Widget& w, int id) { w.set_id(id); return id; }) | execute();
```

### Sorted Stream Operations
```C++
std::vector<int> x = { 1, 2, 3, 4 };
std::vector<int> y = { 1, 3, 5, 7 };

auto xy_merge = x | merge(y) | to_vector();                 // { 1, 1, 2, 3, 3, 4, 5, 7 }
auto xy_union = x | set_union(y) | to_vector();             // { 1, 2, 3, 4, 5, 7 }
auto xy_intersection = x | set_intersect(y) | to_vector();  // { 1, 3 }
auto xy_difference = x | set_diff(y) | to_vector();         // { 2, 4 }
auto xy_sym_diff = x | set_sym_diff(y) | to_vector();       // { 2, 4, 5, 7 }
```
