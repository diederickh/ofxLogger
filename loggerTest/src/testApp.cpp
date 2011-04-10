#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetFrameRate(5);
	
	ofSetLogLevel(OF_LOG_ERROR);
	
	logTest("without header");
	ofxLog::enableHeader();
	logTest("with header");
	ofxLog::setLevel(OF_LOG_ERROR);
	logTest("logLevel at OF_LOG_ERROR");
	ofxLog::disableHeader();
	
	ofLog(OF_LOG_NOTICE, "some more text here");
	ofLog(OF_LOG_WARNING, "%s %d", "text text text", 100);
	
	ofxLog::enableFileRotationMins(1);
	ofxLog::enableFile();
	ofxLog::enableHeader();
	ofxLog::enableHeaderFrameNum();
	ofxLog::enableHeaderMillis();
	
	ofxLog::setLevel(OF_LOG_NOTICE);
	
	ofxLog::addTopic("of.topic1");
	ofxLog::addTopic("of.topic2");
	ofxLog("of") << "a log";
	ofxLog("of.topic1") << "an error";
	ofxLogError("of.topic2") << "an error";
	ofxLog::setTopicLogLevel("of.topic1", OF_LOG_WARNING);
	ofxLog("of.topic1") << "a log ... this should not be printed";
	ofxLogError("of.topic1") << "an error";
	
	ofxLog() << "log file: " << ofxLog::getFilePath();
	
	ofxLog::disableHeaderDate();
	ofxLog::disableHeaderTime();
}

//--------------------------------------------------------------
void testApp::update(){

	ofxLogWarning() << "... a new frame";
}

//--------------------------------------------------------------
void testApp::draw(){

	ofxBitmapString(20, 12) << "frame: " << ofGetFrameNum() << endl
					  	    << "  fps: " << ofGetFrameRate();
}

//--------------------------------------------------------------
void testApp::logTest(const string& msg){
	cout << endl << "------------" << endl << msg << endl; 
	ofxLog() << "log";
	ofxLogVerbose() << "verbose";
	ofxLogWarning() << "warning";
	ofxLogError() << "error";
	ofxLogFatalError() << "fatal error";
	cout << "------------" << endl << endl; 
}