#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul  2 11:20:05 2019

@author: amaity
"""
import numpy as np
import networkx as nx
import os
from networkx.drawing.nx_agraph import write_dot

def main():
    G = nx.gnp_random_graph(4,0.5,directed=True)
    H = nx.DiGraph([(u,v,{'weight':np.random.randint(0,5)}) for (u,v) in G.edges() if u<v])
    if nx.is_directed_acyclic_graph(H):
        write_dot(H, 'fileD.dot')
        os.system('neato -Tpdf fileD.dot >fileD.pdf')
    write_dot(G, 'fileG.dot')
    os.system('neato -Tpdf fileG.dot >fileG.pdf')

if __name__=="__main__":
    main()