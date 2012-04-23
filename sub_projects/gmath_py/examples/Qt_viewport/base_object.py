import copy
from OpenGL.GL import *
from gmath import Vector3, Matrix4
from numpy import float32


class BaseObject(object):
    _pick_color = [float32(0.0), float32(0.0), float32(0.0)]
 
    def __init__(self):
        increment = float32(1.0)

        BaseObject._pick_color[0]+=increment
        if (BaseObject._pick_color[0] > float32(255.0)):
            BaseObject._pick_color[0] = float32(0.0)
            BaseObject._pick_color[1]+=increment
            if (BaseObject._pick_color[1] > float32(255.0)):
                BaseObject._pick_color[1] = float32(0.0)
                BaseObject._pick_color[2]+=increment

           
        self.__pick_color = (
            float32(BaseObject._pick_color[0]/float32(255.0)), 
            float32(BaseObject._pick_color[1]/float32(255.0)), 
            float32(BaseObject._pick_color[2]/float32(255.0))
            )

        self.color = [0.5, 0.5, 0.5]

    def getPickColor(self):
        return self.__pick_color

    def isPickedColor(self, color):
        return (round(self.__pick_color[0], 6) == round(color[0], 6)) and \
               (round(self.__pick_color[1], 6) == round(color[1], 6)) and \
               (round(self.__pick_color[2], 6) == round(color[2], 6))

    def _draw(self):
        pass

    def draw(self):
        glColor3f(self.color[0], self.color[1], self.color[2])
        self._draw()

    def drawForSelection(self):
        glColor3f(
            self.__pick_color[0],
            self.__pick_color[1],
            self.__pick_color[2] )
        self._draw()

    def drawSelected(self):
        glColor3f(1, 1, 1)
        self._draw()