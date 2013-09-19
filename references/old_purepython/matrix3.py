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


from vector3 import Vector3
import constants
from .utils import mathDomainClamp
import epsilon
import types
import math
import copy

__all__ = ['Matrix3']

class Matrix3(object):
    '''
    Matrix class (3x3).
    [Xx, Xy, Xz]
    [Yx, Yy, Yz]
    [Zx, Zy, Zz]

    This class represents a 3x3 matrix that can be used to store
    rotations transformations.
    '''
    def __init__(self, value=[1, 0, 0,
                                0, 1, 0,
                                0, 0, 1]):
        '''
        Initialize a Matrix3 passing:
            - any iterable with 9 numbers
            - another Matrix3
        '''
        self.setValues(value)

    def __repr__(self):
        fmt="%8.4f"
        m11,m12,m13,m21,m22,m23,m31,m32,m33 = self.__data
        return '['+fmt%m11+', '+fmt%m12+', '+fmt%m13+']\n'+ \
               '['+fmt%m21+', '+fmt%m22+', '+fmt%m23+']\n'+ \
               '['+fmt%m31+', '+fmt%m32+', '+fmt%m33+']'

    def __str__(self):
        repr = object.__repr__(self)
        return 'gmath.Matrix3(%s) <object at %s' %(`self.__data`[1:-1], repr.split(' ')[-1])

    def getValues(self):
        return tuple(self.__data)

    def setValues(self, value):
        '''
        Re initialize a Matrix3 passing:
            - any iterable with 9 numbers
            - another Matrix3
        '''
        if isinstance(value, Matrix3):
            self.__data = []
            self.__data.extend( value.getValues() )
        elif hasattr(value, '__iter__'):
            self.__data = [0.0]*9
            for i in range(0, 9):
                self.__data[i] = value[i]

    def setSingleValue(self, row, column, value):
        self.__data[row*3+column] = float(value)

    def getSingleValue(self, row, column):
        if row<0 or row>2 or column<0 or column>2:
            raise IndexError, "index out of range"
        return self.__data[row*3+column]

    def getRow(self, index):
        '''
        Return a row as Vector3.
        '''
        if type(index)==int:
            if   index==0: return Vector3([self.__data[0], self.__data[1], self.__data[2]])
            elif index==1: return Vector3([self.__data[3], self.__data[4], self.__data[5]])
            elif index==2: return Vector3([self.__data[6], self.__data[7], self.__data[8]])
            else:
                raise IndexError,"index out of range"
        else:
            raise TypeError,"index must be an integer"

    def setRow(self, index, value):
        '''
        Set a row using a Vector3.
        '''
        vec = Vector3(value)
        value = vec.getValues()

        if   index==0: self.__data[0], self.__data[1], self.__data[2] = value[0], value[1], value[2]
        elif index==1: self.__data[3], self.__data[4], self.__data[5] = value[0], value[1], value[2]
        elif index==2: self.__data[6], self.__data[7], self.__data[8] = value[0], value[1], value[2]

    def getColumn(self, index):
        '''
        Return a column as Vector3.
        '''
        if   index==0: return Vector3([self.__data[0], self.__data[3], self.__data[6]])
        elif index==1: return Vector3([self.__data[1], self.__data[4], self.__data[7]])
        elif index==2: return Vector3([self.__data[2], self.__data[5], self.__data[8]])

    def setColumn(self, index, value):
        '''
        Set a column using a Vector3.
        '''
        vec = Vector3(value)
        value = vec.getValues()

        if   index==0: self.__data[0], self.__data[3], self.__data[6] = value[0], value[1], value[2]
        elif index==1: self.__data[1], self.__data[4], self.__data[7] = value[0], value[1], value[2]
        elif index==2: self.__data[2], self.__data[5], self.__data[8] = value[0], value[1], value[2]


    def getDiagonal(self):
        '''
        Return the diagonal as a Vector3
        '''
        return Vector3([self.__data[0], self.__data[4], self.__data[8]])

    def setDiagonal(self, value):
        '''
        Set the diagonal using a Vector3
        '''
        vec = Vector3(value)
        value = vec.getValues()
        self.__data[0], self.__data[4], self.__data[8] = value[0], value[1], value[2]

    def add(self, other):
        '''
        Add "self" to "other" and return the result as a Matrix3
        '''
        newMatrixValues = [1,0,0, 0,1,0, 0,0,1]
        otherValues = other.getValues()
        for i in range(0, 9):
            newMatrixValues[i] = self.__data[i] + otherValues[i]
        return Matrix3(newMatrixValues)

    def addInPlace(self, other):
        '''
        Add "self" to "other" and store the result on "self"
        '''
        otherValues = other.getValues()
        for i in range(0, 9):
            self.__data[i] += otherValues[i]

    def sub(self, other):
        '''
        Sub "self" to "other" and return the result as a Matrix3
        '''
        newMatrixValues = [1,0,0, 0,1,0, 0,0,1]
        otherValues = other.getValues()
        for i in range(0, 9):
            newMatrixValues[i] = self.__data[i] - otherValues[i]
        return Matrix3(newMatrixValues)

    def subInPlace(self, other):
        '''
        Subtract "other" from "self" and store the result on "self"
        '''
        otherValues = other.getValues()
        for i in range(0, 9):
            self.__data[i] -= otherValues[i]

    def multiplyByScalar(self, scalar):
        '''
        Multiply "self" by a scalar and return the result as Matrix3
        '''
        newMatrixValues = [1,0,0, 0,1,0, 0,0,1]
        for i in range(0, 9):
            newMatrixValues[i] = self.__data[i] * scalar
        return Matrix3(newMatrixValues)

    def multiplyByScalarInPlace(self, scalar):
        '''
        Multiply "self" by a scalar and store the result in "self"
        '''
        newMatrixValues = [1,0,0, 0,1,0, 0,0,1]
        for i in range(0, 9):
            self.__data[i] *= scalar

    def multiplyByVector3(self, vector):
        '''
        Multiply "self" by a Vector3 and return the result as Vector3
        '''
#        [ax, ay, az,]
#        [bx, by, bz,] * [vx, vy, vz]    here rule is column by rows
#        [cx, cy, cz ]
        oValues = vector.getValues()
        return Vector3([self.__data[0]*oValues[0] + self.__data[3]*oValues[1] + self.__data[6]*oValues[2],
                        self.__data[1]*oValues[0] + self.__data[4]*oValues[1] + self.__data[7]*oValues[2],
                        self.__data[2]*oValues[0] + self.__data[5]*oValues[1] + self.__data[8]*oValues[2]])

    def multiplyByMatrix3(self, matrix):
        '''
        Multiply "self" by a Matrix3 and return the result as Matrix3
        '''
        oValues = matrix.getValues()
        return Matrix3([self.__data[0]*oValues[0] + self.__data[3]*oValues[1] + self.__data[6]*oValues[2],
                        self.__data[1]*oValues[0] + self.__data[4]*oValues[1] + self.__data[7]*oValues[2],
                        self.__data[2]*oValues[0] + self.__data[5]*oValues[1] + self.__data[8]*oValues[2],

                        self.__data[0]*oValues[3] + self.__data[3]*oValues[4] + self.__data[6]*oValues[5],
                        self.__data[1]*oValues[3] + self.__data[4]*oValues[4] + self.__data[7]*oValues[5],
                        self.__data[2]*oValues[3] + self.__data[5]*oValues[4] + self.__data[8]*oValues[5],

                        self.__data[0]*oValues[6] + self.__data[3]*oValues[7] + self.__data[6]*oValues[8],
                        self.__data[1]*oValues[6] + self.__data[4]*oValues[7] + self.__data[7]*oValues[8],
                        self.__data[2]*oValues[6] + self.__data[5]*oValues[7] + self.__data[8]*oValues[8]])

    def multiplyByMatrix3InPlace(self, matrix):
        '''
        Multiply "self" by a Matrix3 and store the result in "self"
        '''
        oValues = matrix.getValues()
        self.__data[0] = self.__data[0]*oValues[0] + self.__data[3]*oValues[1] + self.__data[6]*oValues[2]
        self.__data[1] = self.__data[1]*oValues[0] + self.__data[4]*oValues[1] + self.__data[7]*oValues[2]
        self.__data[2] = self.__data[2]*oValues[0] + self.__data[5]*oValues[1] + self.__data[8]*oValues[2]

        self.__data[3] = self.__data[0]*oValues[3] + self.__data[3]*oValues[4] + self.__data[6]*oValues[5]
        self.__data[4] = self.__data[1]*oValues[3] + self.__data[4]*oValues[4] + self.__data[7]*oValues[5]
        self.__data[5] = self.__data[2]*oValues[3] + self.__data[5]*oValues[4] + self.__data[8]*oValues[5]

        self.__data[6] = self.__data[0]*oValues[6] + self.__data[3]*oValues[7] + self.__data[6]*oValues[8]
        self.__data[7] = self.__data[1]*oValues[6] + self.__data[4]*oValues[7] + self.__data[7]*oValues[8]
        self.__data[8] = self.__data[2]*oValues[6] + self.__data[5]*oValues[7] + self.__data[8]*oValues[8]

    def isEqualTo(self, matrix):
        otherValues = matrix.getValues()
        result = True
        for i in range(0, 9):
            if (self.__data[i] - otherValues[i] <= epsilon.getEpsilon()) == False:
                result = False
                break
        return result

    def toList(self):
        '''
        Create a list containing the matrix elements.
        '''
        return copy.copy(self.__data)

    def setToIdentity(self):
        '''
        Make "self" an identity Matrix3
        '''
        self.__data[0] = 1.0
        self.__data[1] = 0.0
        self.__data[2] = 0.0

        self.__data[3] = 0.0
        self.__data[4] = 1.0
        self.__data[5] = 0.0

        self.__data[6] = 0.0
        self.__data[7] = 0.0
        self.__data[8] = 1.0

    def transpose(self):
        '''
        Return the transposed matrix.
        '''
        return Matrix3([self.__data[0], self.__data[3], self.__data[6],
                        self.__data[1], self.__data[4], self.__data[7],
                        self.__data[2], self.__data[5], self.__data[8]])

    def transposeInPlace(self):
        '''
        Transpose "self".
        '''
        oldValues = copy.copy(self.__data)
        #self.__data[0] = oldValues[0] # it can be skipped
        self.__data[1] = oldValues[3]
        self.__data[2] = oldValues[6]
        self.__data[3] = oldValues[1]
        #self.__data[4] = oldValues[4] # it can be skipped
        self.__data[5] = oldValues[7]
        self.__data[6] = oldValues[2]
        self.__data[7] = oldValues[5]
        #self.__data[8] = oldValues[8] # it can be skipped


    def determinant(self):
        '''Return determinant.'''
        return ( self.__data[0]*self.__data[4]*self.__data[8] +
                 self.__data[1]*self.__data[5]*self.__data[6] +
                 self.__data[2]*self.__data[3]*self.__data[7] -
                 self.__data[6]*self.__data[4]*self.__data[2] -
                 self.__data[7]*self.__data[5]*self.__data[0] -
                 self.__data[8]*self.__data[3]*self.__data[1] )

    def inverse(self):
        '''Return inverse matrix.'''
        d = 1.0/self.determinant()
        matValues = [self.__data[4]*self.__data[8]-self.__data[5]*self.__data[7],
                     self.__data[7]*self.__data[2]-self.__data[1]*self.__data[8],
                     self.__data[1]*self.__data[5]-self.__data[4]*self.__data[2],

                     self.__data[5]*self.__data[6]-self.__data[3]*self.__data[8],
                     self.__data[0]*self.__data[8]-self.__data[6]*self.__data[2],
                     self.__data[3]*self.__data[2]-self.__data[0]*self.__data[5],

                     self.__data[3]*self.__data[7]-self.__data[6]*self.__data[4],
                     self.__data[6]*self.__data[1]-self.__data[0]*self.__data[7],
                     self.__data[0]*self.__data[4]-self.__data[1]*self.__data[3]]

        invertedMatrix = Matrix3(matValues)
        invertedMatrix.multiplyByScalarInPlace(d)
        return invertedMatrix

    def inverseInPlace(self):
        '''
        Invert "self".
        '''
        d = 1.0/self.determinant()
        matValues = [self.__data[4]*self.__data[8]-self.__data[5]*self.__data[7],
                     self.__data[7]*self.__data[2]-self.__data[1]*self.__data[8],
                     self.__data[1]*self.__data[5]-self.__data[4]*self.__data[2],

                     self.__data[5]*self.__data[6]-self.__data[3]*self.__data[8],
                     self.__data[0]*self.__data[8]-self.__data[6]*self.__data[2],
                     self.__data[3]*self.__data[2]-self.__data[0]*self.__data[5],

                     self.__data[3]*self.__data[7]-self.__data[6]*self.__data[4],
                     self.__data[6]*self.__data[1]-self.__data[0]*self.__data[7],
                     self.__data[0]*self.__data[4]-self.__data[1]*self.__data[3]]

        for i in range(0, 9):
            self.__data[i] = matValues[i]*d

    def scale(self, sx, sy, sz):
        return Matrix3([self.__data[0]*sx, self.__data[1]*sx, self.__data[2]*sx,
                        self.__data[3]*sy, self.__data[4]*sy, self.__data[5]*sy,
                        self.__data[6]*sz, self.__data[7]*sz, self.__data[8]*sz])

    def scaleInPlace(self, sx, sy, sz):
        self.__data[0] *= sx
        self.__data[1] *= sx
        self.__data[2] *= sx
        self.__data[3] *= sy
        self.__data[4] *= sy
        self.__data[5] *= sy
        self.__data[6] *= sz
        self.__data[7] *= sz
        self.__data[8] *= sz

    @staticmethod
    def createScaling(s):
        '''
        Return a scale transformation as Matrix3.
        '''
        sx,sy,sz = s
        return Matrix3([sx, 0.0, 0.0,
                        0.0, sy, 0.0,
                        0.0, 0.0, sz])


    @staticmethod
    def createFromAxisAngle(axis, angle):
        '''
        Return a rotation matrix from a Vector3 and an angle in radians
        '''
        axisVals = axis.getValues()
        sqr_a = axisVals[0]*axisVals[0]
        sqr_b = axisVals[1]*axisVals[1]
        sqr_c = axisVals[2]*axisVals[2]
        len2  = sqr_a+sqr_b+sqr_c

        k2    = math.cos(angle)
        k1    = (1.0-k2)/len2
        k3    = math.sin(angle)/math.sqrt(len2)
        k1ab  = k1*axisVals[0]*axisVals[1]
        k1ac  = k1*axisVals[0]*axisVals[2]
        k1bc  = k1*axisVals[1]*axisVals[2]
        k3a   = k3*axisVals[0]
        k3b   = k3*axisVals[1]
        k3c   = k3*axisVals[2]

        return Matrix3([k1*sqr_a+k2, k1ab+k3c,    k1ac-k3b,
                        k1ab-k3c,    k1*sqr_b+k2, k1bc+k3a,
                        k1ac+k3b,    k1bc-k3a,    k1*sqr_c+k2])

    def setFromAxisAngle(self, axis, angle):
        rotationMatrix = self.rotation(axis, angle)
        self.multiplyByMatrix3InPlace(rotationMatrix)

    def makeOrthogonal(self):
        '''
        Return a matrix with orthogonal base vectors.
        '''
        x = Vector3([self.__data[0], self.__data[1], self.__data[2]])
        y = Vector3([self.__data[3], self.__data[4], self.__data[5]])
        z = Vector3([self.__data[6], self.__data[7], self.__data[8]])

        xl = x.length()
        xl *= xl
        #y = y - ((x*y)/xl)*x
        y.subInPlace( x.multiplyByScalar( (x.dot(y)/xl) ) )
        #z = z - ((x*z)/xl)*x
        z.subInPlace( x.multiplyByScalar( (x.dot(z)/xl) ) )

        yl = y.length()
        yl *= yl
        #z = z - ((y*z)/yl)*y
        z.subInPlace( y.multiplyByScalar( (y.dot(z)/yl) ) )

        xvals = x.getValues()
        yvals = y.getValues()
        zvals = z.getValues()

        return Matrix3([xvals[0], xvals[1], xvals[2],
                        yvals[0], yvals[1], yvals[2],
                        zvals[0], zvals[1], zvals[2]])

    def makeOrthogonalInPlace(self):
        '''
        Set "self" with orthogonal base vectors.
        '''

        x = Vector3([self.__data[0], self.__data[1], self.__data[2]])
        y = Vector3([self.__data[3], self.__data[4], self.__data[5]])
        z = Vector3([self.__data[6], self.__data[7], self.__data[8]])

        xl = x.length()
        xl *= xl
        #y = y - ((x*y)/xl)*x
        y.subInPlace( x.multiplyByScalar( (x.dot(y)/xl) ) )
        #z = z - ((x*z)/xl)*x
        z.subInPlace( x.multiplyByScalar( (x.dot(z)/xl) ) )

        yl = y.length()
        yl *= yl
        #z = z - ((y*z)/yl)*y
        z.subInPlace( y.multiplyByScalar( (y.dot(z)/yl) ) )

        self.setRow(0, x.getValues())
        self.setRow(1, y.getValues())
        self.setRow(2, z.getValues())

    def decompose(self):
        '''
        Decomposes the matrix into a rotation and scaling part.

        Returns a tuple (rotation, scaling). The scaling part is given
        as a vec3, the rotation is still a mat3.
        '''
        dummy = self.makeOrthogonal()

        x = dummy.getRow(0)
        y = dummy.getRow(1)
        z = dummy.getRow(2)
        xl = x.length()
        yl = y.length()
        zl = z.length()
        scale = Vector3([xl, yl, zl])

        x.divideInPlace(xl)
        y.divideInPlace(yl)
        z.divideInPlace(zl)

        dummy.setRow(0, x.getValues())
        dummy.setRow(1, y.getValues())
        dummy.setRow(2, z.getValues())
        if dummy.determinant()<0.0:
            dummy.setRow(0, x.multiplyByScalar(-1).getValues())
            scale.setX(-scale.getX())

        return (dummy, scale)

    @staticmethod
    def _getThreeMatrixFromEuler(x, y, z):
        cx = math.cos(x)
        sx = math.sin(x)
        XMat = Matrix3([1.0, 0.0, 0.0,
                        0.0, cx, sx,
                        0.0, -sx, cx])

        cy = math.cos(y)
        sy = math.sin(y)
        YMat = Matrix3([cy, 0.0, -sy,
                        0.0, 1.0, 0.0,
                        sy, 0.0, cy])

        cz = math.cos(z)
        sz = math.sin(z)
        ZMat = Matrix3([cz, sz, 0.0,
                        -sz, cz, 0.0,
                        0.0, 0.0, 1.0])

        return XMat, YMat, ZMat

    @staticmethod
    def createFromEuler(x, y, z, order=constants.xyz):
        '''Create a Matrix3 from Euler angles.'''
        retMat = None
        x, y, z = map(math.radians, [x, y, z])
        if order == constants.yxz:
            XMat, YMat, ZMat = Matrix3._getThreeMatrixFromEuler(x, y, z)
            retMat = ZMat.multiplyByMatrix3(XMat.multiplyByMatrix3(YMat))
        elif order == constants.zxy:
            XMat, YMat, ZMat = Matrix3._getThreeMatrixFromEuler(x, y, z)
            retMat = YMat.multiplyByMatrix3(XMat.multiplyByMatrix3(ZMat))
        elif order == constants.zyx:
            XMat, YMat, ZMat = Matrix3._getThreeMatrixFromEuler(x, y, z)
            retMat = XMat.multiplyByMatrix3(YMat.multiplyByMatrix3(ZMat))
        elif order == constants.yzx:
            XMat, YMat, ZMat = Matrix3._getThreeMatrixFromEuler(x, y, z)
            retMat = XMat.multiplyByMatrix3(ZMat.multiplyByMatrix3(YMat))
        elif order == constants.xzy:
            XMat, YMat, ZMat = Matrix3._getThreeMatrixFromEuler(x, y, z)
            retMat = YMat.multiplyByMatrix3(ZMat.multiplyByMatrix3(XMat))
        elif order == constants.xyz:
            XMat, YMat, ZMat = Matrix3._getThreeMatrixFromEuler(x, y, z)
            retMat = ZMat.multiplyByMatrix3(YMat.multiplyByMatrix3(XMat))
        return retMat

    def setFromEuler(self, x, y, z, order=constants.xyz):
        self.setValues(Matrix3.createFromEuler(x, y, z, order))


    def toEulerYXZ(self):
        '''Return the Euler angles of a rotation matrix.'''
        eps = epsilon.getEpsilon()

        r1 = self.getRow(0)
        r2 = self.getRow(1)
        r3 = self.getRow(2)

        B = -r2.getZ()

        x = math.asin(mathDomainClamp(B))

        A = math.cos(x)

        if (A>eps):
            y = math.acos(mathDomainClamp(r3.getZ()/A))
            z = math.acos(mathDomainClamp(r2.getY()/A))
        else:
            z = 0.0
            y = math.acos(mathDomainClamp(r1.getX()))
        return Vector3((x,y,z))

    def toEulerZXY(self):
        '''Return the Euler angles of a rotation matrix.'''
        eps = epsilon.getEpsilon()

        r1 = self.getRow(0)
        r2 = self.getRow(1)
        r3 = self.getRow(2)

        B = r3.getY()

        x = math.asin(mathDomainClamp(B))

        A = math.cos(x)

        if (A>eps):
            y = math.acos(mathDomainClamp(r3.getZ()/A))
            z = math.acos(mathDomainClamp(r2.getY()/A))
        else:
            z = 0.0
            y = math.acos(mathDomainClamp(r1.getX()))

        return Vector3((x,y,z))

    def toEulerZYX(self):
        '''Return the Euler angles of a rotation matrix.'''
        eps = epsilon.getEpsilon()

        r1 = self.getRow(0)
        r2 = self.getRow(1)
        r3 = self.getRow(2)

        D = -r3.getX()

        y = math.asin(mathDomainClamp(D))

        C = math.cos(y)

        if (C>eps):
            x = math.acos(mathDomainClamp(r3.getZ()/C))
            z = math.acos(mathDomainClamp(r1.getX()/C))
        else:
            z = 0.0
            x = math.acos(mathDomainClamp(-r2.getY()))

        return Vector3((x,y,z))

    def toEulerYZX(self):
        '''Return the Euler angles of a rotation matrix.'''
        eps = epsilon.getEpsilon()

        r1 = self.getRow(0)
        r2 = self.getRow(1)
        r3 = self.getRow(2)

        F = r2.getX()

        z = math.asin(mathDomainClamp(F))

        E = math.cos(z)

        if (E>eps):
            x = math.acos(mathDomainClamp(r2.getY()/E))
            y = math.acos(mathDomainClamp(r1.getX()/E))
        else:
            y = 0.0
            x = math.asin(mathDomainClamp(r3.getY()))

        return Vector3((x,y,z))

    def toEulerXZY(self):
        '''Return the Euler angles of a rotation matrix.'''
        eps = epsilon.getEpsilon()

        r1 = self.getRow(0)
        r2 = self.getRow(1)
        r3 = self.getRow(2)

        F = -r1.getY()

        z = math.asin(mathDomainClamp(F))

        E = math.cos(z)

        if (E>eps):
            x = math.acos(mathDomainClamp(r2.getY()/E))
            y = math.acos(mathDomainClamp(r1.getX()/E))
        else:
            y = 0.0
            x = math.acos(mathDomainClamp(r3.getZ()))

        return Vector3((x,y,z))

    def toEulerXYZ(self):
        '''Return the Euler angles of a rotation matrix.'''
        eps = epsilon.getEpsilon()

        r1 = self.getRow(0)
        r2 = self.getRow(1)
        r3 = self.getRow(2)

        D = r1.getZ()

        y = math.asin(mathDomainClamp(D))

        C = math.cos(y)

        if (C>eps):
            x = math.acos(mathDomainClamp(r3.getZ()/C))
            z = math.acos(mathDomainClamp(r1.getX()/C))
        else:
            z = 0.0
            x = math.acos(mathDomainClamp(r2.getY()))

        return Vector3((x,y,z))

    @staticmethod
    def creatFromVectorToVector(_from, to):
        '''Returns a rotation matrix that rotates one vector into another.

        The generated rotation matrix will rotate the vector _from into
        the vector to. _from and to must be unit vectors!

        This method is based on the code from:

        Tomas Moller, John Hughes
        Efficiently Building a Matrix to Rotate One Vector to Another
        Journal of Graphics Tools, 4(4):1-4, 1999
        http://www.acm.org/jgt/papers/MollerHughes99/
        '''

        if isinstance(_from, Vector3) and isinstance(to, Vector3):
            EPSILON = 0.000001
            e = _from.dot(to)
            f = abs(e)

            if (f>1.0-EPSILON):    # "from" and "to"-vector almost parallel
                # vector most nearly orthogonal to "from"
                fx = abs(_from.getX())
                fy = abs(_from.getY())
                fz = abs(_from.getZ())

                if (fx<fy):
                    if (fx<fz):
                        x = Vector3([1.0, 0.0, 0.0])
                    else:
                        x = Vector3([0.0, 0.0, 1.0])
                else:
                    if (fy<fz):
                        x = Vector3([0.0, 1.0, 0.0])
                    else:
                        x = Vector3([0.0, 0.0, 1.0])

                u = x.sub(_from)
                v = x.sub(to)

                c1 = 2.0/(u.dot(u))
                c2 = 2.0/(v.dot(v))
                c3 = v.dot(u.multiplyByScalar(c1*c2))

                res = [[1, 0, 0],
                       [0, 1, 0],
                       [0, 0, 1]]
                uvals = u.getValues()
                vvals = v.getValues()
                for i in range(3):
                    for j in range(3):
                        res[j,i] =  - c1*uvals[i]*uvals[j] - c2*vvals[i]*vvals[j] + c3*vvals[i]*uvals[j]
                    res[i,i] += 1.0

                return Matrix3([res[0][0], res[0][1], res[0][2],
                                res[1][0], res[1][1], res[1][2],
                                res[2][0], res[2][1], res[2][2]])

            else:  # the most common case, unless "from"="to", or "from"=-"to"
                v = _from.cross(to)
                h = 1.0/(1.0 + e)    # optimization by Gottfried Chen
                hvx = h*v.getX()
                hvz = h*v.getZ()
                hvxy = hvx*v.getY()
                hvxz = hvx*v.getZ()
                hvyz = hvz*v.getY()

                data = [0]*9
                data[0] = e + hvx*v.getX()
                data[1] = hvxy - v.getZ()
                data[2] = hvxz + v.getY()

                data[3] = hvxy + v.getZ()
                data[4] = e + h*v.getY()*v.getY()
                data[5] = hvyz - v.getX()

                data[6] = hvxz - v.getY()
                data[7] = hvyz + v.getX()
                data[8] = e + hvz*v.getZ()

                return Matrix3(data)





















