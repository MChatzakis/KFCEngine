#include "./Animator.h"

bool
Animator::HasFinished(void) const { return state != ANIMATOR_RUNNING; }

void
Animator::Finish(bool isForced) {
	if (!HasFinished()) {
		state = isForced ? ANIMATOR_STOPPED : ANIMATOR_FINISHED;
		NotifyStopped();
	}
}

void
Animator::Stop(void)
{
	Finish(true);
}

void
Animator::NotifyStarted(void) {
	if (onStart)
		(onStart)(this);
}

void
Animator::NotifyStopped(void) {
	if (onFinish)
		(onFinish)(this);
}

void
Animator::NotifyAction(const Animation& anim) {
	if (onAction)
		(onAction)(this, anim);
}

void
Animator::TimeShift(timestamp_t offset)
{
	lastTime += offset;
}

template <typename Tfunc> void
Animator::SetOnFinish(const Tfunc& f) { onFinish = f; }

template <typename Tfunc> void
Animator::SetOnStart(const Tfunc& f) { onStart = f; }

template <typename Tfunc> void
Animator::SetOnAction(const Tfunc& f) { onAction = f; }