#include "neuron.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
using namespace std;

//CONSTRUCTOR
Neuron::Neuron(int id = 0) 
: id_(id), potential_(0.0), nbSpikes_(0), isRefractory_(0), time_(0.0), buffer_(16, 0)
{}

//GETTERS
double Neuron::getPotential() const {
  return potential_;
}
int Neuron::getNbSpikes() const {
  return nbSpikes_;
}

//SETTERS
void Neuron::setTime(double time) {
  time_ = time;
}
void Neuron::setBuffer(int position, double J) {
	buffer_[position] += J;
}


//UPDATE OF THE NEURON STATE AT TIME t
void Neuron::updatePotential(double background, double Iext) {
    int a(floor(time_/h_));
       
    potential_ = cste1_*potential_ + cste2_*Iext + buffer_[a % 16] + 0.1*background;
    buffer_[a % 16] = 0.0;
}
  
//RETURN TRUE IF THE NEURON IS SPIKING
bool Neuron::isSpiking() {
	return (potential_ > Vth_);
}

//SIMULATION LOOP OF THE NEURON
void Neuron::simulationLoop(int nbSimulationLoops, double background, double Iext) {
	for(int i(0); i < nbSimulationLoops; ++i) {
		if(isRefractory_ > 0) {
		  --isRefractory_;
		  potential_ = Vreset_;
		} else {            
		  updatePotential(background, Iext);
		  if(isSpiking()) {
			nbSpikes_ += 1;
			isRefractory_ = (tauref_ / h_);
		  }
		}
		time_ += h_;
	}
}
  
//DESTRUCTOR
Neuron::~Neuron() {
}
