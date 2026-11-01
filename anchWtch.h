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
// watchField
// **********************************************************************

enum paramChoice {
	
	noParam,
	depthParam,
	scopeParam,
	rodeParam,
	radiusParam,
	marginParam,
	swingParam
};


class watchField :	public valueField {

	public:
				watchField(rect* inRect,valueType inType,const char* inMsg);
	virtual	~watchField(void);
	
				void		seType(paramChoice inParam);
	virtual	void		updateValue(const char* newValue);
	
				paramChoice	ourType;
};


// **********************************************************************
// anchWtch
// **********************************************************************
#include <rectObj.h>

class anchWtch :	public panel {

	public:
				anchWtch(int newAppID);
	virtual	~anchWtch(void);
	
				watchField*	setupField(int inX,int inY,const char* labelTxt,const char* inMsg);
	virtual	void			setup(void);		// Run once. do your setup here.
	virtual	void			loop(void);			// Run over and over. Do stuff here.
	virtual	void			drawSelf(void);	// If you want to draw your background, do it here.
	virtual	void			closing(void);		// Need to save anything before closing shop? Do it here.
				void			calculateItems(void);
				
				watchField*	depthFld;
				watchField*	scopeFld;
				watchField*	calcRodeFld;
				watchField*	marginFld;
				watchField*	calcRadiusFld;
				watchField*	totalRadiusFld;
				
				float	depth;
				float	calcRode;
				float	calcRad;
				float	calcTotal;
	
				setLocationBtn*	locationBtn;
				setWatchBtn*		watchBtn;
};
				

#endif