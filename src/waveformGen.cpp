#include <iostream>
#include <fstream>
#include <cstdlib>
#include "waveformGen.hpp"

WaveformGen::WaveformGen(string signalFilePath, 
                         int adcResolution, 
                         int adcVoltage, 
                         string adcInPath, 
                         int dacResolution, 
                         string dacOutPath) {

  int adcValue;
  ifstream adcInputFile(adcInPath.c_str());
  adcInputFile >> adcValue;
  adcInputFile.close();
  
  int supplyVoltage = adcVoltage * adcResolution / adcValue; 

  cout<<"supply "<<supplyVoltage<<endl;
  ifstream fs(signalFilePath.c_str());
  string line;
  if(fs.is_open()) {
    while(getline(fs, line)) {
      int v = atoi(line.c_str());
      this->samples.push_back((int)(v * dacResolution / supplyVoltage));
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
