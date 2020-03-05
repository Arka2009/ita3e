#ifndef _dtss_simulator_h_
#define _dtss_simulator_h_
//#include "dtss_atomic.h"

namespace adtss {

    template <typename X> class Simulator {
        public:
            Simulator(Atomic<X>* model): model(model),t(0),output_up_to_date(false) {}
            void computeNextState(const Bag<X>& input);
            void computeOutput();
            unsigned int getTime() { return t; }
            void addEventListener(EventListener<X>* listener) {
                listeners.push_back(listener);
            }
        
        private:
            Atomic<X>* model; // The model to simulate
            unsigned int t; // Simulation clock
            bool output_up_to_date; // Is the model output up to date?
            typedef std::list<EventListener<X>*> ListenerList;
            Listener<X>*> ListenerList;
    };

    template <typename X> void Simulator<X>::computeNextState(const Bag<X>& input) {
        computeOutput(); // Compute the output at time t
        t++; // Advance the simulation clock
        model->delta(input); // Compute the new state of the model
        // Notify listeners that the state has changed
        for (typename ListenerList::iterator iter = listeners.begin();
        iter != listeners.end(); iter++)
        (*iter)->stateChange(model,t);
        // Cleanup
        model->gc_output(model->output_bag);
        model->output_bag.clear();
        output_up_to_date = false;
    }

    template <typename X> void Simulator<X>::computeOutput() {
        // Return if the output function has been evaluated
        if (output_up_to_date) return;
        // Compute the output
        output_up_to_date = true;
        model->output_func(model->output_bag);
        // Tell listeners about the output
        for (typename Bag<X>::iterator yiter = model->output_bag.begin(); \
            yiter != model->output_bag.end(); yiter++) {
            for (typename ListenerList::iterator iter = listeners.begin();\
             iter != listeners.end(); iter++) {
                 (*iter)->outputEvent(model,*yiter,t);
            }
        }
    }
}
#endif /* _dtss_simulator_h_*/