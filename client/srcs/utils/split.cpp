#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
		if (item != "") {
        	*(result++) = item;
		}
    }
}

void split_string(std::vector<std::string> &result, const std::string &s, std::string const &delim)
{
    std::string ss = std::string(s);
	int start = 0;
    std::string item;

	if (delim.size() > s.size())
	{
		result.push_back(std::string(s));
		return ;
	}
	for (int i = 0; i < ss.size();i++) {
		std::string over = ss.substr(i, delim.size());

		if (over == delim && start != i) {
			item = ss.substr(start, i);
			start = i + delim.size();
			i += delim.size();
			result.push_back(item);
		}
	}
	if (start != 0) {
		item = ss.substr(start);
		result.push_back(item);
	}
}

void split_string(std::vector<std::string> &result, const std::string &s, std::string const &delim, const std::string &without)
{
    std::string ss = std::string(s);
	int start = 0;
    std::string item;
	bool wait = false;

	if (delim.size() > s.size())
	{
		result.push_back(std::string(s));
		return ;
	}
	if (without.size() > s.size())
	{
		result.push_back(std::string(s));
		return ;
	}
	for (int i = 0; i < ss.size();i++) {
		std::string over = ss.substr(i, delim.size());
		std::string over_without = ss.substr(i, without.size());
		if (over_without == without) {
			if (wait == false)
				wait = true;
			else
				wait = false;
		}
		if (wait)
			continue ;
		if (over == delim && start != i) {
			item = ss.substr(start, i);
			start = i + delim.size();
			i += delim.size();
			result.push_back(item);
		}
	}
	if (start != 0) {
		item = ss.substr(start);
		result.push_back(item);
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<std::string> split_string(const std::string &s, const std::string &delim)
{
    std::vector<std::string> elems;
    split_string(elems, s, delim);
    return elems;
}

std::vector<std::string> split_string_without(const std::string &s, const std::string &delim, const std::string &without)
{
    std::vector<std::string> elems;
    split_string(elems, s, delim, without);
    return elems;
}
