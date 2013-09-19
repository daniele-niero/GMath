# /* Copyright (c) 2010-13, Daniele Niero
# All rights reserved.

# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this 
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice, 
#    this list of conditions and the following disclaimer in the documentation 
#    and/or other materials provided with the distribution.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */


import epsilon
import types
import math
import copy

__all__ = ['Vector3']

class Vector3(object):
    '''
    Three-dimensional vector.

    This class can be used to represent points, vectors, normals
    or even colors. The usual vector operations are available.
    '''
    def __init__(self, value=[0, 0, 0]):
        '''
        initialize a new Vector3 passing:
            - any iterable with 3 numbers
            - any object with .x .y .z properties
        '''
        self.setValues(value)

    def __str__(self):
        fmt="%5.4f"
        x, y, z = self.__data
        return '('+fmt%x+', '+fmt%y+', '+fmt%z+')'

    def __repr__(self):
        repr = object.__repr__(self)
        return 'gmath.Vector3(%s) <object at %s' %(`self.__data`[1:-1], repr.split(' ')[-1])

    def copy(self):
        '''
        Return a copy of this vector
        '''
        return Vector3(self)

    def getValues(self):
        return tuple(self.__data)

    def setValues(self, value):
        if isinstance(value, (list, tuple)):
            self.__data = []
            self.__data.extend(value)

            if len(self.__data) == 2:
                self.__data.append(0.0)
        else:
            self.__data = [value.x, value.y, value.z]

    def getX(self):
        return self.__data[0]

    def setX(self, val):
        self.__data[0] = val

    def getY(self):
        return self.__data[1]

    def setY(self, val):
        self.__data[1] = val

    def getZ(self):
        return self.__data[2]

    def setZ(self, val):
        self.__data[2] = val

    x = property(getX, setX)
    y = property(getY, setY)
    z = property(getZ, setZ)

    def add(self, other):
        '''
        Add "self" to "other" and return the result as Vector3
        '''
        otherValues = other.getValues()
        return Vector3([self.__data[0]+otherValues[0],
                        self.__data[1]+otherValues[1],
                        self.__data[2]+otherValues[2]])

    def addInPlace(self, other):
        '''
        Add "self" to "other" and store the result on "self"
        '''
        otherValues = other.getValues()
        self.__data[0] += otherValues[0]
        self.__data[1] += otherValues[1]
        self.__data[2] += otherValues[2]

    def sub(self, other):
        '''
        Subtract "other" from "self" and return the result as a Vector3
        '''
        otherValues = other.getValues()
        return Vector3([self.__data[0]-otherValues[0],
                        self.__data[1]-otherValues[1],
                        self.__data[2]-otherValues[2]])


    def subInPlace(self, other):
        '''
        Subtract "other" from "self" and store the result on "self"
        '''
        otherValues = other.getValues()
        self.__data[0] -= otherValues[0]
        self.__data[1] -= otherValues[1]
        self.__data[2] -= otherValues[2]

    def multiplyByScalar(self, scalar):
        '''
        Multiply "self" by a number and return the result as Vector3
        '''
        return Vector3([self.__data[0]*scalar,
                        self.__data[1]*scalar,
                        self.__data[2]*scalar])

    def multiplyByScalarInPlace(self, scalar):
        '''
        Multiply "self" by a number and store the result on "self"
        '''
        self.__data[0] *= scalar
        self.__data[1] *= scalar
        self.__data[2] *= scalar

    def divide(self, scalar):
        '''
        Divide "self" by a number and return the result as Vector3
        '''
        return Vector3([self.__data[0]/scalar,
                        self.__data[1]/scalar,
                        self.__data[2]/scalar])

    def multiplyByMatrix4(self, matrix4):
        oValues = self.getValues()
        iValues = matrix4.getValues()
        w = iValues[3]*oValues[0] + iValues[7]*oValues[1] + iValues[11]*oValues[2] + iValues[15]
        rvec = Vector3([iValues[0]*oValues[0] + iValues[1]*oValues[1] + iValues[2]*oValues[2] + iValues[12],
                        iValues[4]*oValues[0] + iValues[5]*oValues[1] + iValues[6]*oValues[2] + iValues[13],
                        iValues[8]*oValues[0] + iValues[9]*oValues[1] + iValues[10]*oValues[2]+ iValues[14]])
        rvec.divideInPlace(w)
        return rvec

    def multiplyByMatrix4InPlace(self, matrix4):
        vec = self.multiplyByMatrix4(matrix4)
        self.setValues(vec)

    def divideInPlace(self, scalar):
        '''
        Divide "self" by a number and store the result on "self"
        '''
        self.__data[0] /= scalar
        self.__data[1] /= scalar
        self.__data[2] /= scalar

    def negate(self):
        '''
        Negation

        a = Vector3([3.0, 2.5, -1.8])
        b = a.negate()
        print b
        >>> (-3.0, -2.5, 1.8)
        '''
        return Vector3([-self.__data[0], -self.__data[1], -self.__data[2]])

    def negateInPlace(self):
        '''
        Negation

        a = Vector3(3.0, 2.5, -1.8)
        a.negateInPlace()
        print a
        >>> (-3.0, -2.5, 1.8)
        '''
        self.__data[0] *= -1.0
        self.__data[1] *= -1.0
        self.__data[2] *= -1.0

    def isEqualTo(self, other):
        '''
        a=Vector3(1.0, 0.5, -1.8)
        b=Vector3(-0.3, 0.75, 0.5)
        c=Vector3(-0.3, 0.75, 0.5)
        print a.isEqualTo(b)
        print b.isEqualTo(c)

        >>> False
        >>> True
        '''
        eps = epsilon.getEpsilon()
        otherValue = other.getValues()
        if (abs(self.__data[0] - otherValue[0]) <= eps and
            abs(self.__data[1] - otherValue[1]) <= eps and
            abs(self.__data[2] - otherValue[2]) <= eps):
            return True
        else:
            return False

    def cross(self, other):
        '''
        Cross product between this Vector3 and another Vector3
        '''
        oValues = other.getValues()
        return Vector3([self.__data[1]*oValues[2]-self.__data[2]*oValues[1],
                        self.__data[2]*oValues[0]-self.__data[0]*oValues[2],
                        self.__data[0]*oValues[1]-self.__data[1]*oValues[0]])

    def dot(self, other):
        '''
        return the dot product of this Vector3 by another Vector3
        '''
        otherValues = other.getValues()
        return (self.__data[0]*otherValues[0] +
                self.__data[1]*otherValues[1] +
                self.__data[2]*otherValues[2])

    def length(self):
        '''
        Return the length of this Vector3.
        '''
        dot = (self.__data[0]*self.__data[0] +
               self.__data[1]*self.__data[1] +
               self.__data[2]*self.__data[2])
        return math.sqrt(dot)

    def distance(self, other):
        distVec = other.sub(self)
        return distVec.length()

    def normalize(self):
        '''
        Return the normalized copy of self.
        '''
        dot = (self.__data[0]*self.__data[0] +
               self.__data[1]*self.__data[1] +
               self.__data[2]*self.__data[2])

        if dot < epsilon.getEpsilon():
            nlen = 1.0
        else:
            nlen = 1.0/math.sqrt(dot)
        return Vector3([self.__data[0]*nlen,
                        self.__data[1]*nlen,
                        self.__data[2]*nlen])

    def normalizeInPlace(self):
        '''
        Normalize self.
        '''
        dot = (self.__data[0]*self.__data[0] +
               self.__data[1]*self.__data[1] +
               self.__data[2]*self.__data[2])

        if dot < epsilon.getEpsilon():
            nlen = 1.0
        else:
            nlen = 1.0/math.sqrt(dot)
        self.__data[0]*=nlen
        self.__data[1]*=nlen
        self.__data[2]*=nlen

    def angle(self, other):
        '''
        Return angle (in radians) between self and other.
        The function internally copies the vectors and normalized those copies
        '''
        selfNorm = self.normalize()
        otherNorm = other.normalize()
        return math.acos((selfNorm.dot(otherNorm)) / (selfNorm.length()*otherNorm.length()))


    def reflect(self, normal):
        '''
        Return the reflection vector.
        Normal is the Vector3 which represent the surface normal. It doesn't have to be normalized,
        This function will take care of that aspect
        '''
        N = normal.normalize()
        return self.sub( N.multiplyByScalar(2.0*(self.dot(N))) )

    def reflectInPlace(self, normal):
        '''
        Reflect this Vector3.
        Normal is the Vector3 which represent the surface normal. It doesn't have to be normalized,
        This function will take care of that aspect
        '''
        N = normal.normalize()
        return self.subInPlace( N.multiplyByScalar(2.0*(self.dot(N))) )

    def refract(self, normal, eta):
        '''
        Return the transmitted vector.
        Normal is the Vector3 which represent the surface normal. It doesn't have to be normalized,
        This function will take care of that aspect
        eta is the relative index of refraction. If the returned
        vector is zero then there is no transmitted light because
        of total internal reflection.
        '''
        N = normal.normalize()
        dot = self.dot(N)
        k = 1.0 - eta*eta*(1.0 - dot*dot)
        if k<0:
            return Vector3([0.0, 0.0, 0.0])
        else:
            return self.multiplyByScalar(eta).subInPlace( N.multiplyByScalar(eta*dot + math.sqrt(k)))

    def refractInPlace(self, normal, eta):
        '''
        Transmit This Vector3.
        Normal is the Vector3 which represent the surface normal. It doesn't have to be normalized,
        This function will take care of that aspect
        eta is the relative index of refraction. If the returned
        vector is zero then there is no transmitted light because
        of total internal reflection.
        '''
        N = normal.normalize()
        dot = self.dot(N)
        k = 1.0 - eta*eta*(1.0 - dot*dot)
        if k<0:
            return Vector3([0.0, 0.0, 0.0])
        else:
            return self.multiplyByScalarInPlace(eta).subInPlace( N.multiplyByScalar(eta*dot + math.sqrt(k)))

    def min(self):
        '''
        Return the minimum value of the components.
        '''
        return min(self.__data)

    def max(self):
        '''
        Return the maximum value of the components.
        '''
        return max(self.__data)

    def minIndex(self):
        '''
        Return the index of the component with the minimum value.
        '''
        if self.__data[0]<=self.__data[1] and self.__data[0]<=self.__data[2]:
            return 0
        elif self.__data[1]<=self.__data[2]:
            return 1
        else:
            return 2

    def maxIndex(self):
        '''
        Return the index of the component with the maximum value.
        '''
        if self.__data[0]>=self.__data[1] and self.__data[0]>=self.__data[2]:
            return 0
        elif self.__data[1]>=self.__data[2]:
            return 1
        else:
            return 2

    def minAbs(self):
        '''
        Return the minimum absolute value of the components.
        '''
        return min(abs(self.__data[0]), abs(self.__data[1]), abs(self.__data[2]))

    def maxAbs(self):
        '''
        Return the maximum absolute value of the components.
        '''
        return max(abs(self.__data[0]), abs(self.__data[1]), abs(self.__data[2]))

    def minAbsIndex(self):
        '''
        Return the index of the component with the minimum absolute value.
        '''
        ax = abs(self.__data[0])
        ay = abs(self.__data[1])
        az = abs(self.__data[2])

        if ax<=ay and ax<=az:
            return 0
        elif ay<=az:
            return 1
        else:
            return 2

    def maxAbsIndex(self):
        '''Return the index of the component with the maximum absolute value.
        '''
        ax = abs(self.__data[0])
        ay = abs(self.__data[1])
        az = abs(self.__data[2])

        if ax>=ay and ax>=az:
            return 0
        elif ay>=az:
            return 1
        else:
            return 2

    def toList(self):
        return copy.copy(self.__data)

    def toMayaMVector(self):
        vec = OpenMaya.MVector()
        vec.x = self.__data[0]
        vec.y = self.__data[1]
        vec.z = self.__data[2]
        return vec

    @staticmethod
    def positiveVectorX():
        return Vector3([1, 0, 0])

    @staticmethod
    def positiveVectorY():
        return Vector3([0, 1, 0])

    @staticmethod
    def positiveVectorZ():
        return Vector3([0, 0, 1])

    @staticmethod
    def negativeVectorX():
        return Vector3([-1, 0, 0])

    @staticmethod
    def negativeVectorY():
        return Vector3([0, -1, 0])

    @staticmethod
    def negativeVectorZ():
        return Vector3([0, 0, -1])

