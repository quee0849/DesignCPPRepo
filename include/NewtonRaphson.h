//
//
//                  NewtonRaphson.h
//
//



template<class T, double (T::*Value)(double) const, double (T::*Derivative)(double) const >
double NewtonRaphson(double Target,
                 double Start,
                 double Tolerance,
                 const T& TheObject)
{
	const int maxIterations= 20;
	const int maxXValue= 1000;
    int counter=0; //Ex 9.1
    double y = (TheObject.*Value)(Start);
   
    double x=Start;

    while ( fabs(y - Target) > Tolerance )
    {
        double d = (TheObject.*Derivative)(x);
        counter++;  
        x+= (Target-y)/d;

        y = (TheObject.*Value)(x);
		if (counter> maxIterations || fabs(x) > maxXValue ) {
		 throw("Does not seem to converge to within Tolerance in reasonable time or x appears to be diverging");}
    }

    return x;
}



