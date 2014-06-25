/**
 *
 * OFDevCon Example Code Sprint
 * Camera Ribbon example
 * This example generates ribbons along the mouse trail that descend in space
 * When you click space bar, you can
 *
 * Created by James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
 * Adapted during ofDevCon on 2/23/2012
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//just set up the openFrameworks stuff
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);
    
    spriteRenderer = new ofxSpriteSheetRenderer(1, 10000, 0, 300);
    spriteRenderer->loadTexture("image/spritFly.png", 600, GL_NEAREST);
  
    ofEnableAlphaBlending();

}

//--------------------------------------------------------------
void ofApp::update(){
   
    ofVec3f sumOfAllPoints(0,0,0);
    for(unsigned int i = 0; i < points.size(); i++){
        points[i].pos.z -= 4;
    }

    spriteRenderer->clear();
	spriteRenderer->update(ofGetElapsedTimeMillis());
    
   

}

//--------------------------------------------------------------
void ofApp::draw(){

    
	ofSetColor(0);

    ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for(unsigned int i = 1; i < points.size(); i++){

		ofVec3f thisPoint = points[i-1].pos;
		ofVec3f nextPoint = points[i].pos;
		ofVec3f direction = (nextPoint - thisPoint);
		float distance = direction.length();
		ofVec3f unitDirection = direction.normalized();
		ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
		ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
		float thickness = ofMap(distance, 0, 60, 80, 20, true);
		ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
		ofVec3f rightPoint = thisPoint+toTheRight*thickness;

//        ofColor col;
//        col.setHsb(ofMap(leftPoint.x, 0, ofGetWidth(), 0,255, true), 150, 255, ofMap(leftPoint.z, 0, -1000, 200, 50, true));
//        mesh.addColor(col);
		mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
//        mesh.addColor(col);
		mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
	}

	//end the shape
	mesh.draw();


    if(sprites.size()>0) 	{
		for(int i=sprites.size()-1;i>=0;i--)
		{
			
			if(points[sprites[i]->num].pos.z<-1000)
			{
				delete sprites[i];
				sprites.erase(sprites.begin()+i);
			}
			else{
				spriteRenderer->addCenterRotatedTile(&sprites[i]->animation, points[sprites[i]->num].pos.x, points[sprites[i]->num].pos.y, -1, F_NONE, ofMap(points[sprites[i]->num].pos.z, 0, -1000, 1, 0), 0 ,NULL, 255, 255, 255, ofMap(points[sprites[i]->num].pos.z, 0, -1000, 255, 0));
                
            }
		}
	}
    
    spriteRenderer->draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == ' ') {
        ofVec3f mousePoint(mouseX,mouseY,1);
        point temP;
        points.push_back(temP);
        points.back().pos.set(mouseX, mouseY,0);
        points.back().bAction = true;
        points.back().color.set(ofRandom(255), ofRandom(255), ofRandom(255));
        
        basicSprite * newSprite = new basicSprite();
		newSprite->pos.set(0,0,0);
		newSprite->animation = walkAnimation;
        newSprite->num = (points.size()-1);
		sprites.push_back(newSprite);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    point temP;
    points.push_back(temP);
    points.back().pos.set(mouseX, mouseY,0);
    points.back().bAction = false;
    points.back().color.set(255);
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}










