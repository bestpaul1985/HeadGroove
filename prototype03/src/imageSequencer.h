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
    void init(ofPoint &Pos, int w, int h, bool &Cam);
    void update();
    void draw();
    void animation();
    
    vector <ofImage *> images;
    
    int frameIndex;
    int timer;
    int width, height;
    ofPoint *orgPos;
    ofPoint previous, current;
    int differ;
    bool *bUseCam;
};


#endif /* defined(__cameraRibbonExample__imageSequencer__) */
