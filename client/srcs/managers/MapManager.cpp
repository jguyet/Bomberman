#include "managers/MapManager.hpp"

MapManager::MapManager (Scene *scene, std::string const &map_name) : scene(scene)
{
	this->map_lexer_types["ground"] = &MapManager::addGroundToCase;
	this->map_lexer_types["destructible"] = &MapManager::addDestructibleToCase;
	this->map_lexer_types["indestructible"] = &MapManager::addIndestructibleToCase;
	this->map_lexer_types["AI"] = &MapManager::addAIToCase;
	this->map_lexer_types["solo_position"] = &MapManager::addSoloCase;
	this->map_lexer_types["pvp_position"] = &MapManager::addPvPCase;

	this->map_path = "maps/" + std::string(map_name);
	this->map_name = std::string(map_name);
	this->loadMap();
}

MapManager::MapManager (void)
{
	return;
}

MapManager::MapManager ( MapManager const & src )
{
	*this = src;
}

MapManager::~MapManager ()
{
	delete this->map;
}

MapManager &		MapManager::operator=( MapManager const & rhs )
{
	return (*this);
}

std::ostream &		operator<<(std::ostream & o, MapManager const & i)
{

	return (o);
}

bool				MapManager::loadMap( void )
{
	std::ifstream ifs(this->map_path);

	if (!ifs)
		return false;
	file_get_contents(this->content, this->map_path.c_str());

	replaceAll(this->content, "\t", " ");
	replaceAll(this->content, "\r", " ");
	replaceAll(this->content, "\f", " ");
	if (this->content == "")
		return false;
	this->map = new Map(this->map_name);
	this->parseMap(this->map, this->content);
	return true;
}

Map					*MapManager::getMap(void)
{
	return (this->map);
}

Case				*MapManager::getRandomWalkableSoloCase(void)
{
	Random random;

	if (this->map->soloCases.size() == 0)
		return NULL;
	return (&this->map->soloCases[random.getRandom(0, this->map->soloCases.size() - 1)]);
}

Case				*MapManager::getRandomWalkablePvPCase(void)
{
	Random random;

	if (this->map->pvpCases.size() == 0)
		return NULL;
	return (&this->map->pvpCases.at(random.getRandom(0, this->map->pvpCases.size() - 1)));
}

std::vector<Case*>	MapManager::getAllDestructibleCases(void)
{
	std::vector<Case*> cases;
	for (auto & elem : this->map->content)
	{
		if (elem.second.obstacle != NULL && elem.second.obstacle->tag == "destructible_block") { // need to do a define or an enum
			cases.push_back(&elem.second);
		}
	}
	return cases;
}

std::vector<Case*>	MapManager::getAllIndestructibleCases(void)
{
	std::vector<Case*> cases;
	for (auto & elem : this->map->content)
	{
		if (elem.second.obstacle != NULL && elem.second.obstacle->tag == "indestructible_block") { // need to do a define or an enum
			cases.push_back(&elem.second);
		}
	}
	return cases;
}

bool				MapManager::addGroundToCase( Case &case_ref, std::string const &objectID )
{
	if (objectID == "" || Model::model.count(objectID) == 0) {
		std::cerr << "MapManager : Model \"" << objectID << "\" doesn't exists." << std::endl;
		return false;
	}
	if (case_ref.ground != NULL) {
		delete case_ref.ground;
		case_ref.ground = NULL;
	}

	GameObject	*ground = Factory::new_Ground_block(objectID);
	ground->transform.position = glm::vec3(case_ref.position.x, GROUND_POSITION_HEIGHT, case_ref.position.z);
	ground->transform.scale = glm::vec3(3.5f, 3.5f, 3.5f);
	case_ref.ground = ground;
	return true;
}

bool				MapManager::addDestructibleToCase( Case &case_ref, std::string const &objectID )
{
	if (objectID == "" || Model::model.count(objectID) == 0) {
		std::cerr << "MapManager : Model \"" << objectID << "\" doesn't exists." << std::endl;
		return false;
	}
	if (case_ref.obstacle != NULL) {
		delete case_ref.obstacle;
		case_ref.obstacle = NULL;
	}
	GameObject	*obstacle = Factory::new_Destructible_block(objectID);
	obstacle->transform.position = glm::vec3(case_ref.position.x, WALL_POSITION_HEIGHT, case_ref.position.z);
	obstacle->transform.scale = glm::vec3(3.5f, 3.5f, 3.5f);
	case_ref.obstacle = obstacle;
	return true;
}

bool				MapManager::addIndestructibleToCase( Case &case_ref, std::string const &objectID )
{
	if (objectID == "" || Model::model.count(objectID) == 0) {
		std::cerr << "MapManager : Model \"" << objectID << "\" doesn't exists." << std::endl;
		return false;
	}
	if (case_ref.obstacle != NULL) {
		delete case_ref.obstacle;
		case_ref.obstacle = NULL;
	}
	GameObject	*obstacle = Factory::new_Indestructible_block(objectID);
	obstacle->transform.position = glm::vec3(case_ref.position.x, WALL_POSITION_HEIGHT, case_ref.position.z);
	obstacle->transform.scale = glm::vec3(3.5f, 3.5f, 3.5f);
	case_ref.obstacle = obstacle;
	return true;
}

bool				MapManager::addAIToCase( Case &case_ref, std::string const &objectID )
{
	if (BombermanClient::getInstance()->sock == NULL || BombermanClient::getInstance()->sock->state == true)
		return false;
	if (case_ref.obstacle != NULL) {
		delete case_ref.obstacle;
		case_ref.obstacle = NULL;
	}

	GameObject	*block = Factory::newGoomba();
	block->transform.position = glm::vec3(case_ref.position.x, 0, case_ref.position.z);
	block->transform.scale = glm::vec3(0.05f,0.05f,0.05f);
	case_ref.obstacle = block;
	return true;
}

bool				MapManager::addPvPCase( Case &case_ref, std::string const &objectID )
{
	this->map->pvpCases.push_back(case_ref);
	return true;
}

bool				MapManager::addSoloCase( Case &case_ref, std::string const &objectID )
{
	this->map->soloCases.push_back(case_ref);
	return true;
}

bool				MapManager::parseMap(Map *map, std::string const &content)
{
	std::vector<std::string> splited_map = split(content, '\n');
	std::vector<std::string> operators;
	std::vector<std::string> map_lines;

	//preload operators and map lines
	for (int i = 0; i < splited_map.size(); i++) {
		std::string line = trim(splited_map.at(i));

		if (line == "")
			continue ;
		if (line.find("=") != std::string::npos && line.find("/") != std::string::npos) {
			operators.push_back(line);
			continue ;
		}
		map_lines.push_back(line);
	}
	//load operators to objects map
	for (int i = 0; i < operators.size(); i++) {
		std::vector<std::string> operation_line = split(operators.at(i), ' ');

		if (operation_line.size() != 3) {
			std::cerr << "Error syntax on Operation line : \"" << splited_map.at(i) << "\""  << std::endl;
			return false;
		}

		int							id		= atoi(operation_line.at(0).c_str());
		std::string					operand	= operation_line.at(1);
		std::vector<std::string>	infos	= split(operation_line.at(2), '/');

		if (infos.size() != 2) {
			std::cerr << "Error syntax on Operation line : \"" << splited_map.at(i) << "\" doesn't contains separator textureID/TYPE "  << std::endl;
			return false;
		}
		std::string					textureID	= infos.at(0);
		std::string					type		= infos.at(1);

		MapObject mapObject;

		mapObject.id		= id;
		mapObject.textureID = textureID;
		mapObject.type		= type;

		map->objects[id] = mapObject;
	}
	int position_map_x = 0, position_map_y = 0;
	int height = map_lines.size();
	//load map_lines map
	for (int i = 0; i < map_lines.size(); i++) {
		std::vector<std::string> cases_line = split(map_lines.at(i), ' ');

		for (int width = cases_line.size() - 1; width >= 0; width--) {
			std::vector<std::string> case_infos = split(cases_line.at(width), '/');
			Case			cube;

			cube.ground = NULL;
			cube.obstacle = NULL;
			cube.door = NULL;
			cube.walkable = true;
			cube.position = glm::vec3(height * 2, 0, width * 2);

			for (int c = 0; c < case_infos.size(); c++) {
				int currentID = atoi(case_infos.at(c).c_str());
				if (map->objects.count(currentID) >= 1 && this->map_lexer_types.count(map->objects[currentID].type) >= 1) {
					(*this.*this->map_lexer_types[map->objects[currentID].type])(cube, map->objects[currentID].textureID);
				}
			}
			this->map->content[std::make_pair(height, width)] = cube;
		}
		height--;
	}

	return true;
}

void					MapManager::buildObjects(void)
{

	for (auto & elem : this->map->content)
	{
		if (elem.second.obstacle != NULL && elem.second.obstacle->tag == "Goomba") {

			GameObject *goomba = elem.second.obstacle;
			this->scene->add(goomba); //add on scene
			elem.second.obstacle = NULL;
		} else if (elem.second.obstacle != NULL) {
			this->scene->add(elem.second.obstacle);
		}
		if (elem.second.ground != NULL) {
			this->scene->add(elem.second.ground);
		}
	}
	//this->scene->add(Factory::newBackground());
	this->scene->add(Factory::newSkybox());
}
