//
//
//                        PayOffRegistration.cpp
//
//

#include <PayOffConstructible.h>


// this is an unnamed namespace so we can't access the things inside -  these are global variables
//of type PayOffHelper<PayOffCall> etc. Being global variables, they are initialized at the start of 
// the program and this initialization of payoff aux class registers the payoffs.
namespace
{
 PayOffHelper<PayOffCall> RegisterCall("call");
 
 PayOffHelper<PayOffPut> RegisterPut("put");
 //Ex 10.1
//Define a global variable named RegisterStraddle of type PayOffHelper<PayOffStraddle> - this object
 // should register the class with the factory
 PayOffHelper<PayOffStraddle> RegisterStraddle("straddle");
 //Now register a forward
 PayOffHelper<PayOffForward> RegisterForward("forward");
 PayOffHelper<PayOffDoubleDigital> RegisterDoubleDigital("doubledigital");
 PayOffHelper<PayOffDigitalCall> RegisterDigitalCall("digitalcall");
  PayOffHelper<PayOffStock> RegisterStock("stock");
  // This "payoff" has payoff equal to f'(S_T)S_T so if we value this option by MC and divide by S_0 then we get
  // an estimate of the delta of a vanilla call (using formula (7.32) in Joshi Concepts)
  PayOffHelper<PayOffDeltaCall> RegisterDeltaCallPathwise("deltaCallPathwise");
}




