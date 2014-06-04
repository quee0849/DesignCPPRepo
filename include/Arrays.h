//
//
//
//		Arrays.h	
// A fancy array of doubles that supports things like finding the min/max values,
// applying a given function to each double in the array etc. 
//
//

#ifndef MJARRAYS_H
#define MJARRAYS_H

#ifdef USE_VAL_ARRAY

#include <valarray>

typedef  std::valarray<double> MJArray;

#else   // ifdef USE_VAL_ARRAY


class MJArray
{

public:

	explicit MJArray(unsigned long size=0);
	MJArray(const MJArray& original);
	
	~MJArray();

	MJArray& operator=(const MJArray& original);
	// defines array= a double called val
	// i.e set each entry in the array equal to val
	MJArray& operator=(const double& val);

	MJArray& operator+=(const MJArray& operand);
	MJArray& operator-=(const MJArray& operand);
	MJArray& operator/=(const MJArray& operand);
	MJArray& operator*=(const MJArray& operand);

	MJArray& operator+=(const double& operand);
	MJArray& operator-=(const double& operand);
	MJArray& operator/=(const double& operand);
	MJArray& operator*=(const double& operand);


	// apply a function f to each entry of the array and return a new array with the results (note it is const)
	MJArray apply(double f(double)) const;

	inline double operator[](unsigned long i) const;
	inline double& operator[](unsigned long i);

	inline unsigned long size() const;

	void resize(unsigned long newSize);

	double sum() const;
	double min() const;
	double max() const;

private:

// MJArray is backed by a raw array of doubles i.e a pointer to a double
	// ValuesPtr points to the start address of an array of length Size
	double* ValuesPtr;
	// EndPtr points to the end address of the array
	double* EndPtr;


	unsigned long Size;
	unsigned long Capacity;
	

};



inline double MJArray::operator[](unsigned long i) const
{
#ifdef RANGE_CHECKING
	if (i >= Size)
	{
		throw("Index out of bounds");
	}
#endif 

	return ValuesPtr[i];
}


inline double& MJArray::operator[](unsigned long i)
{
#ifdef  RANGE_CHECKING
	if (i >= Size)
	{
		throw("Index out of bounds");
	}
#endif 

	return ValuesPtr[i];
}

inline unsigned long MJArray::size() const
{
	return Size;
}
// this turns out to be a problem to use this as the base class PathDependent::CashFlow has MJArray as input so 
//we'd have to define a new function CashFlowNew or something in PathDependentGeometricAsian and change things this way.
// Easier to just work out the geometric mean in PathDependentGeomtetricAsian
class ExtendedArray : public MJArray {
public :
	double product() const; 
};





#endif // ifdef USE_VAL_ARRAY

#endif // ifndef MJARRAYS_H



