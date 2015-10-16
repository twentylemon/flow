
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
 
#ifndef FLOW_SOURCE_GENERATE_H
#define FLOW_SOURCE_GENERATE_H

#include "GeneratorSource.h"

namespace flow {
    namespace source {

/// <summary>
/// Stream source that generates an infinite stream using successive calls to a generating function.
/// </summary>
template <typename Generator>
class Generate : public GeneratorSource<std::result_of_t<Generator()>>
{
public:
    using base = GeneratorSource<std::result_of_t<Generator()>>;
    using value_type = typename base::value_type;

    /// <summary>
    /// Initializes a new instance of the Generate class.
    /// </summary>
    /// <param name="generator">The generator used to create stream elements.</param>
    Generate(Generator generator) : base(), _generator(generator) { }

    Generate(const Generate<Generator>&) = delete;
    Generate(Generate<Generator>&&) = default;

    /// <summary>
    /// Returns the next element from the stream.
    /// </summary>
    /// <returns>The next element in the stream.</returns>
    value_type& next() {
        base::assign_temp_current(_generator());
        return base::next();
    }

    /// <summary>
    /// Ignores the next value from the stream.
    /// </summary>
    void lazy_next() {
        _generator();
    }

private:
    Generator _generator;   // the generator of stream elements
};
    }
}
#endif
