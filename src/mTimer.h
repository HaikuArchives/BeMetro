// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mTimer
//
// created: September 21 1998
// updated: August 20 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef _MTIMER_H_
#define _MTIMER_H_

#include <app/Looper.h>
#include <kernel/OS.h>
#include <support/Autolock.h>

class mTimer : public BLooper {
public:
	mTimer(BHandler *client);
	virtual ~mTimer(void);
	status_t	Go(void);
	status_t	SetData(int32 code);
	int32		GetCounter(void);
	void		ResetCounter(void);

protected:
	BLocker		mLocker;
	int32		mCounter;
	int32		tAverage;
	int32		mInterval;
	BLooper		*mTarget;
	BHandler	*mClient;

private:
	static int32 thread_func(void *arg);
	int32 threadFunc(void);
	thread_id m_thread;
};

#endif
