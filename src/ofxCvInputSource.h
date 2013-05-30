/*
 * ofxCvInputSource.h
 *
 *  Created on: Jun 20, 2012
 *      Author: spta32
 */

#ifndef OFXCVINPUTSOURCE_H_
#define OFXCVINPUTSOURCE_H_

#include "ofMain.h"

enum InputType{
	TYPE_VideoPlayer,
	TYPE_LiveVideo,
	TYPE_Image
};

class ofxCvInputSource{
public:

	InputType type;

	ofxCvInputSource();
	virtual ~ofxCvInputSource();

	virtual void close() = 0;

	virtual void update() = 0;
	virtual bool useFrame() = 0; //return?!

	virtual void draw(float x = 0, float y = 0) = 0;
	virtual void drawDataLayer(float x = 0, float y = 0){};

	virtual void setPaused(bool paused) = 0;

	virtual bool isNewFrame() = 0;

	virtual unsigned char * getPixels() = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
};

#endif /* OFXCVINPUTSOURCE_H_ */
