#ifndef anchWtch_h
#define anchWtch_h

#include	<lilOS.h>
#include <fontLabel.h>
#include <dispTools.h>
#include <navPrefs.h>


// **********************************************************************
// setLocationBtn
// **********************************************************************


class setLocationBtn :	public iconButton {

	public:
				setLocationBtn(int xLoc,int yLoc,const char* path);
	virtual	~setLocationBtn(void);
	
	virtual	void	doAction(void);
};
	
	
	
// **********************************************************************
// setWatchBtn
// **********************************************************************


class setWatchBtn :	public iconButton {

	public:
				setWatchBtn(int xLoc,int yLoc,const char* path);
	virtual	~setWatchBtn(void);
	
	virtual	void	doAction(void);
};


// **********************************************************************
// anchWtchValueField
// **********************************************************************


class anchWtchValueField :	public valueField {

	public:
				anchWtchValueField(rect* inRect,const char* inMsg);
	virtual	~anchWtchValueField(void);
	
	//virtual	void	doAction(void);
	//virtual	void	handleCom(stdComs comID);
};


// **********************************************************************
// anchWtch
// **********************************************************************
#include <rectObj.h>

class anchWtch :	public panel {

	public:
				anchWtch(int newAppID);
	virtual	~anchWtch(void);
	
				erasableText*	setupField(int inX,int inY,const char* labelTxt);
	virtual	void				setup(void);		// Run once. do your setup here.
	virtual	void				loop(void);			// Run over and over. Do stuff here.
	virtual	void				drawSelf(void);	// If you want to draw your background, do it here.
	virtual	void				closing(void);		// Need to save anything before closing shop? Do it here.
				void				calculateItems(void);
				
				erasableText*	depthFld;
				erasableText*	scopeFld;
				erasableText*	calcRodeFld;
				erasableText*	marginFld;
				erasableText*	calcRadiusFld;
				erasableText*	totalRadiusFld;
				
				double	depth;
				double	calcRode;
				double	calcRad;
				double	calcTotal;
	
				setLocationBtn*		locationBtn;
				setWatchBtn*			watchBtn;
				bool						editing;
};
				

#endif