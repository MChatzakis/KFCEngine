#include "AnimationFilm.h"

byte AnimationFilm::GetTotalFrames(void) const {
	return boxes.size();
}

Bitmap AnimationFilm::GetBitmap(void) const {
	return bitmap;
}

auto AnimationFilm::GetId(void) const -> const std::string& {
	return id;
}

const Rect& AnimationFilm::GetFrameBox(byte frameNo) const {
	assert(boxes.size() > frameNo);
	return boxes[frameNo];
}

void AnimationFilm::DisplayFrame(Bitmap dest, const Point& at, byte frameNo) const {
	MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);
}

void AnimationFilm::SetBitmap(Bitmap b) {
	assert(!bitmap);
	bitmap = b;
}

void AnimationFilm::Append(const Rect& r) {
	boxes.push_back(r);
}

AnimationFilm::AnimationFilm(const std::string& _id) : id(_id) {}

AnimationFilm::AnimationFilm(Bitmap _bitmap, const std::vector<Rect>& _boxes, const std::string& _id) : bitmap(_bitmap), boxes(_boxes), id(_id) {}