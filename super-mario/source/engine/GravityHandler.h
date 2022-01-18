#ifndef _GRAVITYHANDLER_H_
#define _GRAVITYHANDLER_H_

#include <iostream>
#include <functional>

#include "./General.h"

class GravityHandler
{
public:
	using OnSolidGroundPred = std::function<bool(const Rect &)>;
	using OnStartFalling = std::function<void(void)>;
	using OnStopFalling = std::function<void(void)>;

protected:
	bool gravityAddicted = false;
	bool isFalling = false;

	OnSolidGroundPred onSolidGround;
	OnStartFalling onStartFalling;
	OnStopFalling onStopFalling;

public:
	/*
	template <typename T>
	void SetOnStartFalling(const OnSolidGroundPred &f);
	template <typename T>
	void SetOnStopFalling(const T &f);
	template <typename T>
	void SetOnSolidGround(const T &f);
	*/

	void SetOnStartFalling(const OnStartFalling& f);
	void SetOnStopFalling(const OnStopFalling& f);
	void SetOnSolidGround(const OnSolidGroundPred& f);
	void Reset(void);
	void Check(const Rect &r);
};


#endif _GRAVITYHANDLER_H_