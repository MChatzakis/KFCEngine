#ifndef _TILEACTIONS_H_
#define _TILEACTIONS_H_

#include <iostream>
#include <functional>
#include <list>
#include <map>

#include "./GridLayer.h"
#include "./TileLayer.h"

class TileLayer;

class TileActions {
public:
	using Action = std::function<void(Dim col, Dim row)>;

	// (row,col)->unique tile number (in terrain map)
	using Enumerator = std::function<unsigned(Dim col, Dim row)>;
private:
	using Actions = std::map<std::string, Action>;
	using Tags = std::map<std::string, std::set<unsigned>>;

	Actions actions;
	Tags tags;
	Enumerator enumerator;

	static TileActions singleton;

public:
	template <typename Tfunc> void SetEnumerator(const Tfunc& f);
	template <typename Tfunc>void Install(const std::string& tag, const Tfunc& f);

	void SetTag(Dim col, Dim row, const std::string& tag);
	void Trigger(Dim col, Dim row);

	static auto GetSingleton(void)->TileActions&;

	static auto GetSingletonConst(void) -> const TileActions&;
};



class TriggerScrollUtilities {

public:
	static void FilterGridMotion(/*GridMap**/GridLayer* m, const Rect& r, int* dx, int* dy);

	static void FilterGridMotionLeft(GridLayer* m, const Rect& r, int* dx, std::list<Point>* crossedTiles);

	static void  FilterGridMotionRight(GridLayer* m, const Rect& r, int* dx, std::list<Point>* crossedTiles);

	static void  FilterGridMotionDown(GridLayer* m, const Rect& r, int* dy, std::list<Point>* crossedTiles);

	static void FilterGridMotionUp(GridLayer* m, const Rect& r, int* dy, std::list<Point>* crossedTiles);
};


#endif _TILEACTIONS_H_
