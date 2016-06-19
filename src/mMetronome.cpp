// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mMetronome
//
// created: September 21 1998
// updated: August 20 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "mMetronome.h"

int32
tempoToInterval(float tempo)
{
	return int( (float)(60.0/tempo) * 1000.0 * 1000.0 );
}


void
mMetronome::Start(void)
{
	printf("start !\n");
	IsRunning = true;
}


void
mMetronome::Stop(void)
{
	printf("stop !\n");
	IsRunning = false;
}


void
mMetronome::MessageReceived(BMessage *message)
{
//	message->PrintToStream();

	static bigtime_t time_before;
	static bigtime_t time_now;

	time_now = system_time();
	printf("time: %Ld\t%.3f\n",
	       time_now,
	       (float)((time_before - time_now)/1000.0) + masterInterval/1000.0 );
	time_before = time_now;

	if (IsRunning) {
		// play 'rim shot'
		m_pMidiSynth->NoteOn(10, 37, 100);
		snooze(200);
		m_pMidiSynth->NoteOff(10, 37, 64);
	}
}


void
mMetronome::ChangeTempo(int32 newTempo){
	masterTempo = newTempo;
	printf("new tempo = %d\n", (int)newTempo);
	masterInterval = tempoToInterval(masterTempo);
	fTimer->SetData(masterInterval);
}


mMetronome::mMetronome(void)
{
	printf("loading B_BIG_SYNTH...\n");

	status_t ret;
	ret = m_synth.LoadSynthData(B_BIG_SYNTH);
	if(ret){
		printf("LoadSynthData(B_BIG_SYNTH) failed !\n");
		be_app->PostMessage(B_QUIT_REQUESTED);
	} else {
		printf("LoadSynthData(B_BIG_SYNTH) OK !\n");
	}	
		
	m_pMidiSynth = new BMidiSynth();
	ret = m_pMidiSynth->EnableInput(true, true);
	if(ret) {
		delete m_pMidiSynth; m_pMidiSynth = NULL;
	}

	m_synth.EnableReverb(false);
	masterTempo = 120;

	masterInterval = tempoToInterval(masterTempo);
	fTimer = new mTimer(this);
	fTimer->Go();
	fTimer->SetData(masterInterval);

	IsRunning = false;
}


mMetronome::~mMetronome (void)
{
	delete m_pMidiSynth;
	delete fTimer;
}
