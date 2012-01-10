#ifndef OFXLOGGERDISPLAYH
#define OFXLOGGERDISPLAYH
#include "ofMain.h"
#include "ofxLoggerEvent.h"

class ofxLoggerDisplay {
public:
	ofxLoggerDisplay();
	void setup(int numToShow);
	void draw(float x, float y);
	void onNewLog(ofxLoggerEvent& ev);	
private:
	bool locked;
	int num_messages_to_show;
	deque<ofxLoggerEvent> messages;
	//ofTrueTypeFont log_font;
};
#endif