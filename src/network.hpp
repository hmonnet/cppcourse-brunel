#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "neuron.hpp"
#include <vector>

class Neuron;

class Network {
	private:
		std::vector <Neuron*> neurons_; ///< All the neurons of the network
		std::vector<std::vector<int>> connexions_; ///< All the connexions between the neurons
		double clock_; ///< Clock
		int nbSpikes_; ///< Number of spikes that occured in the network at each time step
		
	public:
////CONSTRUCTOR
		/**
		* Constructor:
		* neurons_ is initialized with 10000 excitatory neurons and 2500 inhibitory neurons
		*/
		Network();
		
		
//INITIALIZATION OF THE CONNECTIONS
		/**
		* Initialization of random connections between the neurons:
		* each neuron targets 1000 excitatory neurons and 250 inhibitory neurons
		*/
		void connexions();
				
//SIMULATION LOOP OF THE NETWORK
		/**
		* Simulation loop of the network
		* @param tstart Time at which the simulation starts
		* @param tstop Time at which the simulation stops
		*/
		void simulationLoop(double tstart, double tstop);
		
//DESTRUCTOR
		/**
		* Destructor:
		* neurons_ is destroyed
		*/	
		~Network();
	
};

#endif
