#ifndef _TILEACTIONS_H_
#define _TILEACTIONS_H_

#include <iostream>
#include <functional>
#include <list>
#include <map>

#include "../TypeDefinitions.h"
#include "./Tilemap.h"
#include "./Grid.h"

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
	template <typename Tfunc>
	void SetEnumerator(const Tfunc& f)
	{
		enumerator = f;
	}
	template <typename Tfunc>
	void Install(const std::string& tag, const Tfunc& f)
	{
		actions[tag] = f;
	}
	void SetTag(Dim col, Dim row, const std::string& tag)
	{
		tags[tag].insert(enumerator(col, row));
	}
	void Trigger(Dim col, Dim row) {
		auto pos = enumerator(col, row);
		for (auto& i : tags)
			if (i.second.find(pos) != i.second.end()) {
				auto j = actions.find(i.first);
				if (j != actions.end())
					j->second(col, row);
				return;
			}
	}
	static auto GetSingleton(void) -> TileActions&
	{
		return singleton;
	}
	static auto GetSingletonConst(void) -> const TileActions&
	{
		return singleton;
	}
};

void FilterGridMotionLeft(GridMap* m, const Rect& r, int* dx, std::list<Point>* crossedTiles) {

	std::list<Point> l;
	for (auto row = startRow; row <= endRow; ++row)
		if (!CanPassGridTile(m, newCol, row, GRID_RIGHT_SOLID_MASK)) {
			*dx = r.x - MUL_GRID_ELEMENT_WIDTH(currCol);
			l.clear();
			break;
		}
		else
			l.push_back({ newCol, row });
	std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
}
void FilterGridMotion(GridMap* m, const Rect& r, int* dx, int* dy) {
	std::list<Point> crossedTiles;

	for (auto& i : crossedTiles)
		TileActions::GetSingleton().Trigger(i.x, i.y);
}

#endif _TILEACTIONS_H_
