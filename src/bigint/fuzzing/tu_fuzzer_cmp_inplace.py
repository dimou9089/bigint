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

def get_int(l):
    s=""
    for i in l:
        s=hex(i)[2:].zfill(2)+s
    return int(s,16)

def concat(l):
    res=0
    for i,v in enumerate(l):
        res=res ^ (v<<(8*i))
    return res

def swap(a,b):
    return b,a

script_path=os.path.dirname(__file__)
path=f"{script_path}/../../../build/bigint/fuzzing/libbigint_fuzzing.so"
lib = ctypes.CDLL(path)

lib.cmp_inplace.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_uint8),ctypes.c_uint32]
lib.cmp_inplace.restype = ctypes.c_int8

size=64
array=(ctypes.c_uint8 * size)


nb_tests=1_000_000
for i in range(nb_tests):
    if i%1000==0:
        print(f"\r{i}/{nb_tests}",end="")
    a=[]
    b=[]
    shift=randint(0,63)

    a_int=gen_int(a)
    b_int=gen_int(b)

    # Shift
    b=b[shift:]+[0]*shift
    b_int=(b_int>>(8*shift))<<(8*shift)


    if a_int>b_int:
        s=1
    elif a_int<b_int:
        s=-1
    else:
        s=0

    a_param=array(*a)
    b_param=array(*b)
    shift_param=(ctypes.c_uint32)(shift)

    # Appel
    res=lib.cmp_inplace(a_param,b_param,shift_param)



    if res!=s:
        expected=s
        print("*****************************")
        print("a10 =",a_int)
        print("b10 =",b_int)
        print("returned =",res)
        print("expected =",expected)
        print("test result :", a_int==s)
        print("test number :",i)
        break
print(f"\r{nb_tests}/{nb_tests}")
