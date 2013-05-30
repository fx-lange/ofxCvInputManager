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
	eFirstFrame = eNextFrame = ePrevFrame = false;
	bStopable = false;
	bChangeSettings = false;
	bNewFrame = false;
	bInputChanged = true;
}

ofxCvInputManager::~ofxCvInputManager() {
}

void ofxCvInputManager::setup(){
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
		input->update();
		bNewFrame = input->useFrame() || bNewFrame;
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

float ofxCvInputManager::getInputWidth(){
	return inputs[inputIdx]->getWidth();
}

float ofxCvInputManager::getInputHeight(){
	return inputs[inputIdx]->getHeight();
}

void ofxCvInputManager::nextInput(){
	setPaused(true);
	inputIdx = (inputIdx + 1) % inputs.size();
	setPaused(false);
	bInputChanged = true;
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
			case OF_KEY_UP:
				nextInput();
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

