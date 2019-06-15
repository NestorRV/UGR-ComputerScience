#!/usr/bin/python

suma = 0

for i in range(100):
    if i%2 != 0:
        print i,
        suma += i
print 'La suma es: %i' % suma
