from pythonnet import load
import os 

load("coreclr")
path = os.getcwd()


import clr

clr.AddReference(path + "/sandbox/DLL_Test/DllTest.dll")

from DllTest import DllTest

p = DllTest()
p.PrintHello()