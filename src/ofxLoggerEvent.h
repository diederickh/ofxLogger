#ifndef OFXLOGGEREVENTH
#define OFXLOGGEREVENTH
#include <string>
class ofxLoggerEvent {
public:
	ofxLoggerEvent(std::string msg, ofLogLevel l)
		:message(msg) 
		,level(l)
	{
	}
	ofLogLevel level;
	string message;
};
#endif