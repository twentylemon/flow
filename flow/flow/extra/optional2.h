
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
 
#ifndef FLOW_EXRRA_OPTIONAL_H
#define FLOW_EXRRA_OPTIONAL_H

#include <type_traits>

namespace flow {
    namespace extra {

template <typename T>
class optional;

namespace detail {
    template <typename T>
    union optional_storage
    {
    public:
        constexpr optional_storage() noexcept : _dummy() { }

        template <typename... Args>
        constexpr optional_storage(Args&&... args) : _value(std::forward<Args>(args)...) { }

        ~optional_storage() { }

        unsigned char _dummy;
        T _value;
    };

    template <typename T>
    union optional_storage_constexpr
    {
    public:
        constexpr optional_storage_constexpr() noexcept : _dummy() { }

        template <typename... Args>
        constexpr optional_storage_constexpr(Args&&... args) : _value(std::forward<Args>(args)...) { }

        ~optional_storage_constexpr() = default;

        unsigned char _dummy;
        T _value;
    };

    template <typename T>
    class optional_parent
    {
    public:
        constexpr optional_parent() noexcept : _engaged(false), _storage() { }

        constexpr optional_parent(const T& value) : _engaged(true), _storage(value) { }

        constexpr optional_parent(T&& value) : _engaged(true), _storage(std::move(value)) { }

        ~optional_parent() {
            if (_engaged) {
                _storage._value.~T();
            }
        }

    protected:
        bool _engaged;
        optional_storage<T> _storage;
    };

    template <typename T>
    class optional_parent_constexpr
    {
    public:
        constexpr optional_parent_constexpr() noexcept : _engaged(false), _storage() { }

        constexpr optional_parent_constexpr(const T& value) : _engaged(true), _storage(value) { }

        constexpr optional_parent_constexpr(T&& value) : _engaged(true), _storage(std::move(value)) { }

        ~optional_parent_constexpr() = default;

    protected:
        bool _engaged;
        optional_storage_constexpr<T> _storage;
    };

    template <typename T>
    using optional_base = std::conditional_t<std::is_trivially_destructible<T>::value, optional_parent_constexpr<T>, optional_parent<T>>;
}

template <typename T>
class optional : detail::optional_base<T>
{
    using base = detail::optional_base<T>;
public:
    constexpr optional() noexcept : base() { }

    optional(const optional<T>& rhs) : base() {
        if (rhs) {
            create(*rhs);
        }
    }

    optional(optional<T>&& rhs) : base() {
        if (rhs) {
            create(std::move(*rhs));
        }
    }

    constexpr optional(const T& value) : base(value) { }

    constexpr optional(T&& value) : base(std::move(value)) { }

    ~optional() = default;

    constexpr operator bool() const noexcept {
        return base::_engaged;
    }

    T* operator->() {
        return std::addressof(base::_storage._value);
    }

    constexpr const T* operator->() const {
        return &base::_storage._value;
    }

    T& operator*() {
        return base::_storage._value;
    }

    constexpr const T& operator*() const {
        return base::_storage._value;
    }

    T& value() {
        if (*this) {
            return **this;
        }
        throw std::logic_error("bad optional access");
    }

    constexpr const T& value() const {
        if (*this) {
            return **this;
        }
        throw std::logic_error("bad optional access");
    }

    template <typename U>
    constexpr T value_or(U&& default_value) const {
        return *this ? **this : static_cast<T>(std::forward<U>(default_value));
    }

    optional<T>& operator=(const optional<T>& rhs) {
        if (*this) {
            if (rhs) {
                create(*rhs);
            }
            else {
                destroy();
            }
        }
        else if (rhs) {
            **this = *rhs;
        }
        return *this;
    }

    optional<T>& operator=(optional<T>&& rhs) {
        if (*this) {
            if (rhs) {
                create(std::move(*rhs));
            }
            else {
                destroy();
            }
        }
        else if (rhs) {
            **this = std::move(*rhs);
        }
        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>::value>>
    optional<T>& operator=(U&& value) {
        if (*this) {
            //**this = std::forward<U>(value);
            destroy();
            create(std::forward<U>(value));
        }
        else {
            create(std::forward<U>(value));
        }
        return *this;
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        if (*this) {
            destroy();
        }
        create(std::forward<Args>(args)...);
    }

private:
    template <typename... Args>
    void create(Args&&... args) noexcept(noexcept(T(std::forward<Args>(args)...))) {
        new(operator->()) T(std::forward<Args>(args)...);
        base::_engaged = true;
    }

    void destroy() noexcept {
        (**this).~T();
        base::_engaged = false;
    }
};

template <typename T>
class optional<T&>
{
public:
    constexpr optional() noexcept : _value(nullptr) { }

    constexpr optional(T& value) noexcept : _value(&value) { }

    constexpr optional(const optional<T&>& rhs) noexcept : _value(rhs.value) { }
    constexpr optional(optional<T&>&& rhs) noexcept : _value(rhs.value) { }

    ~optional() = default;

    optional<T&>& operator=(const optional<T&>&) = delete;
    optional<T&>& operator=(optional<T&>&&) = delete;

    optional<T&>& operator=(T& value) noexcept {
        _value = &value;
        return *this;
    }

    constexpr operator bool() const noexcept {
        return _value != nullptr;
    }

    T* operator->() {
        return _value;
    }

    constexpr const T* operator->() const {
        return _value;
    }

    T& operator*() {
        return *_value;
    }

    constexpr const T& operator*() const {
        return *_value;
    }

    T& value() {
        if (*this) {
            return **this;
        }
        throw std::logic_error("bad optional access");
    }

    constexpr const T& value() const {
        if (*this) {
            return **this;
        }
        throw std::logic_error("bad optional access");
    }

    template <typename U>
    constexpr std::decay_t<T> value_or(U&& default_value) const {
        return *this ? **this : std::forward<U>(default_value);
    }

private:
    T* _value;  // pointer to the referenced value
};
    }
}
#endif
