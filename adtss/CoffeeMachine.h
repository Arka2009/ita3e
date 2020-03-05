#ifndef _CoffeeMachine_h_
#define _CoffeeMachine_h_
#include "adtss.h"

// Input and output values
typedef enum {
    NICKEL, DIME, QUARTER,
    CANCEL, WAIT, COFFEE, NOTHING
} IO_Type;

// Definition of the coffee machine
class CoffeeMachine: public adtss::Atomic<IO_Type> {
    public:
        // Constructor puts the model into its initial state
        CoffeeMachine();
        // State transition function
        void delta(const adtss::Bag<IO_Type>& xb);
        // Output function
        void output_func(adtss::Bag<IO_Type>& yb);
        // Garbage collection method does not do anything
        void gc_output(adtss::Bag<IO_Type>&){}
        // Get the amount of money in the machine
        int getInventoryValue() const { return 5*n+10*d+25*q; }
        // Get the amount of money left to the customer
        int getCustomerValue() const { return v; }
    
    private:
        int n, d, q; // Numbers of nickels, dimes, and quarters
        int v; // Value left to the customer
        bool cancel; // Status of the cancel button
        // Find coins in the inventory.
        void getCoins(int cents, int& nout, int& dout, int& qout);
};
#endif /* _CoffeeMachine_h_ */