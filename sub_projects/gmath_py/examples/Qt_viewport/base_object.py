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