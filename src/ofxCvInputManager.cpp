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

		colorImg.allocate(width,height);
		ofRegisterKeyEvents(this);
	};

void ofxCvInputManager::update(){

	ofxCvInputSource * input = inputs[inputIdx];

	if(input->type == TYPE_VideoPlayer){
		ofxCvVideoInput * videoInput = (ofxCvVideoInput*)input;
		videoInput->update();

		if(eNextFrame){
			bPlay = false;
			setPaused(true);
			videoInput->nextFrame();
			eNextFrame = false;

		}else if(ePrevFrame){
			bPlay = false;
			setPaused(true);
			videoInput->prevFrame();
			ePrevFrame = false;
		}

		videoInput->useFrame();

	}else if(input->type == TYPE_LiveVideo){

	}else if(input->type == TYPE_Image){

	}

}

void ofxCvInputManager::draw(float x, float y){
	ofxCvInputSource * input = inputs[inputIdx];
	input->draw(x,y);
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

ofxCvColorImage * ofxCvInputManager::getInputImage(){
	return NULL;
}

void ofxCvInputManager::keyPressed(ofKeyEventArgs & e){
		switch (e.key) {
			case OF_KEY_LEFT:
				ePrevFrame = true;
				break;
			case OF_KEY_RIGHT:
				eNextFrame = true;
				break;
			case 'p':
				togglePaused();
				break;
			case 'r':
				if(inputs[inputIdx]->type == TYPE_VideoPlayer){
					((ofxCvVideoInput*)inputs[inputIdx])->firstFrame();
				}
				break;
			default:
				break;
		}
}

