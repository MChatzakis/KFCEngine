#ifndef _KEYFRAMEANIMATIONS_H
#define _KEYFRAMEANIMATIONS_H

#include <iostream>
#include <vector>
#include <map>

#include "./General.h"


#define TOTAL_KEY_FRAMES 10
#define FRAME_DELAY 50
#define BLACK_COLOR 0

Bitmap keyFrames[TOTAL_KEY_FRAMES];
Point framePositions[TOTAL_KEY_FRAMES];
void Animate(void) {
	uint64_t t = 0;
	for (auto i = 0; i < TOTAL_KEY_FRAMES; )
		if (CurrTime() >= t) {
			t = CurrTime() + FRAME_DELAY;
			auto b = keyFrames[i];
			Vsync();
			BitmapClear(BitmapGetScreen(), BLACK_COLOR);
			MaskedBlit(
				b,
				{ 0, 0, BitmapGetWidth(b), BitmapGetHeight(b) },
				BitmapGetScreen(),
				framePositions[i++]
			);
		}
}

class AnimationFilm {
	std::vector<Rect> boxes;
	Bitmap bitmap = nullptr;
	std::string id;
public:
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
		assert(boxes.size() > frameNo); return boxes[frameNo];
	}

	void DisplayFrame(Bitmap dest, const Point& at, byte frameNo) const {
		MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);
	}

	void SetBitmap(Bitmap b) {
		assert(!bitmap); bitmap = b;
	}

	void Append(const Rect& r) {
		boxes.push_back(r);
	}

	AnimationFilm(const std::string& _id) : id(_id) {
	}

	AnimationFilm(Bitmap, const std::vector<Rect>&, const std::string&) {

	}

};

void Animate(const AnimationFilm& film, const Point& at) {
	uint64_t t = 0;
	for (byte i = 0; i < film.GetTotalFrames(); )
		if (CurrTime() >= t) {
			t = CurrTime() + FRAME_DELAY;
			Vsync();
			BitmapClear(BitmapGetScreen(), BLACK_COLOR);
			film.DisplayFrame(BitmapGetScreen(), at, i++);
		}
}

class AnimationFilmHolder final {
public:
	using Parser = std::function<
		bool(std::list<AnimationFilm::Data>& output, const std::string& input)
	>;
	using EntryParser = std::function<
		int(// -1=error, 0=ended gracefully, else #chars read
			int startPos,
			const std::string& input,
			std::string& idOutput,
			std::string& pathOutput,
			std::vector<Rect>& rectsOutput
			)
	>;
private:
	using Films = std::map<std::string, AnimationFilm*>;
	Films films;
	BitmapLoader bitmaps; // only for loading of film bitmaps
	static AnimationFilmHolder holder; // singleton
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }
	static auto Get(void) -> const AnimationFilmHolder& { return holder; }
	void Load(const std::string& text, const EntryParser& entryParser);
	void Load(const std::string& text, const Parser& parser);
	void CleanUp(void);
	auto GetFilm(const std::string& id) -> const AnimationFilm* const;
	void AnimationFilmHolder::Load(const std::string& text, const EntryParser& entryParser) {
		int pos = 0;
		while (true) {
			std::string id, path;
			std::vector<Rect> rects;
			auto i = entryParser(pos, text, id, path, rects);
			assert(i >= 0);
			if (!i) return;
			pos += i;
			assert(!GetFilm(id));
			films[id] = new AnimationFilm(bitmaps.Load(path), rects, id);
		}
	}
	void AnimationFilmHolder::Load(const std::string& text, const Parser& parser) {
		std::list<AnimationFilm::Data> output;
		auto result = parser(output, text);
		assert(result);
		for (auto& entry : output) {
			assert(!GetFilm(entry.id));
			films[entry.id] = new AnimationFilm(
				bitmaps.Load(entry.path), entry.rects, entry.id
			);
		}
	}
	// .. continued
	void CleanUp(void) {
		for (auto& i : films)
			delete(i.second);
		films.clear();
	}
	auto GetFilm(const std::string& id) -> const AnimationFilm* const {
		auto i = films.find(id);
		return i != films.end() ? i->second : nullptr;
	}
};

class BitmapLoader {
private:
	using Bitmaps = std::map<std::string, Bitmap>;
	Bitmaps bitmaps;
	Bitmap GetBitmap(const std::string& path) const {
		auto i = bitmaps.find(path);
		return i != bitmaps.end() ? i->second : nullptr;
	}
public:
	Bitmap Load(const std::string& path) {
		auto b = GetBitmap(path);
		if (!b) {
			bitmaps[path] = b = BitmapLoad(path);
			assert(b);
		}
		return b;
	}
	// prefer to massively clear bitmaps at the end than
	// to destroy individual bitmaps during gameplay
	void CleanUp(void) {
		for (auto& i : bitmaps)
			BitmapDestroy(i.second);
		bitmaps.clear();
	}
	BitmapLoader(void) {}
	~BitmapLoader() { CleanUp(); }
};


#endif _KEYFRAMEANIMATIONS_H