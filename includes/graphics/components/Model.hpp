#ifndef MODEL_HPP
# define MODEL_HPP

# include "Bomberman.hpp"

struct MyMesh {

	GLuint vao;
	GLuint texIndex;
	GLuint uniformBlockIndex;
	int numFaces;
};

struct MyMaterial {

	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
};

class Model : public Component
{
	public:
		// STATICS #############################################################
		static bool									load(const std::string& key, unsigned int shader, const std::string& pFile);
		static void									loadGLTextures(std::string &absolutePath, Model *model);
		static void									genVAOsAndUniformBuffer(Model *model);
		static void									buildShader(Model *model);
		static void									deleteModels(void);

		static std::map<const std::string, Model*>	model;
		// #####################################################################
		// CANONICAL ###########################################################
													Model( unsigned int shader );
													Model( Model const & src );
		virtual										~Model( void );
		Model &										operator=( Model const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, Model const & i);
		// #####################################################################
		// @OVERRIDE Component ################################################
		// ####################################################################
		// PUBLIC ##############################################################
		void										draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix);

		Assimp::Importer 							importer;
		const aiScene								*scene;
		GLuint										vertexLoc;
		GLuint										normalLoc;
		GLuint										texCoordLoc;
		GLuint										materialUniLoc = 0;
		GLuint										projectionMatrixLoc;
		GLuint										viewMatrixLoc;
		GLuint										modelMatrixLoc;
		GLuint										transformMatrixLoc;
		GLuint										texUnit;
		std::map<std::string, GLuint>				textureIdMap;
		std::vector<struct MyMesh>					myMeshes;
		std::vector<unsigned int> 					indices;
		unsigned int								shader;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		void 										recursive_render(const aiNode* nd);
		// #####################################################################
};

#endif
