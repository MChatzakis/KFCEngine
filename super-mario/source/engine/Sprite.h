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
#include "./KeyFrameAnimations.h"
#include "./BoundingArea.h"

//class Clipper;
class Sprite {
public:
	using Mover = std::function<void(const Rect&, int* dx, int* dy)>;
protected:
	byte frameNo = 0;
	Rect frameBox; // inside the film
	int x = 0, y = 0;
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	BoundingArea* boundingArea = nullptr;
	unsigned zorder = 0;
	std::string typeId, stateId;
	Mover mover;
	MotionQuantizer quantizer;
public:
	template <typename Tfunc>
	void SetMover(const Tfunc& f)
	{
		quantizer.SetMover(mover = f);
	}
	const Rect GetBox(void) const
	{
		return { x, y, frameBox.w, frameBox.h };
	}
	void Move(int dx, int dy)
	{
		quantizer.Move(GetBox(), &dx, &dy);
	}
	void SetPos(int _x, int _y) { x = _x; y = _y; }
	void SetZorder(unsigned z) { zorder = z; }
	unsigned GetZorder(void) { return zorder; }

	void SetFrame(byte i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());
			frameBox = currFilm->GetFrameBox(frameNo = i);
		}
	}
	byte GetFrame(void) const { return frameNo; }
	void SetBoundingArea(const BoundingArea& area)
	{
		assert(!boundingArea); boundingArea = area.Clone();
	}
	void SetBoundingArea(BoundingArea* area)
	{
		assert(!boundingArea); boundingArea = area;
	}
	auto GetBoundingArea(void) const -> const BoundingArea*
	{
		return boundingArea;
	}
	auto GetTypeId(void) -> const std::string& { return typeId; }
	void SetVisibility(bool v) { isVisible = v; }
	bool IsVisible(void) const { return isVisible; }
	bool CollisionCheck(const Sprite* s) const;
	void Display(Bitmap dest, const Rect& dpyArea, const Clipper& clipper) const;
	Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "") :
		x(_x), y(_y), currFilm(film), typeId(_typeId)
	{
		frameNo = currFilm->GetTotalFrames(); SetFrame(0);
	}

	bool directMotion = false;
	GravityHandler gravity;
	GravityHandler& GetGravityHandler(void)
	{
		return gravity;
	}
	Sprite& SetHasDirectMotion(bool v) { directMotion = true; return *this; }
	bool GetHasDirectMotion(void) const { return directMotion; }
	Sprite& Move(int dx, int dy) {
		if (directMotion) // apply unconditionally offsets!
			x += dx, y += dy;
		else {
			quantizer.Move(GetBox(), &dx, &dy);
			gravity.Check(GetBox());
		}
		return *this;
	}


};

void Sprite::Display(Bitmap dest, const Rect& dpyArea, const Clipper& clipper) const {
	Rect clippedBox;
	Point dpyPos;
	if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {
		Rect clippedFrame{
		frameBox.x + clippedBox.x,
		frameBox.y + clippedBox.y,
		clippedBox.w,
		clippedBox.h
		};
		MaskedBlit(
			currFilm->GetBitmap(),
			clippedFrame,
			dest,
			dpyPos
		);
	}
}

const Clipper MakeTileLayerClipper(TileLayer* layer) {
	return Clipper().SetView(
		[layer](void)
		{ return layer->GetViewWindow(); }
	);
}

const Sprite::Mover MakeSpriteGridLayerMover(GridLayer* gridLayer, Sprite* sprite) {
	return [gridLayer, sprite](const Rect& r, int* dx, int* dy) {
		// the r is actually awlays the sprite->GetBox():
		assert(r == sprite->GetBox());
		gridLayer->FilterGridMotion(r, dx, dy);
		if (*dx || *dy)
			sprite->SetHasDirectMotion(true).Move(*dx, *dy).SetHasDirectMotion(false);
	};
};

void PrepareSpriteGravityHandler(GridLayer* gridLayer, Sprite* sprite) {
	sprite->GetGravityHandler().SetOnSolidGround(
		[gridLayer](const Rect& r)
		{ return gridLayer->IsOnSolidGround(r); }
	);
}

//sprite->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);

#endif _SPRITE_H_