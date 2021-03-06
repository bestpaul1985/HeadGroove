#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetWindowShape(1024, 768);
    video.initGrabber(1024, 768);
    kal.allocate(1024, 768);
    
    soundStream.listDevices();
    int bufferSize = 256;
	
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    video.update();
    
    kal.setTexture(video.getTextureReference());
    kal.setRotation(ofGetElapsedTimef()*0.1*scaledVol);
    kal.update();
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.2, 0.0, 1.0, true);
    
	//record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if bigger the the size we want to record - drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}

    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor(abs(sin(ofGetElapsedTimef()*0.01)*255),
                                 abs(sin(ofGetElapsedTimef()*0.03)*255),
                                 abs(sin(ofGetElapsedTimef()*0.08)*255)),
                         ofColor(0));
    ofSetColor(255, 200);
    kal.draw(1,0);
    
}


//--------------------------------------------------------------


void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}