
#include <anchWtch.h>
#include <navigation.h>
#include <debug.h>


// **********************************************************************
// setLocationBtn
// **********************************************************************


setLocationBtn::setLocationBtn(int xLoc,int yLoc,const char* path)
	: iconButton(xLoc,yLoc,path,60) {  }
	
	
setLocationBtn::~setLocationBtn(void) {  }
	
	
void setLocationBtn::doAction(void) {


}

	
	
// **********************************************************************
// setWatchBtn
// **********************************************************************


setWatchBtn::setWatchBtn(int xLoc,int yLoc,const char* path)
	: iconButton(xLoc,yLoc,path,60) {  }
	
	
setWatchBtn::~setWatchBtn(void) {  }
	
void setWatchBtn::doAction(void) {


}


// **********************************************************************
// anchWtchValueField
// **********************************************************************


anchWtchValueField::anchWtchValueField(rect* inRect,const char* inMsg)
	: valueField(inRect,inMsg) {  }
	
	
anchWtchValueField::~anchWtchValueField(void) {  }

/*	
void anchWtchValueField::doAction(void) {


}
*/

//void anchWtchValueField::handleCom(stdComs comID) {
	

//}


// **********************************************************************
// anchWtch
// **********************************************************************

//#define MSG_BYTES			40

#define FIELD_W			55
#define FIELD_H			28

#define DIA_X				50
#define DIA_Y				164
#define DIA_W				222 
#define DIA_H				145
#define DIA_NAME			"anchDia.bmp"

#define DEPTH_X			38
#define DEPTH_Y			320
#define DEPTH_MSG			"Depth as read from the depth sounder."

#define SCOPE_X			136
#define SCOPE_Y			80
#define SCOPE_MSG			"Scope from your settings. 1:X where this is the X value."

#define CALC_RAD_X		136
#define CALC_RAD_Y		130
#define CALC_RAD_MSG		"Calculated swing radius in feet."

#define CALC_RODE_X		160
#define CALC_RODE_Y		240
#define CALC_RAD_MSG		"Calculated amount of rode in fathoms."

#define MARGIN_X			242
#define MARGIN_Y			130
#define MARGIN_MSG		"Added distance in feet to add to the swing radius."

#define CALC_TOTAL_X		160
#define CALC_TOTAL_Y		320
#define CALC_TOTAL_MSG	"Calcualted total swing radius including your margin value in feet."

#define SET_LOC_X			37
#define SET_LOC_Y			105

#define START_WCH_X		130
#define START_WCH_Y		378

#define LOC_BTN_X			37
#define LOC_BTN_Y			100
#define LOC_BTN			"selct60y.bmp"

#define WATCH_BTN_X		130
#define WATCH_BTN_Y		378
#define WATCH_BTN			"hook60g.bmp"



anchWtch::anchWtch(int newAppID)
	: panel(newAppID) { }


anchWtch::~anchWtch(void) {  }


fontLabel* anchWtch::setupField(int inX,int inY,const char* labelTxt,double inVal,int fixVal) {

	unsigned long	multiplyer;
	char				fixStr[10];
	char				format[10];
	char				buff[40];
	
	multiplyer = pow(10,fixVal);
	inVal = inVal * multiplyer;
	round(inVal);
	inVal = inVal/multiplyer;
	strcpy(format,"%4.");
	strcat(format,itoa(fixVal,fixStr,10));
	strcat(format,"f");
	sprintf(buff,format,inVal);
	return setupField(inX,inY,labelTxt,buff);
}


fontLabel* anchWtch::setupField(int inX,int inY,const char* labelTxt,const char* inStr) {
	
	rect			frame(inX,inY,FIELD_W,FIELD_H);
	rectObj*		ourRectObj;
	fontLabel*	valueLbl;
	label*		itemlabel;
	
	ourRectObj = new rectObj(&frame);
	if (ourRectObj) {
		ourRectObj->setColor(&darkYellow);
		addObj(ourRectObj);
		itemlabel = new label(inX,inY+FIELD_H+2,FIELD_W,8);
		if (itemlabel) {
			itemlabel->setColors(&darkYellow);
			itemlabel->setValue(labelTxt);
			addObj(itemlabel);
			frame.insetRect(3);
			valueLbl = new fontLabel(&frame);
			if (valueLbl) {
				ourTxtPallette.setTypeFace(valueLbl,smallValues);
				valueLbl->setValue(inStr);
				addObj(valueLbl);
				return valueLbl;
			}
		}
	}
	return NULL;
}
	
		
void anchWtch::setup(void) {
	
	rect	frame;
	double	depth;
	double calcRode;
	double	calcRad;
	double calcTotal;
	frame.setRect(DIA_X,DIA_Y,DIA_W,DIA_H);
	
	setFilePath(DIA_NAME);
	bmpObj* theDiagram = new bmpObj(&frame,mFilePath);
	if (theDiagram) {
		addObj(theDiagram);
	}
	
	depth = 5; //ourNavigator->getDepth();
	calcRode = depth * scopeValue;
	calcRad = sqrt(abs(pow(calcRode,2) - pow(depth,2)));
	calcTotal = (calcRad*6) + anchorMargin;
	
	depthFld = setupField(DEPTH_X,DEPTH_Y,"Depth",depth,1);
	scopeFld = setupField(SCOPE_X,SCOPE_Y,"Scope",scopeValue,1);
	calcRodeFld = setupField(CALC_RODE_X,CALC_RODE_Y,"Rode",calcRode,1);
	marginFld = setupField(MARGIN_X,MARGIN_Y,"Margin",anchorMargin,0);
	totalRadiusFld = setupField(CALC_TOTAL_X,CALC_TOTAL_Y,"Swing",calcTotal,0);
	
	
	
	
	setFilePath(LOC_BTN);
	locationBtn = new setLocationBtn(LOC_BTN_X,LOC_BTN_Y,mFilePath);
	if (locationBtn) {
		addObj(locationBtn);
	}
	
	setFilePath(WATCH_BTN);
	watchBtn = new setWatchBtn(WATCH_BTN_X,WATCH_BTN_Y,mFilePath);
	if (watchBtn) {
		addObj(watchBtn);
	}
	
}


void anchWtch::loop(void) {  }


void anchWtch::drawSelf(void) { screen->fillRect(this,&black); }


void anchWtch::closing(void) {  }
	
				
			