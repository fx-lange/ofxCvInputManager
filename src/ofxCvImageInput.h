#ifndef OFXCVIMAGEINPUT_H_
#define OFXCVIMAGEINPUT_H_

#include "ofxCvInputSource.h"

class ofxCvImageInput : public ofxCvInputSource{
public:
	ofxCvImageInput();
	virtual ~ofxCvImageInput();

	virtual void close();

	virtual void update(){}
	virtual bool useFrame(){return isNewFrame();}

	virtual void draw(float x = 0, float y = 0);

	virtual void setPaused(bool paused){};//TODO need to be abstract?
	virtual bool isNewFrame(){return true;} //TODO sure?

	virtual unsigned char * getPixels();
	virtual float getWidth(){return image.width;}
	virtual float getHeight(){return image.height;}
	virtual string getName(){ return name;}

	ofImage image;
	string name;
};
#endif /* OFXCVIMAGEINPUT_H_ */
