#ifndef _UTILS_H_
#define _UTILS_H_

#include <nlohmann/json.hpp>
#include "../engine/AnimationFilm.h"
#include <list>

nlohmann::json readJSON(const std::string filename);
void writeJSON(nlohmann::json j, const std::string filename, unsigned short indent);
bool getAnimationFilmData(const std::string filename, std::list<AnimationFilm::Data>& data);
int getAnimationFilmData(int startPos, const std::string& filename, std::string& idOutput, std::string& pathOutput, std::vector<Rect>& rectsOutput);

#endif _UTILS_H_
