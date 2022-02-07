#ifndef _COIN_H_
#define _COIN_H_

#include <iostream>
#include <map>

#include <nlohmann/json.hpp>

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"

#define BLUE_COIN_ID "coin.blueBG"
#define BLACK_COIN_ID "coin.blackBG"

enum CoinType {
	BLUE,
	BLACK
};

class Coin {
private:
	Sprite* coinSprite = nullptr;
	CoinType type = BLUE;
	void createSprite(int x, int y);

public: 

	Sprite* GetSprite();
	void SetSprite(Sprite* s);

	Coin(int x, int y, CoinType t) {
		type = t;
		createSprite(x, y);
	}

	CoinType getType();
	void setType(CoinType t);

};

class CoinHolder {
private:
	static CoinHolder holder;
	std::map<Sprite*, Coin*>Coins;

public:
	static auto GetSingleton(void)->CoinHolder&;
	static auto GetSingletonConst(void) -> const CoinHolder&;

	void createCoinMap(nlohmann::json conf) {
		nlohmann::json coinArr = conf["coins.blue"];
		for (auto coinData : coinArr) {
			Coin* CoinC = new Coin(coinData["x"], coinData["y"], BLUE);
			Sprite* s = CoinC->GetSprite();
			
			Coins[s] = CoinC;

			SpriteManager::GetSingleton().Add(s);
		}

		coinArr = conf["coins.black"];
		for (auto coinData : coinArr) {
			Coin* CoinC = new Coin(coinData["x"], coinData["y"], BLACK);
			Sprite* s = CoinC->GetSprite();

			Coins[s] = CoinC;

			SpriteManager::GetSingleton().Add(s);
		}

	}

	std::map<Sprite*, Coin*>& GetCoinMap() {
		return Coins;
	}

	void SetCoinMap(std::map<Sprite*, Coin*>m) {
		Coins = std::map<Sprite*, Coin*>(m);
	}

	void Initialize(nlohmann::json conf) {
		createCoinMap(conf);
	}

	void Erase(Sprite* s) {
		Coins.erase(s);
	}

	std::list<Sprite*> GetSpriteList() {
		std::list<Sprite*>l;
		for (auto e : Coins) {
			l.push_back(e.first);
		}
		return l;
	}

};

#endif _COIN_H_