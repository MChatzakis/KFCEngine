#ifndef _UTILS_H_
#define _UTILS_H_

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>

#include "../engine/AnimationFilm.h"
#include "../engine/AnimationFilmHolder.h"

#include <list>

nlohmann::json readJSON(const std::string filename);
void writeJSON(nlohmann::json j, const std::string filename, unsigned short indent);
bool getAnimationFilmDataParser(std::list<AnimationFilm::Data>& output, const std::string& input);
int getAnimationFilmDataEntryParser(int startPos, const std::string& filename, std::string& idOutput, std::string& pathOutput, std::vector<Rect>& rectsOutput);

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
	std::cout << path <<"\n";

	nlohmann::json animations = jsonFile["animations"];
	for (nlohmann::json::iterator it = animations.begin(); it != animations.end(); ++it) {
		nlohmann::json object = *it;

		std::string id = object["id"];
		nlohmann::json frameArray = object["frames"];
		
		AnimationFilm::Data animData;
		animData.id = id;
		animData.path = path;
		for (nlohmann::json::iterator ft = frameArray.begin(); ft != frameArray.end(); ++ft) {
			nlohmann::json jsonRect = *it;
			//animData.rects.push_back(Rect(jsonRect["x"], jsonRect["y"], jsonRect["w"], jsonRect["h"]));
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


#endif _UTILS_H_
