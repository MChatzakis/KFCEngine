#include "./AnimationFilmHolder.h"

AnimationFilmHolder AnimationFilmHolder::holder; // singleton

void AnimationFilmHolder::CleanUp(void) {
	for (auto& i : films)
		delete(i.second);
	films.clear();
}

auto AnimationFilmHolder::GetFilm(const std::string& id) -> const AnimationFilm* const {
	auto i = films.find(id);
	return i != films.end() ? i->second : nullptr;
}

void AnimationFilmHolder::Load(const std::string& text, const EntryParser& entryParser) {
	int pos = 0;
	while (true) {
		std::string id, path;
		std::vector<Rect> rects;

		auto i = entryParser(pos, text, id, path, rects);

		assert(i >= 0);
		if (!i)
			return;

		pos += i;

		assert(!GetFilm(id));
		films[id] = new AnimationFilm(bitmaps.Load(path), rects, id);
	}
}

void AnimationFilmHolder::Load(const std::string& text, const Parser& parser) {
	std::list<AnimationFilm::Data> output;

	auto result = parser(output, text);
	assert(result);

	//std::cout <<"Outputsize: " <<output..size() << "\n";

	for (auto& entry : output) {
		assert(!GetFilm(entry.id));
		//std::cout << "Rectssize: " << entry.rects.size() << "\n";
		films[entry.id] = new AnimationFilm(bitmaps.Load(entry.path), entry.rects, entry.id);
	}
}

void AnimationFilmHolder::printAnimationMap() {
	for (std::map<std::string, AnimationFilm*>::const_iterator it = films.begin(); it != films.end(); ++it) {
		//std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
		std::cout << "{ " << it->first << "->" << it->second->toString() << "}\n";
	}
}
