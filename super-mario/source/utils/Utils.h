#ifndef _UTILS_H_
#define _UTILS_H_

#include <nlohmann/json.hpp>

nlohmann::json readJSON(const std::string filename);
void writeJSON(nlohmann::json j, const std::string filename, unsigned short indent);

#endif _UTILS_H_
