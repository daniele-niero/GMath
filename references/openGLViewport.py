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

import sys, math
from PySide.QtOpenGL import QGLWidget, QGLFormat
from PySide.QtGui import QApplication
from PySide import QtCore

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


from gmath import Matrix4, Matrix3, Vector3, RotationOrder

class Camera(object):
    def __init__(self):
        self.__pov = Matrix4()
        self.__camera = Matrix4()

        self.setZoom(20)
        self.rotate(-25, 40)

    def translate(self, x, y, z):
        self.__pov.translate(Vector3(x, y, z))

    def setZoom(self, z):
        self.__camera[14] = z

    def rotate(self, x, y):
        rotMatrix = Matrix3.createFromEuler(x, y, 0.0, RotationOrder.XYZ)
        self.__pov.setRotation(rotMatrix)

    def getFinalMatrix(self):
        finalMatrix = self.__camera * self.__pov

        return finalMatrix


class TestGLWidget(QGLWidget):
    def __init__(self, parent=None, name=None):
        QGLWidget.__init__(self, parent, name)

        self.rot = Vector3(-25, 40, 0.0)
        self.z = 20

        self.camera = Camera()

        self.farPlane = 1000.0
        self.nearPlane = 1.0

        self.oldMousePos = [ 0.0, 0.0 ]

        self.pressedButton = None

    def screenToWorld(self, winX, winY):
        viewport = glGetIntegerv(GL_VIEWPORT)
        modelview = glGetDoublev(GL_MODELVIEW_MATRIX)
        projection = glGetDoublev(GL_PROJECTION_MATRIX)

        oglPos = gluUnProject( winX, -winY, 1, modelview, projection, viewport)
        retVec = Vector3(oglPos[0], oglPos[1], oglPos[2])
        return retVec

    def mousePressEvent(self, evt):
        screenPos = evt.pos()
        worldPos = self.screenToWorld(screenPos.x(), screenPos.y())
        self.oldMousePos[0], self.oldMousePos[1] = worldPos.x, worldPos.y

        self.pressedButton = evt.button()

    def mouseMoveEvent(self, evt):
        if evt.modifiers() == QtCore.Qt.AltModifier:
            screenPos = evt.pos()
            worldPos = self.screenToWorld(screenPos.x(), screenPos.y())

            deltaX = worldPos.x - self.oldMousePos[ 0 ]
            deltaY = worldPos.y - self.oldMousePos[ 1 ]

            if self.pressedButton == QtCore.Qt.LeftButton:
                multiplier = (self.z/self.farPlane)
                x = -deltaX * multiplier
                y = -deltaY * multiplier
                self.camera.translate(x, y, 0.0)

            elif self.pressedButton == QtCore.Qt.MidButton:
                self.z += deltaY * 0.3
                self.camera.setZoom(self.z)

            elif self.pressedButton == QtCore.Qt.RightButton:
                self.rot.x += deltaY * 0.005
                self.rot.y += -deltaX * 0.005
                self.camera.rotate(self.rot.x, self.rot.y)

            self.oldMousePos[0], self.oldMousePos[1] = worldPos.x, worldPos.y
            self.updateGL()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glPushMatrix()

        inverseFinal = self.camera.getFinalMatrix().inverse()
        values = []
        for i in range(0, 16):
            values.append(inverseFinal[i])
        glLoadMatrixf(values)

        self.drawGround()
        self.draw()

        glPopMatrix()
        glFlush()

    def drawGround(self, increment=1, gridSize=5, gridColor1=[0.6, 0.6, 0.6], gridColor2=[0.4, 0.4, 0.4]):
        glColor3f(gridColor2[0], gridColor2[1], gridColor2[2])
        glLineWidth(2)
        glBegin(GL_LINES)
        glVertex3f(0, -0.001, gridSize)
        glVertex3f(0, -0.001, -gridSize)
        glVertex3f(gridSize, -0.001, 0)
        glVertex3f(-gridSize, -0.001, 0)
        glEnd()

        glColor3f(gridColor1[0], gridColor1[1], gridColor1[2])
        glLineWidth(1)
        glBegin(GL_LINES)
        for i in range(-gridSize, gridSize+1, increment):
            glVertex3f(i, -0.001, gridSize)
            glVertex3f(i, -0.001, -gridSize)

            glVertex3f(gridSize, -0.001, i)
            glVertex3f(-gridSize, -0.001, i)
        glEnd()

    def draw(self):
        pass


    def resizeGL(self, w, h):
        if h==0:
            h=1

        glViewport(0, 0, w, h)
        aspectRatio = float(w)/float(h)

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()

        gluPerspective(35.0, aspectRatio, self.nearPlane, self.farPlane);

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def initializeGL(self):
        glutInit()
        glEnable(GL_DEPTH_TEST)

        ambient = .3
        diffuse = 1
        specular = 1
        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, [ambient, ambient, ambient, 1.0])
        glLightfv(GL_LIGHT0, GL_AMBIENT, [ambient, ambient, ambient, 1.0])
        glLightfv(GL_LIGHT0, GL_DIFFUSE, [diffuse, diffuse, diffuse, 1.0])
        glLightfv(GL_LIGHT0, GL_SPECULAR, [specular, specular, specular, 1.0])
        glLight(GL_LIGHT0, GL_POSITION,  (0, 1.5, 1, 0))

        glEnable(GL_COLOR_MATERIAL)
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE)

        glClearColor(0.7, 0.7, 0.7, 1.0)


if __name__=='__main__':
    QApplication.setColorSpec(QApplication.CustomColor)
    app=QApplication(['un bel pippo esempio'])

    widget=TestGLWidget()
    widget.show()
    app.exec_()

