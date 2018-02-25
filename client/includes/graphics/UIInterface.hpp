#ifndef UIINTERFACE_HPP
# define UIINTERFACE_HPP

# include "Bomberman.hpp"

class UIInterface
{
	public:

											UIInterface( std::string const &ui_file );
											UIInterface( UIInterface const & src );
		virtual								~UIInterface( void );

		UIInterface &						operator=( UIInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, UIInterface const & i);

		Tag									*getElementById(const char *id);
	protected:
		std::map<std::string, Tag*>			elements;
		std::map<std::string, std::string>	styles;
	private:
		//lexer methods
		typedef int (UIInterface::*LexerMethods)( std::string const & value );
		typedef void (UIInterface::*LexerTagMethods)( std::string const &tag_name, std::string const &tag_params, std::string const &content );

		int									scoop_enter(std::string const & value);
		void								addElement(std::string const &tag_name, std::string const &tag_params, std::string const &content);
		void								addStyle(std::string const &tag_name, std::string const &tag_params, std::string const &content);
		//end lexer methods

		void								build_lexer( void );
		void								build_parser( std::string const & content );
		void								initialize( std::string const &ui_file );

		std::map<std::string, LexerMethods>	lexer;
		std::map<std::string, LexerTagMethods>	lexer_tag;
		std::string							content;
		std::string 						ui_file;
};

#endif
