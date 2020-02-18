#include "ofApp.h"

/*
 Shows how to use OSC messages from Wekinator to rotate the Penguin 3D model in the oF ofxAssimpModel example.
*/
float xRotation = 0;
float yRotation = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    
    ofSetVerticalSync(true);
    
    // load the first model
    model.loadModel("penguin.dae", 20);
    // model info
    curFileInfo = ".dae";
    
    // this loads in the model directly into a mesh
    // ofMesh can only read in .plys that are in the ascii and not in the binary format.
    bUsingMesh = false;
    mesh.load("penguin.ply");
    meshNode.setOrientation(glm::angleAxis(ofDegToRad(-90.f), glm::vec3{1.f, 0.f, 0.f}));
    
    // you can create as many rotations as you want
    // choose which axis you want it to effect
    // you can update these rotations later on
    // these rotation set the model so it is oriented correctly
    model.setRotation(0, 180, 1, 0, 0);
    model.setScale(0.9, 0.9, 0.9);
    light.setPosition(0, 0, 500);
    
    cameraOrbit = 0;
    cam.setDistance(700);
    
    //set help text to display by default
    bHelpText  = true;
    
    //Start listening for OSC messages
    receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //cameraOrbit += ofGetLastFrameTime() * 20.; // 20 degrees per second;
    //cam.orbitDeg(cameraOrbit, 0., cam.getDistance(), {0., 0., 0.});
	
    cam.orbitDeg(xRotation * 360, yRotation * 160, cam.getDistance(), {0., 0., 0.});
    
    //Receive any incoming OSC messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // If it's the message we're expecting from Wekinator:
        if(m.getAddress() == "/wek/outputs"){
			//visage droite 
			
			if (m.getArgAsFloat(0) == 1.f) {
				xRotation += 0.01;

			}
			//visage gauche
			if (m.getArgAsFloat(0) == 2.f) {
				xRotation -= 0.01;
			}
			//visage haut
			if (m.getArgAsFloat(0) == 3.f) {
				yRotation -= 0.01;
			}
			//visage bas
			if (m.getArgAsFloat(0) == 4.f) {
				yRotation += 0.01;
			}
			//visage normal
			if (m.getArgAsFloat(0) == 5.f) {
				
			}
			//visage gros
			if (m.getArgAsFloat(0) == 6.f) {
				cam.setDistance(cam.getDistance() - 10);
			}
			//visage petit
			if (m.getArgAsFloat(0) == 7.f) {
				cam.setDistance(cam.getDistance() + 10);
			}

			
             //Use second float in OSC message for y rotation
        } else{
            // unrecognized message: display on the bottom of the screen
            string msgString;
            msgString = m.getAddress();
            msgString += ":";
            for(size_t i = 0; i < m.getNumArgs(); i++){
                
                // get the argument type
                msgString += " ";
                msgString += m.getArgTypeName(i);
                msgString += ":";
                
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msgString += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msgString += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msgString += m.getArgAsString(i);
                }
                else{
                    msgString += "unhandled argument type " + m.getArgTypeName(i);
                }
            }
            
            cout << "Unexpected message: " << msgString << endl;
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // so the model isn't see through.
    ofEnableDepthTest();
    
    light.enable();
    
    cam.begin();
    ofColor(255,255);
    if (bUsingMesh){
        // draws the ply file loaded into the mesh is you pressed 6
        meshNode.transformGL();
        mesh.draw();
        meshNode.restoreTransformGL();
    } else {
        // draws all the other file types which are loaded into model.
        model.drawFaces();
    }
	
    cam.end();
    
    light.disable();
    
    ofDisableDepthTest();

    stringstream ss;
    ss << "Receives 2 outputs from Wekinator: x and y rotation. Listens on port 12000." << endl << endl;
    ss << "Each of these values is expected in the range 0-1 (0-100% rotation)."<<endl;
    ofDrawBitmapString(ss.str().c_str(), 20, 20);
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
