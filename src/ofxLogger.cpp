#include "ofxLogger.h"

#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Message.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeFormatter.h>

const string ofxLogger::s_dateFormat = "%Y-%m-%d %H:%M:%S.%i";
const string ofxLogger::s_timeFormat = "%H:%M:%S.%i";
const string ofxLogger::s_dateAndTimeFormat = "%Y-%m-%d %H:%M:%S.%i";

ofEvent<ofxLoggerEvent> ofxLoggerEventDispatcher;

//
// Useful references:
//  - http://pocoproject.org/docs/Poco.Logger.html
//  - http://pocoproject.org/docs/Poco.FileChannel.html
//
//------------------------------------------------------------------------------------
// inspired by the Poco LogRotation sample
ofxLogger::ofxLogger()
{	

	bConsole = true;
	bFile = false;

	bHeader = false;
	bDate = true;
	bTime = true;
	bFrameNum = false;
	bMillis = false;

	splitterChannel = new Poco::SplitterChannel();

	consoleChannel = new Poco::ConsoleChannel();
	fileChannel = new Poco::FileChannel(ofToDataPath("openframeworks.log"));

	// console open, file not opened (added) by default
	splitterChannel->addChannel(consoleChannel);

	Poco::AutoPtr<Poco::Formatter> formatter(new Poco::PatternFormatter("%t"));
	formattingChannel = new Poco::FormattingChannel(formatter, splitterChannel);

	// the root logger has an empty name
	logger = &Poco::Logger::create("", formattingChannel, _convertOfLogLevel(OF_LOG_NOTICE));

	// setup file logger
	fileChannel->setProperty("times", "local");		// use local system time
	fileChannel->setProperty("archive", "number");	// use number suffixs
	fileChannel->setProperty("compress", "false"); 	// don't compress
	fileChannel->setProperty("purgeCount", "10");	// max number of log files

	// add default of topic
	addTopic("of");
}

//-----------------------------------------------------------------
ofxLogger& ofxLogger::instance()
{
	static ofxLogger* pointerToTheSingletonInstance = new ofxLogger;
	return *pointerToTheSingletonInstance;
}

//--------------------------------------------------------------------------------------
void ofxLogger::log(ofLogLevel logLevel, const string& message){

	_log(logLevel, message, logger);
}

void ofxLogger::log(const string& logTopic, ofLogLevel logLevel, const string& message)
{
	Poco::Logger* topicLogger = Poco::Logger::has(logTopic);
	if(!topicLogger)
	{
		_log(OF_LOG_WARNING, "log topic \""+logTopic+"\" not found", logger);
	}
	else
	{
		_log(logLevel, logTopic+": "+message, topicLogger);
	}
}

//--------------------------------------------------------------
void ofxLogger::setLevel(ofLogLevel logLevel)
{
	logger->setLevel(_convertOfLogLevel(logLevel));
}

ofLogLevel ofxLogger::getLevel()
{
	return _convertPocoLogLevel(logger->getLevel());
}

//-------------------------------------------------
void ofxLogger::enableConsole()
{

	splitterChannel->addChannel(consoleChannel);
	consoleChannel->open();
	bConsole = true;
}

void ofxLogger::disableConsole()
{
	splitterChannel->removeChannel(consoleChannel);
	consoleChannel->close();
	bConsole = false;
}	

bool ofxLogger::usingConsole()
{
	return bConsole;
}

//----------------------------------------------------------------------------------------
// using printf instead of the logger since we don't want to write this as a line
void ofxLogger::setConsoleColor(int color){
	#ifdef TARGET_WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	#else
		printf("\033[%im",  color);
	#endif
}

void ofxLogger::restoreConsoleColor(){
	#ifdef TARGET_WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), OF_CONSOLE_COLOR_RESTORE);
	#else
		printf("\033[%im",  OF_CONSOLE_COLOR_RESTORE);
	#endif
}

//----------------------------------------------
void ofxLogger::setFilePath(const string& file)
{
	fileChannel->setProperty("path", file);
}

string ofxLogger::getFilePath()
{
	return fileChannel->getProperty("path");
}

void ofxLogger::enableFile()
{
	fileChannel->open();
	splitterChannel->addChannel(fileChannel);
	bFile = true;
}

void ofxLogger::disableFile()
{
	fileChannel->close();
	splitterChannel->addChannel(fileChannel);
	bFile = false;
}

bool ofxLogger::usingFile()
{
	return bFile;
}

//-----------------------------------------------------------------------
void ofxLogger::enableFileRotationMins(unsigned int minutes)
{
	fileChannel->setProperty("rotation", ofToString(minutes)+" minutes");
}

void ofxLogger::enableFileRotationHours(unsigned int hours)
{
	fileChannel->setProperty("rotation", ofToString(hours)+" hours");
}

void ofxLogger::enableFileRotationDays(unsigned int days)
{
	fileChannel->setProperty("rotation", ofToString(days)+" days");
}

void ofxLogger::enableFileRotationMonths(unsigned int months)
{
	fileChannel->setProperty("rotation", ofToString(months)+" months");
}

void ofxLogger::enableFileRotationSize(unsigned int sizeKB)
{
	fileChannel->setProperty("rotation", ofToString(sizeKB)+" K");
}

void ofxLogger::disableFileRotation()
{
	fileChannel->setProperty("rotation", "never");
}

//--------------------------------------------------------------------------------
void ofxLogger::setFileRotationMaxNum(unsigned int num)
{
	fileChannel->setProperty("purgeCount", ofToString(num));
}

//--------------------------------------------------------------------------------
void ofxLogger::setFileRotationNumber()
{
	fileChannel->setProperty("archive", "number");
}

void ofxLogger::setFileRotationTimestamp()
{
	fileChannel->setProperty("archive", "timestamp");
}

//--------------------------------------------------------------------------------
void ofxLogger::addTopic(const string& logTopic, ofLogLevel logLevel)
{
	try
	{
		Poco::Logger::create(logTopic, formattingChannel, _convertOfLogLevel(logLevel));
	}
	catch (Poco::ExistsException& e)
	{
		log(OF_LOG_WARNING, "log topic \""+logTopic+"\" does not exist");
	}
}

void ofxLogger::removeTopic(const string& logTopic)
{
	Poco::Logger::destroy(logTopic);
}

bool ofxLogger::topicExists(const string& logTopic)
{
	return (bool) Poco::Logger::has(logTopic); // has returns NULL if topic not found
}

void ofxLogger::setTopicLogLevel(const string& logTopic, ofLogLevel logLevel)
{
	Poco::Logger* topicLogger = Poco::Logger::has(logTopic);
	if(topicLogger)
	{
		topicLogger->setLevel(_convertOfLogLevel(logLevel));
	}
	else
	{
		log(OF_LOG_WARNING, "log topic \""+logTopic+"\" not found");
	}
}
void ofxLogger::resetTopicLogLevel(const string& logTopic)
{
	setTopicLogLevel(logTopic, _convertPocoLogLevel(logger->getLevel()));
}

//--------------------------------------------------------
void ofxLogger::enableHeader()
{
	bHeader = true;
}

void ofxLogger::disableHeader()
{
	bHeader = false;
}

bool ofxLogger::usingHeader()
{
	return bHeader;
}

//----------------------------
void ofxLogger::enableHeaderDate()
{
	bDate = true;
}
void ofxLogger::disableHeaderDate()
{
	bDate = false;
}

bool ofxLogger::usingHeaderDate()
{
	return bDate;
}
//----------------------------
void ofxLogger::enableHeaderTime()
{
	bTime = true;
}

void ofxLogger::disableHeaderTime()
{
	bTime = false;
}

bool ofxLogger::usingHeaderTime()
{
	return bTime;
}

//-----------------------------
void ofxLogger::enableHeaderFrameNum()
{
	bFrameNum = true;
}

void ofxLogger::disableHeaderFrameNum()
{
	bFrameNum = false;
}

bool ofxLogger::usingHeaderFrameNum()
{
	return bFrameNum;
}

//-----------------------------
void ofxLogger::enableHeaderMillis()
{
	bMillis = true;
}

void ofxLogger::disableHeaderMillis()
{
	bMillis = false;
}

bool ofxLogger::usingHeaderMillis()
{
	return bMillis;
}

//---------------------------------------------------------------------------------
void ofxLogger::_log(ofLogLevel logLevel, const string& message, Poco::Logger* theLogger)
{
	string timestamp;
	
	// dispatch a simple logger event.
	ofxLoggerEvent ev(message, logLevel);
	ofNotifyEvent(ofxLoggerEventDispatcher, ev);
	
	// build the header
	if(bHeader)
	{
		Poco::LocalDateTime now;

		if(bDate && bTime)
		{
			timestamp += Poco::DateTimeFormatter::format(now, s_dateAndTimeFormat)+" ";
		}
		else if(bDate)
		{
			timestamp += Poco::DateTimeFormatter::format(now, s_dateFormat)+" ";
		}
		else if(bTime)
		{
			timestamp += Poco::DateTimeFormatter::format(now, s_timeFormat)+" ";	
		}

		if(bFrameNum)
		{
			timestamp += ofToString(ofGetFrameNum())+" ";
		}

		if(bMillis)
		{
			timestamp += ofToString(ofGetElapsedTimeMillis())+" ";
		}
	}

	// log the message
	//
	// Each log call is wrapped in a try / catch in case the logger is called
	// when it has already been destroyed. This can happen if it is used in
	// another destructor as the destruction order is not predictabale.
	//
	switch(logLevel)
	{
		case OF_LOG_SILENT:
			break;

		case OF_LOG_VERBOSE:
			try
			{
				theLogger->trace(timestamp+"OF_VERBOSE: "+message);
			}
			catch(...)
			{
				_logDestroyed("OF_VERBOSE: "+message);
			}
			break;

		case OF_LOG_NOTICE:
			try
			{
				theLogger->notice(timestamp+message);
			}
			catch(...)
			{
				_logDestroyed(message);
			}
			break;

		case OF_LOG_WARNING:
			try
			{
				theLogger->warning(timestamp+"OF_WARNING: "+message);
			}
			catch(...)
			{
				_logDestroyed("OF_WARNING: "+message);
			}
			break;

		case OF_LOG_ERROR:
			try
			{
				theLogger->error(timestamp+"OF_ERROR: "+message);
			}
			catch(...)
			{
				_logDestroyed("OF_ERROR: "+message);
			}
			break;

		case OF_LOG_FATAL_ERROR:
			try
			{
				theLogger->fatal(timestamp+"OF_FATAL_ERROR: "+message);
			}
			catch(...)
			{
				_logDestroyed("OF_FATAL_ERROR: "+message);
			}
			break;
	}
}

void ofxLogger::_logDestroyed(const string& message)
{
	printf("----------\n");
	printf("\tHey ... don't call ofxLog in a destructor!\n");
	printf("\t%s\n", message.c_str());
	printf("----------\n");
}

ofLogLevel ofxLogger::_convertPocoLogLevel(const int level)
{
	switch(level)
	{
		case Poco::Message::PRIO_TRACE:
			return OF_LOG_VERBOSE;
			
		case Poco::Message::PRIO_NOTICE:
			return OF_LOG_NOTICE;
			
		case Poco::Message::PRIO_WARNING:
			return OF_LOG_WARNING;
			
		case Poco::Message::PRIO_ERROR:
			return OF_LOG_ERROR;
			
		case Poco::Message::PRIO_FATAL:
			return OF_LOG_FATAL_ERROR;
			
		case -1:
			return OF_LOG_SILENT;
	}
}

int ofxLogger::_convertOfLogLevel(const ofLogLevel level)
{
	switch(level)
	{
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
	}
}
