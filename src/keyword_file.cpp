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
#include <fstream>

#include "keyword.hpp"

bool tf::Keyword_File::read (tf::KeywordList& keywordList) const
{
  std::ifstream ifstream;
  ifstream.open (m_Filename, std::ifstream::in);
  if (!ifstream)
  {
    std::cout << "Read keywords from \"" << m_Filename << "\" failed!" << std::endl;
    return false;
  }

  std::string str;
  while (std::getline (ifstream, str))
  {
    if (str.size () > 0)
    {
      keywordList.push_back (str.substr(1, str.size () - 2));
    }
  }

  ifstream.close ();

  std::cout << "Read " << keywordList.size() << " keywords from \"" << m_Filename << "\" done! " << std::endl;

  return true;
}


bool tf::Keyword_File::write (const tf::KeywordList& keywordList) const
{
  std::ofstream ofstream;
  ofstream.open (m_Filename, std::ofstream::out | std::ofstream::app);
  if (!ofstream)
  {
    std::cout << "Write keywords to \"" << m_Filename << "\" failed!" << std::endl;
    return false;
  }

  for (const auto& keyword: keywordList)
    ofstream << "\'"<< keyword << "\'" << std::endl;

  ofstream.close();

  std::cout << "Write keywords to \"" << m_Filename << "\" done!" << std::endl;

  return true;
}


void tf::Keyword_File::clear () const
{
  std::ofstream ofstream;
  ofstream.open (m_Filename, std::ofstream::out);
  ofstream.close();

  std::cout << "All keywords in the \"" << m_Filename << "\" cleared!" << std::endl;
}
