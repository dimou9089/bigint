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

lib.sub.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_uint8),ctypes.POINTER(ctypes.c_uint8)]
lib.sub.restype = None

size=64
array=(ctypes.c_uint8 * size)


nb_tests=1_000_000
for i in range(nb_tests):
    if i%1000==0:
        print(f"\r{i}/{nb_tests}",end="")
    a=[]
    b=[]
    c=[0]*size

    a_int=gen_int(a)
    b_int=gen_int(b)
    # Precondition for substraction
    if a_int<b_int:
        a_int,b_int=b_int,a_int
        a,b=swap(a,b)


    a_param=array(*a)
    b_param=array(*b)
    c_param=array(*c)

# Appel
    lib.sub(a_param,b_param,c_param)
    c_int=concat(c_param)

    s=a_int-b_int

    if c_int!=s:
        expected=hex(s).zfill(128)
        res=hex(c_int).zfill(128)
        print("*****************************")
        print("a10 =",a_int)
        print("b10 =",b_int)
        print("returned =",res)
        print("expected =",expected)
        print("test result :", c_int==s)
        break
print(f"\r{nb_tests}/{nb_tests}")
