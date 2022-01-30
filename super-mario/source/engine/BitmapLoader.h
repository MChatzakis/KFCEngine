#ifndef _BITMAPLOADER_H_
#define _BITMAPLOADER_H_

#include <iostream>
#include <map>

#include "./General.h"

class BitmapLoader {
private:
	using Bitmaps = std::map<std::string, Bitmap>;
	Bitmaps bitmaps;
	Bitmap GetBitmap(const std::string& path) const;
public:
	Bitmap Load(const std::string& path);

	// prefer to massively clear bitmaps at the end than to destroy individual bitmaps during gameplay
	void CleanUp(void);

	BitmapLoader(void) {}
	~BitmapLoader() { 
		//CleanUp(); 
	}
};


#endif _BITMAPLOADER_H_