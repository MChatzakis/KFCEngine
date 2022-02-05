#ifndef _COIN_H_
#define _COIN_H_

#include <iostream>
#include <map>

#include <nlohmann/json.hpp>

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"

#define COIN_ID "coin.blueBG"

class Coin {
private:
	Sprite* coinSprite = nullptr;

	void createSprite(int x, int y);

public: 

	Sprite* GetSprite();
	void SetSprite(Sprite* s);

	Coin(int x, int y) {
		createSprite(x, y);
	}

};

class CoinHolder {
private:
	static CoinHolder holder;
	std::map<Sprite*, Coin*>Coins;

public:
	static auto GetSingleton(void)->CoinHolder&;
	static auto GetSingletonConst(void) -> const CoinHolder&;

	void createCoinMap(nlohmann::json conf) {
		nlohmann::json coinArr = conf["coins"];
		for (auto coinData : coinArr) {
			Coin* CoinC = new Coin(coinData["x"], coinData["y"]);
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