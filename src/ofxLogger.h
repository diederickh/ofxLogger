#pragma once

#include <ofConstants.h>

#include "ofxLog.h"
#include "ofxBitmapString.h"

#include <Poco/AutoPtr.h>
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/SplitterChannel.h>

//#define OF_DEFAULT_LOG_LEVEL  OF_LOG_NOTICE

//------------------------------------------------------------------------------
/// \class ofxLogger
/// \brief a singleton log class, this is where the magic happens ...
///
/// ofxLogger is an interface to a global Poco logger. The logger prints lines
/// to the text console and/or a file with an optional header showing the date,
/// time, frameNum, and elapsed millis.
///
/// Each log line is prefixed by an optionally header and log level:
///
///	HEADER LOGLEVEL: LOG TOPIC: your message
///
/// Note: This class dosen't need to be access directy. Use the stream log classes
/// or the global functions.
///
/// See the singleton pattern for more info: http://en.wikipedia.org/wiki/Singleton_pattern
///
class ofxLogger
{
	public:
	
		/// singleton object access, creates a new object on the first call
		static ofxLogger& instance();
		
		/// \section Log
		/// Log the a message as a full line at a specifed log level. Prints a
		/// newline automatically.
		void log(ofLogLevel logLevel, const std::string& message);
		void log(const std::string& logTopic, ofLogLevel logLevel, const std::string& message);
		
		/// \section Log Level
		/// Set the current log level. Messages with a log level below this level 
		/// are not printed.
		///	For example, if the log level is OF_LOG_WARNING:
		///  - OF_LOG_ERROR, OF_LOG_FATAL_ERROR messages are printed
		///  - OF_LOG_NOTICE, OF_LOG_DEBUG, & OF_LOG_VERBOSE message are not printed
		void setLevel(ofLogLevel logLevel);
		ofLogLevel getLevel();
		
		/// \section Console
		
		/// Log to the text console. (on by default)
		void enableConsole();
		void disableConsole();
		bool usingConsole();
		
		/// \section Console Color
		
		/// Set the console text color 
		/// doesn't work in the xcode console - do we need this?
		/// works fine on the terminal though - not much use
		void setConsoleColor(int color);
		void restoreConsoleColor();
		
		/// \section Log File
		
		//// Log to a file. (off by default)
		void enableFile();
		void disableFile();
		bool usingFile();
		
		/// Set the path to the log file. The default filename is "openframeworks.log"
		/// and is saved to the data folder. When setting your own file use
		/// ofToDataPath()+"/filename" to build the full path.
		void setFilePath(const std::string& file);
		std::string getFilePath();
		
		/// Set the automatic rotation of the log file. The log file will grow until
		/// it reaches a specified limit (time or size). It will then have a number or
		/// timestamp appended to it's filename and a new file will be created with the 
		/// original name. This keeps the files from growing arbitrarily large in memory!
		///
		/// Note: only one file rotation type is active at a time
		void enableFileRotationMins(unsigned int minutes);
		void enableFileRotationHours(unsigned int hours);
		void enableFileRotationDays(unsigned int days);
		void enableFileRotationMonths(unsigned int months);
		void enableFileRotationSize(unsigned int sizeKB);
		void disableFileRotation();
	
		/// Set the maximum number of files in the automtic log rotation.
		/// (defualt is 10)
		void setFileRotationMaxNum(unsigned int num);
		
		/// Set the suffix appended to the rotated log files:
		///  - number: logfile.log.#
		///	 - timestamp: logfile.log.YYYYMMDDHHMMSSms
		/// Note: only one type is active at a time
		void setFileRotationNumber();
		void setFileRotationTimestamp();
	
		/// \section Log Topics
		/// Log topics allow fine grained control of logging. Topics are a logging
		/// namespace hierarchy where the logging levels of each topic can be set
		/// independently. The log level is automatically added to the header.
		///
		/// Add a log topic and then log using that topic:
		///		ofLogAddTopic("topic");
		///		ofLogDebug("topic") << "a log message";
		///
		/// Hierarchies can be built by using a period in the topic: "topic.a" &
		/// "topic.b" are children of the "topic" parent topic. The log levels of
		/// the children can be set independently while setting the level of the 
		/// parent sets the level for all children. There is no limit to the 
		/// depth of the hierarchy.
		///
		/// Resetting the level of the log topic sets it to the level of the global
		/// logger.
		void addTopic(const std::string& logTopic, ofLogLevel logLevel=OF_LOG_NOTICE);
		void removeTopic(const std::string& logTopic);
		bool topicExists(const std::string& logTopic);
		void setTopicLogLevel(const std::string& logTopic, ofLogLevel logLevel);
		void resetTopicLogLevel(const std::string& logTopic);
		
		/// \section Header

		/// Prefix the header to each line with a layout of:
		/// DATE TIME FRAMENUM MILLS
		/// 
		/// The header is disabled by default.
		///
		/// Note: The log level and log topic are not part of the header and are
		/// always printed.
		void enableHeader();
		void disableHeader();
		bool usingHeader();
		
		/// Show the date in the header: YYYY-MM-DD
		/// Enabled by default.
		void enableHeaderDate();
		void disableHeaderDate();
		bool usingHeaderDate();
		
		/// Show the time in the header: HH:MM:SS.ms
		/// Enabled by default.
		void enableHeaderTime();
		void disableHeaderTime();
		bool usingHeaderTime();
		
		/// Show the current frame num in the header.
		/// Disabled by default.
		void enableHeaderFrameNum();
		void disableHeaderFrameNum();
		bool usingHeaderFrameNum();
		
		/// Show the current elapsed millis in the header.
		/// Disabled by default.
		void enableHeaderMillis();
		void disableHeaderMillis();
		bool usingHeaderMillis();
		
	protected:

		Poco::AutoPtr<Poco::Logger> 			logger;				///< the logger
		Poco::AutoPtr<Poco::Channel> 			formattingChannel;	///< formatter (needed for creating topics)
		Poco::AutoPtr<Poco::SplitterChannel>	splitterChannel;	///< channel source mixer
		Poco::AutoPtr<Poco::ConsoleChannel> 	consoleChannel;		///< the console io channel
		Poco::AutoPtr<Poco::FileChannel> 		fileChannel;		///< the file io channel
		
		bool bConsole;	///< are we printing to the console?
		bool bFile;		///< are we printing to a file?
		
		bool bHeader;	///< are we printing the header?
		bool bDate;		///< print the date?
		bool bTime;		///< print the time?
		bool bFrameNum;	///< print the frame num?
		bool bMillis;	///< print the elapsed millis?
		
	private:
		
		/// logs the message to the specified logger
		void _log(ofLogLevel logLevel, const std::string& message, Poco::Logger* theLogger);
		
		/// logs using a printf and prints a warning
		/// this is used if the logger has been destroyed
		void _logDestroyed(const string& message);
		
		/// convert an OF log level to the Poco log level and vice versa
		ofLogLevel _convertPocoLogLevel(const int level);
		int _convertOfLogLevel(const ofLogLevel level);
		
		/// static date format strings for the header
		static const std::string s_dateFormat;
		static const std::string s_timeFormat;
		static const std::string s_dateAndTimeFormat;
	
		// hide all the constructors, copy functions here
		ofxLogger(ofxLogger const&);    				// not defined, not copyable
		ofxLogger& operator = (ofxLogger const&);	// not defined, not assignable
		ofxLogger();								// singleton constructor
		~ofxLogger(){}								// singleton destructor
};
