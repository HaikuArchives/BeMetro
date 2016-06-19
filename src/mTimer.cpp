// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mTimer
//
// created: September 21 1998
// updated: August 20 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdio.h>
#include "mTimer.h"

mTimer::mTimer(BHandler *client)
{
	mClient = client;
	mTarget = mClient->Looper();

	/* set default timer interval to 1 msec. */
	mInterval = 1000;
}

mTimer::~mTimer(void)
{
	/* do something here */
}


int32
mTimer::thread_func(void *arg)
{
	mTimer *obj = (mTimer *)arg;
	return (obj->threadFunc());
}


int32
mTimer::threadFunc(void)
{
	thread_id	sender;
	int32		code;
	char		buf[512];
	bool		sts;

	bigtime_t   time = system_time();
	mCounter = 0;

	while (true) {
		/* Be careful, if you are using B_REAL_TIME_PRIORITY ! */

		tAverage += system_time() - time;

		if (has_data(find_thread(NULL))) {
			code = receive_data(&sender, (void *)buf, sizeof(buf));
			printf("receive_data:data %d\n", (int)code);
			mInterval = code;
		}
		BAutolock  autolock(mLocker);
		time += mInterval;
		snooze_until(time, B_SYSTEM_TIMEBASE);

		int32	resolution;
		resolution = 1;

		/* resolution = 1:1 */
		if (mCounter%resolution == 0) {

			printf("running: %ld\t%Ld\n", mCounter, system_time());

			BMessage *message = new BMessage();
			message->what = '1234';
			message->AddInt32("tick", mCounter);
			sts = mTarget->PostMessage(message, mClient);
			if (sts != B_OK) {
				printf("error: this->PostMessage\n");
			}
		}

		mCounter++;
	}

	return B_OK;
}


status_t
mTimer::Go(void)
{
	m_thread = spawn_thread(thread_func, "timer", B_REAL_TIME_PRIORITY, this);
	printf("go\n");
	return(resume_thread(m_thread));
}


status_t
mTimer::SetData(int32 code)
{
	bool sts;
	sts = send_data(m_thread, code, NULL, 0);
	printf("sts:%d\n", sts);
	return (sts == B_NO_ERROR) ? B_OK:B_ERROR;
}


int32
mTimer::GetCounter(void)
{
	return mCounter;
}


void
mTimer::ResetCounter(void)
{
	mCounter = 0;
}
