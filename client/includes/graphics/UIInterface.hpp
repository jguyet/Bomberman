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
		std::map<std::string, std::string>	variables;
		std::vector<std::string>			conditions;
		std::map<std::string, std::map<std::string, std::string>> elements_params;

		void								build(void);
		int									last_modified_date = 0;
		bool								debug_mode = false;
		bool								modified = false;
	private:
		//lexer methods
		typedef int (UIInterface::*LexerMethods)( std::string const & value );
		typedef void (UIInterface::*LexerTagMethods)( std::string const &tag_name, std::string const &tag_params, std::string const &content );
		typedef bool (UIInterface::*LexerConditionMethods)( std::string const &first, std::string const &second );

		int									scoop_enter(std::string const & value);
		void								addElement(std::string const &tag_name, std::string const &tag_params, std::string const &content);
		void								addStyle(std::string const &tag_name, std::string const &tag_params, std::string const &content);
		void								addCondition(std::string const &tag_name, std::string const &tag_params, std::string const &content);
		void								buildCondition(std::string const &tag_name, std::string const &tag_params, std::string const &content);

		bool								equals(std::string const &first, std::string const &second);
		bool								superior(std::string const &first, std::string const &second);
		bool								inferior(std::string const &first, std::string const &second);
		bool								notequals(std::string const &first, std::string const &second);
		//end lexer methods

		void								build_lexer( void );
		void								build_parser( std::string const & content );
		bool								initialize( std::string const &ui_file );

		void								clearElements(void);

		std::map<std::string, LexerMethods>				lexer;
		std::map<std::string, LexerTagMethods>			lexer_tag;
		std::map<std::string, LexerConditionMethods>	lexer_condition;
		std::string							content;
		std::string 						ui_file;
};

#endif
