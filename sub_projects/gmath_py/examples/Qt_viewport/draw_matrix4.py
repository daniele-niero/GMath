import math

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from gmath import Matrix4, Matrix3, Vector3

from base_object import BaseObject

class AxisDraw(BaseObject):
    def __init__(self, color):
        BaseObject.__init__(self)

        self.mat = Matrix4()

        self.color = color
        
        self.topPoint  = Vector3(0, 1, 0)
        self.coneBasePoints = []
        self.cylinderTopPoints = []
        self.cylinderBasePoints = []

        d = 2*math.pi/10
        a = 0.0
        for i in range(0, 11):
            v = Vector3(math.cos(a)*0.05, 0.8, math.sin(a)*0.05)
            self.coneBasePoints.append(v)
            v = Vector3(math.cos(a)*0.01, 0.8, math.sin(a)*0.01)
            self.cylinderTopPoints.append(v)
            v = Vector3(math.cos(a)*0.01, 0.0, math.sin(a)*0.01)
            self.cylinderBasePoints.append(v)
            a += d

    def rotate(self, axis, angle):
        mat = Matrix3.createFromAxisAngle(axis, angle)
        
        self.topPoint  = mat*self.topPoint

        for i in range(0, len(self.coneBasePoints)):
            self.coneBasePoints[i] = mat*self.coneBasePoints[i]
            self.cylinderTopPoints[i] = mat*self.cylinderTopPoints[i]
            self.cylinderBasePoints[i] = mat*self.cylinderBasePoints[i]
            

    def _draw(self):
        res = len(self.coneBasePoints)
        topPoint  = self.mat*self.topPoint

        norms = []
        
        coneBasePoints = []
        cylinderBasePoints = []
        cylinderTopPoints = []
        for i in range(0, res):
            coneBasePoints.append( self.mat*self.coneBasePoints[i] )
            cylinderBasePoints.append( self.mat*self.cylinderBasePoints[i] )
            cylinderTopPoints.append( self.mat*self.cylinderTopPoints[i] )

        # CONE BODY
        glBegin(GL_TRIANGLE_FAN)
        n = (cylinderTopPoints[0] - cylinderBasePoints[0]).normalize()
        glNormal3f(n.x, n.y, n.z)
        glVertex3f(topPoint.x, topPoint.y, topPoint.z)
        for i in range(0, res):
            n = (coneBasePoints[i]-cylinderTopPoints[i]).normalize()
            norms.append(n)
            glNormal3f(n.x, n.y, n.z)
            glVertex3f(coneBasePoints[i].x, coneBasePoints[i].y, coneBasePoints[i].z)
        glEnd()

        # CONE BASE
        n = (cylinderBasePoints[0] - cylinderTopPoints[0]).normalize()
        glBegin(GL_QUAD_STRIP)
        for i in range(0, res):
            glNormal3f(norms[i].x, norms[i].y, norms[i].z)
            glVertex3f(coneBasePoints[i].x, coneBasePoints[i].y, coneBasePoints[i].z)
            glNormal3f(n.x, n.y, n.z)
            glVertex3f(cylinderTopPoints[i].x, cylinderTopPoints[i].y, cylinderTopPoints[i].z)
        glEnd()

        # CYLINDER
        glBegin(GL_QUAD_STRIP)
        for i in range(0, res):
            glNormal3f(norms[i].x, norms[i].y, norms[i].z)
            glVertex3f(cylinderTopPoints[i].x, cylinderTopPoints[i].y, cylinderTopPoints[i].z)
            glNormal3f(norms[i].x, norms[i].y, norms[i].z)
            glVertex3f(cylinderBasePoints[i].x, cylinderBasePoints[i].y, cylinderBasePoints[i].z)
        glEnd()

        # glBegin(GL_QUAD_STRIP)
        # glVertex3f(pos.x, pos.y, pos.z)
        # glVertex3f(topPoint.x, topPoint.y, topPoint.z)
        # glEnd()

    def drawForSelection(self):
        glLineWidth(4)
        BaseObject.drawForSelection(self)

    def draw(self):
        glLineWidth(2)
        BaseObject.draw(self)

    def drawSelected(self):
        glLineWidth(2)
        BaseObject.drawSelected(self)


class Matrix4Draw(object):
    def __init__(self):
        self.mat = Matrix4()

        axisX = AxisDraw( (1,0,0) )
        axisY = AxisDraw( (0,1,0) )
        axisZ = AxisDraw( (0,0,1) )
        axisX.rotate(Vector3(0,0,1), math.radians(90.0))
        axisZ.rotate(Vector3(1,0,0), math.radians(-90.0))

        self.__drawAxis = (axisX, axisY, axisZ)

        self.__selectedAxis = None

    def __update(self):
        for axis in self.__drawAxis:
            axis.mat = self.mat

    def isPickedColor(self, color):
        i=0
        for axis in self.__drawAxis:
            if axis.isPickedColor(color) == True:
                self.__selectedAxis = i
                return True
            i+=1
        return False
        
    def _draw(self):
        self.__update()
        for axis in self.__drawAxis:
            axis._draw()
            
    def draw(self):
        #glDisable(GL_LIGHTING)

        self.__update()
        for axis in self.__drawAxis:
            axis.draw()

        #glEnable(GL_LIGHTING)

    def drawForSelection(self):
        self.__update()
        for axis in self.__drawAxis:
            axis.drawForSelection()

    def drawSelected(self):
        self.__update()
        self.__drawAxis[self.__selectedAxis].drawSelected()





