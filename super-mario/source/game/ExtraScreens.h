#ifndef _EXTRASCREENS_H_
#define _EXTRASCREENS_H_

#include "./GameVars.h"

class ExtraScreens {
private:
	static ExtraScreens screens;
public:
	static auto GetSingleton(void)->ExtraScreens&;
	static auto GetSingletonConst(void) -> const ExtraScreens&;

	void DispScreen(std::string imagePath);
};

#endif _EXTRASCREENS_H_