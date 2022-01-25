#include "./GravityHandler.h"

/*template <typename T>
void GravityHandler::SetOnStartFalling(const OnSolidGroundPred& f)
{
	onStartFalling = f;
}

template <typename T>
void GravityHandler::SetOnStopFalling(const T& f)
{
	onStopFalling = f;
}

template <typename T>
void GravityHandler::SetOnSolidGround(const T& f)
{
	onSolidGround = f;
}
*/

void GravityHandler::SetOnStartFalling(const GravityHandler::OnStartFalling& f)
{
	onStartFalling = f;
}

void GravityHandler::SetOnStopFalling(const GravityHandler::OnStopFalling& f)
{
	onStopFalling = f;
}

void GravityHandler::SetOnSolidGround(const GravityHandler::OnSolidGroundPred& f)
{
	onSolidGround = f;
}

void GravityHandler::Reset(void) { isFalling = false; }

void GravityHandler::Check(const Rect& r)
{
	if (gravityAddicted)
	{
		std::cout << "Mario is gravity addicted\n";
		if (onSolidGround(r))
		{
			if (isFalling)
			{
				isFalling = false;
				onStopFalling();
			}
		}
		else if (!isFalling)
		{
			isFalling = true;
			onStartFalling();
		}
	}
}

void GravityHandler::SetGravityAddicted(bool g) {
	gravityAddicted = g;
}

bool GravityHandler::GetGravityAddicted() {
	return gravityAddicted;
}

bool GravityHandler::IsFalling() {
	return isFalling;
}