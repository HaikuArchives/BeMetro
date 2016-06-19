// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// BeMetro
//
// created: September 21, 1998
// updated: August 20, 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// include files
#include "BeMetro.h"
#include "mMetronome.h"
#include "MainWindow.h"

IEResourceHandler *resourcehandler;

// public functions
int
main (void)
{
	myApp	appObj;	
	appObj.Run();	
	return 0;
}


myApp::myApp (void)
	: IEApplication("application/x-vnd.kotobuki-BeMetro")
{
	/* do something here */
}

myApp::~myApp (void)
{
	/* do something here */
}


// private functions
void
myApp::ReadyToRun (void)
{
	/* open Main Window */
	MainWindow* eWindow = new MainWindow();
	eWindow->Show();
	
	return;
}
