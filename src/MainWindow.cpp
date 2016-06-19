// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow
//
// created: September 21 1998
// updated: August 20 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "MainWindow.h"
#define TEMPOSLIDER_MODIFIED 't123'

MainWindow::MainWindow(void)
	: IEWindow("mainWindow")
{
	fMetronome = new mMetronome();
	fMetronome->Run();

	((BSlider*)FindView("tempoSlider"))->SetModificationMessage(new BMessage(TEMPOSLIDER_MODIFIED));
	((BSlider*)FindView("tempoSlider"))->SetTarget(this);

	mStartButtonStatus = false;	// BeMetro is waiting for start !
}


MainWindow::~MainWindow(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
}


// Handling of user interface and other events
void MainWindow::MessageReceived(BMessage *message)
{
//	message->PrintToStream();

	switch(message->what){
		case IE_MAINWINDOW_TEMPOSLIDER:	// 'tempoSlider' is operated...
			tempoValue = ((BSlider*)FindView("tempoSlider"))->Value();
			printf("tempo: %d\n", (int)tempoValue);
			fMetronome->ChangeTempo(tempoValue);

			sprintf(tempoText, "%3d", (int)tempoValue);
			((BStringView*)FindView("tempoValue"))->SetText(tempoText);
			break;

		case IE_MAINWINDOW_STARTBUTTON:	// 'startButton' is pressed...
			if(!mStartButtonStatus){
				((BButton*)FindView("startButton"))->SetLabel("Stop");
				fMetronome->Start();

				tempoValue = ((BSlider*)FindView("tempoSlider"))->Value();	// get tempo from slider
				printf("tempo: %d\n", (int)tempoValue);
				fMetronome->ChangeTempo(tempoValue);

				mStartButtonStatus = true;
			} else {
				((BButton*)FindView("startButton"))->SetLabel("Start");
				fMetronome->Stop();
				mStartButtonStatus = false;
			}			
			break;

		case TEMPOSLIDER_MODIFIED:	// 'tempoSlider' is modified...
			tempoValue = message->FindInt32("be:value");
			printf("tempo: %d\n", (int)tempoValue);
			sprintf(tempoText, "%3d", (int)tempoValue);
			((BStringView*)FindView("tempoValue"))->SetText(tempoText);
			break;

		default:
			inherited::MessageReceived(message);
			break;
	}
}
