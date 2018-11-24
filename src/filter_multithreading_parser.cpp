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
#include <thread>
#include <algorithm>
#include "filter.hpp"

/***
  Multithread Parser
  Space complexity is in direct ratio to thread count

  <T> : type of tf::Filter and its derived class with a pattern searching algorithm
*/
template <class T>
void tf::Filter_Multithreading_Parser<T>::parse (const KeywordList& keywordList, const std::string& text, FilterResult& result, const size_t threadCount) const
{
  std::cout << "Using multithreading parser, thread count = " << threadCount << std::endl;

  if (keywordList.size () < threadCount)
  {
    std::cout << "ERROR: too many threads required!" << std::endl;
    return;
  }

  size_t count = std::max(threadCount, size_t(1));
  size_t len = keywordList.size () / count;

  std::vector<T> filterGroup;
  std::vector<KeywordList> keywordListGroup;
  std::vector<FilterResult> resultGroup;
  std::vector<std::thread> threadGroup;

  filterGroup.resize (count);
  keywordListGroup.resize (count);
  resultGroup.resize (count);

  size_t i=0;
  auto pos = keywordList.begin ();
  for (i=0; i<count-1; ++i)
  {
    keywordListGroup[i].assign (pos, pos+len);
    pos += len;

    threadGroup.push_back (std::thread (std::ref(filterGroup[i]), i+1, std::ref(keywordListGroup[i]), text, std::ref(resultGroup[i])));
    threadGroup.back ().join ();
  }
  keywordListGroup[i].assign (pos, keywordList.end ());
  threadGroup.push_back (std::thread (std::ref(filterGroup[i]), i+1, std::ref(keywordListGroup[i]), text, std::ref(resultGroup[i])));
  threadGroup.back ().join ();

  // Merge all result
  size_t r_len = len;
  result = resultGroup[0];
  for (i=1; i<resultGroup.size (); ++i)
  {
    for (const auto& v : resultGroup[i])
      result.insert (std::pair<size_t, IndexResult>(std::get<0>(v)+r_len, std::get<1>(v)));
    r_len += len;
  }
}

/***
  Explicitly instantiating all the relevant templates we used.
*/
template class tf::Filter_Multithreading_Parser<tf::Filter_Std>;
template class tf::Filter_Multithreading_Parser<tf::Filter_Native>;
template class tf::Filter_Multithreading_Parser<tf::Filter_KMP>;
