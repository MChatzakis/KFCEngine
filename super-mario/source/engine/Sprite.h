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
	template <typename Tfunc> void SetMover(const Tfunc& f);

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

template <typename Tfunc> void  Sprite::SetMover(const Tfunc& f) {
	quantizer.SetMover(mover = f);
}

const Rect  Sprite::GetBox(void) const {
	return { x, y, frameBox.w, frameBox.h };
}

void  Sprite::MoveOLD(int dx, int dy) {
	quantizer.Move(GetBox(), &dx, &dy);
}

void  Sprite::SetPos(int _x, int _y) {
	x = _x; y = _y;
}

void  Sprite::SetZorder(unsigned z) {
	zorder = z;
}

unsigned  Sprite::GetZorder(void) {
	return zorder;
}

void  Sprite::SetFrame(byte i) {
	if (i != frameNo) {
		assert(i < currFilm->GetTotalFrames());
		frameBox = currFilm->GetFrameBox(frameNo = i);
	}
}

byte  Sprite::GetFrame(void) const {
	return frameNo;
}

void  Sprite::SetBoundingArea(const BoundingArea& area)
{
	assert(!boundingArea); boundingArea = area.Clone();
}

void  Sprite::SetBoundingArea(BoundingArea* area)
{
	assert(!boundingArea); boundingArea = area;
}

auto  Sprite::GetBoundingArea(void) const -> const BoundingArea*
{
	return boundingArea;
}

auto  Sprite::GetTypeId(void) -> const std::string& {
	return typeId;
}

void  Sprite::SetVisibility(bool v) {
	isVisible = v;
}

bool  Sprite::IsVisible(void) const {
	return isVisible;
}

Sprite::Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "") : x(_x), y(_y), currFilm(film), typeId(_typeId) {
	frameNo = currFilm->GetTotalFrames(); SetFrame(0);
}

GravityHandler& Sprite::GetGravityHandler(void)
{
	return gravity;
}

Sprite& Sprite::SetHasDirectMotion(bool v) {
	directMotion = true;
	return *this;
}

bool  Sprite::GetHasDirectMotion(void) const {
	return directMotion;
}

Sprite& Sprite::Move(int dx, int dy) {
	if (directMotion) // apply unconditionally offsets!
		x += dx, y += dy;
	else {
		quantizer.Move(GetBox(), &dx, &dy);
		gravity.Check(GetBox());
	}
	return *this;
}


//sprite->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);

#endif _SPRITE_H_