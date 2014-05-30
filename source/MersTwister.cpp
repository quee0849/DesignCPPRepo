#include "MersTwister.h"


MersTwister::MersTwister(): dist(0,1),gen(eng,dist)
 {}

double MersTwister::getOneUniform() 
{
return CumulativeNormal(gen());
}

//now defined this in the header file to do nothing
//void MersTwister::SetSeed(long Seed_) {
//	Seed = Seed_;
//}

RandomMersTwister::RandomMersTwister(unsigned long Dimensionality , unsigned long Seed_)
:    RandomBase(Dimensionality),
    InnerGenerator()
 ,  InitialSeed(Seed_)
{
//Reciprocal = 1/(1.0+InnerGenerator.Max());
}

RandomBase* RandomMersTwister::clone() const
{
    return new RandomMersTwister(*this);   
}

void RandomMersTwister::GetUniforms(MJArray& variates)
{
	//std::cout << "Calling GetUniforms with dim = " << GetDimensionality() << std::endl;
    for (unsigned long j=0; j < GetDimensionality(); j++)
        variates[j] = InnerGenerator.getOneUniform(); //works with 0.5;
}

// for a given number of paths, draw this number of random uniform draws and throw them away.
// ie put them in a temporary array tmp which will be destroyed when we go out of scope. 
void RandomMersTwister::Skip(unsigned long numberOfPaths)
{
    MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GetUniforms(tmp);
}

void RandomMersTwister::SetSeed(unsigned long Seed)
{

    InitialSeed = Seed;
    InnerGenerator.SetSeed(Seed);
}

void RandomMersTwister::Reset()
{
   InnerGenerator.SetSeed(InitialSeed);
}


void RandomMersTwister::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);
    InnerGenerator.SetSeed(InitialSeed);
}


