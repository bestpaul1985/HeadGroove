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

    ofEnableDepthTest();
	//initialize the variable so it's off at the beginning
    usecamera = false;
    
    myFly.loadImage();
    myFly.init(ofGetWidth()/2, ofGetHeight()/2, 100, 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
	//don't move the points if we are using the camera
    if(!usecamera){
        ofVec3f sumOfAllPoints(0,0,0);
        for(unsigned int i = 0; i < points.size(); i++){
            points[i].pos.z -= 4;
            sumOfAllPoints += points[i].pos;
        }
        center = sumOfAllPoints / points.size();
    }
    
    myFly.update();
}

//--------------------------------------------------------------
void ofApp::draw(){


	//if we're using the camera, start it.
	//everything that you draw between begin()/end() shows up from the view of the camera
    if(usecamera){
        camera.begin();
    }

	ofSetColor(0);
	//do the same thing from the first example...
    ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for(unsigned int i = 1; i < points.size(); i++){

		//find this point and the next point
		ofVec3f thisPoint = points[i-1].pos;
		ofVec3f nextPoint = points[i].pos;

		//get the direction from one to the next.
		//the ribbon should fan out from this direction
		ofVec3f direction = (nextPoint - thisPoint);

		//get the distance from one point to the next
		float distance = direction.length();

		//get the normalized direction. normalized vectors always have a length of one
		//and are really useful for representing directions as opposed to something with length
		ofVec3f unitDirection = direction.normalized();

		//find both directions to the left and to the right
		ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
		ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));

		//use the map function to determine the distance.
		//the longer the distance, the narrower the line.
		//this makes it look a bit like brush strokes
		float thickness = ofMap(distance, 0, 60, 20, 2, true);

		//calculate the points to the left and to the right
		//by extending the current point in the direction of left/right by the length
		ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
		ofVec3f rightPoint = thisPoint+toTheRight*thickness;

		//add these points to the triangle strip
		mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
		mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
	}

	//end the shape
	mesh.draw();

    for (int i=0; i<points.size(); i++) {
        if (points[i].bAction) {
            ofPushMatrix();
            ofTranslate(points[i].pos);
            ofRotateZ(10);
            myFly.draw();
            ofPopMatrix();
        }
    }

	//if we're using the camera, take it away
    if(usecamera){
    	camera.end();
    }
    
   

   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  //hitting any key swaps the camera view
  
    
    if (key == ' ' ) {
        if (key == ' ') {
            ofVec3f mousePoint(mouseX,mouseY,1);
            point temP;
            points.push_back(temP);
            points.back().pos.set(mouseX, mouseY,0);
            points.back().bAction = true;
//            points.back().color.set(ofRandom(255), ofRandom(255), ofRandom(255));
        }
    }
    
    if (key == 'c') {
        usecamera = !usecamera;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    if(usecamera){
        float rotateAmount = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 360);
        ofVec3f furthestPoint;
        if (points.size() > 0) {
            furthestPoint = points[0].pos;
        }
        else
        {
            furthestPoint = ofVec3f(x, y, 0);
        }

        ofVec3f directionToFurthestPoint = (furthestPoint - center);
        ofVec3f directionToFurthestPointRotated = directionToFurthestPoint.rotated(rotateAmount, ofVec3f(0,1,0));
        camera.setPosition(center + directionToFurthestPointRotated);
        camera.lookAt(center);
    }
	//otherwise add points like before
    else{
        
        point temP;
        points.push_back(temP);
        points.back().pos.set(mouseX, mouseY,0);
        points.back().bAction = false;
        points.back().color.set(255);
    }
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
