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

#pragma once

#include "ofMain.h"
#include "imageSequencer.h"

class point{
public:
    ofVec3f pos;
    bool bAction;
    ofColor color;
};

class ofApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
	
	//this holds all of our points
    vector<point> points;
    //this keeps track of the center of all the points
    ofVec3f center;
    
	//our camera objects for looking at the scene from multiple perspectives
	ofCamera camera;
	
	//if usecamera is true, we'll turn on the camera view
    bool usecamera;
    
    imageSequencer myFly;
};
