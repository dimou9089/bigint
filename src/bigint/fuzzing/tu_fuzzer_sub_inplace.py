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

lib.sub_inplace.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_uint8),ctypes.c_uint32]
lib.sub_inplace.restype = None

size=64
array=(ctypes.c_uint8 * size)


nb_tests=1_000_000
for i in range(nb_tests):
    if i%1000==0:
        print(f"\r{i}/{nb_tests}",end="")
    a=[]
    b=[]
    shift=randint(0,63)
    shift2=randint(0,shift)

    a_int=gen_int(a)
    b_int=gen_int(b)
    # Precondition for substraction
    if a_int<b_int:
        a_int,b_int=b_int,a_int
        a,b=swap(a,b)
    b=b[shift:]+[0]*shift
    b_int=(b_int>>(8*shift))<<(8*shift2)
    s=a_int-b_int

    a_param=array(*a)
    b_param=array(*b)
    shift_param=(ctypes.c_uint32)(shift2)

# Appel
    lib.sub_inplace(a_param,b_param,shift_param)

    a_int=concat(a_param)


    if a_int!=s:
        expected=hex(s).zfill(128)
        res=hex(a_int).zfill(128)
        print("*****************************")
        print("a10 =",a_int)
        print("b10 =",b_int)
        print("returned =",res)
        print("expected =",expected)
        print("shift =",shift)
        print("shift2 =",shift2)
        print("test result :", a_int==s)
        print("test number :",i)
        break
print(f"\r{nb_tests}/{nb_tests}")
