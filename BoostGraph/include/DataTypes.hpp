#ifndef DEF_DATATYPES_H
#define DEF_DATATYPES_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

#define M    32  // Maximum number of cores
#define NMax 20000 // Maximum supported taskset size
#define FIXED_FLOAT(x) std::fixed<<std::setprecision(2)<<(x)
#define DEBUG

/*
 * 1. NotReady - Predecessors not yet finished, cannot execute
 * 2. Ready    - Predecessors finished, but not enough resources
 * 3. Active   - Execution under progress
 * 4. Finished - Completed execution already
 */
enum StatusType {NotReady,Ready,Finished,Active};

struct NodeType {
    StatusType status;
    double estart;  /* Earliest possible start time that satisfies the precedence constraints */

    /* Execution type characteristics (static)
     * execution time is modelled \tau_j(m) = \tau_j(1) * m^(-d_{j}).
     * where 0 < d_{j} < 1
     */
    double dj;      /* Exponent 0 < dj < 1 */
    double tau1;
    int id; 

    /* Execution type characteristics (Dynamic)
     * mainly start and finish time in the schedule
     */
    int alloc;
    double start_time;
    double stop_time;
    double C;        /* computation requirement, uninitialized value = -1 */
};

/* Only used for dependency modelling */
struct EdgeType {
    int edgeNum;
};

/* Event types for statistics collection and display */
enum EventType {Stop=1,Start=0};

/* <time stamp, EeventType, alloc, id> */
typedef std::tuple<double,EventType,int,int> Events;

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::bidirectionalS,NodeType,EdgeType> DAGType;
typedef boost::graph_traits<DAGType>::vertex_descriptor DAGVertexType;
typedef boost::graph_traits<DAGType>::edge_descriptor DAGEdgeType;
typedef boost::graph_traits<DAGType>::out_edge_iterator DAGOutEdgeIterator;
typedef boost::graph_traits<DAGType>::in_edge_iterator DAGInEdgeIterator;
typedef boost::graph_traits<DAGType>::vertex_iterator DAGVertexIterator;
typedef boost::graph_traits<DAGType>::degree_size_type DAGDegSizeType;

class DAGVertexPW {
     public:
       DAGVertexPW(DAGType& g) : myGraph(g) {}
       template <class VertexOrEdge>
       void operator()(std::ostream& os, const VertexOrEdge& v) const {
            os << "[status=\"{";
            switch(myGraph[v].status) {
                case NotReady   : os << "NotReady,"; break;
                case Ready      : os << "Ready,"; break;
                case Finished   : os << "Finished,"; break;
                case Active     : os << "Active"; break;
            }
            os << "id:" << myGraph[v].id;
            // os << ",estart:" << FIXED_FLOAT(myGraph[v].estart);
            // os << ",alloc:" << myGraph[v].alloc;
            // os << ",start:" << FIXED_FLOAT(myGraph[v].start_time);
            // os << ",stop:" << FIXED_FLOAT(myGraph[v].stop_time);
            // os << ",C:" << FIXED_FLOAT(myGraph[v].C);
            os << ",dj:" << FIXED_FLOAT(myGraph[v].dj);
            os << ",tau1:" << FIXED_FLOAT(myGraph[v].tau1);
            os << "}\"]";
       }
    private:
        DAGType& myGraph;
};

class DAGEdgePW {
    public:
       DAGEdgePW(DAGType& g) : myGraph(g) {}
       template <class VertexOrEdge>
       void operator()(std::ostream& os, const VertexOrEdge& e) const {
       }
    private:
        DAGType& myGraph;
};

#endif