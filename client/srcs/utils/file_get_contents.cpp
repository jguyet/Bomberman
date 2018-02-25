#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>

void						file_get_contents(std::string &content, const char *file_path)
{
	std::ifstream ifs(file_path);

	if (!ifs)
		return ;
	content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}
