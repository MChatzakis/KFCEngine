#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <iostream>
#include <functional>

#include <assert.h>

#include "./General.h"
#include "./MotionQuantizer.h"
#include "./Clipper.h"
#include "./TileLayer.h"
#include "./GridLayer.h"
#include "./GravityHandler.h"
//#include "./KeyFrameAnimations.h"
#include "./AnimationFilm.h"
#include "./BoundingArea.h"

class Sprite {
public:
	using Mover = std::function<void(const Rect&, int* dx, int* dy)>;

protected:
	int x = 0, y = 0;
	bool isVisible = false;
	unsigned zorder = 0;

	std::string typeId, stateId;

	byte frameNo = 0;
	Rect frameBox; // inside the film

	AnimationFilm* currFilm = nullptr;
	BoundingArea* boundingArea = nullptr;

	Mover mover;
	MotionQuantizer quantizer;

	bool directMotion = false;
	GravityHandler gravity;

public:
	/*template <typename Tfunc>*/ void SetMover(const Mover& f);
	const Rect GetBox(void) const;
	void MoveOLD(int dx, int dy);
	void SetPos(int _x, int _y);
	void SetZorder(unsigned z);
	unsigned GetZorder(void);
	void SetFrame(byte i);
	byte GetFrame(void) const;
	void SetBoundingArea(const BoundingArea& area);
	void SetBoundingArea(BoundingArea* area);
	auto GetBoundingArea(void) const -> const BoundingArea*;
	auto GetTypeId(void) -> const std::string&;
	void SetVisibility(bool v);
	bool IsVisible(void) const;
	bool CollisionCheck(const Sprite* s) const;
	void Display(Bitmap dest, const Rect& dpyArea, const Clipper& clipper) const;
	Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "");
	GravityHandler& GetGravityHandler(void);
	Sprite& SetHasDirectMotion(bool v);
	bool GetHasDirectMotion(void) const;
	Sprite& Move(int dx, int dy);
	void Display(Bitmap dest);
	MotionQuantizer& GetQuantizer();
};

const Clipper MakeTileLayerClipper(TileLayer* layer);

void PrepareSpriteGravityHandler(GridLayer* gridLayer, Sprite* sprite);

const Sprite::Mover MakeSpriteGridLayerMover(GridLayer* gridLayer, Sprite* sprite);

#endif _SPRITE_H_