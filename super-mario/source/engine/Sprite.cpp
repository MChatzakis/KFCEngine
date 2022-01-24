#include "./Sprite.h"
#include "./TileActions.h"

const Clipper MakeTileLayerClipper(TileLayer* layer) {
	return Clipper().SetView(
		[layer](void)
		{ return layer->GetViewWindow(); }
	);
}

void PrepareSpriteGravityHandler(GridLayer* gridLayer, Sprite* sprite) {
	sprite->GetGravityHandler().SetOnSolidGround(
		[gridLayer](const Rect& r)
		{ return gridLayer->IsOnSolidGround(r); }
	);
}

void Sprite::Display(Bitmap dest, const Rect& dpyArea, const Clipper& clipper) const {
	Rect clippedBox;
	Point dpyPos;
	if (clipper.Clip(GetBox(), dpyArea, &dpyPos, &clippedBox)) {
		Rect clippedFrame{ frameBox.x + clippedBox.x,frameBox.y + clippedBox.y,clippedBox.w,clippedBox.h };
		MaskedBlit(currFilm->GetBitmap(), clippedFrame, dest, dpyPos);
	}
}

void Sprite::Display(Bitmap dest) {
	//Rect clippedFrame{ frameBox.x ,frameBox.y , frameBox.w,frameBox.h };
	Bitmap src = currFilm->GetBitmap();
	//std::cout << "FrameBox : " << frameBox.toString() << "\n";
	//std::cout << "(x,y) : (" << x << "," << y << ")\n";
	//std::cout << "Src :" << (int)src << "\n";
	//BitmapBlit(src, Rect(100,100,100,100), dest, Point(x, y));
	//MaskedBlit(currFilm->GetBitmap(), frameBox, dest, Point(x,y));
	BitmapBlit(src, frameBox, dest, Point(x, y));
}

const Sprite::Mover MakeSpriteGridLayerMover(GridLayer* gridLayer, Sprite* sprite) {
	return [gridLayer, sprite](const Rect& r, int* dx, int* dy) {
		// the r is actually always the sprite->GetBox():
		assert(r == sprite->GetBox());
		std::cout << "dx before: " << *dx << "\n";
		gridLayer->FilterGridMotion(r, dx, dy);
		std::cout << "dx after: " << *dx << "\n";
		//TriggerScrollUtilities::FilterGridMotion(gridLayer, r, dx, dy);
		if (*dx || *dy)
			sprite->SetHasDirectMotion(true).Move(*dx, *dy).SetHasDirectMotion(false);
		//sprite->Move(*dx, *dy);
	};
};

/*template <typename Tfunc>*/ void Sprite::SetMover(const Mover& f) {
	quantizer.SetMover(mover = f);
}

const Rect Sprite::GetBox(void) const {
	return { x, y, frameBox.w, frameBox.h };
}

void Sprite::MoveOLD(int dx, int dy) {
	quantizer.Move(GetBox(), &dx, &dy);
}

void  Sprite::SetPos(int _x, int _y) {
	x = _x; y = _y;
}

void Sprite::SetZorder(unsigned z) {
	zorder = z;
}

unsigned Sprite::GetZorder(void) {
	return zorder;
}

void Sprite::SetFrame(byte i) {
	if (i != frameNo) {
		assert(i < currFilm->GetTotalFrames());
		frameBox = currFilm->GetFrameBox(frameNo = i);
	}
}

byte Sprite::GetFrame(void) const {
	return frameNo;
}

void Sprite::SetBoundingArea(const BoundingArea& area)
{
	assert(!boundingArea); boundingArea = area.Clone();
}

void Sprite::SetBoundingArea(BoundingArea* area)
{
	assert(!boundingArea); boundingArea = area;
}

auto Sprite::GetBoundingArea(void) const -> const BoundingArea*
{
	return boundingArea;
}

auto Sprite::GetTypeId(void) -> const std::string& {
	return typeId;
}

auto Sprite::GetStateId(void) -> const std::string&
{
	return stateId;
}

void Sprite::SetStateId(std::string _stateId)
{
	stateId = _stateId;
}

void Sprite::SetVisibility(bool v) {
	isVisible = v;
}

bool Sprite::IsVisible(void) const {
	return isVisible;
}

Sprite::Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId) : x(_x), y(_y), currFilm(film), typeId(_typeId) {
	frameNo = currFilm->GetTotalFrames();
	SetFrame(0);
}

void Sprite::SetAnimationFilm(AnimationFilm* film) {
	currFilm = film;
	frameNo = currFilm->GetTotalFrames();
	SetFrame(0);
}

AnimationFilm* Sprite::GetAnimationFilm()
{
	return currFilm;
}

void Sprite::ChangeAnimationFilm(AnimationFilm* film, const std::string& _typeId) {
	typeId = _typeId;
	SetAnimationFilm(film);
}

GravityHandler& Sprite::GetGravityHandler(void)
{
	return gravity;
}

Sprite& Sprite::SetHasDirectMotion(bool v) {
	directMotion = v;
	return *this;
}

bool Sprite::GetHasDirectMotion(void) const {
	return directMotion;
}

Sprite& Sprite::Move(int dx, int dy) {
	if (directMotion) // apply unconditionally offsets!
		x += dx, y += dy;
	else {
		quantizer.Move(GetBox(), &dx, &dy);
		//gravity.Check(GetBox());
	}
	return *this;
}

//sprite->SetHasDirectMotion(true).Move(dx, dy).SetHasDirectMotion(false);

bool Sprite::CollisionCheck(const Sprite* s) const {
	return this->boundingArea->Intersects(*(s->boundingArea));
}

MotionQuantizer& Sprite::GetQuantizer() {
	return quantizer;
}
