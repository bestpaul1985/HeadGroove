#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(255);

    ofEnableDepthTest();
    usecamera = false;
    loadImage();
  
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    if(!usecamera){
        ofVec3f sumOfAllPoints(0,0,0);
        for(unsigned int i = 0; i < points.size(); i++){
            points[i].pos.z -= 4;
            sumOfAllPoints += points[i].pos;
        }
        center = sumOfAllPoints / points.size();
    }
    
    
    for (int i=0; i<myFlies.size(); i++) {
        myFlies[i].update();
    }
    
    
    cout<<flyImg.size()<<endl;
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(usecamera){
        camera.begin();
    }

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
		float thickness = ofMap(distance, 0, 60, 20, 2, true);
		ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
		ofVec3f rightPoint = thisPoint+toTheRight*thickness;
		mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
		mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
	}

	mesh.draw();

    for (int i=0; i<myFlies.size(); i++) {
        myFlies[i].draw();
    }
    
    if(usecamera){
    	camera.end();
    }
   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == ' ' ) {
            imageSequencer temSeq;
            myFlies.push_back(temSeq);
            myFlies.back().init(points.back().pos, 100, 100, usecamera);
        
            for (int i=0; i<flyImg.size(); i++) {
                ofImage * image = new ofImage;
                image = &flyImg[i];
                myFlies.back().images.push_back(image);
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

//--------------------------------------------------------------
void ofApp::loadImage(){
    
    ofDirectory dir;
    
    int nFiles = dir.listDir("fly");
    if(nFiles) {
        
        for(int i=0; i<dir.numFiles(); i++) {
            string filePath = dir.getPath(i);
            flyImg.push_back(ofImage());
            flyImg.back().loadImage(filePath);
        }
    }
}
