
/**
 * \cond LICENSE
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
 * \endcond
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

/// <summary>
/// Copies the stream into a <c>std::vector&lt;T&gt;</c> in order.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::vector</c>.</returns>
inline auto to_vector() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::vector<T> result;
        result.reserve(stream.estimate_size());
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::vector&lt;T, Allocator&gt;</c> in order.
/// </summary>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::vector</c>.</returns>
template <typename Allocator>
auto to_vector(const Allocator& alloc) {
    return detail::make_terminal([alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::vector<T, Allocator> result(alloc);
        result.reserve(stream.estimate_size());
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::deque&lt;T&gt;</c> in order.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::deque</c>.</returns>
inline auto to_deque() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::deque<T> result;
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::deque&lt;T, Allocator&gt;</c> in order.
/// </summary>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::deque</c>.</returns>
template <typename Allocator>
auto to_deque(const Allocator& alloc) {
    return detail::make_terminal([alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::deque<T, Allocator> result(alloc);
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::forward_list&lt;T&gt;</c> in reverse order.
/// <para>Due to a lack of <c>forward_list::push_back</c>, the list contains the stream elements in reverse order,
/// as they are pushed to the front of the list instead.</para>
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::forward_list</c>.</returns>
inline auto to_forward_list() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::forward_list<T> result;
        stream | copy(std::front_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::forward_list&lt;T, Allocator&gt;</c> in reverse order.
/// <para>Due to a lack of <c>forward_list::push_back</c>, the list contains the stream elements in reverse order,
/// as they are pushed to the front of the list instead.</para>
/// </summary>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::forward_list</c>.</returns>
template <typename Allocator>
auto to_forward_list(const Allocator& alloc) {
    return detail::make_terminal([alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::forward_list<T, Allocator> result(alloc);
        stream | copy(std::front_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::list&lt;T&gt;</c> in order.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::list</c>.</returns>
inline auto to_list() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::list<T> result;
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::list&lt;T, Allocator&gt;</c> in order.
/// </summary>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::list</c>.</returns>
template <typename Allocator>
auto to_list(const Allocator& alloc) {
    return detail::make_terminal([alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::list<T, Allocator> result(alloc);
        stream | copy(std::back_inserter(result));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::set&lt;T&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::set</c>.</returns>
inline auto to_set() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::set<T> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::set&lt;T, Compare&gt;</c>.
/// </summary>
/// <param name="compare">The comparator to use in the set.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::set</c>.</returns>
template <typename Compare>
auto to_set(Compare compare) {
    return detail::make_terminal([compare](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::set<T, Compare> result(compare);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::set&lt;T, Compare, Alloc&lt;T&gt;&gt;</c>.
/// </summary>
/// <param name="compare">The comparator to use in the set.</param>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::set</c>.</returns>
template <typename Compare, typename Allocator>
auto to_set(Compare compare, const Allocator& alloc) {
    return detail::make_terminal([compare, alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::set<T, Compare, Allocator> result(compare, alloc);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::multiset&lt;T&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::multiset</c>.</returns>
inline auto to_multiset() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::multiset<T> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::multiset&lt;T, Compare&gt;</c>.
/// </summary>
/// <param name="compare">The comparator to use in the set.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::multiset</c>.</returns>
template <typename Compare>
auto to_multiset(Compare compare) {
    return detail::make_terminal([compare](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::multiset<T, Compare> result(compare);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::multiset&lt;T, Compare, Alloc&lt;T&gt;&gt;</c>.
/// </summary>
/// <param name="compare">The comparator to use in the set.</param>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::multiset</c>.</returns>
template <typename Compare, typename Allocator>
auto to_multiset(Compare compare, const Allocator& alloc) {
    return detail::make_terminal([compare, alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::multiset<T, Compare, Allocator> result(compare, alloc);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_set&lt;T&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_set</c>.</returns>
inline auto to_unordered_set() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_set<T> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_set&lt;T, Hash&gt;</c>.
/// </summary>
/// <param name="hash">The hash function to use.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_set</c>.</returns>
template <typename Hash>
auto to_unordered_set(const Hash& hash) {
    return detail::make_terminal([hash](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_set<T, Hash> result(16, hash);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_set&lt;T, Hash, EqualPredicate&gt;</c>.
/// </summary>
/// <param name="hash">The hash function to use.</param>
/// <param name="equal">The function to use for the equality predicate in the hash table.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_set</c>.</returns>
template <typename Hash, typename EqualPredicate>
auto to_unordered_set(const Hash& hash, EqualPredicate equal) {
    return detail::make_terminal([hash, equal](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_set<T, Hash, EqualPredicate> result(16, hash, equal);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_set&lt;T, Hash, EqualPredicate, Allocator&gt;</c>.
/// </summary>
/// <param name="hash">The hash function to use.</param>
/// <param name="equal">The function to use for the equality predicate in the hash table.</param>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_set</c>.</returns>
template <typename Hash, typename EqualPredicate, typename Allocator>
auto to_unordered_set(const Hash& hash, EqualPredicate equal, const Allocator& alloc) {
    return detail::make_terminal([hash, equal, alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_set<T, Hash, EqualPredicate, Allocator> result(16, hash, equal, alloc);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_multiset&lt;T&gt;</c>.
/// </summary>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_multiset</c>.</returns>
inline auto to_unordered_multiset() {
    return detail::make_terminal([](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_multiset<T> result;
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_multiset&lt;T, Hash&gt;</c>.
/// </summary>
/// <param name="hash">The hash function to use.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_multiset</c>.</returns>
template <typename Hash>
auto to_unordered_multiset(const Hash& hash) {
    return detail::make_terminal([hash](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_multiset<T, Hash> result(16, hash);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_multiset&lt;T, Hash, EqualPredicate&gt;</c>.
/// </summary>
/// <param name="hash">The hash function to use.</param>
/// <param name="equal">The function to use for the equality predicate in the hash table.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_multiset</c>.</returns>
template <typename Hash, typename EqualPredicate>
auto to_unordered_multiset(const Hash& hash, EqualPredicate equal) {
    return detail::make_terminal([hash, equal](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_multiset<T, Hash, EqualPredicate> result(16, hash, equal);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}

/// <summary>
/// Copies the stream into a <c>std::unordered_multiset&lt;T, Hash, EqualPredicate, Allocator&gt;</c>.
/// </summary>
/// <param name="hash">The hash function to use.</param>
/// <param name="equal">The function to use for the equality predicate in the hash table.</param>
/// <param name="alloc">The allocator to use in the returned container.</param>
/// <returns>The detail::Terminal operation which copies the stream into a <c>std::unordered_multiset</c>.</returns>
template <typename Hash, typename EqualPredicate, typename Allocator>
auto to_unordered_multiset(const Hash& hash, EqualPredicate equal, const Allocator& alloc) {
    return detail::make_terminal([hash, equal, alloc](auto&& stream) {
        using T = std::decay_t<decltype(stream.next())>;
        std::unordered_multiset<T, Hash, EqualPredicate, Allocator> result(16, hash, equal, alloc);
        stream | copy(std::inserter(result, result.end()));
        return result;
    });
}
    }
}
#endif
