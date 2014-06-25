//
//  imageSequencer.h
//  cameraRibbonExample
//
//  Created by Peng Cheng on 6/25/14.
//
//

#ifndef __cameraRibbonExample__imageSequencer__
#define __cameraRibbonExample__imageSequencer__

#include "ofMain.h"
class imageSequencer{
public:
    
    void loadImage();
    void init(int x, int y, int w, int h);
    void update();
    void draw();
    
    vector <ofImage> images;
    
    int frameIndex;
    int timer;
    int width, height;
    ofPoint setPos;
    
};


#endif /* defined(__cameraRibbonExample__imageSequencer__) */
