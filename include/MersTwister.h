#pragma once
#include <Random2.h>
#include <Normals.h>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

// my own random number generator class to plug in to Joshi's RandomMain3.cpp
// using a random number generator from Boost.

class MersTwister {
	typedef boost::mt19937                     ENGINE;    // Mersenne Twister 
    typedef boost::normal_distribution<double> DISTRIBUTION;   // Normal Distribution
    typedef boost::variate_generator<ENGINE,DISTRIBUTION> GENERATOR;    // Variate generator
private:
    ENGINE  eng;
    DISTRIBUTION dist; // this will be initiialized in the init list of the constructor
    GENERATOR gen; // this will be initiialized in the init list of the constructor
//	long Seed;
public:
	void SetSeed(long Seed) {} // do nothing since we dont use Seed
	MersTwister();
	double getOneUniform();	
};

class RandomMersTwister : public RandomBase
{
public:

    RandomMersTwister(unsigned long Dimensionality, unsigned long Seed_=1);

    virtual RandomBase* clone() const;    
    virtual void GetUniforms(MJArray& variates);    
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
    MersTwister InnerGenerator;
    unsigned long InitialSeed;
	// remembers 1/max+1 in ParkMiller for efficiency
//    double Reciprocal;
};
