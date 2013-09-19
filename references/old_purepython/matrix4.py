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


from matrix3 import Matrix3
from vector3 import Vector3
from vector4 import Vector4
import constants
import epsilon
import types
import math
import copy


__all__ = ['Matrix4']

class Matrix4(object):
    '''
    Matrix class (4x4).

    This class represents a 4x4 matrix that can be used to store
    affine transformations.
    '''
    def __init__(self, value = [1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1]):
        '''
        Initialize a Matrix3 passing:
            - any iterable with 16 numbers
            - another Matrix4
            - a Maya MMatrix
        '''
        self.setValues(value)

    def __str__(self):
        fmt="%7.4f"
        m11,m12,m13,m14,m21,m22,m23,m24,m31,m32,m33,m34,m41,m42,m43,m44 = self.__data
        return ('['+fmt%m11+', '+fmt%m12+', '+fmt%m13+', '+fmt%m14+']\n'+
                '['+fmt%m21+', '+fmt%m22+', '+fmt%m23+', '+fmt%m24+']\n'+
                '['+fmt%m31+', '+fmt%m32+', '+fmt%m33+', '+fmt%m34+']\n'+
                '['+fmt%m41+', '+fmt%m42+', '+fmt%m43+', '+fmt%m44+']')

    def copy(self):
        '''
        Return a copy of this matrix
        '''
        return Matrix4(self.__data)

    def getValues(self):
        return tuple(self.__data)

    def setValues(self, value):
        '''
        Initialize a Matrix3 passing:
            - any iterable with 16 numbers
            - another Matrix4
            - a Maya MMatrix
        '''
        if isinstance(value, Matrix4):
            self.__data = []
            self.__data.extend(value.getValues())
        else:
            self.__data = []
            self.__data.extend(value)

    def setSingleValue(self, row, column, value):
        self.__data[row*4+column] = float(value)

    def getSingleValue(self, row, column):
        return self.__data[row*4+column]

    def getRow(self, index):
        '''
        Return row as Vector4.
        '''
        if   index==0: return Vector4([self.__data[0],  self.__data[1],  self.__data[2],  self.__data[3]])
        elif index==1: return Vector4([self.__data[4],  self.__data[5],  self.__data[6],  self.__data[7]])
        elif index==2: return Vector4([self.__data[8],  self.__data[9],  self.__data[10], self.__data[11]])
        elif index==3: return Vector4([self.__data[12], self.__data[13], self.__data[14], self.__data[15]])

    def setRow(self, index, value):
        '''
        Set a row using a Vector4.
        '''
        vec = Vector4(value)
        value = vec.getValues()

        if   index==0: self.__data[0],  self.__data[1],  self.__data[2],  self.__data[3] =  value[0], value[1], value[2], value[3]
        elif index==1: self.__data[4],  self.__data[5],  self.__data[6],  self.__data[7] =  value[0], value[1], value[2], value[3]
        elif index==2: self.__data[8],  self.__data[9],  self.__data[10], self.__data[11] = value[0], value[1], value[2], value[3]
        elif index==3: self.__data[12], self.__data[13], self.__data[14], self.__data[15] = value[0], value[1], value[2], value[3]

    def getColumn(self, index):
        '''
        Return column as Vector4.
        '''
        if   index==0: return Vector4([self.__data[0], self.__data[4], self.__data[8], self.__data[12]])
        elif index==1: return Vector4([self.__data[1], self.__data[5], self.__data[9], self.__data[13]])
        elif index==2: return Vector4([self.__data[2], self.__data[6], self.__data[10], self.__data[14]])
        elif index==3: return Vector4([self.__data[3], self.__data[7], self.__data[11], self.__data[15]])

    def setColumn(self, index, value):
        '''
        Set a column using a Vector4.
        '''
        vec = Vector4(value)
        value = vec.getValues()
        if   index==0: self.__data[0], self.__data[4], self.__data[8],  self.__data[12]  = value
        elif index==1: self.__data[1], self.__data[5], self.__data[9],  self.__data[13]  = value
        elif index==2: self.__data[2], self.__data[6], self.__data[10], self.__data[14] = value
        elif index==3: self.__data[3], self.__data[7], self.__data[11], self.__data[15] = value

    def getDiag(self):
        '''
        Return the diagonal as Vector4
        '''
        return Vector4([self.__data[0], self.__data[5], self.__data[10], self.__data[15]])

    def setDiag(self, value):
        '''
        Set diagonal using a Vector4
        '''
        vec = Vector4(value)
        value = value.getValues()
        self.__data[0], self.__data[5], self.__data[10], self.__data[15]  = value

    def isEqualTo(self, other):
        eps = epsilon.getEpsilon()
        lst = filter(lambda (a,b): abs(a-b)>eps, zip(self.__data, other.getValues()))
        return len(lst) == 0

    def add(self, other):
        '''
        Add "self" to "other" and return the result as a Matrix4
        '''
        newMatrixValues = [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]
        otherValues = other.getValues()
        for i in range(0, 16):
            newMatrixValues[i] = self.__data[i] + otherValues[i]
        return Matrix4(newMatrixValues)

    def addInPlace(self, other):
        '''
        Add "self" to "other" and store the result on "self"
        '''
        otherValues = other.getValues()
        for i in range(0, 16):
            self.__data[i] += otherValues[i]

    def sub(self, other):
        '''
        Sub "self" to "other" and return the result as a Matrix4
        '''
        newMatrixValues = [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]
        otherValues = other.getValues()
        for i in range(0, 9):
            newMatrixValues[i] = self.__data[i] - otherValues[i]
        return Matrix4(newMatrixValues)

    def subInPlace(self, other):
        '''
        Subtract "other" from "self" and store the result on "self"
        '''
        otherValues = other.getValues()
        for i in range(0, 16):
            self.__data[i] -= otherValues[i]

    def multiplyByScalar(self, scalar):
        '''
        Multiply "self" by a scalar and return the result as Matrix4
        '''
        for i in range(0, 16):
            newMatrixValues[i] = self.__data[i] * scalar
        return Matrix4(newMatrixValues)

    def multiplyByScalarInPlace(self, scalar):
        '''
        Multiply "self" by a scalar and store the result in "self"
        '''
        newMatrixValues = [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]
        for i in range(0, 16):
            self.__data[i] *= scalar

    def multiplyByVector3(self, other):
        '''
        Multiply "self" by a Vector3 and return the result as Vector3
        '''
        oValues = other.getValues()
        w = self.__data[3]*oValues[0] + self.__data[7]*oValues[1] + self.__data[11]*oValues[2] + self.__data[15]
        rvec = Vector3([self.__data[0]*oValues[0] + self.__data[1]*oValues[1] + self.__data[2]*oValues[2] + self.__data[12],
                        self.__data[4]*oValues[0] + self.__data[5]*oValues[1] + self.__data[6]*oValues[2] + self.__data[13],
                        self.__data[8]*oValues[0] + self.__data[9]*oValues[1] + self.__data[10]*oValues[2]+ self.__data[14]])
        rvec.divideInPlace(w)
        return rvec

    def multiplyByVector4(self, other):
        '''
        Multiply "self" by a Vector4 and return the result as Vector4
        '''
        oValues = other.getValues()
        return Vector4([self.__data[0]*oValues[0] + self.__data[4]*oValues[1] + self.__data[8]*oValues[2],  self.__data[12]*oValues[2],
                        self.__data[1]*oValues[0] + self.__data[5]*oValues[1] + self.__data[9]*oValues[2],  self.__data[13]*oValues[2],
                        self.__data[2]*oValues[0] + self.__data[5]*oValues[1] + self.__data[10]*oValues[2], self.__data[14]*oValues[2],
                        self.__data[3]*oValues[0] + self.__data[7]*oValues[1] + self.__data[11]*oValues[2], self.__data[15]*oValues[2]])

    def multiplyByMatrix4(self, other):
        '''
        Multiply "self" by a Matrix4 and return the result as Matrix4
        '''
        oValues = other.getValues()
        return Matrix4([self.__data[0]*oValues[0]  + self.__data[1]*oValues[4]  + self.__data[2]*oValues[8]  + self.__data[3]*oValues[12],
                        self.__data[0]*oValues[1]  + self.__data[1]*oValues[5]  + self.__data[2]*oValues[9]  + self.__data[3]*oValues[13],
                        self.__data[0]*oValues[2]  + self.__data[1]*oValues[6]  + self.__data[2]*oValues[10] + self.__data[3]*oValues[14],
                        self.__data[0]*oValues[3]  + self.__data[1]*oValues[7]  + self.__data[2]*oValues[11] + self.__data[3]*oValues[15],

                        self.__data[4]*oValues[0]  + self.__data[5]*oValues[4]  + self.__data[6]*oValues[8]  + self.__data[7]*oValues[12],
                        self.__data[4]*oValues[1]  + self.__data[5]*oValues[5]  + self.__data[6]*oValues[9]  + self.__data[7]*oValues[13],
                        self.__data[4]*oValues[2]  + self.__data[5]*oValues[6]  + self.__data[6]*oValues[10] + self.__data[7]*oValues[14],
                        self.__data[4]*oValues[3]  + self.__data[5]*oValues[7]  + self.__data[6]*oValues[11] + self.__data[7]*oValues[15],

                        self.__data[8]*oValues[0]  + self.__data[9]*oValues[4]  + self.__data[10]*oValues[8]  + self.__data[11]*oValues[12],
                        self.__data[8]*oValues[1]  + self.__data[9]*oValues[5]  + self.__data[10]*oValues[9]  + self.__data[11]*oValues[13],
                        self.__data[8]*oValues[2]  + self.__data[9]*oValues[6]  + self.__data[10]*oValues[10] + self.__data[11]*oValues[14],
                        self.__data[8]*oValues[3]  + self.__data[9]*oValues[7]  + self.__data[10]*oValues[11] + self.__data[11]*oValues[15],

                        self.__data[12]*oValues[0]  + self.__data[13]*oValues[4]  + self.__data[14]*oValues[8]  + self.__data[15]*oValues[12],
                        self.__data[12]*oValues[1]  + self.__data[13]*oValues[5]  + self.__data[14]*oValues[9]  + self.__data[15]*oValues[13],
                        self.__data[12]*oValues[2]  + self.__data[13]*oValues[6]  + self.__data[14]*oValues[10] + self.__data[15]*oValues[14],
                        self.__data[12]*oValues[3]  + self.__data[13]*oValues[7]  + self.__data[14]*oValues[11] + self.__data[15]*oValues[15] ])

    def multiplyByMatrix4InPlace(self, other):
        '''
        Multiply "self" by a Matrix3 and store the result in "self"
        '''
        oValues = other.getValues()
        self.__data[0] = self.__data[0]*oValues[0]  + self.__data[1]*oValues[4]  + self.__data[2]*oValues[8]  + self.__data[3]*oValues[12]
        self.__data[0] = self.__data[0]*oValues[1]  + self.__data[1]*oValues[5]  + self.__data[2]*oValues[9]  + self.__data[3]*oValues[13]
        self.__data[0] = self.__data[0]*oValues[2]  + self.__data[1]*oValues[6]  + self.__data[2]*oValues[10] + self.__data[3]*oValues[14]
        self.__data[0] = self.__data[0]*oValues[3]  + self.__data[1]*oValues[7]  + self.__data[2]*oValues[11] + self.__data[3]*oValues[15]

        self.__data[0] = self.__data[4]*oValues[0]  + self.__data[5]*oValues[4]  + self.__data[6]*oValues[8]  + self.__data[7]*oValues[12]
        self.__data[0] = self.__data[4]*oValues[1]  + self.__data[5]*oValues[5]  + self.__data[6]*oValues[9]  + self.__data[7]*oValues[13]
        self.__data[0] = self.__data[4]*oValues[2]  + self.__data[5]*oValues[6]  + self.__data[6]*oValues[10] + self.__data[7]*oValues[14]
        self.__data[0] = self.__data[4]*oValues[3]  + self.__data[5]*oValues[7]  + self.__data[6]*oValues[11] + self.__data[7]*oValues[15]

        self.__data[0] = self.__data[8]*oValues[0]  + self.__data[9]*oValues[4]  + self.__data[10]*oValues[8]  + self.__data[11]*oValues[12]
        self.__data[0] = self.__data[8]*oValues[1]  + self.__data[9]*oValues[5]  + self.__data[10]*oValues[9]  + self.__data[11]*oValues[13]
        self.__data[0] = self.__data[8]*oValues[2]  + self.__data[9]*oValues[6]  + self.__data[10]*oValues[10] + self.__data[11]*oValues[14]
        self.__data[0] = self.__data[8]*oValues[3]  + self.__data[9]*oValues[7]  + self.__data[10]*oValues[11] + self.__data[11]*oValues[15]

        self.__data[0] = self.__data[12]*oValues[0]  + self.__data[13]*oValues[4]  + self.__data[14]*oValues[8]  + self.__data[15]*oValues[12]
        self.__data[0] = self.__data[12]*oValues[1]  + self.__data[13]*oValues[5]  + self.__data[14]*oValues[9]  + self.__data[15]*oValues[13]
        self.__data[0] = self.__data[12]*oValues[2]  + self.__data[13]*oValues[6]  + self.__data[14]*oValues[10] + self.__data[15]*oValues[14]
        self.__data[0] = self.__data[12]*oValues[3]  + self.__data[13]*oValues[7]  + self.__data[14]*oValues[11] + self.__data[15]*oValues[15]

    def toList(self):
        '''
        Return a list containing the matrix elements.
        '''
        return copy.copy(self.__data)

    def setToIdentity(self):
        self.__data[0],  self.__data[1],  self.__data[2],  self.__data[3]  = 1,0,0,0
        self.__data[4],  self.__data[5],  self.__data[6],  self.__data[7]  = 0,1,0,0
        self.__data[8],  self.__data[9],  self.__data[10], self.__data[11] = 0,0,1,0
        self.__data[12], self.__data[13], self.__data[14], self.__data[15] = 0,0,0,1

    def transpose(self):
        '''
        return the transposed copy of "self"
        '''
        return Matrix4([self.__data[0], self.__data[4], self.__data[8],  self.__data[12],
                        self.__data[1], self.__data[5], self.__data[9],  self.__data[13],
                        self.__data[2], self.__data[6], self.__data[10], self.__data[14],
                        self.__data[3], self.__data[7], self.__data[11], self.__data[15]])

    def transposeInPlace(self):
        '''
        Transpose "self".
        '''
        oldValues = copy.copy(self__data)
        #self.__data[0] = oldValues[0] # it can be skipped
        self.__data[1] = oldValues[4]
        self.__data[2] = oldValues[8]
        self.__data[3] = oldValues[12]

        self.__data[4] = oldValues[1]
        #self.__data[5] = oldValues[5] # it can be skipped
        self.__data[6] = oldValues[9]
        self.__data[7] = oldValues[13]

        self.__data[8]  = oldValues[2]
        self.__data[9]  = oldValues[6]
        #self.__data[10] = oldValues[10] # it can be skipped
        self.__data[11] = oldValues[14]

        self.__data[12] = oldValues[3]
        self.__data[13] = oldValues[7]
        self.__data[14] = oldValues[11]
        #self.__data[15] = oldValues[15] # it can be skipped


    def determinant(self):
        '''Return determinant.

        >>> M=mat4(2.0,0,0,0, 0,2.0,0,0, 0,0,2.0,0, 0,0,0,2.0)
        >>> print M.determinant()
        16.0
        '''
        m11,m12,m13,m14,m21,m22,m23,m24,m31,m32,m33,m34,m41,m42,m43,m44 = self.__data

        return m11*m22*m33*m44 \
               -m11*m22*m34*m43 \
               +m11*m23*m34*m42 \
               -m11*m23*m32*m44 \
               +m11*m24*m32*m43 \
               -m11*m24*m33*m42 \
               -m12*m23*m34*m41 \
               +m12*m23*m31*m44 \
               -m12*m24*m31*m43 \
               +m12*m24*m33*m41 \
               -m12*m21*m33*m44 \
               +m12*m21*m34*m43 \
               +m13*m24*m31*m42 \
               -m13*m24*m32*m41 \
               +m13*m21*m32*m44 \
               -m13*m21*m34*m42 \
               +m13*m22*m34*m41 \
               -m13*m22*m31*m44 \
               -m14*m21*m32*m43 \
               +m14*m21*m33*m42 \
               -m14*m22*m33*m41 \
               +m14*m22*m31*m43 \
               -m14*m23*m31*m42 \
               +m14*m23*m32*m41


    def _submat(self, i,j):
        M=Matrix3()
        for k in range(3):
            for l in range(3):
                t=(k,l)
                if k>=i:
                    t=(k+1,t[1])
                if l>=j:
                    t=(t[0],l+1)
                M.setSingleValue(k, l, self.getSingleValue(t[0], t[1]))
        return M

    def inverse(self):
        '''
        Return inverse matrix.
        '''
        Mi = Matrix4()
        d = self.determinant()
        for i in range(4):
            for j in range(4):
                sign=1-((i+j)%2)*2
                m3 = self._submat(i,j)
                Mi.setSingleValue(j, i, sign*m3.determinant()/d )
        return Mi

    def inverseInPlace(self):
        d = self.determinant()
        for i in range(4):
            for j in range(4):
                sign=1-((i+j)%2)*2
                m3 = self._submat(i,j)
                self.setSingleValue(j, i, sign*m3.determinant()/d )

    def getTranslation(self):
        '''
        Return translation component of "self" as Vector3.
        '''
        return Vector3([self.__data[12], self.__data[13], self.__data[14]])

    def setTranslation(self, vector):
        '''
        Set the translation component of this Matrix4 passing a Vector3
        '''
        vector3 = Vector3(vector)
        values = vector3.getValues()
        self.__data[12] = values[0]
        self.__data[13] = values[1]
        self.__data[14] = values[2]

    def translate(self, vector):
            self.__data[12] += vector.x * self.__data[0] + vector.y * self.__data[4] + vector.z * self.__data[8]
            self.__data[13] += vector.x * self.__data[1] + vector.y * self.__data[5] + vector.z * self.__data[9]
            self.__data[14] += vector.x * self.__data[2] + vector.y * self.__data[6] + vector.z * self.__data[10]
            #self.__data[3][3] += vector[0] * self.__data[0][3] + vector[1] * self.__data[1][3] + vector[2] * self.__data[2][3];

    def getRotationMatrix(self):
        '''
        Return the rotation component of "self" as Matrix3.
        '''
        return Matrix3([self.__data[0], self.__data[1], self.__data[2],
                        self.__data[4], self.__data[5], self.__data[6],
                        self.__data[8], self.__data[9], self.__data[10]])

    def setRotation(self, matrix):
        '''
        Set the rotation component of this Matrix4 passing a Matrix3.
        '''
        values = matrix.getValues()
        self.__data[0], self.__data[1], self.__data[2]  = values[0], values[1], values[2]
        self.__data[4], self.__data[5], self.__data[6]  = values[3], values[4], values[5]
        self.__data[8], self.__data[9], self.__data[10] = values[6], values[7], values[8]

    def scaleInPlace(self, sx, sy, sz):
        self.__data[0] *= sx
        self.__data[1] *= sx
        self.__data[2] *= sx
        self.__data[4] *= sy
        self.__data[5] *= sy
        self.__data[6] *= sy
        self.__data[8] *= sz
        self.__data[9] *= sz
        self.__data[10]*= sz

    @staticmethod
    def createScaling(s):
        '''
        Return a scale transformation as MAtrix3.
        '''
        sx,sy,sz = s
        return Matrix4([sx, 0.0, 0.0, 0.0,
                        0.0, sy, 0.0, 0.0,
                        0.0, 0.0, sz, 0.0,
                        0.0, 0.0, 0.0, 1.0])

    def lookAt(self, pos, target, up, primaryAxis=constants.axisX, secondaryAxis=constants.axisZ):
        '''
        Look from pos to target.

        The resulting transformation moves Matrix to pos and
        rotates so that the primaryAxis points to target. The secondaryAxis is
        as close as possible to the up vector.
        possible values for primary and secondary axis are:
        x=1, y=2, z=3, -x=-1, -y=-2, -z=-3
        '''
        # copy the vectors obtained. This allows us to modify in place this values, without risk to break anything
        pos = pos.copy()
        domVec = target.sub(pos).normalize()
        secVec = up.normalize()
        if primaryAxis<0:
            primaryAxis *= -1
            domVec.multiplyByScalarInPlace(-1.0)
        if secondaryAxis<0:
            secondaryAxis *= -1
            secVec.multiplyByScalarInPlace(-1.0)

        if abs(domVec.dot(secVec))-1.0 == epsilon.getEpsilon():
            raise AttributeError, 'target vector and up vector are perpendicular, impossible to create a matrix out of them.'

        xVec = None
        yVec = None
        zVec = None

        if primaryAxis == constants.axisX:
            if secondaryAxis == constants.axisY:
                xVec = domVec
                yVec = secVec
                zVec = xVec.cross(yVec)
                zVec.normalizeInPlace()
                yVec = zVec.cross(xVec)
            elif secondaryAxis == constants.axisZ:
                xVec = domVec
                zVec = secVec
                yVec = zVec.cross(xVec)
                yVec.normalizeInPlace()
                zVec = xVec.cross(yVec)
                zVec.normalizeInPlace()
        elif primaryAxis == constants.axisY:
            if secondaryAxis == constants.axisX:
                yVec = domVec
                xVec = secVec
                zVec = xVec.cross(yVec)
                zVec.normalizeInPlace()
                xVec = yVec.cross(zVec)
                xVec.normalizeInPlace()
            elif secondaryAxis == constants.axisZ:
                yVec = domVec
                zVec = secVec
                xVec = yVec.cross(zVec)
                xVec.normalizeInPlace()
                zVec = xVec.cross(yVec)
                zVec.normalizeInPlace()
        elif primaryAxis == constants.axisZ:
            if secondaryAxis == constants.axisX:
                zVec = domVec
                xVec = secVec
                yVec = zVec.cross(xVec)
                yVec.normalizeInPlace()
                xVec = yVec.cross(zVec)
                xVec.normalizeInPlace()
            elif secondaryAxis == constants.axisY:
                zVec = domVec
                yVec = secVec
                xVec = yVec.cross(zVec)
                xVec.normalizeInPlace()
                yVec = zVec.cross(xVec)
                yVec.normalizeInPlace()

        xvals = xVec.getValues()
        yvals = yVec.getValues()
        zvals = zVec.getValues()
        posvals = pos.getValues()
        self.setValues([xvals[0], xvals[1], xvals[2], 0,
                        yvals[0], yvals[1], yvals[2], 0,
                        zvals[0], zvals[1], zvals[2], 0,
                        posvals[0], posvals[1], posvals[2], 1])

    @staticmethod
    def createMatrixFromVectors(pos, target, up, primaryAxis=constants.axisX, secondaryAxis=constants.axisZ):
        '''
        Look from pos to target.

        The resulting transformation moves Matrix to pos and
        rotates so that the primaryAxis points to target. The secondaryAxis is
        as close as possible to the up vector.
        possible values for primary and secondary axis are:
        x=1, y=2, z=3, -x=-1, -y=-2, -z=-3
        '''
        lookMat = Matrix4()
        lookMat.lookAt(pos, target, up, primaryAxis, secondaryAxis)
        return lookMat

