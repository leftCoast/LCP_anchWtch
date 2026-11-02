
#include <anchWtch.h>
#include <navOS.h>
#include <navigation.h>
#include <debug.h>

#define ANCHOR_X	60
#define ANCHOR_Y	16


#define FIELD_W			55
#define FIELD_H			28

#define DIAGRAM_X			50
#define DIAGRAM_Y			137
#define DIAGRAM_W			222 
#define DIAGRAM_H			172
#define DIAGRAM_NAME		"anchDia.bmp"

#define DEPTH_X			38
#define DEPTH_Y			320
#define DEPTH_LBL			"Depth Fm"
#define DEPTH_MSG			"Depth as read from the depth sounder."

#define SCOPE_X			136
#define SCOPE_Y			80
#define SCOPE_LBL			"Scope x"
#define SCOPE_MSG			"Scope from your settings. 1:X where this is the X value."

#define CALC_RAD_X		136
#define CALC_RAD_Y		130
#define CALC_RAD_LBL		"Radius Ft"
#define CALC_RAD_MSG		"Calculated swing radius in feet."

#define CALC_RODE_X		160
#define CALC_RODE_Y		240
#define CALC_ROAD_LBL	"Rode Fm"
#define CALC_ROAD_MSG	"Calculated amount of rode in fathoms."

#define MARGIN_X			242
#define MARGIN_Y			130
#define MARGIN_LBL		"Margin Ft"
#define MARGIN_MSG		"Added distance in feet to add to the swing radius."

#define CALC_TOTAL_X		160
#define CALC_TOTAL_Y		320
#define CALC_TOTAL_LBL	"Swing Ft"
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


// **********************************************************************
// setLocationBtn
// **********************************************************************


setLocationBtn::setLocationBtn(int xLoc,int yLoc,const char* path)
	: iconButton(xLoc,yLoc,path,60) {  }
	
	
setLocationBtn::~setLocationBtn(void) {  }
	
	
void setLocationBtn::doAction(void) { ((anchWtch*)(ourPanel))->calculateItems(); }

	
	
// **********************************************************************
// setWatchBtn
// **********************************************************************


setWatchBtn::setWatchBtn(int xLoc,int yLoc,const char* path)
	: iconButton(xLoc,yLoc,path,60) {  }
	
	
setWatchBtn::~setWatchBtn(void) {  }


void setWatchBtn::doAction(void) { nextPanel = runWatchApp; }


// **********************************************************************
// watchField
// **********************************************************************


watchField::watchField(rect* inRect,valueType inType,const char* inMsg)
	: valueField(inRect,inType,inMsg) { ourType = noParam; }
	
	
watchField::~watchField(void) {  }


void watchField::seType(paramChoice inParam) { ourType = inParam; }

			
void watchField::updateValue(const char* newValue) {

	valueField::updateValue(newValue);
	switch(ourType) {
		case noParam		: 																		break;	// Nothing we can do.
		case depthParam	: ((anchWtch*)ourPanel)->depth = atof(newValue);		break;
		case scopeParam	: 
			scopeValue = atof(newValue);
			savePrefs();
		break;
		case rodeParam		: ((anchWtch*)ourPanel)->calcRode = atof(newValue);	break;
		case radiusParam	: ((anchWtch*)ourPanel)->calcRad = atof(newValue);		break;
		case marginParam	:
			anchorMargin = atof(newValue);
			savePrefs();
		break;
		case swingParam	: ((anchWtch*)ourPanel)->calcTotal = atof(newValue);	break;
	}
	((anchWtch*)ourPanel)->calculateItems();
}


// **********************************************************************
// anchWtch
// **********************************************************************


anchWtch::anchWtch(int newAppID)
	: panel(newAppID) { }


anchWtch::~anchWtch(void) {  }


watchField* anchWtch::setupField(int inX,int inY,const char* labelTxt,const char* inMsg) {
	
	rect			frame(inX,inY,FIELD_W,FIELD_H);
	rectObj*		ourRectObj;
	watchField*	valueLbl;
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
			frame.moveRect(0,2);
			valueLbl = new watchField(&frame,aNumber,inMsg);
			if (valueLbl) {
				ourTxtPallette.setTypeFace(valueLbl,smallValues);
				valueLbl->setEventSet(fullClick);
				addObj(valueLbl);
				return valueLbl;
			}
		}
	}
	return NULL;
}
	
		
void anchWtch::setup(void) {
	
	rect			frame;
	fontLabel*	aLbl;
	
	frame.setRect(ANCHOR_X,ANCHOR_Y,200,30);
	aLbl = new fontLabel(&frame);
	ourTxtPallette.setTypeFace(aLbl,panelTitle);
	aLbl->setValue("Anchor setup");
	addObj(aLbl);
	
	frame.setRect(DIAGRAM_X,DIAGRAM_Y,DIAGRAM_W,DIAGRAM_H);
	setFilePath(DIAGRAM_NAME);
	bmpObj* theDiagram = new bmpObj(&frame,mFilePath);
	if (theDiagram) {
		addObj(theDiagram);
	}
				
	depthFld = setupField(DEPTH_X,DEPTH_Y,DEPTH_LBL,DEPTH_MSG);
	if (depthFld) {
		depthFld->seType(depthParam);
	}

	scopeFld = setupField(SCOPE_X,SCOPE_Y,SCOPE_LBL,SCOPE_MSG);
	if (scopeFld) {
		scopeFld->seType(scopeParam);
	}
	
	calcRodeFld = setupField(CALC_RODE_X,CALC_RODE_Y,CALC_ROAD_LBL,CALC_ROAD_MSG);
	if (calcRodeFld) {
		calcRodeFld->seType(rodeParam);
	}
	calcRadiusFld = setupField(CALC_RAD_X,CALC_RAD_Y,CALC_RAD_LBL,CALC_RAD_MSG);
	if (calcRadiusFld) {
		calcRadiusFld->seType(radiusParam);
	}
	marginFld = setupField(MARGIN_X,MARGIN_Y,MARGIN_LBL,MARGIN_MSG);
	if (marginFld) {
		marginFld->seType(marginParam);
	}
	totalRadiusFld = setupField(CALC_TOTAL_X,CALC_TOTAL_Y,CALC_TOTAL_LBL,CALC_TOTAL_MSG);
	if (totalRadiusFld) {
		totalRadiusFld->seType(swingParam);
	}
	
	calculateItems();
	
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


void anchWtch::calculateItems(void) {

	depth = ourNavigator->getDepth(); // Fathoms
	
	calcRode = depth * scopeValue; // Fathoms
	calcRad = sqrt(abs(pow(calcRode,2) - pow(depth,2)));	// Fathoms
	calcRad = calcRad * 6;	// Feet
	calcTotal = calcRad + anchorMargin; // Feet
	
	depthFld->setValue(depth);
	scopeFld->setValue(scopeValue);
	calcRodeFld->setValue(calcRode);
	calcRadiusFld->setValue(calcRad);
	marginFld->setValue(anchorMargin);
	totalRadiusFld->setValue(calcTotal);
}
	
	
void anchWtch::loop(void) {  }


void anchWtch::drawSelf(void) { screen->fillScreen(&black); }


void anchWtch::closing(void) {  }
	
				
			
