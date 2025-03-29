from pythonnet import load
import os 

load("coreclr") # 지정해주지 않으면 default 는 mono로 되어 있음
path = os.getcwd()

import clr

clr.AddReference(path + "/sandbox/DLL_Test/DllTest.dll")

from DllTest import DllTest
p = DllTest()
"""
C# dll 로드 방식 : 
from {namespace} import {class 명}

p.{class 명}() => c#에서 생성자 생성방식과 동일한듯 
ex) DllTest p = new DllTest()
"""
p.PrintHello()
result = p.Add(1, 2)
print(result)