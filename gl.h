// Copyright 2014 The Azul3D Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
//
// This source file was automatically generated using glwrap.
// +build<no value>

#ifndef H_GLWRAP_OPENGL
#define H_GLWRAP_OPENGL


// OpenGL type definitions
#include <stddef.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLclampx;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;
#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
typedef unsigned short GLhalfARB;
typedef unsigned short GLhalf;
typedef GLint GLfixed;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;
typedef int64_t GLint64EXT;
typedef uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void ( *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void ( *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;



// Define GLAPIENTRY for platforms that need it.
#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif


// Typedefs for each OpenGL pointer function; GLAPIENTRY is required on Windows
// OS (but for other platforms is simply nothing).
typedef void (GLAPIENTRY* PFNGLCULLFACEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLFRONTFACEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLHINTPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLLINEWIDTHPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLPOINTSIZEPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLPOLYGONMODEPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLSCISSORPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERFPROC) (GLenum, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE1DPROC) (GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE2DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLDRAWBUFFERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLCLEARPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLCLEARCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCLEARSTENCILPROC) (GLint);
typedef void (GLAPIENTRY* PFNGLCLEARDEPTHPROC) (GLdouble);
typedef void (GLAPIENTRY* PFNGLSTENCILMASKPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLCOLORMASKPROC) (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (GLAPIENTRY* PFNGLDEPTHMASKPROC) (GLboolean);
typedef void (GLAPIENTRY* PFNGLDISABLEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLENABLEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLFINISHPROC) (void);
typedef void (GLAPIENTRY* PFNGLFLUSHPROC) (void);
typedef void (GLAPIENTRY* PFNGLBLENDFUNCPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLLOGICOPPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLSTENCILFUNCPROC) (GLenum, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLSTENCILOPPROC) (GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLDEPTHFUNCPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLPIXELSTOREFPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLPIXELSTOREIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLREADBUFFERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLREADPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLGETBOOLEANVPROC) (GLenum, GLboolean*);
typedef void (GLAPIENTRY* PFNGLGETDOUBLEVPROC) (GLenum, GLdouble*);
typedef GLenum (GLAPIENTRY* PFNGLGETERRORPROC) (void);
typedef void (GLAPIENTRY* PFNGLGETFLOATVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETINTEGERVPROC) (GLenum, GLint*);
typedef GLubyte* (GLAPIENTRY* PFNGLGETSTRINGPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGETTEXIMAGEPROC) (GLenum, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum, GLint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum, GLint, GLenum, GLint*);
typedef GLboolean (GLAPIENTRY* PFNGLISENABLEDPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLDEPTHRANGEPROC) (GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVIEWPORTPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLNEWLISTPROC) (GLuint, GLenum);
typedef void (GLAPIENTRY* PFNGLENDLISTPROC) (void);
typedef void (GLAPIENTRY* PFNGLCALLLISTPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLCALLLISTSPROC) (GLsizei, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLDELETELISTSPROC) (GLuint, GLsizei);
typedef GLuint (GLAPIENTRY* PFNGLGENLISTSPROC) (GLsizei);
typedef void (GLAPIENTRY* PFNGLLISTBASEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBEGINPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLBITMAPPROC) (GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, GLubyte*);
typedef void (GLAPIENTRY* PFNGLCOLOR3BPROC) (GLbyte, GLbyte, GLbyte);
typedef void (GLAPIENTRY* PFNGLCOLOR3BVPROC) (GLbyte*);
typedef void (GLAPIENTRY* PFNGLCOLOR3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLCOLOR3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLCOLOR3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCOLOR3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLCOLOR3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLCOLOR3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLCOLOR3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLCOLOR3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLCOLOR3UBPROC) (GLubyte, GLubyte, GLubyte);
typedef void (GLAPIENTRY* PFNGLCOLOR3UBVPROC) (GLubyte*);
typedef void (GLAPIENTRY* PFNGLCOLOR3UIPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLCOLOR3UIVPROC) (GLuint*);
typedef void (GLAPIENTRY* PFNGLCOLOR3USPROC) (GLushort, GLushort, GLushort);
typedef void (GLAPIENTRY* PFNGLCOLOR3USVPROC) (GLushort*);
typedef void (GLAPIENTRY* PFNGLCOLOR4BPROC) (GLbyte, GLbyte, GLbyte, GLbyte);
typedef void (GLAPIENTRY* PFNGLCOLOR4BVPROC) (GLbyte*);
typedef void (GLAPIENTRY* PFNGLCOLOR4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLCOLOR4DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLCOLOR4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCOLOR4FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLCOLOR4IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLCOLOR4IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLCOLOR4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLCOLOR4SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLCOLOR4UBPROC) (GLubyte, GLubyte, GLubyte, GLubyte);
typedef void (GLAPIENTRY* PFNGLCOLOR4UBVPROC) (GLubyte*);
typedef void (GLAPIENTRY* PFNGLCOLOR4UIPROC) (GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLCOLOR4UIVPROC) (GLuint*);
typedef void (GLAPIENTRY* PFNGLCOLOR4USPROC) (GLushort, GLushort, GLushort, GLushort);
typedef void (GLAPIENTRY* PFNGLCOLOR4USVPROC) (GLushort*);
typedef void (GLAPIENTRY* PFNGLEDGEFLAGPROC) (GLboolean);
typedef void (GLAPIENTRY* PFNGLEDGEFLAGVPROC) (GLboolean*);
typedef void (GLAPIENTRY* PFNGLENDPROC) (void);
typedef void (GLAPIENTRY* PFNGLINDEXDPROC) (GLdouble);
typedef void (GLAPIENTRY* PFNGLINDEXDVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLINDEXFPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLINDEXFVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLINDEXIPROC) (GLint);
typedef void (GLAPIENTRY* PFNGLINDEXIVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLINDEXSPROC) (GLshort);
typedef void (GLAPIENTRY* PFNGLINDEXSVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLNORMAL3BPROC) (GLbyte, GLbyte, GLbyte);
typedef void (GLAPIENTRY* PFNGLNORMAL3BVPROC) (GLbyte*);
typedef void (GLAPIENTRY* PFNGLNORMAL3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLNORMAL3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLNORMAL3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLNORMAL3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLNORMAL3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLNORMAL3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLNORMAL3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLNORMAL3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2DPROC) (GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2FPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2IPROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2SPROC) (GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLRASTERPOS2SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLRASTERPOS3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLRASTERPOS4SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLRECTDPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLRECTDVPROC) (GLdouble*, GLdouble*);
typedef void (GLAPIENTRY* PFNGLRECTFPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLRECTFVPROC) (GLfloat*, GLfloat*);
typedef void (GLAPIENTRY* PFNGLRECTIPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLRECTIVPROC) (GLint*, GLint*);
typedef void (GLAPIENTRY* PFNGLRECTSPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLRECTSVPROC) (GLshort*, GLshort*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1DPROC) (GLdouble);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1FPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1IPROC) (GLint);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1SPROC) (GLshort);
typedef void (GLAPIENTRY* PFNGLTEXCOORD1SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2DPROC) (GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2FPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2IPROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2SPROC) (GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLTEXCOORD2SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLTEXCOORD3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLTEXCOORD4SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEX2DPROC) (GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEX2DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEX2FPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEX2FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEX2IPROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEX2IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEX2SPROC) (GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEX2SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEX3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEX3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEX3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEX3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEX3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEX3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEX3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEX3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEX4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEX4DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEX4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEX4FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEX4IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEX4IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEX4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEX4SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLCLIPPLANEPROC) (GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLCOLORMATERIALPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLFOGFPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLFOGFVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLFOGIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLFOGIVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLLIGHTFPROC) (GLenum, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLLIGHTFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLLIGHTIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLLIGHTIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLLIGHTMODELFPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLLIGHTMODELFVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLLIGHTMODELIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLLIGHTMODELIVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLLINESTIPPLEPROC) (GLint, GLushort);
typedef void (GLAPIENTRY* PFNGLMATERIALFPROC) (GLenum, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLMATERIALFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMATERIALIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLMATERIALIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLPOLYGONSTIPPLEPROC) (GLubyte*);
typedef void (GLAPIENTRY* PFNGLSHADEMODELPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLTEXENVFPROC) (GLenum, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXENVFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXENVIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLTEXENVIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLTEXGENDPROC) (GLenum, GLenum, GLdouble);
typedef void (GLAPIENTRY* PFNGLTEXGENDVPROC) (GLenum, GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLTEXGENFPROC) (GLenum, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLTEXGENFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLTEXGENIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLTEXGENIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLFEEDBACKBUFFERPROC) (GLsizei, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLSELECTBUFFERPROC) (GLsizei, GLuint*);
typedef GLint (GLAPIENTRY* PFNGLRENDERMODEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLINITNAMESPROC) (void);
typedef void (GLAPIENTRY* PFNGLLOADNAMEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLPASSTHROUGHPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLPOPNAMEPROC) (void);
typedef void (GLAPIENTRY* PFNGLPUSHNAMEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLCLEARACCUMPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCLEARINDEXPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLINDEXMASKPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLACCUMPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLPOPATTRIBPROC) (void);
typedef void (GLAPIENTRY* PFNGLPUSHATTRIBPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLMAP1DPROC) (GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLMAP1FPROC) (GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMAP2DPROC) (GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLMAP2FPROC) (GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMAPGRID1DPROC) (GLint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLMAPGRID1FPROC) (GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLMAPGRID2DPROC) (GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLMAPGRID2FPROC) (GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLEVALCOORD1DPROC) (GLdouble);
typedef void (GLAPIENTRY* PFNGLEVALCOORD1DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLEVALCOORD1FPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLEVALCOORD1FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLEVALCOORD2DPROC) (GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLEVALCOORD2DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLEVALCOORD2FPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLEVALCOORD2FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLEVALMESH1PROC) (GLenum, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLEVALPOINT1PROC) (GLint);
typedef void (GLAPIENTRY* PFNGLEVALMESH2PROC) (GLenum, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLEVALPOINT2PROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLALPHAFUNCPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLPIXELZOOMPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPIXELTRANSFERFPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLPIXELTRANSFERIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLPIXELMAPFVPROC) (GLenum, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPIXELMAPUIVPROC) (GLenum, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPIXELMAPUSVPROC) (GLenum, GLsizei, GLushort*);
typedef void (GLAPIENTRY* PFNGLCOPYPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum);
typedef void (GLAPIENTRY* PFNGLDRAWPIXELSPROC) (GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLGETCLIPPLANEPROC) (GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLGETLIGHTFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETLIGHTIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETMAPDVPROC) (GLenum, GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLGETMAPFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETMAPIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETMATERIALFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETMATERIALIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETPIXELMAPFVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETPIXELMAPUIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETPIXELMAPUSVPROC) (GLenum, GLushort*);
typedef void (GLAPIENTRY* PFNGLGETPOLYGONSTIPPLEPROC) (GLubyte*);
typedef void (GLAPIENTRY* PFNGLGETTEXENVFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETTEXENVIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETTEXGENDVPROC) (GLenum, GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLGETTEXGENFVPROC) (GLenum, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETTEXGENIVPROC) (GLenum, GLenum, GLint*);
typedef GLboolean (GLAPIENTRY* PFNGLISLISTPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLFRUSTUMPROC) (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLLOADIDENTITYPROC) (void);
typedef void (GLAPIENTRY* PFNGLLOADMATRIXFPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLLOADMATRIXDPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLMATRIXMODEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLMULTMATRIXFPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLMULTMATRIXDPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLORTHOPROC) (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLPOPMATRIXPROC) (void);
typedef void (GLAPIENTRY* PFNGLPUSHMATRIXPROC) (void);
typedef void (GLAPIENTRY* PFNGLROTATEDPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLROTATEFPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLSCALEDPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLSCALEFPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLTRANSLATEDPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLTRANSLATEFPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSPROC) (GLenum, GLint, GLsizei);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSPROC) (GLenum, GLsizei, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLGETPOINTERVPROC) (GLenum, void**);
typedef void (GLAPIENTRY* PFNGLPOLYGONOFFSETPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCOPYTEXIMAGE1DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
typedef void (GLAPIENTRY* PFNGLCOPYTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void (GLAPIENTRY* PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei);
typedef void (GLAPIENTRY* PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXSUBIMAGE1DPROC) (GLenum, GLint, GLint, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLBINDTEXTUREPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDELETETEXTURESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENTEXTURESPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISTEXTUREPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLARRAYELEMENTPROC) (GLint);
typedef void (GLAPIENTRY* PFNGLCOLORPOINTERPROC) (GLint, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLDISABLECLIENTSTATEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLEDGEFLAGPOINTERPROC) (GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLENABLECLIENTSTATEPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLINDEXPOINTERPROC) (GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLINTERLEAVEDARRAYSPROC) (GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLNORMALPOINTERPROC) (GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLTEXCOORDPOINTERPROC) (GLint, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLVERTEXPOINTERPROC) (GLint, GLenum, GLsizei, void*);
typedef GLboolean (GLAPIENTRY* PFNGLARETEXTURESRESIDENTPROC) (GLsizei, GLuint*, GLboolean*);
typedef void (GLAPIENTRY* PFNGLPRIORITIZETEXTURESPROC) (GLsizei, GLuint*, GLfloat*);
typedef void (GLAPIENTRY* PFNGLINDEXUBPROC) (GLubyte);
typedef void (GLAPIENTRY* PFNGLINDEXUBVPROC) (GLubyte*);
typedef void (GLAPIENTRY* PFNGLPOPCLIENTATTRIBPROC) (void);
typedef void (GLAPIENTRY* PFNGLPUSHCLIENTATTRIBPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLDRAWRANGEELEMENTSPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE3DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLSAMPLECOVERAGEPROC) (GLfloat, GLboolean);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum, GLint, void*);
typedef void (GLAPIENTRY* PFNGLCLIENTACTIVETEXTUREPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1DPROC) (GLenum, GLdouble);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1DVPROC) (GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1FPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1FVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1IPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1IVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1SPROC) (GLenum, GLshort);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD1SVPROC) (GLenum, GLshort*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2DPROC) (GLenum, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2DVPROC) (GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2FPROC) (GLenum, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2FVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2IPROC) (GLenum, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2IVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2SPROC) (GLenum, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD2SVPROC) (GLenum, GLshort*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3DPROC) (GLenum, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3DVPROC) (GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3FPROC) (GLenum, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3FVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3IPROC) (GLenum, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3IVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3SPROC) (GLenum, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD3SVPROC) (GLenum, GLshort*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4DPROC) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4DVPROC) (GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4FPROC) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4FVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4IPROC) (GLenum, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4IVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4SPROC) (GLenum, GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORD4SVPROC) (GLenum, GLshort*);
typedef void (GLAPIENTRY* PFNGLLOADTRANSPOSEMATRIXFPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLLOADTRANSPOSEMATRIXDPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLMULTTRANSPOSEMATRIXFPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLMULTTRANSPOSEMATRIXDPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLBLENDFUNCSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLMULTIDRAWARRAYSPROC) (GLenum, GLint*, GLsizei*, GLsizei);
typedef void (GLAPIENTRY* PFNGLMULTIDRAWELEMENTSPROC) (GLenum, GLsizei*, GLenum, void**, GLsizei);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERFPROC) (GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERFVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLPOINTPARAMETERIVPROC) (GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLFOGCOORDFPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLFOGCOORDFVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLFOGCOORDDPROC) (GLdouble);
typedef void (GLAPIENTRY* PFNGLFOGCOORDDVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLFOGCOORDPOINTERPROC) (GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3BPROC) (GLbyte, GLbyte, GLbyte);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3BVPROC) (GLbyte*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3UBPROC) (GLubyte, GLubyte, GLubyte);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3UBVPROC) (GLubyte*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3UIPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3UIVPROC) (GLuint*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3USPROC) (GLushort, GLushort, GLushort);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLOR3USVPROC) (GLushort*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLORPOINTERPROC) (GLint, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2DPROC) (GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2FPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2IPROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2SPROC) (GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS2SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3DVPROC) (GLdouble*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3FVPROC) (GLfloat*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3IVPROC) (GLint*);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3SPROC) (GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLWINDOWPOS3SVPROC) (GLshort*);
typedef void (GLAPIENTRY* PFNGLBLENDCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLBLENDEQUATIONPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGENQUERIESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETEQUERIESPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISQUERYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBEGINQUERYPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLENDQUERYPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGETQUERYIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETQUERYOBJECTIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETQUERYOBJECTUIVPROC) (GLuint, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDELETEBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENBUFFERSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISBUFFERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, void*, GLenum);
typedef void (GLAPIENTRY* PFNGLBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, void*);
typedef void (GLAPIENTRY* PFNGLGETBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, void*);
typedef void (GLAPIENTRY* PFNGLMAPBUFFERPROC) (GLenum, GLenum);
typedef GLboolean (GLAPIENTRY* PFNGLUNMAPBUFFERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLGETBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETBUFFERPOINTERVPROC) (GLenum, GLenum, void**);
typedef void (GLAPIENTRY* PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLDRAWBUFFERSPROC) (GLsizei, GLenum*);
typedef void (GLAPIENTRY* PFNGLSTENCILOPSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLSTENCILFUNCSEPARATEPROC) (GLenum, GLenum, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLSTENCILMASKSEPARATEPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLATTACHSHADERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDATTRIBLOCATIONPROC) (GLuint, GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLCOMPILESHADERPROC) (GLuint);
typedef GLuint (GLAPIENTRY* PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (GLAPIENTRY* PFNGLCREATESHADERPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLDELETEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETESHADERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDETACHSHADERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLGETACTIVEATTRIBPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETATTACHEDSHADERSPROC) (GLuint, GLsizei, GLsizei*, GLuint*);
typedef GLint (GLAPIENTRY* PFNGLGETATTRIBLOCATIONPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMINFOLOGPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETSHADERIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSHADERINFOLOGPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETSHADERSOURCEPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLint (GLAPIENTRY* PFNGLGETUNIFORMLOCATIONPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMFVPROC) (GLuint, GLint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMIVPROC) (GLuint, GLint, GLint*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBDVPROC) (GLuint, GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBFVPROC) (GLuint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint, GLenum, void**);
typedef GLboolean (GLAPIENTRY* PFNGLISPROGRAMPROC) (GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISSHADERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLLINKPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLSHADERSOURCEPROC) (GLuint, GLsizei, GLchar**, GLint*);
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM1FPROC) (GLint, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM2FPROC) (GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM3FPROC) (GLint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM4FPROC) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLUNIFORM1IPROC) (GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM2IPROC) (GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM3IPROC) (GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM4IPROC) (GLint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLUNIFORM1FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4FVPROC) (GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORM1IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4IVPROC) (GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVALIDATEPROGRAMPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1DPROC) (GLuint, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1FPROC) (GLuint, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1SPROC) (GLuint, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB1SVPROC) (GLuint, GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2DPROC) (GLuint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2FPROC) (GLuint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2SPROC) (GLuint, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB2SVPROC) (GLuint, GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3DPROC) (GLuint, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3FPROC) (GLuint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3SPROC) (GLuint, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB3SVPROC) (GLuint, GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NBVPROC) (GLuint, GLbyte*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NIVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NSVPROC) (GLuint, GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NUBPROC) (GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NUBVPROC) (GLuint, GLubyte*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NUIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4NUSVPROC) (GLuint, GLushort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4BVPROC) (GLuint, GLbyte*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4DPROC) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4FPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4FVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4IVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4SPROC) (GLuint, GLshort, GLshort, GLshort, GLshort);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4SVPROC) (GLuint, GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4UBVPROC) (GLuint, GLubyte*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4UIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIB4USVPROC) (GLuint, GLushort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBPOINTERPROC) (GLuint, GLint, GLenum, GLboolean, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2X3FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3X2FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2X4FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4X2FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3X4FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4X3FVPROC) (GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLCOLORMASKIPROC) (GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (GLAPIENTRY* PFNGLGETBOOLEANI_VPROC) (GLenum, GLuint, GLboolean*);
typedef void (GLAPIENTRY* PFNGLGETINTEGERI_VPROC) (GLenum, GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLENABLEIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDISABLEIPROC) (GLenum, GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISENABLEDIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERRANGEPROC) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERBASEPROC) (GLenum, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint, GLsizei, GLchar**, GLenum);
typedef void (GLAPIENTRY* PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*);
typedef void (GLAPIENTRY* PFNGLCLAMPCOLORPROC) (GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLBEGINCONDITIONALRENDERPROC) (GLuint, GLenum);
typedef void (GLAPIENTRY* PFNGLENDCONDITIONALRENDERPROC) (void);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint, GLint, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBIIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI1IPROC) (GLuint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI2IPROC) (GLuint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI3IPROC) (GLuint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI1UIPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI2UIPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI3UIPROC) (GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4UIPROC) (GLuint, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI1IVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI2IVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI3IVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4IVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI1UIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI2UIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI3UIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4UIVPROC) (GLuint, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4BVPROC) (GLuint, GLbyte*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4SVPROC) (GLuint, GLshort*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4UBVPROC) (GLuint, GLubyte*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBI4USVPROC) (GLuint, GLushort*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMUIVPROC) (GLuint, GLint, GLuint*);
typedef void (GLAPIENTRY* PFNGLBINDFRAGDATALOCATIONPROC) (GLuint, GLuint, GLchar*);
typedef GLint (GLAPIENTRY* PFNGLGETFRAGDATALOCATIONPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLUNIFORM1UIPROC) (GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM2UIPROC) (GLint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM3UIPROC) (GLint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM4UIPROC) (GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLUNIFORM1UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4UIVPROC) (GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLTEXPARAMETERIUIVPROC) (GLenum, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERIIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETTEXPARAMETERIUIVPROC) (GLenum, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERIVPROC) (GLenum, GLint, GLint*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERUIVPROC) (GLenum, GLint, GLuint*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERFVPROC) (GLenum, GLint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERFIPROC) (GLenum, GLint, GLfloat, GLint);
typedef GLubyte* (GLAPIENTRY* PFNGLGETSTRINGIPROC) (GLenum, GLuint);
typedef GLboolean (GLAPIENTRY* PFNGLISRENDERBUFFERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBINDRENDERBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDELETERENDERBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENRENDERBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLRENDERBUFFERSTORAGEPROC) (GLenum, GLenum, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef GLboolean (GLAPIENTRY* PFNGLISFRAMEBUFFERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBINDFRAMEBUFFERPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENFRAMEBUFFERSPROC) (GLsizei, GLuint*);
typedef GLenum (GLAPIENTRY* PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum, GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum, GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGENERATEMIPMAPPROC) (GLenum);
typedef void (GLAPIENTRY* PFNGLBLITFRAMEBUFFERPROC) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef void (GLAPIENTRY* PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum, GLenum, GLuint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLMAPBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr, GLbitfield);
typedef void (GLAPIENTRY* PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLBINDVERTEXARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETEVERTEXARRAYSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENVERTEXARRAYSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISVERTEXARRAYPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum, GLsizei, GLenum, void*, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXBUFFERPROC) (GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLCOPYBUFFERSUBDATAPROC) (GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMINDICESPROC) (GLuint, GLsizei, GLchar**, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint, GLsizei, GLuint*, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLuint (GLAPIENTRY* PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint, GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum, GLsizei, GLenum, void*, GLint);
typedef void (GLAPIENTRY* PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, void*, GLint);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum, GLsizei, GLenum, void*, GLsizei, GLint);
typedef void (GLAPIENTRY* PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum, GLsizei*, GLenum, void**, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROVOKINGVERTEXPROC) (GLenum);
typedef GLsync (GLAPIENTRY* PFNGLFENCESYNCPROC) (GLenum, GLbitfield);
typedef GLboolean (GLAPIENTRY* PFNGLISSYNCPROC) (GLsync);
typedef void (GLAPIENTRY* PFNGLDELETESYNCPROC) (GLsync);
typedef GLenum (GLAPIENTRY* PFNGLCLIENTWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (GLAPIENTRY* PFNGLWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (GLAPIENTRY* PFNGLGETINTEGER64VPROC) (GLenum, GLint64*);
typedef void (GLAPIENTRY* PFNGLGETSYNCIVPROC) (GLsync, GLenum, GLsizei, GLsizei*, GLint*);
typedef void (GLAPIENTRY* PFNGLGETINTEGER64I_VPROC) (GLenum, GLuint, GLint64*);
typedef void (GLAPIENTRY* PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum, GLenum, GLint64*);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum, GLenum, GLuint, GLint);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (GLAPIENTRY* PFNGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
typedef void (GLAPIENTRY* PFNGLGETMULTISAMPLEFVPROC) (GLenum, GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLSAMPLEMASKIPROC) (GLuint, GLbitfield);
typedef void (GLAPIENTRY* PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) (GLuint, GLuint, GLuint, GLchar*);
typedef GLint (GLAPIENTRY* PFNGLGETFRAGDATAINDEXPROC) (GLuint, GLchar*);
typedef void (GLAPIENTRY* PFNGLGENSAMPLERSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLDELETESAMPLERSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISSAMPLERPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLBINDSAMPLERPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERFPROC) (GLuint, GLenum, GLfloat);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERFVPROC) (GLuint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERIIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint, GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLQUERYCOUNTERPROC) (GLuint, GLenum);
typedef void (GLAPIENTRY* PFNGLGETQUERYOBJECTI64VPROC) (GLuint, GLenum, GLint64*);
typedef void (GLAPIENTRY* PFNGLGETQUERYOBJECTUI64VPROC) (GLuint, GLenum, GLuint64*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBDIVISORPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP1UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP1UIVPROC) (GLuint, GLenum, GLboolean, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP2UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP2UIVPROC) (GLuint, GLenum, GLboolean, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP3UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP3UIVPROC) (GLuint, GLenum, GLboolean, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP4UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBP4UIVPROC) (GLuint, GLenum, GLboolean, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXP2UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXP2UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXP3UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXP3UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLVERTEXP4UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXP4UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP1UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP1UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP2UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP2UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP3UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP3UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP4UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLTEXCOORDP4UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP1UIPROC) (GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP1UIVPROC) (GLenum, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP2UIPROC) (GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP2UIVPROC) (GLenum, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP3UIPROC) (GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP3UIVPROC) (GLenum, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP4UIPROC) (GLenum, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLMULTITEXCOORDP4UIVPROC) (GLenum, GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLNORMALP3UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLNORMALP3UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLCOLORP3UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLCOLORP3UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLCOLORP4UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLCOLORP4UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLORP3UIPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLSECONDARYCOLORP3UIVPROC) (GLenum, GLuint*);
typedef void (GLAPIENTRY* PFNGLMINSAMPLESHADINGPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLBLENDEQUATIONIPROC) (GLuint, GLenum);
typedef void (GLAPIENTRY* PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLBLENDFUNCIPROC) (GLuint, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLBLENDFUNCSEPARATEIPROC) (GLuint, GLenum, GLenum, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSINDIRECTPROC) (GLenum, void*);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLUNIFORM1DPROC) (GLint, GLdouble);
typedef void (GLAPIENTRY* PFNGLUNIFORM2DPROC) (GLint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLUNIFORM3DPROC) (GLint, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLUNIFORM4DPROC) (GLint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLUNIFORM1DVPROC) (GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORM2DVPROC) (GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORM3DVPROC) (GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORM4DVPROC) (GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2X3DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX2X4DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3X2DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3X4DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4X2DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4X3DVPROC) (GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMDVPROC) (GLuint, GLint, GLdouble*);
typedef GLint (GLAPIENTRY* PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) (GLuint, GLenum, GLchar*);
typedef GLuint (GLAPIENTRY* PFNGLGETSUBROUTINEINDEXPROC) (GLuint, GLenum, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) (GLuint, GLenum, GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETACTIVESUBROUTINENAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLUNIFORMSUBROUTINESUIVPROC) (GLenum, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETUNIFORMSUBROUTINEUIVPROC) (GLenum, GLint, GLuint*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMSTAGEIVPROC) (GLuint, GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLPATCHPARAMETERIPROC) (GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLPATCHPARAMETERFVPROC) (GLenum, GLfloat*);
typedef void (GLAPIENTRY* PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISTRANSFORMFEEDBACKPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (GLAPIENTRY* PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (GLAPIENTRY* PFNGLDRAWTRANSFORMFEEDBACKPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) (GLenum, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLBEGINQUERYINDEXEDPROC) (GLenum, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLENDQUERYINDEXEDPROC) (GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLGETQUERYINDEXEDIVPROC) (GLenum, GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (GLAPIENTRY* PFNGLSHADERBINARYPROC) (GLsizei, GLuint*, GLenum, void*, GLsizei);
typedef void (GLAPIENTRY* PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum, GLenum, GLint*, GLint*);
typedef void (GLAPIENTRY* PFNGLDEPTHRANGEFPROC) (GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLCLEARDEPTHFPROC) (GLfloat);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMBINARYPROC) (GLuint, GLsizei, GLsizei*, GLenum*, void*);
typedef void (GLAPIENTRY* PFNGLPROGRAMBINARYPROC) (GLuint, GLenum, void*, GLsizei);
typedef void (GLAPIENTRY* PFNGLPROGRAMPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMSTAGESPROC) (GLuint, GLbitfield, GLuint);
typedef void (GLAPIENTRY* PFNGLACTIVESHADERPROGRAMPROC) (GLuint, GLuint);
typedef GLuint (GLAPIENTRY* PFNGLCREATESHADERPROGRAMVPROC) (GLenum, GLsizei, GLchar**);
typedef void (GLAPIENTRY* PFNGLBINDPROGRAMPIPELINEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLGENPROGRAMPIPELINESPROC) (GLsizei, GLuint*);
typedef GLboolean (GLAPIENTRY* PFNGLISPROGRAMPIPELINEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1IPROC) (GLuint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1FPROC) (GLuint, GLint, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1DPROC) (GLuint, GLint, GLdouble);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1DVPROC) (GLuint, GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1UIPROC) (GLuint, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2IPROC) (GLuint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2FPROC) (GLuint, GLint, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2DPROC) (GLuint, GLint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2DVPROC) (GLuint, GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2UIPROC) (GLuint, GLint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3DPROC) (GLuint, GLint, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3DVPROC) (GLuint, GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4IPROC) (GLuint, GLint, GLint, GLint, GLint, GLint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4IVPROC) (GLuint, GLint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4FVPROC) (GLuint, GLint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4DPROC) (GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4DVPROC) (GLuint, GLint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint, GLint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, GLfloat*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint, GLint, GLsizei, GLboolean, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL1DPROC) (GLuint, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL2DPROC) (GLuint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL3DPROC) (GLuint, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL4DPROC) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL1DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL2DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL3DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBL4DVPROC) (GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint, GLint, GLenum, GLsizei, void*);
typedef void (GLAPIENTRY* PFNGLGETVERTEXATTRIBLDVPROC) (GLuint, GLenum, GLdouble*);
typedef void (GLAPIENTRY* PFNGLVIEWPORTARRAYVPROC) (GLuint, GLsizei, GLfloat*);
typedef void (GLAPIENTRY* PFNGLVIEWPORTINDEXEDFPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAPIENTRY* PFNGLVIEWPORTINDEXEDFVPROC) (GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLSCISSORARRAYVPROC) (GLuint, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLSCISSORINDEXEDPROC) (GLuint, GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLSCISSORINDEXEDVPROC) (GLuint, GLint*);
typedef void (GLAPIENTRY* PFNGLDEPTHRANGEARRAYVPROC) (GLuint, GLsizei, GLdouble*);
typedef void (GLAPIENTRY* PFNGLDEPTHRANGEINDEXEDPROC) (GLuint, GLdouble, GLdouble);
typedef void (GLAPIENTRY* PFNGLGETFLOATI_VPROC) (GLenum, GLuint, GLfloat*);
typedef void (GLAPIENTRY* PFNGLGETDOUBLEI_VPROC) (GLenum, GLuint, GLdouble*);
typedef void (GLAPIENTRY* PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum, GLint, GLsizei, GLsizei, GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum, GLsizei, GLenum, void*, GLsizei, GLuint);
typedef void (GLAPIENTRY* PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum, GLsizei, GLenum, void*, GLsizei, GLint, GLuint);
typedef void (GLAPIENTRY* PFNGLGETINTERNALFORMATIVPROC) (GLenum, GLenum, GLenum, GLsizei, GLint*);
typedef void (GLAPIENTRY* PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint, GLuint, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLBINDIMAGETEXTUREPROC) (GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
typedef void (GLAPIENTRY* PFNGLMEMORYBARRIERPROC) (GLbitfield);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE1DPROC) (GLenum, GLsizei, GLenum, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE2DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE3DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum, GLuint, GLsizei);
typedef void (GLAPIENTRY* PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) (GLenum, GLuint, GLuint, GLsizei);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERDATAPROC) (GLenum, GLenum, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLCLEARBUFFERSUBDATAPROC) (GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLDISPATCHCOMPUTEPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr);
typedef void (GLAPIENTRY* PFNGLCOPYIMAGESUBDATAPROC) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (GLAPIENTRY* PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint*);
typedef void (GLAPIENTRY* PFNGLGETINTERNALFORMATI64VPROC) (GLenum, GLenum, GLenum, GLsizei, GLint64*);
typedef void (GLAPIENTRY* PFNGLINVALIDATETEXSUBIMAGEPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLINVALIDATETEXIMAGEPROC) (GLuint, GLint);
typedef void (GLAPIENTRY* PFNGLINVALIDATEBUFFERSUBDATAPROC) (GLuint, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLINVALIDATEBUFFERDATAPROC) (GLuint);
typedef void (GLAPIENTRY* PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum, GLsizei, GLenum*);
typedef void (GLAPIENTRY* PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum, GLsizei, GLenum*, GLint, GLint, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum, void*, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum, GLenum, void*, GLsizei, GLsizei);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint, GLenum, GLenum, GLint*);
typedef GLuint (GLAPIENTRY* PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint, GLenum, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint, GLenum, GLuint, GLsizei, GLenum*, GLsizei, GLsizei*, GLint*);
typedef GLint (GLAPIENTRY* PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint, GLenum, GLchar*);
typedef GLint (GLAPIENTRY* PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint, GLenum, GLchar*);
typedef void (GLAPIENTRY* PFNGLSHADERSTORAGEBLOCKBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLTEXBUFFERRANGEPROC) (GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (GLAPIENTRY* PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
typedef void (GLAPIENTRY* PFNGLTEXTUREVIEWPROC) (GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLBINDVERTEXBUFFERPROC) (GLuint, GLuint, GLintptr, GLsizei);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBFORMATPROC) (GLuint, GLint, GLenum, GLboolean, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBIFORMATPROC) (GLuint, GLint, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBLFORMATPROC) (GLuint, GLint, GLenum, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBBINDINGPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLVERTEXBINDINGDIVISORPROC) (GLuint, GLuint);
typedef void (GLAPIENTRY* PFNGLDEBUGMESSAGECONTROLPROC) (GLenum, GLenum, GLenum, GLsizei, GLuint*, GLboolean);
typedef void (GLAPIENTRY* PFNGLDEBUGMESSAGEINSERTPROC) (GLenum, GLenum, GLuint, GLenum, GLsizei, GLchar*);
typedef void (GLAPIENTRY* PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC, void*);
typedef GLuint (GLAPIENTRY* PFNGLGETDEBUGMESSAGELOGPROC) (GLuint, GLsizei, GLenum*, GLenum*, GLuint*, GLenum*, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLPUSHDEBUGGROUPPROC) (GLenum, GLuint, GLsizei, GLchar*);
typedef void (GLAPIENTRY* PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (GLAPIENTRY* PFNGLOBJECTLABELPROC) (GLenum, GLuint, GLsizei, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETOBJECTLABELPROC) (GLenum, GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLOBJECTPTRLABELPROC) (void*, GLsizei, GLchar*);
typedef void (GLAPIENTRY* PFNGLGETOBJECTPTRLABELPROC) (void*, GLsizei, GLsizei*, GLchar*);
typedef void (GLAPIENTRY* PFNGLBUFFERSTORAGEPROC) (GLenum, GLsizeiptr, void*, GLbitfield);
typedef void (GLAPIENTRY* PFNGLCLEARTEXIMAGEPROC) (GLuint, GLint, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLCLEARTEXSUBIMAGEPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, void*);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERSBASEPROC) (GLenum, GLuint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLBINDBUFFERSRANGEPROC) (GLenum, GLuint, GLsizei, GLuint*, GLintptr*, GLsizeiptr*);
typedef void (GLAPIENTRY* PFNGLBINDTEXTURESPROC) (GLuint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLBINDSAMPLERSPROC) (GLuint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLBINDIMAGETEXTURESPROC) (GLuint, GLsizei, GLuint*);
typedef void (GLAPIENTRY* PFNGLBINDVERTEXBUFFERSPROC) (GLuint, GLsizei, GLuint*, GLintptr*, GLsizei*);


// gl_wrap_context holds the loaded function pointers for a given OpenGL
// context. Pointers are lazily-loaded upon first invocation of each function.
// through their appropriate gl_wrap_context_glFunction() counterparts.
typedef struct {
	PFNGLCULLFACEPROC glCullFaceProc;
	PFNGLFRONTFACEPROC glFrontFaceProc;
	PFNGLHINTPROC glHintProc;
	PFNGLLINEWIDTHPROC glLineWidthProc;
	PFNGLPOINTSIZEPROC glPointSizeProc;
	PFNGLPOLYGONMODEPROC glPolygonModeProc;
	PFNGLSCISSORPROC glScissorProc;
	PFNGLTEXPARAMETERFPROC glTexParameterfProc;
	PFNGLTEXPARAMETERFVPROC glTexParameterfvProc;
	PFNGLTEXPARAMETERIPROC glTexParameteriProc;
	PFNGLTEXPARAMETERIVPROC glTexParameterivProc;
	PFNGLTEXIMAGE1DPROC glTexImage1DProc;
	PFNGLTEXIMAGE2DPROC glTexImage2DProc;
	PFNGLDRAWBUFFERPROC glDrawBufferProc;
	PFNGLCLEARPROC glClearProc;
	PFNGLCLEARCOLORPROC glClearColorProc;
	PFNGLCLEARSTENCILPROC glClearStencilProc;
	PFNGLCLEARDEPTHPROC glClearDepthProc;
	PFNGLSTENCILMASKPROC glStencilMaskProc;
	PFNGLCOLORMASKPROC glColorMaskProc;
	PFNGLDEPTHMASKPROC glDepthMaskProc;
	PFNGLDISABLEPROC glDisableProc;
	PFNGLENABLEPROC glEnableProc;
	PFNGLFINISHPROC glFinishProc;
	PFNGLFLUSHPROC glFlushProc;
	PFNGLBLENDFUNCPROC glBlendFuncProc;
	PFNGLLOGICOPPROC glLogicOpProc;
	PFNGLSTENCILFUNCPROC glStencilFuncProc;
	PFNGLSTENCILOPPROC glStencilOpProc;
	PFNGLDEPTHFUNCPROC glDepthFuncProc;
	PFNGLPIXELSTOREFPROC glPixelStorefProc;
	PFNGLPIXELSTOREIPROC glPixelStoreiProc;
	PFNGLREADBUFFERPROC glReadBufferProc;
	PFNGLREADPIXELSPROC glReadPixelsProc;
	PFNGLGETBOOLEANVPROC glGetBooleanvProc;
	PFNGLGETDOUBLEVPROC glGetDoublevProc;
	PFNGLGETERRORPROC glGetErrorProc;
	PFNGLGETFLOATVPROC glGetFloatvProc;
	PFNGLGETINTEGERVPROC glGetIntegervProc;
	PFNGLGETSTRINGPROC glGetStringProc;
	PFNGLGETTEXIMAGEPROC glGetTexImageProc;
	PFNGLGETTEXPARAMETERFVPROC glGetTexParameterfvProc;
	PFNGLGETTEXPARAMETERIVPROC glGetTexParameterivProc;
	PFNGLGETTEXLEVELPARAMETERFVPROC glGetTexLevelParameterfvProc;
	PFNGLGETTEXLEVELPARAMETERIVPROC glGetTexLevelParameterivProc;
	PFNGLISENABLEDPROC glIsEnabledProc;
	PFNGLDEPTHRANGEPROC glDepthRangeProc;
	PFNGLVIEWPORTPROC glViewportProc;
	PFNGLNEWLISTPROC glNewListProc;
	PFNGLENDLISTPROC glEndListProc;
	PFNGLCALLLISTPROC glCallListProc;
	PFNGLCALLLISTSPROC glCallListsProc;
	PFNGLDELETELISTSPROC glDeleteListsProc;
	PFNGLGENLISTSPROC glGenListsProc;
	PFNGLLISTBASEPROC glListBaseProc;
	PFNGLBEGINPROC glBeginProc;
	PFNGLBITMAPPROC glBitmapProc;
	PFNGLCOLOR3BPROC glColor3bProc;
	PFNGLCOLOR3BVPROC glColor3bvProc;
	PFNGLCOLOR3DPROC glColor3dProc;
	PFNGLCOLOR3DVPROC glColor3dvProc;
	PFNGLCOLOR3FPROC glColor3fProc;
	PFNGLCOLOR3FVPROC glColor3fvProc;
	PFNGLCOLOR3IPROC glColor3iProc;
	PFNGLCOLOR3IVPROC glColor3ivProc;
	PFNGLCOLOR3SPROC glColor3sProc;
	PFNGLCOLOR3SVPROC glColor3svProc;
	PFNGLCOLOR3UBPROC glColor3ubProc;
	PFNGLCOLOR3UBVPROC glColor3ubvProc;
	PFNGLCOLOR3UIPROC glColor3uiProc;
	PFNGLCOLOR3UIVPROC glColor3uivProc;
	PFNGLCOLOR3USPROC glColor3usProc;
	PFNGLCOLOR3USVPROC glColor3usvProc;
	PFNGLCOLOR4BPROC glColor4bProc;
	PFNGLCOLOR4BVPROC glColor4bvProc;
	PFNGLCOLOR4DPROC glColor4dProc;
	PFNGLCOLOR4DVPROC glColor4dvProc;
	PFNGLCOLOR4FPROC glColor4fProc;
	PFNGLCOLOR4FVPROC glColor4fvProc;
	PFNGLCOLOR4IPROC glColor4iProc;
	PFNGLCOLOR4IVPROC glColor4ivProc;
	PFNGLCOLOR4SPROC glColor4sProc;
	PFNGLCOLOR4SVPROC glColor4svProc;
	PFNGLCOLOR4UBPROC glColor4ubProc;
	PFNGLCOLOR4UBVPROC glColor4ubvProc;
	PFNGLCOLOR4UIPROC glColor4uiProc;
	PFNGLCOLOR4UIVPROC glColor4uivProc;
	PFNGLCOLOR4USPROC glColor4usProc;
	PFNGLCOLOR4USVPROC glColor4usvProc;
	PFNGLEDGEFLAGPROC glEdgeFlagProc;
	PFNGLEDGEFLAGVPROC glEdgeFlagvProc;
	PFNGLENDPROC glEndProc;
	PFNGLINDEXDPROC glIndexdProc;
	PFNGLINDEXDVPROC glIndexdvProc;
	PFNGLINDEXFPROC glIndexfProc;
	PFNGLINDEXFVPROC glIndexfvProc;
	PFNGLINDEXIPROC glIndexiProc;
	PFNGLINDEXIVPROC glIndexivProc;
	PFNGLINDEXSPROC glIndexsProc;
	PFNGLINDEXSVPROC glIndexsvProc;
	PFNGLNORMAL3BPROC glNormal3bProc;
	PFNGLNORMAL3BVPROC glNormal3bvProc;
	PFNGLNORMAL3DPROC glNormal3dProc;
	PFNGLNORMAL3DVPROC glNormal3dvProc;
	PFNGLNORMAL3FPROC glNormal3fProc;
	PFNGLNORMAL3FVPROC glNormal3fvProc;
	PFNGLNORMAL3IPROC glNormal3iProc;
	PFNGLNORMAL3IVPROC glNormal3ivProc;
	PFNGLNORMAL3SPROC glNormal3sProc;
	PFNGLNORMAL3SVPROC glNormal3svProc;
	PFNGLRASTERPOS2DPROC glRasterPos2dProc;
	PFNGLRASTERPOS2DVPROC glRasterPos2dvProc;
	PFNGLRASTERPOS2FPROC glRasterPos2fProc;
	PFNGLRASTERPOS2FVPROC glRasterPos2fvProc;
	PFNGLRASTERPOS2IPROC glRasterPos2iProc;
	PFNGLRASTERPOS2IVPROC glRasterPos2ivProc;
	PFNGLRASTERPOS2SPROC glRasterPos2sProc;
	PFNGLRASTERPOS2SVPROC glRasterPos2svProc;
	PFNGLRASTERPOS3DPROC glRasterPos3dProc;
	PFNGLRASTERPOS3DVPROC glRasterPos3dvProc;
	PFNGLRASTERPOS3FPROC glRasterPos3fProc;
	PFNGLRASTERPOS3FVPROC glRasterPos3fvProc;
	PFNGLRASTERPOS3IPROC glRasterPos3iProc;
	PFNGLRASTERPOS3IVPROC glRasterPos3ivProc;
	PFNGLRASTERPOS3SPROC glRasterPos3sProc;
	PFNGLRASTERPOS3SVPROC glRasterPos3svProc;
	PFNGLRASTERPOS4DPROC glRasterPos4dProc;
	PFNGLRASTERPOS4DVPROC glRasterPos4dvProc;
	PFNGLRASTERPOS4FPROC glRasterPos4fProc;
	PFNGLRASTERPOS4FVPROC glRasterPos4fvProc;
	PFNGLRASTERPOS4IPROC glRasterPos4iProc;
	PFNGLRASTERPOS4IVPROC glRasterPos4ivProc;
	PFNGLRASTERPOS4SPROC glRasterPos4sProc;
	PFNGLRASTERPOS4SVPROC glRasterPos4svProc;
	PFNGLRECTDPROC glRectdProc;
	PFNGLRECTDVPROC glRectdvProc;
	PFNGLRECTFPROC glRectfProc;
	PFNGLRECTFVPROC glRectfvProc;
	PFNGLRECTIPROC glRectiProc;
	PFNGLRECTIVPROC glRectivProc;
	PFNGLRECTSPROC glRectsProc;
	PFNGLRECTSVPROC glRectsvProc;
	PFNGLTEXCOORD1DPROC glTexCoord1dProc;
	PFNGLTEXCOORD1DVPROC glTexCoord1dvProc;
	PFNGLTEXCOORD1FPROC glTexCoord1fProc;
	PFNGLTEXCOORD1FVPROC glTexCoord1fvProc;
	PFNGLTEXCOORD1IPROC glTexCoord1iProc;
	PFNGLTEXCOORD1IVPROC glTexCoord1ivProc;
	PFNGLTEXCOORD1SPROC glTexCoord1sProc;
	PFNGLTEXCOORD1SVPROC glTexCoord1svProc;
	PFNGLTEXCOORD2DPROC glTexCoord2dProc;
	PFNGLTEXCOORD2DVPROC glTexCoord2dvProc;
	PFNGLTEXCOORD2FPROC glTexCoord2fProc;
	PFNGLTEXCOORD2FVPROC glTexCoord2fvProc;
	PFNGLTEXCOORD2IPROC glTexCoord2iProc;
	PFNGLTEXCOORD2IVPROC glTexCoord2ivProc;
	PFNGLTEXCOORD2SPROC glTexCoord2sProc;
	PFNGLTEXCOORD2SVPROC glTexCoord2svProc;
	PFNGLTEXCOORD3DPROC glTexCoord3dProc;
	PFNGLTEXCOORD3DVPROC glTexCoord3dvProc;
	PFNGLTEXCOORD3FPROC glTexCoord3fProc;
	PFNGLTEXCOORD3FVPROC glTexCoord3fvProc;
	PFNGLTEXCOORD3IPROC glTexCoord3iProc;
	PFNGLTEXCOORD3IVPROC glTexCoord3ivProc;
	PFNGLTEXCOORD3SPROC glTexCoord3sProc;
	PFNGLTEXCOORD3SVPROC glTexCoord3svProc;
	PFNGLTEXCOORD4DPROC glTexCoord4dProc;
	PFNGLTEXCOORD4DVPROC glTexCoord4dvProc;
	PFNGLTEXCOORD4FPROC glTexCoord4fProc;
	PFNGLTEXCOORD4FVPROC glTexCoord4fvProc;
	PFNGLTEXCOORD4IPROC glTexCoord4iProc;
	PFNGLTEXCOORD4IVPROC glTexCoord4ivProc;
	PFNGLTEXCOORD4SPROC glTexCoord4sProc;
	PFNGLTEXCOORD4SVPROC glTexCoord4svProc;
	PFNGLVERTEX2DPROC glVertex2dProc;
	PFNGLVERTEX2DVPROC glVertex2dvProc;
	PFNGLVERTEX2FPROC glVertex2fProc;
	PFNGLVERTEX2FVPROC glVertex2fvProc;
	PFNGLVERTEX2IPROC glVertex2iProc;
	PFNGLVERTEX2IVPROC glVertex2ivProc;
	PFNGLVERTEX2SPROC glVertex2sProc;
	PFNGLVERTEX2SVPROC glVertex2svProc;
	PFNGLVERTEX3DPROC glVertex3dProc;
	PFNGLVERTEX3DVPROC glVertex3dvProc;
	PFNGLVERTEX3FPROC glVertex3fProc;
	PFNGLVERTEX3FVPROC glVertex3fvProc;
	PFNGLVERTEX3IPROC glVertex3iProc;
	PFNGLVERTEX3IVPROC glVertex3ivProc;
	PFNGLVERTEX3SPROC glVertex3sProc;
	PFNGLVERTEX3SVPROC glVertex3svProc;
	PFNGLVERTEX4DPROC glVertex4dProc;
	PFNGLVERTEX4DVPROC glVertex4dvProc;
	PFNGLVERTEX4FPROC glVertex4fProc;
	PFNGLVERTEX4FVPROC glVertex4fvProc;
	PFNGLVERTEX4IPROC glVertex4iProc;
	PFNGLVERTEX4IVPROC glVertex4ivProc;
	PFNGLVERTEX4SPROC glVertex4sProc;
	PFNGLVERTEX4SVPROC glVertex4svProc;
	PFNGLCLIPPLANEPROC glClipPlaneProc;
	PFNGLCOLORMATERIALPROC glColorMaterialProc;
	PFNGLFOGFPROC glFogfProc;
	PFNGLFOGFVPROC glFogfvProc;
	PFNGLFOGIPROC glFogiProc;
	PFNGLFOGIVPROC glFogivProc;
	PFNGLLIGHTFPROC glLightfProc;
	PFNGLLIGHTFVPROC glLightfvProc;
	PFNGLLIGHTIPROC glLightiProc;
	PFNGLLIGHTIVPROC glLightivProc;
	PFNGLLIGHTMODELFPROC glLightModelfProc;
	PFNGLLIGHTMODELFVPROC glLightModelfvProc;
	PFNGLLIGHTMODELIPROC glLightModeliProc;
	PFNGLLIGHTMODELIVPROC glLightModelivProc;
	PFNGLLINESTIPPLEPROC glLineStippleProc;
	PFNGLMATERIALFPROC glMaterialfProc;
	PFNGLMATERIALFVPROC glMaterialfvProc;
	PFNGLMATERIALIPROC glMaterialiProc;
	PFNGLMATERIALIVPROC glMaterialivProc;
	PFNGLPOLYGONSTIPPLEPROC glPolygonStippleProc;
	PFNGLSHADEMODELPROC glShadeModelProc;
	PFNGLTEXENVFPROC glTexEnvfProc;
	PFNGLTEXENVFVPROC glTexEnvfvProc;
	PFNGLTEXENVIPROC glTexEnviProc;
	PFNGLTEXENVIVPROC glTexEnvivProc;
	PFNGLTEXGENDPROC glTexGendProc;
	PFNGLTEXGENDVPROC glTexGendvProc;
	PFNGLTEXGENFPROC glTexGenfProc;
	PFNGLTEXGENFVPROC glTexGenfvProc;
	PFNGLTEXGENIPROC glTexGeniProc;
	PFNGLTEXGENIVPROC glTexGenivProc;
	PFNGLFEEDBACKBUFFERPROC glFeedbackBufferProc;
	PFNGLSELECTBUFFERPROC glSelectBufferProc;
	PFNGLRENDERMODEPROC glRenderModeProc;
	PFNGLINITNAMESPROC glInitNamesProc;
	PFNGLLOADNAMEPROC glLoadNameProc;
	PFNGLPASSTHROUGHPROC glPassThroughProc;
	PFNGLPOPNAMEPROC glPopNameProc;
	PFNGLPUSHNAMEPROC glPushNameProc;
	PFNGLCLEARACCUMPROC glClearAccumProc;
	PFNGLCLEARINDEXPROC glClearIndexProc;
	PFNGLINDEXMASKPROC glIndexMaskProc;
	PFNGLACCUMPROC glAccumProc;
	PFNGLPOPATTRIBPROC glPopAttribProc;
	PFNGLPUSHATTRIBPROC glPushAttribProc;
	PFNGLMAP1DPROC glMap1dProc;
	PFNGLMAP1FPROC glMap1fProc;
	PFNGLMAP2DPROC glMap2dProc;
	PFNGLMAP2FPROC glMap2fProc;
	PFNGLMAPGRID1DPROC glMapGrid1dProc;
	PFNGLMAPGRID1FPROC glMapGrid1fProc;
	PFNGLMAPGRID2DPROC glMapGrid2dProc;
	PFNGLMAPGRID2FPROC glMapGrid2fProc;
	PFNGLEVALCOORD1DPROC glEvalCoord1dProc;
	PFNGLEVALCOORD1DVPROC glEvalCoord1dvProc;
	PFNGLEVALCOORD1FPROC glEvalCoord1fProc;
	PFNGLEVALCOORD1FVPROC glEvalCoord1fvProc;
	PFNGLEVALCOORD2DPROC glEvalCoord2dProc;
	PFNGLEVALCOORD2DVPROC glEvalCoord2dvProc;
	PFNGLEVALCOORD2FPROC glEvalCoord2fProc;
	PFNGLEVALCOORD2FVPROC glEvalCoord2fvProc;
	PFNGLEVALMESH1PROC glEvalMesh1Proc;
	PFNGLEVALPOINT1PROC glEvalPoint1Proc;
	PFNGLEVALMESH2PROC glEvalMesh2Proc;
	PFNGLEVALPOINT2PROC glEvalPoint2Proc;
	PFNGLALPHAFUNCPROC glAlphaFuncProc;
	PFNGLPIXELZOOMPROC glPixelZoomProc;
	PFNGLPIXELTRANSFERFPROC glPixelTransferfProc;
	PFNGLPIXELTRANSFERIPROC glPixelTransferiProc;
	PFNGLPIXELMAPFVPROC glPixelMapfvProc;
	PFNGLPIXELMAPUIVPROC glPixelMapuivProc;
	PFNGLPIXELMAPUSVPROC glPixelMapusvProc;
	PFNGLCOPYPIXELSPROC glCopyPixelsProc;
	PFNGLDRAWPIXELSPROC glDrawPixelsProc;
	PFNGLGETCLIPPLANEPROC glGetClipPlaneProc;
	PFNGLGETLIGHTFVPROC glGetLightfvProc;
	PFNGLGETLIGHTIVPROC glGetLightivProc;
	PFNGLGETMAPDVPROC glGetMapdvProc;
	PFNGLGETMAPFVPROC glGetMapfvProc;
	PFNGLGETMAPIVPROC glGetMapivProc;
	PFNGLGETMATERIALFVPROC glGetMaterialfvProc;
	PFNGLGETMATERIALIVPROC glGetMaterialivProc;
	PFNGLGETPIXELMAPFVPROC glGetPixelMapfvProc;
	PFNGLGETPIXELMAPUIVPROC glGetPixelMapuivProc;
	PFNGLGETPIXELMAPUSVPROC glGetPixelMapusvProc;
	PFNGLGETPOLYGONSTIPPLEPROC glGetPolygonStippleProc;
	PFNGLGETTEXENVFVPROC glGetTexEnvfvProc;
	PFNGLGETTEXENVIVPROC glGetTexEnvivProc;
	PFNGLGETTEXGENDVPROC glGetTexGendvProc;
	PFNGLGETTEXGENFVPROC glGetTexGenfvProc;
	PFNGLGETTEXGENIVPROC glGetTexGenivProc;
	PFNGLISLISTPROC glIsListProc;
	PFNGLFRUSTUMPROC glFrustumProc;
	PFNGLLOADIDENTITYPROC glLoadIdentityProc;
	PFNGLLOADMATRIXFPROC glLoadMatrixfProc;
	PFNGLLOADMATRIXDPROC glLoadMatrixdProc;
	PFNGLMATRIXMODEPROC glMatrixModeProc;
	PFNGLMULTMATRIXFPROC glMultMatrixfProc;
	PFNGLMULTMATRIXDPROC glMultMatrixdProc;
	PFNGLORTHOPROC glOrthoProc;
	PFNGLPOPMATRIXPROC glPopMatrixProc;
	PFNGLPUSHMATRIXPROC glPushMatrixProc;
	PFNGLROTATEDPROC glRotatedProc;
	PFNGLROTATEFPROC glRotatefProc;
	PFNGLSCALEDPROC glScaledProc;
	PFNGLSCALEFPROC glScalefProc;
	PFNGLTRANSLATEDPROC glTranslatedProc;
	PFNGLTRANSLATEFPROC glTranslatefProc;
	PFNGLDRAWARRAYSPROC glDrawArraysProc;
	PFNGLDRAWELEMENTSPROC glDrawElementsProc;
	PFNGLGETPOINTERVPROC glGetPointervProc;
	PFNGLPOLYGONOFFSETPROC glPolygonOffsetProc;
	PFNGLCOPYTEXIMAGE1DPROC glCopyTexImage1DProc;
	PFNGLCOPYTEXIMAGE2DPROC glCopyTexImage2DProc;
	PFNGLCOPYTEXSUBIMAGE1DPROC glCopyTexSubImage1DProc;
	PFNGLCOPYTEXSUBIMAGE2DPROC glCopyTexSubImage2DProc;
	PFNGLTEXSUBIMAGE1DPROC glTexSubImage1DProc;
	PFNGLTEXSUBIMAGE2DPROC glTexSubImage2DProc;
	PFNGLBINDTEXTUREPROC glBindTextureProc;
	PFNGLDELETETEXTURESPROC glDeleteTexturesProc;
	PFNGLGENTEXTURESPROC glGenTexturesProc;
	PFNGLISTEXTUREPROC glIsTextureProc;
	PFNGLARRAYELEMENTPROC glArrayElementProc;
	PFNGLCOLORPOINTERPROC glColorPointerProc;
	PFNGLDISABLECLIENTSTATEPROC glDisableClientStateProc;
	PFNGLEDGEFLAGPOINTERPROC glEdgeFlagPointerProc;
	PFNGLENABLECLIENTSTATEPROC glEnableClientStateProc;
	PFNGLINDEXPOINTERPROC glIndexPointerProc;
	PFNGLINTERLEAVEDARRAYSPROC glInterleavedArraysProc;
	PFNGLNORMALPOINTERPROC glNormalPointerProc;
	PFNGLTEXCOORDPOINTERPROC glTexCoordPointerProc;
	PFNGLVERTEXPOINTERPROC glVertexPointerProc;
	PFNGLARETEXTURESRESIDENTPROC glAreTexturesResidentProc;
	PFNGLPRIORITIZETEXTURESPROC glPrioritizeTexturesProc;
	PFNGLINDEXUBPROC glIndexubProc;
	PFNGLINDEXUBVPROC glIndexubvProc;
	PFNGLPOPCLIENTATTRIBPROC glPopClientAttribProc;
	PFNGLPUSHCLIENTATTRIBPROC glPushClientAttribProc;
	PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElementsProc;
	PFNGLTEXIMAGE3DPROC glTexImage3DProc;
	PFNGLTEXSUBIMAGE3DPROC glTexSubImage3DProc;
	PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3DProc;
	PFNGLACTIVETEXTUREPROC glActiveTextureProc;
	PFNGLSAMPLECOVERAGEPROC glSampleCoverageProc;
	PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3DProc;
	PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2DProc;
	PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1DProc;
	PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3DProc;
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2DProc;
	PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1DProc;
	PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImageProc;
	PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTextureProc;
	PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1dProc;
	PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dvProc;
	PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1fProc;
	PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fvProc;
	PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1iProc;
	PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1ivProc;
	PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1sProc;
	PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1svProc;
	PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2dProc;
	PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dvProc;
	PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2fProc;
	PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fvProc;
	PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2iProc;
	PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2ivProc;
	PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2sProc;
	PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2svProc;
	PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3dProc;
	PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dvProc;
	PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3fProc;
	PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fvProc;
	PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3iProc;
	PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3ivProc;
	PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3sProc;
	PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3svProc;
	PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4dProc;
	PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dvProc;
	PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4fProc;
	PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fvProc;
	PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4iProc;
	PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4ivProc;
	PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4sProc;
	PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4svProc;
	PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixfProc;
	PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixdProc;
	PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixfProc;
	PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixdProc;
	PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparateProc;
	PFNGLMULTIDRAWARRAYSPROC glMultiDrawArraysProc;
	PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElementsProc;
	PFNGLPOINTPARAMETERFPROC glPointParameterfProc;
	PFNGLPOINTPARAMETERFVPROC glPointParameterfvProc;
	PFNGLPOINTPARAMETERIPROC glPointParameteriProc;
	PFNGLPOINTPARAMETERIVPROC glPointParameterivProc;
	PFNGLFOGCOORDFPROC glFogCoordfProc;
	PFNGLFOGCOORDFVPROC glFogCoordfvProc;
	PFNGLFOGCOORDDPROC glFogCoorddProc;
	PFNGLFOGCOORDDVPROC glFogCoorddvProc;
	PFNGLFOGCOORDPOINTERPROC glFogCoordPointerProc;
	PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3bProc;
	PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bvProc;
	PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3dProc;
	PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dvProc;
	PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3fProc;
	PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fvProc;
	PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3iProc;
	PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3ivProc;
	PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3sProc;
	PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3svProc;
	PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ubProc;
	PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubvProc;
	PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3uiProc;
	PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uivProc;
	PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3usProc;
	PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usvProc;
	PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointerProc;
	PFNGLWINDOWPOS2DPROC glWindowPos2dProc;
	PFNGLWINDOWPOS2DVPROC glWindowPos2dvProc;
	PFNGLWINDOWPOS2FPROC glWindowPos2fProc;
	PFNGLWINDOWPOS2FVPROC glWindowPos2fvProc;
	PFNGLWINDOWPOS2IPROC glWindowPos2iProc;
	PFNGLWINDOWPOS2IVPROC glWindowPos2ivProc;
	PFNGLWINDOWPOS2SPROC glWindowPos2sProc;
	PFNGLWINDOWPOS2SVPROC glWindowPos2svProc;
	PFNGLWINDOWPOS3DPROC glWindowPos3dProc;
	PFNGLWINDOWPOS3DVPROC glWindowPos3dvProc;
	PFNGLWINDOWPOS3FPROC glWindowPos3fProc;
	PFNGLWINDOWPOS3FVPROC glWindowPos3fvProc;
	PFNGLWINDOWPOS3IPROC glWindowPos3iProc;
	PFNGLWINDOWPOS3IVPROC glWindowPos3ivProc;
	PFNGLWINDOWPOS3SPROC glWindowPos3sProc;
	PFNGLWINDOWPOS3SVPROC glWindowPos3svProc;
	PFNGLBLENDCOLORPROC glBlendColorProc;
	PFNGLBLENDEQUATIONPROC glBlendEquationProc;
	PFNGLGENQUERIESPROC glGenQueriesProc;
	PFNGLDELETEQUERIESPROC glDeleteQueriesProc;
	PFNGLISQUERYPROC glIsQueryProc;
	PFNGLBEGINQUERYPROC glBeginQueryProc;
	PFNGLENDQUERYPROC glEndQueryProc;
	PFNGLGETQUERYIVPROC glGetQueryivProc;
	PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectivProc;
	PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuivProc;
	PFNGLBINDBUFFERPROC glBindBufferProc;
	PFNGLDELETEBUFFERSPROC glDeleteBuffersProc;
	PFNGLGENBUFFERSPROC glGenBuffersProc;
	PFNGLISBUFFERPROC glIsBufferProc;
	PFNGLBUFFERDATAPROC glBufferDataProc;
	PFNGLBUFFERSUBDATAPROC glBufferSubDataProc;
	PFNGLGETBUFFERSUBDATAPROC glGetBufferSubDataProc;
	PFNGLMAPBUFFERPROC glMapBufferProc;
	PFNGLUNMAPBUFFERPROC glUnmapBufferProc;
	PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameterivProc;
	PFNGLGETBUFFERPOINTERVPROC glGetBufferPointervProc;
	PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparateProc;
	PFNGLDRAWBUFFERSPROC glDrawBuffersProc;
	PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparateProc;
	PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparateProc;
	PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparateProc;
	PFNGLATTACHSHADERPROC glAttachShaderProc;
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocationProc;
	PFNGLCOMPILESHADERPROC glCompileShaderProc;
	PFNGLCREATEPROGRAMPROC glCreateProgramProc;
	PFNGLCREATESHADERPROC glCreateShaderProc;
	PFNGLDELETEPROGRAMPROC glDeleteProgramProc;
	PFNGLDELETESHADERPROC glDeleteShaderProc;
	PFNGLDETACHSHADERPROC glDetachShaderProc;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArrayProc;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArrayProc;
	PFNGLGETACTIVEATTRIBPROC glGetActiveAttribProc;
	PFNGLGETACTIVEUNIFORMPROC glGetActiveUniformProc;
	PFNGLGETATTACHEDSHADERSPROC glGetAttachedShadersProc;
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocationProc;
	PFNGLGETPROGRAMIVPROC glGetProgramivProc;
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLogProc;
	PFNGLGETSHADERIVPROC glGetShaderivProc;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLogProc;
	PFNGLGETSHADERSOURCEPROC glGetShaderSourceProc;
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocationProc;
	PFNGLGETUNIFORMFVPROC glGetUniformfvProc;
	PFNGLGETUNIFORMIVPROC glGetUniformivProc;
	PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdvProc;
	PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfvProc;
	PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribivProc;
	PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointervProc;
	PFNGLISPROGRAMPROC glIsProgramProc;
	PFNGLISSHADERPROC glIsShaderProc;
	PFNGLLINKPROGRAMPROC glLinkProgramProc;
	PFNGLSHADERSOURCEPROC glShaderSourceProc;
	PFNGLUSEPROGRAMPROC glUseProgramProc;
	PFNGLUNIFORM1FPROC glUniform1fProc;
	PFNGLUNIFORM2FPROC glUniform2fProc;
	PFNGLUNIFORM3FPROC glUniform3fProc;
	PFNGLUNIFORM4FPROC glUniform4fProc;
	PFNGLUNIFORM1IPROC glUniform1iProc;
	PFNGLUNIFORM2IPROC glUniform2iProc;
	PFNGLUNIFORM3IPROC glUniform3iProc;
	PFNGLUNIFORM4IPROC glUniform4iProc;
	PFNGLUNIFORM1FVPROC glUniform1fvProc;
	PFNGLUNIFORM2FVPROC glUniform2fvProc;
	PFNGLUNIFORM3FVPROC glUniform3fvProc;
	PFNGLUNIFORM4FVPROC glUniform4fvProc;
	PFNGLUNIFORM1IVPROC glUniform1ivProc;
	PFNGLUNIFORM2IVPROC glUniform2ivProc;
	PFNGLUNIFORM3IVPROC glUniform3ivProc;
	PFNGLUNIFORM4IVPROC glUniform4ivProc;
	PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fvProc;
	PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fvProc;
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fvProc;
	PFNGLVALIDATEPROGRAMPROC glValidateProgramProc;
	PFNGLVERTEXATTRIB1DPROC glVertexAttrib1dProc;
	PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dvProc;
	PFNGLVERTEXATTRIB1FPROC glVertexAttrib1fProc;
	PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fvProc;
	PFNGLVERTEXATTRIB1SPROC glVertexAttrib1sProc;
	PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1svProc;
	PFNGLVERTEXATTRIB2DPROC glVertexAttrib2dProc;
	PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dvProc;
	PFNGLVERTEXATTRIB2FPROC glVertexAttrib2fProc;
	PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fvProc;
	PFNGLVERTEXATTRIB2SPROC glVertexAttrib2sProc;
	PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2svProc;
	PFNGLVERTEXATTRIB3DPROC glVertexAttrib3dProc;
	PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dvProc;
	PFNGLVERTEXATTRIB3FPROC glVertexAttrib3fProc;
	PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fvProc;
	PFNGLVERTEXATTRIB3SPROC glVertexAttrib3sProc;
	PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3svProc;
	PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4NbvProc;
	PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4NivProc;
	PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4NsvProc;
	PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4NubProc;
	PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4NubvProc;
	PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4NuivProc;
	PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4NusvProc;
	PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bvProc;
	PFNGLVERTEXATTRIB4DPROC glVertexAttrib4dProc;
	PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dvProc;
	PFNGLVERTEXATTRIB4FPROC glVertexAttrib4fProc;
	PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fvProc;
	PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4ivProc;
	PFNGLVERTEXATTRIB4SPROC glVertexAttrib4sProc;
	PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4svProc;
	PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubvProc;
	PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uivProc;
	PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usvProc;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointerProc;
	PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fvProc;
	PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fvProc;
	PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fvProc;
	PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fvProc;
	PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fvProc;
	PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fvProc;
	PFNGLCOLORMASKIPROC glColorMaskiProc;
	PFNGLGETBOOLEANI_VPROC glGetBooleani_vProc;
	PFNGLGETINTEGERI_VPROC glGetIntegeri_vProc;
	PFNGLENABLEIPROC glEnableiProc;
	PFNGLDISABLEIPROC glDisableiProc;
	PFNGLISENABLEDIPROC glIsEnablediProc;
	PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedbackProc;
	PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedbackProc;
	PFNGLBINDBUFFERRANGEPROC glBindBufferRangeProc;
	PFNGLBINDBUFFERBASEPROC glBindBufferBaseProc;
	PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryingsProc;
	PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVaryingProc;
	PFNGLCLAMPCOLORPROC glClampColorProc;
	PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRenderProc;
	PFNGLENDCONDITIONALRENDERPROC glEndConditionalRenderProc;
	PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointerProc;
	PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIivProc;
	PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuivProc;
	PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1iProc;
	PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2iProc;
	PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3iProc;
	PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4iProc;
	PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1uiProc;
	PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2uiProc;
	PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3uiProc;
	PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4uiProc;
	PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1ivProc;
	PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2ivProc;
	PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3ivProc;
	PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4ivProc;
	PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uivProc;
	PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uivProc;
	PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uivProc;
	PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uivProc;
	PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bvProc;
	PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4svProc;
	PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubvProc;
	PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usvProc;
	PFNGLGETUNIFORMUIVPROC glGetUniformuivProc;
	PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocationProc;
	PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocationProc;
	PFNGLUNIFORM1UIPROC glUniform1uiProc;
	PFNGLUNIFORM2UIPROC glUniform2uiProc;
	PFNGLUNIFORM3UIPROC glUniform3uiProc;
	PFNGLUNIFORM4UIPROC glUniform4uiProc;
	PFNGLUNIFORM1UIVPROC glUniform1uivProc;
	PFNGLUNIFORM2UIVPROC glUniform2uivProc;
	PFNGLUNIFORM3UIVPROC glUniform3uivProc;
	PFNGLUNIFORM4UIVPROC glUniform4uivProc;
	PFNGLTEXPARAMETERIIVPROC glTexParameterIivProc;
	PFNGLTEXPARAMETERIUIVPROC glTexParameterIuivProc;
	PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIivProc;
	PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuivProc;
	PFNGLCLEARBUFFERIVPROC glClearBufferivProc;
	PFNGLCLEARBUFFERUIVPROC glClearBufferuivProc;
	PFNGLCLEARBUFFERFVPROC glClearBufferfvProc;
	PFNGLCLEARBUFFERFIPROC glClearBufferfiProc;
	PFNGLGETSTRINGIPROC glGetStringiProc;
	PFNGLISRENDERBUFFERPROC glIsRenderbufferProc;
	PFNGLBINDRENDERBUFFERPROC glBindRenderbufferProc;
	PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffersProc;
	PFNGLGENRENDERBUFFERSPROC glGenRenderbuffersProc;
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorageProc;
	PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameterivProc;
	PFNGLISFRAMEBUFFERPROC glIsFramebufferProc;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebufferProc;
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffersProc;
	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffersProc;
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatusProc;
	PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1DProc;
	PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2DProc;
	PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3DProc;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbufferProc;
	PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameterivProc;
	PFNGLGENERATEMIPMAPPROC glGenerateMipmapProc;
	PFNGLBLITFRAMEBUFFERPROC glBlitFramebufferProc;
	PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisampleProc;
	PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayerProc;
	PFNGLMAPBUFFERRANGEPROC glMapBufferRangeProc;
	PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRangeProc;
	PFNGLBINDVERTEXARRAYPROC glBindVertexArrayProc;
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArraysProc;
	PFNGLGENVERTEXARRAYSPROC glGenVertexArraysProc;
	PFNGLISVERTEXARRAYPROC glIsVertexArrayProc;
	PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstancedProc;
	PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstancedProc;
	PFNGLTEXBUFFERPROC glTexBufferProc;
	PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndexProc;
	PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubDataProc;
	PFNGLGETUNIFORMINDICESPROC glGetUniformIndicesProc;
	PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsivProc;
	PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformNameProc;
	PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndexProc;
	PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockivProc;
	PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockNameProc;
	PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBindingProc;
	PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertexProc;
	PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertexProc;
	PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertexProc;
	PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertexProc;
	PFNGLPROVOKINGVERTEXPROC glProvokingVertexProc;
	PFNGLFENCESYNCPROC glFenceSyncProc;
	PFNGLISSYNCPROC glIsSyncProc;
	PFNGLDELETESYNCPROC glDeleteSyncProc;
	PFNGLCLIENTWAITSYNCPROC glClientWaitSyncProc;
	PFNGLWAITSYNCPROC glWaitSyncProc;
	PFNGLGETINTEGER64VPROC glGetInteger64vProc;
	PFNGLGETSYNCIVPROC glGetSyncivProc;
	PFNGLGETINTEGER64I_VPROC glGetInteger64i_vProc;
	PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64vProc;
	PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTextureProc;
	PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisampleProc;
	PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisampleProc;
	PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefvProc;
	PFNGLSAMPLEMASKIPROC glSampleMaskiProc;
	PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexedProc;
	PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndexProc;
	PFNGLGENSAMPLERSPROC glGenSamplersProc;
	PFNGLDELETESAMPLERSPROC glDeleteSamplersProc;
	PFNGLISSAMPLERPROC glIsSamplerProc;
	PFNGLBINDSAMPLERPROC glBindSamplerProc;
	PFNGLSAMPLERPARAMETERIPROC glSamplerParameteriProc;
	PFNGLSAMPLERPARAMETERIVPROC glSamplerParameterivProc;
	PFNGLSAMPLERPARAMETERFPROC glSamplerParameterfProc;
	PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfvProc;
	PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIivProc;
	PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuivProc;
	PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameterivProc;
	PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIivProc;
	PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfvProc;
	PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuivProc;
	PFNGLQUERYCOUNTERPROC glQueryCounterProc;
	PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64vProc;
	PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64vProc;
	PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisorProc;
	PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1uiProc;
	PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uivProc;
	PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2uiProc;
	PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uivProc;
	PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3uiProc;
	PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uivProc;
	PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4uiProc;
	PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uivProc;
	PFNGLVERTEXP2UIPROC glVertexP2uiProc;
	PFNGLVERTEXP2UIVPROC glVertexP2uivProc;
	PFNGLVERTEXP3UIPROC glVertexP3uiProc;
	PFNGLVERTEXP3UIVPROC glVertexP3uivProc;
	PFNGLVERTEXP4UIPROC glVertexP4uiProc;
	PFNGLVERTEXP4UIVPROC glVertexP4uivProc;
	PFNGLTEXCOORDP1UIPROC glTexCoordP1uiProc;
	PFNGLTEXCOORDP1UIVPROC glTexCoordP1uivProc;
	PFNGLTEXCOORDP2UIPROC glTexCoordP2uiProc;
	PFNGLTEXCOORDP2UIVPROC glTexCoordP2uivProc;
	PFNGLTEXCOORDP3UIPROC glTexCoordP3uiProc;
	PFNGLTEXCOORDP3UIVPROC glTexCoordP3uivProc;
	PFNGLTEXCOORDP4UIPROC glTexCoordP4uiProc;
	PFNGLTEXCOORDP4UIVPROC glTexCoordP4uivProc;
	PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1uiProc;
	PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uivProc;
	PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2uiProc;
	PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uivProc;
	PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3uiProc;
	PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uivProc;
	PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4uiProc;
	PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uivProc;
	PFNGLNORMALP3UIPROC glNormalP3uiProc;
	PFNGLNORMALP3UIVPROC glNormalP3uivProc;
	PFNGLCOLORP3UIPROC glColorP3uiProc;
	PFNGLCOLORP3UIVPROC glColorP3uivProc;
	PFNGLCOLORP4UIPROC glColorP4uiProc;
	PFNGLCOLORP4UIVPROC glColorP4uivProc;
	PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3uiProc;
	PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uivProc;
	PFNGLMINSAMPLESHADINGPROC glMinSampleShadingProc;
	PFNGLBLENDEQUATIONIPROC glBlendEquationiProc;
	PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparateiProc;
	PFNGLBLENDFUNCIPROC glBlendFunciProc;
	PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparateiProc;
	PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirectProc;
	PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirectProc;
	PFNGLUNIFORM1DPROC glUniform1dProc;
	PFNGLUNIFORM2DPROC glUniform2dProc;
	PFNGLUNIFORM3DPROC glUniform3dProc;
	PFNGLUNIFORM4DPROC glUniform4dProc;
	PFNGLUNIFORM1DVPROC glUniform1dvProc;
	PFNGLUNIFORM2DVPROC glUniform2dvProc;
	PFNGLUNIFORM3DVPROC glUniform3dvProc;
	PFNGLUNIFORM4DVPROC glUniform4dvProc;
	PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dvProc;
	PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dvProc;
	PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dvProc;
	PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dvProc;
	PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dvProc;
	PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dvProc;
	PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dvProc;
	PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dvProc;
	PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dvProc;
	PFNGLGETUNIFORMDVPROC glGetUniformdvProc;
	PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocationProc;
	PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndexProc;
	PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformivProc;
	PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformNameProc;
	PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineNameProc;
	PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuivProc;
	PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuivProc;
	PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageivProc;
	PFNGLPATCHPARAMETERIPROC glPatchParameteriProc;
	PFNGLPATCHPARAMETERFVPROC glPatchParameterfvProc;
	PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedbackProc;
	PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacksProc;
	PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacksProc;
	PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedbackProc;
	PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedbackProc;
	PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedbackProc;
	PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedbackProc;
	PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStreamProc;
	PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexedProc;
	PFNGLENDQUERYINDEXEDPROC glEndQueryIndexedProc;
	PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexedivProc;
	PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompilerProc;
	PFNGLSHADERBINARYPROC glShaderBinaryProc;
	PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormatProc;
	PFNGLDEPTHRANGEFPROC glDepthRangefProc;
	PFNGLCLEARDEPTHFPROC glClearDepthfProc;
	PFNGLGETPROGRAMBINARYPROC glGetProgramBinaryProc;
	PFNGLPROGRAMBINARYPROC glProgramBinaryProc;
	PFNGLPROGRAMPARAMETERIPROC glProgramParameteriProc;
	PFNGLUSEPROGRAMSTAGESPROC glUseProgramStagesProc;
	PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgramProc;
	PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramvProc;
	PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipelineProc;
	PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelinesProc;
	PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelinesProc;
	PFNGLISPROGRAMPIPELINEPROC glIsProgramPipelineProc;
	PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineivProc;
	PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1iProc;
	PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1ivProc;
	PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1fProc;
	PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fvProc;
	PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1dProc;
	PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dvProc;
	PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1uiProc;
	PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uivProc;
	PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2iProc;
	PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2ivProc;
	PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2fProc;
	PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fvProc;
	PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2dProc;
	PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dvProc;
	PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2uiProc;
	PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uivProc;
	PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3iProc;
	PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3ivProc;
	PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3fProc;
	PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fvProc;
	PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3dProc;
	PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dvProc;
	PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3uiProc;
	PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uivProc;
	PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4iProc;
	PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4ivProc;
	PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4fProc;
	PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fvProc;
	PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4dProc;
	PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dvProc;
	PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4uiProc;
	PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uivProc;
	PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fvProc;
	PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fvProc;
	PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dvProc;
	PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dvProc;
	PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dvProc;
	PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fvProc;
	PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fvProc;
	PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fvProc;
	PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fvProc;
	PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fvProc;
	PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dvProc;
	PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dvProc;
	PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dvProc;
	PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dvProc;
	PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dvProc;
	PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dvProc;
	PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipelineProc;
	PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLogProc;
	PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1dProc;
	PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2dProc;
	PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3dProc;
	PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4dProc;
	PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dvProc;
	PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dvProc;
	PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dvProc;
	PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dvProc;
	PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointerProc;
	PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdvProc;
	PFNGLVIEWPORTARRAYVPROC glViewportArrayvProc;
	PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedfProc;
	PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfvProc;
	PFNGLSCISSORARRAYVPROC glScissorArrayvProc;
	PFNGLSCISSORINDEXEDPROC glScissorIndexedProc;
	PFNGLSCISSORINDEXEDVPROC glScissorIndexedvProc;
	PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayvProc;
	PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexedProc;
	PFNGLGETFLOATI_VPROC glGetFloati_vProc;
	PFNGLGETDOUBLEI_VPROC glGetDoublei_vProc;
	PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstanceProc;
	PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstanceProc;
	PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstanceProc;
	PFNGLGETINTERNALFORMATIVPROC glGetInternalformativProc;
	PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferivProc;
	PFNGLBINDIMAGETEXTUREPROC glBindImageTextureProc;
	PFNGLMEMORYBARRIERPROC glMemoryBarrierProc;
	PFNGLTEXSTORAGE1DPROC glTexStorage1DProc;
	PFNGLTEXSTORAGE2DPROC glTexStorage2DProc;
	PFNGLTEXSTORAGE3DPROC glTexStorage3DProc;
	PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstancedProc;
	PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstancedProc;
	PFNGLCLEARBUFFERDATAPROC glClearBufferDataProc;
	PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubDataProc;
	PFNGLDISPATCHCOMPUTEPROC glDispatchComputeProc;
	PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirectProc;
	PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubDataProc;
	PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteriProc;
	PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameterivProc;
	PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64vProc;
	PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImageProc;
	PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImageProc;
	PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubDataProc;
	PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferDataProc;
	PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebufferProc;
	PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebufferProc;
	PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirectProc;
	PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirectProc;
	PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceivProc;
	PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndexProc;
	PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceNameProc;
	PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceivProc;
	PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocationProc;
	PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndexProc;
	PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBindingProc;
	PFNGLTEXBUFFERRANGEPROC glTexBufferRangeProc;
	PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisampleProc;
	PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisampleProc;
	PFNGLTEXTUREVIEWPROC glTextureViewProc;
	PFNGLBINDVERTEXBUFFERPROC glBindVertexBufferProc;
	PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormatProc;
	PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormatProc;
	PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormatProc;
	PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBindingProc;
	PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisorProc;
	PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControlProc;
	PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsertProc;
	PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallbackProc;
	PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLogProc;
	PFNGLPUSHDEBUGGROUPPROC glPushDebugGroupProc;
	PFNGLPOPDEBUGGROUPPROC glPopDebugGroupProc;
	PFNGLOBJECTLABELPROC glObjectLabelProc;
	PFNGLGETOBJECTLABELPROC glGetObjectLabelProc;
	PFNGLOBJECTPTRLABELPROC glObjectPtrLabelProc;
	PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabelProc;
	PFNGLBUFFERSTORAGEPROC glBufferStorageProc;
	PFNGLCLEARTEXIMAGEPROC glClearTexImageProc;
	PFNGLCLEARTEXSUBIMAGEPROC glClearTexSubImageProc;
	PFNGLBINDBUFFERSBASEPROC glBindBuffersBaseProc;
	PFNGLBINDBUFFERSRANGEPROC glBindBuffersRangeProc;
	PFNGLBINDTEXTURESPROC glBindTexturesProc;
	PFNGLBINDSAMPLERSPROC glBindSamplersProc;
	PFNGLBINDIMAGETEXTURESPROC glBindImageTexturesProc;
	PFNGLBINDVERTEXBUFFERSPROC glBindVertexBuffersProc;

} gl_wrap_context;

// Function prototype definitions for each appropriate OpenGL function.
inline void gl_wrap_context_glCullFace(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glFrontFace(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glHint(gl_wrap_context* ctx, GLenum target, GLenum mode);
inline void gl_wrap_context_glLineWidth(gl_wrap_context* ctx, GLfloat width);
inline void gl_wrap_context_glPointSize(gl_wrap_context* ctx, GLfloat size);
inline void gl_wrap_context_glPolygonMode(gl_wrap_context* ctx, GLenum face, GLenum mode);
inline void gl_wrap_context_glScissor(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glTexParameterf(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat param);
inline void gl_wrap_context_glTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glTexParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param);
inline void gl_wrap_context_glTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glTexImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glDrawBuffer(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glClear(gl_wrap_context* ctx, GLbitfield mask);
inline void gl_wrap_context_glClearColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
inline void gl_wrap_context_glClearStencil(gl_wrap_context* ctx, GLint s);
inline void gl_wrap_context_glClearDepth(gl_wrap_context* ctx, GLdouble depth);
inline void gl_wrap_context_glStencilMask(gl_wrap_context* ctx, GLuint mask);
inline void gl_wrap_context_glColorMask(gl_wrap_context* ctx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
inline void gl_wrap_context_glDepthMask(gl_wrap_context* ctx, GLboolean flag);
inline void gl_wrap_context_glDisable(gl_wrap_context* ctx, GLenum cap);
inline void gl_wrap_context_glEnable(gl_wrap_context* ctx, GLenum cap);
inline void gl_wrap_context_glFinish(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glFlush(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glBlendFunc(gl_wrap_context* ctx, GLenum sfactor, GLenum dfactor);
inline void gl_wrap_context_glLogicOp(gl_wrap_context* ctx, GLenum opcode);
inline void gl_wrap_context_glStencilFunc(gl_wrap_context* ctx, GLenum func, GLint ref, GLuint mask);
inline void gl_wrap_context_glStencilOp(gl_wrap_context* ctx, GLenum fail, GLenum zfail, GLenum zpass);
inline void gl_wrap_context_glDepthFunc(gl_wrap_context* ctx, GLenum func);
inline void gl_wrap_context_glPixelStoref(gl_wrap_context* ctx, GLenum pname, GLfloat param);
inline void gl_wrap_context_glPixelStorei(gl_wrap_context* ctx, GLenum pname, GLint param);
inline void gl_wrap_context_glReadBuffer(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glReadPixels(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glGetBooleanv(gl_wrap_context* ctx, GLenum pname, GLboolean* data);
inline void gl_wrap_context_glGetDoublev(gl_wrap_context* ctx, GLenum pname, GLdouble* data);
inline GLenum gl_wrap_context_glGetError(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glGetFloatv(gl_wrap_context* ctx, GLenum pname, GLfloat* data);
inline void gl_wrap_context_glGetIntegerv(gl_wrap_context* ctx, GLenum pname, GLint* data);
inline GLubyte* gl_wrap_context_glGetString(gl_wrap_context* ctx, GLenum name);
inline void gl_wrap_context_glGetTexImage(gl_wrap_context* ctx, GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glGetTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetTexLevelParameterfv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetTexLevelParameteriv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLint* params);
inline GLboolean gl_wrap_context_glIsEnabled(gl_wrap_context* ctx, GLenum cap);
inline void gl_wrap_context_glDepthRange(gl_wrap_context* ctx, GLdouble near, GLdouble far);
inline void gl_wrap_context_glViewport(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glNewList(gl_wrap_context* ctx, GLuint list, GLenum mode);
inline void gl_wrap_context_glEndList(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glCallList(gl_wrap_context* ctx, GLuint list);
inline void gl_wrap_context_glCallLists(gl_wrap_context* ctx, GLsizei n, GLenum type, void* lists);
inline void gl_wrap_context_glDeleteLists(gl_wrap_context* ctx, GLuint list, GLsizei range);
inline GLuint gl_wrap_context_glGenLists(gl_wrap_context* ctx, GLsizei range);
inline void gl_wrap_context_glListBase(gl_wrap_context* ctx, GLuint base);
inline void gl_wrap_context_glBegin(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glBitmap(gl_wrap_context* ctx, GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte* bitmap);
inline void gl_wrap_context_glColor3b(gl_wrap_context* ctx, GLbyte red, GLbyte green, GLbyte blue);
inline void gl_wrap_context_glColor3bv(gl_wrap_context* ctx, GLbyte* v);
inline void gl_wrap_context_glColor3d(gl_wrap_context* ctx, GLdouble red, GLdouble green, GLdouble blue);
inline void gl_wrap_context_glColor3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glColor3f(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue);
inline void gl_wrap_context_glColor3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glColor3i(gl_wrap_context* ctx, GLint red, GLint green, GLint blue);
inline void gl_wrap_context_glColor3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glColor3s(gl_wrap_context* ctx, GLshort red, GLshort green, GLshort blue);
inline void gl_wrap_context_glColor3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glColor3ub(gl_wrap_context* ctx, GLubyte red, GLubyte green, GLubyte blue);
inline void gl_wrap_context_glColor3ubv(gl_wrap_context* ctx, GLubyte* v);
inline void gl_wrap_context_glColor3ui(gl_wrap_context* ctx, GLuint red, GLuint green, GLuint blue);
inline void gl_wrap_context_glColor3uiv(gl_wrap_context* ctx, GLuint* v);
inline void gl_wrap_context_glColor3us(gl_wrap_context* ctx, GLushort red, GLushort green, GLushort blue);
inline void gl_wrap_context_glColor3usv(gl_wrap_context* ctx, GLushort* v);
inline void gl_wrap_context_glColor4b(gl_wrap_context* ctx, GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
inline void gl_wrap_context_glColor4bv(gl_wrap_context* ctx, GLbyte* v);
inline void gl_wrap_context_glColor4d(gl_wrap_context* ctx, GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
inline void gl_wrap_context_glColor4dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glColor4f(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
inline void gl_wrap_context_glColor4fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glColor4i(gl_wrap_context* ctx, GLint red, GLint green, GLint blue, GLint alpha);
inline void gl_wrap_context_glColor4iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glColor4s(gl_wrap_context* ctx, GLshort red, GLshort green, GLshort blue, GLshort alpha);
inline void gl_wrap_context_glColor4sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glColor4ub(gl_wrap_context* ctx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
inline void gl_wrap_context_glColor4ubv(gl_wrap_context* ctx, GLubyte* v);
inline void gl_wrap_context_glColor4ui(gl_wrap_context* ctx, GLuint red, GLuint green, GLuint blue, GLuint alpha);
inline void gl_wrap_context_glColor4uiv(gl_wrap_context* ctx, GLuint* v);
inline void gl_wrap_context_glColor4us(gl_wrap_context* ctx, GLushort red, GLushort green, GLushort blue, GLushort alpha);
inline void gl_wrap_context_glColor4usv(gl_wrap_context* ctx, GLushort* v);
inline void gl_wrap_context_glEdgeFlag(gl_wrap_context* ctx, GLboolean flag);
inline void gl_wrap_context_glEdgeFlagv(gl_wrap_context* ctx, GLboolean* flag);
inline void gl_wrap_context_glEnd(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glIndexd(gl_wrap_context* ctx, GLdouble c);
inline void gl_wrap_context_glIndexdv(gl_wrap_context* ctx, GLdouble* c);
inline void gl_wrap_context_glIndexf(gl_wrap_context* ctx, GLfloat c);
inline void gl_wrap_context_glIndexfv(gl_wrap_context* ctx, GLfloat* c);
inline void gl_wrap_context_glIndexi(gl_wrap_context* ctx, GLint c);
inline void gl_wrap_context_glIndexiv(gl_wrap_context* ctx, GLint* c);
inline void gl_wrap_context_glIndexs(gl_wrap_context* ctx, GLshort c);
inline void gl_wrap_context_glIndexsv(gl_wrap_context* ctx, GLshort* c);
inline void gl_wrap_context_glNormal3b(gl_wrap_context* ctx, GLbyte nx, GLbyte ny, GLbyte nz);
inline void gl_wrap_context_glNormal3bv(gl_wrap_context* ctx, GLbyte* v);
inline void gl_wrap_context_glNormal3d(gl_wrap_context* ctx, GLdouble nx, GLdouble ny, GLdouble nz);
inline void gl_wrap_context_glNormal3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glNormal3f(gl_wrap_context* ctx, GLfloat nx, GLfloat ny, GLfloat nz);
inline void gl_wrap_context_glNormal3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glNormal3i(gl_wrap_context* ctx, GLint nx, GLint ny, GLint nz);
inline void gl_wrap_context_glNormal3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glNormal3s(gl_wrap_context* ctx, GLshort nx, GLshort ny, GLshort nz);
inline void gl_wrap_context_glNormal3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glRasterPos2d(gl_wrap_context* ctx, GLdouble x, GLdouble y);
inline void gl_wrap_context_glRasterPos2dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glRasterPos2f(gl_wrap_context* ctx, GLfloat x, GLfloat y);
inline void gl_wrap_context_glRasterPos2fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glRasterPos2i(gl_wrap_context* ctx, GLint x, GLint y);
inline void gl_wrap_context_glRasterPos2iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glRasterPos2s(gl_wrap_context* ctx, GLshort x, GLshort y);
inline void gl_wrap_context_glRasterPos2sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glRasterPos3d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glRasterPos3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glRasterPos3f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glRasterPos3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glRasterPos3i(gl_wrap_context* ctx, GLint x, GLint y, GLint z);
inline void gl_wrap_context_glRasterPos3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glRasterPos3s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z);
inline void gl_wrap_context_glRasterPos3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glRasterPos4d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
inline void gl_wrap_context_glRasterPos4dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glRasterPos4f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
inline void gl_wrap_context_glRasterPos4fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glRasterPos4i(gl_wrap_context* ctx, GLint x, GLint y, GLint z, GLint w);
inline void gl_wrap_context_glRasterPos4iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glRasterPos4s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z, GLshort w);
inline void gl_wrap_context_glRasterPos4sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glRectd(gl_wrap_context* ctx, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
inline void gl_wrap_context_glRectdv(gl_wrap_context* ctx, GLdouble* v1, GLdouble* v2);
inline void gl_wrap_context_glRectf(gl_wrap_context* ctx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
inline void gl_wrap_context_glRectfv(gl_wrap_context* ctx, GLfloat* v1, GLfloat* v2);
inline void gl_wrap_context_glRecti(gl_wrap_context* ctx, GLint x1, GLint y1, GLint x2, GLint y2);
inline void gl_wrap_context_glRectiv(gl_wrap_context* ctx, GLint* v1, GLint* v2);
inline void gl_wrap_context_glRects(gl_wrap_context* ctx, GLshort x1, GLshort y1, GLshort x2, GLshort y2);
inline void gl_wrap_context_glRectsv(gl_wrap_context* ctx, GLshort* v1, GLshort* v2);
inline void gl_wrap_context_glTexCoord1d(gl_wrap_context* ctx, GLdouble s);
inline void gl_wrap_context_glTexCoord1dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glTexCoord1f(gl_wrap_context* ctx, GLfloat s);
inline void gl_wrap_context_glTexCoord1fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glTexCoord1i(gl_wrap_context* ctx, GLint s);
inline void gl_wrap_context_glTexCoord1iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glTexCoord1s(gl_wrap_context* ctx, GLshort s);
inline void gl_wrap_context_glTexCoord1sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glTexCoord2d(gl_wrap_context* ctx, GLdouble s, GLdouble t);
inline void gl_wrap_context_glTexCoord2dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glTexCoord2f(gl_wrap_context* ctx, GLfloat s, GLfloat t);
inline void gl_wrap_context_glTexCoord2fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glTexCoord2i(gl_wrap_context* ctx, GLint s, GLint t);
inline void gl_wrap_context_glTexCoord2iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glTexCoord2s(gl_wrap_context* ctx, GLshort s, GLshort t);
inline void gl_wrap_context_glTexCoord2sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glTexCoord3d(gl_wrap_context* ctx, GLdouble s, GLdouble t, GLdouble r);
inline void gl_wrap_context_glTexCoord3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glTexCoord3f(gl_wrap_context* ctx, GLfloat s, GLfloat t, GLfloat r);
inline void gl_wrap_context_glTexCoord3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glTexCoord3i(gl_wrap_context* ctx, GLint s, GLint t, GLint r);
inline void gl_wrap_context_glTexCoord3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glTexCoord3s(gl_wrap_context* ctx, GLshort s, GLshort t, GLshort r);
inline void gl_wrap_context_glTexCoord3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glTexCoord4d(gl_wrap_context* ctx, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
inline void gl_wrap_context_glTexCoord4dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glTexCoord4f(gl_wrap_context* ctx, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
inline void gl_wrap_context_glTexCoord4fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glTexCoord4i(gl_wrap_context* ctx, GLint s, GLint t, GLint r, GLint q);
inline void gl_wrap_context_glTexCoord4iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glTexCoord4s(gl_wrap_context* ctx, GLshort s, GLshort t, GLshort r, GLshort q);
inline void gl_wrap_context_glTexCoord4sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glVertex2d(gl_wrap_context* ctx, GLdouble x, GLdouble y);
inline void gl_wrap_context_glVertex2dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glVertex2f(gl_wrap_context* ctx, GLfloat x, GLfloat y);
inline void gl_wrap_context_glVertex2fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glVertex2i(gl_wrap_context* ctx, GLint x, GLint y);
inline void gl_wrap_context_glVertex2iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glVertex2s(gl_wrap_context* ctx, GLshort x, GLshort y);
inline void gl_wrap_context_glVertex2sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glVertex3d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glVertex3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glVertex3f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glVertex3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glVertex3i(gl_wrap_context* ctx, GLint x, GLint y, GLint z);
inline void gl_wrap_context_glVertex3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glVertex3s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z);
inline void gl_wrap_context_glVertex3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glVertex4d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
inline void gl_wrap_context_glVertex4dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glVertex4f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
inline void gl_wrap_context_glVertex4fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glVertex4i(gl_wrap_context* ctx, GLint x, GLint y, GLint z, GLint w);
inline void gl_wrap_context_glVertex4iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glVertex4s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z, GLshort w);
inline void gl_wrap_context_glVertex4sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glClipPlane(gl_wrap_context* ctx, GLenum plane, GLdouble* equation);
inline void gl_wrap_context_glColorMaterial(gl_wrap_context* ctx, GLenum face, GLenum mode);
inline void gl_wrap_context_glFogf(gl_wrap_context* ctx, GLenum pname, GLfloat param);
inline void gl_wrap_context_glFogfv(gl_wrap_context* ctx, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glFogi(gl_wrap_context* ctx, GLenum pname, GLint param);
inline void gl_wrap_context_glFogiv(gl_wrap_context* ctx, GLenum pname, GLint* params);
inline void gl_wrap_context_glLightf(gl_wrap_context* ctx, GLenum light, GLenum pname, GLfloat param);
inline void gl_wrap_context_glLightfv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glLighti(gl_wrap_context* ctx, GLenum light, GLenum pname, GLint param);
inline void gl_wrap_context_glLightiv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLint* params);
inline void gl_wrap_context_glLightModelf(gl_wrap_context* ctx, GLenum pname, GLfloat param);
inline void gl_wrap_context_glLightModelfv(gl_wrap_context* ctx, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glLightModeli(gl_wrap_context* ctx, GLenum pname, GLint param);
inline void gl_wrap_context_glLightModeliv(gl_wrap_context* ctx, GLenum pname, GLint* params);
inline void gl_wrap_context_glLineStipple(gl_wrap_context* ctx, GLint factor, GLushort pattern);
inline void gl_wrap_context_glMaterialf(gl_wrap_context* ctx, GLenum face, GLenum pname, GLfloat param);
inline void gl_wrap_context_glMaterialfv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glMateriali(gl_wrap_context* ctx, GLenum face, GLenum pname, GLint param);
inline void gl_wrap_context_glMaterialiv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLint* params);
inline void gl_wrap_context_glPolygonStipple(gl_wrap_context* ctx, GLubyte* mask);
inline void gl_wrap_context_glShadeModel(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glTexEnvf(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat param);
inline void gl_wrap_context_glTexEnvfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glTexEnvi(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param);
inline void gl_wrap_context_glTexEnviv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glTexGend(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLdouble param);
inline void gl_wrap_context_glTexGendv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLdouble* params);
inline void gl_wrap_context_glTexGenf(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLfloat param);
inline void gl_wrap_context_glTexGenfv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glTexGeni(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLint param);
inline void gl_wrap_context_glTexGeniv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLint* params);
inline void gl_wrap_context_glFeedbackBuffer(gl_wrap_context* ctx, GLsizei size, GLenum type, GLfloat* buffer);
inline void gl_wrap_context_glSelectBuffer(gl_wrap_context* ctx, GLsizei size, GLuint* buffer);
inline GLint gl_wrap_context_glRenderMode(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glInitNames(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glLoadName(gl_wrap_context* ctx, GLuint name);
inline void gl_wrap_context_glPassThrough(gl_wrap_context* ctx, GLfloat token);
inline void gl_wrap_context_glPopName(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glPushName(gl_wrap_context* ctx, GLuint name);
inline void gl_wrap_context_glClearAccum(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
inline void gl_wrap_context_glClearIndex(gl_wrap_context* ctx, GLfloat c);
inline void gl_wrap_context_glIndexMask(gl_wrap_context* ctx, GLuint mask);
inline void gl_wrap_context_glAccum(gl_wrap_context* ctx, GLenum op, GLfloat value);
inline void gl_wrap_context_glPopAttrib(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glPushAttrib(gl_wrap_context* ctx, GLbitfield mask);
inline void gl_wrap_context_glMap1d(gl_wrap_context* ctx, GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, GLdouble* points);
inline void gl_wrap_context_glMap1f(gl_wrap_context* ctx, GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, GLfloat* points);
inline void gl_wrap_context_glMap2d(gl_wrap_context* ctx, GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble* points);
inline void gl_wrap_context_glMap2f(gl_wrap_context* ctx, GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat* points);
inline void gl_wrap_context_glMapGrid1d(gl_wrap_context* ctx, GLint un, GLdouble u1, GLdouble u2);
inline void gl_wrap_context_glMapGrid1f(gl_wrap_context* ctx, GLint un, GLfloat u1, GLfloat u2);
inline void gl_wrap_context_glMapGrid2d(gl_wrap_context* ctx, GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
inline void gl_wrap_context_glMapGrid2f(gl_wrap_context* ctx, GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
inline void gl_wrap_context_glEvalCoord1d(gl_wrap_context* ctx, GLdouble u);
inline void gl_wrap_context_glEvalCoord1dv(gl_wrap_context* ctx, GLdouble* u);
inline void gl_wrap_context_glEvalCoord1f(gl_wrap_context* ctx, GLfloat u);
inline void gl_wrap_context_glEvalCoord1fv(gl_wrap_context* ctx, GLfloat* u);
inline void gl_wrap_context_glEvalCoord2d(gl_wrap_context* ctx, GLdouble u, GLdouble v);
inline void gl_wrap_context_glEvalCoord2dv(gl_wrap_context* ctx, GLdouble* u);
inline void gl_wrap_context_glEvalCoord2f(gl_wrap_context* ctx, GLfloat u, GLfloat v);
inline void gl_wrap_context_glEvalCoord2fv(gl_wrap_context* ctx, GLfloat* u);
inline void gl_wrap_context_glEvalMesh1(gl_wrap_context* ctx, GLenum mode, GLint i1, GLint i2);
inline void gl_wrap_context_glEvalPoint1(gl_wrap_context* ctx, GLint i);
inline void gl_wrap_context_glEvalMesh2(gl_wrap_context* ctx, GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
inline void gl_wrap_context_glEvalPoint2(gl_wrap_context* ctx, GLint i, GLint j);
inline void gl_wrap_context_glAlphaFunc(gl_wrap_context* ctx, GLenum func, GLfloat ref);
inline void gl_wrap_context_glPixelZoom(gl_wrap_context* ctx, GLfloat xfactor, GLfloat yfactor);
inline void gl_wrap_context_glPixelTransferf(gl_wrap_context* ctx, GLenum pname, GLfloat param);
inline void gl_wrap_context_glPixelTransferi(gl_wrap_context* ctx, GLenum pname, GLint param);
inline void gl_wrap_context_glPixelMapfv(gl_wrap_context* ctx, GLenum map, GLsizei mapsize, GLfloat* values);
inline void gl_wrap_context_glPixelMapuiv(gl_wrap_context* ctx, GLenum map, GLsizei mapsize, GLuint* values);
inline void gl_wrap_context_glPixelMapusv(gl_wrap_context* ctx, GLenum map, GLsizei mapsize, GLushort* values);
inline void gl_wrap_context_glCopyPixels(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
inline void gl_wrap_context_glDrawPixels(gl_wrap_context* ctx, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glGetClipPlane(gl_wrap_context* ctx, GLenum plane, GLdouble* equation);
inline void gl_wrap_context_glGetLightfv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetLightiv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetMapdv(gl_wrap_context* ctx, GLenum target, GLenum query, GLdouble* v);
inline void gl_wrap_context_glGetMapfv(gl_wrap_context* ctx, GLenum target, GLenum query, GLfloat* v);
inline void gl_wrap_context_glGetMapiv(gl_wrap_context* ctx, GLenum target, GLenum query, GLint* v);
inline void gl_wrap_context_glGetMaterialfv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetMaterialiv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetPixelMapfv(gl_wrap_context* ctx, GLenum map, GLfloat* values);
inline void gl_wrap_context_glGetPixelMapuiv(gl_wrap_context* ctx, GLenum map, GLuint* values);
inline void gl_wrap_context_glGetPixelMapusv(gl_wrap_context* ctx, GLenum map, GLushort* values);
inline void gl_wrap_context_glGetPolygonStipple(gl_wrap_context* ctx, GLubyte* mask);
inline void gl_wrap_context_glGetTexEnvfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetTexEnviv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetTexGendv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLdouble* params);
inline void gl_wrap_context_glGetTexGenfv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetTexGeniv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLint* params);
inline GLboolean gl_wrap_context_glIsList(gl_wrap_context* ctx, GLuint list);
inline void gl_wrap_context_glFrustum(gl_wrap_context* ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
inline void gl_wrap_context_glLoadIdentity(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glLoadMatrixf(gl_wrap_context* ctx, GLfloat* m);
inline void gl_wrap_context_glLoadMatrixd(gl_wrap_context* ctx, GLdouble* m);
inline void gl_wrap_context_glMatrixMode(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glMultMatrixf(gl_wrap_context* ctx, GLfloat* m);
inline void gl_wrap_context_glMultMatrixd(gl_wrap_context* ctx, GLdouble* m);
inline void gl_wrap_context_glOrtho(gl_wrap_context* ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
inline void gl_wrap_context_glPopMatrix(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glPushMatrix(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glRotated(gl_wrap_context* ctx, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glRotatef(gl_wrap_context* ctx, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glScaled(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glScalef(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glTranslated(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glTranslatef(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glDrawArrays(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count);
inline void gl_wrap_context_glDrawElements(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices);
inline void gl_wrap_context_glGetPointerv(gl_wrap_context* ctx, GLenum pname, void** params);
inline void gl_wrap_context_glPolygonOffset(gl_wrap_context* ctx, GLfloat factor, GLfloat units);
inline void gl_wrap_context_glCopyTexImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
inline void gl_wrap_context_glCopyTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
inline void gl_wrap_context_glCopyTexSubImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
inline void gl_wrap_context_glCopyTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glTexSubImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glBindTexture(gl_wrap_context* ctx, GLenum target, GLuint texture);
inline void gl_wrap_context_glDeleteTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures);
inline void gl_wrap_context_glGenTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures);
inline GLboolean gl_wrap_context_glIsTexture(gl_wrap_context* ctx, GLuint texture);
inline void gl_wrap_context_glArrayElement(gl_wrap_context* ctx, GLint i);
inline void gl_wrap_context_glColorPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glDisableClientState(gl_wrap_context* ctx, GLenum array);
inline void gl_wrap_context_glEdgeFlagPointer(gl_wrap_context* ctx, GLsizei stride, void* pointer);
inline void gl_wrap_context_glEnableClientState(gl_wrap_context* ctx, GLenum array);
inline void gl_wrap_context_glIndexPointer(gl_wrap_context* ctx, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glInterleavedArrays(gl_wrap_context* ctx, GLenum format, GLsizei stride, void* pointer);
inline void gl_wrap_context_glNormalPointer(gl_wrap_context* ctx, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glTexCoordPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glVertexPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer);
inline GLboolean gl_wrap_context_glAreTexturesResident(gl_wrap_context* ctx, GLsizei n, GLuint* textures, GLboolean* residences);
inline void gl_wrap_context_glPrioritizeTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures, GLfloat* priorities);
inline void gl_wrap_context_glIndexub(gl_wrap_context* ctx, GLubyte c);
inline void gl_wrap_context_glIndexubv(gl_wrap_context* ctx, GLubyte* c);
inline void gl_wrap_context_glPopClientAttrib(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glPushClientAttrib(gl_wrap_context* ctx, GLbitfield mask);
inline void gl_wrap_context_glDrawRangeElements(gl_wrap_context* ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices);
inline void gl_wrap_context_glTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* pixels);
inline void gl_wrap_context_glCopyTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glActiveTexture(gl_wrap_context* ctx, GLenum texture);
inline void gl_wrap_context_glSampleCoverage(gl_wrap_context* ctx, GLfloat value, GLboolean invert);
inline void gl_wrap_context_glCompressedTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, void* data);
inline void gl_wrap_context_glCompressedTexSubImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, void* data);
inline void gl_wrap_context_glGetCompressedTexImage(gl_wrap_context* ctx, GLenum target, GLint level, void* img);
inline void gl_wrap_context_glClientActiveTexture(gl_wrap_context* ctx, GLenum texture);
inline void gl_wrap_context_glMultiTexCoord1d(gl_wrap_context* ctx, GLenum target, GLdouble s);
inline void gl_wrap_context_glMultiTexCoord1dv(gl_wrap_context* ctx, GLenum target, GLdouble* v);
inline void gl_wrap_context_glMultiTexCoord1f(gl_wrap_context* ctx, GLenum target, GLfloat s);
inline void gl_wrap_context_glMultiTexCoord1fv(gl_wrap_context* ctx, GLenum target, GLfloat* v);
inline void gl_wrap_context_glMultiTexCoord1i(gl_wrap_context* ctx, GLenum target, GLint s);
inline void gl_wrap_context_glMultiTexCoord1iv(gl_wrap_context* ctx, GLenum target, GLint* v);
inline void gl_wrap_context_glMultiTexCoord1s(gl_wrap_context* ctx, GLenum target, GLshort s);
inline void gl_wrap_context_glMultiTexCoord1sv(gl_wrap_context* ctx, GLenum target, GLshort* v);
inline void gl_wrap_context_glMultiTexCoord2d(gl_wrap_context* ctx, GLenum target, GLdouble s, GLdouble t);
inline void gl_wrap_context_glMultiTexCoord2dv(gl_wrap_context* ctx, GLenum target, GLdouble* v);
inline void gl_wrap_context_glMultiTexCoord2f(gl_wrap_context* ctx, GLenum target, GLfloat s, GLfloat t);
inline void gl_wrap_context_glMultiTexCoord2fv(gl_wrap_context* ctx, GLenum target, GLfloat* v);
inline void gl_wrap_context_glMultiTexCoord2i(gl_wrap_context* ctx, GLenum target, GLint s, GLint t);
inline void gl_wrap_context_glMultiTexCoord2iv(gl_wrap_context* ctx, GLenum target, GLint* v);
inline void gl_wrap_context_glMultiTexCoord2s(gl_wrap_context* ctx, GLenum target, GLshort s, GLshort t);
inline void gl_wrap_context_glMultiTexCoord2sv(gl_wrap_context* ctx, GLenum target, GLshort* v);
inline void gl_wrap_context_glMultiTexCoord3d(gl_wrap_context* ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r);
inline void gl_wrap_context_glMultiTexCoord3dv(gl_wrap_context* ctx, GLenum target, GLdouble* v);
inline void gl_wrap_context_glMultiTexCoord3f(gl_wrap_context* ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r);
inline void gl_wrap_context_glMultiTexCoord3fv(gl_wrap_context* ctx, GLenum target, GLfloat* v);
inline void gl_wrap_context_glMultiTexCoord3i(gl_wrap_context* ctx, GLenum target, GLint s, GLint t, GLint r);
inline void gl_wrap_context_glMultiTexCoord3iv(gl_wrap_context* ctx, GLenum target, GLint* v);
inline void gl_wrap_context_glMultiTexCoord3s(gl_wrap_context* ctx, GLenum target, GLshort s, GLshort t, GLshort r);
inline void gl_wrap_context_glMultiTexCoord3sv(gl_wrap_context* ctx, GLenum target, GLshort* v);
inline void gl_wrap_context_glMultiTexCoord4d(gl_wrap_context* ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
inline void gl_wrap_context_glMultiTexCoord4dv(gl_wrap_context* ctx, GLenum target, GLdouble* v);
inline void gl_wrap_context_glMultiTexCoord4f(gl_wrap_context* ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
inline void gl_wrap_context_glMultiTexCoord4fv(gl_wrap_context* ctx, GLenum target, GLfloat* v);
inline void gl_wrap_context_glMultiTexCoord4i(gl_wrap_context* ctx, GLenum target, GLint s, GLint t, GLint r, GLint q);
inline void gl_wrap_context_glMultiTexCoord4iv(gl_wrap_context* ctx, GLenum target, GLint* v);
inline void gl_wrap_context_glMultiTexCoord4s(gl_wrap_context* ctx, GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
inline void gl_wrap_context_glMultiTexCoord4sv(gl_wrap_context* ctx, GLenum target, GLshort* v);
inline void gl_wrap_context_glLoadTransposeMatrixf(gl_wrap_context* ctx, GLfloat* m);
inline void gl_wrap_context_glLoadTransposeMatrixd(gl_wrap_context* ctx, GLdouble* m);
inline void gl_wrap_context_glMultTransposeMatrixf(gl_wrap_context* ctx, GLfloat* m);
inline void gl_wrap_context_glMultTransposeMatrixd(gl_wrap_context* ctx, GLdouble* m);
inline void gl_wrap_context_glBlendFuncSeparate(gl_wrap_context* ctx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
inline void gl_wrap_context_glMultiDrawArrays(gl_wrap_context* ctx, GLenum mode, GLint* first, GLsizei* count, GLsizei drawcount);
inline void gl_wrap_context_glMultiDrawElements(gl_wrap_context* ctx, GLenum mode, GLsizei* count, GLenum type, void** indices, GLsizei drawcount);
inline void gl_wrap_context_glPointParameterf(gl_wrap_context* ctx, GLenum pname, GLfloat param);
inline void gl_wrap_context_glPointParameterfv(gl_wrap_context* ctx, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glPointParameteri(gl_wrap_context* ctx, GLenum pname, GLint param);
inline void gl_wrap_context_glPointParameteriv(gl_wrap_context* ctx, GLenum pname, GLint* params);
inline void gl_wrap_context_glFogCoordf(gl_wrap_context* ctx, GLfloat coord);
inline void gl_wrap_context_glFogCoordfv(gl_wrap_context* ctx, GLfloat* coord);
inline void gl_wrap_context_glFogCoordd(gl_wrap_context* ctx, GLdouble coord);
inline void gl_wrap_context_glFogCoorddv(gl_wrap_context* ctx, GLdouble* coord);
inline void gl_wrap_context_glFogCoordPointer(gl_wrap_context* ctx, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glSecondaryColor3b(gl_wrap_context* ctx, GLbyte red, GLbyte green, GLbyte blue);
inline void gl_wrap_context_glSecondaryColor3bv(gl_wrap_context* ctx, GLbyte* v);
inline void gl_wrap_context_glSecondaryColor3d(gl_wrap_context* ctx, GLdouble red, GLdouble green, GLdouble blue);
inline void gl_wrap_context_glSecondaryColor3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glSecondaryColor3f(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue);
inline void gl_wrap_context_glSecondaryColor3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glSecondaryColor3i(gl_wrap_context* ctx, GLint red, GLint green, GLint blue);
inline void gl_wrap_context_glSecondaryColor3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glSecondaryColor3s(gl_wrap_context* ctx, GLshort red, GLshort green, GLshort blue);
inline void gl_wrap_context_glSecondaryColor3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glSecondaryColor3ub(gl_wrap_context* ctx, GLubyte red, GLubyte green, GLubyte blue);
inline void gl_wrap_context_glSecondaryColor3ubv(gl_wrap_context* ctx, GLubyte* v);
inline void gl_wrap_context_glSecondaryColor3ui(gl_wrap_context* ctx, GLuint red, GLuint green, GLuint blue);
inline void gl_wrap_context_glSecondaryColor3uiv(gl_wrap_context* ctx, GLuint* v);
inline void gl_wrap_context_glSecondaryColor3us(gl_wrap_context* ctx, GLushort red, GLushort green, GLushort blue);
inline void gl_wrap_context_glSecondaryColor3usv(gl_wrap_context* ctx, GLushort* v);
inline void gl_wrap_context_glSecondaryColorPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glWindowPos2d(gl_wrap_context* ctx, GLdouble x, GLdouble y);
inline void gl_wrap_context_glWindowPos2dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glWindowPos2f(gl_wrap_context* ctx, GLfloat x, GLfloat y);
inline void gl_wrap_context_glWindowPos2fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glWindowPos2i(gl_wrap_context* ctx, GLint x, GLint y);
inline void gl_wrap_context_glWindowPos2iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glWindowPos2s(gl_wrap_context* ctx, GLshort x, GLshort y);
inline void gl_wrap_context_glWindowPos2sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glWindowPos3d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glWindowPos3dv(gl_wrap_context* ctx, GLdouble* v);
inline void gl_wrap_context_glWindowPos3f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glWindowPos3fv(gl_wrap_context* ctx, GLfloat* v);
inline void gl_wrap_context_glWindowPos3i(gl_wrap_context* ctx, GLint x, GLint y, GLint z);
inline void gl_wrap_context_glWindowPos3iv(gl_wrap_context* ctx, GLint* v);
inline void gl_wrap_context_glWindowPos3s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z);
inline void gl_wrap_context_glWindowPos3sv(gl_wrap_context* ctx, GLshort* v);
inline void gl_wrap_context_glBlendColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
inline void gl_wrap_context_glBlendEquation(gl_wrap_context* ctx, GLenum mode);
inline void gl_wrap_context_glGenQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline void gl_wrap_context_glDeleteQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline GLboolean gl_wrap_context_glIsQuery(gl_wrap_context* ctx, GLuint id);
inline void gl_wrap_context_glBeginQuery(gl_wrap_context* ctx, GLenum target, GLuint id);
inline void gl_wrap_context_glEndQuery(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glGetQueryiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetQueryObjectiv(gl_wrap_context* ctx, GLuint id, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetQueryObjectuiv(gl_wrap_context* ctx, GLuint id, GLenum pname, GLuint* params);
inline void gl_wrap_context_glBindBuffer(gl_wrap_context* ctx, GLenum target, GLuint buffer);
inline void gl_wrap_context_glDeleteBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers);
inline void gl_wrap_context_glGenBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers);
inline GLboolean gl_wrap_context_glIsBuffer(gl_wrap_context* ctx, GLuint buffer);
inline void gl_wrap_context_glBufferData(gl_wrap_context* ctx, GLenum target, GLsizeiptr size, void* data, GLenum usage);
inline void gl_wrap_context_glBufferSubData(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr size, void* data);
inline void gl_wrap_context_glGetBufferSubData(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr size, void* data);
inline void gl_wrap_context_glMapBuffer(gl_wrap_context* ctx, GLenum target, GLenum access);
inline GLboolean gl_wrap_context_glUnmapBuffer(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glGetBufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetBufferPointerv(gl_wrap_context* ctx, GLenum target, GLenum pname, void** params);
inline void gl_wrap_context_glBlendEquationSeparate(gl_wrap_context* ctx, GLenum modeRGB, GLenum modeAlpha);
inline void gl_wrap_context_glDrawBuffers(gl_wrap_context* ctx, GLsizei n, GLenum* bufs);
inline void gl_wrap_context_glStencilOpSeparate(gl_wrap_context* ctx, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
inline void gl_wrap_context_glStencilFuncSeparate(gl_wrap_context* ctx, GLenum face, GLenum func, GLint ref, GLuint mask);
inline void gl_wrap_context_glStencilMaskSeparate(gl_wrap_context* ctx, GLenum face, GLuint mask);
inline void gl_wrap_context_glAttachShader(gl_wrap_context* ctx, GLuint program, GLuint shader);
inline void gl_wrap_context_glBindAttribLocation(gl_wrap_context* ctx, GLuint program, GLuint index, GLchar* name);
inline void gl_wrap_context_glCompileShader(gl_wrap_context* ctx, GLuint shader);
inline GLuint gl_wrap_context_glCreateProgram(gl_wrap_context* ctxvoid);
inline GLuint gl_wrap_context_glCreateShader(gl_wrap_context* ctx, GLenum type);
inline void gl_wrap_context_glDeleteProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glDeleteShader(gl_wrap_context* ctx, GLuint shader);
inline void gl_wrap_context_glDetachShader(gl_wrap_context* ctx, GLuint program, GLuint shader);
inline void gl_wrap_context_glDisableVertexAttribArray(gl_wrap_context* ctx, GLuint index);
inline void gl_wrap_context_glEnableVertexAttribArray(gl_wrap_context* ctx, GLuint index);
inline void gl_wrap_context_glGetActiveAttrib(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
inline void gl_wrap_context_glGetActiveUniform(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
inline void gl_wrap_context_glGetAttachedShaders(gl_wrap_context* ctx, GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders);
inline GLint gl_wrap_context_glGetAttribLocation(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glGetProgramiv(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetProgramInfoLog(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
inline void gl_wrap_context_glGetShaderiv(gl_wrap_context* ctx, GLuint shader, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetShaderInfoLog(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
inline void gl_wrap_context_glGetShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source);
inline GLint gl_wrap_context_glGetUniformLocation(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glGetUniformfv(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat* params);
inline void gl_wrap_context_glGetUniformiv(gl_wrap_context* ctx, GLuint program, GLint location, GLint* params);
inline void gl_wrap_context_glGetVertexAttribdv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLdouble* params);
inline void gl_wrap_context_glGetVertexAttribfv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetVertexAttribiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetVertexAttribPointerv(gl_wrap_context* ctx, GLuint index, GLenum pname, void** pointer);
inline GLboolean gl_wrap_context_glIsProgram(gl_wrap_context* ctx, GLuint program);
inline GLboolean gl_wrap_context_glIsShader(gl_wrap_context* ctx, GLuint shader);
inline void gl_wrap_context_glLinkProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei count, GLchar** string, GLint* length);
inline void gl_wrap_context_glUseProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glUniform1f(gl_wrap_context* ctx, GLint location, GLfloat v0);
inline void gl_wrap_context_glUniform2f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1);
inline void gl_wrap_context_glUniform3f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
inline void gl_wrap_context_glUniform4f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
inline void gl_wrap_context_glUniform1i(gl_wrap_context* ctx, GLint location, GLint v0);
inline void gl_wrap_context_glUniform2i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1);
inline void gl_wrap_context_glUniform3i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2);
inline void gl_wrap_context_glUniform4i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
inline void gl_wrap_context_glUniform1fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glUniform1iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniform2iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniform3iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniform4iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glUniformMatrix2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glValidateProgram(gl_wrap_context* ctx, GLuint program);
inline void gl_wrap_context_glVertexAttrib1d(gl_wrap_context* ctx, GLuint index, GLdouble x);
inline void gl_wrap_context_glVertexAttrib1dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttrib1f(gl_wrap_context* ctx, GLuint index, GLfloat x);
inline void gl_wrap_context_glVertexAttrib1fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib1s(gl_wrap_context* ctx, GLuint index, GLshort x);
inline void gl_wrap_context_glVertexAttrib1sv(gl_wrap_context* ctx, GLuint index, GLshort* v);
inline void gl_wrap_context_glVertexAttrib2d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y);
inline void gl_wrap_context_glVertexAttrib2dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttrib2f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y);
inline void gl_wrap_context_glVertexAttrib2fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib2s(gl_wrap_context* ctx, GLuint index, GLshort x, GLshort y);
inline void gl_wrap_context_glVertexAttrib2sv(gl_wrap_context* ctx, GLuint index, GLshort* v);
inline void gl_wrap_context_glVertexAttrib3d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glVertexAttrib3dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttrib3f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z);
inline void gl_wrap_context_glVertexAttrib3fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib3s(gl_wrap_context* ctx, GLuint index, GLshort x, GLshort y, GLshort z);
inline void gl_wrap_context_glVertexAttrib3sv(gl_wrap_context* ctx, GLuint index, GLshort* v);
inline void gl_wrap_context_glVertexAttrib4Nbv(gl_wrap_context* ctx, GLuint index, GLbyte* v);
inline void gl_wrap_context_glVertexAttrib4Niv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttrib4Nsv(gl_wrap_context* ctx, GLuint index, GLshort* v);
inline void gl_wrap_context_glVertexAttrib4Nub(gl_wrap_context* ctx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
inline void gl_wrap_context_glVertexAttrib4Nubv(gl_wrap_context* ctx, GLuint index, GLubyte* v);
inline void gl_wrap_context_glVertexAttrib4Nuiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glVertexAttrib4Nusv(gl_wrap_context* ctx, GLuint index, GLushort* v);
inline void gl_wrap_context_glVertexAttrib4bv(gl_wrap_context* ctx, GLuint index, GLbyte* v);
inline void gl_wrap_context_glVertexAttrib4d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
inline void gl_wrap_context_glVertexAttrib4dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttrib4f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
inline void gl_wrap_context_glVertexAttrib4fv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glVertexAttrib4iv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttrib4s(gl_wrap_context* ctx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
inline void gl_wrap_context_glVertexAttrib4sv(gl_wrap_context* ctx, GLuint index, GLshort* v);
inline void gl_wrap_context_glVertexAttrib4ubv(gl_wrap_context* ctx, GLuint index, GLubyte* v);
inline void gl_wrap_context_glVertexAttrib4uiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glVertexAttrib4usv(gl_wrap_context* ctx, GLuint index, GLushort* v);
inline void gl_wrap_context_glVertexAttribPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void* pointer);
inline void gl_wrap_context_glUniformMatrix2x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix3x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix2x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix4x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix3x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glUniformMatrix4x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glColorMaski(gl_wrap_context* ctx, GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
inline void gl_wrap_context_glGetBooleani_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLboolean* data);
inline void gl_wrap_context_glGetIntegeri_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint* data);
inline void gl_wrap_context_glEnablei(gl_wrap_context* ctx, GLenum target, GLuint index);
inline void gl_wrap_context_glDisablei(gl_wrap_context* ctx, GLenum target, GLuint index);
inline GLboolean gl_wrap_context_glIsEnabledi(gl_wrap_context* ctx, GLenum target, GLuint index);
inline void gl_wrap_context_glBeginTransformFeedback(gl_wrap_context* ctx, GLenum primitiveMode);
inline void gl_wrap_context_glEndTransformFeedback(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glBindBufferRange(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
inline void gl_wrap_context_glBindBufferBase(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer);
inline void gl_wrap_context_glTransformFeedbackVaryings(gl_wrap_context* ctx, GLuint program, GLsizei count, GLchar** varyings, GLenum bufferMode);
inline void gl_wrap_context_glGetTransformFeedbackVarying(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name);
inline void gl_wrap_context_glClampColor(gl_wrap_context* ctx, GLenum target, GLenum clamp);
inline void gl_wrap_context_glBeginConditionalRender(gl_wrap_context* ctx, GLuint id, GLenum mode);
inline void gl_wrap_context_glEndConditionalRender(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glVertexAttribIPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glGetVertexAttribIiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetVertexAttribIuiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLuint* params);
inline void gl_wrap_context_glVertexAttribI1i(gl_wrap_context* ctx, GLuint index, GLint x);
inline void gl_wrap_context_glVertexAttribI2i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y);
inline void gl_wrap_context_glVertexAttribI3i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y, GLint z);
inline void gl_wrap_context_glVertexAttribI4i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y, GLint z, GLint w);
inline void gl_wrap_context_glVertexAttribI1ui(gl_wrap_context* ctx, GLuint index, GLuint x);
inline void gl_wrap_context_glVertexAttribI2ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y);
inline void gl_wrap_context_glVertexAttribI3ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y, GLuint z);
inline void gl_wrap_context_glVertexAttribI4ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
inline void gl_wrap_context_glVertexAttribI1iv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttribI2iv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttribI3iv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttribI4iv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glVertexAttribI1uiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glVertexAttribI2uiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glVertexAttribI3uiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glVertexAttribI4uiv(gl_wrap_context* ctx, GLuint index, GLuint* v);
inline void gl_wrap_context_glVertexAttribI4bv(gl_wrap_context* ctx, GLuint index, GLbyte* v);
inline void gl_wrap_context_glVertexAttribI4sv(gl_wrap_context* ctx, GLuint index, GLshort* v);
inline void gl_wrap_context_glVertexAttribI4ubv(gl_wrap_context* ctx, GLuint index, GLubyte* v);
inline void gl_wrap_context_glVertexAttribI4usv(gl_wrap_context* ctx, GLuint index, GLushort* v);
inline void gl_wrap_context_glGetUniformuiv(gl_wrap_context* ctx, GLuint program, GLint location, GLuint* params);
inline void gl_wrap_context_glBindFragDataLocation(gl_wrap_context* ctx, GLuint program, GLuint color, GLchar* name);
inline GLint gl_wrap_context_glGetFragDataLocation(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glUniform1ui(gl_wrap_context* ctx, GLint location, GLuint v0);
inline void gl_wrap_context_glUniform2ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1);
inline void gl_wrap_context_glUniform3ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2);
inline void gl_wrap_context_glUniform4ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
inline void gl_wrap_context_glUniform1uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glUniform2uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glUniform3uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glUniform4uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glTexParameterIiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glTexParameterIuiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLuint* params);
inline void gl_wrap_context_glGetTexParameterIiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetTexParameterIuiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLuint* params);
inline void gl_wrap_context_glClearBufferiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLint* value);
inline void gl_wrap_context_glClearBufferuiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLuint* value);
inline void gl_wrap_context_glClearBufferfv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat* value);
inline void gl_wrap_context_glClearBufferfi(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
inline GLubyte* gl_wrap_context_glGetStringi(gl_wrap_context* ctx, GLenum name, GLuint index);
inline GLboolean gl_wrap_context_glIsRenderbuffer(gl_wrap_context* ctx, GLuint renderbuffer);
inline void gl_wrap_context_glBindRenderbuffer(gl_wrap_context* ctx, GLenum target, GLuint renderbuffer);
inline void gl_wrap_context_glDeleteRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers);
inline void gl_wrap_context_glGenRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers);
inline void gl_wrap_context_glRenderbufferStorage(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
inline void gl_wrap_context_glGetRenderbufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline GLboolean gl_wrap_context_glIsFramebuffer(gl_wrap_context* ctx, GLuint framebuffer);
inline void gl_wrap_context_glBindFramebuffer(gl_wrap_context* ctx, GLenum target, GLuint framebuffer);
inline void gl_wrap_context_glDeleteFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers);
inline void gl_wrap_context_glGenFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers);
inline GLenum gl_wrap_context_glCheckFramebufferStatus(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glFramebufferTexture1D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
inline void gl_wrap_context_glFramebufferTexture2D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
inline void gl_wrap_context_glFramebufferTexture3D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
inline void gl_wrap_context_glFramebufferRenderbuffer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
inline void gl_wrap_context_glGetFramebufferAttachmentParameteriv(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum pname, GLint* params);
inline void gl_wrap_context_glGenerateMipmap(gl_wrap_context* ctx, GLenum target);
inline void gl_wrap_context_glBlitFramebuffer(gl_wrap_context* ctx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
inline void gl_wrap_context_glRenderbufferStorageMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
inline void gl_wrap_context_glFramebufferTextureLayer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
inline void gl_wrap_context_glMapBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
inline void gl_wrap_context_glFlushMappedBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length);
inline void gl_wrap_context_glBindVertexArray(gl_wrap_context* ctx, GLuint array);
inline void gl_wrap_context_glDeleteVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays);
inline void gl_wrap_context_glGenVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays);
inline GLboolean gl_wrap_context_glIsVertexArray(gl_wrap_context* ctx, GLuint array);
inline void gl_wrap_context_glDrawArraysInstanced(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
inline void gl_wrap_context_glDrawElementsInstanced(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount);
inline void gl_wrap_context_glTexBuffer(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLuint buffer);
inline void gl_wrap_context_glPrimitiveRestartIndex(gl_wrap_context* ctx, GLuint index);
inline void gl_wrap_context_glCopyBufferSubData(gl_wrap_context* ctx, GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
inline void gl_wrap_context_glGetUniformIndices(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLchar** uniformNames, GLuint* uniformIndices);
inline void gl_wrap_context_glGetActiveUniformsiv(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLuint* uniformIndices, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetActiveUniformName(gl_wrap_context* ctx, GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName);
inline GLuint gl_wrap_context_glGetUniformBlockIndex(gl_wrap_context* ctx, GLuint program, GLchar* uniformBlockName);
inline void gl_wrap_context_glGetActiveUniformBlockiv(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetActiveUniformBlockName(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName);
inline void gl_wrap_context_glUniformBlockBinding(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
inline void gl_wrap_context_glDrawElementsBaseVertex(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex);
inline void gl_wrap_context_glDrawRangeElementsBaseVertex(gl_wrap_context* ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices, GLint basevertex);
inline void gl_wrap_context_glDrawElementsInstancedBaseVertex(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount, GLint basevertex);
inline void gl_wrap_context_glMultiDrawElementsBaseVertex(gl_wrap_context* ctx, GLenum mode, GLsizei* count, GLenum type, void** indices, GLsizei drawcount, GLint* basevertex);
inline void gl_wrap_context_glProvokingVertex(gl_wrap_context* ctx, GLenum mode);
inline GLsync gl_wrap_context_glFenceSync(gl_wrap_context* ctx, GLenum condition, GLbitfield flags);
inline GLboolean gl_wrap_context_glIsSync(gl_wrap_context* ctx, GLsync sync);
inline void gl_wrap_context_glDeleteSync(gl_wrap_context* ctx, GLsync sync);
inline GLenum gl_wrap_context_glClientWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout);
inline void gl_wrap_context_glWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout);
inline void gl_wrap_context_glGetInteger64v(gl_wrap_context* ctx, GLenum pname, GLint64* data);
inline void gl_wrap_context_glGetSynciv(gl_wrap_context* ctx, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values);
inline void gl_wrap_context_glGetInteger64i_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint64* data);
inline void gl_wrap_context_glGetBufferParameteri64v(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint64* params);
inline void gl_wrap_context_glFramebufferTexture(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLuint texture, GLint level);
inline void gl_wrap_context_glTexImage2DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
inline void gl_wrap_context_glTexImage3DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
inline void gl_wrap_context_glGetMultisamplefv(gl_wrap_context* ctx, GLenum pname, GLuint index, GLfloat* val);
inline void gl_wrap_context_glSampleMaski(gl_wrap_context* ctx, GLuint maskNumber, GLbitfield mask);
inline void gl_wrap_context_glBindFragDataLocationIndexed(gl_wrap_context* ctx, GLuint program, GLuint colorNumber, GLuint index, GLchar* name);
inline GLint gl_wrap_context_glGetFragDataIndex(gl_wrap_context* ctx, GLuint program, GLchar* name);
inline void gl_wrap_context_glGenSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers);
inline void gl_wrap_context_glDeleteSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers);
inline GLboolean gl_wrap_context_glIsSampler(gl_wrap_context* ctx, GLuint sampler);
inline void gl_wrap_context_glBindSampler(gl_wrap_context* ctx, GLuint unit, GLuint sampler);
inline void gl_wrap_context_glSamplerParameteri(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint param);
inline void gl_wrap_context_glSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* param);
inline void gl_wrap_context_glSamplerParameterf(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat param);
inline void gl_wrap_context_glSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* param);
inline void gl_wrap_context_glSamplerParameterIiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* param);
inline void gl_wrap_context_glSamplerParameterIuiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLuint* param);
inline void gl_wrap_context_glGetSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetSamplerParameterIiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* params);
inline void gl_wrap_context_glGetSamplerParameterIuiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLuint* params);
inline void gl_wrap_context_glQueryCounter(gl_wrap_context* ctx, GLuint id, GLenum target);
inline void gl_wrap_context_glGetQueryObjecti64v(gl_wrap_context* ctx, GLuint id, GLenum pname, GLint64* params);
inline void gl_wrap_context_glGetQueryObjectui64v(gl_wrap_context* ctx, GLuint id, GLenum pname, GLuint64* params);
inline void gl_wrap_context_glVertexAttribDivisor(gl_wrap_context* ctx, GLuint index, GLuint divisor);
inline void gl_wrap_context_glVertexAttribP1ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
inline void gl_wrap_context_glVertexAttribP1uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value);
inline void gl_wrap_context_glVertexAttribP2ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
inline void gl_wrap_context_glVertexAttribP2uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value);
inline void gl_wrap_context_glVertexAttribP3ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
inline void gl_wrap_context_glVertexAttribP3uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value);
inline void gl_wrap_context_glVertexAttribP4ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value);
inline void gl_wrap_context_glVertexAttribP4uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value);
inline void gl_wrap_context_glVertexP2ui(gl_wrap_context* ctx, GLenum type, GLuint value);
inline void gl_wrap_context_glVertexP2uiv(gl_wrap_context* ctx, GLenum type, GLuint* value);
inline void gl_wrap_context_glVertexP3ui(gl_wrap_context* ctx, GLenum type, GLuint value);
inline void gl_wrap_context_glVertexP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* value);
inline void gl_wrap_context_glVertexP4ui(gl_wrap_context* ctx, GLenum type, GLuint value);
inline void gl_wrap_context_glVertexP4uiv(gl_wrap_context* ctx, GLenum type, GLuint* value);
inline void gl_wrap_context_glTexCoordP1ui(gl_wrap_context* ctx, GLenum type, GLuint coords);
inline void gl_wrap_context_glTexCoordP1uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords);
inline void gl_wrap_context_glTexCoordP2ui(gl_wrap_context* ctx, GLenum type, GLuint coords);
inline void gl_wrap_context_glTexCoordP2uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords);
inline void gl_wrap_context_glTexCoordP3ui(gl_wrap_context* ctx, GLenum type, GLuint coords);
inline void gl_wrap_context_glTexCoordP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords);
inline void gl_wrap_context_glTexCoordP4ui(gl_wrap_context* ctx, GLenum type, GLuint coords);
inline void gl_wrap_context_glTexCoordP4uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords);
inline void gl_wrap_context_glMultiTexCoordP1ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords);
inline void gl_wrap_context_glMultiTexCoordP1uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords);
inline void gl_wrap_context_glMultiTexCoordP2ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords);
inline void gl_wrap_context_glMultiTexCoordP2uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords);
inline void gl_wrap_context_glMultiTexCoordP3ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords);
inline void gl_wrap_context_glMultiTexCoordP3uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords);
inline void gl_wrap_context_glMultiTexCoordP4ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords);
inline void gl_wrap_context_glMultiTexCoordP4uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords);
inline void gl_wrap_context_glNormalP3ui(gl_wrap_context* ctx, GLenum type, GLuint coords);
inline void gl_wrap_context_glNormalP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords);
inline void gl_wrap_context_glColorP3ui(gl_wrap_context* ctx, GLenum type, GLuint color);
inline void gl_wrap_context_glColorP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* color);
inline void gl_wrap_context_glColorP4ui(gl_wrap_context* ctx, GLenum type, GLuint color);
inline void gl_wrap_context_glColorP4uiv(gl_wrap_context* ctx, GLenum type, GLuint* color);
inline void gl_wrap_context_glSecondaryColorP3ui(gl_wrap_context* ctx, GLenum type, GLuint color);
inline void gl_wrap_context_glSecondaryColorP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* color);
inline void gl_wrap_context_glMinSampleShading(gl_wrap_context* ctx, GLfloat value);
inline void gl_wrap_context_glBlendEquationi(gl_wrap_context* ctx, GLuint buf, GLenum mode);
inline void gl_wrap_context_glBlendEquationSeparatei(gl_wrap_context* ctx, GLuint buf, GLenum modeRGB, GLenum modeAlpha);
inline void gl_wrap_context_glBlendFunci(gl_wrap_context* ctx, GLuint buf, GLenum src, GLenum dst);
inline void gl_wrap_context_glBlendFuncSeparatei(gl_wrap_context* ctx, GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
inline void gl_wrap_context_glDrawArraysIndirect(gl_wrap_context* ctx, GLenum mode, void* indirect);
inline void gl_wrap_context_glDrawElementsIndirect(gl_wrap_context* ctx, GLenum mode, GLenum type, void* indirect);
inline void gl_wrap_context_glUniform1d(gl_wrap_context* ctx, GLint location, GLdouble x);
inline void gl_wrap_context_glUniform2d(gl_wrap_context* ctx, GLint location, GLdouble x, GLdouble y);
inline void gl_wrap_context_glUniform3d(gl_wrap_context* ctx, GLint location, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glUniform4d(gl_wrap_context* ctx, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
inline void gl_wrap_context_glUniform1dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glUniform2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glUniform3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glUniform4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix2x3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix2x4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix3x2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix3x4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix4x2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glUniformMatrix4x3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glGetUniformdv(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble* params);
inline GLint gl_wrap_context_glGetSubroutineUniformLocation(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLchar* name);
inline GLuint gl_wrap_context_glGetSubroutineIndex(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLchar* name);
inline void gl_wrap_context_glGetActiveSubroutineUniformiv(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values);
inline void gl_wrap_context_glGetActiveSubroutineUniformName(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name);
inline void gl_wrap_context_glGetActiveSubroutineName(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name);
inline void gl_wrap_context_glUniformSubroutinesuiv(gl_wrap_context* ctx, GLenum shadertype, GLsizei count, GLuint* indices);
inline void gl_wrap_context_glGetUniformSubroutineuiv(gl_wrap_context* ctx, GLenum shadertype, GLint location, GLuint* params);
inline void gl_wrap_context_glGetProgramStageiv(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLenum pname, GLint* values);
inline void gl_wrap_context_glPatchParameteri(gl_wrap_context* ctx, GLenum pname, GLint value);
inline void gl_wrap_context_glPatchParameterfv(gl_wrap_context* ctx, GLenum pname, GLfloat* values);
inline void gl_wrap_context_glBindTransformFeedback(gl_wrap_context* ctx, GLenum target, GLuint id);
inline void gl_wrap_context_glDeleteTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline void gl_wrap_context_glGenTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids);
inline GLboolean gl_wrap_context_glIsTransformFeedback(gl_wrap_context* ctx, GLuint id);
inline void gl_wrap_context_glPauseTransformFeedback(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glResumeTransformFeedback(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glDrawTransformFeedback(gl_wrap_context* ctx, GLenum mode, GLuint id);
inline void gl_wrap_context_glDrawTransformFeedbackStream(gl_wrap_context* ctx, GLenum mode, GLuint id, GLuint stream);
inline void gl_wrap_context_glBeginQueryIndexed(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint id);
inline void gl_wrap_context_glEndQueryIndexed(gl_wrap_context* ctx, GLenum target, GLuint index);
inline void gl_wrap_context_glGetQueryIndexediv(gl_wrap_context* ctx, GLenum target, GLuint index, GLenum pname, GLint* params);
inline void gl_wrap_context_glReleaseShaderCompiler(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glShaderBinary(gl_wrap_context* ctx, GLsizei count, GLuint* shaders, GLenum binaryformat, void* binary, GLsizei length);
inline void gl_wrap_context_glGetShaderPrecisionFormat(gl_wrap_context* ctx, GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
inline void gl_wrap_context_glDepthRangef(gl_wrap_context* ctx, GLfloat n, GLfloat f);
inline void gl_wrap_context_glClearDepthf(gl_wrap_context* ctx, GLfloat d);
inline void gl_wrap_context_glGetProgramBinary(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary);
inline void gl_wrap_context_glProgramBinary(gl_wrap_context* ctx, GLuint program, GLenum binaryFormat, void* binary, GLsizei length);
inline void gl_wrap_context_glProgramParameteri(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint value);
inline void gl_wrap_context_glUseProgramStages(gl_wrap_context* ctx, GLuint pipeline, GLbitfield stages, GLuint program);
inline void gl_wrap_context_glActiveShaderProgram(gl_wrap_context* ctx, GLuint pipeline, GLuint program);
inline GLuint gl_wrap_context_glCreateShaderProgramv(gl_wrap_context* ctx, GLenum type, GLsizei count, GLchar** strings);
inline void gl_wrap_context_glBindProgramPipeline(gl_wrap_context* ctx, GLuint pipeline);
inline void gl_wrap_context_glDeleteProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines);
inline void gl_wrap_context_glGenProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines);
inline GLboolean gl_wrap_context_glIsProgramPipeline(gl_wrap_context* ctx, GLuint pipeline);
inline void gl_wrap_context_glGetProgramPipelineiv(gl_wrap_context* ctx, GLuint pipeline, GLenum pname, GLint* params);
inline void gl_wrap_context_glProgramUniform1i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0);
inline void gl_wrap_context_glProgramUniform1iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform1f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0);
inline void gl_wrap_context_glProgramUniform1fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform1d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0);
inline void gl_wrap_context_glProgramUniform1dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glProgramUniform1ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0);
inline void gl_wrap_context_glProgramUniform1uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform2i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1);
inline void gl_wrap_context_glProgramUniform2iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform2f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1);
inline void gl_wrap_context_glProgramUniform2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform2d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0, GLdouble v1);
inline void gl_wrap_context_glProgramUniform2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glProgramUniform2ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1);
inline void gl_wrap_context_glProgramUniform2uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform3i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
inline void gl_wrap_context_glProgramUniform3iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform3f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
inline void gl_wrap_context_glProgramUniform3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform3d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
inline void gl_wrap_context_glProgramUniform3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glProgramUniform3ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
inline void gl_wrap_context_glProgramUniform3uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniform4i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
inline void gl_wrap_context_glProgramUniform4iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value);
inline void gl_wrap_context_glProgramUniform4f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
inline void gl_wrap_context_glProgramUniform4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value);
inline void gl_wrap_context_glProgramUniform4d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
inline void gl_wrap_context_glProgramUniform4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value);
inline void gl_wrap_context_glProgramUniform4ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
inline void gl_wrap_context_glProgramUniform4uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value);
inline void gl_wrap_context_glProgramUniformMatrix2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix2x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix3x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix2x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix4x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix3x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix4x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value);
inline void gl_wrap_context_glProgramUniformMatrix2x3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix3x2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix2x4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix4x2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix3x4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glProgramUniformMatrix4x3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value);
inline void gl_wrap_context_glValidateProgramPipeline(gl_wrap_context* ctx, GLuint pipeline);
inline void gl_wrap_context_glGetProgramPipelineInfoLog(gl_wrap_context* ctx, GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
inline void gl_wrap_context_glVertexAttribL1d(gl_wrap_context* ctx, GLuint index, GLdouble x);
inline void gl_wrap_context_glVertexAttribL2d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y);
inline void gl_wrap_context_glVertexAttribL3d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z);
inline void gl_wrap_context_glVertexAttribL4d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
inline void gl_wrap_context_glVertexAttribL1dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttribL2dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttribL3dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttribL4dv(gl_wrap_context* ctx, GLuint index, GLdouble* v);
inline void gl_wrap_context_glVertexAttribLPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLsizei stride, void* pointer);
inline void gl_wrap_context_glGetVertexAttribLdv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLdouble* params);
inline void gl_wrap_context_glViewportArrayv(gl_wrap_context* ctx, GLuint first, GLsizei count, GLfloat* v);
inline void gl_wrap_context_glViewportIndexedf(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
inline void gl_wrap_context_glViewportIndexedfv(gl_wrap_context* ctx, GLuint index, GLfloat* v);
inline void gl_wrap_context_glScissorArrayv(gl_wrap_context* ctx, GLuint first, GLsizei count, GLint* v);
inline void gl_wrap_context_glScissorIndexed(gl_wrap_context* ctx, GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
inline void gl_wrap_context_glScissorIndexedv(gl_wrap_context* ctx, GLuint index, GLint* v);
inline void gl_wrap_context_glDepthRangeArrayv(gl_wrap_context* ctx, GLuint first, GLsizei count, GLdouble* v);
inline void gl_wrap_context_glDepthRangeIndexed(gl_wrap_context* ctx, GLuint index, GLdouble n, GLdouble f);
inline void gl_wrap_context_glGetFloati_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLfloat* data);
inline void gl_wrap_context_glGetDoublei_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLdouble* data);
inline void gl_wrap_context_glDrawArraysInstancedBaseInstance(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
inline void gl_wrap_context_glDrawElementsInstancedBaseInstance(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount, GLuint baseinstance);
inline void gl_wrap_context_glDrawElementsInstancedBaseVertexBaseInstance(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
inline void gl_wrap_context_glGetInternalformativ(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params);
inline void gl_wrap_context_glGetActiveAtomicCounterBufferiv(gl_wrap_context* ctx, GLuint program, GLuint bufferIndex, GLenum pname, GLint* params);
inline void gl_wrap_context_glBindImageTexture(gl_wrap_context* ctx, GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
inline void gl_wrap_context_glMemoryBarrier(gl_wrap_context* ctx, GLbitfield barriers);
inline void gl_wrap_context_glTexStorage1D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
inline void gl_wrap_context_glTexStorage2D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
inline void gl_wrap_context_glTexStorage3D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
inline void gl_wrap_context_glDrawTransformFeedbackInstanced(gl_wrap_context* ctx, GLenum mode, GLuint id, GLsizei instancecount);
inline void gl_wrap_context_glDrawTransformFeedbackStreamInstanced(gl_wrap_context* ctx, GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
inline void gl_wrap_context_glClearBufferData(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum format, GLenum type, void* data);
inline void gl_wrap_context_glClearBufferSubData(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, void* data);
inline void gl_wrap_context_glDispatchCompute(gl_wrap_context* ctx, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
inline void gl_wrap_context_glDispatchComputeIndirect(gl_wrap_context* ctx, GLintptr indirect);
inline void gl_wrap_context_glCopyImageSubData(gl_wrap_context* ctx, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
inline void gl_wrap_context_glFramebufferParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param);
inline void gl_wrap_context_glGetFramebufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params);
inline void gl_wrap_context_glGetInternalformati64v(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params);
inline void gl_wrap_context_glInvalidateTexSubImage(gl_wrap_context* ctx, GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
inline void gl_wrap_context_glInvalidateTexImage(gl_wrap_context* ctx, GLuint texture, GLint level);
inline void gl_wrap_context_glInvalidateBufferSubData(gl_wrap_context* ctx, GLuint buffer, GLintptr offset, GLsizeiptr length);
inline void gl_wrap_context_glInvalidateBufferData(gl_wrap_context* ctx, GLuint buffer);
inline void gl_wrap_context_glInvalidateFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments);
inline void gl_wrap_context_glInvalidateSubFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height);
inline void gl_wrap_context_glMultiDrawArraysIndirect(gl_wrap_context* ctx, GLenum mode, void* indirect, GLsizei drawcount, GLsizei stride);
inline void gl_wrap_context_glMultiDrawElementsIndirect(gl_wrap_context* ctx, GLenum mode, GLenum type, void* indirect, GLsizei drawcount, GLsizei stride);
inline void gl_wrap_context_glGetProgramInterfaceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLenum pname, GLint* params);
inline GLuint gl_wrap_context_glGetProgramResourceIndex(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name);
inline void gl_wrap_context_glGetProgramResourceName(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name);
inline void gl_wrap_context_glGetProgramResourceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params);
inline GLint gl_wrap_context_glGetProgramResourceLocation(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name);
inline GLint gl_wrap_context_glGetProgramResourceLocationIndex(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name);
inline void gl_wrap_context_glShaderStorageBlockBinding(gl_wrap_context* ctx, GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
inline void gl_wrap_context_glTexBufferRange(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
inline void gl_wrap_context_glTexStorage2DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
inline void gl_wrap_context_glTexStorage3DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
inline void gl_wrap_context_glTextureView(gl_wrap_context* ctx, GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
inline void gl_wrap_context_glBindVertexBuffer(gl_wrap_context* ctx, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
inline void gl_wrap_context_glVertexAttribFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
inline void gl_wrap_context_glVertexAttribIFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
inline void gl_wrap_context_glVertexAttribLFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
inline void gl_wrap_context_glVertexAttribBinding(gl_wrap_context* ctx, GLuint attribindex, GLuint bindingindex);
inline void gl_wrap_context_glVertexBindingDivisor(gl_wrap_context* ctx, GLuint bindingindex, GLuint divisor);
inline void gl_wrap_context_glDebugMessageControl(gl_wrap_context* ctx, GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint* ids, GLboolean enabled);
inline void gl_wrap_context_glDebugMessageInsert(gl_wrap_context* ctx, GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar* buf);
inline void gl_wrap_context_glDebugMessageCallback(gl_wrap_context* ctx, GLDEBUGPROC callback, void* userParam);
inline GLuint gl_wrap_context_glGetDebugMessageLog(gl_wrap_context* ctx, GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog);
inline void gl_wrap_context_glPushDebugGroup(gl_wrap_context* ctx, GLenum source, GLuint id, GLsizei length, GLchar* message);
inline void gl_wrap_context_glPopDebugGroup(gl_wrap_context* ctxvoid);
inline void gl_wrap_context_glObjectLabel(gl_wrap_context* ctx, GLenum identifier, GLuint name, GLsizei length, GLchar* label);
inline void gl_wrap_context_glGetObjectLabel(gl_wrap_context* ctx, GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label);
inline void gl_wrap_context_glObjectPtrLabel(gl_wrap_context* ctx, void* ptr, GLsizei length, GLchar* label);
inline void gl_wrap_context_glGetObjectPtrLabel(gl_wrap_context* ctx, void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label);
inline void gl_wrap_context_glBufferStorage(gl_wrap_context* ctx, GLenum target, GLsizeiptr size, void* data, GLbitfield flags);
inline void gl_wrap_context_glClearTexImage(gl_wrap_context* ctx, GLuint texture, GLint level, GLenum format, GLenum type, void* data);
inline void gl_wrap_context_glClearTexSubImage(gl_wrap_context* ctx, GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* data);
inline void gl_wrap_context_glBindBuffersBase(gl_wrap_context* ctx, GLenum target, GLuint first, GLsizei count, GLuint* buffers);
inline void gl_wrap_context_glBindBuffersRange(gl_wrap_context* ctx, GLenum target, GLuint first, GLsizei count, GLuint* buffers, GLintptr* offsets, GLsizeiptr* sizes);
inline void gl_wrap_context_glBindTextures(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* textures);
inline void gl_wrap_context_glBindSamplers(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* samplers);
inline void gl_wrap_context_glBindImageTextures(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* textures);
inline void gl_wrap_context_glBindVertexBuffers(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* buffers, GLintptr* offsets, GLsizei* strides);


// Argument struct definitions for batch function handlers.
typedef struct {
	GLenum mode;
} gl_wrap_handler_glCullFace_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glFrontFace_args;

typedef struct {
	GLenum target;
	GLenum mode;
} gl_wrap_handler_glHint_args;

typedef struct {
	GLfloat width;
} gl_wrap_handler_glLineWidth_args;

typedef struct {
	GLfloat size;
} gl_wrap_handler_glPointSize_args;

typedef struct {
	GLenum face;
	GLenum mode;
} gl_wrap_handler_glPolygonMode_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glScissor_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glTexParameterf_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glTexParameterfv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glTexParameteri_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glTexParameteriv_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint internalformat;
	GLsizei width;
	GLint border;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexImage1D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint internalformat;
	GLsizei width;
	GLsizei height;
	GLint border;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexImage2D_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glDrawBuffer_args;

typedef struct {
	GLbitfield mask;
} gl_wrap_handler_glClear_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} gl_wrap_handler_glClearColor_args;

typedef struct {
	GLint s;
} gl_wrap_handler_glClearStencil_args;

typedef struct {
	GLdouble depth;
} gl_wrap_handler_glClearDepth_args;

typedef struct {
	GLuint mask;
} gl_wrap_handler_glStencilMask_args;

typedef struct {
	GLboolean red;
	GLboolean green;
	GLboolean blue;
	GLboolean alpha;
} gl_wrap_handler_glColorMask_args;

typedef struct {
	GLboolean flag;
} gl_wrap_handler_glDepthMask_args;

typedef struct {
	GLenum cap;
} gl_wrap_handler_glDisable_args;

typedef struct {
	GLenum cap;
} gl_wrap_handler_glEnable_args;

typedef struct {
} gl_wrap_handler_glFinish_args;

typedef struct {
} gl_wrap_handler_glFlush_args;

typedef struct {
	GLenum sfactor;
	GLenum dfactor;
} gl_wrap_handler_glBlendFunc_args;

typedef struct {
	GLenum opcode;
} gl_wrap_handler_glLogicOp_args;

typedef struct {
	GLenum func;
	GLint ref;
	GLuint mask;
} gl_wrap_handler_glStencilFunc_args;

typedef struct {
	GLenum fail;
	GLenum zfail;
	GLenum zpass;
} gl_wrap_handler_glStencilOp_args;

typedef struct {
	GLenum func;
} gl_wrap_handler_glDepthFunc_args;

typedef struct {
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glPixelStoref_args;

typedef struct {
	GLenum pname;
	GLint param;
} gl_wrap_handler_glPixelStorei_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glReadBuffer_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glReadPixels_args;

typedef struct {
	GLenum pname;
	GLboolean* data;
} gl_wrap_handler_glGetBooleanv_args;

typedef struct {
	GLenum pname;
	GLdouble* data;
} gl_wrap_handler_glGetDoublev_args;

typedef struct {
	GLenum pname;
	GLfloat* data;
} gl_wrap_handler_glGetFloatv_args;

typedef struct {
	GLenum pname;
	GLint* data;
} gl_wrap_handler_glGetIntegerv_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glGetTexImage_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetTexParameterfv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexParameteriv_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetTexLevelParameterfv_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexLevelParameteriv_args;

typedef struct {
	GLdouble near;
	GLdouble far;
} gl_wrap_handler_glDepthRange_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glViewport_args;

typedef struct {
	GLuint list;
	GLenum mode;
} gl_wrap_handler_glNewList_args;

typedef struct {
} gl_wrap_handler_glEndList_args;

typedef struct {
	GLuint list;
} gl_wrap_handler_glCallList_args;

typedef struct {
	GLsizei n;
	GLenum type;
	void* lists;
} gl_wrap_handler_glCallLists_args;

typedef struct {
	GLuint list;
	GLsizei range;
} gl_wrap_handler_glDeleteLists_args;

typedef struct {
	GLuint base;
} gl_wrap_handler_glListBase_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glBegin_args;

typedef struct {
	GLsizei width;
	GLsizei height;
	GLfloat xorig;
	GLfloat yorig;
	GLfloat xmove;
	GLfloat ymove;
	GLubyte* bitmap;
} gl_wrap_handler_glBitmap_args;

typedef struct {
	GLbyte red;
	GLbyte green;
	GLbyte blue;
} gl_wrap_handler_glColor3b_args;

typedef struct {
	GLbyte* v;
} gl_wrap_handler_glColor3bv_args;

typedef struct {
	GLdouble red;
	GLdouble green;
	GLdouble blue;
} gl_wrap_handler_glColor3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glColor3dv_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
} gl_wrap_handler_glColor3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glColor3fv_args;

typedef struct {
	GLint red;
	GLint green;
	GLint blue;
} gl_wrap_handler_glColor3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glColor3iv_args;

typedef struct {
	GLshort red;
	GLshort green;
	GLshort blue;
} gl_wrap_handler_glColor3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glColor3sv_args;

typedef struct {
	GLubyte red;
	GLubyte green;
	GLubyte blue;
} gl_wrap_handler_glColor3ub_args;

typedef struct {
	GLubyte* v;
} gl_wrap_handler_glColor3ubv_args;

typedef struct {
	GLuint red;
	GLuint green;
	GLuint blue;
} gl_wrap_handler_glColor3ui_args;

typedef struct {
	GLuint* v;
} gl_wrap_handler_glColor3uiv_args;

typedef struct {
	GLushort red;
	GLushort green;
	GLushort blue;
} gl_wrap_handler_glColor3us_args;

typedef struct {
	GLushort* v;
} gl_wrap_handler_glColor3usv_args;

typedef struct {
	GLbyte red;
	GLbyte green;
	GLbyte blue;
	GLbyte alpha;
} gl_wrap_handler_glColor4b_args;

typedef struct {
	GLbyte* v;
} gl_wrap_handler_glColor4bv_args;

typedef struct {
	GLdouble red;
	GLdouble green;
	GLdouble blue;
	GLdouble alpha;
} gl_wrap_handler_glColor4d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glColor4dv_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} gl_wrap_handler_glColor4f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glColor4fv_args;

typedef struct {
	GLint red;
	GLint green;
	GLint blue;
	GLint alpha;
} gl_wrap_handler_glColor4i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glColor4iv_args;

typedef struct {
	GLshort red;
	GLshort green;
	GLshort blue;
	GLshort alpha;
} gl_wrap_handler_glColor4s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glColor4sv_args;

typedef struct {
	GLubyte red;
	GLubyte green;
	GLubyte blue;
	GLubyte alpha;
} gl_wrap_handler_glColor4ub_args;

typedef struct {
	GLubyte* v;
} gl_wrap_handler_glColor4ubv_args;

typedef struct {
	GLuint red;
	GLuint green;
	GLuint blue;
	GLuint alpha;
} gl_wrap_handler_glColor4ui_args;

typedef struct {
	GLuint* v;
} gl_wrap_handler_glColor4uiv_args;

typedef struct {
	GLushort red;
	GLushort green;
	GLushort blue;
	GLushort alpha;
} gl_wrap_handler_glColor4us_args;

typedef struct {
	GLushort* v;
} gl_wrap_handler_glColor4usv_args;

typedef struct {
	GLboolean flag;
} gl_wrap_handler_glEdgeFlag_args;

typedef struct {
	GLboolean* flag;
} gl_wrap_handler_glEdgeFlagv_args;

typedef struct {
} gl_wrap_handler_glEnd_args;

typedef struct {
	GLdouble c;
} gl_wrap_handler_glIndexd_args;

typedef struct {
	GLdouble* c;
} gl_wrap_handler_glIndexdv_args;

typedef struct {
	GLfloat c;
} gl_wrap_handler_glIndexf_args;

typedef struct {
	GLfloat* c;
} gl_wrap_handler_glIndexfv_args;

typedef struct {
	GLint c;
} gl_wrap_handler_glIndexi_args;

typedef struct {
	GLint* c;
} gl_wrap_handler_glIndexiv_args;

typedef struct {
	GLshort c;
} gl_wrap_handler_glIndexs_args;

typedef struct {
	GLshort* c;
} gl_wrap_handler_glIndexsv_args;

typedef struct {
	GLbyte nx;
	GLbyte ny;
	GLbyte nz;
} gl_wrap_handler_glNormal3b_args;

typedef struct {
	GLbyte* v;
} gl_wrap_handler_glNormal3bv_args;

typedef struct {
	GLdouble nx;
	GLdouble ny;
	GLdouble nz;
} gl_wrap_handler_glNormal3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glNormal3dv_args;

typedef struct {
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
} gl_wrap_handler_glNormal3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glNormal3fv_args;

typedef struct {
	GLint nx;
	GLint ny;
	GLint nz;
} gl_wrap_handler_glNormal3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glNormal3iv_args;

typedef struct {
	GLshort nx;
	GLshort ny;
	GLshort nz;
} gl_wrap_handler_glNormal3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glNormal3sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
} gl_wrap_handler_glRasterPos2d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glRasterPos2dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
} gl_wrap_handler_glRasterPos2f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glRasterPos2fv_args;

typedef struct {
	GLint x;
	GLint y;
} gl_wrap_handler_glRasterPos2i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glRasterPos2iv_args;

typedef struct {
	GLshort x;
	GLshort y;
} gl_wrap_handler_glRasterPos2s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glRasterPos2sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glRasterPos3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glRasterPos3dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glRasterPos3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glRasterPos3fv_args;

typedef struct {
	GLint x;
	GLint y;
	GLint z;
} gl_wrap_handler_glRasterPos3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glRasterPos3iv_args;

typedef struct {
	GLshort x;
	GLshort y;
	GLshort z;
} gl_wrap_handler_glRasterPos3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glRasterPos3sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble w;
} gl_wrap_handler_glRasterPos4d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glRasterPos4dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
} gl_wrap_handler_glRasterPos4f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glRasterPos4fv_args;

typedef struct {
	GLint x;
	GLint y;
	GLint z;
	GLint w;
} gl_wrap_handler_glRasterPos4i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glRasterPos4iv_args;

typedef struct {
	GLshort x;
	GLshort y;
	GLshort z;
	GLshort w;
} gl_wrap_handler_glRasterPos4s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glRasterPos4sv_args;

typedef struct {
	GLdouble x1;
	GLdouble y1;
	GLdouble x2;
	GLdouble y2;
} gl_wrap_handler_glRectd_args;

typedef struct {
	GLdouble* v1;
	GLdouble* v2;
} gl_wrap_handler_glRectdv_args;

typedef struct {
	GLfloat x1;
	GLfloat y1;
	GLfloat x2;
	GLfloat y2;
} gl_wrap_handler_glRectf_args;

typedef struct {
	GLfloat* v1;
	GLfloat* v2;
} gl_wrap_handler_glRectfv_args;

typedef struct {
	GLint x1;
	GLint y1;
	GLint x2;
	GLint y2;
} gl_wrap_handler_glRecti_args;

typedef struct {
	GLint* v1;
	GLint* v2;
} gl_wrap_handler_glRectiv_args;

typedef struct {
	GLshort x1;
	GLshort y1;
	GLshort x2;
	GLshort y2;
} gl_wrap_handler_glRects_args;

typedef struct {
	GLshort* v1;
	GLshort* v2;
} gl_wrap_handler_glRectsv_args;

typedef struct {
	GLdouble s;
} gl_wrap_handler_glTexCoord1d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glTexCoord1dv_args;

typedef struct {
	GLfloat s;
} gl_wrap_handler_glTexCoord1f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glTexCoord1fv_args;

typedef struct {
	GLint s;
} gl_wrap_handler_glTexCoord1i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glTexCoord1iv_args;

typedef struct {
	GLshort s;
} gl_wrap_handler_glTexCoord1s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glTexCoord1sv_args;

typedef struct {
	GLdouble s;
	GLdouble t;
} gl_wrap_handler_glTexCoord2d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glTexCoord2dv_args;

typedef struct {
	GLfloat s;
	GLfloat t;
} gl_wrap_handler_glTexCoord2f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glTexCoord2fv_args;

typedef struct {
	GLint s;
	GLint t;
} gl_wrap_handler_glTexCoord2i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glTexCoord2iv_args;

typedef struct {
	GLshort s;
	GLshort t;
} gl_wrap_handler_glTexCoord2s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glTexCoord2sv_args;

typedef struct {
	GLdouble s;
	GLdouble t;
	GLdouble r;
} gl_wrap_handler_glTexCoord3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glTexCoord3dv_args;

typedef struct {
	GLfloat s;
	GLfloat t;
	GLfloat r;
} gl_wrap_handler_glTexCoord3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glTexCoord3fv_args;

typedef struct {
	GLint s;
	GLint t;
	GLint r;
} gl_wrap_handler_glTexCoord3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glTexCoord3iv_args;

typedef struct {
	GLshort s;
	GLshort t;
	GLshort r;
} gl_wrap_handler_glTexCoord3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glTexCoord3sv_args;

typedef struct {
	GLdouble s;
	GLdouble t;
	GLdouble r;
	GLdouble q;
} gl_wrap_handler_glTexCoord4d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glTexCoord4dv_args;

typedef struct {
	GLfloat s;
	GLfloat t;
	GLfloat r;
	GLfloat q;
} gl_wrap_handler_glTexCoord4f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glTexCoord4fv_args;

typedef struct {
	GLint s;
	GLint t;
	GLint r;
	GLint q;
} gl_wrap_handler_glTexCoord4i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glTexCoord4iv_args;

typedef struct {
	GLshort s;
	GLshort t;
	GLshort r;
	GLshort q;
} gl_wrap_handler_glTexCoord4s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glTexCoord4sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
} gl_wrap_handler_glVertex2d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glVertex2dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
} gl_wrap_handler_glVertex2f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glVertex2fv_args;

typedef struct {
	GLint x;
	GLint y;
} gl_wrap_handler_glVertex2i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glVertex2iv_args;

typedef struct {
	GLshort x;
	GLshort y;
} gl_wrap_handler_glVertex2s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glVertex2sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glVertex3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glVertex3dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glVertex3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glVertex3fv_args;

typedef struct {
	GLint x;
	GLint y;
	GLint z;
} gl_wrap_handler_glVertex3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glVertex3iv_args;

typedef struct {
	GLshort x;
	GLshort y;
	GLshort z;
} gl_wrap_handler_glVertex3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glVertex3sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble w;
} gl_wrap_handler_glVertex4d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glVertex4dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
} gl_wrap_handler_glVertex4f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glVertex4fv_args;

typedef struct {
	GLint x;
	GLint y;
	GLint z;
	GLint w;
} gl_wrap_handler_glVertex4i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glVertex4iv_args;

typedef struct {
	GLshort x;
	GLshort y;
	GLshort z;
	GLshort w;
} gl_wrap_handler_glVertex4s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glVertex4sv_args;

typedef struct {
	GLenum plane;
	GLdouble* equation;
} gl_wrap_handler_glClipPlane_args;

typedef struct {
	GLenum face;
	GLenum mode;
} gl_wrap_handler_glColorMaterial_args;

typedef struct {
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glFogf_args;

typedef struct {
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glFogfv_args;

typedef struct {
	GLenum pname;
	GLint param;
} gl_wrap_handler_glFogi_args;

typedef struct {
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glFogiv_args;

typedef struct {
	GLenum light;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glLightf_args;

typedef struct {
	GLenum light;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glLightfv_args;

typedef struct {
	GLenum light;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glLighti_args;

typedef struct {
	GLenum light;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glLightiv_args;

typedef struct {
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glLightModelf_args;

typedef struct {
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glLightModelfv_args;

typedef struct {
	GLenum pname;
	GLint param;
} gl_wrap_handler_glLightModeli_args;

typedef struct {
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glLightModeliv_args;

typedef struct {
	GLint factor;
	GLushort pattern;
} gl_wrap_handler_glLineStipple_args;

typedef struct {
	GLenum face;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glMaterialf_args;

typedef struct {
	GLenum face;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glMaterialfv_args;

typedef struct {
	GLenum face;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glMateriali_args;

typedef struct {
	GLenum face;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glMaterialiv_args;

typedef struct {
	GLubyte* mask;
} gl_wrap_handler_glPolygonStipple_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glShadeModel_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glTexEnvf_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glTexEnvfv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glTexEnvi_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glTexEnviv_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLdouble param;
} gl_wrap_handler_glTexGend_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLdouble* params;
} gl_wrap_handler_glTexGendv_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glTexGenf_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glTexGenfv_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glTexGeni_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glTexGeniv_args;

typedef struct {
	GLsizei size;
	GLenum type;
	GLfloat* buffer;
} gl_wrap_handler_glFeedbackBuffer_args;

typedef struct {
	GLsizei size;
	GLuint* buffer;
} gl_wrap_handler_glSelectBuffer_args;

typedef struct {
} gl_wrap_handler_glInitNames_args;

typedef struct {
	GLuint name;
} gl_wrap_handler_glLoadName_args;

typedef struct {
	GLfloat token;
} gl_wrap_handler_glPassThrough_args;

typedef struct {
} gl_wrap_handler_glPopName_args;

typedef struct {
	GLuint name;
} gl_wrap_handler_glPushName_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} gl_wrap_handler_glClearAccum_args;

typedef struct {
	GLfloat c;
} gl_wrap_handler_glClearIndex_args;

typedef struct {
	GLuint mask;
} gl_wrap_handler_glIndexMask_args;

typedef struct {
	GLenum op;
	GLfloat value;
} gl_wrap_handler_glAccum_args;

typedef struct {
} gl_wrap_handler_glPopAttrib_args;

typedef struct {
	GLbitfield mask;
} gl_wrap_handler_glPushAttrib_args;

typedef struct {
	GLenum target;
	GLdouble u1;
	GLdouble u2;
	GLint stride;
	GLint order;
	GLdouble* points;
} gl_wrap_handler_glMap1d_args;

typedef struct {
	GLenum target;
	GLfloat u1;
	GLfloat u2;
	GLint stride;
	GLint order;
	GLfloat* points;
} gl_wrap_handler_glMap1f_args;

typedef struct {
	GLenum target;
	GLdouble u1;
	GLdouble u2;
	GLint ustride;
	GLint uorder;
	GLdouble v1;
	GLdouble v2;
	GLint vstride;
	GLint vorder;
	GLdouble* points;
} gl_wrap_handler_glMap2d_args;

typedef struct {
	GLenum target;
	GLfloat u1;
	GLfloat u2;
	GLint ustride;
	GLint uorder;
	GLfloat v1;
	GLfloat v2;
	GLint vstride;
	GLint vorder;
	GLfloat* points;
} gl_wrap_handler_glMap2f_args;

typedef struct {
	GLint un;
	GLdouble u1;
	GLdouble u2;
} gl_wrap_handler_glMapGrid1d_args;

typedef struct {
	GLint un;
	GLfloat u1;
	GLfloat u2;
} gl_wrap_handler_glMapGrid1f_args;

typedef struct {
	GLint un;
	GLdouble u1;
	GLdouble u2;
	GLint vn;
	GLdouble v1;
	GLdouble v2;
} gl_wrap_handler_glMapGrid2d_args;

typedef struct {
	GLint un;
	GLfloat u1;
	GLfloat u2;
	GLint vn;
	GLfloat v1;
	GLfloat v2;
} gl_wrap_handler_glMapGrid2f_args;

typedef struct {
	GLdouble u;
} gl_wrap_handler_glEvalCoord1d_args;

typedef struct {
	GLdouble* u;
} gl_wrap_handler_glEvalCoord1dv_args;

typedef struct {
	GLfloat u;
} gl_wrap_handler_glEvalCoord1f_args;

typedef struct {
	GLfloat* u;
} gl_wrap_handler_glEvalCoord1fv_args;

typedef struct {
	GLdouble u;
	GLdouble v;
} gl_wrap_handler_glEvalCoord2d_args;

typedef struct {
	GLdouble* u;
} gl_wrap_handler_glEvalCoord2dv_args;

typedef struct {
	GLfloat u;
	GLfloat v;
} gl_wrap_handler_glEvalCoord2f_args;

typedef struct {
	GLfloat* u;
} gl_wrap_handler_glEvalCoord2fv_args;

typedef struct {
	GLenum mode;
	GLint i1;
	GLint i2;
} gl_wrap_handler_glEvalMesh1_args;

typedef struct {
	GLint i;
} gl_wrap_handler_glEvalPoint1_args;

typedef struct {
	GLenum mode;
	GLint i1;
	GLint i2;
	GLint j1;
	GLint j2;
} gl_wrap_handler_glEvalMesh2_args;

typedef struct {
	GLint i;
	GLint j;
} gl_wrap_handler_glEvalPoint2_args;

typedef struct {
	GLenum func;
	GLfloat ref;
} gl_wrap_handler_glAlphaFunc_args;

typedef struct {
	GLfloat xfactor;
	GLfloat yfactor;
} gl_wrap_handler_glPixelZoom_args;

typedef struct {
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glPixelTransferf_args;

typedef struct {
	GLenum pname;
	GLint param;
} gl_wrap_handler_glPixelTransferi_args;

typedef struct {
	GLenum map;
	GLsizei mapsize;
	GLfloat* values;
} gl_wrap_handler_glPixelMapfv_args;

typedef struct {
	GLenum map;
	GLsizei mapsize;
	GLuint* values;
} gl_wrap_handler_glPixelMapuiv_args;

typedef struct {
	GLenum map;
	GLsizei mapsize;
	GLushort* values;
} gl_wrap_handler_glPixelMapusv_args;

typedef struct {
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	GLenum type;
} gl_wrap_handler_glCopyPixels_args;

typedef struct {
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glDrawPixels_args;

typedef struct {
	GLenum plane;
	GLdouble* equation;
} gl_wrap_handler_glGetClipPlane_args;

typedef struct {
	GLenum light;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetLightfv_args;

typedef struct {
	GLenum light;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetLightiv_args;

typedef struct {
	GLenum target;
	GLenum query;
	GLdouble* v;
} gl_wrap_handler_glGetMapdv_args;

typedef struct {
	GLenum target;
	GLenum query;
	GLfloat* v;
} gl_wrap_handler_glGetMapfv_args;

typedef struct {
	GLenum target;
	GLenum query;
	GLint* v;
} gl_wrap_handler_glGetMapiv_args;

typedef struct {
	GLenum face;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetMaterialfv_args;

typedef struct {
	GLenum face;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetMaterialiv_args;

typedef struct {
	GLenum map;
	GLfloat* values;
} gl_wrap_handler_glGetPixelMapfv_args;

typedef struct {
	GLenum map;
	GLuint* values;
} gl_wrap_handler_glGetPixelMapuiv_args;

typedef struct {
	GLenum map;
	GLushort* values;
} gl_wrap_handler_glGetPixelMapusv_args;

typedef struct {
	GLubyte* mask;
} gl_wrap_handler_glGetPolygonStipple_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetTexEnvfv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexEnviv_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLdouble* params;
} gl_wrap_handler_glGetTexGendv_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetTexGenfv_args;

typedef struct {
	GLenum coord;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexGeniv_args;

typedef struct {
	GLdouble left;
	GLdouble right;
	GLdouble bottom;
	GLdouble top;
	GLdouble zNear;
	GLdouble zFar;
} gl_wrap_handler_glFrustum_args;

typedef struct {
} gl_wrap_handler_glLoadIdentity_args;

typedef struct {
	GLfloat* m;
} gl_wrap_handler_glLoadMatrixf_args;

typedef struct {
	GLdouble* m;
} gl_wrap_handler_glLoadMatrixd_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glMatrixMode_args;

typedef struct {
	GLfloat* m;
} gl_wrap_handler_glMultMatrixf_args;

typedef struct {
	GLdouble* m;
} gl_wrap_handler_glMultMatrixd_args;

typedef struct {
	GLdouble left;
	GLdouble right;
	GLdouble bottom;
	GLdouble top;
	GLdouble zNear;
	GLdouble zFar;
} gl_wrap_handler_glOrtho_args;

typedef struct {
} gl_wrap_handler_glPopMatrix_args;

typedef struct {
} gl_wrap_handler_glPushMatrix_args;

typedef struct {
	GLdouble angle;
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glRotated_args;

typedef struct {
	GLfloat angle;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glRotatef_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glScaled_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glScalef_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glTranslated_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glTranslatef_args;

typedef struct {
	GLenum mode;
	GLint first;
	GLsizei count;
} gl_wrap_handler_glDrawArrays_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
} gl_wrap_handler_glDrawElements_args;

typedef struct {
	GLenum pname;
	void** params;
} gl_wrap_handler_glGetPointerv_args;

typedef struct {
	GLfloat factor;
	GLfloat units;
} gl_wrap_handler_glPolygonOffset_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLint x;
	GLint y;
	GLsizei width;
	GLint border;
} gl_wrap_handler_glCopyTexImage1D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	GLint border;
} gl_wrap_handler_glCopyTexImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint x;
	GLint y;
	GLsizei width;
} gl_wrap_handler_glCopyTexSubImage1D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glCopyTexSubImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLsizei width;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexSubImage1D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexSubImage2D_args;

typedef struct {
	GLenum target;
	GLuint texture;
} gl_wrap_handler_glBindTexture_args;

typedef struct {
	GLsizei n;
	GLuint* textures;
} gl_wrap_handler_glDeleteTextures_args;

typedef struct {
	GLsizei n;
	GLuint* textures;
} gl_wrap_handler_glGenTextures_args;

typedef struct {
	GLint i;
} gl_wrap_handler_glArrayElement_args;

typedef struct {
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glColorPointer_args;

typedef struct {
	GLenum array;
} gl_wrap_handler_glDisableClientState_args;

typedef struct {
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glEdgeFlagPointer_args;

typedef struct {
	GLenum array;
} gl_wrap_handler_glEnableClientState_args;

typedef struct {
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glIndexPointer_args;

typedef struct {
	GLenum format;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glInterleavedArrays_args;

typedef struct {
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glNormalPointer_args;

typedef struct {
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glTexCoordPointer_args;

typedef struct {
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glVertexPointer_args;

typedef struct {
	GLsizei n;
	GLuint* textures;
	GLfloat* priorities;
} gl_wrap_handler_glPrioritizeTextures_args;

typedef struct {
	GLubyte c;
} gl_wrap_handler_glIndexub_args;

typedef struct {
	GLubyte* c;
} gl_wrap_handler_glIndexubv_args;

typedef struct {
} gl_wrap_handler_glPopClientAttrib_args;

typedef struct {
	GLbitfield mask;
} gl_wrap_handler_glPushClientAttrib_args;

typedef struct {
	GLenum mode;
	GLuint start;
	GLuint end;
	GLsizei count;
	GLenum type;
	void* indices;
} gl_wrap_handler_glDrawRangeElements_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLint border;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLenum format;
	GLenum type;
	void* pixels;
} gl_wrap_handler_glTexSubImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glCopyTexSubImage3D_args;

typedef struct {
	GLenum texture;
} gl_wrap_handler_glActiveTexture_args;

typedef struct {
	GLfloat value;
	GLboolean invert;
} gl_wrap_handler_glSampleCoverage_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLint border;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLint border;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLint border;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexImage1D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLenum format;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexSubImage3D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexSubImage2D_args;

typedef struct {
	GLenum target;
	GLint level;
	GLint xoffset;
	GLsizei width;
	GLenum format;
	GLsizei imageSize;
	void* data;
} gl_wrap_handler_glCompressedTexSubImage1D_args;

typedef struct {
	GLenum target;
	GLint level;
	void* img;
} gl_wrap_handler_glGetCompressedTexImage_args;

typedef struct {
	GLenum texture;
} gl_wrap_handler_glClientActiveTexture_args;

typedef struct {
	GLenum target;
	GLdouble s;
} gl_wrap_handler_glMultiTexCoord1d_args;

typedef struct {
	GLenum target;
	GLdouble* v;
} gl_wrap_handler_glMultiTexCoord1dv_args;

typedef struct {
	GLenum target;
	GLfloat s;
} gl_wrap_handler_glMultiTexCoord1f_args;

typedef struct {
	GLenum target;
	GLfloat* v;
} gl_wrap_handler_glMultiTexCoord1fv_args;

typedef struct {
	GLenum target;
	GLint s;
} gl_wrap_handler_glMultiTexCoord1i_args;

typedef struct {
	GLenum target;
	GLint* v;
} gl_wrap_handler_glMultiTexCoord1iv_args;

typedef struct {
	GLenum target;
	GLshort s;
} gl_wrap_handler_glMultiTexCoord1s_args;

typedef struct {
	GLenum target;
	GLshort* v;
} gl_wrap_handler_glMultiTexCoord1sv_args;

typedef struct {
	GLenum target;
	GLdouble s;
	GLdouble t;
} gl_wrap_handler_glMultiTexCoord2d_args;

typedef struct {
	GLenum target;
	GLdouble* v;
} gl_wrap_handler_glMultiTexCoord2dv_args;

typedef struct {
	GLenum target;
	GLfloat s;
	GLfloat t;
} gl_wrap_handler_glMultiTexCoord2f_args;

typedef struct {
	GLenum target;
	GLfloat* v;
} gl_wrap_handler_glMultiTexCoord2fv_args;

typedef struct {
	GLenum target;
	GLint s;
	GLint t;
} gl_wrap_handler_glMultiTexCoord2i_args;

typedef struct {
	GLenum target;
	GLint* v;
} gl_wrap_handler_glMultiTexCoord2iv_args;

typedef struct {
	GLenum target;
	GLshort s;
	GLshort t;
} gl_wrap_handler_glMultiTexCoord2s_args;

typedef struct {
	GLenum target;
	GLshort* v;
} gl_wrap_handler_glMultiTexCoord2sv_args;

typedef struct {
	GLenum target;
	GLdouble s;
	GLdouble t;
	GLdouble r;
} gl_wrap_handler_glMultiTexCoord3d_args;

typedef struct {
	GLenum target;
	GLdouble* v;
} gl_wrap_handler_glMultiTexCoord3dv_args;

typedef struct {
	GLenum target;
	GLfloat s;
	GLfloat t;
	GLfloat r;
} gl_wrap_handler_glMultiTexCoord3f_args;

typedef struct {
	GLenum target;
	GLfloat* v;
} gl_wrap_handler_glMultiTexCoord3fv_args;

typedef struct {
	GLenum target;
	GLint s;
	GLint t;
	GLint r;
} gl_wrap_handler_glMultiTexCoord3i_args;

typedef struct {
	GLenum target;
	GLint* v;
} gl_wrap_handler_glMultiTexCoord3iv_args;

typedef struct {
	GLenum target;
	GLshort s;
	GLshort t;
	GLshort r;
} gl_wrap_handler_glMultiTexCoord3s_args;

typedef struct {
	GLenum target;
	GLshort* v;
} gl_wrap_handler_glMultiTexCoord3sv_args;

typedef struct {
	GLenum target;
	GLdouble s;
	GLdouble t;
	GLdouble r;
	GLdouble q;
} gl_wrap_handler_glMultiTexCoord4d_args;

typedef struct {
	GLenum target;
	GLdouble* v;
} gl_wrap_handler_glMultiTexCoord4dv_args;

typedef struct {
	GLenum target;
	GLfloat s;
	GLfloat t;
	GLfloat r;
	GLfloat q;
} gl_wrap_handler_glMultiTexCoord4f_args;

typedef struct {
	GLenum target;
	GLfloat* v;
} gl_wrap_handler_glMultiTexCoord4fv_args;

typedef struct {
	GLenum target;
	GLint s;
	GLint t;
	GLint r;
	GLint q;
} gl_wrap_handler_glMultiTexCoord4i_args;

typedef struct {
	GLenum target;
	GLint* v;
} gl_wrap_handler_glMultiTexCoord4iv_args;

typedef struct {
	GLenum target;
	GLshort s;
	GLshort t;
	GLshort r;
	GLshort q;
} gl_wrap_handler_glMultiTexCoord4s_args;

typedef struct {
	GLenum target;
	GLshort* v;
} gl_wrap_handler_glMultiTexCoord4sv_args;

typedef struct {
	GLfloat* m;
} gl_wrap_handler_glLoadTransposeMatrixf_args;

typedef struct {
	GLdouble* m;
} gl_wrap_handler_glLoadTransposeMatrixd_args;

typedef struct {
	GLfloat* m;
} gl_wrap_handler_glMultTransposeMatrixf_args;

typedef struct {
	GLdouble* m;
} gl_wrap_handler_glMultTransposeMatrixd_args;

typedef struct {
	GLenum sfactorRGB;
	GLenum dfactorRGB;
	GLenum sfactorAlpha;
	GLenum dfactorAlpha;
} gl_wrap_handler_glBlendFuncSeparate_args;

typedef struct {
	GLenum mode;
	GLint* first;
	GLsizei* count;
	GLsizei drawcount;
} gl_wrap_handler_glMultiDrawArrays_args;

typedef struct {
	GLenum mode;
	GLsizei* count;
	GLenum type;
	void** indices;
	GLsizei drawcount;
} gl_wrap_handler_glMultiDrawElements_args;

typedef struct {
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glPointParameterf_args;

typedef struct {
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glPointParameterfv_args;

typedef struct {
	GLenum pname;
	GLint param;
} gl_wrap_handler_glPointParameteri_args;

typedef struct {
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glPointParameteriv_args;

typedef struct {
	GLfloat coord;
} gl_wrap_handler_glFogCoordf_args;

typedef struct {
	GLfloat* coord;
} gl_wrap_handler_glFogCoordfv_args;

typedef struct {
	GLdouble coord;
} gl_wrap_handler_glFogCoordd_args;

typedef struct {
	GLdouble* coord;
} gl_wrap_handler_glFogCoorddv_args;

typedef struct {
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glFogCoordPointer_args;

typedef struct {
	GLbyte red;
	GLbyte green;
	GLbyte blue;
} gl_wrap_handler_glSecondaryColor3b_args;

typedef struct {
	GLbyte* v;
} gl_wrap_handler_glSecondaryColor3bv_args;

typedef struct {
	GLdouble red;
	GLdouble green;
	GLdouble blue;
} gl_wrap_handler_glSecondaryColor3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glSecondaryColor3dv_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
} gl_wrap_handler_glSecondaryColor3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glSecondaryColor3fv_args;

typedef struct {
	GLint red;
	GLint green;
	GLint blue;
} gl_wrap_handler_glSecondaryColor3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glSecondaryColor3iv_args;

typedef struct {
	GLshort red;
	GLshort green;
	GLshort blue;
} gl_wrap_handler_glSecondaryColor3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glSecondaryColor3sv_args;

typedef struct {
	GLubyte red;
	GLubyte green;
	GLubyte blue;
} gl_wrap_handler_glSecondaryColor3ub_args;

typedef struct {
	GLubyte* v;
} gl_wrap_handler_glSecondaryColor3ubv_args;

typedef struct {
	GLuint red;
	GLuint green;
	GLuint blue;
} gl_wrap_handler_glSecondaryColor3ui_args;

typedef struct {
	GLuint* v;
} gl_wrap_handler_glSecondaryColor3uiv_args;

typedef struct {
	GLushort red;
	GLushort green;
	GLushort blue;
} gl_wrap_handler_glSecondaryColor3us_args;

typedef struct {
	GLushort* v;
} gl_wrap_handler_glSecondaryColor3usv_args;

typedef struct {
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glSecondaryColorPointer_args;

typedef struct {
	GLdouble x;
	GLdouble y;
} gl_wrap_handler_glWindowPos2d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glWindowPos2dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
} gl_wrap_handler_glWindowPos2f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glWindowPos2fv_args;

typedef struct {
	GLint x;
	GLint y;
} gl_wrap_handler_glWindowPos2i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glWindowPos2iv_args;

typedef struct {
	GLshort x;
	GLshort y;
} gl_wrap_handler_glWindowPos2s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glWindowPos2sv_args;

typedef struct {
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glWindowPos3d_args;

typedef struct {
	GLdouble* v;
} gl_wrap_handler_glWindowPos3dv_args;

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glWindowPos3f_args;

typedef struct {
	GLfloat* v;
} gl_wrap_handler_glWindowPos3fv_args;

typedef struct {
	GLint x;
	GLint y;
	GLint z;
} gl_wrap_handler_glWindowPos3i_args;

typedef struct {
	GLint* v;
} gl_wrap_handler_glWindowPos3iv_args;

typedef struct {
	GLshort x;
	GLshort y;
	GLshort z;
} gl_wrap_handler_glWindowPos3s_args;

typedef struct {
	GLshort* v;
} gl_wrap_handler_glWindowPos3sv_args;

typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} gl_wrap_handler_glBlendColor_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glBlendEquation_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glGenQueries_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glDeleteQueries_args;

typedef struct {
	GLenum target;
	GLuint id;
} gl_wrap_handler_glBeginQuery_args;

typedef struct {
	GLenum target;
} gl_wrap_handler_glEndQuery_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetQueryiv_args;

typedef struct {
	GLuint id;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetQueryObjectiv_args;

typedef struct {
	GLuint id;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glGetQueryObjectuiv_args;

typedef struct {
	GLenum target;
	GLuint buffer;
} gl_wrap_handler_glBindBuffer_args;

typedef struct {
	GLsizei n;
	GLuint* buffers;
} gl_wrap_handler_glDeleteBuffers_args;

typedef struct {
	GLsizei n;
	GLuint* buffers;
} gl_wrap_handler_glGenBuffers_args;

typedef struct {
	GLenum target;
	GLsizeiptr size;
	void* data;
	GLenum usage;
} gl_wrap_handler_glBufferData_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr size;
	void* data;
} gl_wrap_handler_glBufferSubData_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr size;
	void* data;
} gl_wrap_handler_glGetBufferSubData_args;

typedef struct {
	GLenum target;
	GLenum access;
} gl_wrap_handler_glMapBuffer_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetBufferParameteriv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	void** params;
} gl_wrap_handler_glGetBufferPointerv_args;

typedef struct {
	GLenum modeRGB;
	GLenum modeAlpha;
} gl_wrap_handler_glBlendEquationSeparate_args;

typedef struct {
	GLsizei n;
	GLenum* bufs;
} gl_wrap_handler_glDrawBuffers_args;

typedef struct {
	GLenum face;
	GLenum sfail;
	GLenum dpfail;
	GLenum dppass;
} gl_wrap_handler_glStencilOpSeparate_args;

typedef struct {
	GLenum face;
	GLenum func;
	GLint ref;
	GLuint mask;
} gl_wrap_handler_glStencilFuncSeparate_args;

typedef struct {
	GLenum face;
	GLuint mask;
} gl_wrap_handler_glStencilMaskSeparate_args;

typedef struct {
	GLuint program;
	GLuint shader;
} gl_wrap_handler_glAttachShader_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLchar* name;
} gl_wrap_handler_glBindAttribLocation_args;

typedef struct {
	GLuint shader;
} gl_wrap_handler_glCompileShader_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glDeleteProgram_args;

typedef struct {
	GLuint shader;
} gl_wrap_handler_glDeleteShader_args;

typedef struct {
	GLuint program;
	GLuint shader;
} gl_wrap_handler_glDetachShader_args;

typedef struct {
	GLuint index;
} gl_wrap_handler_glDisableVertexAttribArray_args;

typedef struct {
	GLuint index;
} gl_wrap_handler_glEnableVertexAttribArray_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLint* size;
	GLenum* type;
	GLchar* name;
} gl_wrap_handler_glGetActiveAttrib_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLint* size;
	GLenum* type;
	GLchar* name;
} gl_wrap_handler_glGetActiveUniform_args;

typedef struct {
	GLuint program;
	GLsizei maxCount;
	GLsizei* count;
	GLuint* shaders;
} gl_wrap_handler_glGetAttachedShaders_args;

typedef struct {
	GLuint program;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetProgramiv_args;

typedef struct {
	GLuint program;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* infoLog;
} gl_wrap_handler_glGetProgramInfoLog_args;

typedef struct {
	GLuint shader;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetShaderiv_args;

typedef struct {
	GLuint shader;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* infoLog;
} gl_wrap_handler_glGetShaderInfoLog_args;

typedef struct {
	GLuint shader;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* source;
} gl_wrap_handler_glGetShaderSource_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat* params;
} gl_wrap_handler_glGetUniformfv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint* params;
} gl_wrap_handler_glGetUniformiv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLdouble* params;
} gl_wrap_handler_glGetVertexAttribdv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetVertexAttribfv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetVertexAttribiv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	void** pointer;
} gl_wrap_handler_glGetVertexAttribPointerv_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glLinkProgram_args;

typedef struct {
	GLuint shader;
	GLsizei count;
	GLchar** string;
	GLint* length;
} gl_wrap_handler_glShaderSource_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glUseProgram_args;

typedef struct {
	GLint location;
	GLfloat v0;
} gl_wrap_handler_glUniform1f_args;

typedef struct {
	GLint location;
	GLfloat v0;
	GLfloat v1;
} gl_wrap_handler_glUniform2f_args;

typedef struct {
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
} gl_wrap_handler_glUniform3f_args;

typedef struct {
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;
} gl_wrap_handler_glUniform4f_args;

typedef struct {
	GLint location;
	GLint v0;
} gl_wrap_handler_glUniform1i_args;

typedef struct {
	GLint location;
	GLint v0;
	GLint v1;
} gl_wrap_handler_glUniform2i_args;

typedef struct {
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
} gl_wrap_handler_glUniform3i_args;

typedef struct {
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
	GLint v3;
} gl_wrap_handler_glUniform4i_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform1fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform3fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glUniform4fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform1iv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform2iv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform3iv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glUniform4iv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix3fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix4fv_args;

typedef struct {
	GLuint program;
} gl_wrap_handler_glValidateProgram_args;

typedef struct {
	GLuint index;
	GLdouble x;
} gl_wrap_handler_glVertexAttrib1d_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttrib1dv_args;

typedef struct {
	GLuint index;
	GLfloat x;
} gl_wrap_handler_glVertexAttrib1f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib1fv_args;

typedef struct {
	GLuint index;
	GLshort x;
} gl_wrap_handler_glVertexAttrib1s_args;

typedef struct {
	GLuint index;
	GLshort* v;
} gl_wrap_handler_glVertexAttrib1sv_args;

typedef struct {
	GLuint index;
	GLdouble x;
	GLdouble y;
} gl_wrap_handler_glVertexAttrib2d_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttrib2dv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
} gl_wrap_handler_glVertexAttrib2f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib2fv_args;

typedef struct {
	GLuint index;
	GLshort x;
	GLshort y;
} gl_wrap_handler_glVertexAttrib2s_args;

typedef struct {
	GLuint index;
	GLshort* v;
} gl_wrap_handler_glVertexAttrib2sv_args;

typedef struct {
	GLuint index;
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glVertexAttrib3d_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttrib3dv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} gl_wrap_handler_glVertexAttrib3f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib3fv_args;

typedef struct {
	GLuint index;
	GLshort x;
	GLshort y;
	GLshort z;
} gl_wrap_handler_glVertexAttrib3s_args;

typedef struct {
	GLuint index;
	GLshort* v;
} gl_wrap_handler_glVertexAttrib3sv_args;

typedef struct {
	GLuint index;
	GLbyte* v;
} gl_wrap_handler_glVertexAttrib4Nbv_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttrib4Niv_args;

typedef struct {
	GLuint index;
	GLshort* v;
} gl_wrap_handler_glVertexAttrib4Nsv_args;

typedef struct {
	GLuint index;
	GLubyte x;
	GLubyte y;
	GLubyte z;
	GLubyte w;
} gl_wrap_handler_glVertexAttrib4Nub_args;

typedef struct {
	GLuint index;
	GLubyte* v;
} gl_wrap_handler_glVertexAttrib4Nubv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttrib4Nuiv_args;

typedef struct {
	GLuint index;
	GLushort* v;
} gl_wrap_handler_glVertexAttrib4Nusv_args;

typedef struct {
	GLuint index;
	GLbyte* v;
} gl_wrap_handler_glVertexAttrib4bv_args;

typedef struct {
	GLuint index;
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble w;
} gl_wrap_handler_glVertexAttrib4d_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttrib4dv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
} gl_wrap_handler_glVertexAttrib4f_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glVertexAttrib4fv_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttrib4iv_args;

typedef struct {
	GLuint index;
	GLshort x;
	GLshort y;
	GLshort z;
	GLshort w;
} gl_wrap_handler_glVertexAttrib4s_args;

typedef struct {
	GLuint index;
	GLshort* v;
} gl_wrap_handler_glVertexAttrib4sv_args;

typedef struct {
	GLuint index;
	GLubyte* v;
} gl_wrap_handler_glVertexAttrib4ubv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttrib4uiv_args;

typedef struct {
	GLuint index;
	GLushort* v;
} gl_wrap_handler_glVertexAttrib4usv_args;

typedef struct {
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glVertexAttribPointer_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix2x3fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix3x2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix2x4fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix4x2fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix3x4fv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glUniformMatrix4x3fv_args;

typedef struct {
	GLuint index;
	GLboolean r;
	GLboolean g;
	GLboolean b;
	GLboolean a;
} gl_wrap_handler_glColorMaski_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLboolean* data;
} gl_wrap_handler_glGetBooleani_v_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLint* data;
} gl_wrap_handler_glGetIntegeri_v_args;

typedef struct {
	GLenum target;
	GLuint index;
} gl_wrap_handler_glEnablei_args;

typedef struct {
	GLenum target;
	GLuint index;
} gl_wrap_handler_glDisablei_args;

typedef struct {
	GLenum primitiveMode;
} gl_wrap_handler_glBeginTransformFeedback_args;

typedef struct {
} gl_wrap_handler_glEndTransformFeedback_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLuint buffer;
	GLintptr offset;
	GLsizeiptr size;
} gl_wrap_handler_glBindBufferRange_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLuint buffer;
} gl_wrap_handler_glBindBufferBase_args;

typedef struct {
	GLuint program;
	GLsizei count;
	GLchar** varyings;
	GLenum bufferMode;
} gl_wrap_handler_glTransformFeedbackVaryings_args;

typedef struct {
	GLuint program;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLsizei* size;
	GLenum* type;
	GLchar* name;
} gl_wrap_handler_glGetTransformFeedbackVarying_args;

typedef struct {
	GLenum target;
	GLenum clamp;
} gl_wrap_handler_glClampColor_args;

typedef struct {
	GLuint id;
	GLenum mode;
} gl_wrap_handler_glBeginConditionalRender_args;

typedef struct {
} gl_wrap_handler_glEndConditionalRender_args;

typedef struct {
	GLuint index;
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glVertexAttribIPointer_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetVertexAttribIiv_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glGetVertexAttribIuiv_args;

typedef struct {
	GLuint index;
	GLint x;
} gl_wrap_handler_glVertexAttribI1i_args;

typedef struct {
	GLuint index;
	GLint x;
	GLint y;
} gl_wrap_handler_glVertexAttribI2i_args;

typedef struct {
	GLuint index;
	GLint x;
	GLint y;
	GLint z;
} gl_wrap_handler_glVertexAttribI3i_args;

typedef struct {
	GLuint index;
	GLint x;
	GLint y;
	GLint z;
	GLint w;
} gl_wrap_handler_glVertexAttribI4i_args;

typedef struct {
	GLuint index;
	GLuint x;
} gl_wrap_handler_glVertexAttribI1ui_args;

typedef struct {
	GLuint index;
	GLuint x;
	GLuint y;
} gl_wrap_handler_glVertexAttribI2ui_args;

typedef struct {
	GLuint index;
	GLuint x;
	GLuint y;
	GLuint z;
} gl_wrap_handler_glVertexAttribI3ui_args;

typedef struct {
	GLuint index;
	GLuint x;
	GLuint y;
	GLuint z;
	GLuint w;
} gl_wrap_handler_glVertexAttribI4ui_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttribI1iv_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttribI2iv_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttribI3iv_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glVertexAttribI4iv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttribI1uiv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttribI2uiv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttribI3uiv_args;

typedef struct {
	GLuint index;
	GLuint* v;
} gl_wrap_handler_glVertexAttribI4uiv_args;

typedef struct {
	GLuint index;
	GLbyte* v;
} gl_wrap_handler_glVertexAttribI4bv_args;

typedef struct {
	GLuint index;
	GLshort* v;
} gl_wrap_handler_glVertexAttribI4sv_args;

typedef struct {
	GLuint index;
	GLubyte* v;
} gl_wrap_handler_glVertexAttribI4ubv_args;

typedef struct {
	GLuint index;
	GLushort* v;
} gl_wrap_handler_glVertexAttribI4usv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint* params;
} gl_wrap_handler_glGetUniformuiv_args;

typedef struct {
	GLuint program;
	GLuint color;
	GLchar* name;
} gl_wrap_handler_glBindFragDataLocation_args;

typedef struct {
	GLint location;
	GLuint v0;
} gl_wrap_handler_glUniform1ui_args;

typedef struct {
	GLint location;
	GLuint v0;
	GLuint v1;
} gl_wrap_handler_glUniform2ui_args;

typedef struct {
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
} gl_wrap_handler_glUniform3ui_args;

typedef struct {
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
	GLuint v3;
} gl_wrap_handler_glUniform4ui_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform1uiv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform2uiv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform3uiv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glUniform4uiv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glTexParameterIiv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glTexParameterIuiv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetTexParameterIiv_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glGetTexParameterIuiv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLint* value;
} gl_wrap_handler_glClearBufferiv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLuint* value;
} gl_wrap_handler_glClearBufferuiv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLfloat* value;
} gl_wrap_handler_glClearBufferfv_args;

typedef struct {
	GLenum buffer;
	GLint drawbuffer;
	GLfloat depth;
	GLint stencil;
} gl_wrap_handler_glClearBufferfi_args;

typedef struct {
	GLenum target;
	GLuint renderbuffer;
} gl_wrap_handler_glBindRenderbuffer_args;

typedef struct {
	GLsizei n;
	GLuint* renderbuffers;
} gl_wrap_handler_glDeleteRenderbuffers_args;

typedef struct {
	GLsizei n;
	GLuint* renderbuffers;
} gl_wrap_handler_glGenRenderbuffers_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glRenderbufferStorage_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetRenderbufferParameteriv_args;

typedef struct {
	GLenum target;
	GLuint framebuffer;
} gl_wrap_handler_glBindFramebuffer_args;

typedef struct {
	GLsizei n;
	GLuint* framebuffers;
} gl_wrap_handler_glDeleteFramebuffers_args;

typedef struct {
	GLsizei n;
	GLuint* framebuffers;
} gl_wrap_handler_glGenFramebuffers_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum textarget;
	GLuint texture;
	GLint level;
} gl_wrap_handler_glFramebufferTexture1D_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum textarget;
	GLuint texture;
	GLint level;
} gl_wrap_handler_glFramebufferTexture2D_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum textarget;
	GLuint texture;
	GLint level;
	GLint zoffset;
} gl_wrap_handler_glFramebufferTexture3D_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum renderbuffertarget;
	GLuint renderbuffer;
} gl_wrap_handler_glFramebufferRenderbuffer_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args;

typedef struct {
	GLenum target;
} gl_wrap_handler_glGenerateMipmap_args;

typedef struct {
	GLint srcX0;
	GLint srcY0;
	GLint srcX1;
	GLint srcY1;
	GLint dstX0;
	GLint dstY0;
	GLint dstX1;
	GLint dstY1;
	GLbitfield mask;
	GLenum filter;
} gl_wrap_handler_glBlitFramebuffer_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glRenderbufferStorageMultisample_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLuint texture;
	GLint level;
	GLint layer;
} gl_wrap_handler_glFramebufferTextureLayer_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr length;
	GLbitfield access;
} gl_wrap_handler_glMapBufferRange_args;

typedef struct {
	GLenum target;
	GLintptr offset;
	GLsizeiptr length;
} gl_wrap_handler_glFlushMappedBufferRange_args;

typedef struct {
	GLuint array;
} gl_wrap_handler_glBindVertexArray_args;

typedef struct {
	GLsizei n;
	GLuint* arrays;
} gl_wrap_handler_glDeleteVertexArrays_args;

typedef struct {
	GLsizei n;
	GLuint* arrays;
} gl_wrap_handler_glGenVertexArrays_args;

typedef struct {
	GLenum mode;
	GLint first;
	GLsizei count;
	GLsizei instancecount;
} gl_wrap_handler_glDrawArraysInstanced_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
	GLsizei instancecount;
} gl_wrap_handler_glDrawElementsInstanced_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLuint buffer;
} gl_wrap_handler_glTexBuffer_args;

typedef struct {
	GLuint index;
} gl_wrap_handler_glPrimitiveRestartIndex_args;

typedef struct {
	GLenum readTarget;
	GLenum writeTarget;
	GLintptr readOffset;
	GLintptr writeOffset;
	GLsizeiptr size;
} gl_wrap_handler_glCopyBufferSubData_args;

typedef struct {
	GLuint program;
	GLsizei uniformCount;
	GLchar** uniformNames;
	GLuint* uniformIndices;
} gl_wrap_handler_glGetUniformIndices_args;

typedef struct {
	GLuint program;
	GLsizei uniformCount;
	GLuint* uniformIndices;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetActiveUniformsiv_args;

typedef struct {
	GLuint program;
	GLuint uniformIndex;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* uniformName;
} gl_wrap_handler_glGetActiveUniformName_args;

typedef struct {
	GLuint program;
	GLuint uniformBlockIndex;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetActiveUniformBlockiv_args;

typedef struct {
	GLuint program;
	GLuint uniformBlockIndex;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* uniformBlockName;
} gl_wrap_handler_glGetActiveUniformBlockName_args;

typedef struct {
	GLuint program;
	GLuint uniformBlockIndex;
	GLuint uniformBlockBinding;
} gl_wrap_handler_glUniformBlockBinding_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
	GLint basevertex;
} gl_wrap_handler_glDrawElementsBaseVertex_args;

typedef struct {
	GLenum mode;
	GLuint start;
	GLuint end;
	GLsizei count;
	GLenum type;
	void* indices;
	GLint basevertex;
} gl_wrap_handler_glDrawRangeElementsBaseVertex_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
	GLsizei instancecount;
	GLint basevertex;
} gl_wrap_handler_glDrawElementsInstancedBaseVertex_args;

typedef struct {
	GLenum mode;
	GLsizei* count;
	GLenum type;
	void** indices;
	GLsizei drawcount;
	GLint* basevertex;
} gl_wrap_handler_glMultiDrawElementsBaseVertex_args;

typedef struct {
	GLenum mode;
} gl_wrap_handler_glProvokingVertex_args;

typedef struct {
	GLsync sync;
} gl_wrap_handler_glDeleteSync_args;

typedef struct {
	GLsync sync;
	GLbitfield flags;
	GLuint64 timeout;
} gl_wrap_handler_glWaitSync_args;

typedef struct {
	GLenum pname;
	GLint64* data;
} gl_wrap_handler_glGetInteger64v_args;

typedef struct {
	GLsync sync;
	GLenum pname;
	GLsizei bufSize;
	GLsizei* length;
	GLint* values;
} gl_wrap_handler_glGetSynciv_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLint64* data;
} gl_wrap_handler_glGetInteger64i_v_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint64* params;
} gl_wrap_handler_glGetBufferParameteri64v_args;

typedef struct {
	GLenum target;
	GLenum attachment;
	GLuint texture;
	GLint level;
} gl_wrap_handler_glFramebufferTexture_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLboolean fixedsamplelocations;
} gl_wrap_handler_glTexImage2DMultisample_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLboolean fixedsamplelocations;
} gl_wrap_handler_glTexImage3DMultisample_args;

typedef struct {
	GLenum pname;
	GLuint index;
	GLfloat* val;
} gl_wrap_handler_glGetMultisamplefv_args;

typedef struct {
	GLuint maskNumber;
	GLbitfield mask;
} gl_wrap_handler_glSampleMaski_args;

typedef struct {
	GLuint program;
	GLuint colorNumber;
	GLuint index;
	GLchar* name;
} gl_wrap_handler_glBindFragDataLocationIndexed_args;

typedef struct {
	GLsizei count;
	GLuint* samplers;
} gl_wrap_handler_glGenSamplers_args;

typedef struct {
	GLsizei count;
	GLuint* samplers;
} gl_wrap_handler_glDeleteSamplers_args;

typedef struct {
	GLuint unit;
	GLuint sampler;
} gl_wrap_handler_glBindSampler_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glSamplerParameteri_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint* param;
} gl_wrap_handler_glSamplerParameteriv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLfloat param;
} gl_wrap_handler_glSamplerParameterf_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLfloat* param;
} gl_wrap_handler_glSamplerParameterfv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint* param;
} gl_wrap_handler_glSamplerParameterIiv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLuint* param;
} gl_wrap_handler_glSamplerParameterIuiv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetSamplerParameteriv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetSamplerParameterIiv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLfloat* params;
} gl_wrap_handler_glGetSamplerParameterfv_args;

typedef struct {
	GLuint sampler;
	GLenum pname;
	GLuint* params;
} gl_wrap_handler_glGetSamplerParameterIuiv_args;

typedef struct {
	GLuint id;
	GLenum target;
} gl_wrap_handler_glQueryCounter_args;

typedef struct {
	GLuint id;
	GLenum pname;
	GLint64* params;
} gl_wrap_handler_glGetQueryObjecti64v_args;

typedef struct {
	GLuint id;
	GLenum pname;
	GLuint64* params;
} gl_wrap_handler_glGetQueryObjectui64v_args;

typedef struct {
	GLuint index;
	GLuint divisor;
} gl_wrap_handler_glVertexAttribDivisor_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint value;
} gl_wrap_handler_glVertexAttribP1ui_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint* value;
} gl_wrap_handler_glVertexAttribP1uiv_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint value;
} gl_wrap_handler_glVertexAttribP2ui_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint* value;
} gl_wrap_handler_glVertexAttribP2uiv_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint value;
} gl_wrap_handler_glVertexAttribP3ui_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint* value;
} gl_wrap_handler_glVertexAttribP3uiv_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint value;
} gl_wrap_handler_glVertexAttribP4ui_args;

typedef struct {
	GLuint index;
	GLenum type;
	GLboolean normalized;
	GLuint* value;
} gl_wrap_handler_glVertexAttribP4uiv_args;

typedef struct {
	GLenum type;
	GLuint value;
} gl_wrap_handler_glVertexP2ui_args;

typedef struct {
	GLenum type;
	GLuint* value;
} gl_wrap_handler_glVertexP2uiv_args;

typedef struct {
	GLenum type;
	GLuint value;
} gl_wrap_handler_glVertexP3ui_args;

typedef struct {
	GLenum type;
	GLuint* value;
} gl_wrap_handler_glVertexP3uiv_args;

typedef struct {
	GLenum type;
	GLuint value;
} gl_wrap_handler_glVertexP4ui_args;

typedef struct {
	GLenum type;
	GLuint* value;
} gl_wrap_handler_glVertexP4uiv_args;

typedef struct {
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glTexCoordP1ui_args;

typedef struct {
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glTexCoordP1uiv_args;

typedef struct {
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glTexCoordP2ui_args;

typedef struct {
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glTexCoordP2uiv_args;

typedef struct {
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glTexCoordP3ui_args;

typedef struct {
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glTexCoordP3uiv_args;

typedef struct {
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glTexCoordP4ui_args;

typedef struct {
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glTexCoordP4uiv_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glMultiTexCoordP1ui_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glMultiTexCoordP1uiv_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glMultiTexCoordP2ui_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glMultiTexCoordP2uiv_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glMultiTexCoordP3ui_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glMultiTexCoordP3uiv_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glMultiTexCoordP4ui_args;

typedef struct {
	GLenum texture;
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glMultiTexCoordP4uiv_args;

typedef struct {
	GLenum type;
	GLuint coords;
} gl_wrap_handler_glNormalP3ui_args;

typedef struct {
	GLenum type;
	GLuint* coords;
} gl_wrap_handler_glNormalP3uiv_args;

typedef struct {
	GLenum type;
	GLuint color;
} gl_wrap_handler_glColorP3ui_args;

typedef struct {
	GLenum type;
	GLuint* color;
} gl_wrap_handler_glColorP3uiv_args;

typedef struct {
	GLenum type;
	GLuint color;
} gl_wrap_handler_glColorP4ui_args;

typedef struct {
	GLenum type;
	GLuint* color;
} gl_wrap_handler_glColorP4uiv_args;

typedef struct {
	GLenum type;
	GLuint color;
} gl_wrap_handler_glSecondaryColorP3ui_args;

typedef struct {
	GLenum type;
	GLuint* color;
} gl_wrap_handler_glSecondaryColorP3uiv_args;

typedef struct {
	GLfloat value;
} gl_wrap_handler_glMinSampleShading_args;

typedef struct {
	GLuint buf;
	GLenum mode;
} gl_wrap_handler_glBlendEquationi_args;

typedef struct {
	GLuint buf;
	GLenum modeRGB;
	GLenum modeAlpha;
} gl_wrap_handler_glBlendEquationSeparatei_args;

typedef struct {
	GLuint buf;
	GLenum src;
	GLenum dst;
} gl_wrap_handler_glBlendFunci_args;

typedef struct {
	GLuint buf;
	GLenum srcRGB;
	GLenum dstRGB;
	GLenum srcAlpha;
	GLenum dstAlpha;
} gl_wrap_handler_glBlendFuncSeparatei_args;

typedef struct {
	GLenum mode;
	void* indirect;
} gl_wrap_handler_glDrawArraysIndirect_args;

typedef struct {
	GLenum mode;
	GLenum type;
	void* indirect;
} gl_wrap_handler_glDrawElementsIndirect_args;

typedef struct {
	GLint location;
	GLdouble x;
} gl_wrap_handler_glUniform1d_args;

typedef struct {
	GLint location;
	GLdouble x;
	GLdouble y;
} gl_wrap_handler_glUniform2d_args;

typedef struct {
	GLint location;
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glUniform3d_args;

typedef struct {
	GLint location;
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble w;
} gl_wrap_handler_glUniform4d_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glUniform1dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glUniform2dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glUniform3dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glUniform4dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix2dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix3dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix4dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix2x3dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix2x4dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix3x2dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix3x4dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix4x2dv_args;

typedef struct {
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glUniformMatrix4x3dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLdouble* params;
} gl_wrap_handler_glGetUniformdv_args;

typedef struct {
	GLuint program;
	GLenum shadertype;
	GLuint index;
	GLenum pname;
	GLint* values;
} gl_wrap_handler_glGetActiveSubroutineUniformiv_args;

typedef struct {
	GLuint program;
	GLenum shadertype;
	GLuint index;
	GLsizei bufsize;
	GLsizei* length;
	GLchar* name;
} gl_wrap_handler_glGetActiveSubroutineUniformName_args;

typedef struct {
	GLuint program;
	GLenum shadertype;
	GLuint index;
	GLsizei bufsize;
	GLsizei* length;
	GLchar* name;
} gl_wrap_handler_glGetActiveSubroutineName_args;

typedef struct {
	GLenum shadertype;
	GLsizei count;
	GLuint* indices;
} gl_wrap_handler_glUniformSubroutinesuiv_args;

typedef struct {
	GLenum shadertype;
	GLint location;
	GLuint* params;
} gl_wrap_handler_glGetUniformSubroutineuiv_args;

typedef struct {
	GLuint program;
	GLenum shadertype;
	GLenum pname;
	GLint* values;
} gl_wrap_handler_glGetProgramStageiv_args;

typedef struct {
	GLenum pname;
	GLint value;
} gl_wrap_handler_glPatchParameteri_args;

typedef struct {
	GLenum pname;
	GLfloat* values;
} gl_wrap_handler_glPatchParameterfv_args;

typedef struct {
	GLenum target;
	GLuint id;
} gl_wrap_handler_glBindTransformFeedback_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glDeleteTransformFeedbacks_args;

typedef struct {
	GLsizei n;
	GLuint* ids;
} gl_wrap_handler_glGenTransformFeedbacks_args;

typedef struct {
} gl_wrap_handler_glPauseTransformFeedback_args;

typedef struct {
} gl_wrap_handler_glResumeTransformFeedback_args;

typedef struct {
	GLenum mode;
	GLuint id;
} gl_wrap_handler_glDrawTransformFeedback_args;

typedef struct {
	GLenum mode;
	GLuint id;
	GLuint stream;
} gl_wrap_handler_glDrawTransformFeedbackStream_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLuint id;
} gl_wrap_handler_glBeginQueryIndexed_args;

typedef struct {
	GLenum target;
	GLuint index;
} gl_wrap_handler_glEndQueryIndexed_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetQueryIndexediv_args;

typedef struct {
} gl_wrap_handler_glReleaseShaderCompiler_args;

typedef struct {
	GLsizei count;
	GLuint* shaders;
	GLenum binaryformat;
	void* binary;
	GLsizei length;
} gl_wrap_handler_glShaderBinary_args;

typedef struct {
	GLenum shadertype;
	GLenum precisiontype;
	GLint* range;
	GLint* precision;
} gl_wrap_handler_glGetShaderPrecisionFormat_args;

typedef struct {
	GLfloat n;
	GLfloat f;
} gl_wrap_handler_glDepthRangef_args;

typedef struct {
	GLfloat d;
} gl_wrap_handler_glClearDepthf_args;

typedef struct {
	GLuint program;
	GLsizei bufSize;
	GLsizei* length;
	GLenum* binaryFormat;
	void* binary;
} gl_wrap_handler_glGetProgramBinary_args;

typedef struct {
	GLuint program;
	GLenum binaryFormat;
	void* binary;
	GLsizei length;
} gl_wrap_handler_glProgramBinary_args;

typedef struct {
	GLuint program;
	GLenum pname;
	GLint value;
} gl_wrap_handler_glProgramParameteri_args;

typedef struct {
	GLuint pipeline;
	GLbitfield stages;
	GLuint program;
} gl_wrap_handler_glUseProgramStages_args;

typedef struct {
	GLuint pipeline;
	GLuint program;
} gl_wrap_handler_glActiveShaderProgram_args;

typedef struct {
	GLuint pipeline;
} gl_wrap_handler_glBindProgramPipeline_args;

typedef struct {
	GLsizei n;
	GLuint* pipelines;
} gl_wrap_handler_glDeleteProgramPipelines_args;

typedef struct {
	GLsizei n;
	GLuint* pipelines;
} gl_wrap_handler_glGenProgramPipelines_args;

typedef struct {
	GLuint pipeline;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetProgramPipelineiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
} gl_wrap_handler_glProgramUniform1i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform1iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
} gl_wrap_handler_glProgramUniform1f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform1fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLdouble v0;
} gl_wrap_handler_glProgramUniform1d_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glProgramUniform1dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
} gl_wrap_handler_glProgramUniform1ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform1uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
	GLint v1;
} gl_wrap_handler_glProgramUniform2i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform2iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
	GLfloat v1;
} gl_wrap_handler_glProgramUniform2f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLdouble v0;
	GLdouble v1;
} gl_wrap_handler_glProgramUniform2d_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glProgramUniform2dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
	GLuint v1;
} gl_wrap_handler_glProgramUniform2ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform2uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
} gl_wrap_handler_glProgramUniform3i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform3iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
} gl_wrap_handler_glProgramUniform3f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLdouble v0;
	GLdouble v1;
	GLdouble v2;
} gl_wrap_handler_glProgramUniform3d_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glProgramUniform3dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
} gl_wrap_handler_glProgramUniform3ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform3uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLint v0;
	GLint v1;
	GLint v2;
	GLint v3;
} gl_wrap_handler_glProgramUniform4i_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLint* value;
} gl_wrap_handler_glProgramUniform4iv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;
} gl_wrap_handler_glProgramUniform4f_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLfloat* value;
} gl_wrap_handler_glProgramUniform4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLdouble v0;
	GLdouble v1;
	GLdouble v2;
	GLdouble v3;
} gl_wrap_handler_glProgramUniform4d_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLdouble* value;
} gl_wrap_handler_glProgramUniform4dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLuint v0;
	GLuint v1;
	GLuint v2;
	GLuint v3;
} gl_wrap_handler_glProgramUniform4ui_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLuint* value;
} gl_wrap_handler_glProgramUniform4uiv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix2dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix3dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix4dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix2x3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix3x2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix2x4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix4x2fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix3x4fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat* value;
} gl_wrap_handler_glProgramUniformMatrix4x3fv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix2x3dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix3x2dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix2x4dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix4x2dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix3x4dv_args;

typedef struct {
	GLuint program;
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLdouble* value;
} gl_wrap_handler_glProgramUniformMatrix4x3dv_args;

typedef struct {
	GLuint pipeline;
} gl_wrap_handler_glValidateProgramPipeline_args;

typedef struct {
	GLuint pipeline;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* infoLog;
} gl_wrap_handler_glGetProgramPipelineInfoLog_args;

typedef struct {
	GLuint index;
	GLdouble x;
} gl_wrap_handler_glVertexAttribL1d_args;

typedef struct {
	GLuint index;
	GLdouble x;
	GLdouble y;
} gl_wrap_handler_glVertexAttribL2d_args;

typedef struct {
	GLuint index;
	GLdouble x;
	GLdouble y;
	GLdouble z;
} gl_wrap_handler_glVertexAttribL3d_args;

typedef struct {
	GLuint index;
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble w;
} gl_wrap_handler_glVertexAttribL4d_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttribL1dv_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttribL2dv_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttribL3dv_args;

typedef struct {
	GLuint index;
	GLdouble* v;
} gl_wrap_handler_glVertexAttribL4dv_args;

typedef struct {
	GLuint index;
	GLint size;
	GLenum type;
	GLsizei stride;
	void* pointer;
} gl_wrap_handler_glVertexAttribLPointer_args;

typedef struct {
	GLuint index;
	GLenum pname;
	GLdouble* params;
} gl_wrap_handler_glGetVertexAttribLdv_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLfloat* v;
} gl_wrap_handler_glViewportArrayv_args;

typedef struct {
	GLuint index;
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
} gl_wrap_handler_glViewportIndexedf_args;

typedef struct {
	GLuint index;
	GLfloat* v;
} gl_wrap_handler_glViewportIndexedfv_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLint* v;
} gl_wrap_handler_glScissorArrayv_args;

typedef struct {
	GLuint index;
	GLint left;
	GLint bottom;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glScissorIndexed_args;

typedef struct {
	GLuint index;
	GLint* v;
} gl_wrap_handler_glScissorIndexedv_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLdouble* v;
} gl_wrap_handler_glDepthRangeArrayv_args;

typedef struct {
	GLuint index;
	GLdouble n;
	GLdouble f;
} gl_wrap_handler_glDepthRangeIndexed_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLfloat* data;
} gl_wrap_handler_glGetFloati_v_args;

typedef struct {
	GLenum target;
	GLuint index;
	GLdouble* data;
} gl_wrap_handler_glGetDoublei_v_args;

typedef struct {
	GLenum mode;
	GLint first;
	GLsizei count;
	GLsizei instancecount;
	GLuint baseinstance;
} gl_wrap_handler_glDrawArraysInstancedBaseInstance_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
	GLsizei instancecount;
	GLuint baseinstance;
} gl_wrap_handler_glDrawElementsInstancedBaseInstance_args;

typedef struct {
	GLenum mode;
	GLsizei count;
	GLenum type;
	void* indices;
	GLsizei instancecount;
	GLint basevertex;
	GLuint baseinstance;
} gl_wrap_handler_glDrawElementsInstancedBaseVertexBaseInstance_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLenum pname;
	GLsizei bufSize;
	GLint* params;
} gl_wrap_handler_glGetInternalformativ_args;

typedef struct {
	GLuint program;
	GLuint bufferIndex;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetActiveAtomicCounterBufferiv_args;

typedef struct {
	GLuint unit;
	GLuint texture;
	GLint level;
	GLboolean layered;
	GLint layer;
	GLenum access;
	GLenum format;
} gl_wrap_handler_glBindImageTexture_args;

typedef struct {
	GLbitfield barriers;
} gl_wrap_handler_glMemoryBarrier_args;

typedef struct {
	GLenum target;
	GLsizei levels;
	GLenum internalformat;
	GLsizei width;
} gl_wrap_handler_glTexStorage1D_args;

typedef struct {
	GLenum target;
	GLsizei levels;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glTexStorage2D_args;

typedef struct {
	GLenum target;
	GLsizei levels;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
} gl_wrap_handler_glTexStorage3D_args;

typedef struct {
	GLenum mode;
	GLuint id;
	GLsizei instancecount;
} gl_wrap_handler_glDrawTransformFeedbackInstanced_args;

typedef struct {
	GLenum mode;
	GLuint id;
	GLuint stream;
	GLsizei instancecount;
} gl_wrap_handler_glDrawTransformFeedbackStreamInstanced_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLenum format;
	GLenum type;
	void* data;
} gl_wrap_handler_glClearBufferData_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLintptr offset;
	GLsizeiptr size;
	GLenum format;
	GLenum type;
	void* data;
} gl_wrap_handler_glClearBufferSubData_args;

typedef struct {
	GLuint num_groups_x;
	GLuint num_groups_y;
	GLuint num_groups_z;
} gl_wrap_handler_glDispatchCompute_args;

typedef struct {
	GLintptr indirect;
} gl_wrap_handler_glDispatchComputeIndirect_args;

typedef struct {
	GLuint srcName;
	GLenum srcTarget;
	GLint srcLevel;
	GLint srcX;
	GLint srcY;
	GLint srcZ;
	GLuint dstName;
	GLenum dstTarget;
	GLint dstLevel;
	GLint dstX;
	GLint dstY;
	GLint dstZ;
	GLsizei srcWidth;
	GLsizei srcHeight;
	GLsizei srcDepth;
} gl_wrap_handler_glCopyImageSubData_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint param;
} gl_wrap_handler_glFramebufferParameteri_args;

typedef struct {
	GLenum target;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetFramebufferParameteriv_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLenum pname;
	GLsizei bufSize;
	GLint64* params;
} gl_wrap_handler_glGetInternalformati64v_args;

typedef struct {
	GLuint texture;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
} gl_wrap_handler_glInvalidateTexSubImage_args;

typedef struct {
	GLuint texture;
	GLint level;
} gl_wrap_handler_glInvalidateTexImage_args;

typedef struct {
	GLuint buffer;
	GLintptr offset;
	GLsizeiptr length;
} gl_wrap_handler_glInvalidateBufferSubData_args;

typedef struct {
	GLuint buffer;
} gl_wrap_handler_glInvalidateBufferData_args;

typedef struct {
	GLenum target;
	GLsizei numAttachments;
	GLenum* attachments;
} gl_wrap_handler_glInvalidateFramebuffer_args;

typedef struct {
	GLenum target;
	GLsizei numAttachments;
	GLenum* attachments;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
} gl_wrap_handler_glInvalidateSubFramebuffer_args;

typedef struct {
	GLenum mode;
	void* indirect;
	GLsizei drawcount;
	GLsizei stride;
} gl_wrap_handler_glMultiDrawArraysIndirect_args;

typedef struct {
	GLenum mode;
	GLenum type;
	void* indirect;
	GLsizei drawcount;
	GLsizei stride;
} gl_wrap_handler_glMultiDrawElementsIndirect_args;

typedef struct {
	GLuint program;
	GLenum programInterface;
	GLenum pname;
	GLint* params;
} gl_wrap_handler_glGetProgramInterfaceiv_args;

typedef struct {
	GLuint program;
	GLenum programInterface;
	GLuint index;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* name;
} gl_wrap_handler_glGetProgramResourceName_args;

typedef struct {
	GLuint program;
	GLenum programInterface;
	GLuint index;
	GLsizei propCount;
	GLenum* props;
	GLsizei bufSize;
	GLsizei* length;
	GLint* params;
} gl_wrap_handler_glGetProgramResourceiv_args;

typedef struct {
	GLuint program;
	GLuint storageBlockIndex;
	GLuint storageBlockBinding;
} gl_wrap_handler_glShaderStorageBlockBinding_args;

typedef struct {
	GLenum target;
	GLenum internalformat;
	GLuint buffer;
	GLintptr offset;
	GLsizeiptr size;
} gl_wrap_handler_glTexBufferRange_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLboolean fixedsamplelocations;
} gl_wrap_handler_glTexStorage2DMultisample_args;

typedef struct {
	GLenum target;
	GLsizei samples;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLboolean fixedsamplelocations;
} gl_wrap_handler_glTexStorage3DMultisample_args;

typedef struct {
	GLuint texture;
	GLenum target;
	GLuint origtexture;
	GLenum internalformat;
	GLuint minlevel;
	GLuint numlevels;
	GLuint minlayer;
	GLuint numlayers;
} gl_wrap_handler_glTextureView_args;

typedef struct {
	GLuint bindingindex;
	GLuint buffer;
	GLintptr offset;
	GLsizei stride;
} gl_wrap_handler_glBindVertexBuffer_args;

typedef struct {
	GLuint attribindex;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLuint relativeoffset;
} gl_wrap_handler_glVertexAttribFormat_args;

typedef struct {
	GLuint attribindex;
	GLint size;
	GLenum type;
	GLuint relativeoffset;
} gl_wrap_handler_glVertexAttribIFormat_args;

typedef struct {
	GLuint attribindex;
	GLint size;
	GLenum type;
	GLuint relativeoffset;
} gl_wrap_handler_glVertexAttribLFormat_args;

typedef struct {
	GLuint attribindex;
	GLuint bindingindex;
} gl_wrap_handler_glVertexAttribBinding_args;

typedef struct {
	GLuint bindingindex;
	GLuint divisor;
} gl_wrap_handler_glVertexBindingDivisor_args;

typedef struct {
	GLenum source;
	GLenum type;
	GLenum severity;
	GLsizei count;
	GLuint* ids;
	GLboolean enabled;
} gl_wrap_handler_glDebugMessageControl_args;

typedef struct {
	GLenum source;
	GLenum type;
	GLuint id;
	GLenum severity;
	GLsizei length;
	GLchar* buf;
} gl_wrap_handler_glDebugMessageInsert_args;

typedef struct {
	GLDEBUGPROC callback;
	void* userParam;
} gl_wrap_handler_glDebugMessageCallback_args;

typedef struct {
	GLenum source;
	GLuint id;
	GLsizei length;
	GLchar* message;
} gl_wrap_handler_glPushDebugGroup_args;

typedef struct {
} gl_wrap_handler_glPopDebugGroup_args;

typedef struct {
	GLenum identifier;
	GLuint name;
	GLsizei length;
	GLchar* label;
} gl_wrap_handler_glObjectLabel_args;

typedef struct {
	GLenum identifier;
	GLuint name;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* label;
} gl_wrap_handler_glGetObjectLabel_args;

typedef struct {
	void* ptr;
	GLsizei length;
	GLchar* label;
} gl_wrap_handler_glObjectPtrLabel_args;

typedef struct {
	void* ptr;
	GLsizei bufSize;
	GLsizei* length;
	GLchar* label;
} gl_wrap_handler_glGetObjectPtrLabel_args;

typedef struct {
	GLenum target;
	GLsizeiptr size;
	void* data;
	GLbitfield flags;
} gl_wrap_handler_glBufferStorage_args;

typedef struct {
	GLuint texture;
	GLint level;
	GLenum format;
	GLenum type;
	void* data;
} gl_wrap_handler_glClearTexImage_args;

typedef struct {
	GLuint texture;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLenum format;
	GLenum type;
	void* data;
} gl_wrap_handler_glClearTexSubImage_args;

typedef struct {
	GLenum target;
	GLuint first;
	GLsizei count;
	GLuint* buffers;
} gl_wrap_handler_glBindBuffersBase_args;

typedef struct {
	GLenum target;
	GLuint first;
	GLsizei count;
	GLuint* buffers;
	GLintptr* offsets;
	GLsizeiptr* sizes;
} gl_wrap_handler_glBindBuffersRange_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLuint* textures;
} gl_wrap_handler_glBindTextures_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLuint* samplers;
} gl_wrap_handler_glBindSamplers_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLuint* textures;
} gl_wrap_handler_glBindImageTextures_args;

typedef struct {
	GLuint first;
	GLsizei count;
	GLuint* buffers;
	GLintptr* offsets;
	GLsizei* strides;
} gl_wrap_handler_glBindVertexBuffers_args;



// Other custom definitions
typedef void (*gl_wrap_jump_handler)(gl_wrap_context* ctx, void* args);

typedef struct {
	int jump_index;
	void* args;
} gl_wrap_batch_func;

void gl_wrap_batch_exec(gl_wrap_context* ctx, gl_wrap_batch_func* funcs, int numFuncs);

#endif
