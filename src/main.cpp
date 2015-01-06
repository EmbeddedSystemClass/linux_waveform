#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include "waveformGen.hpp"

using namespace std;

int main(int argc, char** argv) {

	if(argc < 9) { 
		cout<<"Usage: wavegen -s path_to_signal -r sampling_rate_hz -o path_to_dac_output_file -c path_to_dac_scale_file"<<endl;
		return 0;
	}
	
	int option;
	char* dac_out;
	char* dac_scale;
	char* signal;
	int	sampling;

	while((option = getopt(argc, argv, "r:o:s:c:")) != -1) {
		switch(option) {
			case 'r':
				sampling = atoi(optarg);
				break;
			case 'o':
				dac_out = optarg;
				break;
			case 'c':
				dac_scale = optarg;
				break;
			case 's':
				signal = optarg;
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

	WaveformGen gen(signal, dac_scale, dac_out );
	while(1) {
		gen.generateNextSample();
		nanosleep(&tspec, NULL);
	}
	
	return 0;
}

