#ifndef _ANIMATIONFILM_H
#define _ANIMATIONFILM_H

#include <vector>

#include "./General.h"

class AnimationFilm {
	std::vector<Rect> boxes; //we must give these values from a json (precise space of the frame)
	std::string id;

	Bitmap bitmap = nullptr;
public:
	struct Data
	{
		std::string id;
		std::string path;
		std::vector<Rect> rects;
	};

	byte GetTotalFrames(void) const;

	Bitmap GetBitmap(void) const;

	auto GetId(void) const -> const std::string&;

	const Rect& GetFrameBox(byte frameNo) const;

	void DisplayFrame(Bitmap dest, const Point& at, byte frameNo) const;

	void SetBitmap(Bitmap b);

	void Append(const Rect& r);

	AnimationFilm(const std::string& _id);

	AnimationFilm(Bitmap _bitmap, const std::vector<Rect>& _boxes, const std::string& _id);

};

#endif _ANIMATIONFILM_H