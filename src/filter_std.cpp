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
#include <string>
#include "filter.hpp"

/***
  Parse function loop throuth all element of keywordList

*/
void tf::Filter_Std::parse (const KeywordList& keywordList, const std::string& text, FilterResult& result, const size_t threadCount) const
{
  std::cout << "Using " << m_AlgorithmName << " algorithm" << std::endl;

  if (threadCount == 0){}

  // A loop through keyword list
  for (size_t i=0; i<keywordList.size(); ++i)
  {
    IndexResult indexList;
    find (keywordList[i], text, indexList);
    if (indexList.size() > 0)
      result.insert (std::pair<size_t, IndexResult>(i, indexList));
  }
}
/***
  Override function call operator ()

*/
void tf::Filter_Std::operator() (const size_t thread_id, const KeywordList& keywordList, const std::string& text, FilterResult& result) const
{
  std::cout << "Thread " << thread_id << " started : ";
  parse (keywordList, text, result);
}


/***
  std::string::find() for pattern searching

*/
void tf::Filter_Std::find (const std::string& pattern, const std::string& text, IndexResult& result) const
{
  result.clear ();

  size_t pattern_len = pattern.size ();
  size_t start_index = 0;
  size_t end_index = text.size () - pattern_len;

  while (start_index <= end_index)
  {
    size_t found = text.find (pattern, start_index);
    if (found != std::string::npos)
    {
      result.push_back (found);
      start_index = found + pattern_len;
    }
    else
    {
      break;
    }
  }
}
