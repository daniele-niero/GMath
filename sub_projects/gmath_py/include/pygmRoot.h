/*
A math library for 3D graphic.
Copyright (C) 2010 Daniele Niero

Author contact: nieroinfo@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef PYGMROOT_H
#define PYGMROOT_H

#include "gmRoot.h"


template <typename GMathType>
void setitem_wrap(GMathType* self, int index, float value)
{
    self->operator[](index) = value;
}

template <typename GMathType>
float getitem_wrap(GMathType* self, int index)
{
    return self->operator[](index);
}


void wrapRoot();

#endif //PYGMROOT_H
