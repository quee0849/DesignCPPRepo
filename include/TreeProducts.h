//
//
//
//                         TreeProducts.h
//
//

#ifndef TREE_PRODUCTS_H
#define TREE_PRODUCTS_H

class TreeProduct
{
public:
	//constructor: input the expiry time
    TreeProduct(double FinalTime_);
	// FinalPayOff - pure virtual 
	// input spot output the payoff e.g (S-K)_+ for a euro call
    virtual double FinalPayOff(double Spot) const=0;
    // gives the value at a point in the tree as a function of spot, time and
	// the discounted future value of the option
	// i.e we input the discounted future value of the option - the average of the value at the two child nodes, future discounted,
	// and then we out the value at the current node after updating depending on whether spot had breached a barrier for example
	// or if early exercise were profitable. 
	virtual double PreFinalValue(double Spot,
                                 double Time,
                                 double DiscountedFutureValue) const=0;
    virtual ~TreeProduct(){}
    virtual TreeProduct* clone() const=0;
	//getter for FinalTime
    double GetFinalTime() const;

private:
    double FinalTime;

};

#endif
