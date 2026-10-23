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
	
				fontLabel*	setupField(int inX,int inY,const char* labelTxt,double inVal,int fixVal);
				fontLabel*	setupField(int inX,int inY,const char* labelTxt,const char* inStr);
	virtual	void			setup(void);		// Run once. do your setup here.
	virtual	void			loop(void);			// Run over and over. Do stuff here.
	virtual	void			drawSelf(void);	// If you want to draw your background, do it here.
	virtual	void			closing(void);		// Need to save anything before closing shop? Do it here.
	
				//anchWtchValueField*	depthFld;
				//anchWtchValueField*	scopeFld;
				//anchWtchValueField*	calcRodeFld;
				//anchWtchValueField*	marginFld;
				//anchWtchValueField*	calcRadiusFld;
				//anchWtchValueField*	totalRadiusFld;
				
				fontLabel*	depthFld;
				fontLabel*	scopeFld;
				fontLabel*	calcRodeFld;
				fontLabel*	marginFld;
				fontLabel*	calcRadiusFld;
				fontLabel*	totalRadiusFld;
				
				setLocationBtn*		locationBtn;
				setWatchBtn*			watchBtn;
				bool						editing;
};
				

#endif