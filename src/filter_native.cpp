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

#include <iostream>
#include "filter.hpp"


/***
  Native algorithm for pattern searching

  * pattern length = m
  * text length = N

  * The best case occurs when the first character of
    the pattern is not present in text at all.
      pattern = "FAA";
      text = "AAACCCBBBDEDE";

    The number of comparisons in best case is O(N).

  * The worst case occurs in following scenarios.
    1) When all characters of the text and pattern are same.
      pattern = "AAA";
      text = "AAAAAAAAAAAAA"
    2) When only the last character is different.
      pattern = "AAB";
      text = "AAAAAAAAAAAAB"

    The number of comparisons in the worst case is O(M*(N-M+1))
*/
void tf::Filter_Native::find (const std::string& pattern, const std::string& text, IndexResult& result) const
{
  result.clear ();

  int M = pattern.length ();
  int N = text.length ();

  // A loop to slide character of pattern one by one
  for (int i=0; i<= N-M; ++i)
  {
    int j;

    // For current index i, check for pattern match
    for (j = 0; j<M; ++j)
    {
      if (text[i+j] != pattern[j])
        break;
    }

    // if pattern[0...M-1] = text[i, i+1, ...i+M-1]
    if (j == M)
      result.push_back (i);
  }
}
