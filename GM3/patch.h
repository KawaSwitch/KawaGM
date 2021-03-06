#pragma once

#include <string>
#include <sstream>

// Windows環境でstd::stringが使えない問題の解決策
// https://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-g-mingw#answer-20861692

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}