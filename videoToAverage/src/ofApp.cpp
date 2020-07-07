#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
  // initialize the video
  video.setPixelFormat(OF_PIXELS_RGB);
  video.load("input.mkv");
  video.setLoopState(OF_LOOP_NONE);
  video.play();

  totalFrames = video.getTotalNumFrames();
  frameCount = 1;
 
  // initialize data structures
  // associated with the texture
  w = video.getWidth();
  h = video.getHeight();
  totalPixelValues = w*h*3; // 3 (r,g,b) 
  for(int i = 0; i<totalPixelValues;i++){
    sumVideoData.push_back(0); 
  }
  avgVideoData = new unsigned char [totalPixelValues];
  
  // initialize the texture
  avgTexture.allocate(w,h,GL_RGB);

}

//--------------------------------------------------------------
void ofApp::update(){
  video.update();

  if (video.isFrameNew()){

    frameCount++;
    // get the current frame's raw pixels data in 8 bit format (0 - 255)
    unsigned char * currentPixels = video.getPixels().getData();
    
    // int sum of each r g b value of each pixel
    // divide sum by num of frames
    // as "raw pixel data"
    for (int i = 0; i < totalPixelValues; i++){
      sumVideoData[i] += currentPixels[i];
      avgVideoData[i] = sumVideoData[i] / frameCount;
    }

    // update the texture to the newly averaged "raw pixel data" 
    avgTexture.loadData(avgVideoData,w,h,GL_RGB);
  }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
  //ofScale(0.5,0.5);
  
  // draw the video
  video.draw(0,0); 

  // draw the texture
  avgTexture.draw(w,0);

  // video status
  string videoFrameStatus = "video frame: " + to_string(frameCount) + " / " + to_string(totalFrames); 
  ofDrawBitmapString(videoFrameStatus, 10, h +30);
  ofDrawBitmapString("press p to pause/unpause video", 10, h +90);

  // avg image status
  string avgFrameStatus = "texture: " + to_string(frameCount) + " averaged frames"; 
  ofDrawBitmapString(avgFrameStatus, w +10, h +30);
  ofDrawBitmapString("press s to save texture as an image", w +10, h +90);

}
    
    

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  if(key =='s'){
    // convert the ofTexture to ofPixels
    ofPixels savedPixels;
    avgTexture.readToPixels(savedPixels);

    // convert the ofPixels to an ofImage
    ofImage savedImg;
    savedImg.allocate(w,h,OF_IMAGE_COLOR);
    savedImg.setFromPixels(savedPixels);

    //save image
    savedImg.save(to_string(frameCount)+"_of_"+ to_string(totalFrames) +"-frames"+".png");
    
    // alternatively you can save the image
    // in the update function
    // when the video is done by using
    // video.getIsMovieDone()
  }

  if(key == 'p'){
    video.isPaused() ? video.setPaused(false) : video.setPaused(true);
  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
