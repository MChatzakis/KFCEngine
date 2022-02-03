#include "./Coin.h"
#include "../engine/AnimationFilmHolder.h"

void Coin::createSprite(int x, int y) {
	coinSprite = new Sprite(x, y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(COIN_ID), COIN_ID);
	coinSprite->GetGravityHandler().SetGravityAddicted(false);
}

Sprite* Coin::GetSprite() {
	return coinSprite;
}

void Coin::SetSprite(Sprite* s) {
	coinSprite = s;
}

CoinHolder CoinHolder::holder;
auto CoinHolder::GetSingleton(void) -> CoinHolder& { return holder; }
auto CoinHolder::GetSingletonConst(void) -> const CoinHolder& { return holder; }