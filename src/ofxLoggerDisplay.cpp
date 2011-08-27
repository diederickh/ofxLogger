#include "ofxLoggerDisplay.h"
#include "ofxLogger.h"
ofxLoggerDisplay::ofxLoggerDisplay()
:num_messages_to_show(0)
{
}

void ofxLoggerDisplay::setup(int numToShow) {
	num_messages_to_show = numToShow;
	// copy the font used to the data path.
	/* wierd crashes... no time to fix.
	string font_source_file = "logview_font.ttf";
	string font_data_path = ofToDataPath(font_source_file, true);
	ofFile datapath_font(font_data_path);
	if(!datapath_font.exists()) {
		ofFile curr_file(__FILE__);
		string path = curr_file.getEnclosingDirectory();
		string font_source_path = path +"../extra/" +font_source_file;
		ofFile font_source(font_source_path);
		font_source.copyTo(font_source_file, true);
	}
	log_font.loadFont(font_source_file, 18);
	*/
	
	
	// add event listener
	ofxLogger::addListener(this, &ofxLoggerDisplay::onNewLog);
}

/*

		case OF_LOG_VERBOSE:
			return Poco::Message::PRIO_TRACE;
			
		case OF_LOG_NOTICE:
			return Poco::Message::PRIO_NOTICE;
			
		case OF_LOG_WARNING:
			return Poco::Message::PRIO_WARNING;
			
		case OF_LOG_ERROR:
			return Poco::Message::PRIO_ERROR;
			
		case OF_LOG_FATAL_ERROR:
			return Poco::Message::PRIO_FATAL;
			
		case OF_LOG_SILENT:
			return -1;
*/

void ofxLoggerDisplay::draw(float x, float y) {
	ofSetColor(33,33,33);
	ofRect(0,0, ofGetWidth(), ofGetHeight());

	deque<ofxLoggerEvent>::iterator it = messages.begin();
	int h = y+10;
	while(it != messages.end()) {
		ofxLoggerEvent& ev = *it;
		switch(ev.level) {
			case OF_LOG_VERBOSE: 		ofSetColor(63,  88,  116); 	break;
			case OF_LOG_NOTICE:			ofSetColor(35,  255, 131);	break;
			case OF_LOG_WARNING: 		ofSetColor(0,   160, 255); 	break;
			case OF_LOG_ERROR:			ofSetColor(255, 43,  56);	break;
			case OF_LOG_FATAL_ERROR:	ofSetColor(211, 24,  149);	break;
			default: 					ofSetColor(255, 255, 255); 	break;
		};
		ofDrawBitmapString((*it).message, x,h);
		h+= 13;
		++it;
	}
}

void ofxLoggerDisplay::onNewLog(ofxLoggerEvent& ev) {
	messages.push_back(ev);
	if(messages.size() > num_messages_to_show) {
		messages.erase(messages.begin());
	}
}

