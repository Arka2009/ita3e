#include "CoffeeMachine.h"
using namespace adtss;

void CoffeeMachine::getCoins(int cents, int& nout, int& dout, int& qout) {
    int qc = q, dc = d, nc = n;
    nout = dout = qout = 0;
    // Pick quarters
    while (qc > 0 && cents >= 25) {
        qout++; qc--; cents -= 25;
    }
    // Pick dimes
    while (dc > 0 && cents >= 10) {
        dout++; dc--; cents -= 10;
    }
    // Pick nickels
    while (nc > 0 && cents >= 5) {
        nout++; nc--; cents -= 5;
    }
}

CoffeeMachine::CoffeeMachine():
    adtss::Atomic<IO_Type>(),
    n(10),d(10),q(10), // Start with ten of each type of coin
    v(0),cancel(false){}

void CoffeeMachine::delta(const Bag<IO_Type>& xb)   {
    // Sell a cup of coffee
    if (v >= 100) v -= 100;
    // Remove change if the cancel button is pressed
    if (cancel) {
        // Clear the cancel signal
        cancel = false;
        // Return the coins
        int nc, dc, qc;
        getCoins(v,nc,dc,qc);
        q -= qc; d -= dc; n -= nc;
        v = 0;
    }
    // Add change that was inserted by the customer
    // and check the state of the cancel button
    for (Bag<IO_Type>::const_iterator iter = xb.begin();
    iter != xb.end(); iter++) {
        if ((*iter) == NICKEL) { n++; v += 5; }
        else if ((*iter) == DIME) { d++; v += 10; }
        else if ((*iter) == QUARTER) { q++; v += 25; }
        else if ((*iter) == CANCEL) cancel = true;
    }
}

void CoffeeMachine::output_func(Bag<IO_Type>& yb) {
    // How much cash is in the machine?
    int cash = v;
    // If there is enough money for a cup of coffee, then pour a cup
    if (cash >= 100) {
        yb.insert(COFFEE);
        cash -= 100;
    }
    // Return any remaining change if the cancel button is pressed
    if (cancel) {
        int nreturn, dreturn, qreturn;
        getCoins(cash,nreturn,dreturn,qreturn);
        for (int i = 0; i < nreturn; i++) yb.insert(NICKEL);
        for (int i = 0; i < dreturn; i++) yb.insert(DIME);
        for (int i = 0; i < qreturn; i++) yb.insert(QUARTER);
    }
    // If no output was produced then put NOTHING into the output bag
    if (yb.empty()) yb.insert(NOTHING);
}