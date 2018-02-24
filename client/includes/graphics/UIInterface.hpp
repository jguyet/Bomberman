#ifndef UIINTERFACE_HPP
# define UIINTERFACE_HPP

# include "Bomberman.hpp"

class UIInterface
{
	public:

											UIInterface( const char *ui_file );
											UIInterface( UIInterface const & src );
		virtual								~UIInterface( void );

		UIInterface &						operator=( UIInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, UIInterface const & i);

		Tag									*getElementById(const char *id);
	protected:
		std::map<std::string, Tag*>			elements;
	private:
		void								initialize( const char *ui_file );
};

#endif
