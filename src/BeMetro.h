// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// BeMetro
//
// created: September 21, 1998
// updated: August 20, 1999
// author : Shigeru Kobayashi (kotobuki@rinc.or.jp)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef _BE_METRO_H_
#define _BE_METRO_H_

// include files
#include "IEApplication.h"
#include <MidiKit.h>

// class difinitions
class myApp : public IEApplication {
public:
	myApp(void);
	~myApp(void);

private:
	void	ReadyToRun(void);
};

#endif // _BE_METRO_H_
