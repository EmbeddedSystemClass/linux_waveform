#ifndef WAVEFORM_GEN_HPP
#define WAVEFORM_GEN_HPP

#include <string>
#include <vector>

using namespace std;

class WaveformGen {
	
public:

  WaveformGen(string signalFilePath, 
              int adcResolution, 
              int adcVoltage, 
              string adcInPath, 
              int dacResolution,
              string dacOutPath);
  int getNextSample();
  void generateNextSample();

private:
	
  vector<int> samples;
  vector <int>::iterator it;
  int sampleIndex;
  string outputFilePath;
};

#endif

