#ifndef _ANIMATIONFILMHOLDER_H_
#define _ANIMATIONFILMHOLDER_H_

#include "./General.h"
#include "./BitmapLoader.h"
#include "./AnimationFilm.h"

#include <vector>
#include <map>
#include <list>

class AnimationFilmHolder final {
public:
	using Parser = std::function<bool(std::list<AnimationFilm::Data>& output, const std::string& input)>;
	using EntryParser = std::function<int(// -1=error, 0=ended gracefully, else #chars read
		int startPos, const std::string& input, std::string& idOutput, std::string& pathOutput, std::vector<Rect>& rectsOutput)>;
private:
	using Films = std::map<std::string, AnimationFilm*>; //prefer to massively load films at the begining
	Films films;
	BitmapLoader bitmaps; // only for loading of film bitmaps
	static AnimationFilmHolder holder; // singleton
	
public: //giati htan private ayta?
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }

	static auto Get(void) -> const AnimationFilmHolder& { return holder; } //na paei cpp?
	//AnimationFilmHolder& Get(void) { return holder; }
	static AnimationFilmHolder& GetSingleton()
	{
		return holder;
	}

	void Load(const std::string& text, const EntryParser& entryParser);
	void Load(const std::string& text, const Parser& parser);

	//continued..
	void CleanUp(void);
	auto GetFilm(const std::string& id) -> const AnimationFilm* const;

	void printAnimationMap();
};

#endif _ANIMATIONFILMHOLDER_H_