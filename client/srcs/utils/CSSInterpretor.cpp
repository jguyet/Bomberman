#include "Bomberman.hpp"

// STATIC ########################################################

void				CSSInterpretor::interpretCSS( Tag *tag, const char *style )
{
	std::string style_pattern = (std::ostringstream() << style).str();
	std::vector<std::string> style_splited = split(style_pattern, ';');

	for (int command_n = 0; command_n < style_splited.size(); command_n++)
	{
		std::string					cmd_line = style_splited.at(command_n);
		std::vector<std::string>	splited_line = split(cmd_line, ':');
		std::string					cmd;
		std::string					value;

		if (splited_line.size() < 2)
			continue ;

		cmd = splited_line.at(0);
		value = splited_line.at(1);

		if (cmd == "float")//float:left
		{
			if (value == "left")
				tag->setFloat(TAG_POSITION_LEFT);
			else if (value == "right")
				tag->setFloat(TAG_POSITION_RIGHT);
			else if (value == "center")
				tag->setFloat(TAG_POSITION_CENTER);
		}
		else if (cmd == "text-align")//text-align:center
		{
			if (value == "left")
				tag->setTextAlign(TAG_POSITION_LEFT);
			else if (value == "right")
				tag->setTextAlign(TAG_POSITION_RIGHT);
			else if (value == "center")
				tag->setTextAlign(TAG_POSITION_CENTER);
		}
		else if (cmd == "background-color")//background-color:#ffffff
		{
			glm::vec3 color;
			ColorUtils::hexaColorToRGB(color, value);
			tag->setBackgroundColor(color);
		}
		else if (cmd == "color")//color:#ffffff
		{
			glm::vec3 color;
			ColorUtils::hexaColorToRGB(color, value);
			tag->setColor(color);
		}
		else if (cmd == "font-size")//font-size:10px
		{
			int size = atoi(value.c_str());
			tag->setFontSize(size);
		}
		else if (cmd == "font-family")//font-family:arial
		{
			tag->setFontFamily(value.c_str());
		}
	}
}

// ###############################################################

// CANONICAL #####################################################

CSSInterpretor::CSSInterpretor ( void )
{
	return ;
}

CSSInterpretor::CSSInterpretor ( CSSInterpretor const & src )
{
	*this = src;
	return ;
}

CSSInterpretor &			CSSInterpretor::operator=( CSSInterpretor const & rhs ) {
	if (this != &rhs) {
		// make stuff
	}
	return (*this);
}

CSSInterpretor::~CSSInterpretor ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, CSSInterpretor const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################
