#include "./Coin.h"
#include "../engine/AnimationFilmHolder.h"

void Coin::createSprite(int x, int y) {
	if (type == BLUE) {
		coinSprite = new Sprite(x, y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(BLUE_COIN_ID), BLUE_COIN_ID);
	}
	else {
		coinSprite = new Sprite(x, y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(BLACK_COIN_ID), BLACK_COIN_ID);
	}
	coinSprite->GetGravityHandler().SetGravityAddicted(false);
}

Sprite* Coin::GetSprite() {
	return coinSprite;
}

void Coin::SetSprite(Sprite* s) {
	coinSprite = s;
}

CoinType Coin::getType() {
	return type;
}

void Coin::setType(CoinType t) {
	type = t;
}

CoinHolder CoinHolder::holder;
auto CoinHolder::GetSingleton(void) -> CoinHolder& { return holder; }
auto CoinHolder::GetSingletonConst(void) -> const CoinHolder& { return holder; }