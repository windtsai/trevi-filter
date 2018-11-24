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

#ifndef KEYWORD_HPP_
#define KEYWORD_HPP_

#include <vector>

namespace tf
{
  typedef std::vector<std::string> KeywordList;

  class Keyword
  {
  public:
    virtual bool read (KeywordList& keywordList) const = 0;
    virtual bool write (const KeywordList& keywordList) const = 0;
    virtual void clear () const = 0;
  };

  class Keyword_File : public Keyword
  {
  public:
    Keyword_File (std::string filename) : m_Filename (std::move(filename)) {}

    bool read (KeywordList& keywordList) const;
    bool write (const KeywordList& keywordList) const;
    void clear () const;

  private:
    std::string m_Filename;
  };

  class Keyword_SQL : public Keyword
  {
  public:
    Keyword_SQL (std::string host, std::string port,
                 std::string db, std::string user,
                 std::string pwd)
                 : m_Host (std::move(host)), m_Port (std::move(port)),
                   m_Database (std::move(db)), m_User (std::move(user)),
                   m_Password (std::move(pwd))
                 {}

    bool connect ();

    bool read (KeywordList& keywordList) const;
    bool write (const KeywordList& keywordList) const;
    void clear () const;

  private:
    std::string m_Host;
    std::string m_Port;
    std::string m_Database;
    std::string m_User;
    std::string m_Password;
  };

}

#endif
