from ctypes import *

baobab = CDLL('./Dll1.dll')

baobab.scalarProduct.argtypes = (POINTER(c_double), POINTER(c_double), c_int)
baobab.scalarProduct.restype  = c_double

n = 3
a = (c_double * n)(2.0, 5.0, 3.0)
b = (c_double * n)(3.0, 9.0, 7.0)

res = baobab.scalarProduct(a, b, n)
print("Скалярное произведение =", res)
