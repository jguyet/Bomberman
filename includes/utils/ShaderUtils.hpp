#ifndef SHADERUTILS_HPP
# define SHADERUTILS_HPP

# include "Bomberman.hpp"

class ShaderUtils
{
	public:

		static ShaderUtils						*instance;

		ShaderUtils( void );
		ShaderUtils( ShaderUtils const & src );
		virtual ~ShaderUtils( void );

		ShaderUtils &							operator=( ShaderUtils const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, ShaderUtils const & i);

		void									loadShader(const char *name, const char *vertex_file_path, const char *fragment_file_path);
		unsigned int							get(const char *name);

	private:
		std::map<const char *, unsigned int>	shaders;
};

#endif
