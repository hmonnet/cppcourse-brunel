#include "network.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <cmath>
using namespace std;

//CONSTRUCTOR
Network::Network()
: connexions_(12500, vector<int>(1250, 0)), clock_(0.0), nbSpikes_(0)
{
	for(int i(0); i < 12500; ++i) {
		neurons_.push_back(new Neuron(i));
	}
	cout << "The network has been created." << endl;
}


//INITIALIZATION OF THE CONNECTIONS
void Network::connexions() {
	random_device rd;
	std::mt19937 gen(rd());
	
	for(int n(0); n < 12500; ++n) {
		for(int excTarget(0); excTarget < 1000; ++excTarget) {
			uniform_int_distribution<> excDis (0, 9999);
			connexions_[n][excTarget] = excDis(gen);
		}
		
		for(int inhTarget(1000); inhTarget < 1250; ++inhTarget) {
			uniform_int_distribution<> inhDis (10000, 12499);
			connexions_[n][inhTarget] = inhDis(gen);
		}
	}
	cout << "Connexions between neurons have been done." << endl;
}

			
//SIMULATION LOOP OF THE NETWORK
void Network::simulationLoop(double tstart, double tstop) {
	clock_ = tstart;
	
	for(auto neuron: neurons_) {
		neuron->setTime(tstart);
	}
	
	connexions();
	
	cout << "Beginning of the simulation" << endl;
	
	random_device rd;
	mt19937 gen(rd());
	
	ofstream storeSpikes;
	storeSpikes.open("spikes.txt", ios::out|ios::app);
	ofstream storeNbSpikes;
	storeNbSpikes.open("nbSpikes.txt", ios::out|ios::app);
	
	while(clock_ < tstop) {
		int a((clock_ + 1.5)/0.1);
		int position(a % 16);
		
		for(int n(0); n < 10000; ++n) {
			poisson_distribution<> dis(2); //v_ext*h=20*0.1=2
			neurons_[n]->simulationLoop(1, dis(gen), 0.0);
			
			if(neurons_[n]->isSpiking()) {
				storeSpikes << clock_ << "	" << n << endl;
				nbSpikes_ += 1;
				for(int target(0); target < 1250; ++target) {
					neurons_[connexions_[n][target]]->setBuffer(position, 0.1);
				}
			}
		}
		for(int n(10000); n < 12500; ++n) {
			poisson_distribution<> dis(2); //v_ext*h=20*0.1=2
			neurons_[n]->simulationLoop(1, dis(gen), 0.0);
			
			if(neurons_[n]->isSpiking()) {
				nbSpikes_ += 1;
				for(int target(0); target < 1250; ++target) {
					neurons_[connexions_[n][target]]->setBuffer(position, -0.5);
				}
			}
		}
		
		storeNbSpikes << clock_ << "	" << nbSpikes_ << endl;
		nbSpikes_ = 0;
		clock_ += 0.1;
	}
	storeSpikes.close();
	storeNbSpikes.close();
	
	cout << "End of the simulation" << endl;
}
		
				
//DESTRUCTOR	
Network::~Network() {
	for(auto& neuron: neurons_) {
		delete neuron;
		neuron = nullptr;
    }
    cout << "The network has been destroyed." << endl;
}
