#include "network.hpp"
#include "neuron.hpp"
#include <iostream>
using namespace std;

/*! \file */

int main() {

//INITIALIZATION OF tstart AND tstop 
/// 1) tstart and tstop are asked to the user
	double tstart;
	double tstop;
	
	cout << "Enter a time interval [tstart,tstop] for the simulation." << endl;
	cout << "tstart = " << flush;
	cin >> tstart;
	while(cin.fail()) {
	cout << "Error, you have to enter a double." << endl;
	cin.clear();
	cin.ignore(256,'\n');
	cout << "tstart = " << flush;
	cin >> tstart;
	}

	cout << "tstop = " << flush;
	cin >> tstop;
	while(cin.fail()) {
	cout << "Error, you have to enter a double." << endl;
	cin.clear();
	cin.ignore(256,'\n');
	cout << "tstop = " << flush;
	cin >> tstop;
	}
  
//SIMULATION OF THE NETWORK FROM tstart TO tstop
/// 2) initialization and simulation of the network from tstart to tstop
	Network network;
	network.simulationLoop(tstart, tstop);		
  
	return 0;
}
