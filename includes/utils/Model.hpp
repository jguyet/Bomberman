#ifndef MODEL_HPP
# define MODEL_HPP

# include "Bomberman.hpp"
# include "graphics/IRenderLoop.hpp"
# include "graphics/RenderLoop.hpp"
# include "graphics/components/Camera.hpp"
# include "client/BombermanClient.hpp"

class Model
{
	public:

		class Face;
		class Material;

		static Model							*loadModel(std::string filename);
		// static Model							*loadTexturedModel(std::string filename);
		static void								parseVertex(Model *model, std::string line);
		static void								parseNormals(Model *model, std::string line);
		static void								parseFace(Model *model, std::string line, Material *currentMaterial);
		static void								parseTextureCoordinates(Model *model, std::string line);
		//static int								createTexturedDisplayList(Model *model);

		Model( void );
		Model( Model const & src );
		virtual ~Model( void );

		Model &									operator=( Model const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, Model const & i);

		// void									enableStates( void );
		bool									hasTextureCoordinates( void );
		bool									hasNormals( void );
		std::vector<glm::vec3>					&getVertices( void );
		std::vector<glm::vec2>					&getTextureCoordinates( void );
		std::vector<glm::vec3>					&getNormals( void );
		std::vector<Model::Face>				&getFaces( void );
		bool									isSmoothShadingEnabled( void );
		void									setSmoothShadingEnabled(bool smoothShadingEnabled);
		std::map<std::string, Model::Material>	&getMaterials( void );

		void									produce( void );
		void									render( const GLfloat *mvp );

	class Material {
		public:
			std::string		toString() {
				std::ostringstream oss;
				oss << "Material{" << "specularCoefficient=" << this->specularCoefficient << ", ambientColour=" << this->ambientColour << ", diffuseColour=" << this->diffuseColour << ", specularColour=" << this->specularColour << "}";
				return (oss.str());
			};

			float			specularCoefficient = 100;
			float			ambientColour[3] = {0.2f, 0.2f, 0.2f};
			float			diffuseColour[3] = {0.3f, 1, 1};
			float			specularColour[3] = {1, 1, 1};
			std::string		texture;
	};

	class Face {
		public:

		Material								*getMaterial() {
			return (this->material);
		};

		bool									hasNormals() {
			return (this->normalIndices[0] != -1);
		};

		bool									hasTextureCoordinates() {
			return (this->textureCoordinateIndices[0] != -1);
		};

		int										*getVertexIndices() {
			return (this->vertexIndices);
		};

		int										*getTextureCoordinatesIndices() {
			return (this->textureCoordinateIndices);
		};

		int										*getNormalIndices() {
			return (this->normalIndices);
		};

		Face(int vertexIndices[3]) {
			this->vertexIndices[0] = vertexIndices[0] - 1;
			this->vertexIndices[1] = vertexIndices[1] - 1;
			this->vertexIndices[2] = vertexIndices[2] - 1;
		}

		Face(int vertexIndices[3], int normalIndices[3]) {
			this->vertexIndices[0] = vertexIndices[0] - 1;
			this->vertexIndices[1] = vertexIndices[1] - 1;
			this->vertexIndices[2] = vertexIndices[2] - 1;
			this->normalIndices[0] = normalIndices[0] - 1;
			this->normalIndices[1] = normalIndices[1] - 1;
			this->normalIndices[2] = normalIndices[2] - 1;
		};

		Face(int vertexIndices[3], int normalIndices[3], int textureCoordinateIndices[3], Material *material) {
			this->vertexIndices[0] = vertexIndices[0] - 1;
			this->vertexIndices[1] = vertexIndices[1] - 1;
			this->vertexIndices[2] = vertexIndices[2] - 1;
			this->normalIndices[0] = normalIndices[0] - 1;
			this->normalIndices[1] = normalIndices[1] - 1;
			this->normalIndices[2] = normalIndices[2] - 1;
			this->textureCoordinateIndices[0] = textureCoordinateIndices[0] - 1;
            this->textureCoordinateIndices[1] = textureCoordinateIndices[1] - 1;
            this->textureCoordinateIndices[2] = textureCoordinateIndices[2] - 1;
			this->material = material;
		};

		void								build(Model *model)
		{
			this->vertex[0] = model->getVertices().at(this->vertexIndices[0]);
			this->vertex[1] = model->getVertices().at(this->vertexIndices[1]);
			this->vertex[2] = model->getVertices().at(this->vertexIndices[2]);

			if (this->hasNormals()) {
				this->normals[0] = model->getNormals().at(this->normalIndices[0]);
				this->normals[1] = model->getNormals().at(this->normalIndices[1]);
				this->normals[2] = model->getNormals().at(this->normalIndices[2]);
			}

			if (this->hasTextureCoordinates()) {
				this->textureCoordinate[0] = model->getTextureCoordinates().at(this->textureCoordinateIndices[0]);
				this->textureCoordinate[1] = model->getTextureCoordinates().at(this->textureCoordinateIndices[1]);
				this->textureCoordinate[2] = model->getTextureCoordinates().at(this->textureCoordinateIndices[2]);
			}
		}

		void								build_vertexs( void )
		{
			glGenBuffers(1, &this->vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec3), &this->vertex[0], GL_STATIC_DRAW);
		}

		void								build_TextureCoordinates( void )
		{
			if (this->hasTextureCoordinates() == false) {
				return ;
			}
			glGenBuffers(1, &this->textureCoordinatesBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, this->textureCoordinatesBuffer);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec2), &this->textureCoordinate[0], GL_STATIC_DRAW);
		}

		void								build_normals( void )
		{
			if (this->hasNormals() == false) {
				return ;
			}
			glGenBuffers(1, &this->normalsBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
		}

		void								produce( void )
		{
			GLuint VertexArrayID;
			glGenVertexArrays(1, &VertexArrayID);
			{
				glBindVertexArray(VertexArrayID);
				this->matrixID = glGetUniformLocation(ShaderUtils::instance->get("simple"), "MVP");
				this->modelmatrixID = glGetUniformLocation(ShaderUtils::instance->get("simple"), "modelMatrix");
				this->viewmatrixID = glGetUniformLocation(ShaderUtils::instance->get("simple"), "viewMatrix");

				this->build_vertexs();
				this->build_TextureCoordinates();
				this->build_normals();

				//TODO materialbuild

				//this->Texture = loadDDS("uvmap_2_.png");

				this->Texture = SOIL_load_OGL_texture
				(
					"uvmap_2_.png",
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
				);

				this->textureID  = glGetUniformLocation(ShaderUtils::instance->get("simple"), "myTextureSampler");
			}
		}

		void								render( void )
		{
			glUseProgram(ShaderUtils::instance->get("simple"));

			glUniformMatrix4fv(this->matrixID, 1, GL_FALSE, &BombermanClient::instance->camera->modelviewprojectionMatrix[0][0]);
			glUniformMatrix4fv(this->modelmatrixID, 1, GL_FALSE, &BombermanClient::instance->camera->modelMatrix[0][0]);
			glUniformMatrix4fv(this->viewmatrixID, 1, GL_FALSE, &BombermanClient::instance->camera->viewMatrix[0][0]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->Texture);
			glUniform1i(this->textureID, 0);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
			glVertexAttribPointer(
				 0,                  // attribute id 0
				 3,                  // vec3
				 GL_FLOAT,           // object type
				 false,              // normalized?
				 0,                  // saut apres lecture du vec3
				 0           		 // offset de depart
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, this->textureCoordinatesBuffer);
			glVertexAttribPointer(
				 1,                  // attribute id 0
				 2,                  // vec3
				 GL_FLOAT,           // object type
				 false,              // normalized?
				 0,                  // saut apres lecture du vec3
				 0           		 // offset de depart
			);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
			glVertexAttribPointer(
				 2,                  // attribute id 0
				 3,                  // vec3
				 GL_FLOAT,           // object type
				 false,              // normalized?
				 0,                  // saut apres lecture du vec3
				 0           		 // offset de depart
			);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glUseProgram(0);
		}

		~Face()
		{
			if (this->material != NULL) {
				delete material;
			}
		}

		glm::vec3							vertex[3];
		glm::vec3							normals[3];
		glm::vec2							textureCoordinate[3];
		Material							*material;

		private:
			int								vertexIndices[3] = {-1, -1, -1};
			int								normalIndices[3] = {-1, -1, -1};
			int								textureCoordinateIndices[3] = {-1, -1, -1};

			GLuint									vertexBuffer;
			GLuint									normalsBuffer;
			GLuint									textureCoordinatesBuffer;

			GLuint									Texture;
			GLuint									textureID;

			GLuint									matrixID;
			GLuint									modelmatrixID;
			GLuint									viewmatrixID;
			GLuint									lightID;

	};



	private:
		GLuint									vertexBuffer;
		GLuint									normalsBuffer;

		GLuint									Texture;
		GLuint									textureID;

		GLuint									matrixID;
		GLuint									modelmatrixID;
		GLuint									viewmatrixID;
		GLuint									lightID;

		std::vector<glm::vec3>					vertices;
		std::vector<glm::vec2>					textureCoordinates;
		std::vector<glm::vec3>					normals;
		std::vector<Model::Face>				faces;
		std::map<std::string, Model::Material>	materials;
		bool									enableSmoothShading;
};

#endif
