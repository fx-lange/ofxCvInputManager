#ifndef OFXCVINPUTMANAGER_H_
#define OFXCVINPUTMANAGER_H_

#include "ofxCvVideoInput.h"
#include "ofxCvLiveInput.h"
#include "ofxCvImageInput.h"

class ofxCvInputManager {
public:
	ofxCvInputManager();
	virtual ~ofxCvInputManager();

	void setup();

	void addInputSource(ofxCvInputSource * source){
		inputs.push_back(source);
	}

//	//get color image to work with
	unsigned char * getPixels(){
		return inputs[inputIdx]->getPixels();
	}

	float getInputWidth();
	float getInputHeight();

	//update manager -> eg. play current input player
	bool update();

	void draw(float x = 0,float y = 0);
	void drawExtraData(float x = 0, float y = 0);

	void setPaused(bool paused);

	void debugStop(){
		if(bStopable)
			setPaused(true);

	}

	void togglePaused(){
		bPlay = !bPlay;
		setPaused(!bPlay);
	}

	bool isNewFrame(){
		return inputs[inputIdx]->isNewFrame();
	}

	void nextFrame();
	void previousFrame();

	virtual void keyPressed(ofKeyEventArgs & e);
	virtual void keyReleased(ofKeyEventArgs & e){}

protected:
	bool bPlay, bNewFrame, bChangeSettings;
	bool eNextFrame;
	bool ePrevFrame;
	bool eFirstFrame;

	bool bStopable;

	int inputIdx;
	vector<ofxCvInputSource *> inputs;
};

#endif /* OFXCVINPUTMANAGER_H_ */
