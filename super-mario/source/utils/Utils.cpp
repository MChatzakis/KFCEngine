#include "Utils.h"

#include <fstream>
#include <iostream>
#include <iomanip>

nlohmann::json readJSON(const std::string filename) {
	std::ifstream ifp (filename);
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

bool getAnimationFilmData(const std::string filename, std::list<AnimationFilm::Data>& data) {
	return false;
}

int getAnimationFilmData(int startPos, const std::string& filename, std::string& idOutput, std::string& pathOutput, std::vector<Rect>& rectsOutput) {
	return 0;
}