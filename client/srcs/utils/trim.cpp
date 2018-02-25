#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start (in place)
static void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
std::string		trim(std::string const &s)
{
	std::string tmp = std::string(s);
    ltrim(tmp);
    rtrim(tmp);
	return (tmp);
}
