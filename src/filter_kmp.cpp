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
  KMP(Knuth Morris Pratt) algorithm for pattern searching
  The time complexity of KMP algorithm is O(N) in the worst case.
*/
void tf::Filter_KMP::find (const std::string& pattern, const std::string& text, IndexResult& result) const
{
  result.clear();

  size_t M = pattern.length ();
  size_t N = text.length ();

  // create LPS that will hold the longest prefix suffix values for pattern
  std::vector<size_t> lps;

  // preprocess the pattern (calculate LPS)
  computeLPS (pattern, M, lps);

  size_t i = 0; // index for text
  size_t j = 0; // index for pattern
  while (i < N)
  {
    if (pattern[j] == text[i])
    {
      ++j;
      ++i;
    }

    if (j == M)
    {
      result.push_back(i-j);
      j = lps[j - 1];
    }
    else if (i < N && pattern[j] != text[i])  // mismatch after j matches
    {
      // Do not match lps[0..lps[j-1]] characters,
      if (j != 0)
        j = lps[j - 1];
      else
        ++i;
    }
  }
}


/***
  Fills lps list for given pattern[0..M-1]
*/
void tf::Filter_KMP::computeLPS (const std::string& pattern, size_t M, std::vector<size_t>& lps) const
{
  // length of the previous longest prefix suffix
  size_t len = 0;

  if (lps.size () != M)
    lps.resize (M);

  // lps[0] is always be 0
  lps[0] = 0;

  // the loop calculates lps[i] for i = 1 to M-1
  size_t i = 1;
  while (i < M)
  {
    if (pattern[i] == pattern[len])
    {
      len++;
      lps[i] = len;
      i++;
    }
    else
    {
      // This is tricky. Consider the example.
      // AAACAAAA and i = 7. The idea is similar
      // to search step.
      if (len != 0)
      {
        len = lps[len -1];

        // Also, note that we do not increment i here
      }
      else
      {
        lps[i] = 0;
        ++i;
      }
    }
  }
}
