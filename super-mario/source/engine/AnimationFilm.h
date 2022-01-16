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

	byte GetTotalFrames(void) const {
		return boxes.size();
	}

	Bitmap GetBitmap(void) const {
		return bitmap;
	}

	auto GetId(void) const -> const std::string& {
		return id;
	}

	const Rect& GetFrameBox(byte frameNo) const {
		assert(boxes.size() > frameNo); 
		return boxes[frameNo];
	}

	void DisplayFrame(Bitmap dest, const Point& at, byte frameNo) const {
		MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);
	}

	void SetBitmap(Bitmap b) {
		assert(!bitmap); 
		bitmap = b;
	}

	void Append(const Rect& r) {
		boxes.push_back(r);
	}

	AnimationFilm(const std::string& _id) : id(_id) {}

	AnimationFilm(Bitmap _bitmap, const std::vector<Rect>& _boxes, const std::string& _id) : bitmap(_bitmap), boxes(_boxes), id(_id) {}

};

#endif _ANIMATIONFILM_H