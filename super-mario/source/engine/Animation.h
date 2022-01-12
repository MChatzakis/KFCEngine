#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <iostream>
#include <string>

#include "./General.h"

class Animation {
protected:
	std::string id;
public:
	const std::string& GetId(void) {
		return id;
	}

	void SetId(const std::string& _id) {
		id = _id;
	}

	Animation(const std::string& _id) : id(_id) {}

	virtual Animation* Clone(void) const = 0;
	virtual ~Animation() {}
};

#endif _ANIMATION_H_