#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

void						file_get_contents(std::string &content, std::string const &file_path)
{
	std::ifstream ifs(file_path.c_str());

	if (!ifs)
		return ;
	content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}
