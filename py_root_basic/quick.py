#!/Library/Frameworks/Python.framework/Versions/3.7/bin/python3

# make this a pyROOT script
import ROOT
import numpy as np
from array import array

# lets get the header information we care about
ROOT.gInterpreter.ProcessLine('.L data_headers.hh')

# can even define your own methods for whatever struct you want!
ROOT.gROOT.ProcessLine(
    "struct test_struct {\
    Int_t a;\
    Int_t b;\
    std::string bla;\
    test_struct() = default;\
    test_struct(Int_t a1, Int_t b1) : a(a1), b(b1) {};\
};")

from ROOT import extype

# lets make sure we can access these values
bla = extype(2, 3)  # non-default imported constructor

# get our variables, with member types defined in the header
print("value of a is: %s" % bla.get_a())  # custom methods
print("value of b is: %s" % bla.get_b())

# let's try writing to a root tree
filename = "file-name.root"
treename = "tt"
tf = ROOT.TFile(filename, "RECREATE")
tree = ROOT.TTree(treename, "descript")

# add things to the tree
maxn = 10

# values
n = array('i', [0])
d = array('f', maxn*[0.])
a = np.empty(1, dtype=np.float32)
struc1 = ROOT.test_struct(2, 3)
ex1 = ROOT.extype(3, 4)

# making STL values
vec1 = ROOT.std.vector("int")(3)  # start with 3 slots
vec1[0] = 1  # assign values like a tuple
vec1[1] = 2
vec1[3] = 3

# vector of vectors of ints..
vv1 = ROOT.std.vector(type(vec1))(3)  # start with 3 slots
vv2 = ROOT.std.vector(type(ROOT.std.vector("int")()))()  # or straight..
vv2.push_back(vec1)  # add to vectors with normal methods..

# can iterate over vector<vector<int>> like you would expect:
# for vec in vv1:
#     for each vector in the vector<vector<int>> logic
#     print(vec)
#     for i in vec:
#         for each int in the vector<int> logic
#         print(i)

# branches
tree.Branch('mynum', n, 'mynum/I')
tree.Branch('myval', d, 'myval/F')
tree.Branch('mynpval', a, 'a/F')
tree.Branch("test_struct", struc1, "a/I:b/I:bla/C")
tree.Branch("extype", ex1, "a/I:b/I")
tree.Branch("vec1", vec1)
tree.Branch("vecv2", vv2)
tree.Fill()

for i in range(25):
    n[0] = min(i, maxn)
    a[0] = i*i

    # structs have everything public
    struc1.a = i
    struc1.b = i*i
    if i == 0:
        struc1.bla = ""
    else:
        struc1.bla = "val is: " + str(i)
    # can assign to PUBLIC member values
    ex1.a = i
    ex1.b = i*i
    # changing values MUST ONLY be done when
    # using member fuctions..
    ex1.mult(3)
    for j in range(n[0]):
        d[j] = i * 0.1 + j
    tree.Fill()

# save the data
tree.Print()
tree.Write()
tf.Close()  # close the file


# TFile reading
f = ROOT.TFile.Open(filename)
print('opening root file..')
tt = f.Get(treename)
for event in tt:
    # basic values
    print("mynum is: %s " % event.mynum)
    print("myval is: %s" % event.myval)
    print("mynpval is: %s" % event.mynpval)

    # getting stl containers:
    print("vec1 is: %s" % event.vec1)
    print("vv2 is: %s" % event.vecv2)

    # getting special leafs off of the structs requires getattr value..
    print("extype a is: ", getattr(tt, "extype/a"))
    print("extype b is: ", getattr(tt, "extype/b"))
    print("struct a is: ", getattr(tt, "test_struct/a"))
    print("struct b is: ", getattr(tt, "test_struct/b"))
    print("struct bla is: ", getattr(tt, "test_struct/bla"))
