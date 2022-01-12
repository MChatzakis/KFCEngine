#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <iostream>
#include <functional>

#include "./Animation.h"
#include "./DestructionManager.h"

typedef uint64_t timestamp_t;
enum animatorstate_t {
	ANIMATOR_FINISHED = 0, ANIMATOR_RUNNING = 1, ANIMATOR_STOPPED = 2
};

class Animator : public LatelyDestroyable  {
public:
	using OnFinish = std::function<void(Animator*)>;
	using OnStart = std::function<void(Animator*)>;
	using OnAction = std::function<void(Animator*, const Animation&)>;
protected:
	timestamp_t lastTime = 0;
	animatorstate_t state = ANIMATOR_FINISHED;
	OnFinish onFinish;
	OnStart onStart;
	OnAction onAction;

	void NotifyStopped(void);
	void NotifyStarted(void);
	void NotifyAction(const Animation&);
	void Finish(bool isForced = false);
public:
	void Stop(void);
	bool HasFinished(void) const { return state != ANIMATOR_RUNNING; }
	
	virtual void TimeShift(timestamp_t offset);
	virtual void Progress(timestamp_t currTime) = 0;
	
	template <typename Tfunc> void SetOnFinish(const Tfunc& f) { onFinish = f; }
	template <typename Tfunc> void SetOnStart(const Tfunc& f) { onStart = f; }
	template <typename Tfunc> void SetOnAction(const Tfunc& f) { onAction = f; }

	Animator(void);
	Animator(const Animator&) = delete;
	Animator(Animator&&) = delete;
	virtual ~Animator() {}

};

void Animator::Finish(bool isForced) {
	if (!HasFinished()) {
		state = isForced ? ANIMATOR_STOPPED : ANIMATOR_FINISHED;
		NotifyStopped();
	}
}
void Animator::Stop(void)
{
	Finish(true);
}
void Animator::NotifyStopped(void) {
	if (onFinish)
		(onFinish)(this);
}
void Animator::NotifyAction(const Animation& anim) {
	if (onAction)
		(onAction)(this, anim);
}
void Animator::TimeShift(timestamp_t offset)
{
	lastTime += offset;
}

#endif _ANIMATOR_H_
