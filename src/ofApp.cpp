#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    //// KINECT SETUP ///
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();		// opens first available kinect
    kinect.setLed(ofxKinect::LED_GREEN);
    
    //// GUI SETUP ////
    gui.setup();
    gui.add(angle.set("Camera Angle", 20,0, 30));
    gui.add(move.set("Skip Points", 2, 1, 12));
    gui.add(posz.set("Z-axis", -750,-500, -2000));
    gui.add(size.set("Point Size", 0.5,0.25, 2));
    //gui.add(stripes.set("Stripes", 0, 2, 4));
    gui.add(noiseValue.set("Noise Value", 0,0, 50));
    gui.add(fill.setup("Color Fill", true));
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    kinect.setCameraTiltAngle(angle); // Update the camera angle
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    drawPointCloud();
}

//void ofApp::drawPointCloudMesh(){
//
//    int w = 640; // width
//    int h = 480; // height
//
//    ofMesh mesh;
//    ofVec3f pos;
//
//    if(mode){
//        mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//    } else{
//        mesh.setMode(OF_PRIMITIVE_POINTS);
//        glPointSize(3);
//    }
//
//    for(int y = 0; y < h; y += move) {
//        for(int x = 0; x < w; x += move) {
//
//            if(kinect.getDistanceAt(x, y) > 0 && kinect.getDistanceAt(x, y) <  1500) {
//
//                if(fill) {
//                    mesh.addColor(kinect.getColorAt(x,y));
//                }
//                // pos.set(kinect.getWorldCoordinateAt(x, y));
//                mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
//
//            }
//        }
//    }
//
//    ofPushMatrix();
//    // the projected points are 'upside down' and 'backwards'
//    ofScale(1, -1, -1);
//    ofTranslate(0, 0, -1000); // center the points a bit
//    ofEnableDepthTest();
//    mesh.draw(); // Draw the points
//
//    ofDisableDepthTest();
//    ofPopMatrix();
//}

void ofApp::drawPointCloud(){
    
    easyCam.begin(); // Start easyCam
    ofFloatPixels distancePixels = kinect.getDistancePixels();
    ofPushMatrix();
    ofScale(1, -1, -1); // Orient the point cloud properly
    ofTranslate(-320, -240, posz); // Translate to a better position
    ofPushStyle();
    
    for(int x = 0; x < kinect.width; x+= move) {
        for(int y = 0; y < kinect.height; y+= move) {
            
            int i = y * kinect.width + x;
            float z = distancePixels[i]; // DistancePixels return a float array of points in the z-axis
            
            pos.set(x, y, z); // Set the position of the points
            
            if( fill ) {
                ofSetColor(kinect.getColorAt(x, y)); // If fill = true then grab the color from the camera
            }else{
                ofSetColor(255); // Else make all the points white
            }
            float ran = ofRandom(noiseValue);
            pos.y += ran; // Add noise to the z position
            // If the distance is greater than 0 and less than 1500
            if(kinect.getDistanceAt(x, y) > 0 && kinect.getDistanceAt(x, y) <  1500) {
                
                ofDrawCircle(pos.x, pos.y,pos.z, size); // Draw the points
            }
        }
    }
    
    ofPopStyle();
    ofPopMatrix();
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
