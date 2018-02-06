#ifndef MODEL_HPP
# define MODEL_HPP

# include "Bomberman.hpp"
# include "graphics/IRenderLoop.hpp"
# include "graphics/RenderLoop.hpp"
# include "graphics/components/Camera.hpp"
# include "client/BombermanClient.hpp"

struct MyMesh{

	GLuint vao;
	GLuint texIndex;
	GLuint uniformBlockIndex;
	int numFaces;
};

struct MyMaterial{

	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
};

class Model
{
	public:
		static Model							*load( const std::string& pFile );
		static void								loadGLTextures(Model *model);
		static void								genVAOsAndUniformBuffer(Model *model);


		Model( void );
		Model( Model const & src );
		virtual ~Model( void );

		Model &									operator=( Model const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, Model const & i);

		void									draw( const GLfloat *mvp );
		void									buildShader( void );
		void 									recursive_render(const aiNode* nd);

		Assimp::Importer 						importer;
		const aiScene							*scene;

		GLuint									vertexLoc = 0;
		GLuint									normalLoc = 1;
		GLuint									texCoordLoc = 2;

		GLuint									materialUniLoc = 0;

		GLuint									projectionMatrixLoc;
		GLuint									viewMatrixLoc;
		GLuint									modelMatrixLoc;
		GLuint									transformMatrixLoc;

		GLuint									texUnit;

		std::map<std::string, GLuint>			textureIdMap;
		std::vector<struct MyMesh>				myMeshes;
};

#endif
