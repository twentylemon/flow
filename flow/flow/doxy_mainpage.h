
/**
 * \mainpage
 * Sick Flow, Bro
 * ==============
 * <para>
 * Inspired by Java 8 [Streams](http://www.oracle.com/technetwork/articles/java/ma14-java-se-8-streams-2177646.html),
 * flow is a C++14 library that provides lazy evaluation and functional transformations on data. It's like Haskell for C++.
 * The library provides many common data transformations, such as map, filter and fold, as well as other commonly used
 * operations like computing the sum, min and max or simply counting the number or elements. And all of it is packaged
 * in a nice, easy to read and understand syntax. To use, simply <c>\#include &lt;flow.h&gt;</c> in your C++14 program.
 * </para>
 * 
 * What is a Sick Flow?
 * --------------------
 * <para>A flow is usually called a stream. But if I called the library "Stream" I couldn't say "sick flow" all the time.
 * I'll use flow and stream interchangeably, just know that a stream is a source of data, data that you would want to
 * do things with.</para>
 * 
 * Creating a Sick Flow
 * --------------------
 * <para>The flow::generator namespace contains several factory methods for creating a Stream object. Probably the most
 * common generator used is from(), which creates a Stream from an iterator range or a container.</para>
 * <code>auto stream = from(my_vector); // a stream over the entire vector in the same order</code>
 * <para>Other common stream generators are iota(), which counts up from a value, and repeat(), which repeats a value or
 * cycles a container.</para>
 *
 * Manipulating a Sick Flow
 * ------------------------
 * <para>Say you want to loop through a list of numbers. But you only want the even values. Then you want the squares of those
 * values for some reason. Oh, and you want at most 10 of those. How would you do that in normal C++? Probably something like</para>
 * \code{.cpp}int count = 0;
 * for (auto it = list.begin(), end = list.end(); it != end & count < 10; ++it) {
 *     if (*it % 2 == 0) {
 *         ++count;
 *         process(*it * *it);
 *     }
 * }\endcode
 * <para>Not bad, but it's not quickly clear what is going on. The same operation can be done as a sick flow instead:</para>
 * \code{.cpp}list | filter([](int i){ return i % 2 == 0; }) | limit(10) | map([](int i){ return i*i; }) | each(process);\endcode
 * <para>Reading the line aloud, it's obvious what is happening. Take the list, keep even values, limit it to 10 elements,
 * map the elements to their square, and then process each of those. Fun. This is just a trivial example, there many other
 * stream operations available to be used.</para>
 * <para>Stream operations are broken down into two main types: Intermediate and Terminal operations. Intermediate operations
 * transform a stream into another stream. We saw three examples above in <c>filter</c>, <c>limit</c> and <c>map</c>. Intermediate
 * operations are meaningless without some sort of Terminal operation, such as <c>each</c> or <c>count</c>. Terminal operations
 * do something with the final stream data, be it summing, counting, calling a function, finding the min, and so on.</para>
 * <para>Intermediate operations are all inside the flow::intermediate namespace.<br/>Terminal operations are all inside the
 * flow::terminal namespace.</para>
 * ### A Word on the flow namespace
 * <para>All of the functions in flow::generator, flow::intermediate and flow::terminal are aliased to also be in the flow namespace.
 * For your program, if you do <c>using namespace flow;</c> (if you want), you get access to all the core parts of the flow library.
 * If not, you can still just write <c>flow::map</c> instead of <c>flow::intermediate::map</c>.</para>
 * ### Documentation at a Glance
 * <para>The best way to view all available functions, use the <a href="namespacemembers_func.html">Namespace Members</a> page. It lists
 * every important function and the namespace it sits in, indicating whether it is a generator, or an intermediate or terminal operation.</para>
 */