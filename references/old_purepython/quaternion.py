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


import constants
import epsilon
import types
import math
import copy
from matrix3 import Matrix3
from matrix4 import Matrix4
from vector3 import Vector3

__all__ = ['Quaternion']

class Quaternion(object):
    '''
    Quaternion class.
    Quaternions are an extension to complex numbers and can be used
    to store rotations. They are composed of four floats which can be
    seen as an angle and an axis of rotation.
    '''

    def __init__(self, value=[0, 0, 0, 1]):
        '''
        initialize a new Quaternion passing:
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
        return 'gmath.Quaternion(%s) <object at %s' %(`self.__data`[1:-1], repr.split(' ')[-1])

    def setValues(self, value):
        if hasattr(value, '__iter__'):
            self.__data = []
            for o in value:
                self.__data.append(o)
        else:
            self.__data = [value.x, value.y, value.z, value.w]

    def getValues(self):
        return (self.__data[0], self.__data[1], self.__data[2], self.__data[3])

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

    def isEqualTo(self, other):
        eps = epsilon.getEpsilon()
        otherValue = other.getValues()
        return (abs(self.__data[0] - otherValue[0]) <= eps and
                abs(self.__data[1] - otherValue[1]) <= eps and
                abs(self.__data[2] - otherValue[2]) <= eps and
                abs(self.__data[3] - otherValue[3]) <= eps)

    def add(self, other):
        '''
        Add "self" to "other" and return the result as a Vector4
        '''
        otherValues = other.getValues()
        return Quaternion([self.__data[0]+otherValues[0],
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
        return Quaternion([self.__data[0]-otherValues[0],
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
        return Quaternion([self.__data[0]*scalar,
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

    def multiplyByQuaternion(self, other):
        ax, ay, az, aw = self.__data[0], self.__data[1], self.__data[2], self.__data[3]
        bx, by, bz, bw = other.getValues()
        return Quaternion(( aw*bx + ax*bw + ay*bz - az*by,
                            aw*by + ay*bw + az*bx - ax*bz,
                            aw*bz + az*bw + ax*by - ay*bx,
                            aw*bw - ax*bx - ay*by - az*bz ))

    def multiplyByQuaternionInPlace(self, other):
        ax, ay, az, aw = self.__data[0], self.__data[1], self.__data[2], self.__data[3]
        bx, by, bz, bw = other.getValues()
        self.__data[0] = aw*bx + ax*bw + ay*bz - az*by
        self.__data[1] = aw*by + ay*bw + az*bx - ax*bz
        self.__data[2] = aw*bz + az*bw + ax*by - ay*bx
        self.__data[3] = aw*bw - ax*bx - ay*by - az*bz

    def dot(self, other):
        _dot = 0.0
        otherValues = other.getValues()
        for i in range(0, 4):
            _dot += self.__data[i]*otherValues[i]
        return _dot

    def normalize(self):
        q_abs = math.sqrt(self.x*self.x + self.y*self.y +
                          self.z*self.z + self.w*self.w)
        nlen = 1.0/q_abs
        return Quaternion(self.x*nlen, self.y*nlen, self.z*nlen, self.w*nlen)

    def normalizeInPlace(self):
        q_abs = math.sqrt(self.x*self.x + self.y*self.y +
                          self.z*self.z + self.w*self.w)
        nlen = 1.0/q_abs
        self.setValues((self.x*nlen, self.y*nlen, self.z*nlen, self.w*nlen))

    def inverse(self):
        dot = self.dot(self)
        x = -self.__data[0]/dot
        y = -self.__data[1]/dot
        z = -self.__data[2]/dot
        w = self.__data[3]/dot
        return Quaternion((x,y,z,w))

    def inverseInPlace(self):
        dot = self.dot(self)
        self.__data[0] = -self.__data[0]/dot
        self.__data[1] = -self.__data[1]/dot
        self.__data[2] = -self.__data[2]/dot
        self.__data[3] = self.__data[3]/dot

    def slerp(self, q, p, blend, shortest=False):
        eps = epsilon.getEpsilon()

        qValues = q.getValues()
        pValues = p.getValues()

        cos = q.dot(p)
        inv = 1.0
        if cos<0.0 and shortest==True:
            cos = -cos
            inv = -1.0

        if 1.0-cos >= eps:
            angle = math.acos(cos)
            sin = math.sin(angle)
            invSin = 1.0/sin
            coeff0 = math.sin((1.0-blend)*angle)*invSin
            coeff1 = math.sin(blend*angle)*invSin
        else:
            coeff0 = 1.0-blend
            coeff1 = blend

        self.__data[0] = coeff0*qValues[0] + coeff1*(pValues[0]*inv)
        self.__data[1] = coeff0*qValues[1] + coeff1*(pValues[1]*inv)
        self.__data[2] = coeff0*qValues[2] + coeff1*(pValues[2]*inv)
        self.__data[3] = coeff0*qValues[3] + coeff1*(pValues[3]*inv)
        self.normalizeInPlace()


    def fromAngleAxis(self, angle, axis):
        axisVec = Vector3(axis)

        if axisVec.length() > epsilon.getEpsilon():
            angle*=0.5
            w = math.cos(angle)
            x, y, z = axisVec.getValues()
            s = math.sin(angle)/math.sqrt(x*x+y*y+z*z)

            self.__data[0] = x*s
            self.__data[1] = y*s
            self.__data[2] = z*s
            self.__data[3] = w
            self.normalizeInPlace()
        else:
            self.__data[0] = 0.0
            self.__data[1] = 0.0
            self.__data[2] = 0.0
            self.__data[3] = 1.0

    @staticmethod
    def createFromAngleAxis(angle, axis):
        axisVec = Vector3(axis)
        retQuat = Quaternion()
        if axisVec.length() > epsilon.getEpsilon():
            angle*=0.5
            w = math.cos(angle)
            x, y, z = axisVec.getValues()
            s = math.sin(angle)/math.sqrt(x*x+y*y+z*z)
            x*=s
            y*=s
            z*=s
            retQuat.setValues((x, y, z, w))
            retQuat.normalizeInPlace()

        return retQuat

    def toEulerAngles(self, order=constants.xyz):
        mat = self.toMatrix3()
        angles = None
        if order == constants.xyz:
            angles = mat.toEulerXYZ()
        elif order == constants.xzy:
            angles = mat.toEulerXZY()
        elif order == constants.yxz:
            angles = mat.toEulerYXZ()
        elif order == constants.yzx:
            angles = mat.toEulerYZX()
        elif order == constants.zxy:
            angles = mat.toEulerZXY()
        elif order == constants.zyx:
            angles = mat.toEulerZYX()
        return angles

    def fromMatrix(self, inMatrix):
        matrix = Matrix3(inMatrix)
        eps = epsilon.getEpsilon()

        d0,d1,d2 = matrix.getDiagonal().getValues()
        t = d0+d1+d2+1.0
        if t>eps:
            s = 0.5/math.sqrt(t)
            self.x = (matrix.getSingleValue(2,1)-matrix.getSingleValue(1,2))*s
            self.y = (matrix.getSingleValue(0,2)-matrix.getSingleValue(2,0))*s
            self.z = (matrix.getSingleValue(1,0)-matrix.getSingleValue(0,1))*s
            self.w = 0.25/s
        else:
            ad0 = d0
            ad1 = d1
            ad2 = d2
            if d0>=d1 and d0>=d2:
                s = math.sqrt(1.0+d0-d1-d2)*2.0
                self.x = 0.25*s
                self.y = (matrix.getSingleValue(0,1)+matrix.getSingleValue(1,0))/s
                self.z = (matrix.getSingleValue(0,2)+matrix.getSingleValue(2,0))/s
                self.w = (matrix.getSingleValue(2,1)-matrix.getSingleValue(1,2))/s
            elif d1>=d2:
                s = math.sqrt(1.0+d1-d0-d2)*2.0
                self.x = (matrix.getSingleValue(0,1)+matrix.getSingleValue(1,0))/s
                self.y = 0.25*s
                self.z = (matrix.getSingleValue(1,2)+matrix.getSingleValue(2,1))/s
                self.w = (matrix.getSingleValue(0,2)+matrix.getSingleValue(2,0))/s
            else:
                s = math.sqrt(1.0+d2-d0-d1)*2.0
                self.x = (matrix.getSingleValue(0,2)+matrix.getSingleValue(2,0))/s
                self.y = (matrix.getSingleValue(1,2)+matrix.getSingleValue(2,1))/s
                self.z = 0.25*s
                self.w = (matrix.getSingleValue(1,0)+matrix.getSingleValue(0,1))/s
        self.normalizeInPlace()


    @staticmethod
    def createFromMatrix(inMatrix):
        matrix = Matrix3(inMatrix)
        matrix.transposeInPlace()
        eps = epsilon.getEpsilon()

        x, y, z, w = (0.0, 0.0, 0.0, 1.0)

        d1,d2,d3 = matrix.getDiagonal().getValues()
        t = d1+d2+d3+1.0
        if t>eps:
            s = 0.5/math.sqrt(t)
            x = (matrix.getSingleValue(2,1)-matrix.getSingleValue(1,2))*s
            y = (matrix.getSingleValue(0,2)-matrix.getSingleValue(2,0))*s
            z = (matrix.getSingleValue(1,0)-matrix.getSingleValue(0,1))*s
            w = 0.25/s
        else:
            ad1 = d1
            ad2 = d2
            ad3 = d3
            if ad1>=ad2 and ad1>=ad3:
                s = math.sqrt(1.0+d1-d2-d3)*2.0
                x = 0.5/s
                y = (matrix.getSingleValue(0,1)+matrix.getSingleValue(1,0))/s
                z = (matrix.getSingleValue(0,2)+matrix.getSingleValue(2,0))/s
                w = (matrix.getSingleValue(1,2)+matrix.getSingleValue(2,1))/s
            elif ad2>=ad1 and ad2>=ad3:
                s = math.sqrt(1.0+d2-d1-d3)*2.0
                x = (matrix.getSingleValue(0,1)+matrix.getSingleValue(1,0))/s
                y = 0.5/s
                z = (matrix.getSingleValue(1,2)+matrix.getSingleValue(2,1))/s
                w = (matrix.getSingleValue(0,2)+matrix.getSingleValue(2,0))/s
            else:
                s = math.sqrt(1.0+d3-d1-d2)*2.0
                x = (matrix.getSingleValue(0,2)+matrix.getSingleValue(2,0))/s
                y = (matrix.getSingleValue(1,2)+matrix.getSingleValue(2,1))/s
                z = 0.5/s
                w = (matrix.getSingleValue(0,1)+matrix.getSingleValue(1,0))/s

        return Quaternion((x, y, z, w))

    def __toMatrixPreCalculation(self):
        x,y,z,w = self.__data
        xx = 2.0*x*x
        yy = 2.0*y*y
        zz = 2.0*z*z
        xy = 2.0*x*y
        zw = 2.0*z*w
        xz = 2.0*x*z
        yw = 2.0*y*w
        yz = 2.0*y*z
        xw = 2.0*x*w
        return xx, yy, zz, xy, zw, xz, yw, yz, xw

    def toMatrix3(self):
        xx, yy, zz, xy, zw, xz, yw, yz, xw = self.__toMatrixPreCalculation()
        return Matrix3([1.0-yy-zz, xy-zw, xz+yw,
                        xy+zw, 1.0-xx-zz, yz-xw,
                        xz-yw, yz+xw, 1.0-xx-yy])

    def toMatrix4(self):
        xx, yy, zz, xy, zw, xz, yw, yz, xw = self.__toMatrixPreCalculation()
        return Matrix4([1.0-yy-zz, xy-zw, xz+yw, 0.0,
                        xy+zw, 1.0-xx-zz, yz-xw, 0.0,
                        xz-yw, yz+xw, 1.0-xx-yy, 0.0,
                        0.0, 0.0, 0.0, 1.0])

    def toMayaMQuaternion(self):
        return OpenMaya.MQuaternion(self.__data[0], self.__data[1], self.__data[2], self.__data[3])


#    def __div__(self, other):
#        """Division.
#
#        >>> q=quat(0.9689, 0.2160, 0.1080, 0.0540)
#        >>> print q/2.0
#        (0.4844, 0.1080, 0.0540, 0.0270)
#        """
#        T = type(other)
#        # quat/scalar
#        if T==types.FloatType or T==types.IntType or T==types.LongType:
#            return quat(self.w/other, self.x/other, self.y/other, self.z/other)
#        # unsupported
#        else:
#            raise TypeError, "unsupported operand type for /"
#
#    def __pow__(self, other):
#        """Return self**q."""
##        if modulo!=None:
##            raise TypeError, "unsupported operation"
#        q = quat(other)
#        return (q*self.log()).exp()
#
#    def __neg__(self):
#        """Negation.
#
#        >>> q=quat(0.9689, 0.2160, 0.1080, 0.0540)
#        >>> print -q
#        (-0.9689, -0.2160, -0.1080, -0.0540)
#        """
#        return quat(-self.w, -self.x, -self.y, -self.z)
#
#    def __pos__(self):
#        """
#        >>> q=quat(0.9689, 0.2160, 0.1080, 0.0540)
#        >>> print +q
#        (0.9689, 0.2160, 0.1080, 0.0540)
#        """
#        return quat(+self.w, +self.x, +self.y, +self.z)
#
#    def __abs__(self):
#        """Return magnitude.
#
#        >>> q=quat(0.9689, 0.2160, 0.1080, 0.0540)
#        >>> print round(abs(q),5)
#        1.0
#        """
#        return math.sqrt(self.w*self.w + self.x*self.x +
#                         self.y*self.y + self.z*self.z)
#
#    def conjugate(self):
#        """Return conjugate.
#
#        >>> q=quat(0.9689, 0.2160, 0.1080, 0.0540)
#        >>> print q.conjugate()
#        (0.9689, -0.2160, -0.1080, -0.0540)
#        """
#        return quat(self.w, -self.x, -self.y, -self.z)
#
#    def normalize(self):
#        """Return normalized quaternion.
#
#        >>> q=quat(0.9, 0.5, 0.2, 0.3)
#        >>> q=q.normalize()
#        >>> print q
#        (0.8250, 0.4583, 0.1833, 0.2750)
#        >>> print abs(q)
#        1.0
#        """
#        nlen = 1.0/abs(self)
#        return quat(self.w*nlen, self.x*nlen, self.y*nlen, self.z*nlen)
#
#    def inverse(self):
#        """Return inverse.
#
#        >>> q=quat(0.9, 0.5, 0.2, 0.3)
#        >>> print q.inverse()
#        (0.7563, -0.4202, -0.1681, -0.2521)
#        """
#        len_2 = self.w*self.w + self.x*self.x + self.y*self.y + self.z*self.z
#        return self.conjugate()/len_2
#
#    def toAngleAxis(self):
#        """Return angle (in radians) and rotation axis.
#
#        >>> q=quat(0.9, 0.5, 0.2, 0.3)
#        >>> angle, axis = q.toAngleAxis()
#        >>> print round(angle,4)
#        1.2011
#        >>> print axis
#        (0.8111, 0.3244, 0.4867)
#        """
#
#        nself = self.normalize()
#
#        # Clamp nself.w (since the quat has to be normalized it should
#        # be between -1 and 1 anyway, but it might be slightly off due
#        # to numerical inaccuracies)
#        w = max(min(nself.w,1.0),-1.0)
#
#        w = math.acos(w)
#        s = math.sin(w)
#        if s<1E-12:
#            return (0.0, Vector3(0.0,0.0,0.0))
#        return (2.0*w, Vector3(nself.x/s, nself.y/s, nself.z/s))
#
#    def fromAngleAxis(self, angle, axis):
#        """Initialize self from an angle (in radians) and an axis and returns self."""
#        if axis==Vector3(0):
#            self.w = 1.0
#            self.x = 0.0
#            self.y = 0.0
#            self.z = 0.0
#        else:
#            angle/=2.0
#            self.w = math.cos(angle)
#            x, y, z = axis
#            s = math.sin(angle)/math.sqrt(x*x+y*y+z*z)
#            self.x = x*s
#            self.y = y*s
#            self.z = z*s
#            dummy = self.normalize()
#            self.w = dummy.w
#            self.x = dummy.x
#            self.y = dummy.y
#            self.z = dummy.z
#
#        return self
#
#    def toMat3(self):
#        """Return rotation matrix as mat3."""
#        x,y,z,w = self.x, self.y, self.z, self.w
#        xx = 2.0*x*x
#        yy = 2.0*y*y
#        zz = 2.0*z*z
#        xy = 2.0*x*y
#        zw = 2.0*z*w
#        xz = 2.0*x*z
#        yw = 2.0*y*w
#        yz = 2.0*y*z
#        xw = 2.0*x*w
#        return Matrix3(1.0-yy-zz, xy-zw, xz+yw,
#                     xy+zw, 1.0-xx-zz, yz-xw,
#                     xz-yw, yz+xw, 1.0-xx-yy)
#
#    def toMat4(self):
#        """Return rotation matrix as mat4."""
#        x,y,z,w = self.x, self.y, self.z, self.w
#        xx = 2.0*x*x
#        yy = 2.0*y*y
#        zz = 2.0*z*z
#        xy = 2.0*x*y
#        zw = 2.0*z*w
#        xz = 2.0*x*z
#        yw = 2.0*y*w
#        yz = 2.0*y*z
#        xw = 2.0*x*w
#        return Matrix4(1.0-yy-zz, xy-zw, xz+yw, 0.0,
#                     xy+zw, 1.0-xx-zz, yz-xw, 0.0,
#                     xz-yw, yz+xw, 1.0-xx-yy, 0.0,
#                     0.0, 0.0, 0.0, 1.0)
#
#    def fromMat(self, m):
#        """Initialize self from either a mat3 or mat4 and returns self."""
#        global _epsilon
#
#        d1,d2,d3 = m[0,0],m[1,1],m[2,2]
#        t = d1+d2+d3+1.0
#        if t>_epsilon:
#            s = 0.5/math.sqrt(t)
#            self.w = 0.25/s
#            self.x = (m[2,1]-m[1,2])*s
#            self.y = (m[0,2]-m[2,0])*s
#            self.z = (m[1,0]-m[0,1])*s
#        else:
#            ad1 = d1
#            ad2 = d2
#            ad3 = d3
#            if ad1>=ad2 and ad1>=ad3:
#                s = math.sqrt(1.0+d1-d2-d3)*2.0
#                self.x = 0.5/s
#                self.y = (m[0,1]+m[1,0])/s
#                self.z = (m[0,2]+m[2,0])/s
#                self.w = (m[1,2]+m[2,1])/s
#            elif ad2>=ad1 and ad2>=ad3:
#                s = math.sqrt(1.0+d2-d1-d3)*2.0
#                self.x = (m[0,1]+m[1,0])/s
#                self.y = 0.5/s
#                self.z = (m[1,2]+m[2,1])/s
#                self.w = (m[0,2]+m[2,0])/s
#            else:
#                s = math.sqrt(1.0+d3-d1-d2)*2.0
#                self.x = (m[0,2]+m[2,0])/s
#                self.y = (m[1,2]+m[2,1])/s
#                self.z = 0.5/s
#                self.w = (m[0,1]+m[1,0])/s
#
#        return self
#
#    def dot(self, b):
#        """Return the dot product of self and b."""
#        return self.w*b.w + self.x*b.x + self.y*b.y + self.z*b.z
#
#    def log(self):
#        """Return the natural logarithm of self."""
#        global _epsilon
#
#        b = math.sqrt(self.x*self.x + self.y*self.y + self.z*self.z)
#        res = quat()
#        if abs(b)<=_epsilon:
#            res.x = 0.0
#            res.y = 0.0
#            res.z = 0.0
#            if self.w<=_epsilon:
#                raise ValueError, "math domain error"
#            res.w = math.log(self.w)
#        else:
#            t = math.atan2(b, self.w)
#            f = t/b
#            res.x = f*self.x
#            res.y = f*self.y
#            res.z = f*self.z
#            ct = math.cos(t)
#            if abs(ct)<=_epsilon:
#                raise ValueError, "math domain error"
#            r = self.w/ct
#            if r<=_epsilon:
#                raise ValueError, "math domain error"
#            res.w = math.log(r)
#
#        return res
#
#    def exp(self):
#        """Return the exponential of self."""
#        global _epsilon
#
#        b = math.sqrt(self.x*self.x + self.y*self.y + self.z*self.z)
#        res = quat()
#        if abs(b)<=_epsilon:
#            res.x = 0.0
#            res.y = 0.0
#            res.z = 0.0
#            res.w = math.exp(self.w)
#        else:
#            f = math.sin(b)/b
#            res.x = f*self.x
#            res.y = f*self.y
#            res.z = f*self.z
#            res.w = math.exp(self.w)*math.cos(b)
#
#        return res
#
#    def rotateVec(self, v):
#        """Return the rotated vector v.
#
#        The quaternion must be a unit quaternion.
#        This operation is equivalent to turning v into a quat, computing
#        self*v*self.conjugate() and turning the result back into a vec3.
#        """
#
#        v = Vector3(v)
#        ww = self.w*self.w
#        xx = self.x*self.x
#        yy = self.y*self.y
#        zz = self.z*self.z
#        wx = self.w*self.x
#        wy = self.w*self.y
#        wz = self.w*self.z
#        xy = self.x*self.y
#        xz = self.x*self.z
#        yz = self.y*self.z
#
#        return Vector3(ww*v.x + xx*v.x - yy*v.x - zz*v.x + 2*((xy-wz)*v.y + (xz+wy)*v.z),
#                     ww*v.y - xx*v.y + yy*v.y - zz*v.y + 2*((xy+wz)*v.x + (yz-wx)*v.z),
#                     ww*v.z - xx*v.z - yy*v.z + zz*v.z + 2*((xz-wy)*v.x + (yz+wx)*v.y))
#
#
#def slerp(t, q0, q1, shortest=True):
#    """Spherical linear interpolation between two quaternions.
#
#    The return value is an interpolation between q0 and q1. For t=0.0
#    the return value equals q0, for t=1.0 it equals q1.
#    q0 and q1 must be unit quaternions.
#    If shortest is True the interpolation is always done along the
#    shortest path.
#    """
#    global _epsilon
#
#    ca = q0.dot(q1)
#    if shortest and ca<0:
#        ca = -ca
#        neg_q1 = True
#    else:
#        neg_q1 = False
#    o = math.acos(ca)
#    so = math.sin(o)
#
#    if (abs(so)<=_epsilon):
#        return quat(q0)
#
#    a = math.sin(o*(1.0-t)) / so
#    b = math.sin(o*t) / so
#    if neg_q1:
#        return q0*a - q1*b
#    else:
#        return q0*a + q1*b
#
#def squad(t, a, b, c, d):
#    """Spherical cubic interpolation."""
#    return slerp(2*t*(1.0-t), slerp(t,a,d), slerp(t,b,c))
#
