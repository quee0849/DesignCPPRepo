//                      ParkMiller.h
//
//
#ifndef PARK_MILLER_H
#define PARK_MILLER_H
#include <Random2.h>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"


// Class to generate ONE random integer at a time by Park Miller. 
// This class is private data in the RandomParkMiller class that inherits fromm RandomBase
class ParkMiller
{
public:
    
    ParkMiller(long Seed = 1);

    long GetOneRandomInteger();
    void SetSeed(long Seed);

    static unsigned long Max();
    static unsigned long Min();

private:

    long Seed;

};

// This is an example of the adapter pattern since we have a random generator class ParkMiller
// that works and is effective but its interface does not fit with what we require. We therefore write
// another class RandomParkMiller around it that adapts the interface to what we want. 
class RandomParkMiller : public RandomBase
{
public:

    RandomParkMiller(unsigned long Dimensionality, unsigned long Seed=1);

    virtual RandomBase* clone() const;    
    virtual void GetUniforms(MJArray& variates);    
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

    ParkMiller InnerGenerator;
    unsigned long InitialSeed;
	// remembers 1/max+1 in ParkMiller for efficiency
    double Reciprocal;

};

// implementing another random number generator class here.


#endif
