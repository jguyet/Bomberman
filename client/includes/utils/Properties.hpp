#ifndef PROPERTIES_HPP
# define PROPERTIES_HPP

# include "Bomberman.hpp"

class Properties
{
	public:

		Properties( const char *file_path );
		Properties( Properties const & src );
		virtual ~Properties( void );

		Properties &						operator=( Properties const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Properties const & i);

		const char							*get(const char *key);

	private:
		void								initialize(const char *file_path);

		const char							*file_path;
		std::string							content;
		std::map<std::string, std::string>	map;
};

#endif
