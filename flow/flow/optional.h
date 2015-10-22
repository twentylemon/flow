
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

#ifndef FLOW_OPTIONAL_H
#define FLOW_OPTIONAL_H

namespace flow {

/// <summary>
/// Manages an optionally contained value, one that may or may not be present.
/// <para>This class functions as a stripped down version of the soon to exist <c>std::optional</c>. Once
/// <c>std::optional</c> is released and implemented by major compilers, this class will be aliased to be <c>std::optional</c>
/// instead, and it will serve as a drop in replacement assuming the standard does not change.</para>
/// </summary>
template <typename T>
class optional
{
public:
    /// <summary>
    /// Initializes a new instance of the optional class which contains no value.
    /// </summary>
    optional() : _storage(), _engaged(false) { }

    /// <summary>
    /// Initializes a new instance of the optional class containing a copy of <paramref name="value"/>.
    /// </summary>
    /// <param name="value">The value to set.</param>
    optional(const T& value) : _storage(), _engaged(false)
    {
        assign(value);
    }

    /// <summary>
    /// Initializes a new instance of the optional class containing <paramref name="value"/>.
    /// </summary>
    /// <param name="value">The value to move into the contained value.</param>
    optional(T&& value) : _storage(), _engaged(false)
    {
        assign(std::move(value));
    }

    optional(const optional<T>& rhs) = default;
    optional(optional<T>&& rhs) = default;

    /// <summary>
    /// Finalizes an instance of the optional class.
    /// </summary>
    ~optional() {
        if (*this) {
            //reinterpret_cast<T&>(_storage).~T();
        }
    }

    /// <summary>
    /// Assigns the contained value to be <paramref name="value"/>.
    /// </summary>
    /// <param name="value">The value to set.</param>
    /// <returns><c>*this</c></returns>
    template <typename U, typename = std::enable_if_t<std::is_convertible<U, T>::value>>
    optional<T>& operator=(U&& value) {
        assign(std::forward<U>(value));
        return *this;
    }

    /// <summary>
    /// Returns <c>true</c> if this object contains a value.
    /// </summary>
    /// <returns><c>true</c> if this object contains a value.</returns>
    operator bool() const {
        return _engaged;
    }

    /// <summary>
    /// Returns a pointer to the contained value, undefined if no there is no contained value.
    /// </summary>
    /// <returns>A pointer to the contained value.</returns>
    T* operator->() {
        return &reinterpret_cast<T&>(_storage);
    }

    /// <summary>
    /// Returns a pointer to the contained value, undefined if there is no contained value.
    /// </summary>
    /// <returns>A pointer to the contained value.</returns>
    const T* operator->() const {
        return &reinterpret_cast<const T&>(_storage);
    }

    /// <summary>
    /// Returns a reference to the contained value, undefined if there is no contained value.
    /// </summary>
    /// <returns>A reference to the contained value.</returns>
    T& operator*() {
        return reinterpret_cast<T&>(_storage);
    }

    /// <summary>
    /// Returns a reference to the contained value, undefined if there is no contained value.
    /// </summary>
    /// <returns>A reference to the contained value.</returns>
   const T& operator*() const {
       return reinterpret_cast<const T&>(_storage);
    }

   /// <summary>
   /// Returns a reference to the contained value.
   /// </summary>
   /// <returns>A reference to the contained value.</returns>
    /// <exception cref="std::logic_error">Thrown when there is no contained value.</exception>
   T& value() {
       if (*this) {
           return **this;
       }
       throw std::logic_error("bad optional access");
   }

   /// <summary>
   /// Returns a reference to the contained value.
   /// </summary>
   /// <returns>A reference to the contained value.</returns>
   /// <exception cref="std::logic_error">Thrown when there is no contained value.</exception>
   const T& value() const {
       if (*this) {
           return **this;
       }
       throw std::logic_error("bad optional access");
   }

   /// <summary>
   /// Returns a copy of the contained value if it exists, otherwise returns <paramref name="default_value"/>.
   /// </summary>
   /// <param name="default_value">The value to return if there is no contained value.</param>
   /// <returns>A copy of the contained value if it exists, <paramref name="default_value"/> otherwise.</returns>
   template <typename U>
   T value_or(U&& default_value) const {
       if (*this) {
           return **this;
       }
       return std::forward<U>(default_value);
   }

private:
    /// <summary>
    /// Allocates and assigns the value in this option -- this should only be called once.
    /// </summary>
    /// <param name="value">The value to set.</param>
    template <typename U>
    void assign(U&& value) {
        if (*this) {
            reinterpret_cast<T&>(_storage).~T();
        }
        new(&_storage) T(std::forward<U>(value));
        _engaged = true;
    }

    std::aligned_storage_t<sizeof(T), alignof(T)> _storage; // storage for the value
    bool _engaged;                                          // if the storage contains a real value
};

/// <summary>
/// Manages an optionally contained reference, one that may or may not be present.
/// <para>This class functions as a stripped down version of the soon to exist <c>std::optional</c>. Once
/// <c>std::optional</c> is released and implemented by major compilers, this class will be aliased to be <c>std::optional</c>
/// instead, and it will serve as a drop in replacement assuming the standard does not change.</para>
/// </summary>
template <typename T>
class optional<T&>
{
public:
    /// <summary>
    /// Initializes a new instance of the optional class which contains no value.
    /// </summary>
    optional() : _value(nullptr) { }

    /// <summary>
    /// Initializes a new instance of the optional class containing <paramref name="value"/>.
    /// </summary>
    /// <param name="value">The value to move into the contained value.</param>
    optional(T& value) : _value(&value) { }

    optional(const optional<T&>&) = default;
    optional(optional<T&>&&) = default;

    /// <summary>
    /// Assigns the contained value to be <paramref name="value"/>.
    /// </summary>
    /// <param name="value">The value to set.</param>
    /// <returns><c>*this</c></returns>
    optional<T&>& operator=(T& value) {
        _value = &value;
        return *this;
    }

    /// <summary>
    /// Returns <c>true</c> if this object contains a value.
    /// </summary>
    /// <returns><c>true</c> if this object contains a value.</returns>
    operator bool() const {
        return _value != nullptr;
    }

    /// <summary>
    /// Returns a pointer to the contained value, undefined if no there is no contained value.
    /// </summary>
    /// <returns>A pointer to the contained value.</returns>
    T* operator->() {
        return _value;
    }

    /// <summary>
    /// Returns a pointer to the contained value, undefined if there is no contained value.
    /// </summary>
    /// <returns>A pointer to the contained value.</returns>
    const T* operator->() const {
        return _value;
    }

    /// <summary>
    /// Returns a reference to the contained value, undefined if there is no contained value.
    /// </summary>
    /// <returns>A reference to the contained value.</returns>
    T& operator*() {
        return *_value;
    }

    /// <summary>
    /// Returns a reference to the contained value, undefined if there is no contained value.
    /// </summary>
    /// <returns>A reference to the contained value.</returns>
    const T& operator*() const {
        return *_value;
    }

    /// <summary>
    /// Returns a reference to the contained value.
    /// </summary>
    /// <returns>A reference to the contained value.</returns>
    /// <exception cref="std::logic_error">Thrown when there is no contained value.</exception>
    T& value() {
        if (*this) {
            return **this;
        }
        throw std::logic_error("bad optional access");
    }

    /// <summary>
    /// Returns a reference to the contained value.
    /// </summary>
    /// <returns>A reference to the contained value.</returns>
    /// <exception cref="std::logic_error">Thrown when there is no contained value.</exception>
    const T& value() const {
        if (*this) {
            return **this;
        }
        throw std::logic_error("bad optional access");
    }

    /// <summary>
    /// Returns a copy of the contained value if it exists, otherwise returns <paramref name="default_value"/>.
    /// </summary>
    /// <param name="default_value">The value to return if there is no contained value.</param>
    /// <returns>A copy of the contained value if it exists, <paramref name="default_value"/> otherwise.</returns>
    template <typename U>
    T value_or(U&& default_value) const {
        if (*this) {
            return **this;
        }
        return std::forward<U>(default_value);
    }

private:
    T* _value;  // pointer to the referenced value
};
}
#endif
