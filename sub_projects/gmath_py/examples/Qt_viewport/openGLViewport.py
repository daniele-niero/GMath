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
        self._pov = Matrix4()
        self._camera = Matrix4()

        self.reset()

    def reset(self):
        self._pov.setToIdentity()
        self._camera.setToIdentity()
        self.__rotX = -25.0
        self.__rotY = 20.0
        self.setZoom(20.0)
        self.rotate(self.__rotX, self.__rotY)
        
    def translate(self, x, y, z):
        self._pov.translate(Vector3(x, y, z))

    def getPosition(self):
        return self._pov.getPosition()

    def setZoom(self, z):
        self._camera[14] = z

    def getZoom(self):
        return self._camera[14]

    def rotate(self, x, y):
        rotMatrix = Matrix3.createFromEuler(
            math.radians(x), math.radians(y), 0.0, RotationOrder.XYZ)
        self._pov.setRotation(rotMatrix)

    def addRotation(self, x, y):
        self.__rotX += x
        self.__rotY += y
        rotMatrix = Matrix3.createFromEuler(
            math.radians(self.__rotX), math.radians(self.__rotY), 0.0, RotationOrder.XYZ)
        self._pov.setRotation(rotMatrix)

    def getFinalMatrix(self):
        finalMatrix = self._camera * self._pov
        return finalMatrix


class SceneLights(object):
    def __init__(self):
        self.ambient  = [0.3, 0.3, 0.3, 1.0]
        self.diffuse  = [1.0, 1.0, 1.0, 1.0]
        self.specular = [1.0, 1.0, 1.0, 1.0]

        self.specularPos = Vector3(100, 100, 100)
        self.diffusePos  = Vector3(100, 100, 100)


class Viewport(QGLWidget):
    def __init__(self, parent=None, name=None):
        QGLWidget.__init__(self, parent, name)

        self.camera = Camera()

        self.farPlane = 1000.0
        self.nearPlane = 0.0001

        self.oldMousePos = [ 0.0, 0.0 ]

        self.pressedButton = None

        self.objsToDraw = []
        self.selectedObj = []

    def resetCamera(self):
        self.camera.reset()

    def initializeGL(self):
        glEnable(GL_DEPTH_TEST)
        glFrontFace(GL_CW)
        glEnable(GL_CULL_FACE)

        ambient = 0.2
        diffuse = 0.8
        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)

        glLightfv(GL_LIGHT0, GL_AMBIENT, [ambient, ambient, ambient, 1.0])
        glLightfv(GL_LIGHT0, GL_DIFFUSE, [diffuse, diffuse, diffuse, 1.0])
        glLight(GL_LIGHT0, GL_POSITION,  (10, 5, 20))

        glEnable(GL_COLOR_MATERIAL)
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE)

        glClearColor(0.7, 0.7, 0.7, 1.0)

    def resizeGL(self, w, h):
        if h==0:
            h=1

        glViewport(0, 0, w, h)
        aspectRatio = float(w)/float(h)

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()

        gluPerspective(35.0, aspectRatio, self.nearPlane, self.farPlane)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glPushMatrix()

        values = self.camera.getFinalMatrix().inverse().data
        glLoadMatrixf(values)

        glDisable(GL_LIGHTING)
        for obj in self.selectedObj:
            obj.drawSelected()
        
        self.drawGround()
        
        glEnable(GL_LIGHTING)
        for obj in self.objsToDraw:
            obj.draw()
            
        glPopMatrix()
        glFlush()

    def paintGLForPicking(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        # turn off texturing, lighting and fog
        #glDisable(GL_TEXTURE_2D)
        #glDisable(GL_FOG)
        glDisable(GL_LIGHTING)

        glPushMatrix()

        values = self.camera.getFinalMatrix().inverse().data
        glLoadMatrixf(values)

        # render every object in our scene
        for obj in self.objsToDraw:
            obj.drawForSelection()

        glPopMatrix()
        glFlush()

    def screenToWorld(self, winX, winY):
        viewport = glGetIntegerv(GL_VIEWPORT)
        modelview = glGetDoublev(GL_MODELVIEW_MATRIX)
        projection = glGetDoublev(GL_PROJECTION_MATRIX)

        oglPos = gluUnProject( winX, -winY, 1, modelview, projection, viewport)
        retVec = Vector3(oglPos[0], oglPos[1], oglPos[2])
        return retVec

    def keyPressEvent(self, evt):
        if evt.text() == 'r':
            self.resetCamera()
            self.updateGL()

    def mousePressEvent(self, evt):
        screenPos = evt.pos()
        print screenPos.x(), screenPos.y()
        worldPos = self.screenToWorld(screenPos.x(), screenPos.y())
        self.oldMousePos[0], self.oldMousePos[1] = worldPos.x, worldPos.y

        self.pressedButton = evt.button()

        if evt.modifiers() != QtCore.Qt.AltModifier:

            self.selectedObj = []

            self.paintGLForPicking()

            viewport = glGetIntegerv(GL_VIEWPORT)
            pixel = glReadPixels(screenPos.x(), viewport[3] - screenPos.y(), 1, 1, GL_RGB, GL_FLOAT)
            pixel = (pixel[0][0][0], pixel[0][0][1], pixel[0][0][2])
            # now our picked screen pixel color is stored in pixel[3]
            # so we search through our object list looking for the object that was selected
            i = 0
            for obj in self.objsToDraw:
                if obj.isPickedColor(pixel):
                    self.selectedObj.append(obj)
                    break
                i+=1

            self.updateGL()

    def mouseMoveEvent(self, evt):
        if evt.modifiers() == QtCore.Qt.AltModifier:
            screenPos = evt.pos()
            worldPos = self.screenToWorld(screenPos.x(), screenPos.y())

            deltaX = worldPos.x - self.oldMousePos[ 0 ]
            deltaY = worldPos.y - self.oldMousePos[ 1 ]

            if self.pressedButton == QtCore.Qt.LeftButton:
                multiplier = (self.camera.getZoom()/self.farPlane)
                x = -deltaX * multiplier
                y = -deltaY * multiplier
                self.camera.translate(x, y, 0.0)

            elif self.pressedButton == QtCore.Qt.MidButton:
                zoom = self.camera.getZoom() + deltaY * 0.3
                self.camera.setZoom(zoom)

            elif self.pressedButton == QtCore.Qt.RightButton:
                x = deltaY * 0.3
                y = -deltaX * 0.3
                self.camera.addRotation(x, y)

            self.oldMousePos[0], self.oldMousePos[1] = worldPos.x, worldPos.y
            self.updateGL()
 
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



if __name__=='__main__':
    from draw_matrix4 import Matrix4Draw

    QApplication.setColorSpec(QApplication.CustomColor)
    app=QApplication(['GMath in Action!'])

    widget=Viewport()
    widget.show()

    for i in range (-2, 3):
        for j in range (-2, 3):
            m = Matrix4Draw()
            m.mat.translate(Vector3(0, i+i*0.2, j+j*0.2))
            widget.objsToDraw.append( m )
    app.exec_()

