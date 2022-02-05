#ifndef _PIPE_H_
#define _PIPE_H_

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"

#include <iostream>
#include <map>
#include <nlohmann/json.hpp>


#define VERTICAL_PIPE_ID "pipe.vertical"
#define HORIZONTAL_PIPE_ID "pipe.horizontal"

enum PipeType {
	VERTICAL,
	HORIZONTAL
};

class Pipe {
private:
	Sprite* sprite = nullptr;
	PipeType type;

	void createSprite(int x, int y);
public:
	Sprite* GetSprite();
	void SetSprite(Sprite* s);

	PipeType GetPipeType();
	void SetPipeType(PipeType _t);

	Pipe(int x, int y, PipeType t) {
		type = t;
		createSprite(x, y);
	}
};

class PipeHolder {
private:
	static PipeHolder holder;
	std::map<Sprite*, Pipe*>Pipes;
public:
	static auto GetSingleton(void)->PipeHolder&;
	static auto GetSingletonConst(void) -> const PipeHolder&;

	void createPipeMap(nlohmann::json conf);

	std::map<Sprite*, Pipe*>& GetPipeMap();

	void SetCoinMap(std::map<Sprite*, Pipe*>m);

	void Initialize(nlohmann::json conf);

	void Erase(Sprite* s);

	std::list<Sprite*> GetSpriteList();
};

#endif _PIPE_H_