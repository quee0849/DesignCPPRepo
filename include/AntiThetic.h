//                  AntiThetic.h
//

#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include <Random2.h>
#include <wrapper.h>

// An example of the decorator pattern. We want to use Antithetic sampling with any
// random number generator - so i think this is why we have 
// AntiThetic(const Wrapper<RandomBase>& innerGenerator );
// The input of the constructor is basically a pointer to a RandomBase. 
// But we can actually input a wrapper/pointer of any object inheriting from RandomBase
// -- is this correct? See pg 97. We may just actually be using the object as a base class object and
// copying the data. 
class AntiThetic : public RandomBase
{

public:
    AntiThetic(const Wrapper<RandomBase>& innerGenerator );

    virtual RandomBase* clone() const;
    
    virtual void GetUniforms(MJArray& variates);

    virtual void Skip(unsigned long numberOfPaths);

    virtual void SetSeed(unsigned long Seed);

    virtual void ResetDimensionality(unsigned long NewDimensionality);

    virtual void Reset();
private:
    Wrapper<RandomBase> InnerGenerator;
// stores whether the next draw should be from the inner generator or be the
// antithetic of the last draw.
    bool OddEven;
// Contains an array of 
    MJArray NextVariates;
};

#endif
