#ifndef PROPERTIES_HPP
# define PROPERTIES_HPP

# include "Bomberman.hpp"

class Properties
{
	public:

		Properties( std::string const &file_path );
		Properties( Properties const & src );
		virtual ~Properties( void );

		Properties &						operator=( Properties const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Properties const & i);

		std::string							get(std::string const &key);
		int									getInt(std::string const &key);
		bool								getBool(std::string const &key);

	private:
		void								initialize(std::string const &file_path);

		std::string							file_path;
		std::string							content;
		std::map<std::string, std::string>	map;
};

#endif
