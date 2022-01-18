#include "./BitmapLoader.h"

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