/*
 * ofxCvVideoInput.h
 *
 *  Created on: Jun 20, 2012
 *      Author: spta32
 */

#ifndef OFXCVVIDEOINPUT_H_
#define OFXCVVIDEOINPUT_H_

#include "ofxCvInputSource.h"

class ofxCvVideoInput : public ofxCvInputSource {
public:

	ofVideoPlayer player;

	ofxCvVideoInput(){}
	virtual ~ofxCvVideoInput(){
		type = TYPE_VideoPlayer;
	}

	ofxCvVideoInput(string videoFilename){
		setup(videoFilename);
	}

	virtual void setup(string videoFilename){
		player.loadMovie(videoFilename);
		player.play();
		bPlay = true;
		type = TYPE_VideoPlayer;
	}

	virtual void close(){
		player.close();
	}

	virtual void update(){
		player.update();
	}

	virtual bool useFrame(){
		return player.isFrameNew();
	}

	virtual void nextFrame(){
		player.nextFrame();
	}
	virtual void prevFrame(){
		player.previousFrame();
	}

	virtual void firstFrame(){
		player.firstFrame();
	}

	virtual void draw(float x = 0, float y = 0){
		player.draw(x,y);
	}

	virtual void setPaused(bool paused){
		bPlay = !paused;
		player.setPaused(paused);
	}

protected:
	bool bPlay;
};

#endif /* OFXCVVIDEOINPUT_H_ */
