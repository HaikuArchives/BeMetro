// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow
//
// created: September 21 1998
// updated: August 20 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "IEWindow.h"
#include "MainWindowDefs.h"
#include "mMetronome.h"


class MainWindow : public IEWindow
{
public:
	MainWindow(void);
	~MainWindow(void);

private:
	virtual void	MessageReceived(BMessage *message);

	char			tempoText[4];
	bool			mStartButtonStatus;
	int32			tempoValue;
	mMetronome*		fMetronome;
};

#endif
