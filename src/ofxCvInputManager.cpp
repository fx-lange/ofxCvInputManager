/*
 * ofxCvInputManager.cpp
 *
 *  Created on: Jun 20, 2012
 *      Author: spta32
 */

#include "ofxCvInputManager.h"

ofxCvInputManager::ofxCvInputManager() {
	bPlay = true;
	inputIdx = 0;
}

ofxCvInputManager::~ofxCvInputManager() {
}

void ofxCvInputManager::setup(float w, float h){
		width = w;
		height = h;

		bStopable = false;
		bChangeSettings = false;

		colorImg.allocate(width,height);
		ofRegisterKeyEvents(this);
	};

bool ofxCvInputManager::update(){
	if(!bPlay && !bChangeSettings){
		return false;
	}

	bNewFrame = false;

	ofxCvInputSource * input = inputs[inputIdx];

	if(input->type == TYPE_VideoPlayer){
		ofxCvVideoInput * videoInput = (ofxCvVideoInput*)input;
		videoInput->update();

		if(eNextFrame){
			bPlay = false;
			setPaused(true);
			videoInput->nextFrame();
			bNewFrame = true;
			eNextFrame = false;

		}else if(ePrevFrame){
			bPlay = false;
			setPaused(true);
			videoInput->prevFrame();
			bNewFrame = true;
			ePrevFrame = false;
		}

		bNewFrame = videoInput->useFrame() || bNewFrame;

	}else if(input->type == TYPE_LiveVideo){

	}else if(input->type == TYPE_Image){

	}


	return bNewFrame || bChangeSettings;
}

void ofxCvInputManager::draw(float x, float y){
	ofxCvInputSource * input = inputs[inputIdx];
	input->draw(x,y);
	input->drawDataLayer(x,y);
}

void ofxCvInputManager::drawExtraData(float x, float y){
	ofxCvInputSource * input = inputs[inputIdx];
	input->drawDataLayer(x,y);
}

void ofxCvInputManager::setPaused(bool paused){
	ofxCvInputSource * input = inputs[inputIdx];
	bPlay = !paused;
	input->setPaused(paused);
}

void ofxCvInputManager::nextFrame(){
	eNextFrame = true;
}

void ofxCvInputManager::previousFrame(){
	ePrevFrame =  true;
}

void ofxCvInputManager::keyPressed(ofKeyEventArgs & e){
		switch (e.key) {
			case OF_KEY_LEFT:
				ePrevFrame = true;
				bPlay = true;
				break;
			case OF_KEY_RIGHT:
				eNextFrame = true;
				bPlay = true;
				break;
			case 'p':
				togglePaused();
				break;
			case 'o':
				bChangeSettings = !bChangeSettings;
				break;
			case 'r':
				if(inputs[inputIdx]->type == TYPE_VideoPlayer){
					((ofxCvVideoInput*)inputs[inputIdx])->firstFrame();
				}
				setPaused(false);
				break;
			case 'i':
				bStopable = !bStopable;
				break;
			default:
				break;
		}

		//TODO draw/explain interface
}

