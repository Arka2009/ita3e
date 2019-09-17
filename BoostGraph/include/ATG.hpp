#ifndef DEF_ATG_H
#define DEF_ATG_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <boost/graph/adjacency_list.hpp>

void testATG(int N, double p);
void randDAGGen();
std::ostream& operator<<(std::ostream &os, const NodeType  &et);

class AppTaskGraph {
    private:
        DAGType gSS;
        std::vector<DAGVertexType> vdMap;   /* Node identifier set, vdMap[N-1] is a sink */
        std::map<DAGVertexType,std::vector<DAGVertexType>> predVdMap;  /* Map of predecessors */
        std::map<DAGVertexType,std::vector<DAGVertexType>> succVdMap;  /* Map of successors */
        bool initialized;
        bool scheduled;
        double t;         /* Execution time spent */
        int util;         /* Number of processors used */
        int finishCounter;
        double wC;        /* Worst case makespan */
        double deadline;
        void computeNbdMap();
        int execute(int M_X, double delta);
        int KlausHuangLP(int M_X, double rho, int mu);
        double KlausHuangListM(int M_X, double delta);
        void computeHeight(bool schedule);
        void reset();     /* Reset the schedules and status */
    public:
        AppTaskGraph(int N, double p);
        AppTaskGraph(std::string dotFile);                /* Read a dot file */
        AppTaskGraph();
        void writeDot(int iter);
        std::vector<DAGVertexType> getPreds(int jid) { return this->predVdMap[this->vdMap[jid]]; };
        std::vector<DAGVertexType> getPreds(DAGVertexType vptr) { return this->predVdMap[vptr]; };
        std::vector<DAGVertexType> getSuccs(int jid) { return this->succVdMap[this->vdMap[jid]]; };
        std::vector<DAGVertexType> getSuccs(DAGVertexType vptr) { return this->succVdMap[vptr]; };
        NodeType getNode(int jid) { return this->gSS[this->vdMap[jid]]; };
        NodeType getNode(DAGVertexType vptr) { return this->gSS[vptr]; };
        double tau_j(int jid, int l);
        int getSize() { return this->vdMap.size(); };
        double KlausHuangMethodSched(int M_X);
        void KHMBinSearch(int K); /* Minimum peak power scheduling */
        void genStats();
};
#endif