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

#ifndef FILTER_HPP_
#define FILTER_HPP_

#include <map>
#include <mutex>
#include "keyword.hpp"

namespace tf
{
  typedef std::vector<size_t> IndexResult;
  typedef std::map<size_t, IndexResult> FilterResult;

  // -----------------------------------------------------------
  // Filter interface
  // -----------------------------------------------------------
  class Filter
  {
  public:
    virtual ~Filter(){}
    virtual void parse (const KeywordList& keywordList, const std::string& text, FilterResult& result, const size_t threadCount = 0) const = 0;
    virtual void operator() (const size_t thread_id, const KeywordList& keywordList, const std::string& text, FilterResult& result) const = 0;

  protected:
    virtual void find (const std::string& pattern, const std::string& text, IndexResult& result) const = 0;

  protected:
    std::string m_AlgorithmName;
  };

  // -----------------------------------------------------------
  // Filter implementation using std::string::find()
  // -----------------------------------------------------------
  class Filter_Std : public Filter
  {
  public:
    Filter_Std() { m_AlgorithmName = "Std-String"; }
    virtual void parse (const KeywordList& keywordList, const std::string& text, FilterResult& result, const size_t threadCount = 0) const;
    virtual void operator() (const size_t thread_id, const KeywordList& keywordList, const std::string& text, FilterResult& result) const;

  protected:
    virtual void find (const std::string& pattern, const std::string& text, IndexResult& result) const;
  };

  // -----------------------------------------------------------
  // Filter implementation using native algorithm
  // -----------------------------------------------------------
  class Filter_Native : public Filter_Std
  {
  public:
    Filter_Native() { m_AlgorithmName = "Native"; }

  protected:
    virtual void find (const std::string& pattern, const std::string& text, IndexResult& result) const;
  };

  // -----------------------------------------------------------
  // Filter implementation using
  // -----------------------------------------------------------
  class Filter_KMP : public Filter_Std
  {
  public:
    Filter_KMP() { m_AlgorithmName = "KMP"; }

  protected:
    virtual void find (const std::string& pattern, const std::string& text, IndexResult& result) const;
    virtual void computeLPS (const std::string& pattern, size_t M, std::vector<size_t>& lps) const;
  };

  // -----------------------------------------------------------
  // Multithreading Parser
  // -----------------------------------------------------------
  template <class T>
  class Filter_Multithreading_Parser
  {
  public:
    virtual void parse (const KeywordList& keywordList, const std::string& text, FilterResult& result, const size_t threadCount) const;
  };
}


#endif
