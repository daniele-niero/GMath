# A math library for 3D graphic.
# Copyright (C) 2010 Daniele Niero

# Author contact: nieroinfo@gmail.com

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

from .. import dagWrappers

from maya import OpenMaya
import vector3
import copy


__all__ = ['_NurbsCurve']

class _NurbsCurve(object):
    def __init__(self,
                 points=([0.0,0.0,0.0], [0.0,2.0,0.0], [0.0,4.0,0.0], [0.0,6.0,0.0], [0.0,8.0,0.0]),
                 degree=3):

        self.__positions = []
        self.__weights = []
        self.__knots = []
        self.__degree = degree
        self.__normalized = False

        # note that this class doesn't support close curves yet,
        # but this attribute is necessary for properly get information from maya.
        # see also the method initFromMayaCurve in this class and also the method __createCurves in bitCurve.BitCurve,
        # where this attribute is used for properly build a curve in maya.
        self.__closed = False

        self.init(points, degree)

    def init(self, points, degree):
        self._destroy()
        self.__setCvPositions(points)

        self.__degree = degree
        nknots = len(self.__positions) + (self.__degree * 2) -2

        for i in range(self.__degree):
            self.__knots.append(float(0))

        n = 0
        nspans = self.getSpansNumber()
        for i in range(0, nspans): # was (0, nspans - (self.__degree - 1))  but at that point nspans was len(self.__positions)-1, which is wrong!
            self.__knots.append(float(n))
            n += 1

        for i in range(self.__degree + 1):
            self.__knots.append(float(n))

        for i in range(len(self.__positions)):
            self.__weights.append(1.0)

    def _destroy(self):
        self.__positions = []
        self.__weights = []
        self.__knots = []

    def getSpansNumber(self):
        return len(self.__positions) - self.__degree

    # please, see the __init__ for a detail explanation of these getter and setter
    def getClosedValue(self):
        return self.__closed

    def setClosedValue(self, value):
        self.__closed = value

    def getKnots(self):
        return self.__knots

    def setKnots(self, knots):
        self.__knots = knots

    def __setCvPositions(self, points):
        self.__positions = []
        for point in points:
            self.__positions.append(toPimathVec3(point))

    def setCvPositions(self, points):
        '''
        Please note that this function is only calling the init function for reinitialise the curve.
        If you are planning to change the degree as well, you would probably better to call the init function
        and passing cv's positions and degree with one single call
        '''
        self.init(points, self.__degree)

    def getCvPositions(self):
        return copy.copy(self.__positions)

    def setDegree(self, degree):
        '''
        Please note that this function is only calling the init function for reinitialise the curve.
        If you are planning to change the degree as well, you would probably better to call the init function
        and passing cv's positions and degree with one single call
        '''
        self.init(self.__positions, degree)

    def getDegree(self):
        return self.__degree

    def __basis(self, i, degree, param, knots):
        ret = 0

        if degree>0:
            n1 = (param-knots[i])*self.__basis(i, degree-1, param, knots)

            d1 = knots[i+degree] - knots[i]
            n2 = (knots[i+degree+1] - param) * self.__basis(i+1, degree-1, param, knots)
            d2 = knots[i+degree+1] - knots[i+1]
            if d1 > 0.0001 or d1 < -0.0001:
                a = n1 / d1
            else:
                a = 0
            if d2 > 0.0001 or d2 < -0.0001:
                b = n2 / d2
            else:
                b = 0
            ret = a + b
        else:
            if knots[i] <= param and param <= knots[i+1]:

                ret = 1
            else:
                ret = 0
        return ret

    def __evaluatePositionOnCurve(self, param, degree, points, weights, knots):
        position = pimath.Vec3()
        rational = 0
        for i in range(0, len(self.__positions)):
            b = self.__basis(i, degree, param, knots)
            p = points[i] * (b*weights[i])
            position += p
            rational = rational + b*weights[i]

        position *= (1.0/(rational+0.00001))
        return position

    def evaluatePositionOnCurve(self, param, normalizeParam = True):
        if normalizeParam:
            param = param * abs(self.__knots[0] - self.__knots[-1])

        position = self.__evaluatePositionOnCurve(param, self.__degree, self.__positions, self.__weights, self.__knots)

        return position

    def normalize(self):
        """Normalizes curve 0-1, and makes uniform"""
        for i in range(0, self.__degree):
            self.__knots[i]  = 0.0
            self.__knots[-(i+1)] = 1.0

        knotsrange = len(self.__knots)-self.__degree*2
        step = 1.0/(knotsrange-1)

        for i in range(0, knotsrange):
            self.__knots[i+self.__degree] = step*i


    def initFromMayaCurve(self, mayaCurve, pointSpace=OpenMaya.MSpace.kWorld):
        self._destroy()

        mayaCurve = dagWrappers.DagNodeWrapper(mayaCurve)
        if mayaCurve.getApiTypeStr() == 'kTransform':
            mayaCurve = mayaCurve.getChild(0, 'kNurbsCurve')
        if mayaCurve.getApiTypeStr() != 'kNurbsCurve':
            raise TypeError, `mayaCurve`+' is not a mayaCurve'

        crvFn = OpenMaya.MFnNurbsCurve()
        crvFn.setObject(mayaCurve.getMDagPath())

        # please, see the __init__ for a detail explanation of this
        self.__closed = crvFn.form() != 0

        knots = OpenMaya.MDoubleArray()
        crvFn.getKnots(knots)
        self.__degree = crvFn.degree()
        points = OpenMaya.MPointArray()
        crvFn.getCVs(points, pointSpace)

        positions = []
        for i in range(0,points.length()):
            positions.append(OpenMaya.MVector(points[i]))
            self.__weights.append(1.0)

        self.__setCvPositions(positions)

        for i in range(0,knots.length()):
            self.__knots.append(float(knots[i]))

        self.__knots.insert(0, knots[0])
        self.__knots.append(knots[len(knots)-1])

    def getTangent(self, param):
        if param == 0.0:
            param = 0.000001
        paramStep = 0.000001
        paramStart = param - paramStep
        paramEnd = param + paramStep

        start = self.evaluatePositionOnCurve(paramStart)
        end = self.evaluatePositionOnCurve(paramEnd)

        tangent = (end - start).normalized()

        return tangent

    def __smallestNumberIdInArray(self, array):
        smallestNumberId = 0
        smallestNumber = 9999999999999.0
        i = 0
        for number in array:
            if number < smallestNumber:
                smallestNumber = number
                smallestNumberId = i

            i += 1

        return smallestNumberId

    def __getParamRecursive(self, position, startParam, endParam, normalizeParam):
        if startParam < 0.0:
            startParam = 0.0
        if endParam > self.__knots[-1]:
            endParam = self.__knots[-1]

        nSteps = 10.0
        step = abs(startParam - endParam) / nSteps
        param = startParam

        shortestDistance = 9999999999999.0
        shortestPointParam = 0.0
        params = []
        distances = []
        for i in range(int(nSteps)):
            paramPos = self.evaluatePositionOnCurve(param, normalizeParam)
            distance = (paramPos - position).length()

            params.append(param)
            distances.append(distance)

            param += step

        smallestDistanceId = self.__smallestNumberIdInArray(distances)
        shortestPointParam = params[smallestDistanceId]

        resultParam = shortestPointParam

        if abs(startParam - endParam) > 0.001:
            resultParam = self.__getParamRecursive(position, shortestPointParam - step, shortestPointParam + step, normalizeParam)

        return resultParam

    def findClosestParameter(self, position, normalizeParam = True):
        parameter = self.__getParamRecursive(position, self.__knots[0], self.__knots[-1], False)

        if parameter < 0.0:
            parameter = 0.0
        elif parameter > self.__knots[-1]:
            parameter = self.__knots[-1]

        if normalizeParam:
            parameter = parameter / abs(self.__knots[0] - self.__knots[-1])

        return parameter


