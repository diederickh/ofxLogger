#pragma once

#include "ofMain.h"

//------------------------------------------------------------------------------
/// \class ofxLog
/// \brief a public streaming log interface
///
/// ofxLog accepts variables via the ostream operator << and builds a string
/// and logs it when the stream is finished (via the destructor). A newline is
/// printed automatically and all the stream controls (endl, flush, hex, etc)
/// work normally. The log level is explicitly OF_LOG_NOTICE, see the derived 
/// wrapper classes:
///
/// Usage: ofxLog() << "a string" << 100 << 20.234f;
///
/// Public control to the ofLogger is provided through wrapper functions.
///
/// class idea from:
/// 	http://www.gamedev.net/community/forums/topic.asp?topic_id=525405&whichpage=1&#3406418
/// how to catch std::endl (which is actually a func pointer):
/// 	http://yvan.seth.id.au/Entries/Technology/Code/std__endl.html
///
///
class ofxLog
{
    public:

		ofxLog()
		{
			level = OF_LOG_NOTICE;
		}
		
		ofxLog(string logTopic)
		{
			level = OF_LOG_NOTICE;
			topic = logTopic;
		}
// an interface to set the log level when using:
//
// ofLogNotice(OF_LOG_WARNING) << "a string;
//
// This is commented for now as setting the level directly seems redundant when
// the derived log level classes are available. It would be nice if this class
// was named ofLog ...
//
//        ofLogNotice(ofLogLevel logLevel){
//			level = logLevel;
//		}

        /// does the actual printing on when the ostream is done
        ~ofxLog();

        /// catch the << ostream with a template class to read any type of data
        template <class T> 
		ofxLog& operator<<(const T& value)
		{
            message << value;
            return *this;
        }

        /// catch the << ostream function pointers such as std::endl and std::hex
        ofxLog& operator<<(std::ostream& (*func)(std::ostream&))
		{
			func(message);
            return *this;
        }

		/// \section Global Log Function Wrappers
		///
		/// Ok Ok, I know this looks scary ... but it's just a long list
		/// of static public wrappers to access the ofLogger class.
		static void setLevel(ofLogLevel logLevel);
		static ofLogLevel getLevel();
		
		static void enableConsole();
		static void disableConsole();
		static bool usingConsole();
		
		static void setConsoleColor(int color);
		static void restoreConsoleColor();
		
		static void enableFile();
		static void disableFile();
		static bool usingFile();
		
		static void setFilePath(const string& file);
		static string getFilePath();
		
		static void setupUsingDefaultSettingsForFileRotation();
		static void enableFileRotationMins(unsigned int minutes);
		static void enableFileRotationHours(unsigned int hours);
		static void enableFileRotationDays(unsigned int days);
		static void enableFileRotationMonths(unsigned int months);
		static void enableFileRotationSize(unsigned int sizeKB);
		static void disableFileRotation();

		static void setFileRotationMaxNum(unsigned int num);
		
		static void setFileRotationNumber();
		static void setFileRotationTimestamp();
	
		static void addTopic(const string& logTopic, ofLogLevel logLevel=OF_LOG_NOTICE);
		static void removeTopic(const string& logTopic);
		static bool topicExists(const string& logTopic);
		static void setTopicLogLevel(const string& logTopic, ofLogLevel logLevel);
		static void resetTopicLogLevel(const string& logTopic);
		
		static void enableHeader();
		static void disableHeader();
		static bool usingHeader();
		
		static void enableHeaderDate();
		static void disableHeaderDate();
		static bool usingHeaderDate();
		
		static void enableHeaderTime();
		static void disableHeaderTime();
		static bool usingHeaderTime();

		static void enableHeaderFrameNum();
		static void disableHeaderFrameNum();
		static bool usingHeaderFrameNum();
		
		static void enableHeaderMillis();
		static void disableHeaderMillis();
		static bool usingHeaderMillis();
		
	protected:
	
		ofLogLevel level;			///< log level
		std::string topic;			///< log topic
					
	private:
	
        std::ostringstream message;	///< temp buffer
		
		ofxLog(ofxLog const&) {}        				// not defined, not copyable
        ofxLog& operator=(ofxLog& from) {return *this;}	// not defined, not assignable
};

//--------------------------------------------------------------
///
/// \section Log Aliases
/// derived log classes for easy to use names
///
class ofxLogVerbose : public ofxLog
{
	public:
		ofxLogVerbose()	{level = OF_LOG_VERBOSE;}
		ofxLogVerbose(std::string logTopic)
			{level = OF_LOG_VERBOSE; topic = logTopic;}
};

class ofxLogWarning : public ofxLog
{
	public:
		ofxLogWarning() {level = OF_LOG_WARNING;}
		ofxLogWarning(std::string logTopic)
			{level = OF_LOG_WARNING; topic = logTopic;}
};

class ofxLogError : public ofxLog
{
	public:
		ofxLogError() {level = OF_LOG_ERROR;}
		ofxLogError(std::string logTopic)
			{level = OF_LOG_ERROR; topic = logTopic;}
};

class ofxLogFatalError : public ofxLog
{
	public:
		ofxLogFatalError() {level = OF_LOG_FATAL_ERROR;}
		ofxLogFatalError(std::string logTopic)
			{level = OF_LOG_FATAL_ERROR; topic = logTopic;}
};
