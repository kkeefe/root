#!/usr/bin/python

# the thing we need for pyRoot to work..
import ROOT

# lets try to get our header..
ROOT.gROOT.ProcessLine('#import "data_headers.hh"')

# then lets try to make that object
