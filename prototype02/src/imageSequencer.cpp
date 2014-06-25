//
//  imageSequencer.cpp
//  cameraRibbonExample
//
//  Created by Peng Cheng on 6/25/14.
//
//

#include "imageSequencer.h"

void imageSequencer::loadImage(){

    ofDirectory dir;
    
    int nFiles = dir.listDir("fly");
    if(nFiles) {
        
        for(int i=0; i<dir.numFiles(); i++) {
            
            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
            
        }
        
    }
    
    frameIndex = 0;
    timer = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void imageSequencer::init(int x, int y, int w, int h){

    setPos.set(x, y);
    width = w;
    height = h;

}

//--------------------------------------------------------------
void imageSequencer::update(){
    
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
       
        ofSetColor(255);
        images[frameIndex].draw(-width/2, -height/2,width,height);
       
    }
    
}
















