//                        Random3.h
// RandomBase is abstract class and defines the interface. 
// This is Joshi's random number generator class that writes into an MJArray a bunch of 
// random uniforms or Gaussians.
 
#ifndef RANDOM3_H
#define RANDOM3_H

#include <Arrays.h>
#include <Random2.h>

class RandomRand : public RandomBase
{
public:
   
    RandomRand(unsigned long Dimensionality, unsigned long InitialSeed_ = 1UL);

    virtual RandomBase* clone() const;    
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();


private:

    unsigned long InitialSeed;
};

#endif



