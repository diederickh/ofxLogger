

ofxLogger
==================

ofxLogger is an advanced logger addon for Open Frameworks which adds C++ stream operators (no more ofToString needed), file logging, timestamps, and other features. There is also ofxBitmapString which is a stream operator ofDrawBitmapString.

OpenFrameworks is a cross platform open source toolkit for creative coding in C++.

[http://www.openframeworks.cc/](http://www.openframeworks.cc/)

Installation
------------

To use ofxLogger, first you need to download and install Open Frameworks. ofxLogger.xcodeproj is currently developed against the latest version of Open Frameworks on github (007), but ofxLogger itself should work with 0062.

To get a copy of the repository you can download the source from [http://github.com/danomatika/ofxLogger/zipball/master](http://github.com/danomatika/ofxLogger/zipball/master) or, alternatively, you can use git clone:
<pre>
git clone git://github.com/danomatika/ofxLogger.git
</pre>

The addon should sit in openFrameworks/addons/ofxLogger/.

Running the Example Project
-------------------------------

If you're using OS X, open the XCode project in ofxLogger/loggerTest/ and hit "Build and Run".

Adding ofxLogger to an Existing Project
---------------------------------------

If you want to add ofxKinect to another project, you need to make sure you include the src folders:
<pre>
openFrameworks/addons/ofxLogger/src
</pre>

For XCode:
* create a new group "ofxLogger"
* drag these directories from ofxLogger into this new group: ofxLogger/src

