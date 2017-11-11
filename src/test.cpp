#include <iostream>
#include "neuron.hpp"
#include "gtest/gtest.h"

/*! \file */

//TEST IF THE MEMBRANE POTENTIAL IS COMPUTED CORRECTLY WITH A POSITIVE CURRENT
/**
* Test is the membrane potential is computed correctly with a positive current
*/
TEST(OneNeuron, PositiveCurrent) {
	Neuron neuron(0);
	
	neuron.simulationLoop(1, 0.0, 1.00);
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getPotential(), 1e-3);
	/// 1) with a Iext of 1.00, membrane potential expectd after one simulation loop
	
	neuron.simulationLoop(1000, 0.0, 1.00);
	EXPECT_NEAR(20.0, neuron.getPotential(), 2e-1);
	/// 2) with an Iext of 1.00, membrane potential expected to be near 20.0 after 1000 simulation loops
	
	neuron.simulationLoop(1000, 0.0, 0.0);
	EXPECT_NEAR(0.0, neuron.getPotential(), 2e-1);
	/// 3) with an Iext of 0.00, membrane potential expected to be near 0.0 after 1000 simulation loops
	
} 

//TEST IF THE MEMBRANE POTENTIAL IS COMPUTED CORRECTLY WITH A NEGATIVE CURRENT
/**
* Test is the membrane potential is computed correctly with a negative current.
*/
TEST(OneNeuron, NegativeCurrent) {
	Neuron neuron(0);
	
	neuron.simulationLoop(1, 0.0,-1.00);
	EXPECT_NEAR(-20.0*(1.0-std::exp(-0.1/20.0)), neuron.getPotential(), 1e-3);
	/// 1) with a Iext of -1.00, membrane potential after one simulation loop 
	
	neuron.simulationLoop(1000, 0.0, -1.00);
	EXPECT_NEAR(-20.0, neuron.getPotential(), 2e-1);
	/// 2) with an Iext of -1.00, membrane potential expected to be near -20.0 after 1000 simulation loops
	
}

//TEST IF THE SPIKE ARRIVES AT THE RIGHT TIME
/**
* Test if the spike arrives at the right time
*/
TEST(OneNeuron, SpikeTimes) {
	Neuron neuron(0);
	
	neuron.simulationLoop(923, 0.0, 1.01);
	EXPECT_EQ(0, neuron.getNbSpikes());
	neuron.simulationLoop(1, 0.0, 1.01);
	EXPECT_EQ(1, neuron.getNbSpikes());
	/// 1) with a Iext of 1.01 => first spike expected at time 92.4
	
	neuron.simulationLoop(943, 0.0, 1.01);
	EXPECT_EQ(1, neuron.getNbSpikes());
	neuron.simulationLoop(1, 0.0, 1.01);
	EXPECT_EQ(2, neuron.getNbSpikes());
	/// 2) with a Iext of 1.01 => second spike expected at time 186.8

}

//TEST IF THE SECOND NEURON (IEXT = 0) RECEIVES A J WITH THE CORRECT DELAY WHEN THE FIRST NEURON SPIKE
/**
* Test if the second neuron (Iext=0.00) receives a J with the correct delay when the first neuron spike
*/
TEST(TwoNeurons, NoPSSpike) {
	Neuron neuron1(1), neuron2(2);
	int delay(15);
	
	for(int i(0); i < (924+delay); ++i) {	
		neuron1.simulationLoop(1, 0.0, 1.01);
		if(neuron1.isSpiking()) {
			neuron2.setBuffer((i+delay) % 16, 0.1);
			EXPECT_EQ(0.0, neuron2.getPotential());
		}
		neuron2.simulationLoop(1, 0.0, 0.0);
	}
	
	EXPECT_NEAR(0.1, neuron2.getPotential(), 1e-2);	
}

//TEST IF THE SECOND NEURON (IEXT = 1.00) SPIKES THANKS TO THE J RECEIVED FROM THE SPIKE OF THE FIRST NEURON
/**
* Test if the second neuron (Iext=1.00) spikes thanks to the J received from the spike of the first neuron
*/
TEST(TwoNeurons, WithPSSpike) {
	Neuron neuron1(1), neuron2(2);
	int delay(15);
	
	for(int i(0); i < (1868+delay); ++i) {	
		neuron1.simulationLoop(1, 0.0, 1.01);
		if(neuron1.isSpiking()) {
			neuron2.setBuffer((i+delay) % 16, 0.1);
			EXPECT_EQ(0, neuron2.getNbSpikes());
		}
		neuron2.simulationLoop(1, 0.0, 1.00);
	}
	
	EXPECT_EQ(1, neuron2.getNbSpikes());	
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 
}
