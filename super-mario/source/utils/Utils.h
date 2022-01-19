#ifndef _UTILS_H_
#define _UTILS_H_

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>

#include "../engine/AnimationFilm.h"
#include "../engine/AnimationFilmHolder.h"
#include "../engine/SoundsManager.h"

#include <list>

nlohmann::json readJSON(const std::string filename);
void writeJSON(nlohmann::json j, const std::string filename, unsigned short indent);
bool getAnimationFilmDataParser(std::list<AnimationFilm::Data>& output, const std::string& input);
int getAnimationFilmDataEntryParser(int startPos, const std::string& filename, std::string& idOutput, std::string& pathOutput, std::vector<Rect>& rectsOutput);
bool getSoundsDataParser(std::list<Sound>& output, const std::string& input);


#endif _UTILS_H_
