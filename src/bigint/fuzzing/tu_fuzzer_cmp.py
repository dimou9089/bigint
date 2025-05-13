from random import randint
import ctypes
import os

def gen_int(l):
    s=""
    for i in range(64):
        r=randint(0,255)
        s=hex(r)[2:].zfill(2)+s
        l+=[r]
    return int(s,16)



script_path=os.path.dirname(__file__)
path=f"{script_path}/../../../build/bigint/fuzzing/libbigint_fuzzing.so"
lib = ctypes.CDLL(path)

lib.cmp.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_uint8)]
lib.cmp.restype = ctypes.c_int8

size=64
array=(ctypes.c_uint8 * size)


nb_tests=1_000_000
for i in range(nb_tests):
    if i%1000==0:
        print(f"\r{i}/{nb_tests}",end="")
    a=[]
    b=[]
    res=0

    a_int=gen_int(a)
    b_int=gen_int(b)


    a_param=array(*a)
    b_param=array(*b)
    res_param=(ctypes.c_int8)(res)

# Appel
    res_param=lib.cmp(a_param,b_param)

    s=0
    if a_int>b_int:
        s=1
    elif a_int<b_int:
        s=-1

    if res_param!=s:
        expected=s
        res=res_param
        print("*****************************")
        print("a10 =",a_int)
        print("b10 =",b_int)
        print("returned =",res)
        print("expected =",expected)
        print("test result :", res_param==s)
        break
print(f"\r{nb_tests}/{nb_tests}")

