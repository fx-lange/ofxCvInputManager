/*
 * ofxCvInputManager.h
 *
 *  Created on: Jun 20, 2012
 *      Author: spta32
 *      TODO inputs with different size
 */

#ifndef OFXCVINPUTMANAGER_H_
#define OFXCVINPUTMANAGER_H_

#include "ofxOpenCv.h"
#include "ofxCvVideoInput.h"

class ofxCvInputManager {
public:
	ofxCvInputManager();
	virtual ~ofxCvInputManager();

	void setup(float w, float h);

	void addInputSource(ofxCvInputSource * source){
		inputs.push_back(source);
	}

	//get color image to work with
	ofxCvColorImage * getInputImage();

	//update manager -> eg. play current input player
	void update();

	void draw(float x = 0,float y = 0);

	void setPaused(bool paused);

	void togglePaused(){
		bPlay = !bPlay;
		setPaused(!bPlay);
	}

	void nextFrame();
	void previousFrame();

	virtual void keyPressed(ofKeyEventArgs & e);
	virtual void keyReleased(ofKeyEventArgs & e){}

protected:
	float width, height;

	bool bPlay;
	bool eNextFrame;
	bool ePrevFrame;
	bool eFirstFrame;

	int inputIdx;
	vector<ofxCvInputSource *> inputs;

	ofxCvColorImage colorImg;
};

#endif /* OFXCVINPUTMANAGER_H_ */
