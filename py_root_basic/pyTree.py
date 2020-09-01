#!/usr/bin/env python3

import numpy as np
import ROOT

import sys

# make an example root tree
def make_tree(filename="pyTree_output.root", rng=4):
    # where to create the root file
    root_file = ROOT.TFile(filename, "RECREATE")
    tree = ROOT.TTree("tree", "test")
    # make the values we want
    x = np.empty((1), dtype="float32")
    y = np.empty((1), dtype="float32")
    # load up the branches
    tree.Branch("x", x, "x/F")
    tree.Branch("y", y, "y/F")
    for i in range(rng):
        x[0] = i
        y[0] = i**2
        tree.Fill()
    root_file.Write()

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("using default")
        make_tree()
    else:
        make_tree(sys.argv[1])
