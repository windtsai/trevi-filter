/*

Copyright (c) 2018 Wind Tsai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <iostream>
#include <string>
#include <chrono>

namespace tf::utility
{
  inline size_t utf8_string_length (std::string& str)
  {
  	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
  	return conv.from_bytes(std::move(str)).size();
  }

  inline std::chrono::steady_clock::time_point timestamp ()
  {
    return std::chrono::steady_clock::now();
  }

  inline void print_past_sec (std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end)
  {
    std::chrono::duration<double> sec = end - start;
    std::cout << "\nTotal using " << sec.count() << " sec." << std::endl;
  }

  template <typename T>
  inline void print_vector (const std::vector<T>& v)
  {
    auto len = v.size() - 1;

		std::cout << "{";

		for (size_t i=0; i<len; ++i)
			std::cout << v[i] << ",";

		std::cout << v.back () << "}" << std::endl;
  }
}


#endif
