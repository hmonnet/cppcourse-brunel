#ifndef NEURON_HPP
#define NEURON_HPP
#include <vector>
#include <cmath>

class Neuron {
	private:
		int id_; ///< ID of the neuron 
		double potential_; ///< Membrane potential of the neuron (in mV)
		int nbSpikes_; ///< Number of times that the neuron spiked
		int isRefractory_; ///< Time during which the neuron is in a refractory period after spiking
		double time_; ///< Time (in ms)
		std::vector<double> buffer_; ///< Buffer that sums up all the spikes that arrive at each time step
 
	
//NEURON PARAMETERS
		const double h_=0.1; ///< Integration time step (in ms)
		const double tau_=20.0; ///< Membrane time constant (in ms)
		const double tauref_=2.0; ///< Membrane time constant for the refractory period (in ms)
		const double Vreset_=0.0; ///< Reset value of the membrane potential (in mV) 
		const double Vth_=20.0; ///< Spike threshold (in mV) 
		const double delay_=1.5; ///< Synaptic delay (in ms) 
		const double cste1_=exp(-h_/tau_); ///< Constant used for the update of the membrane potential 
		const double cste2_=20*(1-cste1_); ///< Constant used for the update of the membrane potential 
		
		
	public:
//CONSTRUCTOR	
		/**
		* Constructor
		* @param id ID of the neuron (0 by default)
		*/
		Neuron(int id);
		
//GETTERS		
		/**
		* Getter for the membrane potential
		* @return potential_
		*/
		double getPotential() const;
		
		/**
		* Getter for the number of spikes
		* @return nbSpikes_
		*/
		int getNbSpikes() const;

//SETTERS
		/**
		* Setter for the time
		* @param time
		*/
		void setTime(double time);
		
		/**
		* Setter for the buffer
		* @param position in the buffer: (time at which the neuron spike+delay of the neuron)%16
		* @param J spike response amplitude (0.1mV if the neuron is excitatory, -0.5mV if inhibitory)
		*/
		void setBuffer(int position, double J);
		
//UPDATE OF THE NEURON STATE AT TIME t
		/**
		* Update of the membrane potential
		* @param background noise (number of spikes that occurs in the whole brain) randomly determined by a poisson distribution
		* @param Iext external current only used for the unittests (when there is no background)
		*/
		void updatePotential(double background, double Iext);
		
//RETURN TRUE IF THE NEURON IS SPIKING
		/**
		* Is the neuron spiking ?
		* @return true if the neuron is spiking, false if not
		*/
		bool isSpiking();
		
//SIMULATION LOOP OF THE NEURON
		/**
		* Simulation loop of the neuron
		* @param nbSimulationLoops only used for the unittests (when there is no time interval for the simulation)
		* @param background used when calling updatePotential()
		* @param Iext used when calling updatePotential()
		*/
		void simulationLoop(int nbSimulationLoops, double background, double Iext);
				
//DESTRUCTOR
		/**
		* Destructor
		*/
		~Neuron();
		
};

#endif
