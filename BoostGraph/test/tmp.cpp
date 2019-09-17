void computeReady(std::set<DAGVertexType> &execSet,\
                          std::set<DAGVertexType> &finishedSet,\
                          std::priority_queue<std::pair<double,DAGVertexType>> &readySet);











int AppTaskGraph::KlausHuangList(int M_X) {
  /* Applying Graham's list scheduling */
  double C = 0.0;
  double W = 0.0;
  int m    = M_X;
  //int mu = (113*m - std::sqrt(6469*m*m - 6300*m))/100;
  int mu = (m+1)/2;
  for (auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
    NodeType *nd                     = &(this->gSS[*it]);
    nd->start_time                   = 0.0;
    nd->alloc                        = std::min(mu,nd->alloc);
    nd->C                            = this->tau_j(nd->id,nd->alloc);
    std::vector<DAGVertexType> preds = this->getPreds(*it);
    for (auto jt = preds.begin(); jt != preds.end(); jt++) {
      NodeType *prevNd = &(this->gSS[*jt]);
      nd->start_time   = std::max(nd->start_time,prevNd->stop_time);
      /* What if M_X < nd->alloc */
    }
    nd->stop_time                     = nd->start_time + nd->C;

    #ifdef DEBUG
    C                                 = std::max(nd->stop_time,C);
    W                                += (nd->C)*(nd->alloc);
    #endif
  }
  #ifdef DEBUG
  std::cout<<"ATG (normalized) total work : "<<W/M_X<<"\n";
  std::cout<<"ATG makespan : "<<C<<"\n";
  #endif
  return 0;
}

// /* Set of ready to execute at t */
// NodeType* AppTaskGraph::getBestNode(double t,int util) {
//   std::cout<<"-------------------------\n";
//   std::cout<<"Ready Set("<<t<<")\n";
//   for(auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
//     NodeType *currNd = &(this->gSS[*it]);
//     /* Dont bother if you are already scheduled */
//     if (currNd->start_time >= 0) {
//       continue;
//     }
//     auto preds = this->getPreds(*it);
//     bool ready = true;
//     for (auto jt = preds.begin(); jt != preds.end(); jt++) {
//       NodeType *nd = &(this->gSS[*jt]);
//       /* All the predecesors are scheduled and finished their execution */
//       if (t >= nd->stop_time && nd->stop_time > 0) {
//         ready &= true;
//       } else {
//         ready &= false;
//       }
//     }
//     /* but I am not scheduled yet */
//     if (currNd->start_time < 0) {
//       ready &= true;
//     } else {
//       ready &= false;
//     }
//     if (ready) {
//       std::cout<<*currNd<<std::endl;
//       this->readySet.insert(*it);
//     }
//   }
//   std::cout<<"-------------------------\n\n";
// }

// /* Set of active nodes, that are currently executing at t */
// int AppTaskGraph::getCurrentUtil(double t) {
//   int m = 0;
//   for(auto it = this->vdMap.begin(); it != this->vdMap.end(); it++) {
//     NodeType *nd = &(this->gSS[*it]);
//     if (nd->start_time >= 0 && t >= nd->start_time && nd->stop_time > t) {
//       // this->activeSet.insert(*it);
//       m += nd->alloc;
//     }
//   }
//   return m;
// }