
sick flow, bro
==============

Inspired by Java 8 [Streams](http://www.oracle.com/technetwork/articles/java/ma14-java-se-8-streams-2177646.html),
flow is a C++14 library that provides lazy evaluation and functional transformations on data. It's like Haskell for C++.
The library provides many common data transformations, such as map, filter and fold, as well as other commonly used
operations like computing the sum, min and max or simply counting the number or elements. And all of it is packaged
in a nice, easy to read and understand syntax. To use, simply `#include <flow.h>` in your C++14 program.


What is a Sick Flow?
--------------------
A flow is usually called a stream. But if I called the library "Stream" I couldn't say "sick flow" all the time.
I'll use flow and stream interchangeably, just know that a stream is a source of data, data that would want to
do things with.

Creating a Sick Flow
--------------------
The `flow::generator` namespace contains several factory methods for creating a Stream object. Probably the most
common generator used is `from()`, which creates a Stream from an iterator range or a container.

```C++
auto stream = from(my_vector); // a stream over the entire vector in the same order
```

Other common stream generators are `iota()`, which counts up from a value, and `repeat()`, which repeats a value or
cycles a container.

Manipulating a Sick Flow
------------------------
Say you want to loop through a list of numbers. But you only want the even values. Then you want the squares of those
values for some reason. Oh, and you want at most 10 of those. How would you do that in normal C++? Probably something like

```C++
int count = 0;
for (auto it = list.begin(), end = list.end(); it != end & count < 10; ++it) {
    if (*it % 2 == 0) {
        ++count;
        process(*it * *it);
    }
}
```

Not bad, but it's not quickly clear what is going on. The same operation can be done as a sick flow instead:

```C++
list | filter([](int i){ return i % 2 == 0; }) | limit(10) | map([](int i){ return i*i; }) | each(process);
```

Reading the line aloud, it's obvious what is happening. Take the list, keep even values, limit it to 10 elements,
map the elements to their square, and then process each of those. Fun. This is just a trivial example, there many other
stream operations available to be used.
Stream operations are broken down into two main types: Intermediate and Terminal operations. Intermediate operations
transform a stream into another stream. We saw three examples above in `filter`, `limit` and `map`. Intermediate
operations are meaningless without some sort of Terminal operation, such as `each` or `count`. Terminal operations
do something with the final stream data, be it summing, counting, calling a function, finding the min, and so on.

Intermediate operations are all inside the flow::intermediate namespace.

Terminal operations are all inside the flow::terminal namespace.

### A Word on the flow namespace
All of the functions in `flow::generator`, `flow::intermediate` and `flow::terminal` are aliased to also be in the `flow` namespace.
For your program, if you do `using namespace flow;` (if you want), you get access to all the core parts of the flow library.
If not, you can still just write `flow::map` instead of `flow::intermediate::map`.

### Documentation at a Glance
The best way to view all available functions, use the <a href="namespacemembers_func.html">Namespace Members</a> page. It lists
every important function and the namespace it sits in, indicating whether it is a generator, or an intermediate or terminal operation.

