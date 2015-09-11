
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
 
#ifndef FLOW_COMPOSE_H
#define FLOW_COMPOSE_H

namespace flow {
    template <typename Source> class Stream;
    namespace terminal {
        namespace detail {
            template <typename F> class Terminal;
        }
    }
    namespace intermediate {
        namespace detail {
            template <typename F> class Intermediate;
        }
    }
}

namespace flow {
    namespace detail {

/// <summary>
/// Composes the two functions F and G. Represents the composition <c>F(G(...))</c>.
/// </summary>
template <typename F, typename G>
class Compose
{
public:
    /// <summary>
    /// Initializes a new instance of the Compose class. Represents the composition <c>F(G(...))</c>.
    /// </summary>
    /// <param name="f">The f function.</param>
    /// <param name="g">The g function.</param>
    Compose(F&& f, G&& g) : _f(std::forward<F>(f)), _g(std::forward<G>(g)) { }

    /// <summary>
    /// Executes the composition of operations on the Stream given.
    /// </summary>
    /// <param name="stream">The stream to operate on.</param>
    /// <returns>The result of the composition of the operations on the stream.</returns>
    template <typename Source>
    std::result_of_t<F(std::result_of_t<G(Stream<Source>&&)>)> operator()(Stream<Source>&& stream) {
        return _f(_g(stream));
    }

protected:
    /// <summary>
    /// The outer operation.
    /// </summary>
    F _f;

    /// <summary>
    /// The inner operation.
    /// </summary>
    G _g;
};
    }
}
#endif
