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
	~BitmapLoader() { CleanUp(); }
};

Bitmap BitmapLoader::GetBitmap(const std::string& path) const {
	auto i = bitmaps.find(path);
	return i != bitmaps.end() ? i->second : nullptr;
}

void BitmapLoader::CleanUp(void) {
	for (auto& i : bitmaps)
		BitmapDestroy(i.second);
	bitmaps.clear();
}

Bitmap BitmapLoader::Load(const std::string& path) {
	auto b = GetBitmap(path);
	if (!b) {
		//std::cout << path.c_str() << "lala\n";
		bitmaps[path] = b = BitmapLoad(path.c_str());
		//std::cout << al_load_bitmap(path.c_str()) << "lala\n";
		assert(b);
	}
	return b;
}

#endif _BITMAPLOADER_H_