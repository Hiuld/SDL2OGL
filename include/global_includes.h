#ifndef GLOBAL_INCLUDES_H_INCLUDED
#define GLOBAL_INCLUDES_H_INCLUDED

#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>
#include <map>
#include <vector>
#include <list>
#include <cstring>
#include "C3DException.h"

struct CEnums
{
    enum Matrix
    {
        M_PROJECTION = GL_PROJECTION,
        M_MODELVIEW = GL_MODELVIEW,
        M_TEXTURE = GL_TEXTURE
    };

    enum PrimitiveType
    {
        PT_POINT = GL_POINT,
        PT_LINES = GL_LINES,
        PT_LINE_STRIP = GL_LINE_STRIP,
        PT_TRIANGLES = GL_TRIANGLES,
        PT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
        PT_TRIANGLE_FAN = GL_TRIANGLE_FAN,
        PT_QUADS = GL_QUADS,
        PT_QUAD_STRIP = GL_QUAD_STRIP
    };

    enum QuadStyle
    {
        QS_POINT = GLU_POINT,
        QS_LINES = GLU_LINE,
        QS_FILL = GLU_FILL
    };

    enum QuadType
    {
        QT_SPHERE,
        QT_CYLINDER,
        QT_DISK,
        QT_PARTIALDISK
    };
};
#endif // GLOBAL_INCLUDES_H_INCLUDED
