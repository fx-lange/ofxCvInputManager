/*
 * ofxCvLiveInput.h
 *
 *  Created on: Jun 27, 2012
 *      Author: spta32
 */

#ifndef OFXCVLIVEINPUT_H_
#define OFXCVLIVEINPUT_H_

#include "ofMain.h"
#include "ofxCvInputSource.h"

class ofxCvLiveInput : public ofxCvInputSource {
public:
	ofVideoGrabber videoGrabber;

	ofxCvLiveInput(){
		type = TYPE_VideoPlayer;
	}
	virtual ~ofxCvLiveInput(){
		close();
	}

	virtual void setup(float w, float h){
		videoGrabber.initGrabber(w,h);
		type = TYPE_LiveVideo;
	}

	virtual void close(){
		videoGrabber.close();
	}

	virtual void update(){
		videoGrabber.grabFrame();
	}

	virtual bool useFrame(){
		return isNewFrame();
	}

	virtual void draw(float x = 0, float y = 0){
		videoGrabber.draw(x,y);
	}

	virtual void setPaused(bool paused){};

	virtual bool isNewFrame(){
		return videoGrabber.isFrameNew();
	}

	virtual unsigned char * getPixels(){
		return videoGrabber.getPixels();
	}
	virtual float getWidth(){return videoGrabber.width;}
	virtual float getHeight(){return videoGrabber.height;}

protected:
};

#endif /* OFXCVLIVEINPUT_H_ */
