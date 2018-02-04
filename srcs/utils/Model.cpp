#include "Bomberman.hpp"


bool DoTheImportThing( const std::string& pFile)
{
  // Create an instance of the Importer class
  Assimp::Importer importer;
  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // propably to request more postprocessing than we do in this example.
  const aiScene* scene = importer.ReadFile( pFile,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  // If the import failed, report it
  if( !scene)
  {
    //DoTheErrorLogging( importer.GetErrorString());
    return false;
  }
  // Now we can access the file's contents.
  //DoTheSceneProcessing( scene);
  // We're done. Everything will be cleaned up by the importer destructor
  return true;
}

// STATIC ########################################################

// int					Model::createTexturedDisplayList(Model *model)
// {
// 	int displayList = glGenLists(1);
//
// 	glNewList(displayList, GL_COMPILE);
// 	{
// 		glBegin(GL_TRIANGLES);
// 		for (std::vector<Model::Face*>::iterator it = model->getFaces()->begin() ; it != model->getFaces()->end(); ++it) {
// 			Model::Face *face = *it;
// 			if (face->hasTextureCoordinates()) {
// 				float mat_diffuse[4] = {
// 									face->getMaterial()->diffuseColour[0],
// 									face->getMaterial()->diffuseColour[1],
// 									face->getMaterial()->diffuseColour[2],
// 									1.0f
// 									};
// 				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//
// 				float no_mat[4] = {
// 									face->getMaterial()->ambientColour[0],
// 									face->getMaterial()->ambientColour[1],
// 									face->getMaterial()->ambientColour[2],
// 									1.0f
// 									};
// 				glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
// 				glMaterialf(GL_FRONT, GL_SHININESS, face->getMaterial()->specularCoefficient);
// 			}
// 			for (int i = 0; i < 2; i++) {
// 				if (face->hasNormals()) {
// 					glm::vec3 *n1 = model->getNormals()->at(face->getNormalIndices()[i] - 1);
// 					glNormal3f(n1->x, n1->y, n1->z);
// 				}
// 				if (face->hasTextureCoordinates()) {
// 					glm::vec2 *t1 = model->getTextureCoordinates()->at(face->getTextureCoordinatesIndices()[i] - 1);
// 					glTexCoord2f(t1->x, t1->y);
// 				}
// 				glm::vec3 *v1 = model->getVertices()->at(face->getVertexIndices()[i] - 1);
// 				glVertex3f(v1->x, v1->y, v1->z);
// 			}
// 		}
// 		glEnd();
// 	}
// 	glEndList();
// 	return displayList;
// }

void					Model::loadMaterials(Model *model, std::string absolutePath, std::string filename)
{
	std::ifstream file;

	file.open(absolutePath + filename);

	if (!file.good()) {
		printf("Impossible to open the file %s !\n", (absolutePath + filename).c_str());
		return ;
	}

	std::string materialLine;
	Model::Material *parseMaterial = NULL;
	std::string parseMaterialName = "";

	for (std::string materialLine; std::getline(file, materialLine);) {
		std::vector<std::string> materialspl = split(materialLine, ' ');

		if (materialLine == "" || materialspl.at(0) == "#") {
			continue ;
		}

		if (materialspl.at(0) == "newmtl") { // indique le début d'un nouveau matériel
			if (parseMaterialName != "" && model->getMaterials().count(parseMaterialName) == 0) {
				model->getMaterials()[parseMaterialName] = parseMaterial;
			}
			parseMaterialName = materialspl.at(1);
			parseMaterial = new Model::Material();

		} else if (materialspl.at(0) == "Ns") { //pour le specular exponent entre 0 et 100
			parseMaterial->specularCoefficient = std::stof(materialspl.at(1));
		} else if (materialspl.at(0) == "Ka") { //nous donne la couleur ambiante (la couleur de l'objet sans lumière directe), RVB entre 0 (Min) et 1 (Max)
			parseMaterial->ambientColour[0] = std::stof(materialspl.at(1));
			parseMaterial->ambientColour[1] = std::stof(materialspl.at(2));
			parseMaterial->ambientColour[2] = std::stof(materialspl.at(3));
		} else if (materialspl.at(0) == "Ks") { //pour la couleur spéculaire (specular)
			parseMaterial->specularColour[0] = std::stof(materialspl.at(1));
			parseMaterial->specularColour[1] = std::stof(materialspl.at(2));
			parseMaterial->specularColour[2] = std::stof(materialspl.at(3));
		} else if (materialspl.at(0) == "Kd") { //est utilisé pour la couleur diffuse (la couleur de l'objet sous lumière blanche)
			parseMaterial->diffuseColour[0] = std::stof(materialspl.at(1));
			parseMaterial->diffuseColour[1] = std::stof(materialspl.at(2));
			parseMaterial->diffuseColour[2] = std::stof(materialspl.at(3));
		} else if (materialspl.at(0) == "map_Kd") { //"map_kd" (ks, ka) pour la texture utilisé diffuse (specular, ambiante)
			parseMaterial->texture = (absolutePath + "/" + materialspl.at(1)).c_str();
		} else if (materialspl.at(0) == "illum") {
			//TODO paramtere de lumiere
		} else if (materialspl.at(0) == "d") {
			//TODO pour la transparence entre 0 et 1 (aucune transparence)
		} else if (materialspl.at(0) == "Ni") {
			//TODO pour la densité optique
		} else if (materialspl.at(0) == "Ke") {
			//TODO pour la couleur émissive (emissive)
		}
	}
	if (parseMaterialName != "" && model->getMaterials().count(parseMaterialName) == 0) {
		model->getMaterials()[parseMaterialName] = parseMaterial;
	}
	file.close();
}

Model				*Model::loadModel(std::string filename)
{
	std::ifstream file;

	file.open(filename);
	if(!file.good()) {
		printf("Impossible to open the file %s !\n", filename.c_str());
		return NULL;
	}
	Model *model = new Model();
	Model::Material *currentMaterial = NULL;

	int lastslash = filename.find_last_of("/");
	std::string absolutePath = filename;

	if (lastslash == -1) {
		absolutePath = "";
	} else {
		absolutePath = absolutePath.substr(0, lastslash + 1);
	}

	for (std::string line; std::getline(file, line);) {
		std::vector<std::string> spl = split(line, ' ');
		std::string prefix = spl.at(0);

		if (line == "" || prefix == "#") {
			continue ;
		}
		if (prefix == "mtllib") {
			Model::loadMaterials(model, absolutePath, spl.at(1));
		} else if (prefix == "usemtl") {
			if (model->getMaterials().count(spl.at(1)) == 1)
				currentMaterial = model->getMaterials()[spl.at(1)];
			else
				currentMaterial = NULL;
		} else if (prefix == "v") {
			Model::parseVertex(model, line);
		} else if (prefix == "vn") {
			Model::parseNormals(model, line);
		} else if (prefix == "vt") {
			Model::parseTextureCoordinates(model, line);
		} else if (prefix == "f") {
			Model::parseFace(model, line, currentMaterial);
		} else if (spl.at(0) == "s") {
			model->setSmoothShadingEnabled(line.find("off") != -1);
		} else {
			std::cout << "[OBJ] Unknown Line: " << line << std::endl;
		}
	}
	std::cout << "Vertex size: " << model->getVertices().size() << std::endl;
	std::cout << "Normals size: " << model->getNormals().size() << std::endl;
	std::cout << "Faces size: " << model->getFaces().size() << std::endl;
	for (int i = 0; i < model->getFaces().size(); i++) {
		model->getFaces().at(i).build(model);
	}
	file.close();
	return model;
}
//
// Model				*Model::loadTexturedModel(std::string filename)
// {
// 	std::ifstream file;
//
// 	file.open(filename);
// 	if(!file.good()) {
// 		printf("Impossible to open the file %s !\n", filename.c_str());
// 		return NULL;
// 	}
// 	Model *model = new Model();
// 	Model::Material *currentMaterial = new Model::Material();
//
// 	int lastslash = filename.find_last_of("/");
// 	std::string absolutePath = filename;
//
// 	if (lastslash == -1) {
// 		absolutePath = "";
// 	} else {
// 		absolutePath = absolutePath.substr(0, lastslash + 1);
// 	}
//
// 	for (std::string line; std::getline(file, line);) {
// 		std::vector<std::string> spl = split(line, ' ');
//
// 		if (spl.at(0) == "#") {
// 			continue ;
// 		}
//
// 		if (spl.at(0) == "mtllib") {
// 			std::string materialFileName = split(line, ' ').at(1);
// 			std::ifstream materialFile;
//
// 			materialFile.open(absolutePath + materialFileName);
//
// 			if (!materialFile.good()) {
// 				printf("Impossible to open the file %s !\n", (absolutePath + materialFileName).c_str());
// 				return NULL;
// 			}
//
// 			std::string materialLine;
// 			Model::Material *parseMaterial = new Model::Material();
// 			std::string parseMaterialName = "";
//
// 			for (std::string materialLine; std::getline(materialFile, materialLine);) {
// 				std::vector<std::string> materialspl = split(materialLine, ' ');
//
// 				if (materialLine == "" || materialspl.at(0) == "#") {
// 					continue ;
// 				}
//
// 				if (materialspl.at(0) == "newmtl") {
// 					if (parseMaterialName != "") {
// 						model->getMaterials()[parseMaterialName] = parseMaterial;
// 					}
// 					parseMaterialName = materialspl.at(1);
// 					parseMaterial = new Model::Material();
//
// 				} else if (materialspl.at(0) == "Ns") {
// 					parseMaterial->specularCoefficient = std::stof(materialspl.at(1));
// 				} else if (materialspl.at(0) == "Ka") {
// 					parseMaterial->ambientColour[0] = std::stof(materialspl.at(1));
// 					parseMaterial->ambientColour[1] = std::stof(materialspl.at(2));
// 					parseMaterial->ambientColour[2] = std::stof(materialspl.at(3));
// 				} else if (materialspl.at(0) == "Ks") {
// 					parseMaterial->specularColour[0] = std::stof(materialspl.at(1));
// 					parseMaterial->specularColour[1] = std::stof(materialspl.at(2));
// 					parseMaterial->specularColour[2] = std::stof(materialspl.at(3));
// 				} else if (materialspl.at(0) == "Kd") {
// 					parseMaterial->diffuseColour[0] = std::stof(materialspl.at(1));
// 					parseMaterial->diffuseColour[1] = std::stof(materialspl.at(2));
// 					parseMaterial->diffuseColour[2] = std::stof(materialspl.at(3));
// 				} else if (materialspl.at(0) == "map_Kd") {
// 					parseMaterial->texture = (absolutePath + "/" + materialspl.at(1) + ".png");
// 				} else {
//
// 				}
// 			}
// 			model->getMaterials()[parseMaterialName] = parseMaterial;
// 			materialFile.close();
// 		} else if (spl.at(0) == "usemtl") {
// 			currentMaterial = model->getMaterials()[spl.at(1)];
// 		} else if (spl.at(0) == "v") {
// 			model->getVertices().insert(model.getVertices()->begin(), Model::parseVertex(line));
// 		} else if (spl.at(0) == "vn") {
// 			model->getNormals()->insert(model.getNormals()->begin(), Model::parseNormals(line));
// 		} else if (spl.at(0) == "vt") {
// 			model->getTextureCoordinates().insert(model->getTextureCoordinates()->begin(), Model::parseTextureCoordinates(line));
// 		} else if (spl.at(0) == "f") {
// 			model->getFaces().insert(model->getFaces().begin(), Model::parseFace(model, line, currentMaterial));
// 		} else if (spl.at(0) == "s") {
// 			model->setSmoothShadingEnabled(line.find("off") != -1);
// 		} else if (spl.at(0) == "o") {
// 			//Name
// 		} else {
// 			std::cout << "[OBJ] Unknown Line: " << spl.at(0) << std::endl;
// 		}
// 	}
// 	file.close();
// 	return model;
// }

void					Model::parseVertex(Model *model, std::string line)
{
    std::vector<std::string> xyz = split(line, ' ');
    float x = std::stof(xyz.at(1));
    float y = std::stof(xyz.at(2));
    float z = std::stof(xyz.at(3));

	model->getVertices().push_back(glm::vec3(x, y, z));
}

void					Model::parseNormals(Model *model, std::string line)
{
    std::vector<std::string> xyz = split(line, ' ');
    float x = std::stof(xyz.at(1));
    float y = std::stof(xyz.at(2));
    float z = std::stof(xyz.at(3));
	model->getNormals().push_back(glm::vec3(x, y, z));
}

void					Model::parseTextureCoordinates(Model *model, std::string line)
{
    std::vector<std::string> xyz = split(line, ' ');
    float s = std::stof(xyz.at(1));
    float t = std::stof(xyz.at(2));
	model->getTextureCoordinates().push_back(glm::vec2(s, t));
}


void					Model::parseFace(Model *model, std::string line, Material *currentMaterial)
{
	if (line.find("/") == -1) {
		Model::parseFaceVertex(model, line, currentMaterial);
		return ;
	}
	std::vector<std::string> faceIndices = split(line, ' ');
	int textureCoordinateIndicesArray[3] = {-1, -1, -1};
	int	normalIndicesArray[3] = {-1, -1, -1};
	int vertexIndicesArray[3] = {
									std::stoi(split(faceIndices.at(1), '/').at(0)) - 1,
									std::stoi(split(faceIndices.at(2), '/').at(0)) - 1,
									std::stoi(split(faceIndices.at(3), '/').at(0)) - 1
								};

	if (model->hasTextureCoordinates() && faceIndices.at(1).find("//") == -1) {
        textureCoordinateIndicesArray[0] = std::stoi(split(faceIndices.at(1), '/').at(1)) - 1;
        textureCoordinateIndicesArray[1] = std::stoi(split(faceIndices.at(2), '/').at(1)) - 1;
        textureCoordinateIndicesArray[2] = std::stoi(split(faceIndices.at(3), '/').at(1)) - 1;
    }
	if (model->hasNormals()) {
		normalIndicesArray[0] = std::stoi(split(faceIndices.at(1), '/').at(2)) - 1;
		normalIndicesArray[1] = std::stoi(split(faceIndices.at(2), '/').at(2)) - 1;
		normalIndicesArray[2] = std::stoi(split(faceIndices.at(3), '/').at(2)) - 1;
	}
	model->getFaces().push_back(Model::Face(vertexIndicesArray, normalIndicesArray, textureCoordinateIndicesArray, currentMaterial));
}

void					Model::parseFaceVertex(Model *model, std::string line, Material *currentMaterial)
{
	std::vector<std::string> faceIndices = split(line, ' ');
	int textureCoordinateIndicesArray[3] = {-1, -1, -1};
	int	normalIndicesArray[3] = {-1, -1, -1};
	int vertexIndicesArray[3] = {
									std::stoi(faceIndices.at(1)) - 1,
									std::stoi(faceIndices.at(2)) - 1,
									std::stoi(faceIndices.at(3)) - 1
								};
	model->getFaces().push_back(Model::Face(vertexIndicesArray, normalIndicesArray, textureCoordinateIndicesArray, currentMaterial));
}


// ###############################################################

// CANONICAL #####################################################

Model::Model ( void )
{
	this->enableSmoothShading = false;
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

// void									Model::enableStates( void )
// {
// 	if (this->hasTextureCoordinates()) {
// 		glEnable(GL_TEXTURE_2D);
// 	}
// 	if (this->isSmoothShadingEnabled()) {
// 		glShadeModel(GL_SMOOTH);
// 	} else {
// 		glShadeModel(GL_FLAT);
// 	}
// }

bool									Model::hasTextureCoordinates( void )
{
	return (this->textureCoordinates.size() > 0);
}

bool									Model::hasNormals( void )
{
	return (this->normals.size() > 0);
}

std::vector<glm::vec3>					&Model::getVertices( void )
{
	return (this->vertices);
}

std::vector<glm::vec2>					&Model::getTextureCoordinates( void )
{
	return (this->textureCoordinates);
}

std::vector<Model::Face>				&Model::getFaces( void )
{
	return (this->faces);
}

std::vector<glm::vec3>					&Model::getNormals( void )
{
	return (this->normals);
}

bool									Model::isSmoothShadingEnabled( void )
{
	return (this->enableSmoothShading);
}

void									Model::setSmoothShadingEnabled(bool smoothShadingEnabled)
{
	this->enableSmoothShading = smoothShadingEnabled;
}

std::map<std::string, Model::Material*>	&Model::getMaterials( void )
{
	return (this->materials);
}

void									Model::produce( void )
{


	for (int i = 0; i < this->faces.size(); i++) {
		this->faces.at(i).produce();
	}
}

void									Model::render( const GLfloat *mvp )
{
	for (int i = 0; i < this->faces.size(); i++) {
		this->faces.at(i).render();
	}
}

// ###############################################################
