#include "ofxCvImageInput.h"

ofxCvImageInput::ofxCvImageInput() {
	type = TYPE_Image;
}

ofxCvImageInput::~ofxCvImageInput() {}

void ofxCvImageInput::close(){
	image.clear();//TODO clear == close?
}

void ofxCvImageInput::draw(float x,float y){
	image.draw(x,y);
}

unsigned char * ofxCvImageInput::getPixels(){
	return image.getPixels();
}
