#ifndef UTILITIES_H
#define UTILITIES_H

#include <GL/gl.h>
#include <QDebug>

static void MoCheckOpenGLErrorState(int err, const char *file, int line) {
    if (err) {
        qDebug() << "OpenGL error (" << err << ") at: "
                 << file << "(" << line << ").";
    }
}

#ifdef NDEBUG
#define MO_CHECK_GL_ERROR
#else
#define MO_CHECK_GL_ERROR \
    MoCheckOpenGLErrorState(glGetError(), __FILE__, __LINE__)
#endif

#endif // UTILITIES_H


#define MO_CHECKED_CALL(call, message)         \
    do {                                       \
        if (!(call)) {                         \
            throw std::runtime_error(message); \
        }                                      \
    } while(0)
