# include <boost/program_options.hpp>
# include <iostream>

using namespace std;

namespace po = boost::program_options;	// boost: 1.77.0

//class DummyClass {
//public:
	void dummy()
	{
		po::options_description general("General options");
		using strings = ::std::vector<::std::string>;
		general.add_options()
		("help,h", po::value<::std::vector<::std::string>>()
		->multitoken()
		->implicit_value( strings { "","format" }, ""),
		"shows help for topic 'arg'");
	}
//}

static std::string _teeex("hello world!");
