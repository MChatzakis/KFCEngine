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

	static auto GetSingleton(void)->TileActions& {
		return singleton;
	}

	static auto GetSingletonConst(void) -> const TileActions& {
		return singleton;
	}
};

class TriggerScrollUtilities {

public:
	static void FilterGridMotion(/*GridMap**/GridLayer* m, const Rect& r, int* dx, int* dy) {
		std::list<Point> crossedTiles;

		assert(abs(*dx) <= GRID_ELEMENT_WIDTH && abs(*dy) <= GRID_ELEMENT_HEIGHT);
		// try horizontal move
		if (*dx < 0)
			FilterGridMotionLeft(m, r, dx, &crossedTiles);
		else
			if (*dx > 0)
				FilterGridMotionRight(m, r, dx, &crossedTiles);
		// try vertical move
		if (*dy < 0)
			FilterGridMotionUp(m, r, dy, &crossedTiles);
		else
			if (*dy > 0)
				FilterGridMotionDown(m, r, dy, &crossedTiles);

		for (auto& i : crossedTiles)
			TileActions::GetSingleton().Trigger(i.x, i.y);
	}

	static void FilterGridMotionLeft(GridLayer* m, const Rect& r, int* dx, std::list<Point>* crossedTiles) {
		auto x1 = r.x;
		auto x1_next = x1 + *dx;
		if (x1_next < 0)
			*dx = *dx - x1_next; //goes full left
		else {
			auto newCol = DIV_GRID_ELEMENT_WIDTH(x1_next);
			auto currCol = DIV_GRID_ELEMENT_WIDTH(x1);
			if (newCol != currCol) {
				assert(newCol + 1 == currCol); // we really move left
				auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
				auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
				std::list<Point> l;
				for (auto row = startRow; row <= endRow; ++row)
					if (!m->CanPassGridTile(newCol, row, GRID_RIGHT_SOLID_MASK)) {
						*dx = MUL_GRID_ELEMENT_WIDTH(currCol) - x1;
						//*dx = r.x - MUL_GRID_ELEMENT_WIDTH(currCol); //etsi to exei sto lecture 9
						break;
					}
					else
						l.push_back({ newCol, row });
				std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
			}
		}
	}

	static void  FilterGridMotionRight(GridLayer* m, const Rect& r, int* dx, std::list<Point>* crossedTiles) {
		auto x2 = r.x + r.w - 1;
		auto x2_next = x2 + *dx;
		if (x2_next >= MAX_PIXEL_WIDTH) {
			*dx = (MAX_PIXEL_WIDTH - 1) - x2; //goes full right
			std::cout << "kseperase to orio deksia\n";
		}
		else {
			auto newCol = DIV_GRID_ELEMENT_WIDTH(x2_next);
			auto currCol = DIV_GRID_ELEMENT_WIDTH(x2);
			if (newCol != currCol) {
				assert(newCol - 1 == currCol); // we really move right
				auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
				auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
				std::list<Point> l;
				for (auto row = startRow; row <= endRow; ++row)
					if (!m->CanPassGridTile(newCol, row, GRID_LEFT_SOLID_MASK)) {
						*dx = (MUL_GRID_ELEMENT_WIDTH(newCol) - 1) - x2; //sigoura swsta ayta ?
						//*dx = (MUL_GRID_ELEMENT_WIDTH(newCol) - 0) - x2; //sigoura swsta ayta ?
						std::cout << "synantise solid tile\n";
						l.clear();
						break;
					}
					else
						l.push_back({ newCol, row });
				std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));



			}
		}
	}

	static void  FilterGridMotionDown(GridLayer* m, const Rect& r, int* dy, std::list<Point>* crossedTiles) {
		auto y1 = r.y + r.h - 1;
		auto y1_next = y1 + *dy;
		if (y1_next >= MAX_PIXEL_HEIGHT)
			*dy = (MAX_PIXEL_HEIGHT - 1) - y1; //goes full down
		else {
			auto newRow = DIV_GRID_ELEMENT_HEIGHT(y1_next);
			auto currRow = DIV_GRID_ELEMENT_HEIGHT(y1);
			if (newRow != currRow) {
				assert(newRow == currRow + 1); // we really move down
				auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x);
				auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1);
				std::list<Point> l;
				for (auto col = startCol; col <= endCol; ++col)
					if (!m->CanPassGridTile(col, newRow, GRID_TOP_SOLID_MASK)) {
						*dy = MUL_GRID_ELEMENT_HEIGHT(newRow) - y1 - 1; //sigoura swsta ayta?
						l.clear();
						break;
					}
					else
						l.push_back({ col, newRow });
				std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
			}
		}
	}

	static void FilterGridMotionUp(GridLayer* m, const Rect& r, int* dy, std::list<Point>* crossedTiles) {
		auto y2 = r.y;
		auto y2_next = y2 + *dy;
		//auto y1_next = r.y + *dy;
		if (y2_next < 0)
			*dy = *dy - y2_next; //goes full top
		else {
			auto newRow = DIV_GRID_ELEMENT_HEIGHT(y2_next);
			auto currRow = DIV_GRID_ELEMENT_HEIGHT(y2);
			if (newRow != currRow) {
				assert(newRow == currRow - 1); // we really move up
				auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x);
				auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1);
				std::list<Point> l;
				for (auto col = startCol; col <= endCol; ++col)
					if (!m->CanPassGridTile(col, newRow, GRID_BOTTOM_SOLID_MASK)) {
						*dy = MUL_GRID_ELEMENT_HEIGHT(currRow) - y2; //sigoura swsta ayta? -1?
						l.clear();
						break;
					}
					else {
						l.push_back({ col, newRow });
					}

				std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
			}
		}
	}
};

/* TileActions */
template <typename Tfunc> void TileActions::SetEnumerator(const Tfunc& f) {
	enumerator = f;
}

template <typename Tfunc>void TileActions::Install(const std::string& tag, const Tfunc& f) {
	actions[tag] = f;
}

void TileActions::SetTag(Dim col, Dim row, const std::string& tag) {
	tags[tag].insert(enumerator(col, row));
}

void TileActions::Trigger(Dim col, Dim row) {
	auto pos = enumerator(col, row);
	for (auto& i : tags)
		if (i.second.find(pos) != i.second.end()) {
			auto j = actions.find(i.first);
			if (j != actions.end())
				j->second(col, row);
			return;
		}
}


/* TrigerScrollUtilities */


#endif _TILEACTIONS_H_
