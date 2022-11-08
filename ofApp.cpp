#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int radius = 180;
	float phi_deg_step = 5;
	float theta_deg_step = 5;

	for (float theta_deg = theta_deg_step; theta_deg < 180; theta_deg += theta_deg_step) {

		float noise_param = radius * cos((theta_deg)* DEG_TO_RAD);
		float noise_value = ofNoise(noise_param * 0.085, ofGetFrameNum() * 0.0065);
		float noise_x = 0;

		if (noise_value > 0.75) {

			noise_x = ofMap(noise_value, 0.75, 1, 0, 600);
		}
		else if (noise_value < 0.25) {

			noise_x = ofMap(noise_value, 0, 0.25, -600, 0);
		}

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			float upper_z = radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD);
			float bottom_z = radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD);

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(
				noise_x + radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				noise_x + radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				noise_x + radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(
				noise_x + radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
				radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
			vertices.push_back(glm::vec3(noise_x, 0, upper_z));
			vertices.push_back(glm::vec3(noise_x, 0, bottom_z));

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 4);
			this->face.addIndex(index + 2); this->face.addIndex(index + 3); this->face.addIndex(index + 5);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 3); this->frame.addIndex(index + 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(0);
	this->face.draw();

	ofSetColor(255);
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}