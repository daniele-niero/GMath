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


from vector3 import Vector3

def getPlaneNormal(point1, point2, point3):
    vec1 = Vector3(point1)
    vec2 = Vector3(point2)
    vec3 = Vector3(point3)

    segment1 = vec2.sub(vec1)
    segment2 = vec3.sub(vec2)
    normal = segment2.cross(segment1)
    normal.normalizeInPlace()

    return normal

def mathDomainClamp(value):
    if value < -1.0:
        return -1.0
    elif value > 1.0:
        return 1.0
    else:
        return value