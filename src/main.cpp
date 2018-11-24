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
#include <codecvt>

#include <typeinfo>

#include "cxxopts.hpp"
#include "keyword.hpp"
#include "filter.hpp"
#include "utility.hpp"

cxxopts::ParseResult parse (int argc, char* argv[])
{
	try
	{
		// setup options
		cxxopts::Options options (argv[0], "trevi-fileter command line options");
		options
			.positional_help ("[optional args]")
			.show_positional_help ();


		options
			.allow_unrecognised_options ()
			.add_options ()
			("h,help", "print help")
			("l,list", "list keywords")
			("c,clear", "clear keywords")
			("a,add", "add keywords", cxxopts::value<std::vector<std::string>> ())
			("p,parse", "parse text", cxxopts::value<std::string>())
			("f,filter", "filter id [0:Std 1:Native, 2:KMP]", cxxopts::value<int>())
			("t,thread", "thread count", cxxopts::value<int>())
			;

		options.parse_positional ({"add", "parse", "filter", "thread"});

		auto result = options.parse (argc, argv);

		// setup default keyword container
		auto keyword = tf::Keyword_File ("keywords.txt");
		tf::KeywordList keywordList;

		// process show help information option
		if (result.count ("help"))
		{
			std::cout << options.help ({"", "Group"}) << std::endl;
			exit (0);
		}

		// process add keywords option
		if (result.count ("add"))
		{
			auto& v = result["add"].as<std::vector<std::string>> ();

			std::cout << "Add Keywords : ";
			tf::utility::print_vector (v);
			keyword.write (v);
		}

		// process show keywords list option
		if (result.count ("list"))
		{
			if (keyword.read (keywordList))
			{
				if (keywordList.size () > 0)
				{
					std::cout << "Keyword list : ";
					tf::utility::print_vector (keywordList);
				}
				else
				{
					std::cout << "No keywords found!" << std::endl;
				}
			}
		}

		// process clear keywords option
		if (result.count ("clear"))
		{
			keyword.clear ();
		}

		// process select filter algorithm option
		int filter_id = 0;
		if (result.count ("filter"))
		{
			filter_id = result["filter"].as<int> ();
		}

		// process thread count option
		int threadCount = 0;
		if (result.count ("thread"))
		{
			threadCount = result["thread"].as<int> ();
		}

		// process parse text option
		if (result.count ("parse"))
		{
			if (keyword.read (keywordList))
			{
				tf::FilterResult filterResult;

				auto& v = result["parse"].as<std::string> ();

				auto t1 = tf::utility::timestamp ();
				switch (filter_id)
				{
					case 1:
						if (threadCount < 1)
							tf::Filter_Native ().parse (keywordList, v, filterResult);
						else
							tf::Filter_Multithreading_Parser<tf::Filter_Native> ().parse (keywordList, v, filterResult, threadCount);
						break;
					case 2:
						if (threadCount < 1)
							tf::Filter_KMP ().parse (keywordList, v, filterResult);
						else
							tf::Filter_Multithreading_Parser<tf::Filter_KMP> ().parse (keywordList, v, filterResult, threadCount);
						break;
					default:
						if (threadCount < 1)
							tf::Filter_Std ().parse (keywordList, v, filterResult);
						else
							tf::Filter_Multithreading_Parser<tf::Filter_Std> ().parse (keywordList, v, filterResult, threadCount);

						break;
				}
				auto t2 = tf::utility::timestamp ();

				if (filterResult.size() > 0)
				{
					for (const auto& pair : filterResult)
					{
						std::cout << "find {" << keywordList[std::get<0>(pair)] << "} at index (" ;

						int index = 0;
						auto indexList = std::get<1> (pair);
						for (const auto& i : indexList)
						{
							if (i > 0)
							{
								auto u8_str = v.substr (0, i - 1);
								index = tf::utility::utf8_string_length (u8_str) + 1;
							}
							std::cout << index;

							if (i != indexList.back())
								std::cout << ", ";
						}

						std::cout << ")" << std::endl;
					}
				}
				else
				{
					std::cout << "No any keywords found in the text!" << std::endl;
				}

				tf::utility::print_past_sec (t1, t2);
			}
		}

		return result;
	}
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what () << std::endl;
		exit (1);
	}
}


int main (int argc, char *argv[])
{
	auto result = parse (argc, argv);
	auto arguments = result.arguments ();
	return 0;
}
