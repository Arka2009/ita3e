#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <cmath>
#include <string>
#include <chrono>
#include <exception>
#include <queue>
#include <stack>
#include <bitset>
#include <random>
#include <set>
#include <boost/math/distributions/normal.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <sys/time.h>
#include "DataTypes.hpp"
#include "ATG.hpp"

std::ostream& operator<<(std::ostream &os, const NodeType  &et) {
  std::string state; 
  switch(et.status) {
      case NotReady : state = "NotReady"; break;
      case Ready    : state = "Ready"; break;
      case Finished : state = "Finished"; break;
      case Active   : state = "Active"; break;
      default  : state = "None"; break;
  }  
  os << "Task{id:"<<et.id<<",start:" << et.start_time << ",C:" <<  et.C << ",stop:"<<et.stop_time<<",alloc:"<<et.alloc<<",status:"<<state<<"}";
  return os;
}

/* Execution time characteristics of jth MT-task */
double AppTaskGraph::tau_j(int jid, int l) {
  NodeType *nd = &(this->gSS[this->vdMap[jid]]);
  double dj    = nd->dj;
  double tau1  = nd->tau1;
  double ret   = (tau1)*(pow(l,-dj));
  return ret;
}

/* Generate a random task graph */
AppTaskGraph::AppTaskGraph(int N, double p) : vdMap(N) {
    if (p >= 1 && p < 0) {
        throw std::invalid_argument("Wrong value of parameter p");
    }
    // initExecTimeChar(int N)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis2(0.01, 0.99);
    std::uniform_real_distribution<> dis1(80,400);
    std::bernoulli_distribution d(p);

    int i, j, cnt = 0;
    
    this->wC = 0.0;
    /* Create the nodes */
    /*
     * -1 reflects unintialized values
     */
    for (i = 0; i < N; i++) {
        NodeType vi2       = {.status = NotReady, \
                              .estart = -1, \
                              .dj = dis2(gen), .tau1 = dis1(gen), .id = i, \
                              .alloc = -1, .start_time = -1, .stop_time = -1, .C = -1};
        this->vdMap[i]     = add_vertex(vi2,this->gSS);

        this->wC += this->tau_j(vi2.id,1);
    }
    this->deadline = 0.4*(this->wC);

    /* Connect the nodes */
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
            if (d(gen)) {
                EdgeType edg = {.edgeNum = cnt++};
                add_edge(this->vdMap[i],this->vdMap[j],edg,this->gSS);
            }
        }
    }

    /* Initialize the ready set and schedule set to null */
    this->t = 0;
    this->computeNbdMap();
    this->initialized = true;
}

AppTaskGraph::AppTaskGraph() : vdMap(6) {
    /* Create a DAG as shown in buggy.dot */
    int N = 6;
    int i;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis2(0.01, 0.99);
    std::uniform_real_distribution<> dis1(80,400);
    // std::bernoulli_distribution d(p);

    for (i = 0; i < N; i++) {
        NodeType vi2       = {.status = NotReady, \
                              .estart = -1, \
                              .dj = dis2(gen), .tau1 = dis1(gen), .id = i, \
                              .alloc = -1, .start_time = -1, .stop_time = -1, .C = -1};
        this->vdMap[i]     = add_vertex(vi2,this->gSS);
    }

    EdgeType edg = {.edgeNum = 8};
    add_edge(this->vdMap[0],this->vdMap[2],edg,this->gSS);
    add_edge(this->vdMap[0],this->vdMap[4],edg,this->gSS);
    add_edge(this->vdMap[0],this->vdMap[5],edg,this->gSS);
    add_edge(this->vdMap[1],this->vdMap[2],edg,this->gSS);
    add_edge(this->vdMap[1],this->vdMap[4],edg,this->gSS);
    add_edge(this->vdMap[1],this->vdMap[5],edg,this->gSS);
    add_edge(this->vdMap[2],this->vdMap[3],edg,this->gSS);
    add_edge(this->vdMap[2],this->vdMap[5],edg,this->gSS);
    add_edge(this->vdMap[3],this->vdMap[5],edg,this->gSS);
    add_edge(this->vdMap[4],this->vdMap[5],edg,this->gSS);

}

void AppTaskGraph::writeDot(int iter) {
    std::cout << "\n-- graphviz output START --" << std::endl;
    std::ofstream dotf;
    std::string dotFilename = "demo"+std::to_string(iter)+".dot";
    dotf.open(dotFilename,std::ios::out | std::ios::trunc);
    write_graphviz(dotf,this->gSS,DAGVertexPW(this->gSS),DAGEdgePW(this->gSS));
    dotf.close();
    std::cout << "\n-- graphviz output END --" << std::endl;
}

/* Compute the longest path to each node in DAG from source node */
void AppTaskGraph::computeHeight(bool schedule) {
    DAGInEdgeIterator  eiIS, eiIE;
    int N = this->vdMap.size();
    for (int i = 0; i < N; i++) {
        NodeType *nd = &(this->gSS[this->vdMap[i]]);
        nd->estart   = 0;

        int max = 0;
        for (boost::tie(eiIS,eiIE) = boost::in_edges(this->vdMap[i],this->gSS); eiIS != eiIE; eiIS++) {
            auto ndPrevId    = boost::source(*eiIS, this->gSS);
            NodeType *ndPrev = &(this->gSS[ndPrevId]);
            if (max < (ndPrev->estart + ndPrev->C))
                max = ndPrev->estart + ndPrev->C;
        }
        nd->estart = max;

        if (schedule) {
            nd->start_time = nd->estart;
            nd->stop_time  = nd->start_time + nd->C;
        }
    }
}

void AppTaskGraph::reset() {
    for (auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
        NodeType *nd = &(this->gSS[*it]);

        nd->status = NotReady;
        nd->estart = -1;
        nd->start_time = -1;
        nd->stop_time = -1;
        nd->alloc  = -1;
    }
}

void AppTaskGraph::computeNbdMap() {
    int N = this->vdMap.size();
    DAGInEdgeIterator  eiIS, eiIE;
    DAGOutEdgeIterator  eiOS, eiOE;

    for (int i = 0; i < N; i++) {
        /* Insert predecessors */
        std::vector<DAGVertexType> preds;
        std::vector<DAGVertexType> succs;

        for (boost::tie(eiIS,eiIE) = boost::in_edges(this->vdMap[i],this->gSS); eiIS != eiIE; eiIS++) {
            auto ndPrevId    = boost::source(*eiIS, this->gSS);
            preds.push_back(ndPrevId);
        }
    
        /* Insert successors */    
        for (boost::tie(eiOS,eiOE) = boost::out_edges(this->vdMap[i],this->gSS); eiOS != eiOE; eiOS++) {
            auto ndSuccId    = boost::target(*eiOS, this->gSS);
            succs.push_back(ndSuccId);
        }

        /* */
        this->predVdMap.insert({this->vdMap[i],preds});
        this->succVdMap.insert({this->vdMap[i],succs});
    }
}

/* Construct an ATG from a dot file */
AppTaskGraph::AppTaskGraph(std::string dotFile) {
    boost::dynamic_properties dp;
    std::ifstream dotF(dotFile);
    
    dp.property("dj", boost::get(&NodeType::dj,this->gSS));
    dp.property("tau1", boost::get(&NodeType::tau1,this->gSS));
    dp.property("node_id", boost::get(&NodeType::id,this->gSS));

    read_graphviz(dotF,this->gSS,dp);
}