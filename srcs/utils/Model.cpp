#include "Bomberman.hpp"

// STATIC ########################################################

// #define aisgl_min(x,y) (x<y?x:y)
// #define aisgl_max(x,y) (y>x?y:x)
//
// void	get_bounding_box_for_node(Model *model, const aiNode* nd,
// 	aiVector3D* min,
// 	aiVector3D* max)
//
// {
// 	aiMatrix4x4 prev;
// 	unsigned int n = 0, t;
//
// 	for (; n < nd->mNumMeshes; ++n) {
// 		const aiMesh* mesh = model->scene->mMeshes[nd->mMeshes[n]];
// 		for (t = 0; t < mesh->mNumVertices; ++t) {
//
// 			aiVector3D tmp = mesh->mVertices[t];
//
// 			min->x = aisgl_min(min->x,tmp.x);
// 			min->y = aisgl_min(min->y,tmp.y);
// 			min->z = aisgl_min(min->z,tmp.z);
//
// 			max->x = aisgl_max(max->x,tmp.x);
// 			max->y = aisgl_max(max->y,tmp.y);
// 			max->z = aisgl_max(max->z,tmp.z);
// 		}
// 	}
//
// 	for (n = 0; n < nd->mNumChildren; ++n) {
// 		get_bounding_box_for_node(model, nd->mChildren[n],min,max);
// 	}
// }
//
// void get_bounding_box (Model *model, aiVector3D* min, aiVector3D* max)
// {
//
// 	min->x = min->y = min->z =  1e10f;
// 	max->x = max->y = max->z = -1e10f;
// 	get_bounding_box_for_node(model, model->scene->mRootNode, min, max);
// }

inline void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

inline void color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

Model				*Model::load( const std::string& pFile )
{
    std::ifstream fin(pFile.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{
        printf("Couldn't open file: %s\n", pFile.c_str());
        return NULL;
    }

	Model *model = new Model();

    model->scene = model->importer.ReadFile( pFile, aiProcessPreset_TargetRealtime_Quality);

    // If the import failed, report it
    if( !model->scene)
    {
        printf("%s\n", model->importer.GetErrorString());
		delete model;
        return NULL;
    }

    // Now we can access the file's contents.
    printf("Import of scene %s succeeded.\n",pFile.c_str());

	Model::loadGLTextures(model);
	Model::buildShader(model);
	Model::genVAOsAndUniformBuffer(model);

    //aiVector3D scene_min, scene_max, scene_center;
    //get_bounding_box(model, &scene_min, &scene_max);
    //float tmp;
    //tmp = scene_max.x-scene_min.x;
    //tmp = scene_max.y - scene_min.y > tmp?scene_max.y - scene_min.y:tmp;
    //tmp = scene_max.z - scene_min.z > tmp?scene_max.z - scene_min.z:tmp;
    //scaleFactor = 1.f / tmp;

    return model;
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

		// ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		// ilEnable(IL_ORIGIN_SET);
		// ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		// success = ilLoadImage((ILstring)filename.c_str());
        //
		// if (success) {
		// 	/* Convert image to RGBA */
		// 	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        //
		// 	/* Create and load textures to OpenGL */
		// 	glBindTexture(GL_TEXTURE_2D, textureIds[i]);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
		// 		ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
		// 		ilGetData());
		// }
		// else
		// 	printf("Couldn't load Image: %s\n", filename.c_str());
	}
	delete [] textureIds;
}

void						Model::buildShader( Model *model )
{
	glBindFragDataLocation(ShaderUtils::instance->get("dir"), 0, "o_color");

	glBindAttribLocation(ShaderUtils::instance->get("dir"),model->vertexLoc,"a_pos");
	glBindAttribLocation(ShaderUtils::instance->get("dir"),model->normalLoc,"a_norm");
	glBindAttribLocation(ShaderUtils::instance->get("dir"),model->texCoordLoc,"a_texCoord");


	model->projectionMatrixLoc = glGetUniformLocation(ShaderUtils::instance->get("dir"), "u_projMatrix");
	model->viewMatrixLoc = glGetUniformLocation(ShaderUtils::instance->get("dir"), "u_viewMatrix");
	model->modelMatrixLoc = glGetUniformLocation(ShaderUtils::instance->get("dir"), "u_modelMatrix");
	model->transformMatrixLoc = glGetUniformLocation(ShaderUtils::instance->get("dir"), "u_transformMatrix");

	GLuint m = glGetUniformBlockIndex(ShaderUtils::instance->get("dir"),"u_material");
	glUniformBlockBinding(ShaderUtils::instance->get("dir"), m, model->materialUniLoc);

	model->texUnit = glGetUniformLocation(ShaderUtils::instance->get("dir"), "u_texUnit");
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

// ###############################################################

// CANONICAL #####################################################

Model::Model ( void )
{
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

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Model const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void					Model::draw( glm::vec3 &position, glm::vec3 &scale )
{
	glUseProgram(ShaderUtils::instance->get("dir"));

	this->recursive_render(this->scene->mRootNode, position, scale);

	glUseProgram(0);
}

void 					Model::recursive_render(const aiNode* nd, glm::vec3 &position, glm::vec3 &scale)
{
	if (nd->mNumMeshes == 0) {
		for (unsigned int n=0; n < nd->mNumChildren; ++n){
			this->recursive_render(nd->mChildren[n], position, scale);
		}
		return ;
	}
	// Get node transformation matrix
	aiMatrix4x4 m = nd->mTransformation;
	glm::mat4 transformedModelMatrix;
	glm::mat4 transformMatrix;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			transformedModelMatrix[y][x] = m[y][x];
			transformMatrix[y][x] += m[y][x];
		}
	}

	glm::mat4 modelMatrix = BombermanClient::instance->camera->modelMatrix;
	modelMatrix = glm::scale(modelMatrix, scale);
	modelMatrix = glm::translate(modelMatrix, -position);
	//modelMatrix = (modelMatrix + transformedModelMatrix);

	glUniformMatrix4fv(this->projectionMatrixLoc, 1, GL_FALSE, &BombermanClient::instance->camera->projectionMatrix[0][0]);
	glUniformMatrix4fv(this->viewMatrixLoc, 1, GL_FALSE, &BombermanClient::instance->camera->viewMatrix[0][0]);
	glUniformMatrix4fv(this->modelMatrixLoc, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(this->transformMatrixLoc, 1, GL_FALSE, &transformMatrix[0][0]);

	glUniform1i(this->texUnit,0);

	// draw all meshes assigned to this node

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
		//glBindVertexArray(0);
	}

	// draw all children
	for (unsigned int n=0; n < nd->mNumChildren; ++n){
		this->recursive_render(nd->mChildren[n], position, scale);
	}
}

// ###############################################################
