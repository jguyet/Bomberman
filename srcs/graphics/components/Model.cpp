#include "Bomberman.hpp"

// STATIC ########################################################

std::map<const std::string, Model*>		Model::model = std::map<const std::string, Model*>();

inline void 			set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

inline void 			color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

bool					Model::load(const std::string& key, unsigned int shader, const std::string& pFile)
{
    std::ifstream fin(pFile.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{
        printf("Couldn't open file: %s\n", pFile.c_str());
		return false;
    }

	Model *model = new Model(shader);

    model->scene = model->importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

    // If the import failed, report it
    if( !model->scene)
    {
        printf("%s\n", model->importer.GetErrorString());
		delete model;
		return false;
    }

    // Now we can access the file's contents.
    printf("Import of scene %s succeeded.\n",pFile.c_str());

	Model::loadGLTextures(model);
	Model::buildShader(model);
	Model::genVAOsAndUniformBuffer(model);

	Model::model[key] = model;
	return true;
}

void					Model::loadGLTextures(Model *model)
{

	/* scan scene's materials for textures */
	for (unsigned int m=0; m<model->scene->mNumMaterials; ++m)
	{
		int texIndex = 0;
		aiString path;	// filename

		aiReturn texFound = model->scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		while (texFound == AI_SUCCESS) {
			//fill map with textures, OpenGL image ids set to 0
			model->textureIdMap[path.data] = 0;
			// more textures?
			texIndex++;
			texFound = model->scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		}
	}

	int numTextures = model->textureIdMap.size();

	/* create and fill array with GL texture ids */
	GLuint* textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds); /* Texture name generation */

	/* get iterator */
	std::map<std::string, GLuint>::iterator itr = model->textureIdMap.begin();
	int i=0;
	for (; itr != model->textureIdMap.end(); ++i, ++itr)
	{
		//save IL image ID
		std::string filename = "assets/" + (*itr).first;  // get filename

		textureIds[i] = SOIL_load_OGL_texture
		(
			filename.c_str(),
			SOIL_LOAD_AUTO,
        	SOIL_CREATE_NEW_ID,
        	SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
		);

		if (textureIds[i] == 0) {
			printf("Couldn't load Image: %s\n", filename.c_str());
		} else {
			printf("Image: %s Loaded\n", filename.c_str());

			(*itr).second = textureIds[i];	  // save texture id for filename in map
		}
	}
	delete [] textureIds;
}

/*
 * DEFAULT SHADER FOR THIS MODELS :
 *
 * add on vertex shader :
 * in vec3 a_pos;
 * in vec3 a_norm;
 * in vec2 a_texCoord;
 *
 * uniform mat4 u_projMatrix
 * uniform mat4 u_viewMatrix
 * uniform mat4 u_modelMatrix
 * uniform mat4 u_transformMatrix
 *
 * add on fragment shader :
 * layout (std140) uniform u_material {
 * 	vec4 diffuse;
 * 	vec4 ambient;
 * 	vec4 specular;
 * 	vec4 emissive;
 * 	float shininess;
 * 	int texCount;
 * }
 * uniform	sampler2D u_texUnit;
 * out vec4 o_color;
 */
void						Model::buildShader(Model *model)
{
	//vertex shader
	model->vertexLoc = glGetAttribLocation(model->shader,"a_pos");
	model->normalLoc = glGetAttribLocation(model->shader,"a_norm");
	model->texCoordLoc = glGetAttribLocation(model->shader,"a_texCoord");

	model->projectionMatrixLoc = glGetUniformLocation(model->shader, "u_projMatrix");
	model->viewMatrixLoc = glGetUniformLocation(model->shader, "u_viewMatrix");
	model->modelMatrixLoc = glGetUniformLocation(model->shader, "u_modelMatrix");
	model->transformMatrixLoc = glGetUniformLocation(model->shader, "u_transformMatrix");

	//fragment shader
	GLuint m = glGetUniformBlockIndex(model->shader,"u_material");
	glUniformBlockBinding(model->shader, m, model->materialUniLoc);

	model->texUnit = glGetUniformLocation(model->shader, "u_texUnit");

	glBindFragDataLocation(model->shader, 0, "o_color");
}

void						Model::genVAOsAndUniformBuffer(Model *model)
{
    struct MyMesh aMesh;
    struct MyMaterial aMat;
    GLuint buffer;

    // For each mesh
	std::cout << "Number of meshs : " << model->scene->mNumMeshes << std::endl;
    for (unsigned int n = 0; n < model->scene->mNumMeshes; ++n)
    {
        const aiMesh* mesh = model->scene->mMeshes[n];

        // create array with faces
        // have to convert from Assimp format to array
        unsigned int *faceArray;
        faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
        unsigned int faceIndex = 0;

        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            const aiFace* face = &mesh->mFaces[t];

            memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
            faceIndex += 3;
        }
        aMesh.numFaces = model->scene->mMeshes[n]->mNumFaces;

        // generate Vertex Array for mesh
        glGenVertexArrays(1,&(aMesh.vao));
        glBindVertexArray(aMesh.vao);

        // buffer for faces
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
        // buffer for vertex positions
        if (mesh->HasPositions()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(model->vertexLoc);
            glVertexAttribPointer(model->vertexLoc, 3, GL_FLOAT, false, 0, 0);
        }

        // buffer for vertex normals
        if (mesh->HasNormals()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
            glEnableVertexAttribArray(model->normalLoc);
            glVertexAttribPointer(model->normalLoc, 3, GL_FLOAT, false, 0, 0);
        }

        // buffer for vertex texture coordinates
        if (mesh->HasTextureCoords(0)) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, &mesh->mTextureCoords[0][0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(model->texCoordLoc);
            glVertexAttribPointer(model->texCoordLoc, 3, GL_FLOAT, false, 0, 0);
        }

        // unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

        //create material uniform buffer
        aiMaterial *mtl = model->scene->mMaterials[mesh->mMaterialIndex];

        aiString texPath;   //contains filename of texture
        if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath)){
                //bind texture
                unsigned int texId = model->textureIdMap[texPath.data];
                aMesh.texIndex = texId;
                aMat.texCount = 1;
            }
        else
            aMat.texCount = 0;

        float c[4];
        set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            color4_to_float4(&diffuse, c);
        memcpy(aMat.diffuse, c, sizeof(c));

        set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
        aiColor4D ambient;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
            color4_to_float4(&ambient, c);
        memcpy(aMat.ambient, c, sizeof(c));

        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D specular;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
            color4_to_float4(&specular, c);
        memcpy(aMat.specular, c, sizeof(c));

        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D emission;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
            color4_to_float4(&emission, c);
        memcpy(aMat.emissive, c, sizeof(c));

        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        aMat.shininess = shininess;

        glGenBuffers(1,&(aMesh.uniformBlockIndex));
        glBindBuffer(GL_UNIFORM_BUFFER,aMesh.uniformBlockIndex);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(aMat), (void *)(&aMat), GL_STATIC_DRAW);

		std::cout << "Number of Faces : " << aMesh.numFaces << std::endl;

        model->myMeshes.push_back(aMesh);
    }
}

void								Model::deleteModels(void)
{
	for (std::map<const std::string, Model*>::iterator it = Model::model.begin(); it != Model::model.end(); ++it)
	{
		Model *m = it->second;
		delete m;
	}
}

// ###############################################################

// CANONICAL #####################################################

Model::Model (unsigned int shader)
{
	this->shader = shader;
	return ;
}

Model::Model ( Model const & src )
{
	*this = src;
	return ;
}

Model &				Model::operator=( Model const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Model::~Model ( void )
{
	return ;
}

std::ostream &				operator<<(std::ostream & o, Model const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void					Model::draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix)
{
	glUseProgram(this->shader);

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	glm::vec3 p = position * glm::vec3(2,2,2);
	glm::vec3 s = glm::vec3(scale);
	s.x = s.x / 2;
	s.y = s.y / 2;
	s.z = s.z / 2;

	//SCALE
	modelMatrix = glm::scale(modelMatrix, s);
	//ROTATION
	glm::mat4 matRoll  = glm::mat4(1.0f);//identity matrix;
	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
	glm::mat4 matYaw   = glm::mat4(1.0f);//identity matrix
	matRoll  = glm::rotate(matRoll,  rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matPitch = glm::rotate(matPitch, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw   = glm::rotate(matYaw,  rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotate = matRoll * matPitch * matYaw;
	modelMatrix = rotate * modelMatrix;

	//POSITION
	modelMatrix = glm::translate(modelMatrix, -p);

	glUniformMatrix4fv(this->projectionMatrixLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(this->viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(this->modelMatrixLoc, 1, GL_FALSE, &modelMatrix[0][0]);

	this->recursive_render(this->scene->mRootNode);

	glUseProgram(0);
}

void 					Model::recursive_render(const aiNode* nd)
{
	if (nd->mNumMeshes == 0) {
		for (unsigned int n=0; n < nd->mNumChildren; ++n){
			this->recursive_render(nd->mChildren[n]);
		}
		return ;
	}
	// Get node transformation matrix
	aiMatrix4x4 m = nd->mTransformation;
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			transformMatrix[y][x] = m[y][x];
		}
	}
	glUniformMatrix4fv(this->transformMatrixLoc, 1, GL_FALSE, &transformMatrix[0][0]);
	glUniform1i(this->texUnit,0);
	for (unsigned int n=0; n < nd->mNumMeshes; ++n) {
		// bind material uniform
		glBindBufferRange(GL_UNIFORM_BUFFER, this->materialUniLoc, this->myMeshes[nd->mMeshes[n]].uniformBlockIndex, 0, sizeof(struct MyMaterial));
		// bind texture
		//std::cout << this->myMeshes[nd->mMeshes[n]].texIndex << std::endl;
		glBindTexture(GL_TEXTURE_2D, this->myMeshes[nd->mMeshes[n]].texIndex);
		// bind VAO
		glBindVertexArray(this->myMeshes[nd->mMeshes[n]].vao);
		// draw
		glDrawElements(GL_TRIANGLES,this->myMeshes[nd->mMeshes[n]].numFaces*3,GL_UNSIGNED_INT,0);
		//unbind VAO
		glBindVertexArray(0);
	}
	// draw all children
	for (unsigned int n=0; n < nd->mNumChildren; ++n){
		this->recursive_render(nd->mChildren[n]);
	}
}

// ###############################################################
