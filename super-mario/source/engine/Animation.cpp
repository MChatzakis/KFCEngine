#include "./Animation.h"

const std::string& Animation::GetId(void) {
	return id;
}

void Animation::SetId(const std::string& _id) {
	id = _id;
}

Animation::Animation(const std::string& _id) : id(_id) {}