#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofSetColor(0);

	this->shader.load("shader/shader.vert", "shader/shader.frag");
	this->tex1.allocate(ofGetWidth(), ofGetHeight());
	this->tex2.allocate(ofGetWidth(), ofGetHeight());

	this->tex1.begin();
	ofClear(0);

	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 5) {

		ofVertex(250 * cos(deg * DEG_TO_RAD) + ofGetWidth() * 0.5, 250 * sin(deg * DEG_TO_RAD) + ofGetHeight() * 0.5);
	}
	ofEndShape();

	this->tex1.end();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->tex2.begin();
	ofClear(0);

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int size = ofGetWidth();
	for (int i = 0; i < 8; i++) {
			
		int line_param = ofRandom(1, 5);
		int start_param = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005) * 100;
		vector<glm::vec2> vertices;
		for (int param = start_param; param < start_param + line_param; param++) {

			vertices.push_back(glm::vec2(this->make_point(size * 0.95, param)));
		}

		start_param += 50 + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -15, 15);
		for (int param = start_param; param < start_param + line_param; param++) {

			vertices.push_back(glm::vec2(this->make_point(size * 0.95, param)));
		}

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
	}

	this->tex2.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->tex1.getTexture(), 1);
	this->shader.setUniformTexture("tex2", this->tex2.getTexture(), 2);

	ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}