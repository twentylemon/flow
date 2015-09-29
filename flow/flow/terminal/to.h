
/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Taras Mychaskiw
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
#ifndef FLOW_TERMINAL_TO_H
#define FLOW_TERMINAL_TO_H

#include <deque>
#include <vector>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <iterator>

#include "copy.h"

namespace flow {
    namespace terminal {

        namespace detail {
/// <summary>
/// Wrapper for <c>std::hash&lt;T&gt;</c>.
/// </summary>
struct hash {
    template <typename T>
    std::size_t operator()(const T& value) const {
        return std::hash<T>()(value);
    }
};
        }

/// <summary>
/// Copies the stream into a <c>std::vector&lt;T, Alloc&lt;T&gt;&gt;</c> in order.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::vector</c>.</returns>
template <template <typename> class Alloc = std::allocator>
auto to_vector() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::vector<T, Alloc<T>> result;
        result.reserve(stream.estimate_size());
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::deque&lt;T, Alloc&lt;T&gt;&gt;</c> in order.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::deque</c>.</returns>
template <template <typename> class Alloc = std::allocator>
auto to_deque() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::deque<T, Alloc<T>> result;
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::forward_list&lt;T, Alloc&lt;T&gt;&gt;</c> in reverse order.
/// <para>Due to a lack of <c>forward_list::push_back</c>, the list contains the stream elements in reverse order,
/// as they are pushed to the front of the list instead.</para>
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::forward_list</c>.</returns>
template <template <typename> class Alloc = std::allocator>
auto to_forward_list() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::forward_list<T, Alloc<T>> result;
        stream | copy(std::front_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::list&lt;T, Alloc&lt;T&gt;&gt;</c> in order.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::list</c>.</returns>
template <template <typename> class Alloc = std::allocator>
auto to_list() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::list<T, Alloc<T>> result;
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::set&lt;T, Compare, Alloc&lt;T&gt;&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::set</c>.</returns>
template <typename Compare = std::less<void>, template <typename> class Alloc = std::allocator>
auto to_set() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::set<T, Compare, Alloc<T>> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::multiset&lt;T, Compare, Alloc&lt;T&gt;&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::multiset</c>.</returns>
template <typename Compare = std::less<void>, template <typename> class Alloc = std::allocator>
auto to_multiset() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::multiset<T, Compare, Alloc<T>> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_set&lt;T, Hash, UnaryPredicate, Alloc&lt;T&gt;&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_set</c>.</returns>
template <typename Hash = detail::hash, typename UnaryPredicate = std::equal_to<void>, template <typename> class Alloc = std::allocator>
auto to_unordered_set() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_set<T, Hash, UnaryPredicate, Alloc<T>> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_multiset&lt;T, Hash, UnaryPredicate, Alloc&lt;T&gt;&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_multiset</c>.</returns>
template <typename Hash = detail::hash, typename UnaryPredicate = std::equal_to<void>, template <typename> class Alloc = std::allocator>
auto to_unordered_multiset() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_multiset<T, Hash, UnaryPredicate, Alloc<T>> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}
    }
}
#endif
