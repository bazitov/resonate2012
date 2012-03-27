#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetFrameRate(60);
    
    outputImgURL= "test.jpg";
    img.loadImage("resonate.jpg");
    vidGrabber.initGrabber(640,480);
    
    arduino.setup();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    vidGrabber.grabFrame();

    arduino.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    ofLog(OF_LOG_NOTICE, "pct %f", arduino.pct);
    // img.draw(0,0, 400,800);
    
    bufferImg.clear();
	//if(bHasLoaded) glitchImg->clear();
	
	// set pixels and be sure we're converting it to RGB, we'll need this further for image recording
	// also alpha is needed for desktop mode 
	
    if (vidGrabber.isFrameNew()){
    unsigned char *		pixels = vidGrabber.getPixels();
        
    
    
	bufferImg.setFromPixels(pixels, 640, 480, OF_IMAGE_COLOR, true);
    
	
	// save image ( one frame ) locally
	bufferImg.saveImage(outputImgURL);
	
	// open buffer from file to get binary data
	ofBuffer file = ofBufferFromFile(outputImgURL, true);
	
	// send this data to glitch it!
	
    char * buffer = file.getBinaryBuffer();
    
    
	int scrambleStart = 617;
	int scrambleEnd = file.size();
	
	int nbOfReplacements =  (int)(arduino.pct*10);
	
	for(int i = 0; i < nbOfReplacements; i++) {
		
		int PosA = (int) (ofRandom (scrambleStart, scrambleEnd - scrambleStart));
		int PosB = (int) (ofRandom (scrambleStart, scrambleEnd - scrambleStart));
		
		char tmp	 =  buffer[PosA];
		buffer[PosA] =	buffer[PosB];
		buffer[PosB] =	tmp;
        
	}
    
    
    
	
	// create a new image from this
	ofBufferToFile(outputImgURL, file, true);
	
	// and then we try to load this image again
	// glitch can be randomly corrupted, so we have to be careful on this 
	
	
	if(!glitchImg.loadImage(file)) {
		
		
	}
	
    glitchImg.draw(0,0);
    
    //img.draw(0,0);
    }
}









//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}