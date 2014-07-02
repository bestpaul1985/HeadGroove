//
//  imageSequencer.cpp
//  cameraRibbonExample
//
//  Created by Peng Cheng on 6/25/14.
//
//

#include "imageSequencer.h"
void rotateToNormal(ofVec3f normal) {
	normal.normalize();
	
	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;
	
	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
}



//--------------------------------------------------------------
void imageSequencer::init(ofPoint &Pos, int w, int h, bool &Cam){

    orgPos = &Pos;
    width = w;
    height = h;
    frameIndex = 0;
    timer = ofGetElapsedTimeMillis();
    differ = ofRandom(0,100);
    bUseCam = &Cam;
}

//--------------------------------------------------------------
void imageSequencer::update(){
    previous = current;
    float t = (differ + ofGetElapsedTimef()) * .1;
	current.x = ofSignedNoise(t, 0, 0);
	current.y = ofSignedNoise(0, t, 0);
	current.z = ofSignedNoise(0, 0, t);
	current *= 400;
    
    if (ofGetElapsedTimeMillis() - timer > 45) {
        frameIndex ++;
        timer = ofGetElapsedTimeMillis();
    }
    
    if (frameIndex > images.size()-1) {
        frameIndex = 0;
    }

    
}

//--------------------------------------------------------------
void imageSequencer::draw(){
    
    if (images.size()>0) {
        animation();
    }
    
}

//--------------------------------------------------------------
void imageSequencer::animation(){

    ofPushMatrix();
    ofTranslate(*orgPos+current);
    if( (current - previous ).length() > 0.0 ){
        rotateToNormal(current - previous);
    }
    ofPushMatrix();
    ofRotateX(90);
    if(!*bUseCam)ofRotateZ(180);
    ofSetColor(255);
    images[frameIndex]->draw(-width/2, -height/2,width,height);
    ofSetColor(120);
    ofPopMatrix();

//    ofDrawAxis(32);
    ofPopMatrix();
    

}














