//
//
//                        Random2.h
//
//

#ifndef RANDOM2_H
#define RANDOM2_H

#include <Arrays.h>


// This is the abstract base random number generator class that generates a certain number (given by dimensionality)
// of random numbers from a uniform or normal distribution (using GetUniforms or GetGaussians)
//
// This defines an interface. Things like antithetic will inherit from this class so we can plug in an antithetic 
// object wherever we plugged in our random generator. 
// Classes like antithetic and RandomParkMiller inherit from this - and share the same interface. 
// See Random3.h for a concrete inherited random numbers class.
class RandomBase
{
public:

    RandomBase(unsigned long Dimensionality);

    inline unsigned long GetDimensionality() const;

    virtual RandomBase* clone() const=0;
    virtual void GetUniforms(MJArray& variates)=0;
    virtual void Skip(unsigned long numberOfPaths)=0;
    virtual void SetSeed(unsigned long Seed) =0;
    virtual void Reset()=0;
	// uses a random draw from GetUniforms to generate a draw from a normal dist.: this is not pure virtual
	// so we only have to redefine this class if we want to. 
    virtual void GetGaussians(MJArray& variates);
	// concrete virtual so that in the inherited class the base class can be told that the dimension has been
	// changed.
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
    unsigned long Dimensionality;

};

unsigned long RandomBase::GetDimensionality() const
{
    return Dimensionality;
}

#endif

