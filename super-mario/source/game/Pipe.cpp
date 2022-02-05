#include "./Pipe.h"
#include "../engine/AnimationFilmHolder.h"

Sprite* Pipe::GetSprite() {
	return sprite;
}

void Pipe::SetSprite(Sprite* s) {
	sprite = s;
}

void Pipe::SetPipeType(PipeType t) {
	type = t;
}

PipeType Pipe::GetPipeType() {
	return type;
}

void Pipe::createSprite(int x, int y) {
	

	if (type == HORIZONTAL) {
		sprite = new Sprite(x, y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(HORIZONTAL_PIPE_ID), HORIZONTAL_PIPE_ID);
	}
	else {
		sprite = new Sprite(x, y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(VERTICAL_PIPE_ID), VERTICAL_PIPE_ID);
	}

	sprite->GetGravityHandler().SetGravityAddicted(false);
}

////////////////////////////////

PipeHolder PipeHolder::holder;
auto PipeHolder::GetSingleton(void) -> PipeHolder& { return holder; }
auto PipeHolder::GetSingletonConst(void) -> const PipeHolder& { return holder; }

void PipeHolder::createPipeMap(nlohmann::json conf) {
	//1. Add vertical pipes:
	nlohmann::json vpipes = conf["pipe.Vertical"];
	for (auto pipeData : vpipes) {
		Pipe* pipe = new Pipe(pipeData["x"], pipeData["y"], VERTICAL);
		Sprite* s = pipe->GetSprite();
		Pipes[s] = pipe;

		SpriteManager::GetSingleton().Add(s);
	}

	//2. Add horizontal pipes:
	nlohmann::json hpipes = conf["pipe.Horizontal"];
	for (auto pipeData : hpipes) {
		Pipe* pipe = new Pipe(pipeData["x"], pipeData["y"], HORIZONTAL);
		Sprite* s = pipe->GetSprite();
		Pipes[s] = pipe;

		SpriteManager::GetSingleton().Add(s);
	}

}


std::map<Sprite*, Pipe*>& PipeHolder::GetPipeMap() {
	return Pipes;
}

void PipeHolder::SetCoinMap(std::map<Sprite*, Pipe*>m) {
	Pipes = std::map<Sprite*, Pipe*>(m);
}

void PipeHolder::Initialize(nlohmann::json conf) {
	createPipeMap(conf);
}

void PipeHolder::Erase(Sprite* s) {
	Pipes.erase(s);
}

std::list<Sprite*> PipeHolder::GetSpriteList() {
	std::list<Sprite*>l;
	for (auto e : Pipes) {
		l.push_back(e.first);
	}

	return l;
}