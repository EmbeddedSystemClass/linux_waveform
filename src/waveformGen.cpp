#include <iostream>
#include <fstream>
#include <cstdlib>
#include "waveformGen.hpp"

WaveformGen::WaveformGen(string signalFilePath, string dacScalePath, string dacOutPath) {
	ifstream fs(signalFilePath.c_str());
	string line;

	float scale;
	ifstream dacScaleFile(dacScalePath.c_str());
    dacScaleFile >> scale;
    dacScaleFile.close();

	scale *= 1000;

	if(fs.is_open()) {
		while(getline(fs, line)) {
			int v = atoi(line.c_str());
			this->samples.push_back((int)(v/scale));
		}
		this->it = this->samples.begin();
		fs.close();
	}

	this->outputFilePath = dacOutPath;
}

void WaveformGen::generateNextSample() {
	ofstream outputFile(outputFilePath.c_str());
	outputFile << this->getNextSample();
	outputFile.close();
}


int WaveformGen::getNextSample() {
	if(this->it == this->samples.end())
		this->it = this->samples.begin();

	return *(this->it++);
}
