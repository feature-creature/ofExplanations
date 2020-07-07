#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofVideoPlayer video;

    int w;
    int h;
    int totalPixelValues;
    int totalFrames;
    int frameCount;

    vector <unsigned long int> sumVideoData; // 32 bit (0 - 4,294,967,297)
    unsigned char* avgVideoData; // 8 bit (0 - 255) pointer
    ofTexture avgTexture;

};
