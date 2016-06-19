// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mMetronome
//
// created: September 21, 1998
// updated: August 20, 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef _M_METRONOME_H_
#define _M_METRONOME_H_

// include files
#include <app/Application.h>
#include <MidiKit.h>
#include <KernelKit.h>
#include "mTimer.h"

// class difinitions
class mMetronome : public BLooper {

public:
					mMetronome(void);
					~mMetronome(void);
	void			Start(void);
	void			Stop(void);
	void			ChangeTempo(int32 newTempo);

private:
	virtual void	MessageReceived(BMessage *message);
	float			currentTempo;
	uint32			masterTempo;
	uint32			masterInterval;
	bool			IsRunning;

	mTimer*			fTimer;
	BSynth 			m_synth;
	BMidiSynth* 	m_pMidiSynth;
};

#endif