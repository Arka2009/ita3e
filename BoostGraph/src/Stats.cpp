#include <iostream>
#include <tuple>
#include <queue>
#include <map>
#include <cstdlib>
#include "DataTypes.hpp"
#include "ATG.hpp"

void AppTaskGraph::genStats() {
    std::priority_queue<Events> eventQ;
    if(this->scheduled) {
        for (auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
            NodeType *nd = &(this->gSS[*it]);

            Events e1 = std::make_tuple(-nd->start_time,Start,nd->alloc,nd->id);
            Events e2 = std::make_tuple(-nd->stop_time,Stop,nd->alloc,nd->id);
            eventQ.push(e1);
            eventQ.push(e2);
        }

        std::map<double,int> tsDB; // Utilization time series
        double ts = 0.0, tmp;
        EventType evtType;
        std::string evtS;
        int alloc, id, util = 0;
        while(!eventQ.empty()) {
            std::tie(tmp,evtType,alloc,id) = eventQ.top();
            ts = -tmp;
            if (evtType == Start) {
                util += alloc;
                evtS = "Start";
            }
            else {
                util -= alloc;
                evtS  = "Stop";
            }
            if (tsDB.count(ts) > 0) {
                if (evtType == Start)
                    tsDB[ts] += alloc;
                else
                    tsDB[ts] -= alloc;
            } else {
                tsDB[ts] = util;
            }
            // std::cout<<"T:"<<ts<<",Alloc:"<<alloc<<",State:"<<evtS<<",id:"<<id<<"\n";
            eventQ.pop();
        }
        std::cout<<"----------------------\n";
        int max = 0;
        for (auto it = tsDB.begin();it != tsDB.end();it++) {
            double ts;
            int util;
            std::tie(ts,util) = *it;
            max = std::max(util,max);
            // std::cout<<ts<<","<<util<<std::endl;
        }
        std::cout<<"max = "<<max<<", M = "<<M<<std::endl;
    } else {
        std::cerr<<"ATG not scheduled"<<std::endl;
        std::abort();
    }
}