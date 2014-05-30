//
//
//                              wrapper.h
// This is our own smart pointer class
// So we want objects of this type to behave like pointers but for our class
// to take care of the memory management etc.
// We overload operator-> so that we can use -> as with raw pointers.
// And we overload operator* so that we can dereference as with raw pointers.
// Our object data simply consists of a raw pointer to the templatized object.
//
// Note there is no wrapper.cpp file since this class is templatized.


#ifndef WRAPPER_H
#define WRAPPER_H

template< class T>
class Wrapper
{
public:

    Wrapper()
    { DataPtr =0;}

    Wrapper(const T& inner)
    {
        DataPtr = inner.clone();
    }

    ~Wrapper()
    {
        if (DataPtr !=0)
            delete DataPtr;
    }
  
    Wrapper(const Wrapper<T>& original)
    {
        if (original.DataPtr !=0)
            DataPtr = original.DataPtr->clone();
        else
            DataPtr=0;
    }

    Wrapper& operator=(const Wrapper<T>& original)
    {
        if (this != &original)
        {
            if (DataPtr!=0)
                delete DataPtr;

            DataPtr = (original.DataPtr !=0) ? original.DataPtr->clone() : 0;
        }

        return *this;
    }

	// overload the * operator so we can dereference a wrapper object just like we can dereference a
	// raw pointer
    T& operator*()
    {
        return *DataPtr; 
    }

    const T& operator*() const
    {
        return *DataPtr; 
    }

    const T* const operator->() const
    {
        return DataPtr;
    }
	// overload -> so we can use as it as for raw pointers e.g.
	// wrapperObject->sampleMethod();
    T* operator->()
    {
        return DataPtr;
    }


private:
	// this is what we are 'wrapping' - just a raw pointer to our object.
    T* DataPtr;


};
#endif



