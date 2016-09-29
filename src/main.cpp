#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "waveformGen.hpp"

using namespace std;

int main(int argc, char** argv) {

  if(argc != 15) { 
    cout<<"Usage: wavegen -s path_to_signal"<<endl; 
    cout<<"               -r sampling_rate_hz"<<endl;
    cout<<"               -o path_to_dac_output_file"<<endl;
    cout<<"               -i path_to_adc_input_file"<<endl;
    cout<<"               -d dac_resolution"<<endl;
    cout<<"               -a adc_resolution"<<endl;
    cout<<"               -v adc_voltage_mv"<<endl;
    return 0;
  }
	
  int option;
  char* signal;
  int sampling;
  char* dacOutFile;;
  char* adcInFile;;
  int dacResolution;
  int adcResolution;
  int adcVoltage;

  while((option = getopt(argc, argv, "r:o:s:i:d:a:v:")) != -1) {
    switch(option) {
      case 's':
        signal = optarg;
        break;
      case 'r':
        sampling = atoi(optarg);
        break;
      case 'o':
        dacOutFile = optarg;
        break;
      case 'i':
        adcInFile = optarg;
        break;
      case 'd':
        dacResolution = atoi(optarg);
        break;
      case 'a':
        adcResolution = atoi(optarg);
        break;
      case 'v':
        adcVoltage = atoi(optarg);
        break;
      default:
        break;
    }
  }

  long period = 1000000000/sampling;

  struct timespec tspec;
  tspec.tv_sec = period/1000000000;
  tspec.tv_nsec = period%1000000000;

  cout<<"Generating singal from file "<<signal<<endl;
  cout<<"freq "<<sampling<<"Hz ["<<period<<"ns]"<<endl;

  WaveformGen gen(signal, adcResolution, adcVoltage, adcInFile, dacResolution, dacOutFile);
  
  while(1) {
    gen.generateNextSample();
    nanosleep(&tspec, NULL);
  }
	
  return 0;
}

