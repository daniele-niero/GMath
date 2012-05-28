# A math library for 3D graphic.
# Copyright (C) 2010-2012 Daniele Niero

# Author contact: daniele . niero @ gmail . com

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


import epsilon
import types
import math
import copy

__all__ = ['Vector4']

class Vector4(object):
    '''
    Four-dimensional vector.
    This class represents a 4D vector.
    '''
    def __init__(self, value=[0, 0, 0, 0]):
        '''
        initialize a new Vector3 passing:
            - any iterable with 4 numbers
            - any object with .x .y .z .w properties
        '''
        self.setValues(value)

    def __repr__(self):
        fmt="%5.4f"
        x, y, z, w = self.__data
        return '('+fmt%x+', '+fmt%y+', '+fmt%z+', '+fmt%w+')'

    def __str__(self):
        repr = object.__repr__(self)
        return 'gmath.Vector4(%s) <object at %s' %(`self.__data`[1:-1], repr.split(' ')[-1])

    def copy(self):
        '''
        Return a copy of this vector
        '''
        return Vector4(self)

    def getValues(self):
        return tuple(self.__data)

    def setValues(self, value):
        if hasattr(value, '__iter__'):
            self.__data = []
            for o in value:
                self.__data.append(o)
        else:
            self.__data = [value.x, value.y, value.z, value.w]

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

    def getW(self):
        return self.__data[3]

    def setW(self, val):
        self.__data[3] = val

    x = property(getX, setX)
    y = property(getY, setY)
    z = property(getZ, setZ)
    w = property(getW, setW)

    def add(self, other):
        '''
        Add "self" to "other" and return the result as a Vector4
        '''
        otherValues = other.getValues()
        return Vector4([self.__data[0]+otherValues[0],
                        self.__data[1]+otherValues[1],
                        self.__data[2]+otherValues[2],
                        self.__data[3]+otherValues[3]])

    def addInPlace(self, other):
        '''
        Add "self" to "other" and store the result on "self"
        '''
        otherValues = other.getValues()
        self.__data[0] += otherValues[0]
        self.__data[1] += otherValues[1]
        self.__data[2] += otherValues[2]
        self.__data[3] += otherValues[3]

    def sub(self, other):
        '''
        Subtract "other" from "self" and return the result as a Vector4
        '''
        otherValues = other.getValues()
        return Vector4([self.__data[0]-otherValues[0],
                        self.__data[1]-otherValues[1],
                        self.__data[2]-otherValues[2],
                        self.__data[3]-otherValues[3]])

    def subInPlace(self, other):
        '''
        Subtract "other" from "self" and store the result on "self"
        '''
        otherValues = other.getValues()
        self.__data[0] -= otherValues[0]
        self.__data[1] -= otherValues[1]
        self.__data[2] -= otherValues[2]
        self.__data[3] -= otherValues[3]


    def multiplyByScalar(self, scalar):
        '''
        Multiply this "self" by a number and return the result as Vector4
        '''
        return Vector4([self.__data[0]*scalar,
                        self.__data[1]*scalar,
                        self.__data[2]*scalar,
                        self.__data[2]*scalar])

    def multiplyByScalarInPlace(self, scalar):
        '''
        Multiply "self" by a number and store the result on "self"
        '''
        self.__data[0] *= scalar
        self.__data[1] *= scalar
        self.__data[2] *= scalar
        self.__data[3] *= scalar

    def divide(self, scalar):
        '''
        Divide "self" by a number and return the result as Vector4
        '''
        return Vector4([self.__data[0]/scalar,
                        self.__data[1]/scalar,
                        self.__data[2]/scalar,
                        self.__data[4]/scalar])

    def divideInPlace(self, scalar):
        '''
        Divide "self" by a number and store the result on "self"
        '''
        self.__data[0] /= scalar
        self.__data[1] /= scalar
        self.__data[2] /= scalar
        self.__data[4] /= scalar

    def negate(self):
        '''
        Negate "self" and return the result as Vector4

        a = Vector4([3.0, 2.5, -1.8, 0.0])
        b = a.negate()
        print b
        >>> (-3.0, -2.5, 1.8, 0.0)
        '''
        return Vector4([-self.__data[0], -self.__data[1], -self.__data[2], -self.__data[3]])

    def negateInPlace(self):
        '''
        Negate "self"

        a = Vector4([3.0, 2.5, -1.8, 0.0])
        a.negateInPlace()
        print a
        >>> (-3.0, -2.5, 1.8, 0.0)
        '''
        self.__data[0] *= -1.0
        self.__data[1] *= -1.0
        self.__data[2] *= -1.0
        self.__data[3] *= -1.0

    def isEqualTo(self, other):
        '''
        a=Vector4([1.0, 0.5, -1.8, 0.0])
        b=Vector4([-0.3, 0.75, 0.5, 1.0])
        c=Vector4([-0.3, 0.75, 0.5, 1.0])
        print a.isEqualTo(b)
        print b.isEqualTo(c)

        >>> False
        >>> True
        '''
        eps = epsilon.getEpsilon()
        otherValue = other.getValues()
        if (abs(self.__data[0] - otherValue[0]) <= eps and
            abs(self.__data[1] - otherValue[1]) <= eps and
            abs(self.__data[2] - otherValue[2]) <= eps and
            abs(self.__data[3] - otherValue[3]) <= eps):
            return True

    def dot(self, other):
        '''
        return the dot product of self by other
        '''
        otherValues = other.getValues()
        return (self.__data[0]*otherValues[0] +
                self.__data[1]*otherValues[1] +
                self.__data[2]*otherValues[2] +
                self.__data[3]*otherValues[3])

    def length(self):
        '''
        Return the length of self.
        '''
        dot = (self.__data[0]*self.__data[0] +
               self.__data[1]*self.__data[1] +
               self.__data[2]*self.__data[2] +
               self.__data[3]*self.__data[3])
        return math.sqrt(dot)

    def normalize(self):
        '''
        Return the normalized copy of self.
        '''
        dot = (self.__data[0]*self.__data[0] +
               self.__data[1]*self.__data[1] +
               self.__data[2]*self.__data[2] +
               self.__data[3]*self.__data[3])

        nlen = 1.0/math.sqrt(dot)
        return Vector4([self.__data[0]*nlen,
                        self.__data[1]*nlen,
                        self.__data[2]*nlen,
                        self.__data[3]*nlen])

    def normalizeInPlace(self):
        '''
        Normalize self.
        '''
        dot = (self.__data[0]*self.__data[0] +
               self.__data[1]*self.__data[1] +
               self.__data[2]*self.__data[2] +
               self.__data[3]*self.__data[3])

        nlen = 1.0/math.sqrt(dot)
        self.__data[0]*=nlen
        self.__data[1]*=nlen
        self.__data[2]*=nlen
        self.__data[3]*=nlen

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
        if self.__data[0]<=self.__data[1] and self.__data[0]<=self.__data[2] and self.__data[0]<=self.__data[3]:
            return 0
        elif self.__data[1]<=self.__data[2] and self.__data[1]<=self.__data[3]:
            return 1
        elif self.__data[2]<=self.__data[3]:
            return 2
        else:
            return 3

    def maxIndex(self):
        '''
        Return the index of the component with the maximum value.
        '''
        if self.__data[0]>=self.__data[1] and self.__data[0]>=self.__data[2] and self.__data[0]>=self.__data[3]:
            return 0
        elif self.__data[1]>=self.__data[2] and self.__data[1]>=self.__data[3]:
            return 1
        elif self.__data[2]>=self.__data[3]:
            return 2
        else:
            return 3

    def minAbs(self):
        '''
        Return the minimum absolute value of the components.
        '''
        ax = abs(self.__data[0])
        ay = abs(self.__data[1])
        az = abs(self.__data[2])
        aw = abs(self.__data[3])
        return min(ax, ay, az, aw)

    def maxAbs(self):
        '''
        Return the maximum absolute value of the components.
        '''
        ax = abs(self.__data[0])
        ay = abs(self.__data[1])
        az = abs(self.__data[2])
        aw = abs(self.__data[3])
        return max(ax, ay, az, aw)

    def minAbsIndex(self):
        '''
        Return the index of the component with the minimum absolute value.
        '''
        ax = abs(self.__data[0])
        ay = abs(self.__data[1])
        az = abs(self.__data[2])
        aw = abs(self.__data[3])

        if ax<=ay and ax<=az and ax<=aw:
            return 0
        elif ay<=az and ay<=aw:
            return 1
        elif az<=aw:
            return 2
        else:
            return 3

    def maxAbsIndex(self):
        '''Return the index of the component with the maximum absolute value.
        '''
        ax = abs(self.__data[0])
        ay = abs(self.__data[1])
        az = abs(self.__data[2])
        aw = abs(self.__data[3])

        if ax>=ay and ax>=az and ax>=aw:
            return 0
        elif ay>=az and ay>=aw:
            return 1
        elif az>=aw:
            return 2
        else:
            return 3

    def toMayaMVector(self):
        from maya import OpenMaya
        vec = OpenMaya.MVector()
        vec.x = self.__data[0]
        vec.y = self.__data[1]
        vec.z = self.__data[2]
        return vec

    @staticmethod
    def createFromMayaMVector(mayaVec):
        from maya import OpenMaya
        retVec = Vector4([mayaVec.x, mayaVec.y, mayaVec.z, 0.0])
        return retVec

