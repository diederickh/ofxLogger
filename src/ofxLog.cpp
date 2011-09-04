#include "ofxLog.h"

#include "ofxLogger.h"

//-------------------------------------------------------
ofxLog::~ofxLog(){
	if(topic.empty()){
		ofxLogger::instance().log(level, message.str());
	}
	else{
		ofxLogger::instance().log(topic, level, message.str());
	}
}

//--------------------------------------------------------------
void ofxLog::setLevel(ofLogLevel logLevel){
	ofxLogger::instance().setLevel(logLevel);
}

ofLogLevel ofxLog::getLevel(){
	return (ofLogLevel) ofxLogger::instance().getLevel();
}


// Helper if you just want to quickly log to a file with
// file rotation enabled for each 1mb.
void ofxLog::setupUsingDefaultSettingsForFileRotation() {
	ofxLog::enableFileRotationSize(1024);
	ofxLog::enableFile();
	ofxLog::enableHeader();
	ofxLog::enableHeaderFrameNum();
	ofxLog::setLevel(OF_LOG_VERBOSE);
}


//----------------------------------------------------------------------------------------
void ofxLog::enableConsole()	{ofxLogger::instance().enableConsole();}
void ofxLog::disableConsole()	{ofxLogger::instance().disableConsole();}
bool usingConsole()				{return ofxLogger::instance().usingConsole();}

void ofxLog::setConsoleColor(int color)	{ofxLogger::instance().setConsoleColor(color);}
void ofxLog::restoreConsoleColor()		{ofxLogger::instance().restoreConsoleColor();}

void ofxLog::enableFile()	{ofxLogger::instance().enableFile();}
void ofxLog::disableFile()	{ofxLogger::instance().disableFile();}
bool usingFile()			{return ofxLogger::instance().usingFile();}

void ofxLog::setFilePath(const string& file) {ofxLogger::instance().setFilePath(file);}
string ofxLog::getFilePath()				 {return ofxLogger::instance().getFilePath();}

void ofxLog::enableFileRotationMins(unsigned int minutes)
	{ofxLogger::instance().enableFileRotationMins(minutes);}
void ofxLog::enableFileRotationHours(unsigned int hours)
	{ofxLogger::instance().enableFileRotationHours(hours);}
void ofxLog::enableFileRotationDays(unsigned int days)
	{ofxLogger::instance().enableFileRotationDays(days);}
void ofxLog::enableFileRotationMonths(unsigned int months)
	{ofxLogger::instance().enableFileRotationMonths(months);}
void ofxLog::enableFileRotationSize(unsigned int sizeKB)
	{ofxLogger::instance().enableFileRotationSize(sizeKB);}
void ofxLog::disableFileRotation()	{ofxLogger::instance().disableFileRotation();}

void ofxLog::setFileRotationMaxNum(unsigned int num)
	{ofxLogger::instance().setFileRotationMaxNum(num);}

void ofxLog::setFileRotationNumber()	{ofxLogger::instance().setFileRotationNumber();}
void ofxLog::setFileRotationTimestamp()	{ofxLogger::instance().setFileRotationTimestamp();}

void ofxLog::addTopic(const string& logTopic, ofLogLevel logLevel)
	{ofxLogger::instance().addTopic(logTopic, logLevel);}
void ofxLog::removeTopic(const string& logTopic)	{ofxLogger::instance().removeTopic(logTopic);}
bool topicExists(const string& logTopic)
	{return ofxLogger::instance().topicExists(logTopic);}
void ofxLog::setTopicLogLevel(const string& logTopic, ofLogLevel logLevel)
	{ofxLogger::instance().setTopicLogLevel(logTopic, logLevel);}
void ofxLog::resetTopicLogLevel(const string& logTopic)
	{ofxLogger::instance().resetTopicLogLevel(logTopic);}

void ofxLog::enableHeader()		{ofxLogger::instance().enableHeader();}
void ofxLog::disableHeader()	{ofxLogger::instance().disableHeader();}
bool usingHeader()				{return ofxLogger::instance().usingHeader();}

void ofxLog::enableHeaderDate()		{ofxLogger::instance().enableHeaderDate();}
void ofxLog::disableHeaderDate()	{ofxLogger::instance().disableHeaderDate();}
bool usingHeaderDate()				{return ofxLogger::instance().usingHeaderDate();}

void ofxLog::enableHeaderTime()		{ofxLogger::instance().enableHeaderTime();}
void ofxLog::disableHeaderTime()	{ofxLogger::instance().disableHeaderTime();}
bool usingHeaderTime()				{return ofxLogger::instance().usingHeaderTime();}

void ofxLog::enableHeaderFrameNum()		{ofxLogger::instance().enableHeaderFrameNum();}
void ofxLog::disableHeaderFrameNum()	{ofxLogger::instance().disableHeaderFrameNum();}
bool usingHeaderFrameNum()				{return ofxLogger::instance().usingHeaderFrameNum();}

void ofxLog::enableHeaderMillis()	{ofxLogger::instance().enableHeaderMillis();}
void ofxLog::disableHeaderMillis()	{ofxLogger::instance().disableHeaderMillis();}
bool usingHeaderMillis()			{return ofxLogger::instance().usingHeaderMillis();}
