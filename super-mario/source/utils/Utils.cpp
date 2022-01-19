#include "Utils.h"

nlohmann::json readJSON(const std::string filename) {
	std::ifstream ifp(filename);
	if (!ifp.is_open()) {
		return NULL;
	}
	nlohmann::json j;
	ifp >> j;
	return j;
}

void writeJSON(nlohmann::json j, const std::string filename, unsigned short indent) { //maybe arg for overwrite or append
	std::ofstream ofp(filename);
	if (ofp.bad()) {
		std::cout << "Could not write JSON to file" << std::endl;
		return;
	}
	ofp << std::setw(indent) << j << std::endl;
}

bool getAnimationFilmDataParser(std::list<AnimationFilm::Data>& output, const std::string& input) {
	nlohmann::json jsonFile = readJSON(input);

	if (jsonFile == NULL) {
		return false;
	}

	std::string path = jsonFile["path"];
	std::cout << path << "\n";

	nlohmann::json animations = jsonFile["animations"];
	for (nlohmann::json::iterator it = animations.begin(); it != animations.end(); ++it) {
		nlohmann::json object = *it;

		std::string id = object["id"];
		nlohmann::json frameArray = object["frames"];

		AnimationFilm::Data animData;
		animData.id = id;
		animData.path = path;
		for (nlohmann::json::iterator ft = frameArray.begin(); ft != frameArray.end(); ++ft) {
			nlohmann::json jsonRect = *ft;
			animData.rects.push_back(Rect(jsonRect["x"], jsonRect["y"], jsonRect["w"], jsonRect["h"]));
			//std::string x = jsonRect["x"], y = jsonRect["y"], w = jsonRect["w"], h = jsonRect["h"];
			//animData.rects.push_back(Rect(0,0,0,0));
		}

		output.push_back(animData);
	}

	return true;
}

int getAnimationFilmDataEntryParser(int startPos, const std::string& filename, std::string& idOutput, std::string& pathOutput, std::vector<Rect>& rectsOutput) {
	nlohmann::json jsonFile = readJSON(filename);
	if (jsonFile == NULL)
		return -1;

	std::string path = jsonFile["path"];

	nlohmann::json animations = jsonFile["animations"];

	if (startPos >= animations.size())
		return 0;

	std::string id = animations[startPos]["id"];

	nlohmann::json frameArray = animations[startPos]["frames"];
	for (nlohmann::json::iterator it = frameArray.begin(); it != frameArray.end(); ++it)
		rectsOutput.push_back(Rect((*it)["x"], (*it)["y"], (*it)["w"], (*it)["h"]));

	pathOutput = path;
	idOutput = id;

	return 1;
}

bool getSoundsDataParser(std::list<Sound>& output, const std::string& input) {
	nlohmann::json jsonFile = readJSON(input);

	if (jsonFile == NULL) {
		return false;
	}
	float gain = jsonFile["gain"];
	float pan = jsonFile["pan"];
	float speed = jsonFile["speed"];
	nlohmann::json main_sound_object = jsonFile["main_sound"];
	nlohmann::json other_sounds = jsonFile["sounds"];

	Sound main_sound = Sound(main_sound_object["id"], NULL, main_sound_object["path"], gain, pan, speed, ALLEGRO_PLAYMODE_LOOP);
	output.push_back(main_sound);

	for (nlohmann::json::iterator it = other_sounds.begin(); it != other_sounds.end(); ++it) {
		nlohmann::json object = *it;

		Sound sound = Sound(object["id"], NULL, object["path"], gain, pan, speed, ALLEGRO_PLAYMODE_ONCE);
		output.push_back(sound);
	}

	return true;
}
