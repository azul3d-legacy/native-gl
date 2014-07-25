// Copyright 2014 The Azul3D Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
//
// This source file was automatically generated using glwrap.

#include "gl.h"

typedef void (*__glwrap_func_ptr)(void);

#if defined(__WIN32) || defined(__WIN64)
	typedef void* HMODULE;
	typedef int (*FARPROC)(void);
	typedef int (*PROC)(void);

	//extern PROC wglGetProcAddress(const char* name);
	extern HMODULE LoadLibraryA(const char* name);
	extern FARPROC GetProcAddress(HMODULE, const char*);

	HMODULE glwrap_OpenGL32;


	typedef PROC (*__glwrap_PFNWGLGETPROCADDRESS)(const char*);
	__glwrap_PFNWGLGETPROCADDRESS __glwrap_wglGetProcAddressPtr;
	inline PROC __glwrap_wglGetProcAddress(const char* name) {
		if(__glwrap_wglGetProcAddressPtr == NULL) {
			if(glwrap_OpenGL32 == NULL) {
				glwrap_OpenGL32 = LoadLibraryA("opengl32.dll");
			}
			__glwrap_wglGetProcAddressPtr = (__glwrap_PFNWGLGETPROCADDRESS)GetProcAddress(glwrap_OpenGL32, "wglGetProcAddress");
		}
		return __glwrap_wglGetProcAddressPtr(name);
	}

#elif defined(__linux) || defined(__unix) || defined(__posix)
	// See http://dri.freedesktop.org/wiki/glXGetProcAddressNeverReturnsNULL
	//
	// glXGetProcAddressARB is *required* to be statically defined in libGL,
	// but glXGetProcAddress is not, and will fail to be found in nvidia's
	// libGL
	extern __glwrap_func_ptr glXGetProcAddressARB(const GLubyte * procName);

#elif defined(__APPLE__)
	// Todo: OS X support.
#endif

inline __glwrap_func_ptr gl_wrap_get_pointer(const char* name) {
	#if defined(__WIN32) || defined(__WIN64)
		void* ptr = __glwrap_wglGetProcAddress(name);
		intptr_t iptr = (intptr_t)ptr;

		if(iptr == 0 || iptr == 1 || iptr == 2 || iptr == 3 || iptr == -1) {
			// Could be a core function, then.

			// No need for this: because it's done in wglGetProcAddress()
			//if(glwrap_OpenGL32 == NULL) {
			//	glwrap_OpenGL32 = LoadLibraryA("opengl32.dll");
			//}
			return (__glwrap_func_ptr)GetProcAddress(glwrap_OpenGL32, name);
		}

		return ptr;

	#elif defined(__linux) || defined(__unix) || defined(__posix)
		return glXGetProcAddressARB(name);

	#elif defined(__APPLE__)
		// Todo: OS X support.
	#endif
}

// Function definition for each appropriate OpenGL function.
//
// If the pointer in the context for the function is null; it is loaded
// immedietly (as such this is effectively lazy-loading).
void gl_wrap_context_glCullFace(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glCullFaceProc == NULL) {
		ctx->glCullFaceProc = (PFNGLCULLFACEPROC)gl_wrap_get_pointer("glCullFace");
	}
	ctx->glCullFaceProc(mode);
};
void gl_wrap_context_glFrontFace(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glFrontFaceProc == NULL) {
		ctx->glFrontFaceProc = (PFNGLFRONTFACEPROC)gl_wrap_get_pointer("glFrontFace");
	}
	ctx->glFrontFaceProc(mode);
};
void gl_wrap_context_glHint(gl_wrap_context* ctx, GLenum target, GLenum mode) {
	if(ctx->glHintProc == NULL) {
		ctx->glHintProc = (PFNGLHINTPROC)gl_wrap_get_pointer("glHint");
	}
	ctx->glHintProc(target, mode);
};
void gl_wrap_context_glLineWidth(gl_wrap_context* ctx, GLfloat width) {
	if(ctx->glLineWidthProc == NULL) {
		ctx->glLineWidthProc = (PFNGLLINEWIDTHPROC)gl_wrap_get_pointer("glLineWidth");
	}
	ctx->glLineWidthProc(width);
};
void gl_wrap_context_glPointSize(gl_wrap_context* ctx, GLfloat size) {
	if(ctx->glPointSizeProc == NULL) {
		ctx->glPointSizeProc = (PFNGLPOINTSIZEPROC)gl_wrap_get_pointer("glPointSize");
	}
	ctx->glPointSizeProc(size);
};
void gl_wrap_context_glPolygonMode(gl_wrap_context* ctx, GLenum face, GLenum mode) {
	if(ctx->glPolygonModeProc == NULL) {
		ctx->glPolygonModeProc = (PFNGLPOLYGONMODEPROC)gl_wrap_get_pointer("glPolygonMode");
	}
	ctx->glPolygonModeProc(face, mode);
};
void gl_wrap_context_glScissor(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glScissorProc == NULL) {
		ctx->glScissorProc = (PFNGLSCISSORPROC)gl_wrap_get_pointer("glScissor");
	}
	ctx->glScissorProc(x, y, width, height);
};
void gl_wrap_context_glTexParameterf(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat param) {
	if(ctx->glTexParameterfProc == NULL) {
		ctx->glTexParameterfProc = (PFNGLTEXPARAMETERFPROC)gl_wrap_get_pointer("glTexParameterf");
	}
	ctx->glTexParameterfProc(target, pname, param);
};
void gl_wrap_context_glTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params) {
	if(ctx->glTexParameterfvProc == NULL) {
		ctx->glTexParameterfvProc = (PFNGLTEXPARAMETERFVPROC)gl_wrap_get_pointer("glTexParameterfv");
	}
	ctx->glTexParameterfvProc(target, pname, params);
};
void gl_wrap_context_glTexParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param) {
	if(ctx->glTexParameteriProc == NULL) {
		ctx->glTexParameteriProc = (PFNGLTEXPARAMETERIPROC)gl_wrap_get_pointer("glTexParameteri");
	}
	ctx->glTexParameteriProc(target, pname, param);
};
void gl_wrap_context_glTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glTexParameterivProc == NULL) {
		ctx->glTexParameterivProc = (PFNGLTEXPARAMETERIVPROC)gl_wrap_get_pointer("glTexParameteriv");
	}
	ctx->glTexParameterivProc(target, pname, params);
};
void gl_wrap_context_glTexImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexImage1DProc == NULL) {
		ctx->glTexImage1DProc = (PFNGLTEXIMAGE1DPROC)gl_wrap_get_pointer("glTexImage1D");
	}
	ctx->glTexImage1DProc(target, level, internalformat, width, border, format, type, pixels);
};
void gl_wrap_context_glTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexImage2DProc == NULL) {
		ctx->glTexImage2DProc = (PFNGLTEXIMAGE2DPROC)gl_wrap_get_pointer("glTexImage2D");
	}
	ctx->glTexImage2DProc(target, level, internalformat, width, height, border, format, type, pixels);
};
void gl_wrap_context_glDrawBuffer(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glDrawBufferProc == NULL) {
		ctx->glDrawBufferProc = (PFNGLDRAWBUFFERPROC)gl_wrap_get_pointer("glDrawBuffer");
	}
	ctx->glDrawBufferProc(mode);
};
void gl_wrap_context_glClear(gl_wrap_context* ctx, GLbitfield mask) {
	if(ctx->glClearProc == NULL) {
		ctx->glClearProc = (PFNGLCLEARPROC)gl_wrap_get_pointer("glClear");
	}
	ctx->glClearProc(mask);
};
void gl_wrap_context_glClearColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if(ctx->glClearColorProc == NULL) {
		ctx->glClearColorProc = (PFNGLCLEARCOLORPROC)gl_wrap_get_pointer("glClearColor");
	}
	ctx->glClearColorProc(red, green, blue, alpha);
};
void gl_wrap_context_glClearStencil(gl_wrap_context* ctx, GLint s) {
	if(ctx->glClearStencilProc == NULL) {
		ctx->glClearStencilProc = (PFNGLCLEARSTENCILPROC)gl_wrap_get_pointer("glClearStencil");
	}
	ctx->glClearStencilProc(s);
};
void gl_wrap_context_glClearDepth(gl_wrap_context* ctx, GLdouble depth) {
	if(ctx->glClearDepthProc == NULL) {
		ctx->glClearDepthProc = (PFNGLCLEARDEPTHPROC)gl_wrap_get_pointer("glClearDepth");
	}
	ctx->glClearDepthProc(depth);
};
void gl_wrap_context_glStencilMask(gl_wrap_context* ctx, GLuint mask) {
	if(ctx->glStencilMaskProc == NULL) {
		ctx->glStencilMaskProc = (PFNGLSTENCILMASKPROC)gl_wrap_get_pointer("glStencilMask");
	}
	ctx->glStencilMaskProc(mask);
};
void gl_wrap_context_glColorMask(gl_wrap_context* ctx, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
	if(ctx->glColorMaskProc == NULL) {
		ctx->glColorMaskProc = (PFNGLCOLORMASKPROC)gl_wrap_get_pointer("glColorMask");
	}
	ctx->glColorMaskProc(red, green, blue, alpha);
};
void gl_wrap_context_glDepthMask(gl_wrap_context* ctx, GLboolean flag) {
	if(ctx->glDepthMaskProc == NULL) {
		ctx->glDepthMaskProc = (PFNGLDEPTHMASKPROC)gl_wrap_get_pointer("glDepthMask");
	}
	ctx->glDepthMaskProc(flag);
};
void gl_wrap_context_glDisable(gl_wrap_context* ctx, GLenum cap) {
	if(ctx->glDisableProc == NULL) {
		ctx->glDisableProc = (PFNGLDISABLEPROC)gl_wrap_get_pointer("glDisable");
	}
	ctx->glDisableProc(cap);
};
void gl_wrap_context_glEnable(gl_wrap_context* ctx, GLenum cap) {
	if(ctx->glEnableProc == NULL) {
		ctx->glEnableProc = (PFNGLENABLEPROC)gl_wrap_get_pointer("glEnable");
	}
	ctx->glEnableProc(cap);
};
void gl_wrap_context_glFinish(gl_wrap_context* ctx) {
	if(ctx->glFinishProc == NULL) {
		ctx->glFinishProc = (PFNGLFINISHPROC)gl_wrap_get_pointer("glFinish");
	}
	ctx->glFinishProc();
};
void gl_wrap_context_glFlush(gl_wrap_context* ctx) {
	if(ctx->glFlushProc == NULL) {
		ctx->glFlushProc = (PFNGLFLUSHPROC)gl_wrap_get_pointer("glFlush");
	}
	ctx->glFlushProc();
};
void gl_wrap_context_glBlendFunc(gl_wrap_context* ctx, GLenum sfactor, GLenum dfactor) {
	if(ctx->glBlendFuncProc == NULL) {
		ctx->glBlendFuncProc = (PFNGLBLENDFUNCPROC)gl_wrap_get_pointer("glBlendFunc");
	}
	ctx->glBlendFuncProc(sfactor, dfactor);
};
void gl_wrap_context_glLogicOp(gl_wrap_context* ctx, GLenum opcode) {
	if(ctx->glLogicOpProc == NULL) {
		ctx->glLogicOpProc = (PFNGLLOGICOPPROC)gl_wrap_get_pointer("glLogicOp");
	}
	ctx->glLogicOpProc(opcode);
};
void gl_wrap_context_glStencilFunc(gl_wrap_context* ctx, GLenum func, GLint ref, GLuint mask) {
	if(ctx->glStencilFuncProc == NULL) {
		ctx->glStencilFuncProc = (PFNGLSTENCILFUNCPROC)gl_wrap_get_pointer("glStencilFunc");
	}
	ctx->glStencilFuncProc(func, ref, mask);
};
void gl_wrap_context_glStencilOp(gl_wrap_context* ctx, GLenum fail, GLenum zfail, GLenum zpass) {
	if(ctx->glStencilOpProc == NULL) {
		ctx->glStencilOpProc = (PFNGLSTENCILOPPROC)gl_wrap_get_pointer("glStencilOp");
	}
	ctx->glStencilOpProc(fail, zfail, zpass);
};
void gl_wrap_context_glDepthFunc(gl_wrap_context* ctx, GLenum func) {
	if(ctx->glDepthFuncProc == NULL) {
		ctx->glDepthFuncProc = (PFNGLDEPTHFUNCPROC)gl_wrap_get_pointer("glDepthFunc");
	}
	ctx->glDepthFuncProc(func);
};
void gl_wrap_context_glPixelStoref(gl_wrap_context* ctx, GLenum pname, GLfloat param) {
	if(ctx->glPixelStorefProc == NULL) {
		ctx->glPixelStorefProc = (PFNGLPIXELSTOREFPROC)gl_wrap_get_pointer("glPixelStoref");
	}
	ctx->glPixelStorefProc(pname, param);
};
void gl_wrap_context_glPixelStorei(gl_wrap_context* ctx, GLenum pname, GLint param) {
	if(ctx->glPixelStoreiProc == NULL) {
		ctx->glPixelStoreiProc = (PFNGLPIXELSTOREIPROC)gl_wrap_get_pointer("glPixelStorei");
	}
	ctx->glPixelStoreiProc(pname, param);
};
void gl_wrap_context_glReadBuffer(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glReadBufferProc == NULL) {
		ctx->glReadBufferProc = (PFNGLREADBUFFERPROC)gl_wrap_get_pointer("glReadBuffer");
	}
	ctx->glReadBufferProc(mode);
};
void gl_wrap_context_glReadPixels(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
	if(ctx->glReadPixelsProc == NULL) {
		ctx->glReadPixelsProc = (PFNGLREADPIXELSPROC)gl_wrap_get_pointer("glReadPixels");
	}
	ctx->glReadPixelsProc(x, y, width, height, format, type, pixels);
};
void gl_wrap_context_glGetBooleanv(gl_wrap_context* ctx, GLenum pname, GLboolean* data) {
	if(ctx->glGetBooleanvProc == NULL) {
		ctx->glGetBooleanvProc = (PFNGLGETBOOLEANVPROC)gl_wrap_get_pointer("glGetBooleanv");
	}
	ctx->glGetBooleanvProc(pname, data);
};
void gl_wrap_context_glGetDoublev(gl_wrap_context* ctx, GLenum pname, GLdouble* data) {
	if(ctx->glGetDoublevProc == NULL) {
		ctx->glGetDoublevProc = (PFNGLGETDOUBLEVPROC)gl_wrap_get_pointer("glGetDoublev");
	}
	ctx->glGetDoublevProc(pname, data);
};
GLenum gl_wrap_context_glGetError(gl_wrap_context* ctx) {
	if(ctx->glGetErrorProc == NULL) {
		ctx->glGetErrorProc = (PFNGLGETERRORPROC)gl_wrap_get_pointer("glGetError");
	}
	return ctx->glGetErrorProc();
};
void gl_wrap_context_glGetFloatv(gl_wrap_context* ctx, GLenum pname, GLfloat* data) {
	if(ctx->glGetFloatvProc == NULL) {
		ctx->glGetFloatvProc = (PFNGLGETFLOATVPROC)gl_wrap_get_pointer("glGetFloatv");
	}
	ctx->glGetFloatvProc(pname, data);
};
void gl_wrap_context_glGetIntegerv(gl_wrap_context* ctx, GLenum pname, GLint* data) {
	if(ctx->glGetIntegervProc == NULL) {
		ctx->glGetIntegervProc = (PFNGLGETINTEGERVPROC)gl_wrap_get_pointer("glGetIntegerv");
	}
	ctx->glGetIntegervProc(pname, data);
};
GLubyte* gl_wrap_context_glGetString(gl_wrap_context* ctx, GLenum name) {
	if(ctx->glGetStringProc == NULL) {
		ctx->glGetStringProc = (PFNGLGETSTRINGPROC)gl_wrap_get_pointer("glGetString");
	}
	return ctx->glGetStringProc(name);
};
void gl_wrap_context_glGetTexImage(gl_wrap_context* ctx, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) {
	if(ctx->glGetTexImageProc == NULL) {
		ctx->glGetTexImageProc = (PFNGLGETTEXIMAGEPROC)gl_wrap_get_pointer("glGetTexImage");
	}
	ctx->glGetTexImageProc(target, level, format, type, pixels);
};
void gl_wrap_context_glGetTexParameterfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params) {
	if(ctx->glGetTexParameterfvProc == NULL) {
		ctx->glGetTexParameterfvProc = (PFNGLGETTEXPARAMETERFVPROC)gl_wrap_get_pointer("glGetTexParameterfv");
	}
	ctx->glGetTexParameterfvProc(target, pname, params);
};
void gl_wrap_context_glGetTexParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetTexParameterivProc == NULL) {
		ctx->glGetTexParameterivProc = (PFNGLGETTEXPARAMETERIVPROC)gl_wrap_get_pointer("glGetTexParameteriv");
	}
	ctx->glGetTexParameterivProc(target, pname, params);
};
void gl_wrap_context_glGetTexLevelParameterfv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLfloat* params) {
	if(ctx->glGetTexLevelParameterfvProc == NULL) {
		ctx->glGetTexLevelParameterfvProc = (PFNGLGETTEXLEVELPARAMETERFVPROC)gl_wrap_get_pointer("glGetTexLevelParameterfv");
	}
	ctx->glGetTexLevelParameterfvProc(target, level, pname, params);
};
void gl_wrap_context_glGetTexLevelParameteriv(gl_wrap_context* ctx, GLenum target, GLint level, GLenum pname, GLint* params) {
	if(ctx->glGetTexLevelParameterivProc == NULL) {
		ctx->glGetTexLevelParameterivProc = (PFNGLGETTEXLEVELPARAMETERIVPROC)gl_wrap_get_pointer("glGetTexLevelParameteriv");
	}
	ctx->glGetTexLevelParameterivProc(target, level, pname, params);
};
GLboolean gl_wrap_context_glIsEnabled(gl_wrap_context* ctx, GLenum cap) {
	if(ctx->glIsEnabledProc == NULL) {
		ctx->glIsEnabledProc = (PFNGLISENABLEDPROC)gl_wrap_get_pointer("glIsEnabled");
	}
	return ctx->glIsEnabledProc(cap);
};
void gl_wrap_context_glDepthRange(gl_wrap_context* ctx, GLdouble near, GLdouble far) {
	if(ctx->glDepthRangeProc == NULL) {
		ctx->glDepthRangeProc = (PFNGLDEPTHRANGEPROC)gl_wrap_get_pointer("glDepthRange");
	}
	ctx->glDepthRangeProc(near, far);
};
void gl_wrap_context_glViewport(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glViewportProc == NULL) {
		ctx->glViewportProc = (PFNGLVIEWPORTPROC)gl_wrap_get_pointer("glViewport");
	}
	ctx->glViewportProc(x, y, width, height);
};
void gl_wrap_context_glNewList(gl_wrap_context* ctx, GLuint list, GLenum mode) {
	if(ctx->glNewListProc == NULL) {
		ctx->glNewListProc = (PFNGLNEWLISTPROC)gl_wrap_get_pointer("glNewList");
	}
	ctx->glNewListProc(list, mode);
};
void gl_wrap_context_glEndList(gl_wrap_context* ctx) {
	if(ctx->glEndListProc == NULL) {
		ctx->glEndListProc = (PFNGLENDLISTPROC)gl_wrap_get_pointer("glEndList");
	}
	ctx->glEndListProc();
};
void gl_wrap_context_glCallList(gl_wrap_context* ctx, GLuint list) {
	if(ctx->glCallListProc == NULL) {
		ctx->glCallListProc = (PFNGLCALLLISTPROC)gl_wrap_get_pointer("glCallList");
	}
	ctx->glCallListProc(list);
};
void gl_wrap_context_glCallLists(gl_wrap_context* ctx, GLsizei n, GLenum type, void* lists) {
	if(ctx->glCallListsProc == NULL) {
		ctx->glCallListsProc = (PFNGLCALLLISTSPROC)gl_wrap_get_pointer("glCallLists");
	}
	ctx->glCallListsProc(n, type, lists);
};
void gl_wrap_context_glDeleteLists(gl_wrap_context* ctx, GLuint list, GLsizei range) {
	if(ctx->glDeleteListsProc == NULL) {
		ctx->glDeleteListsProc = (PFNGLDELETELISTSPROC)gl_wrap_get_pointer("glDeleteLists");
	}
	ctx->glDeleteListsProc(list, range);
};
GLuint gl_wrap_context_glGenLists(gl_wrap_context* ctx, GLsizei range) {
	if(ctx->glGenListsProc == NULL) {
		ctx->glGenListsProc = (PFNGLGENLISTSPROC)gl_wrap_get_pointer("glGenLists");
	}
	return ctx->glGenListsProc(range);
};
void gl_wrap_context_glListBase(gl_wrap_context* ctx, GLuint base) {
	if(ctx->glListBaseProc == NULL) {
		ctx->glListBaseProc = (PFNGLLISTBASEPROC)gl_wrap_get_pointer("glListBase");
	}
	ctx->glListBaseProc(base);
};
void gl_wrap_context_glBegin(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glBeginProc == NULL) {
		ctx->glBeginProc = (PFNGLBEGINPROC)gl_wrap_get_pointer("glBegin");
	}
	ctx->glBeginProc(mode);
};
void gl_wrap_context_glBitmap(gl_wrap_context* ctx, GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte* bitmap) {
	if(ctx->glBitmapProc == NULL) {
		ctx->glBitmapProc = (PFNGLBITMAPPROC)gl_wrap_get_pointer("glBitmap");
	}
	ctx->glBitmapProc(width, height, xorig, yorig, xmove, ymove, bitmap);
};
void gl_wrap_context_glColor3b(gl_wrap_context* ctx, GLbyte red, GLbyte green, GLbyte blue) {
	if(ctx->glColor3bProc == NULL) {
		ctx->glColor3bProc = (PFNGLCOLOR3BPROC)gl_wrap_get_pointer("glColor3b");
	}
	ctx->glColor3bProc(red, green, blue);
};
void gl_wrap_context_glColor3bv(gl_wrap_context* ctx, GLbyte* v) {
	if(ctx->glColor3bvProc == NULL) {
		ctx->glColor3bvProc = (PFNGLCOLOR3BVPROC)gl_wrap_get_pointer("glColor3bv");
	}
	ctx->glColor3bvProc(v);
};
void gl_wrap_context_glColor3d(gl_wrap_context* ctx, GLdouble red, GLdouble green, GLdouble blue) {
	if(ctx->glColor3dProc == NULL) {
		ctx->glColor3dProc = (PFNGLCOLOR3DPROC)gl_wrap_get_pointer("glColor3d");
	}
	ctx->glColor3dProc(red, green, blue);
};
void gl_wrap_context_glColor3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glColor3dvProc == NULL) {
		ctx->glColor3dvProc = (PFNGLCOLOR3DVPROC)gl_wrap_get_pointer("glColor3dv");
	}
	ctx->glColor3dvProc(v);
};
void gl_wrap_context_glColor3f(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue) {
	if(ctx->glColor3fProc == NULL) {
		ctx->glColor3fProc = (PFNGLCOLOR3FPROC)gl_wrap_get_pointer("glColor3f");
	}
	ctx->glColor3fProc(red, green, blue);
};
void gl_wrap_context_glColor3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glColor3fvProc == NULL) {
		ctx->glColor3fvProc = (PFNGLCOLOR3FVPROC)gl_wrap_get_pointer("glColor3fv");
	}
	ctx->glColor3fvProc(v);
};
void gl_wrap_context_glColor3i(gl_wrap_context* ctx, GLint red, GLint green, GLint blue) {
	if(ctx->glColor3iProc == NULL) {
		ctx->glColor3iProc = (PFNGLCOLOR3IPROC)gl_wrap_get_pointer("glColor3i");
	}
	ctx->glColor3iProc(red, green, blue);
};
void gl_wrap_context_glColor3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glColor3ivProc == NULL) {
		ctx->glColor3ivProc = (PFNGLCOLOR3IVPROC)gl_wrap_get_pointer("glColor3iv");
	}
	ctx->glColor3ivProc(v);
};
void gl_wrap_context_glColor3s(gl_wrap_context* ctx, GLshort red, GLshort green, GLshort blue) {
	if(ctx->glColor3sProc == NULL) {
		ctx->glColor3sProc = (PFNGLCOLOR3SPROC)gl_wrap_get_pointer("glColor3s");
	}
	ctx->glColor3sProc(red, green, blue);
};
void gl_wrap_context_glColor3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glColor3svProc == NULL) {
		ctx->glColor3svProc = (PFNGLCOLOR3SVPROC)gl_wrap_get_pointer("glColor3sv");
	}
	ctx->glColor3svProc(v);
};
void gl_wrap_context_glColor3ub(gl_wrap_context* ctx, GLubyte red, GLubyte green, GLubyte blue) {
	if(ctx->glColor3ubProc == NULL) {
		ctx->glColor3ubProc = (PFNGLCOLOR3UBPROC)gl_wrap_get_pointer("glColor3ub");
	}
	ctx->glColor3ubProc(red, green, blue);
};
void gl_wrap_context_glColor3ubv(gl_wrap_context* ctx, GLubyte* v) {
	if(ctx->glColor3ubvProc == NULL) {
		ctx->glColor3ubvProc = (PFNGLCOLOR3UBVPROC)gl_wrap_get_pointer("glColor3ubv");
	}
	ctx->glColor3ubvProc(v);
};
void gl_wrap_context_glColor3ui(gl_wrap_context* ctx, GLuint red, GLuint green, GLuint blue) {
	if(ctx->glColor3uiProc == NULL) {
		ctx->glColor3uiProc = (PFNGLCOLOR3UIPROC)gl_wrap_get_pointer("glColor3ui");
	}
	ctx->glColor3uiProc(red, green, blue);
};
void gl_wrap_context_glColor3uiv(gl_wrap_context* ctx, GLuint* v) {
	if(ctx->glColor3uivProc == NULL) {
		ctx->glColor3uivProc = (PFNGLCOLOR3UIVPROC)gl_wrap_get_pointer("glColor3uiv");
	}
	ctx->glColor3uivProc(v);
};
void gl_wrap_context_glColor3us(gl_wrap_context* ctx, GLushort red, GLushort green, GLushort blue) {
	if(ctx->glColor3usProc == NULL) {
		ctx->glColor3usProc = (PFNGLCOLOR3USPROC)gl_wrap_get_pointer("glColor3us");
	}
	ctx->glColor3usProc(red, green, blue);
};
void gl_wrap_context_glColor3usv(gl_wrap_context* ctx, GLushort* v) {
	if(ctx->glColor3usvProc == NULL) {
		ctx->glColor3usvProc = (PFNGLCOLOR3USVPROC)gl_wrap_get_pointer("glColor3usv");
	}
	ctx->glColor3usvProc(v);
};
void gl_wrap_context_glColor4b(gl_wrap_context* ctx, GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
	if(ctx->glColor4bProc == NULL) {
		ctx->glColor4bProc = (PFNGLCOLOR4BPROC)gl_wrap_get_pointer("glColor4b");
	}
	ctx->glColor4bProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4bv(gl_wrap_context* ctx, GLbyte* v) {
	if(ctx->glColor4bvProc == NULL) {
		ctx->glColor4bvProc = (PFNGLCOLOR4BVPROC)gl_wrap_get_pointer("glColor4bv");
	}
	ctx->glColor4bvProc(v);
};
void gl_wrap_context_glColor4d(gl_wrap_context* ctx, GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) {
	if(ctx->glColor4dProc == NULL) {
		ctx->glColor4dProc = (PFNGLCOLOR4DPROC)gl_wrap_get_pointer("glColor4d");
	}
	ctx->glColor4dProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glColor4dvProc == NULL) {
		ctx->glColor4dvProc = (PFNGLCOLOR4DVPROC)gl_wrap_get_pointer("glColor4dv");
	}
	ctx->glColor4dvProc(v);
};
void gl_wrap_context_glColor4f(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if(ctx->glColor4fProc == NULL) {
		ctx->glColor4fProc = (PFNGLCOLOR4FPROC)gl_wrap_get_pointer("glColor4f");
	}
	ctx->glColor4fProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glColor4fvProc == NULL) {
		ctx->glColor4fvProc = (PFNGLCOLOR4FVPROC)gl_wrap_get_pointer("glColor4fv");
	}
	ctx->glColor4fvProc(v);
};
void gl_wrap_context_glColor4i(gl_wrap_context* ctx, GLint red, GLint green, GLint blue, GLint alpha) {
	if(ctx->glColor4iProc == NULL) {
		ctx->glColor4iProc = (PFNGLCOLOR4IPROC)gl_wrap_get_pointer("glColor4i");
	}
	ctx->glColor4iProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glColor4ivProc == NULL) {
		ctx->glColor4ivProc = (PFNGLCOLOR4IVPROC)gl_wrap_get_pointer("glColor4iv");
	}
	ctx->glColor4ivProc(v);
};
void gl_wrap_context_glColor4s(gl_wrap_context* ctx, GLshort red, GLshort green, GLshort blue, GLshort alpha) {
	if(ctx->glColor4sProc == NULL) {
		ctx->glColor4sProc = (PFNGLCOLOR4SPROC)gl_wrap_get_pointer("glColor4s");
	}
	ctx->glColor4sProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glColor4svProc == NULL) {
		ctx->glColor4svProc = (PFNGLCOLOR4SVPROC)gl_wrap_get_pointer("glColor4sv");
	}
	ctx->glColor4svProc(v);
};
void gl_wrap_context_glColor4ub(gl_wrap_context* ctx, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
	if(ctx->glColor4ubProc == NULL) {
		ctx->glColor4ubProc = (PFNGLCOLOR4UBPROC)gl_wrap_get_pointer("glColor4ub");
	}
	ctx->glColor4ubProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4ubv(gl_wrap_context* ctx, GLubyte* v) {
	if(ctx->glColor4ubvProc == NULL) {
		ctx->glColor4ubvProc = (PFNGLCOLOR4UBVPROC)gl_wrap_get_pointer("glColor4ubv");
	}
	ctx->glColor4ubvProc(v);
};
void gl_wrap_context_glColor4ui(gl_wrap_context* ctx, GLuint red, GLuint green, GLuint blue, GLuint alpha) {
	if(ctx->glColor4uiProc == NULL) {
		ctx->glColor4uiProc = (PFNGLCOLOR4UIPROC)gl_wrap_get_pointer("glColor4ui");
	}
	ctx->glColor4uiProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4uiv(gl_wrap_context* ctx, GLuint* v) {
	if(ctx->glColor4uivProc == NULL) {
		ctx->glColor4uivProc = (PFNGLCOLOR4UIVPROC)gl_wrap_get_pointer("glColor4uiv");
	}
	ctx->glColor4uivProc(v);
};
void gl_wrap_context_glColor4us(gl_wrap_context* ctx, GLushort red, GLushort green, GLushort blue, GLushort alpha) {
	if(ctx->glColor4usProc == NULL) {
		ctx->glColor4usProc = (PFNGLCOLOR4USPROC)gl_wrap_get_pointer("glColor4us");
	}
	ctx->glColor4usProc(red, green, blue, alpha);
};
void gl_wrap_context_glColor4usv(gl_wrap_context* ctx, GLushort* v) {
	if(ctx->glColor4usvProc == NULL) {
		ctx->glColor4usvProc = (PFNGLCOLOR4USVPROC)gl_wrap_get_pointer("glColor4usv");
	}
	ctx->glColor4usvProc(v);
};
void gl_wrap_context_glEdgeFlag(gl_wrap_context* ctx, GLboolean flag) {
	if(ctx->glEdgeFlagProc == NULL) {
		ctx->glEdgeFlagProc = (PFNGLEDGEFLAGPROC)gl_wrap_get_pointer("glEdgeFlag");
	}
	ctx->glEdgeFlagProc(flag);
};
void gl_wrap_context_glEdgeFlagv(gl_wrap_context* ctx, GLboolean* flag) {
	if(ctx->glEdgeFlagvProc == NULL) {
		ctx->glEdgeFlagvProc = (PFNGLEDGEFLAGVPROC)gl_wrap_get_pointer("glEdgeFlagv");
	}
	ctx->glEdgeFlagvProc(flag);
};
void gl_wrap_context_glEnd(gl_wrap_context* ctx) {
	if(ctx->glEndProc == NULL) {
		ctx->glEndProc = (PFNGLENDPROC)gl_wrap_get_pointer("glEnd");
	}
	ctx->glEndProc();
};
void gl_wrap_context_glIndexd(gl_wrap_context* ctx, GLdouble c) {
	if(ctx->glIndexdProc == NULL) {
		ctx->glIndexdProc = (PFNGLINDEXDPROC)gl_wrap_get_pointer("glIndexd");
	}
	ctx->glIndexdProc(c);
};
void gl_wrap_context_glIndexdv(gl_wrap_context* ctx, GLdouble* c) {
	if(ctx->glIndexdvProc == NULL) {
		ctx->glIndexdvProc = (PFNGLINDEXDVPROC)gl_wrap_get_pointer("glIndexdv");
	}
	ctx->glIndexdvProc(c);
};
void gl_wrap_context_glIndexf(gl_wrap_context* ctx, GLfloat c) {
	if(ctx->glIndexfProc == NULL) {
		ctx->glIndexfProc = (PFNGLINDEXFPROC)gl_wrap_get_pointer("glIndexf");
	}
	ctx->glIndexfProc(c);
};
void gl_wrap_context_glIndexfv(gl_wrap_context* ctx, GLfloat* c) {
	if(ctx->glIndexfvProc == NULL) {
		ctx->glIndexfvProc = (PFNGLINDEXFVPROC)gl_wrap_get_pointer("glIndexfv");
	}
	ctx->glIndexfvProc(c);
};
void gl_wrap_context_glIndexi(gl_wrap_context* ctx, GLint c) {
	if(ctx->glIndexiProc == NULL) {
		ctx->glIndexiProc = (PFNGLINDEXIPROC)gl_wrap_get_pointer("glIndexi");
	}
	ctx->glIndexiProc(c);
};
void gl_wrap_context_glIndexiv(gl_wrap_context* ctx, GLint* c) {
	if(ctx->glIndexivProc == NULL) {
		ctx->glIndexivProc = (PFNGLINDEXIVPROC)gl_wrap_get_pointer("glIndexiv");
	}
	ctx->glIndexivProc(c);
};
void gl_wrap_context_glIndexs(gl_wrap_context* ctx, GLshort c) {
	if(ctx->glIndexsProc == NULL) {
		ctx->glIndexsProc = (PFNGLINDEXSPROC)gl_wrap_get_pointer("glIndexs");
	}
	ctx->glIndexsProc(c);
};
void gl_wrap_context_glIndexsv(gl_wrap_context* ctx, GLshort* c) {
	if(ctx->glIndexsvProc == NULL) {
		ctx->glIndexsvProc = (PFNGLINDEXSVPROC)gl_wrap_get_pointer("glIndexsv");
	}
	ctx->glIndexsvProc(c);
};
void gl_wrap_context_glNormal3b(gl_wrap_context* ctx, GLbyte nx, GLbyte ny, GLbyte nz) {
	if(ctx->glNormal3bProc == NULL) {
		ctx->glNormal3bProc = (PFNGLNORMAL3BPROC)gl_wrap_get_pointer("glNormal3b");
	}
	ctx->glNormal3bProc(nx, ny, nz);
};
void gl_wrap_context_glNormal3bv(gl_wrap_context* ctx, GLbyte* v) {
	if(ctx->glNormal3bvProc == NULL) {
		ctx->glNormal3bvProc = (PFNGLNORMAL3BVPROC)gl_wrap_get_pointer("glNormal3bv");
	}
	ctx->glNormal3bvProc(v);
};
void gl_wrap_context_glNormal3d(gl_wrap_context* ctx, GLdouble nx, GLdouble ny, GLdouble nz) {
	if(ctx->glNormal3dProc == NULL) {
		ctx->glNormal3dProc = (PFNGLNORMAL3DPROC)gl_wrap_get_pointer("glNormal3d");
	}
	ctx->glNormal3dProc(nx, ny, nz);
};
void gl_wrap_context_glNormal3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glNormal3dvProc == NULL) {
		ctx->glNormal3dvProc = (PFNGLNORMAL3DVPROC)gl_wrap_get_pointer("glNormal3dv");
	}
	ctx->glNormal3dvProc(v);
};
void gl_wrap_context_glNormal3f(gl_wrap_context* ctx, GLfloat nx, GLfloat ny, GLfloat nz) {
	if(ctx->glNormal3fProc == NULL) {
		ctx->glNormal3fProc = (PFNGLNORMAL3FPROC)gl_wrap_get_pointer("glNormal3f");
	}
	ctx->glNormal3fProc(nx, ny, nz);
};
void gl_wrap_context_glNormal3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glNormal3fvProc == NULL) {
		ctx->glNormal3fvProc = (PFNGLNORMAL3FVPROC)gl_wrap_get_pointer("glNormal3fv");
	}
	ctx->glNormal3fvProc(v);
};
void gl_wrap_context_glNormal3i(gl_wrap_context* ctx, GLint nx, GLint ny, GLint nz) {
	if(ctx->glNormal3iProc == NULL) {
		ctx->glNormal3iProc = (PFNGLNORMAL3IPROC)gl_wrap_get_pointer("glNormal3i");
	}
	ctx->glNormal3iProc(nx, ny, nz);
};
void gl_wrap_context_glNormal3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glNormal3ivProc == NULL) {
		ctx->glNormal3ivProc = (PFNGLNORMAL3IVPROC)gl_wrap_get_pointer("glNormal3iv");
	}
	ctx->glNormal3ivProc(v);
};
void gl_wrap_context_glNormal3s(gl_wrap_context* ctx, GLshort nx, GLshort ny, GLshort nz) {
	if(ctx->glNormal3sProc == NULL) {
		ctx->glNormal3sProc = (PFNGLNORMAL3SPROC)gl_wrap_get_pointer("glNormal3s");
	}
	ctx->glNormal3sProc(nx, ny, nz);
};
void gl_wrap_context_glNormal3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glNormal3svProc == NULL) {
		ctx->glNormal3svProc = (PFNGLNORMAL3SVPROC)gl_wrap_get_pointer("glNormal3sv");
	}
	ctx->glNormal3svProc(v);
};
void gl_wrap_context_glRasterPos2d(gl_wrap_context* ctx, GLdouble x, GLdouble y) {
	if(ctx->glRasterPos2dProc == NULL) {
		ctx->glRasterPos2dProc = (PFNGLRASTERPOS2DPROC)gl_wrap_get_pointer("glRasterPos2d");
	}
	ctx->glRasterPos2dProc(x, y);
};
void gl_wrap_context_glRasterPos2dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glRasterPos2dvProc == NULL) {
		ctx->glRasterPos2dvProc = (PFNGLRASTERPOS2DVPROC)gl_wrap_get_pointer("glRasterPos2dv");
	}
	ctx->glRasterPos2dvProc(v);
};
void gl_wrap_context_glRasterPos2f(gl_wrap_context* ctx, GLfloat x, GLfloat y) {
	if(ctx->glRasterPos2fProc == NULL) {
		ctx->glRasterPos2fProc = (PFNGLRASTERPOS2FPROC)gl_wrap_get_pointer("glRasterPos2f");
	}
	ctx->glRasterPos2fProc(x, y);
};
void gl_wrap_context_glRasterPos2fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glRasterPos2fvProc == NULL) {
		ctx->glRasterPos2fvProc = (PFNGLRASTERPOS2FVPROC)gl_wrap_get_pointer("glRasterPos2fv");
	}
	ctx->glRasterPos2fvProc(v);
};
void gl_wrap_context_glRasterPos2i(gl_wrap_context* ctx, GLint x, GLint y) {
	if(ctx->glRasterPos2iProc == NULL) {
		ctx->glRasterPos2iProc = (PFNGLRASTERPOS2IPROC)gl_wrap_get_pointer("glRasterPos2i");
	}
	ctx->glRasterPos2iProc(x, y);
};
void gl_wrap_context_glRasterPos2iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glRasterPos2ivProc == NULL) {
		ctx->glRasterPos2ivProc = (PFNGLRASTERPOS2IVPROC)gl_wrap_get_pointer("glRasterPos2iv");
	}
	ctx->glRasterPos2ivProc(v);
};
void gl_wrap_context_glRasterPos2s(gl_wrap_context* ctx, GLshort x, GLshort y) {
	if(ctx->glRasterPos2sProc == NULL) {
		ctx->glRasterPos2sProc = (PFNGLRASTERPOS2SPROC)gl_wrap_get_pointer("glRasterPos2s");
	}
	ctx->glRasterPos2sProc(x, y);
};
void gl_wrap_context_glRasterPos2sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glRasterPos2svProc == NULL) {
		ctx->glRasterPos2svProc = (PFNGLRASTERPOS2SVPROC)gl_wrap_get_pointer("glRasterPos2sv");
	}
	ctx->glRasterPos2svProc(v);
};
void gl_wrap_context_glRasterPos3d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glRasterPos3dProc == NULL) {
		ctx->glRasterPos3dProc = (PFNGLRASTERPOS3DPROC)gl_wrap_get_pointer("glRasterPos3d");
	}
	ctx->glRasterPos3dProc(x, y, z);
};
void gl_wrap_context_glRasterPos3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glRasterPos3dvProc == NULL) {
		ctx->glRasterPos3dvProc = (PFNGLRASTERPOS3DVPROC)gl_wrap_get_pointer("glRasterPos3dv");
	}
	ctx->glRasterPos3dvProc(v);
};
void gl_wrap_context_glRasterPos3f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glRasterPos3fProc == NULL) {
		ctx->glRasterPos3fProc = (PFNGLRASTERPOS3FPROC)gl_wrap_get_pointer("glRasterPos3f");
	}
	ctx->glRasterPos3fProc(x, y, z);
};
void gl_wrap_context_glRasterPos3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glRasterPos3fvProc == NULL) {
		ctx->glRasterPos3fvProc = (PFNGLRASTERPOS3FVPROC)gl_wrap_get_pointer("glRasterPos3fv");
	}
	ctx->glRasterPos3fvProc(v);
};
void gl_wrap_context_glRasterPos3i(gl_wrap_context* ctx, GLint x, GLint y, GLint z) {
	if(ctx->glRasterPos3iProc == NULL) {
		ctx->glRasterPos3iProc = (PFNGLRASTERPOS3IPROC)gl_wrap_get_pointer("glRasterPos3i");
	}
	ctx->glRasterPos3iProc(x, y, z);
};
void gl_wrap_context_glRasterPos3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glRasterPos3ivProc == NULL) {
		ctx->glRasterPos3ivProc = (PFNGLRASTERPOS3IVPROC)gl_wrap_get_pointer("glRasterPos3iv");
	}
	ctx->glRasterPos3ivProc(v);
};
void gl_wrap_context_glRasterPos3s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z) {
	if(ctx->glRasterPos3sProc == NULL) {
		ctx->glRasterPos3sProc = (PFNGLRASTERPOS3SPROC)gl_wrap_get_pointer("glRasterPos3s");
	}
	ctx->glRasterPos3sProc(x, y, z);
};
void gl_wrap_context_glRasterPos3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glRasterPos3svProc == NULL) {
		ctx->glRasterPos3svProc = (PFNGLRASTERPOS3SVPROC)gl_wrap_get_pointer("glRasterPos3sv");
	}
	ctx->glRasterPos3svProc(v);
};
void gl_wrap_context_glRasterPos4d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	if(ctx->glRasterPos4dProc == NULL) {
		ctx->glRasterPos4dProc = (PFNGLRASTERPOS4DPROC)gl_wrap_get_pointer("glRasterPos4d");
	}
	ctx->glRasterPos4dProc(x, y, z, w);
};
void gl_wrap_context_glRasterPos4dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glRasterPos4dvProc == NULL) {
		ctx->glRasterPos4dvProc = (PFNGLRASTERPOS4DVPROC)gl_wrap_get_pointer("glRasterPos4dv");
	}
	ctx->glRasterPos4dvProc(v);
};
void gl_wrap_context_glRasterPos4f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	if(ctx->glRasterPos4fProc == NULL) {
		ctx->glRasterPos4fProc = (PFNGLRASTERPOS4FPROC)gl_wrap_get_pointer("glRasterPos4f");
	}
	ctx->glRasterPos4fProc(x, y, z, w);
};
void gl_wrap_context_glRasterPos4fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glRasterPos4fvProc == NULL) {
		ctx->glRasterPos4fvProc = (PFNGLRASTERPOS4FVPROC)gl_wrap_get_pointer("glRasterPos4fv");
	}
	ctx->glRasterPos4fvProc(v);
};
void gl_wrap_context_glRasterPos4i(gl_wrap_context* ctx, GLint x, GLint y, GLint z, GLint w) {
	if(ctx->glRasterPos4iProc == NULL) {
		ctx->glRasterPos4iProc = (PFNGLRASTERPOS4IPROC)gl_wrap_get_pointer("glRasterPos4i");
	}
	ctx->glRasterPos4iProc(x, y, z, w);
};
void gl_wrap_context_glRasterPos4iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glRasterPos4ivProc == NULL) {
		ctx->glRasterPos4ivProc = (PFNGLRASTERPOS4IVPROC)gl_wrap_get_pointer("glRasterPos4iv");
	}
	ctx->glRasterPos4ivProc(v);
};
void gl_wrap_context_glRasterPos4s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z, GLshort w) {
	if(ctx->glRasterPos4sProc == NULL) {
		ctx->glRasterPos4sProc = (PFNGLRASTERPOS4SPROC)gl_wrap_get_pointer("glRasterPos4s");
	}
	ctx->glRasterPos4sProc(x, y, z, w);
};
void gl_wrap_context_glRasterPos4sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glRasterPos4svProc == NULL) {
		ctx->glRasterPos4svProc = (PFNGLRASTERPOS4SVPROC)gl_wrap_get_pointer("glRasterPos4sv");
	}
	ctx->glRasterPos4svProc(v);
};
void gl_wrap_context_glRectd(gl_wrap_context* ctx, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	if(ctx->glRectdProc == NULL) {
		ctx->glRectdProc = (PFNGLRECTDPROC)gl_wrap_get_pointer("glRectd");
	}
	ctx->glRectdProc(x1, y1, x2, y2);
};
void gl_wrap_context_glRectdv(gl_wrap_context* ctx, GLdouble* v1, GLdouble* v2) {
	if(ctx->glRectdvProc == NULL) {
		ctx->glRectdvProc = (PFNGLRECTDVPROC)gl_wrap_get_pointer("glRectdv");
	}
	ctx->glRectdvProc(v1, v2);
};
void gl_wrap_context_glRectf(gl_wrap_context* ctx, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	if(ctx->glRectfProc == NULL) {
		ctx->glRectfProc = (PFNGLRECTFPROC)gl_wrap_get_pointer("glRectf");
	}
	ctx->glRectfProc(x1, y1, x2, y2);
};
void gl_wrap_context_glRectfv(gl_wrap_context* ctx, GLfloat* v1, GLfloat* v2) {
	if(ctx->glRectfvProc == NULL) {
		ctx->glRectfvProc = (PFNGLRECTFVPROC)gl_wrap_get_pointer("glRectfv");
	}
	ctx->glRectfvProc(v1, v2);
};
void gl_wrap_context_glRecti(gl_wrap_context* ctx, GLint x1, GLint y1, GLint x2, GLint y2) {
	if(ctx->glRectiProc == NULL) {
		ctx->glRectiProc = (PFNGLRECTIPROC)gl_wrap_get_pointer("glRecti");
	}
	ctx->glRectiProc(x1, y1, x2, y2);
};
void gl_wrap_context_glRectiv(gl_wrap_context* ctx, GLint* v1, GLint* v2) {
	if(ctx->glRectivProc == NULL) {
		ctx->glRectivProc = (PFNGLRECTIVPROC)gl_wrap_get_pointer("glRectiv");
	}
	ctx->glRectivProc(v1, v2);
};
void gl_wrap_context_glRects(gl_wrap_context* ctx, GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
	if(ctx->glRectsProc == NULL) {
		ctx->glRectsProc = (PFNGLRECTSPROC)gl_wrap_get_pointer("glRects");
	}
	ctx->glRectsProc(x1, y1, x2, y2);
};
void gl_wrap_context_glRectsv(gl_wrap_context* ctx, GLshort* v1, GLshort* v2) {
	if(ctx->glRectsvProc == NULL) {
		ctx->glRectsvProc = (PFNGLRECTSVPROC)gl_wrap_get_pointer("glRectsv");
	}
	ctx->glRectsvProc(v1, v2);
};
void gl_wrap_context_glTexCoord1d(gl_wrap_context* ctx, GLdouble s) {
	if(ctx->glTexCoord1dProc == NULL) {
		ctx->glTexCoord1dProc = (PFNGLTEXCOORD1DPROC)gl_wrap_get_pointer("glTexCoord1d");
	}
	ctx->glTexCoord1dProc(s);
};
void gl_wrap_context_glTexCoord1dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glTexCoord1dvProc == NULL) {
		ctx->glTexCoord1dvProc = (PFNGLTEXCOORD1DVPROC)gl_wrap_get_pointer("glTexCoord1dv");
	}
	ctx->glTexCoord1dvProc(v);
};
void gl_wrap_context_glTexCoord1f(gl_wrap_context* ctx, GLfloat s) {
	if(ctx->glTexCoord1fProc == NULL) {
		ctx->glTexCoord1fProc = (PFNGLTEXCOORD1FPROC)gl_wrap_get_pointer("glTexCoord1f");
	}
	ctx->glTexCoord1fProc(s);
};
void gl_wrap_context_glTexCoord1fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glTexCoord1fvProc == NULL) {
		ctx->glTexCoord1fvProc = (PFNGLTEXCOORD1FVPROC)gl_wrap_get_pointer("glTexCoord1fv");
	}
	ctx->glTexCoord1fvProc(v);
};
void gl_wrap_context_glTexCoord1i(gl_wrap_context* ctx, GLint s) {
	if(ctx->glTexCoord1iProc == NULL) {
		ctx->glTexCoord1iProc = (PFNGLTEXCOORD1IPROC)gl_wrap_get_pointer("glTexCoord1i");
	}
	ctx->glTexCoord1iProc(s);
};
void gl_wrap_context_glTexCoord1iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glTexCoord1ivProc == NULL) {
		ctx->glTexCoord1ivProc = (PFNGLTEXCOORD1IVPROC)gl_wrap_get_pointer("glTexCoord1iv");
	}
	ctx->glTexCoord1ivProc(v);
};
void gl_wrap_context_glTexCoord1s(gl_wrap_context* ctx, GLshort s) {
	if(ctx->glTexCoord1sProc == NULL) {
		ctx->glTexCoord1sProc = (PFNGLTEXCOORD1SPROC)gl_wrap_get_pointer("glTexCoord1s");
	}
	ctx->glTexCoord1sProc(s);
};
void gl_wrap_context_glTexCoord1sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glTexCoord1svProc == NULL) {
		ctx->glTexCoord1svProc = (PFNGLTEXCOORD1SVPROC)gl_wrap_get_pointer("glTexCoord1sv");
	}
	ctx->glTexCoord1svProc(v);
};
void gl_wrap_context_glTexCoord2d(gl_wrap_context* ctx, GLdouble s, GLdouble t) {
	if(ctx->glTexCoord2dProc == NULL) {
		ctx->glTexCoord2dProc = (PFNGLTEXCOORD2DPROC)gl_wrap_get_pointer("glTexCoord2d");
	}
	ctx->glTexCoord2dProc(s, t);
};
void gl_wrap_context_glTexCoord2dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glTexCoord2dvProc == NULL) {
		ctx->glTexCoord2dvProc = (PFNGLTEXCOORD2DVPROC)gl_wrap_get_pointer("glTexCoord2dv");
	}
	ctx->glTexCoord2dvProc(v);
};
void gl_wrap_context_glTexCoord2f(gl_wrap_context* ctx, GLfloat s, GLfloat t) {
	if(ctx->glTexCoord2fProc == NULL) {
		ctx->glTexCoord2fProc = (PFNGLTEXCOORD2FPROC)gl_wrap_get_pointer("glTexCoord2f");
	}
	ctx->glTexCoord2fProc(s, t);
};
void gl_wrap_context_glTexCoord2fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glTexCoord2fvProc == NULL) {
		ctx->glTexCoord2fvProc = (PFNGLTEXCOORD2FVPROC)gl_wrap_get_pointer("glTexCoord2fv");
	}
	ctx->glTexCoord2fvProc(v);
};
void gl_wrap_context_glTexCoord2i(gl_wrap_context* ctx, GLint s, GLint t) {
	if(ctx->glTexCoord2iProc == NULL) {
		ctx->glTexCoord2iProc = (PFNGLTEXCOORD2IPROC)gl_wrap_get_pointer("glTexCoord2i");
	}
	ctx->glTexCoord2iProc(s, t);
};
void gl_wrap_context_glTexCoord2iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glTexCoord2ivProc == NULL) {
		ctx->glTexCoord2ivProc = (PFNGLTEXCOORD2IVPROC)gl_wrap_get_pointer("glTexCoord2iv");
	}
	ctx->glTexCoord2ivProc(v);
};
void gl_wrap_context_glTexCoord2s(gl_wrap_context* ctx, GLshort s, GLshort t) {
	if(ctx->glTexCoord2sProc == NULL) {
		ctx->glTexCoord2sProc = (PFNGLTEXCOORD2SPROC)gl_wrap_get_pointer("glTexCoord2s");
	}
	ctx->glTexCoord2sProc(s, t);
};
void gl_wrap_context_glTexCoord2sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glTexCoord2svProc == NULL) {
		ctx->glTexCoord2svProc = (PFNGLTEXCOORD2SVPROC)gl_wrap_get_pointer("glTexCoord2sv");
	}
	ctx->glTexCoord2svProc(v);
};
void gl_wrap_context_glTexCoord3d(gl_wrap_context* ctx, GLdouble s, GLdouble t, GLdouble r) {
	if(ctx->glTexCoord3dProc == NULL) {
		ctx->glTexCoord3dProc = (PFNGLTEXCOORD3DPROC)gl_wrap_get_pointer("glTexCoord3d");
	}
	ctx->glTexCoord3dProc(s, t, r);
};
void gl_wrap_context_glTexCoord3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glTexCoord3dvProc == NULL) {
		ctx->glTexCoord3dvProc = (PFNGLTEXCOORD3DVPROC)gl_wrap_get_pointer("glTexCoord3dv");
	}
	ctx->glTexCoord3dvProc(v);
};
void gl_wrap_context_glTexCoord3f(gl_wrap_context* ctx, GLfloat s, GLfloat t, GLfloat r) {
	if(ctx->glTexCoord3fProc == NULL) {
		ctx->glTexCoord3fProc = (PFNGLTEXCOORD3FPROC)gl_wrap_get_pointer("glTexCoord3f");
	}
	ctx->glTexCoord3fProc(s, t, r);
};
void gl_wrap_context_glTexCoord3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glTexCoord3fvProc == NULL) {
		ctx->glTexCoord3fvProc = (PFNGLTEXCOORD3FVPROC)gl_wrap_get_pointer("glTexCoord3fv");
	}
	ctx->glTexCoord3fvProc(v);
};
void gl_wrap_context_glTexCoord3i(gl_wrap_context* ctx, GLint s, GLint t, GLint r) {
	if(ctx->glTexCoord3iProc == NULL) {
		ctx->glTexCoord3iProc = (PFNGLTEXCOORD3IPROC)gl_wrap_get_pointer("glTexCoord3i");
	}
	ctx->glTexCoord3iProc(s, t, r);
};
void gl_wrap_context_glTexCoord3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glTexCoord3ivProc == NULL) {
		ctx->glTexCoord3ivProc = (PFNGLTEXCOORD3IVPROC)gl_wrap_get_pointer("glTexCoord3iv");
	}
	ctx->glTexCoord3ivProc(v);
};
void gl_wrap_context_glTexCoord3s(gl_wrap_context* ctx, GLshort s, GLshort t, GLshort r) {
	if(ctx->glTexCoord3sProc == NULL) {
		ctx->glTexCoord3sProc = (PFNGLTEXCOORD3SPROC)gl_wrap_get_pointer("glTexCoord3s");
	}
	ctx->glTexCoord3sProc(s, t, r);
};
void gl_wrap_context_glTexCoord3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glTexCoord3svProc == NULL) {
		ctx->glTexCoord3svProc = (PFNGLTEXCOORD3SVPROC)gl_wrap_get_pointer("glTexCoord3sv");
	}
	ctx->glTexCoord3svProc(v);
};
void gl_wrap_context_glTexCoord4d(gl_wrap_context* ctx, GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
	if(ctx->glTexCoord4dProc == NULL) {
		ctx->glTexCoord4dProc = (PFNGLTEXCOORD4DPROC)gl_wrap_get_pointer("glTexCoord4d");
	}
	ctx->glTexCoord4dProc(s, t, r, q);
};
void gl_wrap_context_glTexCoord4dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glTexCoord4dvProc == NULL) {
		ctx->glTexCoord4dvProc = (PFNGLTEXCOORD4DVPROC)gl_wrap_get_pointer("glTexCoord4dv");
	}
	ctx->glTexCoord4dvProc(v);
};
void gl_wrap_context_glTexCoord4f(gl_wrap_context* ctx, GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
	if(ctx->glTexCoord4fProc == NULL) {
		ctx->glTexCoord4fProc = (PFNGLTEXCOORD4FPROC)gl_wrap_get_pointer("glTexCoord4f");
	}
	ctx->glTexCoord4fProc(s, t, r, q);
};
void gl_wrap_context_glTexCoord4fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glTexCoord4fvProc == NULL) {
		ctx->glTexCoord4fvProc = (PFNGLTEXCOORD4FVPROC)gl_wrap_get_pointer("glTexCoord4fv");
	}
	ctx->glTexCoord4fvProc(v);
};
void gl_wrap_context_glTexCoord4i(gl_wrap_context* ctx, GLint s, GLint t, GLint r, GLint q) {
	if(ctx->glTexCoord4iProc == NULL) {
		ctx->glTexCoord4iProc = (PFNGLTEXCOORD4IPROC)gl_wrap_get_pointer("glTexCoord4i");
	}
	ctx->glTexCoord4iProc(s, t, r, q);
};
void gl_wrap_context_glTexCoord4iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glTexCoord4ivProc == NULL) {
		ctx->glTexCoord4ivProc = (PFNGLTEXCOORD4IVPROC)gl_wrap_get_pointer("glTexCoord4iv");
	}
	ctx->glTexCoord4ivProc(v);
};
void gl_wrap_context_glTexCoord4s(gl_wrap_context* ctx, GLshort s, GLshort t, GLshort r, GLshort q) {
	if(ctx->glTexCoord4sProc == NULL) {
		ctx->glTexCoord4sProc = (PFNGLTEXCOORD4SPROC)gl_wrap_get_pointer("glTexCoord4s");
	}
	ctx->glTexCoord4sProc(s, t, r, q);
};
void gl_wrap_context_glTexCoord4sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glTexCoord4svProc == NULL) {
		ctx->glTexCoord4svProc = (PFNGLTEXCOORD4SVPROC)gl_wrap_get_pointer("glTexCoord4sv");
	}
	ctx->glTexCoord4svProc(v);
};
void gl_wrap_context_glVertex2d(gl_wrap_context* ctx, GLdouble x, GLdouble y) {
	if(ctx->glVertex2dProc == NULL) {
		ctx->glVertex2dProc = (PFNGLVERTEX2DPROC)gl_wrap_get_pointer("glVertex2d");
	}
	ctx->glVertex2dProc(x, y);
};
void gl_wrap_context_glVertex2dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glVertex2dvProc == NULL) {
		ctx->glVertex2dvProc = (PFNGLVERTEX2DVPROC)gl_wrap_get_pointer("glVertex2dv");
	}
	ctx->glVertex2dvProc(v);
};
void gl_wrap_context_glVertex2f(gl_wrap_context* ctx, GLfloat x, GLfloat y) {
	if(ctx->glVertex2fProc == NULL) {
		ctx->glVertex2fProc = (PFNGLVERTEX2FPROC)gl_wrap_get_pointer("glVertex2f");
	}
	ctx->glVertex2fProc(x, y);
};
void gl_wrap_context_glVertex2fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glVertex2fvProc == NULL) {
		ctx->glVertex2fvProc = (PFNGLVERTEX2FVPROC)gl_wrap_get_pointer("glVertex2fv");
	}
	ctx->glVertex2fvProc(v);
};
void gl_wrap_context_glVertex2i(gl_wrap_context* ctx, GLint x, GLint y) {
	if(ctx->glVertex2iProc == NULL) {
		ctx->glVertex2iProc = (PFNGLVERTEX2IPROC)gl_wrap_get_pointer("glVertex2i");
	}
	ctx->glVertex2iProc(x, y);
};
void gl_wrap_context_glVertex2iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glVertex2ivProc == NULL) {
		ctx->glVertex2ivProc = (PFNGLVERTEX2IVPROC)gl_wrap_get_pointer("glVertex2iv");
	}
	ctx->glVertex2ivProc(v);
};
void gl_wrap_context_glVertex2s(gl_wrap_context* ctx, GLshort x, GLshort y) {
	if(ctx->glVertex2sProc == NULL) {
		ctx->glVertex2sProc = (PFNGLVERTEX2SPROC)gl_wrap_get_pointer("glVertex2s");
	}
	ctx->glVertex2sProc(x, y);
};
void gl_wrap_context_glVertex2sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glVertex2svProc == NULL) {
		ctx->glVertex2svProc = (PFNGLVERTEX2SVPROC)gl_wrap_get_pointer("glVertex2sv");
	}
	ctx->glVertex2svProc(v);
};
void gl_wrap_context_glVertex3d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glVertex3dProc == NULL) {
		ctx->glVertex3dProc = (PFNGLVERTEX3DPROC)gl_wrap_get_pointer("glVertex3d");
	}
	ctx->glVertex3dProc(x, y, z);
};
void gl_wrap_context_glVertex3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glVertex3dvProc == NULL) {
		ctx->glVertex3dvProc = (PFNGLVERTEX3DVPROC)gl_wrap_get_pointer("glVertex3dv");
	}
	ctx->glVertex3dvProc(v);
};
void gl_wrap_context_glVertex3f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glVertex3fProc == NULL) {
		ctx->glVertex3fProc = (PFNGLVERTEX3FPROC)gl_wrap_get_pointer("glVertex3f");
	}
	ctx->glVertex3fProc(x, y, z);
};
void gl_wrap_context_glVertex3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glVertex3fvProc == NULL) {
		ctx->glVertex3fvProc = (PFNGLVERTEX3FVPROC)gl_wrap_get_pointer("glVertex3fv");
	}
	ctx->glVertex3fvProc(v);
};
void gl_wrap_context_glVertex3i(gl_wrap_context* ctx, GLint x, GLint y, GLint z) {
	if(ctx->glVertex3iProc == NULL) {
		ctx->glVertex3iProc = (PFNGLVERTEX3IPROC)gl_wrap_get_pointer("glVertex3i");
	}
	ctx->glVertex3iProc(x, y, z);
};
void gl_wrap_context_glVertex3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glVertex3ivProc == NULL) {
		ctx->glVertex3ivProc = (PFNGLVERTEX3IVPROC)gl_wrap_get_pointer("glVertex3iv");
	}
	ctx->glVertex3ivProc(v);
};
void gl_wrap_context_glVertex3s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z) {
	if(ctx->glVertex3sProc == NULL) {
		ctx->glVertex3sProc = (PFNGLVERTEX3SPROC)gl_wrap_get_pointer("glVertex3s");
	}
	ctx->glVertex3sProc(x, y, z);
};
void gl_wrap_context_glVertex3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glVertex3svProc == NULL) {
		ctx->glVertex3svProc = (PFNGLVERTEX3SVPROC)gl_wrap_get_pointer("glVertex3sv");
	}
	ctx->glVertex3svProc(v);
};
void gl_wrap_context_glVertex4d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	if(ctx->glVertex4dProc == NULL) {
		ctx->glVertex4dProc = (PFNGLVERTEX4DPROC)gl_wrap_get_pointer("glVertex4d");
	}
	ctx->glVertex4dProc(x, y, z, w);
};
void gl_wrap_context_glVertex4dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glVertex4dvProc == NULL) {
		ctx->glVertex4dvProc = (PFNGLVERTEX4DVPROC)gl_wrap_get_pointer("glVertex4dv");
	}
	ctx->glVertex4dvProc(v);
};
void gl_wrap_context_glVertex4f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	if(ctx->glVertex4fProc == NULL) {
		ctx->glVertex4fProc = (PFNGLVERTEX4FPROC)gl_wrap_get_pointer("glVertex4f");
	}
	ctx->glVertex4fProc(x, y, z, w);
};
void gl_wrap_context_glVertex4fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glVertex4fvProc == NULL) {
		ctx->glVertex4fvProc = (PFNGLVERTEX4FVPROC)gl_wrap_get_pointer("glVertex4fv");
	}
	ctx->glVertex4fvProc(v);
};
void gl_wrap_context_glVertex4i(gl_wrap_context* ctx, GLint x, GLint y, GLint z, GLint w) {
	if(ctx->glVertex4iProc == NULL) {
		ctx->glVertex4iProc = (PFNGLVERTEX4IPROC)gl_wrap_get_pointer("glVertex4i");
	}
	ctx->glVertex4iProc(x, y, z, w);
};
void gl_wrap_context_glVertex4iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glVertex4ivProc == NULL) {
		ctx->glVertex4ivProc = (PFNGLVERTEX4IVPROC)gl_wrap_get_pointer("glVertex4iv");
	}
	ctx->glVertex4ivProc(v);
};
void gl_wrap_context_glVertex4s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z, GLshort w) {
	if(ctx->glVertex4sProc == NULL) {
		ctx->glVertex4sProc = (PFNGLVERTEX4SPROC)gl_wrap_get_pointer("glVertex4s");
	}
	ctx->glVertex4sProc(x, y, z, w);
};
void gl_wrap_context_glVertex4sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glVertex4svProc == NULL) {
		ctx->glVertex4svProc = (PFNGLVERTEX4SVPROC)gl_wrap_get_pointer("glVertex4sv");
	}
	ctx->glVertex4svProc(v);
};
void gl_wrap_context_glClipPlane(gl_wrap_context* ctx, GLenum plane, GLdouble* equation) {
	if(ctx->glClipPlaneProc == NULL) {
		ctx->glClipPlaneProc = (PFNGLCLIPPLANEPROC)gl_wrap_get_pointer("glClipPlane");
	}
	ctx->glClipPlaneProc(plane, equation);
};
void gl_wrap_context_glColorMaterial(gl_wrap_context* ctx, GLenum face, GLenum mode) {
	if(ctx->glColorMaterialProc == NULL) {
		ctx->glColorMaterialProc = (PFNGLCOLORMATERIALPROC)gl_wrap_get_pointer("glColorMaterial");
	}
	ctx->glColorMaterialProc(face, mode);
};
void gl_wrap_context_glFogf(gl_wrap_context* ctx, GLenum pname, GLfloat param) {
	if(ctx->glFogfProc == NULL) {
		ctx->glFogfProc = (PFNGLFOGFPROC)gl_wrap_get_pointer("glFogf");
	}
	ctx->glFogfProc(pname, param);
};
void gl_wrap_context_glFogfv(gl_wrap_context* ctx, GLenum pname, GLfloat* params) {
	if(ctx->glFogfvProc == NULL) {
		ctx->glFogfvProc = (PFNGLFOGFVPROC)gl_wrap_get_pointer("glFogfv");
	}
	ctx->glFogfvProc(pname, params);
};
void gl_wrap_context_glFogi(gl_wrap_context* ctx, GLenum pname, GLint param) {
	if(ctx->glFogiProc == NULL) {
		ctx->glFogiProc = (PFNGLFOGIPROC)gl_wrap_get_pointer("glFogi");
	}
	ctx->glFogiProc(pname, param);
};
void gl_wrap_context_glFogiv(gl_wrap_context* ctx, GLenum pname, GLint* params) {
	if(ctx->glFogivProc == NULL) {
		ctx->glFogivProc = (PFNGLFOGIVPROC)gl_wrap_get_pointer("glFogiv");
	}
	ctx->glFogivProc(pname, params);
};
void gl_wrap_context_glLightf(gl_wrap_context* ctx, GLenum light, GLenum pname, GLfloat param) {
	if(ctx->glLightfProc == NULL) {
		ctx->glLightfProc = (PFNGLLIGHTFPROC)gl_wrap_get_pointer("glLightf");
	}
	ctx->glLightfProc(light, pname, param);
};
void gl_wrap_context_glLightfv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLfloat* params) {
	if(ctx->glLightfvProc == NULL) {
		ctx->glLightfvProc = (PFNGLLIGHTFVPROC)gl_wrap_get_pointer("glLightfv");
	}
	ctx->glLightfvProc(light, pname, params);
};
void gl_wrap_context_glLighti(gl_wrap_context* ctx, GLenum light, GLenum pname, GLint param) {
	if(ctx->glLightiProc == NULL) {
		ctx->glLightiProc = (PFNGLLIGHTIPROC)gl_wrap_get_pointer("glLighti");
	}
	ctx->glLightiProc(light, pname, param);
};
void gl_wrap_context_glLightiv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLint* params) {
	if(ctx->glLightivProc == NULL) {
		ctx->glLightivProc = (PFNGLLIGHTIVPROC)gl_wrap_get_pointer("glLightiv");
	}
	ctx->glLightivProc(light, pname, params);
};
void gl_wrap_context_glLightModelf(gl_wrap_context* ctx, GLenum pname, GLfloat param) {
	if(ctx->glLightModelfProc == NULL) {
		ctx->glLightModelfProc = (PFNGLLIGHTMODELFPROC)gl_wrap_get_pointer("glLightModelf");
	}
	ctx->glLightModelfProc(pname, param);
};
void gl_wrap_context_glLightModelfv(gl_wrap_context* ctx, GLenum pname, GLfloat* params) {
	if(ctx->glLightModelfvProc == NULL) {
		ctx->glLightModelfvProc = (PFNGLLIGHTMODELFVPROC)gl_wrap_get_pointer("glLightModelfv");
	}
	ctx->glLightModelfvProc(pname, params);
};
void gl_wrap_context_glLightModeli(gl_wrap_context* ctx, GLenum pname, GLint param) {
	if(ctx->glLightModeliProc == NULL) {
		ctx->glLightModeliProc = (PFNGLLIGHTMODELIPROC)gl_wrap_get_pointer("glLightModeli");
	}
	ctx->glLightModeliProc(pname, param);
};
void gl_wrap_context_glLightModeliv(gl_wrap_context* ctx, GLenum pname, GLint* params) {
	if(ctx->glLightModelivProc == NULL) {
		ctx->glLightModelivProc = (PFNGLLIGHTMODELIVPROC)gl_wrap_get_pointer("glLightModeliv");
	}
	ctx->glLightModelivProc(pname, params);
};
void gl_wrap_context_glLineStipple(gl_wrap_context* ctx, GLint factor, GLushort pattern) {
	if(ctx->glLineStippleProc == NULL) {
		ctx->glLineStippleProc = (PFNGLLINESTIPPLEPROC)gl_wrap_get_pointer("glLineStipple");
	}
	ctx->glLineStippleProc(factor, pattern);
};
void gl_wrap_context_glMaterialf(gl_wrap_context* ctx, GLenum face, GLenum pname, GLfloat param) {
	if(ctx->glMaterialfProc == NULL) {
		ctx->glMaterialfProc = (PFNGLMATERIALFPROC)gl_wrap_get_pointer("glMaterialf");
	}
	ctx->glMaterialfProc(face, pname, param);
};
void gl_wrap_context_glMaterialfv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLfloat* params) {
	if(ctx->glMaterialfvProc == NULL) {
		ctx->glMaterialfvProc = (PFNGLMATERIALFVPROC)gl_wrap_get_pointer("glMaterialfv");
	}
	ctx->glMaterialfvProc(face, pname, params);
};
void gl_wrap_context_glMateriali(gl_wrap_context* ctx, GLenum face, GLenum pname, GLint param) {
	if(ctx->glMaterialiProc == NULL) {
		ctx->glMaterialiProc = (PFNGLMATERIALIPROC)gl_wrap_get_pointer("glMateriali");
	}
	ctx->glMaterialiProc(face, pname, param);
};
void gl_wrap_context_glMaterialiv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLint* params) {
	if(ctx->glMaterialivProc == NULL) {
		ctx->glMaterialivProc = (PFNGLMATERIALIVPROC)gl_wrap_get_pointer("glMaterialiv");
	}
	ctx->glMaterialivProc(face, pname, params);
};
void gl_wrap_context_glPolygonStipple(gl_wrap_context* ctx, GLubyte* mask) {
	if(ctx->glPolygonStippleProc == NULL) {
		ctx->glPolygonStippleProc = (PFNGLPOLYGONSTIPPLEPROC)gl_wrap_get_pointer("glPolygonStipple");
	}
	ctx->glPolygonStippleProc(mask);
};
void gl_wrap_context_glShadeModel(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glShadeModelProc == NULL) {
		ctx->glShadeModelProc = (PFNGLSHADEMODELPROC)gl_wrap_get_pointer("glShadeModel");
	}
	ctx->glShadeModelProc(mode);
};
void gl_wrap_context_glTexEnvf(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat param) {
	if(ctx->glTexEnvfProc == NULL) {
		ctx->glTexEnvfProc = (PFNGLTEXENVFPROC)gl_wrap_get_pointer("glTexEnvf");
	}
	ctx->glTexEnvfProc(target, pname, param);
};
void gl_wrap_context_glTexEnvfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params) {
	if(ctx->glTexEnvfvProc == NULL) {
		ctx->glTexEnvfvProc = (PFNGLTEXENVFVPROC)gl_wrap_get_pointer("glTexEnvfv");
	}
	ctx->glTexEnvfvProc(target, pname, params);
};
void gl_wrap_context_glTexEnvi(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param) {
	if(ctx->glTexEnviProc == NULL) {
		ctx->glTexEnviProc = (PFNGLTEXENVIPROC)gl_wrap_get_pointer("glTexEnvi");
	}
	ctx->glTexEnviProc(target, pname, param);
};
void gl_wrap_context_glTexEnviv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glTexEnvivProc == NULL) {
		ctx->glTexEnvivProc = (PFNGLTEXENVIVPROC)gl_wrap_get_pointer("glTexEnviv");
	}
	ctx->glTexEnvivProc(target, pname, params);
};
void gl_wrap_context_glTexGend(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLdouble param) {
	if(ctx->glTexGendProc == NULL) {
		ctx->glTexGendProc = (PFNGLTEXGENDPROC)gl_wrap_get_pointer("glTexGend");
	}
	ctx->glTexGendProc(coord, pname, param);
};
void gl_wrap_context_glTexGendv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLdouble* params) {
	if(ctx->glTexGendvProc == NULL) {
		ctx->glTexGendvProc = (PFNGLTEXGENDVPROC)gl_wrap_get_pointer("glTexGendv");
	}
	ctx->glTexGendvProc(coord, pname, params);
};
void gl_wrap_context_glTexGenf(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLfloat param) {
	if(ctx->glTexGenfProc == NULL) {
		ctx->glTexGenfProc = (PFNGLTEXGENFPROC)gl_wrap_get_pointer("glTexGenf");
	}
	ctx->glTexGenfProc(coord, pname, param);
};
void gl_wrap_context_glTexGenfv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLfloat* params) {
	if(ctx->glTexGenfvProc == NULL) {
		ctx->glTexGenfvProc = (PFNGLTEXGENFVPROC)gl_wrap_get_pointer("glTexGenfv");
	}
	ctx->glTexGenfvProc(coord, pname, params);
};
void gl_wrap_context_glTexGeni(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLint param) {
	if(ctx->glTexGeniProc == NULL) {
		ctx->glTexGeniProc = (PFNGLTEXGENIPROC)gl_wrap_get_pointer("glTexGeni");
	}
	ctx->glTexGeniProc(coord, pname, param);
};
void gl_wrap_context_glTexGeniv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLint* params) {
	if(ctx->glTexGenivProc == NULL) {
		ctx->glTexGenivProc = (PFNGLTEXGENIVPROC)gl_wrap_get_pointer("glTexGeniv");
	}
	ctx->glTexGenivProc(coord, pname, params);
};
void gl_wrap_context_glFeedbackBuffer(gl_wrap_context* ctx, GLsizei size, GLenum type, GLfloat* buffer) {
	if(ctx->glFeedbackBufferProc == NULL) {
		ctx->glFeedbackBufferProc = (PFNGLFEEDBACKBUFFERPROC)gl_wrap_get_pointer("glFeedbackBuffer");
	}
	ctx->glFeedbackBufferProc(size, type, buffer);
};
void gl_wrap_context_glSelectBuffer(gl_wrap_context* ctx, GLsizei size, GLuint* buffer) {
	if(ctx->glSelectBufferProc == NULL) {
		ctx->glSelectBufferProc = (PFNGLSELECTBUFFERPROC)gl_wrap_get_pointer("glSelectBuffer");
	}
	ctx->glSelectBufferProc(size, buffer);
};
GLint gl_wrap_context_glRenderMode(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glRenderModeProc == NULL) {
		ctx->glRenderModeProc = (PFNGLRENDERMODEPROC)gl_wrap_get_pointer("glRenderMode");
	}
	return ctx->glRenderModeProc(mode);
};
void gl_wrap_context_glInitNames(gl_wrap_context* ctx) {
	if(ctx->glInitNamesProc == NULL) {
		ctx->glInitNamesProc = (PFNGLINITNAMESPROC)gl_wrap_get_pointer("glInitNames");
	}
	ctx->glInitNamesProc();
};
void gl_wrap_context_glLoadName(gl_wrap_context* ctx, GLuint name) {
	if(ctx->glLoadNameProc == NULL) {
		ctx->glLoadNameProc = (PFNGLLOADNAMEPROC)gl_wrap_get_pointer("glLoadName");
	}
	ctx->glLoadNameProc(name);
};
void gl_wrap_context_glPassThrough(gl_wrap_context* ctx, GLfloat token) {
	if(ctx->glPassThroughProc == NULL) {
		ctx->glPassThroughProc = (PFNGLPASSTHROUGHPROC)gl_wrap_get_pointer("glPassThrough");
	}
	ctx->glPassThroughProc(token);
};
void gl_wrap_context_glPopName(gl_wrap_context* ctx) {
	if(ctx->glPopNameProc == NULL) {
		ctx->glPopNameProc = (PFNGLPOPNAMEPROC)gl_wrap_get_pointer("glPopName");
	}
	ctx->glPopNameProc();
};
void gl_wrap_context_glPushName(gl_wrap_context* ctx, GLuint name) {
	if(ctx->glPushNameProc == NULL) {
		ctx->glPushNameProc = (PFNGLPUSHNAMEPROC)gl_wrap_get_pointer("glPushName");
	}
	ctx->glPushNameProc(name);
};
void gl_wrap_context_glClearAccum(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if(ctx->glClearAccumProc == NULL) {
		ctx->glClearAccumProc = (PFNGLCLEARACCUMPROC)gl_wrap_get_pointer("glClearAccum");
	}
	ctx->glClearAccumProc(red, green, blue, alpha);
};
void gl_wrap_context_glClearIndex(gl_wrap_context* ctx, GLfloat c) {
	if(ctx->glClearIndexProc == NULL) {
		ctx->glClearIndexProc = (PFNGLCLEARINDEXPROC)gl_wrap_get_pointer("glClearIndex");
	}
	ctx->glClearIndexProc(c);
};
void gl_wrap_context_glIndexMask(gl_wrap_context* ctx, GLuint mask) {
	if(ctx->glIndexMaskProc == NULL) {
		ctx->glIndexMaskProc = (PFNGLINDEXMASKPROC)gl_wrap_get_pointer("glIndexMask");
	}
	ctx->glIndexMaskProc(mask);
};
void gl_wrap_context_glAccum(gl_wrap_context* ctx, GLenum op, GLfloat value) {
	if(ctx->glAccumProc == NULL) {
		ctx->glAccumProc = (PFNGLACCUMPROC)gl_wrap_get_pointer("glAccum");
	}
	ctx->glAccumProc(op, value);
};
void gl_wrap_context_glPopAttrib(gl_wrap_context* ctx) {
	if(ctx->glPopAttribProc == NULL) {
		ctx->glPopAttribProc = (PFNGLPOPATTRIBPROC)gl_wrap_get_pointer("glPopAttrib");
	}
	ctx->glPopAttribProc();
};
void gl_wrap_context_glPushAttrib(gl_wrap_context* ctx, GLbitfield mask) {
	if(ctx->glPushAttribProc == NULL) {
		ctx->glPushAttribProc = (PFNGLPUSHATTRIBPROC)gl_wrap_get_pointer("glPushAttrib");
	}
	ctx->glPushAttribProc(mask);
};
void gl_wrap_context_glMap1d(gl_wrap_context* ctx, GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, GLdouble* points) {
	if(ctx->glMap1dProc == NULL) {
		ctx->glMap1dProc = (PFNGLMAP1DPROC)gl_wrap_get_pointer("glMap1d");
	}
	ctx->glMap1dProc(target, u1, u2, stride, order, points);
};
void gl_wrap_context_glMap1f(gl_wrap_context* ctx, GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, GLfloat* points) {
	if(ctx->glMap1fProc == NULL) {
		ctx->glMap1fProc = (PFNGLMAP1FPROC)gl_wrap_get_pointer("glMap1f");
	}
	ctx->glMap1fProc(target, u1, u2, stride, order, points);
};
void gl_wrap_context_glMap2d(gl_wrap_context* ctx, GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble* points) {
	if(ctx->glMap2dProc == NULL) {
		ctx->glMap2dProc = (PFNGLMAP2DPROC)gl_wrap_get_pointer("glMap2d");
	}
	ctx->glMap2dProc(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
};
void gl_wrap_context_glMap2f(gl_wrap_context* ctx, GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat* points) {
	if(ctx->glMap2fProc == NULL) {
		ctx->glMap2fProc = (PFNGLMAP2FPROC)gl_wrap_get_pointer("glMap2f");
	}
	ctx->glMap2fProc(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
};
void gl_wrap_context_glMapGrid1d(gl_wrap_context* ctx, GLint un, GLdouble u1, GLdouble u2) {
	if(ctx->glMapGrid1dProc == NULL) {
		ctx->glMapGrid1dProc = (PFNGLMAPGRID1DPROC)gl_wrap_get_pointer("glMapGrid1d");
	}
	ctx->glMapGrid1dProc(un, u1, u2);
};
void gl_wrap_context_glMapGrid1f(gl_wrap_context* ctx, GLint un, GLfloat u1, GLfloat u2) {
	if(ctx->glMapGrid1fProc == NULL) {
		ctx->glMapGrid1fProc = (PFNGLMAPGRID1FPROC)gl_wrap_get_pointer("glMapGrid1f");
	}
	ctx->glMapGrid1fProc(un, u1, u2);
};
void gl_wrap_context_glMapGrid2d(gl_wrap_context* ctx, GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) {
	if(ctx->glMapGrid2dProc == NULL) {
		ctx->glMapGrid2dProc = (PFNGLMAPGRID2DPROC)gl_wrap_get_pointer("glMapGrid2d");
	}
	ctx->glMapGrid2dProc(un, u1, u2, vn, v1, v2);
};
void gl_wrap_context_glMapGrid2f(gl_wrap_context* ctx, GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) {
	if(ctx->glMapGrid2fProc == NULL) {
		ctx->glMapGrid2fProc = (PFNGLMAPGRID2FPROC)gl_wrap_get_pointer("glMapGrid2f");
	}
	ctx->glMapGrid2fProc(un, u1, u2, vn, v1, v2);
};
void gl_wrap_context_glEvalCoord1d(gl_wrap_context* ctx, GLdouble u) {
	if(ctx->glEvalCoord1dProc == NULL) {
		ctx->glEvalCoord1dProc = (PFNGLEVALCOORD1DPROC)gl_wrap_get_pointer("glEvalCoord1d");
	}
	ctx->glEvalCoord1dProc(u);
};
void gl_wrap_context_glEvalCoord1dv(gl_wrap_context* ctx, GLdouble* u) {
	if(ctx->glEvalCoord1dvProc == NULL) {
		ctx->glEvalCoord1dvProc = (PFNGLEVALCOORD1DVPROC)gl_wrap_get_pointer("glEvalCoord1dv");
	}
	ctx->glEvalCoord1dvProc(u);
};
void gl_wrap_context_glEvalCoord1f(gl_wrap_context* ctx, GLfloat u) {
	if(ctx->glEvalCoord1fProc == NULL) {
		ctx->glEvalCoord1fProc = (PFNGLEVALCOORD1FPROC)gl_wrap_get_pointer("glEvalCoord1f");
	}
	ctx->glEvalCoord1fProc(u);
};
void gl_wrap_context_glEvalCoord1fv(gl_wrap_context* ctx, GLfloat* u) {
	if(ctx->glEvalCoord1fvProc == NULL) {
		ctx->glEvalCoord1fvProc = (PFNGLEVALCOORD1FVPROC)gl_wrap_get_pointer("glEvalCoord1fv");
	}
	ctx->glEvalCoord1fvProc(u);
};
void gl_wrap_context_glEvalCoord2d(gl_wrap_context* ctx, GLdouble u, GLdouble v) {
	if(ctx->glEvalCoord2dProc == NULL) {
		ctx->glEvalCoord2dProc = (PFNGLEVALCOORD2DPROC)gl_wrap_get_pointer("glEvalCoord2d");
	}
	ctx->glEvalCoord2dProc(u, v);
};
void gl_wrap_context_glEvalCoord2dv(gl_wrap_context* ctx, GLdouble* u) {
	if(ctx->glEvalCoord2dvProc == NULL) {
		ctx->glEvalCoord2dvProc = (PFNGLEVALCOORD2DVPROC)gl_wrap_get_pointer("glEvalCoord2dv");
	}
	ctx->glEvalCoord2dvProc(u);
};
void gl_wrap_context_glEvalCoord2f(gl_wrap_context* ctx, GLfloat u, GLfloat v) {
	if(ctx->glEvalCoord2fProc == NULL) {
		ctx->glEvalCoord2fProc = (PFNGLEVALCOORD2FPROC)gl_wrap_get_pointer("glEvalCoord2f");
	}
	ctx->glEvalCoord2fProc(u, v);
};
void gl_wrap_context_glEvalCoord2fv(gl_wrap_context* ctx, GLfloat* u) {
	if(ctx->glEvalCoord2fvProc == NULL) {
		ctx->glEvalCoord2fvProc = (PFNGLEVALCOORD2FVPROC)gl_wrap_get_pointer("glEvalCoord2fv");
	}
	ctx->glEvalCoord2fvProc(u);
};
void gl_wrap_context_glEvalMesh1(gl_wrap_context* ctx, GLenum mode, GLint i1, GLint i2) {
	if(ctx->glEvalMesh1Proc == NULL) {
		ctx->glEvalMesh1Proc = (PFNGLEVALMESH1PROC)gl_wrap_get_pointer("glEvalMesh1");
	}
	ctx->glEvalMesh1Proc(mode, i1, i2);
};
void gl_wrap_context_glEvalPoint1(gl_wrap_context* ctx, GLint i) {
	if(ctx->glEvalPoint1Proc == NULL) {
		ctx->glEvalPoint1Proc = (PFNGLEVALPOINT1PROC)gl_wrap_get_pointer("glEvalPoint1");
	}
	ctx->glEvalPoint1Proc(i);
};
void gl_wrap_context_glEvalMesh2(gl_wrap_context* ctx, GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) {
	if(ctx->glEvalMesh2Proc == NULL) {
		ctx->glEvalMesh2Proc = (PFNGLEVALMESH2PROC)gl_wrap_get_pointer("glEvalMesh2");
	}
	ctx->glEvalMesh2Proc(mode, i1, i2, j1, j2);
};
void gl_wrap_context_glEvalPoint2(gl_wrap_context* ctx, GLint i, GLint j) {
	if(ctx->glEvalPoint2Proc == NULL) {
		ctx->glEvalPoint2Proc = (PFNGLEVALPOINT2PROC)gl_wrap_get_pointer("glEvalPoint2");
	}
	ctx->glEvalPoint2Proc(i, j);
};
void gl_wrap_context_glAlphaFunc(gl_wrap_context* ctx, GLenum func, GLfloat ref) {
	if(ctx->glAlphaFuncProc == NULL) {
		ctx->glAlphaFuncProc = (PFNGLALPHAFUNCPROC)gl_wrap_get_pointer("glAlphaFunc");
	}
	ctx->glAlphaFuncProc(func, ref);
};
void gl_wrap_context_glPixelZoom(gl_wrap_context* ctx, GLfloat xfactor, GLfloat yfactor) {
	if(ctx->glPixelZoomProc == NULL) {
		ctx->glPixelZoomProc = (PFNGLPIXELZOOMPROC)gl_wrap_get_pointer("glPixelZoom");
	}
	ctx->glPixelZoomProc(xfactor, yfactor);
};
void gl_wrap_context_glPixelTransferf(gl_wrap_context* ctx, GLenum pname, GLfloat param) {
	if(ctx->glPixelTransferfProc == NULL) {
		ctx->glPixelTransferfProc = (PFNGLPIXELTRANSFERFPROC)gl_wrap_get_pointer("glPixelTransferf");
	}
	ctx->glPixelTransferfProc(pname, param);
};
void gl_wrap_context_glPixelTransferi(gl_wrap_context* ctx, GLenum pname, GLint param) {
	if(ctx->glPixelTransferiProc == NULL) {
		ctx->glPixelTransferiProc = (PFNGLPIXELTRANSFERIPROC)gl_wrap_get_pointer("glPixelTransferi");
	}
	ctx->glPixelTransferiProc(pname, param);
};
void gl_wrap_context_glPixelMapfv(gl_wrap_context* ctx, GLenum map, GLsizei mapsize, GLfloat* values) {
	if(ctx->glPixelMapfvProc == NULL) {
		ctx->glPixelMapfvProc = (PFNGLPIXELMAPFVPROC)gl_wrap_get_pointer("glPixelMapfv");
	}
	ctx->glPixelMapfvProc(map, mapsize, values);
};
void gl_wrap_context_glPixelMapuiv(gl_wrap_context* ctx, GLenum map, GLsizei mapsize, GLuint* values) {
	if(ctx->glPixelMapuivProc == NULL) {
		ctx->glPixelMapuivProc = (PFNGLPIXELMAPUIVPROC)gl_wrap_get_pointer("glPixelMapuiv");
	}
	ctx->glPixelMapuivProc(map, mapsize, values);
};
void gl_wrap_context_glPixelMapusv(gl_wrap_context* ctx, GLenum map, GLsizei mapsize, GLushort* values) {
	if(ctx->glPixelMapusvProc == NULL) {
		ctx->glPixelMapusvProc = (PFNGLPIXELMAPUSVPROC)gl_wrap_get_pointer("glPixelMapusv");
	}
	ctx->glPixelMapusvProc(map, mapsize, values);
};
void gl_wrap_context_glCopyPixels(gl_wrap_context* ctx, GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) {
	if(ctx->glCopyPixelsProc == NULL) {
		ctx->glCopyPixelsProc = (PFNGLCOPYPIXELSPROC)gl_wrap_get_pointer("glCopyPixels");
	}
	ctx->glCopyPixelsProc(x, y, width, height, type);
};
void gl_wrap_context_glDrawPixels(gl_wrap_context* ctx, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
	if(ctx->glDrawPixelsProc == NULL) {
		ctx->glDrawPixelsProc = (PFNGLDRAWPIXELSPROC)gl_wrap_get_pointer("glDrawPixels");
	}
	ctx->glDrawPixelsProc(width, height, format, type, pixels);
};
void gl_wrap_context_glGetClipPlane(gl_wrap_context* ctx, GLenum plane, GLdouble* equation) {
	if(ctx->glGetClipPlaneProc == NULL) {
		ctx->glGetClipPlaneProc = (PFNGLGETCLIPPLANEPROC)gl_wrap_get_pointer("glGetClipPlane");
	}
	ctx->glGetClipPlaneProc(plane, equation);
};
void gl_wrap_context_glGetLightfv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLfloat* params) {
	if(ctx->glGetLightfvProc == NULL) {
		ctx->glGetLightfvProc = (PFNGLGETLIGHTFVPROC)gl_wrap_get_pointer("glGetLightfv");
	}
	ctx->glGetLightfvProc(light, pname, params);
};
void gl_wrap_context_glGetLightiv(gl_wrap_context* ctx, GLenum light, GLenum pname, GLint* params) {
	if(ctx->glGetLightivProc == NULL) {
		ctx->glGetLightivProc = (PFNGLGETLIGHTIVPROC)gl_wrap_get_pointer("glGetLightiv");
	}
	ctx->glGetLightivProc(light, pname, params);
};
void gl_wrap_context_glGetMapdv(gl_wrap_context* ctx, GLenum target, GLenum query, GLdouble* v) {
	if(ctx->glGetMapdvProc == NULL) {
		ctx->glGetMapdvProc = (PFNGLGETMAPDVPROC)gl_wrap_get_pointer("glGetMapdv");
	}
	ctx->glGetMapdvProc(target, query, v);
};
void gl_wrap_context_glGetMapfv(gl_wrap_context* ctx, GLenum target, GLenum query, GLfloat* v) {
	if(ctx->glGetMapfvProc == NULL) {
		ctx->glGetMapfvProc = (PFNGLGETMAPFVPROC)gl_wrap_get_pointer("glGetMapfv");
	}
	ctx->glGetMapfvProc(target, query, v);
};
void gl_wrap_context_glGetMapiv(gl_wrap_context* ctx, GLenum target, GLenum query, GLint* v) {
	if(ctx->glGetMapivProc == NULL) {
		ctx->glGetMapivProc = (PFNGLGETMAPIVPROC)gl_wrap_get_pointer("glGetMapiv");
	}
	ctx->glGetMapivProc(target, query, v);
};
void gl_wrap_context_glGetMaterialfv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLfloat* params) {
	if(ctx->glGetMaterialfvProc == NULL) {
		ctx->glGetMaterialfvProc = (PFNGLGETMATERIALFVPROC)gl_wrap_get_pointer("glGetMaterialfv");
	}
	ctx->glGetMaterialfvProc(face, pname, params);
};
void gl_wrap_context_glGetMaterialiv(gl_wrap_context* ctx, GLenum face, GLenum pname, GLint* params) {
	if(ctx->glGetMaterialivProc == NULL) {
		ctx->glGetMaterialivProc = (PFNGLGETMATERIALIVPROC)gl_wrap_get_pointer("glGetMaterialiv");
	}
	ctx->glGetMaterialivProc(face, pname, params);
};
void gl_wrap_context_glGetPixelMapfv(gl_wrap_context* ctx, GLenum map, GLfloat* values) {
	if(ctx->glGetPixelMapfvProc == NULL) {
		ctx->glGetPixelMapfvProc = (PFNGLGETPIXELMAPFVPROC)gl_wrap_get_pointer("glGetPixelMapfv");
	}
	ctx->glGetPixelMapfvProc(map, values);
};
void gl_wrap_context_glGetPixelMapuiv(gl_wrap_context* ctx, GLenum map, GLuint* values) {
	if(ctx->glGetPixelMapuivProc == NULL) {
		ctx->glGetPixelMapuivProc = (PFNGLGETPIXELMAPUIVPROC)gl_wrap_get_pointer("glGetPixelMapuiv");
	}
	ctx->glGetPixelMapuivProc(map, values);
};
void gl_wrap_context_glGetPixelMapusv(gl_wrap_context* ctx, GLenum map, GLushort* values) {
	if(ctx->glGetPixelMapusvProc == NULL) {
		ctx->glGetPixelMapusvProc = (PFNGLGETPIXELMAPUSVPROC)gl_wrap_get_pointer("glGetPixelMapusv");
	}
	ctx->glGetPixelMapusvProc(map, values);
};
void gl_wrap_context_glGetPolygonStipple(gl_wrap_context* ctx, GLubyte* mask) {
	if(ctx->glGetPolygonStippleProc == NULL) {
		ctx->glGetPolygonStippleProc = (PFNGLGETPOLYGONSTIPPLEPROC)gl_wrap_get_pointer("glGetPolygonStipple");
	}
	ctx->glGetPolygonStippleProc(mask);
};
void gl_wrap_context_glGetTexEnvfv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLfloat* params) {
	if(ctx->glGetTexEnvfvProc == NULL) {
		ctx->glGetTexEnvfvProc = (PFNGLGETTEXENVFVPROC)gl_wrap_get_pointer("glGetTexEnvfv");
	}
	ctx->glGetTexEnvfvProc(target, pname, params);
};
void gl_wrap_context_glGetTexEnviv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetTexEnvivProc == NULL) {
		ctx->glGetTexEnvivProc = (PFNGLGETTEXENVIVPROC)gl_wrap_get_pointer("glGetTexEnviv");
	}
	ctx->glGetTexEnvivProc(target, pname, params);
};
void gl_wrap_context_glGetTexGendv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLdouble* params) {
	if(ctx->glGetTexGendvProc == NULL) {
		ctx->glGetTexGendvProc = (PFNGLGETTEXGENDVPROC)gl_wrap_get_pointer("glGetTexGendv");
	}
	ctx->glGetTexGendvProc(coord, pname, params);
};
void gl_wrap_context_glGetTexGenfv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLfloat* params) {
	if(ctx->glGetTexGenfvProc == NULL) {
		ctx->glGetTexGenfvProc = (PFNGLGETTEXGENFVPROC)gl_wrap_get_pointer("glGetTexGenfv");
	}
	ctx->glGetTexGenfvProc(coord, pname, params);
};
void gl_wrap_context_glGetTexGeniv(gl_wrap_context* ctx, GLenum coord, GLenum pname, GLint* params) {
	if(ctx->glGetTexGenivProc == NULL) {
		ctx->glGetTexGenivProc = (PFNGLGETTEXGENIVPROC)gl_wrap_get_pointer("glGetTexGeniv");
	}
	ctx->glGetTexGenivProc(coord, pname, params);
};
GLboolean gl_wrap_context_glIsList(gl_wrap_context* ctx, GLuint list) {
	if(ctx->glIsListProc == NULL) {
		ctx->glIsListProc = (PFNGLISLISTPROC)gl_wrap_get_pointer("glIsList");
	}
	return ctx->glIsListProc(list);
};
void gl_wrap_context_glFrustum(gl_wrap_context* ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
	if(ctx->glFrustumProc == NULL) {
		ctx->glFrustumProc = (PFNGLFRUSTUMPROC)gl_wrap_get_pointer("glFrustum");
	}
	ctx->glFrustumProc(left, right, bottom, top, zNear, zFar);
};
void gl_wrap_context_glLoadIdentity(gl_wrap_context* ctx) {
	if(ctx->glLoadIdentityProc == NULL) {
		ctx->glLoadIdentityProc = (PFNGLLOADIDENTITYPROC)gl_wrap_get_pointer("glLoadIdentity");
	}
	ctx->glLoadIdentityProc();
};
void gl_wrap_context_glLoadMatrixf(gl_wrap_context* ctx, GLfloat* m) {
	if(ctx->glLoadMatrixfProc == NULL) {
		ctx->glLoadMatrixfProc = (PFNGLLOADMATRIXFPROC)gl_wrap_get_pointer("glLoadMatrixf");
	}
	ctx->glLoadMatrixfProc(m);
};
void gl_wrap_context_glLoadMatrixd(gl_wrap_context* ctx, GLdouble* m) {
	if(ctx->glLoadMatrixdProc == NULL) {
		ctx->glLoadMatrixdProc = (PFNGLLOADMATRIXDPROC)gl_wrap_get_pointer("glLoadMatrixd");
	}
	ctx->glLoadMatrixdProc(m);
};
void gl_wrap_context_glMatrixMode(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glMatrixModeProc == NULL) {
		ctx->glMatrixModeProc = (PFNGLMATRIXMODEPROC)gl_wrap_get_pointer("glMatrixMode");
	}
	ctx->glMatrixModeProc(mode);
};
void gl_wrap_context_glMultMatrixf(gl_wrap_context* ctx, GLfloat* m) {
	if(ctx->glMultMatrixfProc == NULL) {
		ctx->glMultMatrixfProc = (PFNGLMULTMATRIXFPROC)gl_wrap_get_pointer("glMultMatrixf");
	}
	ctx->glMultMatrixfProc(m);
};
void gl_wrap_context_glMultMatrixd(gl_wrap_context* ctx, GLdouble* m) {
	if(ctx->glMultMatrixdProc == NULL) {
		ctx->glMultMatrixdProc = (PFNGLMULTMATRIXDPROC)gl_wrap_get_pointer("glMultMatrixd");
	}
	ctx->glMultMatrixdProc(m);
};
void gl_wrap_context_glOrtho(gl_wrap_context* ctx, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
	if(ctx->glOrthoProc == NULL) {
		ctx->glOrthoProc = (PFNGLORTHOPROC)gl_wrap_get_pointer("glOrtho");
	}
	ctx->glOrthoProc(left, right, bottom, top, zNear, zFar);
};
void gl_wrap_context_glPopMatrix(gl_wrap_context* ctx) {
	if(ctx->glPopMatrixProc == NULL) {
		ctx->glPopMatrixProc = (PFNGLPOPMATRIXPROC)gl_wrap_get_pointer("glPopMatrix");
	}
	ctx->glPopMatrixProc();
};
void gl_wrap_context_glPushMatrix(gl_wrap_context* ctx) {
	if(ctx->glPushMatrixProc == NULL) {
		ctx->glPushMatrixProc = (PFNGLPUSHMATRIXPROC)gl_wrap_get_pointer("glPushMatrix");
	}
	ctx->glPushMatrixProc();
};
void gl_wrap_context_glRotated(gl_wrap_context* ctx, GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glRotatedProc == NULL) {
		ctx->glRotatedProc = (PFNGLROTATEDPROC)gl_wrap_get_pointer("glRotated");
	}
	ctx->glRotatedProc(angle, x, y, z);
};
void gl_wrap_context_glRotatef(gl_wrap_context* ctx, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glRotatefProc == NULL) {
		ctx->glRotatefProc = (PFNGLROTATEFPROC)gl_wrap_get_pointer("glRotatef");
	}
	ctx->glRotatefProc(angle, x, y, z);
};
void gl_wrap_context_glScaled(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glScaledProc == NULL) {
		ctx->glScaledProc = (PFNGLSCALEDPROC)gl_wrap_get_pointer("glScaled");
	}
	ctx->glScaledProc(x, y, z);
};
void gl_wrap_context_glScalef(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glScalefProc == NULL) {
		ctx->glScalefProc = (PFNGLSCALEFPROC)gl_wrap_get_pointer("glScalef");
	}
	ctx->glScalefProc(x, y, z);
};
void gl_wrap_context_glTranslated(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glTranslatedProc == NULL) {
		ctx->glTranslatedProc = (PFNGLTRANSLATEDPROC)gl_wrap_get_pointer("glTranslated");
	}
	ctx->glTranslatedProc(x, y, z);
};
void gl_wrap_context_glTranslatef(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glTranslatefProc == NULL) {
		ctx->glTranslatefProc = (PFNGLTRANSLATEFPROC)gl_wrap_get_pointer("glTranslatef");
	}
	ctx->glTranslatefProc(x, y, z);
};
void gl_wrap_context_glDrawArrays(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count) {
	if(ctx->glDrawArraysProc == NULL) {
		ctx->glDrawArraysProc = (PFNGLDRAWARRAYSPROC)gl_wrap_get_pointer("glDrawArrays");
	}
	ctx->glDrawArraysProc(mode, first, count);
};
void gl_wrap_context_glDrawElements(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices) {
	if(ctx->glDrawElementsProc == NULL) {
		ctx->glDrawElementsProc = (PFNGLDRAWELEMENTSPROC)gl_wrap_get_pointer("glDrawElements");
	}
	ctx->glDrawElementsProc(mode, count, type, indices);
};
void gl_wrap_context_glGetPointerv(gl_wrap_context* ctx, GLenum pname, void** params) {
	if(ctx->glGetPointervProc == NULL) {
		ctx->glGetPointervProc = (PFNGLGETPOINTERVPROC)gl_wrap_get_pointer("glGetPointerv");
	}
	ctx->glGetPointervProc(pname, params);
};
void gl_wrap_context_glPolygonOffset(gl_wrap_context* ctx, GLfloat factor, GLfloat units) {
	if(ctx->glPolygonOffsetProc == NULL) {
		ctx->glPolygonOffsetProc = (PFNGLPOLYGONOFFSETPROC)gl_wrap_get_pointer("glPolygonOffset");
	}
	ctx->glPolygonOffsetProc(factor, units);
};
void gl_wrap_context_glCopyTexImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
	if(ctx->glCopyTexImage1DProc == NULL) {
		ctx->glCopyTexImage1DProc = (PFNGLCOPYTEXIMAGE1DPROC)gl_wrap_get_pointer("glCopyTexImage1D");
	}
	ctx->glCopyTexImage1DProc(target, level, internalformat, x, y, width, border);
};
void gl_wrap_context_glCopyTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
	if(ctx->glCopyTexImage2DProc == NULL) {
		ctx->glCopyTexImage2DProc = (PFNGLCOPYTEXIMAGE2DPROC)gl_wrap_get_pointer("glCopyTexImage2D");
	}
	ctx->glCopyTexImage2DProc(target, level, internalformat, x, y, width, height, border);
};
void gl_wrap_context_glCopyTexSubImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
	if(ctx->glCopyTexSubImage1DProc == NULL) {
		ctx->glCopyTexSubImage1DProc = (PFNGLCOPYTEXSUBIMAGE1DPROC)gl_wrap_get_pointer("glCopyTexSubImage1D");
	}
	ctx->glCopyTexSubImage1DProc(target, level, xoffset, x, y, width);
};
void gl_wrap_context_glCopyTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glCopyTexSubImage2DProc == NULL) {
		ctx->glCopyTexSubImage2DProc = (PFNGLCOPYTEXSUBIMAGE2DPROC)gl_wrap_get_pointer("glCopyTexSubImage2D");
	}
	ctx->glCopyTexSubImage2DProc(target, level, xoffset, yoffset, x, y, width, height);
};
void gl_wrap_context_glTexSubImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexSubImage1DProc == NULL) {
		ctx->glTexSubImage1DProc = (PFNGLTEXSUBIMAGE1DPROC)gl_wrap_get_pointer("glTexSubImage1D");
	}
	ctx->glTexSubImage1DProc(target, level, xoffset, width, format, type, pixels);
};
void gl_wrap_context_glTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexSubImage2DProc == NULL) {
		ctx->glTexSubImage2DProc = (PFNGLTEXSUBIMAGE2DPROC)gl_wrap_get_pointer("glTexSubImage2D");
	}
	ctx->glTexSubImage2DProc(target, level, xoffset, yoffset, width, height, format, type, pixels);
};
void gl_wrap_context_glBindTexture(gl_wrap_context* ctx, GLenum target, GLuint texture) {
	if(ctx->glBindTextureProc == NULL) {
		ctx->glBindTextureProc = (PFNGLBINDTEXTUREPROC)gl_wrap_get_pointer("glBindTexture");
	}
	ctx->glBindTextureProc(target, texture);
};
void gl_wrap_context_glDeleteTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures) {
	if(ctx->glDeleteTexturesProc == NULL) {
		ctx->glDeleteTexturesProc = (PFNGLDELETETEXTURESPROC)gl_wrap_get_pointer("glDeleteTextures");
	}
	ctx->glDeleteTexturesProc(n, textures);
};
void gl_wrap_context_glGenTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures) {
	if(ctx->glGenTexturesProc == NULL) {
		ctx->glGenTexturesProc = (PFNGLGENTEXTURESPROC)gl_wrap_get_pointer("glGenTextures");
	}
	ctx->glGenTexturesProc(n, textures);
};
GLboolean gl_wrap_context_glIsTexture(gl_wrap_context* ctx, GLuint texture) {
	if(ctx->glIsTextureProc == NULL) {
		ctx->glIsTextureProc = (PFNGLISTEXTUREPROC)gl_wrap_get_pointer("glIsTexture");
	}
	return ctx->glIsTextureProc(texture);
};
void gl_wrap_context_glArrayElement(gl_wrap_context* ctx, GLint i) {
	if(ctx->glArrayElementProc == NULL) {
		ctx->glArrayElementProc = (PFNGLARRAYELEMENTPROC)gl_wrap_get_pointer("glArrayElement");
	}
	ctx->glArrayElementProc(i);
};
void gl_wrap_context_glColorPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glColorPointerProc == NULL) {
		ctx->glColorPointerProc = (PFNGLCOLORPOINTERPROC)gl_wrap_get_pointer("glColorPointer");
	}
	ctx->glColorPointerProc(size, type, stride, pointer);
};
void gl_wrap_context_glDisableClientState(gl_wrap_context* ctx, GLenum array) {
	if(ctx->glDisableClientStateProc == NULL) {
		ctx->glDisableClientStateProc = (PFNGLDISABLECLIENTSTATEPROC)gl_wrap_get_pointer("glDisableClientState");
	}
	ctx->glDisableClientStateProc(array);
};
void gl_wrap_context_glEdgeFlagPointer(gl_wrap_context* ctx, GLsizei stride, void* pointer) {
	if(ctx->glEdgeFlagPointerProc == NULL) {
		ctx->glEdgeFlagPointerProc = (PFNGLEDGEFLAGPOINTERPROC)gl_wrap_get_pointer("glEdgeFlagPointer");
	}
	ctx->glEdgeFlagPointerProc(stride, pointer);
};
void gl_wrap_context_glEnableClientState(gl_wrap_context* ctx, GLenum array) {
	if(ctx->glEnableClientStateProc == NULL) {
		ctx->glEnableClientStateProc = (PFNGLENABLECLIENTSTATEPROC)gl_wrap_get_pointer("glEnableClientState");
	}
	ctx->glEnableClientStateProc(array);
};
void gl_wrap_context_glIndexPointer(gl_wrap_context* ctx, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glIndexPointerProc == NULL) {
		ctx->glIndexPointerProc = (PFNGLINDEXPOINTERPROC)gl_wrap_get_pointer("glIndexPointer");
	}
	ctx->glIndexPointerProc(type, stride, pointer);
};
void gl_wrap_context_glInterleavedArrays(gl_wrap_context* ctx, GLenum format, GLsizei stride, void* pointer) {
	if(ctx->glInterleavedArraysProc == NULL) {
		ctx->glInterleavedArraysProc = (PFNGLINTERLEAVEDARRAYSPROC)gl_wrap_get_pointer("glInterleavedArrays");
	}
	ctx->glInterleavedArraysProc(format, stride, pointer);
};
void gl_wrap_context_glNormalPointer(gl_wrap_context* ctx, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glNormalPointerProc == NULL) {
		ctx->glNormalPointerProc = (PFNGLNORMALPOINTERPROC)gl_wrap_get_pointer("glNormalPointer");
	}
	ctx->glNormalPointerProc(type, stride, pointer);
};
void gl_wrap_context_glTexCoordPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glTexCoordPointerProc == NULL) {
		ctx->glTexCoordPointerProc = (PFNGLTEXCOORDPOINTERPROC)gl_wrap_get_pointer("glTexCoordPointer");
	}
	ctx->glTexCoordPointerProc(size, type, stride, pointer);
};
void gl_wrap_context_glVertexPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glVertexPointerProc == NULL) {
		ctx->glVertexPointerProc = (PFNGLVERTEXPOINTERPROC)gl_wrap_get_pointer("glVertexPointer");
	}
	ctx->glVertexPointerProc(size, type, stride, pointer);
};
GLboolean gl_wrap_context_glAreTexturesResident(gl_wrap_context* ctx, GLsizei n, GLuint* textures, GLboolean* residences) {
	if(ctx->glAreTexturesResidentProc == NULL) {
		ctx->glAreTexturesResidentProc = (PFNGLARETEXTURESRESIDENTPROC)gl_wrap_get_pointer("glAreTexturesResident");
	}
	return ctx->glAreTexturesResidentProc(n, textures, residences);
};
void gl_wrap_context_glPrioritizeTextures(gl_wrap_context* ctx, GLsizei n, GLuint* textures, GLfloat* priorities) {
	if(ctx->glPrioritizeTexturesProc == NULL) {
		ctx->glPrioritizeTexturesProc = (PFNGLPRIORITIZETEXTURESPROC)gl_wrap_get_pointer("glPrioritizeTextures");
	}
	ctx->glPrioritizeTexturesProc(n, textures, priorities);
};
void gl_wrap_context_glIndexub(gl_wrap_context* ctx, GLubyte c) {
	if(ctx->glIndexubProc == NULL) {
		ctx->glIndexubProc = (PFNGLINDEXUBPROC)gl_wrap_get_pointer("glIndexub");
	}
	ctx->glIndexubProc(c);
};
void gl_wrap_context_glIndexubv(gl_wrap_context* ctx, GLubyte* c) {
	if(ctx->glIndexubvProc == NULL) {
		ctx->glIndexubvProc = (PFNGLINDEXUBVPROC)gl_wrap_get_pointer("glIndexubv");
	}
	ctx->glIndexubvProc(c);
};
void gl_wrap_context_glPopClientAttrib(gl_wrap_context* ctx) {
	if(ctx->glPopClientAttribProc == NULL) {
		ctx->glPopClientAttribProc = (PFNGLPOPCLIENTATTRIBPROC)gl_wrap_get_pointer("glPopClientAttrib");
	}
	ctx->glPopClientAttribProc();
};
void gl_wrap_context_glPushClientAttrib(gl_wrap_context* ctx, GLbitfield mask) {
	if(ctx->glPushClientAttribProc == NULL) {
		ctx->glPushClientAttribProc = (PFNGLPUSHCLIENTATTRIBPROC)gl_wrap_get_pointer("glPushClientAttrib");
	}
	ctx->glPushClientAttribProc(mask);
};
void gl_wrap_context_glDrawRangeElements(gl_wrap_context* ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices) {
	if(ctx->glDrawRangeElementsProc == NULL) {
		ctx->glDrawRangeElementsProc = (PFNGLDRAWRANGEELEMENTSPROC)gl_wrap_get_pointer("glDrawRangeElements");
	}
	ctx->glDrawRangeElementsProc(mode, start, end, count, type, indices);
};
void gl_wrap_context_glTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexImage3DProc == NULL) {
		ctx->glTexImage3DProc = (PFNGLTEXIMAGE3DPROC)gl_wrap_get_pointer("glTexImage3D");
	}
	ctx->glTexImage3DProc(target, level, internalformat, width, height, depth, border, format, type, pixels);
};
void gl_wrap_context_glTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* pixels) {
	if(ctx->glTexSubImage3DProc == NULL) {
		ctx->glTexSubImage3DProc = (PFNGLTEXSUBIMAGE3DPROC)gl_wrap_get_pointer("glTexSubImage3D");
	}
	ctx->glTexSubImage3DProc(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
};
void gl_wrap_context_glCopyTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glCopyTexSubImage3DProc == NULL) {
		ctx->glCopyTexSubImage3DProc = (PFNGLCOPYTEXSUBIMAGE3DPROC)gl_wrap_get_pointer("glCopyTexSubImage3D");
	}
	ctx->glCopyTexSubImage3DProc(target, level, xoffset, yoffset, zoffset, x, y, width, height);
};
void gl_wrap_context_glActiveTexture(gl_wrap_context* ctx, GLenum texture) {
	if(ctx->glActiveTextureProc == NULL) {
		ctx->glActiveTextureProc = (PFNGLACTIVETEXTUREPROC)gl_wrap_get_pointer("glActiveTexture");
	}
	ctx->glActiveTextureProc(texture);
};
void gl_wrap_context_glSampleCoverage(gl_wrap_context* ctx, GLfloat value, GLboolean invert) {
	if(ctx->glSampleCoverageProc == NULL) {
		ctx->glSampleCoverageProc = (PFNGLSAMPLECOVERAGEPROC)gl_wrap_get_pointer("glSampleCoverage");
	}
	ctx->glSampleCoverageProc(value, invert);
};
void gl_wrap_context_glCompressedTexImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexImage3DProc == NULL) {
		ctx->glCompressedTexImage3DProc = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)gl_wrap_get_pointer("glCompressedTexImage3D");
	}
	ctx->glCompressedTexImage3DProc(target, level, internalformat, width, height, depth, border, imageSize, data);
};
void gl_wrap_context_glCompressedTexImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexImage2DProc == NULL) {
		ctx->glCompressedTexImage2DProc = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)gl_wrap_get_pointer("glCompressedTexImage2D");
	}
	ctx->glCompressedTexImage2DProc(target, level, internalformat, width, height, border, imageSize, data);
};
void gl_wrap_context_glCompressedTexImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexImage1DProc == NULL) {
		ctx->glCompressedTexImage1DProc = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)gl_wrap_get_pointer("glCompressedTexImage1D");
	}
	ctx->glCompressedTexImage1DProc(target, level, internalformat, width, border, imageSize, data);
};
void gl_wrap_context_glCompressedTexSubImage3D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexSubImage3DProc == NULL) {
		ctx->glCompressedTexSubImage3DProc = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)gl_wrap_get_pointer("glCompressedTexSubImage3D");
	}
	ctx->glCompressedTexSubImage3DProc(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
};
void gl_wrap_context_glCompressedTexSubImage2D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexSubImage2DProc == NULL) {
		ctx->glCompressedTexSubImage2DProc = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)gl_wrap_get_pointer("glCompressedTexSubImage2D");
	}
	ctx->glCompressedTexSubImage2DProc(target, level, xoffset, yoffset, width, height, format, imageSize, data);
};
void gl_wrap_context_glCompressedTexSubImage1D(gl_wrap_context* ctx, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, void* data) {
	if(ctx->glCompressedTexSubImage1DProc == NULL) {
		ctx->glCompressedTexSubImage1DProc = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)gl_wrap_get_pointer("glCompressedTexSubImage1D");
	}
	ctx->glCompressedTexSubImage1DProc(target, level, xoffset, width, format, imageSize, data);
};
void gl_wrap_context_glGetCompressedTexImage(gl_wrap_context* ctx, GLenum target, GLint level, void* img) {
	if(ctx->glGetCompressedTexImageProc == NULL) {
		ctx->glGetCompressedTexImageProc = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)gl_wrap_get_pointer("glGetCompressedTexImage");
	}
	ctx->glGetCompressedTexImageProc(target, level, img);
};
void gl_wrap_context_glClientActiveTexture(gl_wrap_context* ctx, GLenum texture) {
	if(ctx->glClientActiveTextureProc == NULL) {
		ctx->glClientActiveTextureProc = (PFNGLCLIENTACTIVETEXTUREPROC)gl_wrap_get_pointer("glClientActiveTexture");
	}
	ctx->glClientActiveTextureProc(texture);
};
void gl_wrap_context_glMultiTexCoord1d(gl_wrap_context* ctx, GLenum target, GLdouble s) {
	if(ctx->glMultiTexCoord1dProc == NULL) {
		ctx->glMultiTexCoord1dProc = (PFNGLMULTITEXCOORD1DPROC)gl_wrap_get_pointer("glMultiTexCoord1d");
	}
	ctx->glMultiTexCoord1dProc(target, s);
};
void gl_wrap_context_glMultiTexCoord1dv(gl_wrap_context* ctx, GLenum target, GLdouble* v) {
	if(ctx->glMultiTexCoord1dvProc == NULL) {
		ctx->glMultiTexCoord1dvProc = (PFNGLMULTITEXCOORD1DVPROC)gl_wrap_get_pointer("glMultiTexCoord1dv");
	}
	ctx->glMultiTexCoord1dvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord1f(gl_wrap_context* ctx, GLenum target, GLfloat s) {
	if(ctx->glMultiTexCoord1fProc == NULL) {
		ctx->glMultiTexCoord1fProc = (PFNGLMULTITEXCOORD1FPROC)gl_wrap_get_pointer("glMultiTexCoord1f");
	}
	ctx->glMultiTexCoord1fProc(target, s);
};
void gl_wrap_context_glMultiTexCoord1fv(gl_wrap_context* ctx, GLenum target, GLfloat* v) {
	if(ctx->glMultiTexCoord1fvProc == NULL) {
		ctx->glMultiTexCoord1fvProc = (PFNGLMULTITEXCOORD1FVPROC)gl_wrap_get_pointer("glMultiTexCoord1fv");
	}
	ctx->glMultiTexCoord1fvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord1i(gl_wrap_context* ctx, GLenum target, GLint s) {
	if(ctx->glMultiTexCoord1iProc == NULL) {
		ctx->glMultiTexCoord1iProc = (PFNGLMULTITEXCOORD1IPROC)gl_wrap_get_pointer("glMultiTexCoord1i");
	}
	ctx->glMultiTexCoord1iProc(target, s);
};
void gl_wrap_context_glMultiTexCoord1iv(gl_wrap_context* ctx, GLenum target, GLint* v) {
	if(ctx->glMultiTexCoord1ivProc == NULL) {
		ctx->glMultiTexCoord1ivProc = (PFNGLMULTITEXCOORD1IVPROC)gl_wrap_get_pointer("glMultiTexCoord1iv");
	}
	ctx->glMultiTexCoord1ivProc(target, v);
};
void gl_wrap_context_glMultiTexCoord1s(gl_wrap_context* ctx, GLenum target, GLshort s) {
	if(ctx->glMultiTexCoord1sProc == NULL) {
		ctx->glMultiTexCoord1sProc = (PFNGLMULTITEXCOORD1SPROC)gl_wrap_get_pointer("glMultiTexCoord1s");
	}
	ctx->glMultiTexCoord1sProc(target, s);
};
void gl_wrap_context_glMultiTexCoord1sv(gl_wrap_context* ctx, GLenum target, GLshort* v) {
	if(ctx->glMultiTexCoord1svProc == NULL) {
		ctx->glMultiTexCoord1svProc = (PFNGLMULTITEXCOORD1SVPROC)gl_wrap_get_pointer("glMultiTexCoord1sv");
	}
	ctx->glMultiTexCoord1svProc(target, v);
};
void gl_wrap_context_glMultiTexCoord2d(gl_wrap_context* ctx, GLenum target, GLdouble s, GLdouble t) {
	if(ctx->glMultiTexCoord2dProc == NULL) {
		ctx->glMultiTexCoord2dProc = (PFNGLMULTITEXCOORD2DPROC)gl_wrap_get_pointer("glMultiTexCoord2d");
	}
	ctx->glMultiTexCoord2dProc(target, s, t);
};
void gl_wrap_context_glMultiTexCoord2dv(gl_wrap_context* ctx, GLenum target, GLdouble* v) {
	if(ctx->glMultiTexCoord2dvProc == NULL) {
		ctx->glMultiTexCoord2dvProc = (PFNGLMULTITEXCOORD2DVPROC)gl_wrap_get_pointer("glMultiTexCoord2dv");
	}
	ctx->glMultiTexCoord2dvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord2f(gl_wrap_context* ctx, GLenum target, GLfloat s, GLfloat t) {
	if(ctx->glMultiTexCoord2fProc == NULL) {
		ctx->glMultiTexCoord2fProc = (PFNGLMULTITEXCOORD2FPROC)gl_wrap_get_pointer("glMultiTexCoord2f");
	}
	ctx->glMultiTexCoord2fProc(target, s, t);
};
void gl_wrap_context_glMultiTexCoord2fv(gl_wrap_context* ctx, GLenum target, GLfloat* v) {
	if(ctx->glMultiTexCoord2fvProc == NULL) {
		ctx->glMultiTexCoord2fvProc = (PFNGLMULTITEXCOORD2FVPROC)gl_wrap_get_pointer("glMultiTexCoord2fv");
	}
	ctx->glMultiTexCoord2fvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord2i(gl_wrap_context* ctx, GLenum target, GLint s, GLint t) {
	if(ctx->glMultiTexCoord2iProc == NULL) {
		ctx->glMultiTexCoord2iProc = (PFNGLMULTITEXCOORD2IPROC)gl_wrap_get_pointer("glMultiTexCoord2i");
	}
	ctx->glMultiTexCoord2iProc(target, s, t);
};
void gl_wrap_context_glMultiTexCoord2iv(gl_wrap_context* ctx, GLenum target, GLint* v) {
	if(ctx->glMultiTexCoord2ivProc == NULL) {
		ctx->glMultiTexCoord2ivProc = (PFNGLMULTITEXCOORD2IVPROC)gl_wrap_get_pointer("glMultiTexCoord2iv");
	}
	ctx->glMultiTexCoord2ivProc(target, v);
};
void gl_wrap_context_glMultiTexCoord2s(gl_wrap_context* ctx, GLenum target, GLshort s, GLshort t) {
	if(ctx->glMultiTexCoord2sProc == NULL) {
		ctx->glMultiTexCoord2sProc = (PFNGLMULTITEXCOORD2SPROC)gl_wrap_get_pointer("glMultiTexCoord2s");
	}
	ctx->glMultiTexCoord2sProc(target, s, t);
};
void gl_wrap_context_glMultiTexCoord2sv(gl_wrap_context* ctx, GLenum target, GLshort* v) {
	if(ctx->glMultiTexCoord2svProc == NULL) {
		ctx->glMultiTexCoord2svProc = (PFNGLMULTITEXCOORD2SVPROC)gl_wrap_get_pointer("glMultiTexCoord2sv");
	}
	ctx->glMultiTexCoord2svProc(target, v);
};
void gl_wrap_context_glMultiTexCoord3d(gl_wrap_context* ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r) {
	if(ctx->glMultiTexCoord3dProc == NULL) {
		ctx->glMultiTexCoord3dProc = (PFNGLMULTITEXCOORD3DPROC)gl_wrap_get_pointer("glMultiTexCoord3d");
	}
	ctx->glMultiTexCoord3dProc(target, s, t, r);
};
void gl_wrap_context_glMultiTexCoord3dv(gl_wrap_context* ctx, GLenum target, GLdouble* v) {
	if(ctx->glMultiTexCoord3dvProc == NULL) {
		ctx->glMultiTexCoord3dvProc = (PFNGLMULTITEXCOORD3DVPROC)gl_wrap_get_pointer("glMultiTexCoord3dv");
	}
	ctx->glMultiTexCoord3dvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord3f(gl_wrap_context* ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r) {
	if(ctx->glMultiTexCoord3fProc == NULL) {
		ctx->glMultiTexCoord3fProc = (PFNGLMULTITEXCOORD3FPROC)gl_wrap_get_pointer("glMultiTexCoord3f");
	}
	ctx->glMultiTexCoord3fProc(target, s, t, r);
};
void gl_wrap_context_glMultiTexCoord3fv(gl_wrap_context* ctx, GLenum target, GLfloat* v) {
	if(ctx->glMultiTexCoord3fvProc == NULL) {
		ctx->glMultiTexCoord3fvProc = (PFNGLMULTITEXCOORD3FVPROC)gl_wrap_get_pointer("glMultiTexCoord3fv");
	}
	ctx->glMultiTexCoord3fvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord3i(gl_wrap_context* ctx, GLenum target, GLint s, GLint t, GLint r) {
	if(ctx->glMultiTexCoord3iProc == NULL) {
		ctx->glMultiTexCoord3iProc = (PFNGLMULTITEXCOORD3IPROC)gl_wrap_get_pointer("glMultiTexCoord3i");
	}
	ctx->glMultiTexCoord3iProc(target, s, t, r);
};
void gl_wrap_context_glMultiTexCoord3iv(gl_wrap_context* ctx, GLenum target, GLint* v) {
	if(ctx->glMultiTexCoord3ivProc == NULL) {
		ctx->glMultiTexCoord3ivProc = (PFNGLMULTITEXCOORD3IVPROC)gl_wrap_get_pointer("glMultiTexCoord3iv");
	}
	ctx->glMultiTexCoord3ivProc(target, v);
};
void gl_wrap_context_glMultiTexCoord3s(gl_wrap_context* ctx, GLenum target, GLshort s, GLshort t, GLshort r) {
	if(ctx->glMultiTexCoord3sProc == NULL) {
		ctx->glMultiTexCoord3sProc = (PFNGLMULTITEXCOORD3SPROC)gl_wrap_get_pointer("glMultiTexCoord3s");
	}
	ctx->glMultiTexCoord3sProc(target, s, t, r);
};
void gl_wrap_context_glMultiTexCoord3sv(gl_wrap_context* ctx, GLenum target, GLshort* v) {
	if(ctx->glMultiTexCoord3svProc == NULL) {
		ctx->glMultiTexCoord3svProc = (PFNGLMULTITEXCOORD3SVPROC)gl_wrap_get_pointer("glMultiTexCoord3sv");
	}
	ctx->glMultiTexCoord3svProc(target, v);
};
void gl_wrap_context_glMultiTexCoord4d(gl_wrap_context* ctx, GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
	if(ctx->glMultiTexCoord4dProc == NULL) {
		ctx->glMultiTexCoord4dProc = (PFNGLMULTITEXCOORD4DPROC)gl_wrap_get_pointer("glMultiTexCoord4d");
	}
	ctx->glMultiTexCoord4dProc(target, s, t, r, q);
};
void gl_wrap_context_glMultiTexCoord4dv(gl_wrap_context* ctx, GLenum target, GLdouble* v) {
	if(ctx->glMultiTexCoord4dvProc == NULL) {
		ctx->glMultiTexCoord4dvProc = (PFNGLMULTITEXCOORD4DVPROC)gl_wrap_get_pointer("glMultiTexCoord4dv");
	}
	ctx->glMultiTexCoord4dvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord4f(gl_wrap_context* ctx, GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
	if(ctx->glMultiTexCoord4fProc == NULL) {
		ctx->glMultiTexCoord4fProc = (PFNGLMULTITEXCOORD4FPROC)gl_wrap_get_pointer("glMultiTexCoord4f");
	}
	ctx->glMultiTexCoord4fProc(target, s, t, r, q);
};
void gl_wrap_context_glMultiTexCoord4fv(gl_wrap_context* ctx, GLenum target, GLfloat* v) {
	if(ctx->glMultiTexCoord4fvProc == NULL) {
		ctx->glMultiTexCoord4fvProc = (PFNGLMULTITEXCOORD4FVPROC)gl_wrap_get_pointer("glMultiTexCoord4fv");
	}
	ctx->glMultiTexCoord4fvProc(target, v);
};
void gl_wrap_context_glMultiTexCoord4i(gl_wrap_context* ctx, GLenum target, GLint s, GLint t, GLint r, GLint q) {
	if(ctx->glMultiTexCoord4iProc == NULL) {
		ctx->glMultiTexCoord4iProc = (PFNGLMULTITEXCOORD4IPROC)gl_wrap_get_pointer("glMultiTexCoord4i");
	}
	ctx->glMultiTexCoord4iProc(target, s, t, r, q);
};
void gl_wrap_context_glMultiTexCoord4iv(gl_wrap_context* ctx, GLenum target, GLint* v) {
	if(ctx->glMultiTexCoord4ivProc == NULL) {
		ctx->glMultiTexCoord4ivProc = (PFNGLMULTITEXCOORD4IVPROC)gl_wrap_get_pointer("glMultiTexCoord4iv");
	}
	ctx->glMultiTexCoord4ivProc(target, v);
};
void gl_wrap_context_glMultiTexCoord4s(gl_wrap_context* ctx, GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) {
	if(ctx->glMultiTexCoord4sProc == NULL) {
		ctx->glMultiTexCoord4sProc = (PFNGLMULTITEXCOORD4SPROC)gl_wrap_get_pointer("glMultiTexCoord4s");
	}
	ctx->glMultiTexCoord4sProc(target, s, t, r, q);
};
void gl_wrap_context_glMultiTexCoord4sv(gl_wrap_context* ctx, GLenum target, GLshort* v) {
	if(ctx->glMultiTexCoord4svProc == NULL) {
		ctx->glMultiTexCoord4svProc = (PFNGLMULTITEXCOORD4SVPROC)gl_wrap_get_pointer("glMultiTexCoord4sv");
	}
	ctx->glMultiTexCoord4svProc(target, v);
};
void gl_wrap_context_glLoadTransposeMatrixf(gl_wrap_context* ctx, GLfloat* m) {
	if(ctx->glLoadTransposeMatrixfProc == NULL) {
		ctx->glLoadTransposeMatrixfProc = (PFNGLLOADTRANSPOSEMATRIXFPROC)gl_wrap_get_pointer("glLoadTransposeMatrixf");
	}
	ctx->glLoadTransposeMatrixfProc(m);
};
void gl_wrap_context_glLoadTransposeMatrixd(gl_wrap_context* ctx, GLdouble* m) {
	if(ctx->glLoadTransposeMatrixdProc == NULL) {
		ctx->glLoadTransposeMatrixdProc = (PFNGLLOADTRANSPOSEMATRIXDPROC)gl_wrap_get_pointer("glLoadTransposeMatrixd");
	}
	ctx->glLoadTransposeMatrixdProc(m);
};
void gl_wrap_context_glMultTransposeMatrixf(gl_wrap_context* ctx, GLfloat* m) {
	if(ctx->glMultTransposeMatrixfProc == NULL) {
		ctx->glMultTransposeMatrixfProc = (PFNGLMULTTRANSPOSEMATRIXFPROC)gl_wrap_get_pointer("glMultTransposeMatrixf");
	}
	ctx->glMultTransposeMatrixfProc(m);
};
void gl_wrap_context_glMultTransposeMatrixd(gl_wrap_context* ctx, GLdouble* m) {
	if(ctx->glMultTransposeMatrixdProc == NULL) {
		ctx->glMultTransposeMatrixdProc = (PFNGLMULTTRANSPOSEMATRIXDPROC)gl_wrap_get_pointer("glMultTransposeMatrixd");
	}
	ctx->glMultTransposeMatrixdProc(m);
};
void gl_wrap_context_glBlendFuncSeparate(gl_wrap_context* ctx, GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
	if(ctx->glBlendFuncSeparateProc == NULL) {
		ctx->glBlendFuncSeparateProc = (PFNGLBLENDFUNCSEPARATEPROC)gl_wrap_get_pointer("glBlendFuncSeparate");
	}
	ctx->glBlendFuncSeparateProc(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
};
void gl_wrap_context_glMultiDrawArrays(gl_wrap_context* ctx, GLenum mode, GLint* first, GLsizei* count, GLsizei drawcount) {
	if(ctx->glMultiDrawArraysProc == NULL) {
		ctx->glMultiDrawArraysProc = (PFNGLMULTIDRAWARRAYSPROC)gl_wrap_get_pointer("glMultiDrawArrays");
	}
	ctx->glMultiDrawArraysProc(mode, first, count, drawcount);
};
void gl_wrap_context_glMultiDrawElements(gl_wrap_context* ctx, GLenum mode, GLsizei* count, GLenum type, void** indices, GLsizei drawcount) {
	if(ctx->glMultiDrawElementsProc == NULL) {
		ctx->glMultiDrawElementsProc = (PFNGLMULTIDRAWELEMENTSPROC)gl_wrap_get_pointer("glMultiDrawElements");
	}
	ctx->glMultiDrawElementsProc(mode, count, type, indices, drawcount);
};
void gl_wrap_context_glPointParameterf(gl_wrap_context* ctx, GLenum pname, GLfloat param) {
	if(ctx->glPointParameterfProc == NULL) {
		ctx->glPointParameterfProc = (PFNGLPOINTPARAMETERFPROC)gl_wrap_get_pointer("glPointParameterf");
	}
	ctx->glPointParameterfProc(pname, param);
};
void gl_wrap_context_glPointParameterfv(gl_wrap_context* ctx, GLenum pname, GLfloat* params) {
	if(ctx->glPointParameterfvProc == NULL) {
		ctx->glPointParameterfvProc = (PFNGLPOINTPARAMETERFVPROC)gl_wrap_get_pointer("glPointParameterfv");
	}
	ctx->glPointParameterfvProc(pname, params);
};
void gl_wrap_context_glPointParameteri(gl_wrap_context* ctx, GLenum pname, GLint param) {
	if(ctx->glPointParameteriProc == NULL) {
		ctx->glPointParameteriProc = (PFNGLPOINTPARAMETERIPROC)gl_wrap_get_pointer("glPointParameteri");
	}
	ctx->glPointParameteriProc(pname, param);
};
void gl_wrap_context_glPointParameteriv(gl_wrap_context* ctx, GLenum pname, GLint* params) {
	if(ctx->glPointParameterivProc == NULL) {
		ctx->glPointParameterivProc = (PFNGLPOINTPARAMETERIVPROC)gl_wrap_get_pointer("glPointParameteriv");
	}
	ctx->glPointParameterivProc(pname, params);
};
void gl_wrap_context_glFogCoordf(gl_wrap_context* ctx, GLfloat coord) {
	if(ctx->glFogCoordfProc == NULL) {
		ctx->glFogCoordfProc = (PFNGLFOGCOORDFPROC)gl_wrap_get_pointer("glFogCoordf");
	}
	ctx->glFogCoordfProc(coord);
};
void gl_wrap_context_glFogCoordfv(gl_wrap_context* ctx, GLfloat* coord) {
	if(ctx->glFogCoordfvProc == NULL) {
		ctx->glFogCoordfvProc = (PFNGLFOGCOORDFVPROC)gl_wrap_get_pointer("glFogCoordfv");
	}
	ctx->glFogCoordfvProc(coord);
};
void gl_wrap_context_glFogCoordd(gl_wrap_context* ctx, GLdouble coord) {
	if(ctx->glFogCoorddProc == NULL) {
		ctx->glFogCoorddProc = (PFNGLFOGCOORDDPROC)gl_wrap_get_pointer("glFogCoordd");
	}
	ctx->glFogCoorddProc(coord);
};
void gl_wrap_context_glFogCoorddv(gl_wrap_context* ctx, GLdouble* coord) {
	if(ctx->glFogCoorddvProc == NULL) {
		ctx->glFogCoorddvProc = (PFNGLFOGCOORDDVPROC)gl_wrap_get_pointer("glFogCoorddv");
	}
	ctx->glFogCoorddvProc(coord);
};
void gl_wrap_context_glFogCoordPointer(gl_wrap_context* ctx, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glFogCoordPointerProc == NULL) {
		ctx->glFogCoordPointerProc = (PFNGLFOGCOORDPOINTERPROC)gl_wrap_get_pointer("glFogCoordPointer");
	}
	ctx->glFogCoordPointerProc(type, stride, pointer);
};
void gl_wrap_context_glSecondaryColor3b(gl_wrap_context* ctx, GLbyte red, GLbyte green, GLbyte blue) {
	if(ctx->glSecondaryColor3bProc == NULL) {
		ctx->glSecondaryColor3bProc = (PFNGLSECONDARYCOLOR3BPROC)gl_wrap_get_pointer("glSecondaryColor3b");
	}
	ctx->glSecondaryColor3bProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3bv(gl_wrap_context* ctx, GLbyte* v) {
	if(ctx->glSecondaryColor3bvProc == NULL) {
		ctx->glSecondaryColor3bvProc = (PFNGLSECONDARYCOLOR3BVPROC)gl_wrap_get_pointer("glSecondaryColor3bv");
	}
	ctx->glSecondaryColor3bvProc(v);
};
void gl_wrap_context_glSecondaryColor3d(gl_wrap_context* ctx, GLdouble red, GLdouble green, GLdouble blue) {
	if(ctx->glSecondaryColor3dProc == NULL) {
		ctx->glSecondaryColor3dProc = (PFNGLSECONDARYCOLOR3DPROC)gl_wrap_get_pointer("glSecondaryColor3d");
	}
	ctx->glSecondaryColor3dProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glSecondaryColor3dvProc == NULL) {
		ctx->glSecondaryColor3dvProc = (PFNGLSECONDARYCOLOR3DVPROC)gl_wrap_get_pointer("glSecondaryColor3dv");
	}
	ctx->glSecondaryColor3dvProc(v);
};
void gl_wrap_context_glSecondaryColor3f(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue) {
	if(ctx->glSecondaryColor3fProc == NULL) {
		ctx->glSecondaryColor3fProc = (PFNGLSECONDARYCOLOR3FPROC)gl_wrap_get_pointer("glSecondaryColor3f");
	}
	ctx->glSecondaryColor3fProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glSecondaryColor3fvProc == NULL) {
		ctx->glSecondaryColor3fvProc = (PFNGLSECONDARYCOLOR3FVPROC)gl_wrap_get_pointer("glSecondaryColor3fv");
	}
	ctx->glSecondaryColor3fvProc(v);
};
void gl_wrap_context_glSecondaryColor3i(gl_wrap_context* ctx, GLint red, GLint green, GLint blue) {
	if(ctx->glSecondaryColor3iProc == NULL) {
		ctx->glSecondaryColor3iProc = (PFNGLSECONDARYCOLOR3IPROC)gl_wrap_get_pointer("glSecondaryColor3i");
	}
	ctx->glSecondaryColor3iProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glSecondaryColor3ivProc == NULL) {
		ctx->glSecondaryColor3ivProc = (PFNGLSECONDARYCOLOR3IVPROC)gl_wrap_get_pointer("glSecondaryColor3iv");
	}
	ctx->glSecondaryColor3ivProc(v);
};
void gl_wrap_context_glSecondaryColor3s(gl_wrap_context* ctx, GLshort red, GLshort green, GLshort blue) {
	if(ctx->glSecondaryColor3sProc == NULL) {
		ctx->glSecondaryColor3sProc = (PFNGLSECONDARYCOLOR3SPROC)gl_wrap_get_pointer("glSecondaryColor3s");
	}
	ctx->glSecondaryColor3sProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glSecondaryColor3svProc == NULL) {
		ctx->glSecondaryColor3svProc = (PFNGLSECONDARYCOLOR3SVPROC)gl_wrap_get_pointer("glSecondaryColor3sv");
	}
	ctx->glSecondaryColor3svProc(v);
};
void gl_wrap_context_glSecondaryColor3ub(gl_wrap_context* ctx, GLubyte red, GLubyte green, GLubyte blue) {
	if(ctx->glSecondaryColor3ubProc == NULL) {
		ctx->glSecondaryColor3ubProc = (PFNGLSECONDARYCOLOR3UBPROC)gl_wrap_get_pointer("glSecondaryColor3ub");
	}
	ctx->glSecondaryColor3ubProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3ubv(gl_wrap_context* ctx, GLubyte* v) {
	if(ctx->glSecondaryColor3ubvProc == NULL) {
		ctx->glSecondaryColor3ubvProc = (PFNGLSECONDARYCOLOR3UBVPROC)gl_wrap_get_pointer("glSecondaryColor3ubv");
	}
	ctx->glSecondaryColor3ubvProc(v);
};
void gl_wrap_context_glSecondaryColor3ui(gl_wrap_context* ctx, GLuint red, GLuint green, GLuint blue) {
	if(ctx->glSecondaryColor3uiProc == NULL) {
		ctx->glSecondaryColor3uiProc = (PFNGLSECONDARYCOLOR3UIPROC)gl_wrap_get_pointer("glSecondaryColor3ui");
	}
	ctx->glSecondaryColor3uiProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3uiv(gl_wrap_context* ctx, GLuint* v) {
	if(ctx->glSecondaryColor3uivProc == NULL) {
		ctx->glSecondaryColor3uivProc = (PFNGLSECONDARYCOLOR3UIVPROC)gl_wrap_get_pointer("glSecondaryColor3uiv");
	}
	ctx->glSecondaryColor3uivProc(v);
};
void gl_wrap_context_glSecondaryColor3us(gl_wrap_context* ctx, GLushort red, GLushort green, GLushort blue) {
	if(ctx->glSecondaryColor3usProc == NULL) {
		ctx->glSecondaryColor3usProc = (PFNGLSECONDARYCOLOR3USPROC)gl_wrap_get_pointer("glSecondaryColor3us");
	}
	ctx->glSecondaryColor3usProc(red, green, blue);
};
void gl_wrap_context_glSecondaryColor3usv(gl_wrap_context* ctx, GLushort* v) {
	if(ctx->glSecondaryColor3usvProc == NULL) {
		ctx->glSecondaryColor3usvProc = (PFNGLSECONDARYCOLOR3USVPROC)gl_wrap_get_pointer("glSecondaryColor3usv");
	}
	ctx->glSecondaryColor3usvProc(v);
};
void gl_wrap_context_glSecondaryColorPointer(gl_wrap_context* ctx, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glSecondaryColorPointerProc == NULL) {
		ctx->glSecondaryColorPointerProc = (PFNGLSECONDARYCOLORPOINTERPROC)gl_wrap_get_pointer("glSecondaryColorPointer");
	}
	ctx->glSecondaryColorPointerProc(size, type, stride, pointer);
};
void gl_wrap_context_glWindowPos2d(gl_wrap_context* ctx, GLdouble x, GLdouble y) {
	if(ctx->glWindowPos2dProc == NULL) {
		ctx->glWindowPos2dProc = (PFNGLWINDOWPOS2DPROC)gl_wrap_get_pointer("glWindowPos2d");
	}
	ctx->glWindowPos2dProc(x, y);
};
void gl_wrap_context_glWindowPos2dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glWindowPos2dvProc == NULL) {
		ctx->glWindowPos2dvProc = (PFNGLWINDOWPOS2DVPROC)gl_wrap_get_pointer("glWindowPos2dv");
	}
	ctx->glWindowPos2dvProc(v);
};
void gl_wrap_context_glWindowPos2f(gl_wrap_context* ctx, GLfloat x, GLfloat y) {
	if(ctx->glWindowPos2fProc == NULL) {
		ctx->glWindowPos2fProc = (PFNGLWINDOWPOS2FPROC)gl_wrap_get_pointer("glWindowPos2f");
	}
	ctx->glWindowPos2fProc(x, y);
};
void gl_wrap_context_glWindowPos2fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glWindowPos2fvProc == NULL) {
		ctx->glWindowPos2fvProc = (PFNGLWINDOWPOS2FVPROC)gl_wrap_get_pointer("glWindowPos2fv");
	}
	ctx->glWindowPos2fvProc(v);
};
void gl_wrap_context_glWindowPos2i(gl_wrap_context* ctx, GLint x, GLint y) {
	if(ctx->glWindowPos2iProc == NULL) {
		ctx->glWindowPos2iProc = (PFNGLWINDOWPOS2IPROC)gl_wrap_get_pointer("glWindowPos2i");
	}
	ctx->glWindowPos2iProc(x, y);
};
void gl_wrap_context_glWindowPos2iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glWindowPos2ivProc == NULL) {
		ctx->glWindowPos2ivProc = (PFNGLWINDOWPOS2IVPROC)gl_wrap_get_pointer("glWindowPos2iv");
	}
	ctx->glWindowPos2ivProc(v);
};
void gl_wrap_context_glWindowPos2s(gl_wrap_context* ctx, GLshort x, GLshort y) {
	if(ctx->glWindowPos2sProc == NULL) {
		ctx->glWindowPos2sProc = (PFNGLWINDOWPOS2SPROC)gl_wrap_get_pointer("glWindowPos2s");
	}
	ctx->glWindowPos2sProc(x, y);
};
void gl_wrap_context_glWindowPos2sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glWindowPos2svProc == NULL) {
		ctx->glWindowPos2svProc = (PFNGLWINDOWPOS2SVPROC)gl_wrap_get_pointer("glWindowPos2sv");
	}
	ctx->glWindowPos2svProc(v);
};
void gl_wrap_context_glWindowPos3d(gl_wrap_context* ctx, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glWindowPos3dProc == NULL) {
		ctx->glWindowPos3dProc = (PFNGLWINDOWPOS3DPROC)gl_wrap_get_pointer("glWindowPos3d");
	}
	ctx->glWindowPos3dProc(x, y, z);
};
void gl_wrap_context_glWindowPos3dv(gl_wrap_context* ctx, GLdouble* v) {
	if(ctx->glWindowPos3dvProc == NULL) {
		ctx->glWindowPos3dvProc = (PFNGLWINDOWPOS3DVPROC)gl_wrap_get_pointer("glWindowPos3dv");
	}
	ctx->glWindowPos3dvProc(v);
};
void gl_wrap_context_glWindowPos3f(gl_wrap_context* ctx, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glWindowPos3fProc == NULL) {
		ctx->glWindowPos3fProc = (PFNGLWINDOWPOS3FPROC)gl_wrap_get_pointer("glWindowPos3f");
	}
	ctx->glWindowPos3fProc(x, y, z);
};
void gl_wrap_context_glWindowPos3fv(gl_wrap_context* ctx, GLfloat* v) {
	if(ctx->glWindowPos3fvProc == NULL) {
		ctx->glWindowPos3fvProc = (PFNGLWINDOWPOS3FVPROC)gl_wrap_get_pointer("glWindowPos3fv");
	}
	ctx->glWindowPos3fvProc(v);
};
void gl_wrap_context_glWindowPos3i(gl_wrap_context* ctx, GLint x, GLint y, GLint z) {
	if(ctx->glWindowPos3iProc == NULL) {
		ctx->glWindowPos3iProc = (PFNGLWINDOWPOS3IPROC)gl_wrap_get_pointer("glWindowPos3i");
	}
	ctx->glWindowPos3iProc(x, y, z);
};
void gl_wrap_context_glWindowPos3iv(gl_wrap_context* ctx, GLint* v) {
	if(ctx->glWindowPos3ivProc == NULL) {
		ctx->glWindowPos3ivProc = (PFNGLWINDOWPOS3IVPROC)gl_wrap_get_pointer("glWindowPos3iv");
	}
	ctx->glWindowPos3ivProc(v);
};
void gl_wrap_context_glWindowPos3s(gl_wrap_context* ctx, GLshort x, GLshort y, GLshort z) {
	if(ctx->glWindowPos3sProc == NULL) {
		ctx->glWindowPos3sProc = (PFNGLWINDOWPOS3SPROC)gl_wrap_get_pointer("glWindowPos3s");
	}
	ctx->glWindowPos3sProc(x, y, z);
};
void gl_wrap_context_glWindowPos3sv(gl_wrap_context* ctx, GLshort* v) {
	if(ctx->glWindowPos3svProc == NULL) {
		ctx->glWindowPos3svProc = (PFNGLWINDOWPOS3SVPROC)gl_wrap_get_pointer("glWindowPos3sv");
	}
	ctx->glWindowPos3svProc(v);
};
void gl_wrap_context_glBlendColor(gl_wrap_context* ctx, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	if(ctx->glBlendColorProc == NULL) {
		ctx->glBlendColorProc = (PFNGLBLENDCOLORPROC)gl_wrap_get_pointer("glBlendColor");
	}
	ctx->glBlendColorProc(red, green, blue, alpha);
};
void gl_wrap_context_glBlendEquation(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glBlendEquationProc == NULL) {
		ctx->glBlendEquationProc = (PFNGLBLENDEQUATIONPROC)gl_wrap_get_pointer("glBlendEquation");
	}
	ctx->glBlendEquationProc(mode);
};
void gl_wrap_context_glGenQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glGenQueriesProc == NULL) {
		ctx->glGenQueriesProc = (PFNGLGENQUERIESPROC)gl_wrap_get_pointer("glGenQueries");
	}
	ctx->glGenQueriesProc(n, ids);
};
void gl_wrap_context_glDeleteQueries(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glDeleteQueriesProc == NULL) {
		ctx->glDeleteQueriesProc = (PFNGLDELETEQUERIESPROC)gl_wrap_get_pointer("glDeleteQueries");
	}
	ctx->glDeleteQueriesProc(n, ids);
};
GLboolean gl_wrap_context_glIsQuery(gl_wrap_context* ctx, GLuint id) {
	if(ctx->glIsQueryProc == NULL) {
		ctx->glIsQueryProc = (PFNGLISQUERYPROC)gl_wrap_get_pointer("glIsQuery");
	}
	return ctx->glIsQueryProc(id);
};
void gl_wrap_context_glBeginQuery(gl_wrap_context* ctx, GLenum target, GLuint id) {
	if(ctx->glBeginQueryProc == NULL) {
		ctx->glBeginQueryProc = (PFNGLBEGINQUERYPROC)gl_wrap_get_pointer("glBeginQuery");
	}
	ctx->glBeginQueryProc(target, id);
};
void gl_wrap_context_glEndQuery(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glEndQueryProc == NULL) {
		ctx->glEndQueryProc = (PFNGLENDQUERYPROC)gl_wrap_get_pointer("glEndQuery");
	}
	ctx->glEndQueryProc(target);
};
void gl_wrap_context_glGetQueryiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetQueryivProc == NULL) {
		ctx->glGetQueryivProc = (PFNGLGETQUERYIVPROC)gl_wrap_get_pointer("glGetQueryiv");
	}
	ctx->glGetQueryivProc(target, pname, params);
};
void gl_wrap_context_glGetQueryObjectiv(gl_wrap_context* ctx, GLuint id, GLenum pname, GLint* params) {
	if(ctx->glGetQueryObjectivProc == NULL) {
		ctx->glGetQueryObjectivProc = (PFNGLGETQUERYOBJECTIVPROC)gl_wrap_get_pointer("glGetQueryObjectiv");
	}
	ctx->glGetQueryObjectivProc(id, pname, params);
};
void gl_wrap_context_glGetQueryObjectuiv(gl_wrap_context* ctx, GLuint id, GLenum pname, GLuint* params) {
	if(ctx->glGetQueryObjectuivProc == NULL) {
		ctx->glGetQueryObjectuivProc = (PFNGLGETQUERYOBJECTUIVPROC)gl_wrap_get_pointer("glGetQueryObjectuiv");
	}
	ctx->glGetQueryObjectuivProc(id, pname, params);
};
void gl_wrap_context_glBindBuffer(gl_wrap_context* ctx, GLenum target, GLuint buffer) {
	if(ctx->glBindBufferProc == NULL) {
		ctx->glBindBufferProc = (PFNGLBINDBUFFERPROC)gl_wrap_get_pointer("glBindBuffer");
	}
	ctx->glBindBufferProc(target, buffer);
};
void gl_wrap_context_glDeleteBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers) {
	if(ctx->glDeleteBuffersProc == NULL) {
		ctx->glDeleteBuffersProc = (PFNGLDELETEBUFFERSPROC)gl_wrap_get_pointer("glDeleteBuffers");
	}
	ctx->glDeleteBuffersProc(n, buffers);
};
void gl_wrap_context_glGenBuffers(gl_wrap_context* ctx, GLsizei n, GLuint* buffers) {
	if(ctx->glGenBuffersProc == NULL) {
		ctx->glGenBuffersProc = (PFNGLGENBUFFERSPROC)gl_wrap_get_pointer("glGenBuffers");
	}
	ctx->glGenBuffersProc(n, buffers);
};
GLboolean gl_wrap_context_glIsBuffer(gl_wrap_context* ctx, GLuint buffer) {
	if(ctx->glIsBufferProc == NULL) {
		ctx->glIsBufferProc = (PFNGLISBUFFERPROC)gl_wrap_get_pointer("glIsBuffer");
	}
	return ctx->glIsBufferProc(buffer);
};
void gl_wrap_context_glBufferData(gl_wrap_context* ctx, GLenum target, GLsizeiptr size, void* data, GLenum usage) {
	if(ctx->glBufferDataProc == NULL) {
		ctx->glBufferDataProc = (PFNGLBUFFERDATAPROC)gl_wrap_get_pointer("glBufferData");
	}
	ctx->glBufferDataProc(target, size, data, usage);
};
void gl_wrap_context_glBufferSubData(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr size, void* data) {
	if(ctx->glBufferSubDataProc == NULL) {
		ctx->glBufferSubDataProc = (PFNGLBUFFERSUBDATAPROC)gl_wrap_get_pointer("glBufferSubData");
	}
	ctx->glBufferSubDataProc(target, offset, size, data);
};
void gl_wrap_context_glGetBufferSubData(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr size, void* data) {
	if(ctx->glGetBufferSubDataProc == NULL) {
		ctx->glGetBufferSubDataProc = (PFNGLGETBUFFERSUBDATAPROC)gl_wrap_get_pointer("glGetBufferSubData");
	}
	ctx->glGetBufferSubDataProc(target, offset, size, data);
};
void gl_wrap_context_glMapBuffer(gl_wrap_context* ctx, GLenum target, GLenum access) {
	if(ctx->glMapBufferProc == NULL) {
		ctx->glMapBufferProc = (PFNGLMAPBUFFERPROC)gl_wrap_get_pointer("glMapBuffer");
	}
	ctx->glMapBufferProc(target, access);
};
GLboolean gl_wrap_context_glUnmapBuffer(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glUnmapBufferProc == NULL) {
		ctx->glUnmapBufferProc = (PFNGLUNMAPBUFFERPROC)gl_wrap_get_pointer("glUnmapBuffer");
	}
	return ctx->glUnmapBufferProc(target);
};
void gl_wrap_context_glGetBufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetBufferParameterivProc == NULL) {
		ctx->glGetBufferParameterivProc = (PFNGLGETBUFFERPARAMETERIVPROC)gl_wrap_get_pointer("glGetBufferParameteriv");
	}
	ctx->glGetBufferParameterivProc(target, pname, params);
};
void gl_wrap_context_glGetBufferPointerv(gl_wrap_context* ctx, GLenum target, GLenum pname, void** params) {
	if(ctx->glGetBufferPointervProc == NULL) {
		ctx->glGetBufferPointervProc = (PFNGLGETBUFFERPOINTERVPROC)gl_wrap_get_pointer("glGetBufferPointerv");
	}
	ctx->glGetBufferPointervProc(target, pname, params);
};
void gl_wrap_context_glBlendEquationSeparate(gl_wrap_context* ctx, GLenum modeRGB, GLenum modeAlpha) {
	if(ctx->glBlendEquationSeparateProc == NULL) {
		ctx->glBlendEquationSeparateProc = (PFNGLBLENDEQUATIONSEPARATEPROC)gl_wrap_get_pointer("glBlendEquationSeparate");
	}
	ctx->glBlendEquationSeparateProc(modeRGB, modeAlpha);
};
void gl_wrap_context_glDrawBuffers(gl_wrap_context* ctx, GLsizei n, GLenum* bufs) {
	if(ctx->glDrawBuffersProc == NULL) {
		ctx->glDrawBuffersProc = (PFNGLDRAWBUFFERSPROC)gl_wrap_get_pointer("glDrawBuffers");
	}
	ctx->glDrawBuffersProc(n, bufs);
};
void gl_wrap_context_glStencilOpSeparate(gl_wrap_context* ctx, GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
	if(ctx->glStencilOpSeparateProc == NULL) {
		ctx->glStencilOpSeparateProc = (PFNGLSTENCILOPSEPARATEPROC)gl_wrap_get_pointer("glStencilOpSeparate");
	}
	ctx->glStencilOpSeparateProc(face, sfail, dpfail, dppass);
};
void gl_wrap_context_glStencilFuncSeparate(gl_wrap_context* ctx, GLenum face, GLenum func, GLint ref, GLuint mask) {
	if(ctx->glStencilFuncSeparateProc == NULL) {
		ctx->glStencilFuncSeparateProc = (PFNGLSTENCILFUNCSEPARATEPROC)gl_wrap_get_pointer("glStencilFuncSeparate");
	}
	ctx->glStencilFuncSeparateProc(face, func, ref, mask);
};
void gl_wrap_context_glStencilMaskSeparate(gl_wrap_context* ctx, GLenum face, GLuint mask) {
	if(ctx->glStencilMaskSeparateProc == NULL) {
		ctx->glStencilMaskSeparateProc = (PFNGLSTENCILMASKSEPARATEPROC)gl_wrap_get_pointer("glStencilMaskSeparate");
	}
	ctx->glStencilMaskSeparateProc(face, mask);
};
void gl_wrap_context_glAttachShader(gl_wrap_context* ctx, GLuint program, GLuint shader) {
	if(ctx->glAttachShaderProc == NULL) {
		ctx->glAttachShaderProc = (PFNGLATTACHSHADERPROC)gl_wrap_get_pointer("glAttachShader");
	}
	ctx->glAttachShaderProc(program, shader);
};
void gl_wrap_context_glBindAttribLocation(gl_wrap_context* ctx, GLuint program, GLuint index, GLchar* name) {
	if(ctx->glBindAttribLocationProc == NULL) {
		ctx->glBindAttribLocationProc = (PFNGLBINDATTRIBLOCATIONPROC)gl_wrap_get_pointer("glBindAttribLocation");
	}
	ctx->glBindAttribLocationProc(program, index, name);
};
void gl_wrap_context_glCompileShader(gl_wrap_context* ctx, GLuint shader) {
	if(ctx->glCompileShaderProc == NULL) {
		ctx->glCompileShaderProc = (PFNGLCOMPILESHADERPROC)gl_wrap_get_pointer("glCompileShader");
	}
	ctx->glCompileShaderProc(shader);
};
GLuint gl_wrap_context_glCreateProgram(gl_wrap_context* ctx) {
	if(ctx->glCreateProgramProc == NULL) {
		ctx->glCreateProgramProc = (PFNGLCREATEPROGRAMPROC)gl_wrap_get_pointer("glCreateProgram");
	}
	return ctx->glCreateProgramProc();
};
GLuint gl_wrap_context_glCreateShader(gl_wrap_context* ctx, GLenum type) {
	if(ctx->glCreateShaderProc == NULL) {
		ctx->glCreateShaderProc = (PFNGLCREATESHADERPROC)gl_wrap_get_pointer("glCreateShader");
	}
	return ctx->glCreateShaderProc(type);
};
void gl_wrap_context_glDeleteProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glDeleteProgramProc == NULL) {
		ctx->glDeleteProgramProc = (PFNGLDELETEPROGRAMPROC)gl_wrap_get_pointer("glDeleteProgram");
	}
	ctx->glDeleteProgramProc(program);
};
void gl_wrap_context_glDeleteShader(gl_wrap_context* ctx, GLuint shader) {
	if(ctx->glDeleteShaderProc == NULL) {
		ctx->glDeleteShaderProc = (PFNGLDELETESHADERPROC)gl_wrap_get_pointer("glDeleteShader");
	}
	ctx->glDeleteShaderProc(shader);
};
void gl_wrap_context_glDetachShader(gl_wrap_context* ctx, GLuint program, GLuint shader) {
	if(ctx->glDetachShaderProc == NULL) {
		ctx->glDetachShaderProc = (PFNGLDETACHSHADERPROC)gl_wrap_get_pointer("glDetachShader");
	}
	ctx->glDetachShaderProc(program, shader);
};
void gl_wrap_context_glDisableVertexAttribArray(gl_wrap_context* ctx, GLuint index) {
	if(ctx->glDisableVertexAttribArrayProc == NULL) {
		ctx->glDisableVertexAttribArrayProc = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)gl_wrap_get_pointer("glDisableVertexAttribArray");
	}
	ctx->glDisableVertexAttribArrayProc(index);
};
void gl_wrap_context_glEnableVertexAttribArray(gl_wrap_context* ctx, GLuint index) {
	if(ctx->glEnableVertexAttribArrayProc == NULL) {
		ctx->glEnableVertexAttribArrayProc = (PFNGLENABLEVERTEXATTRIBARRAYPROC)gl_wrap_get_pointer("glEnableVertexAttribArray");
	}
	ctx->glEnableVertexAttribArrayProc(index);
};
void gl_wrap_context_glGetActiveAttrib(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {
	if(ctx->glGetActiveAttribProc == NULL) {
		ctx->glGetActiveAttribProc = (PFNGLGETACTIVEATTRIBPROC)gl_wrap_get_pointer("glGetActiveAttrib");
	}
	ctx->glGetActiveAttribProc(program, index, bufSize, length, size, type, name);
};
void gl_wrap_context_glGetActiveUniform(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {
	if(ctx->glGetActiveUniformProc == NULL) {
		ctx->glGetActiveUniformProc = (PFNGLGETACTIVEUNIFORMPROC)gl_wrap_get_pointer("glGetActiveUniform");
	}
	ctx->glGetActiveUniformProc(program, index, bufSize, length, size, type, name);
};
void gl_wrap_context_glGetAttachedShaders(gl_wrap_context* ctx, GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders) {
	if(ctx->glGetAttachedShadersProc == NULL) {
		ctx->glGetAttachedShadersProc = (PFNGLGETATTACHEDSHADERSPROC)gl_wrap_get_pointer("glGetAttachedShaders");
	}
	ctx->glGetAttachedShadersProc(program, maxCount, count, shaders);
};
GLint gl_wrap_context_glGetAttribLocation(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetAttribLocationProc == NULL) {
		ctx->glGetAttribLocationProc = (PFNGLGETATTRIBLOCATIONPROC)gl_wrap_get_pointer("glGetAttribLocation");
	}
	return ctx->glGetAttribLocationProc(program, name);
};
void gl_wrap_context_glGetProgramiv(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint* params) {
	if(ctx->glGetProgramivProc == NULL) {
		ctx->glGetProgramivProc = (PFNGLGETPROGRAMIVPROC)gl_wrap_get_pointer("glGetProgramiv");
	}
	ctx->glGetProgramivProc(program, pname, params);
};
void gl_wrap_context_glGetProgramInfoLog(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	if(ctx->glGetProgramInfoLogProc == NULL) {
		ctx->glGetProgramInfoLogProc = (PFNGLGETPROGRAMINFOLOGPROC)gl_wrap_get_pointer("glGetProgramInfoLog");
	}
	ctx->glGetProgramInfoLogProc(program, bufSize, length, infoLog);
};
void gl_wrap_context_glGetShaderiv(gl_wrap_context* ctx, GLuint shader, GLenum pname, GLint* params) {
	if(ctx->glGetShaderivProc == NULL) {
		ctx->glGetShaderivProc = (PFNGLGETSHADERIVPROC)gl_wrap_get_pointer("glGetShaderiv");
	}
	ctx->glGetShaderivProc(shader, pname, params);
};
void gl_wrap_context_glGetShaderInfoLog(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	if(ctx->glGetShaderInfoLogProc == NULL) {
		ctx->glGetShaderInfoLogProc = (PFNGLGETSHADERINFOLOGPROC)gl_wrap_get_pointer("glGetShaderInfoLog");
	}
	ctx->glGetShaderInfoLogProc(shader, bufSize, length, infoLog);
};
void gl_wrap_context_glGetShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source) {
	if(ctx->glGetShaderSourceProc == NULL) {
		ctx->glGetShaderSourceProc = (PFNGLGETSHADERSOURCEPROC)gl_wrap_get_pointer("glGetShaderSource");
	}
	ctx->glGetShaderSourceProc(shader, bufSize, length, source);
};
GLint gl_wrap_context_glGetUniformLocation(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetUniformLocationProc == NULL) {
		ctx->glGetUniformLocationProc = (PFNGLGETUNIFORMLOCATIONPROC)gl_wrap_get_pointer("glGetUniformLocation");
	}
	return ctx->glGetUniformLocationProc(program, name);
};
void gl_wrap_context_glGetUniformfv(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat* params) {
	if(ctx->glGetUniformfvProc == NULL) {
		ctx->glGetUniformfvProc = (PFNGLGETUNIFORMFVPROC)gl_wrap_get_pointer("glGetUniformfv");
	}
	ctx->glGetUniformfvProc(program, location, params);
};
void gl_wrap_context_glGetUniformiv(gl_wrap_context* ctx, GLuint program, GLint location, GLint* params) {
	if(ctx->glGetUniformivProc == NULL) {
		ctx->glGetUniformivProc = (PFNGLGETUNIFORMIVPROC)gl_wrap_get_pointer("glGetUniformiv");
	}
	ctx->glGetUniformivProc(program, location, params);
};
void gl_wrap_context_glGetVertexAttribdv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLdouble* params) {
	if(ctx->glGetVertexAttribdvProc == NULL) {
		ctx->glGetVertexAttribdvProc = (PFNGLGETVERTEXATTRIBDVPROC)gl_wrap_get_pointer("glGetVertexAttribdv");
	}
	ctx->glGetVertexAttribdvProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribfv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLfloat* params) {
	if(ctx->glGetVertexAttribfvProc == NULL) {
		ctx->glGetVertexAttribfvProc = (PFNGLGETVERTEXATTRIBFVPROC)gl_wrap_get_pointer("glGetVertexAttribfv");
	}
	ctx->glGetVertexAttribfvProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params) {
	if(ctx->glGetVertexAttribivProc == NULL) {
		ctx->glGetVertexAttribivProc = (PFNGLGETVERTEXATTRIBIVPROC)gl_wrap_get_pointer("glGetVertexAttribiv");
	}
	ctx->glGetVertexAttribivProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribPointerv(gl_wrap_context* ctx, GLuint index, GLenum pname, void** pointer) {
	if(ctx->glGetVertexAttribPointervProc == NULL) {
		ctx->glGetVertexAttribPointervProc = (PFNGLGETVERTEXATTRIBPOINTERVPROC)gl_wrap_get_pointer("glGetVertexAttribPointerv");
	}
	ctx->glGetVertexAttribPointervProc(index, pname, pointer);
};
GLboolean gl_wrap_context_glIsProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glIsProgramProc == NULL) {
		ctx->glIsProgramProc = (PFNGLISPROGRAMPROC)gl_wrap_get_pointer("glIsProgram");
	}
	return ctx->glIsProgramProc(program);
};
GLboolean gl_wrap_context_glIsShader(gl_wrap_context* ctx, GLuint shader) {
	if(ctx->glIsShaderProc == NULL) {
		ctx->glIsShaderProc = (PFNGLISSHADERPROC)gl_wrap_get_pointer("glIsShader");
	}
	return ctx->glIsShaderProc(shader);
};
void gl_wrap_context_glLinkProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glLinkProgramProc == NULL) {
		ctx->glLinkProgramProc = (PFNGLLINKPROGRAMPROC)gl_wrap_get_pointer("glLinkProgram");
	}
	ctx->glLinkProgramProc(program);
};
void gl_wrap_context_glShaderSource(gl_wrap_context* ctx, GLuint shader, GLsizei count, GLchar** string, GLint* length) {
	if(ctx->glShaderSourceProc == NULL) {
		ctx->glShaderSourceProc = (PFNGLSHADERSOURCEPROC)gl_wrap_get_pointer("glShaderSource");
	}
	ctx->glShaderSourceProc(shader, count, string, length);
};
void gl_wrap_context_glUseProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glUseProgramProc == NULL) {
		ctx->glUseProgramProc = (PFNGLUSEPROGRAMPROC)gl_wrap_get_pointer("glUseProgram");
	}
	ctx->glUseProgramProc(program);
};
void gl_wrap_context_glUniform1f(gl_wrap_context* ctx, GLint location, GLfloat v0) {
	if(ctx->glUniform1fProc == NULL) {
		ctx->glUniform1fProc = (PFNGLUNIFORM1FPROC)gl_wrap_get_pointer("glUniform1f");
	}
	ctx->glUniform1fProc(location, v0);
};
void gl_wrap_context_glUniform2f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1) {
	if(ctx->glUniform2fProc == NULL) {
		ctx->glUniform2fProc = (PFNGLUNIFORM2FPROC)gl_wrap_get_pointer("glUniform2f");
	}
	ctx->glUniform2fProc(location, v0, v1);
};
void gl_wrap_context_glUniform3f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
	if(ctx->glUniform3fProc == NULL) {
		ctx->glUniform3fProc = (PFNGLUNIFORM3FPROC)gl_wrap_get_pointer("glUniform3f");
	}
	ctx->glUniform3fProc(location, v0, v1, v2);
};
void gl_wrap_context_glUniform4f(gl_wrap_context* ctx, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
	if(ctx->glUniform4fProc == NULL) {
		ctx->glUniform4fProc = (PFNGLUNIFORM4FPROC)gl_wrap_get_pointer("glUniform4f");
	}
	ctx->glUniform4fProc(location, v0, v1, v2, v3);
};
void gl_wrap_context_glUniform1i(gl_wrap_context* ctx, GLint location, GLint v0) {
	if(ctx->glUniform1iProc == NULL) {
		ctx->glUniform1iProc = (PFNGLUNIFORM1IPROC)gl_wrap_get_pointer("glUniform1i");
	}
	ctx->glUniform1iProc(location, v0);
};
void gl_wrap_context_glUniform2i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1) {
	if(ctx->glUniform2iProc == NULL) {
		ctx->glUniform2iProc = (PFNGLUNIFORM2IPROC)gl_wrap_get_pointer("glUniform2i");
	}
	ctx->glUniform2iProc(location, v0, v1);
};
void gl_wrap_context_glUniform3i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2) {
	if(ctx->glUniform3iProc == NULL) {
		ctx->glUniform3iProc = (PFNGLUNIFORM3IPROC)gl_wrap_get_pointer("glUniform3i");
	}
	ctx->glUniform3iProc(location, v0, v1, v2);
};
void gl_wrap_context_glUniform4i(gl_wrap_context* ctx, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
	if(ctx->glUniform4iProc == NULL) {
		ctx->glUniform4iProc = (PFNGLUNIFORM4IPROC)gl_wrap_get_pointer("glUniform4i");
	}
	ctx->glUniform4iProc(location, v0, v1, v2, v3);
};
void gl_wrap_context_glUniform1fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform1fvProc == NULL) {
		ctx->glUniform1fvProc = (PFNGLUNIFORM1FVPROC)gl_wrap_get_pointer("glUniform1fv");
	}
	ctx->glUniform1fvProc(location, count, value);
};
void gl_wrap_context_glUniform2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform2fvProc == NULL) {
		ctx->glUniform2fvProc = (PFNGLUNIFORM2FVPROC)gl_wrap_get_pointer("glUniform2fv");
	}
	ctx->glUniform2fvProc(location, count, value);
};
void gl_wrap_context_glUniform3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform3fvProc == NULL) {
		ctx->glUniform3fvProc = (PFNGLUNIFORM3FVPROC)gl_wrap_get_pointer("glUniform3fv");
	}
	ctx->glUniform3fvProc(location, count, value);
};
void gl_wrap_context_glUniform4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glUniform4fvProc == NULL) {
		ctx->glUniform4fvProc = (PFNGLUNIFORM4FVPROC)gl_wrap_get_pointer("glUniform4fv");
	}
	ctx->glUniform4fvProc(location, count, value);
};
void gl_wrap_context_glUniform1iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform1ivProc == NULL) {
		ctx->glUniform1ivProc = (PFNGLUNIFORM1IVPROC)gl_wrap_get_pointer("glUniform1iv");
	}
	ctx->glUniform1ivProc(location, count, value);
};
void gl_wrap_context_glUniform2iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform2ivProc == NULL) {
		ctx->glUniform2ivProc = (PFNGLUNIFORM2IVPROC)gl_wrap_get_pointer("glUniform2iv");
	}
	ctx->glUniform2ivProc(location, count, value);
};
void gl_wrap_context_glUniform3iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform3ivProc == NULL) {
		ctx->glUniform3ivProc = (PFNGLUNIFORM3IVPROC)gl_wrap_get_pointer("glUniform3iv");
	}
	ctx->glUniform3ivProc(location, count, value);
};
void gl_wrap_context_glUniform4iv(gl_wrap_context* ctx, GLint location, GLsizei count, GLint* value) {
	if(ctx->glUniform4ivProc == NULL) {
		ctx->glUniform4ivProc = (PFNGLUNIFORM4IVPROC)gl_wrap_get_pointer("glUniform4iv");
	}
	ctx->glUniform4ivProc(location, count, value);
};
void gl_wrap_context_glUniformMatrix2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix2fvProc == NULL) {
		ctx->glUniformMatrix2fvProc = (PFNGLUNIFORMMATRIX2FVPROC)gl_wrap_get_pointer("glUniformMatrix2fv");
	}
	ctx->glUniformMatrix2fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix3fvProc == NULL) {
		ctx->glUniformMatrix3fvProc = (PFNGLUNIFORMMATRIX3FVPROC)gl_wrap_get_pointer("glUniformMatrix3fv");
	}
	ctx->glUniformMatrix3fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix4fvProc == NULL) {
		ctx->glUniformMatrix4fvProc = (PFNGLUNIFORMMATRIX4FVPROC)gl_wrap_get_pointer("glUniformMatrix4fv");
	}
	ctx->glUniformMatrix4fvProc(location, count, transpose, value);
};
void gl_wrap_context_glValidateProgram(gl_wrap_context* ctx, GLuint program) {
	if(ctx->glValidateProgramProc == NULL) {
		ctx->glValidateProgramProc = (PFNGLVALIDATEPROGRAMPROC)gl_wrap_get_pointer("glValidateProgram");
	}
	ctx->glValidateProgramProc(program);
};
void gl_wrap_context_glVertexAttrib1d(gl_wrap_context* ctx, GLuint index, GLdouble x) {
	if(ctx->glVertexAttrib1dProc == NULL) {
		ctx->glVertexAttrib1dProc = (PFNGLVERTEXATTRIB1DPROC)gl_wrap_get_pointer("glVertexAttrib1d");
	}
	ctx->glVertexAttrib1dProc(index, x);
};
void gl_wrap_context_glVertexAttrib1dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttrib1dvProc == NULL) {
		ctx->glVertexAttrib1dvProc = (PFNGLVERTEXATTRIB1DVPROC)gl_wrap_get_pointer("glVertexAttrib1dv");
	}
	ctx->glVertexAttrib1dvProc(index, v);
};
void gl_wrap_context_glVertexAttrib1f(gl_wrap_context* ctx, GLuint index, GLfloat x) {
	if(ctx->glVertexAttrib1fProc == NULL) {
		ctx->glVertexAttrib1fProc = (PFNGLVERTEXATTRIB1FPROC)gl_wrap_get_pointer("glVertexAttrib1f");
	}
	ctx->glVertexAttrib1fProc(index, x);
};
void gl_wrap_context_glVertexAttrib1fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib1fvProc == NULL) {
		ctx->glVertexAttrib1fvProc = (PFNGLVERTEXATTRIB1FVPROC)gl_wrap_get_pointer("glVertexAttrib1fv");
	}
	ctx->glVertexAttrib1fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib1s(gl_wrap_context* ctx, GLuint index, GLshort x) {
	if(ctx->glVertexAttrib1sProc == NULL) {
		ctx->glVertexAttrib1sProc = (PFNGLVERTEXATTRIB1SPROC)gl_wrap_get_pointer("glVertexAttrib1s");
	}
	ctx->glVertexAttrib1sProc(index, x);
};
void gl_wrap_context_glVertexAttrib1sv(gl_wrap_context* ctx, GLuint index, GLshort* v) {
	if(ctx->glVertexAttrib1svProc == NULL) {
		ctx->glVertexAttrib1svProc = (PFNGLVERTEXATTRIB1SVPROC)gl_wrap_get_pointer("glVertexAttrib1sv");
	}
	ctx->glVertexAttrib1svProc(index, v);
};
void gl_wrap_context_glVertexAttrib2d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y) {
	if(ctx->glVertexAttrib2dProc == NULL) {
		ctx->glVertexAttrib2dProc = (PFNGLVERTEXATTRIB2DPROC)gl_wrap_get_pointer("glVertexAttrib2d");
	}
	ctx->glVertexAttrib2dProc(index, x, y);
};
void gl_wrap_context_glVertexAttrib2dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttrib2dvProc == NULL) {
		ctx->glVertexAttrib2dvProc = (PFNGLVERTEXATTRIB2DVPROC)gl_wrap_get_pointer("glVertexAttrib2dv");
	}
	ctx->glVertexAttrib2dvProc(index, v);
};
void gl_wrap_context_glVertexAttrib2f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y) {
	if(ctx->glVertexAttrib2fProc == NULL) {
		ctx->glVertexAttrib2fProc = (PFNGLVERTEXATTRIB2FPROC)gl_wrap_get_pointer("glVertexAttrib2f");
	}
	ctx->glVertexAttrib2fProc(index, x, y);
};
void gl_wrap_context_glVertexAttrib2fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib2fvProc == NULL) {
		ctx->glVertexAttrib2fvProc = (PFNGLVERTEXATTRIB2FVPROC)gl_wrap_get_pointer("glVertexAttrib2fv");
	}
	ctx->glVertexAttrib2fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib2s(gl_wrap_context* ctx, GLuint index, GLshort x, GLshort y) {
	if(ctx->glVertexAttrib2sProc == NULL) {
		ctx->glVertexAttrib2sProc = (PFNGLVERTEXATTRIB2SPROC)gl_wrap_get_pointer("glVertexAttrib2s");
	}
	ctx->glVertexAttrib2sProc(index, x, y);
};
void gl_wrap_context_glVertexAttrib2sv(gl_wrap_context* ctx, GLuint index, GLshort* v) {
	if(ctx->glVertexAttrib2svProc == NULL) {
		ctx->glVertexAttrib2svProc = (PFNGLVERTEXATTRIB2SVPROC)gl_wrap_get_pointer("glVertexAttrib2sv");
	}
	ctx->glVertexAttrib2svProc(index, v);
};
void gl_wrap_context_glVertexAttrib3d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glVertexAttrib3dProc == NULL) {
		ctx->glVertexAttrib3dProc = (PFNGLVERTEXATTRIB3DPROC)gl_wrap_get_pointer("glVertexAttrib3d");
	}
	ctx->glVertexAttrib3dProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttrib3dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttrib3dvProc == NULL) {
		ctx->glVertexAttrib3dvProc = (PFNGLVERTEXATTRIB3DVPROC)gl_wrap_get_pointer("glVertexAttrib3dv");
	}
	ctx->glVertexAttrib3dvProc(index, v);
};
void gl_wrap_context_glVertexAttrib3f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z) {
	if(ctx->glVertexAttrib3fProc == NULL) {
		ctx->glVertexAttrib3fProc = (PFNGLVERTEXATTRIB3FPROC)gl_wrap_get_pointer("glVertexAttrib3f");
	}
	ctx->glVertexAttrib3fProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttrib3fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib3fvProc == NULL) {
		ctx->glVertexAttrib3fvProc = (PFNGLVERTEXATTRIB3FVPROC)gl_wrap_get_pointer("glVertexAttrib3fv");
	}
	ctx->glVertexAttrib3fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib3s(gl_wrap_context* ctx, GLuint index, GLshort x, GLshort y, GLshort z) {
	if(ctx->glVertexAttrib3sProc == NULL) {
		ctx->glVertexAttrib3sProc = (PFNGLVERTEXATTRIB3SPROC)gl_wrap_get_pointer("glVertexAttrib3s");
	}
	ctx->glVertexAttrib3sProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttrib3sv(gl_wrap_context* ctx, GLuint index, GLshort* v) {
	if(ctx->glVertexAttrib3svProc == NULL) {
		ctx->glVertexAttrib3svProc = (PFNGLVERTEXATTRIB3SVPROC)gl_wrap_get_pointer("glVertexAttrib3sv");
	}
	ctx->glVertexAttrib3svProc(index, v);
};
void gl_wrap_context_glVertexAttrib4Nbv(gl_wrap_context* ctx, GLuint index, GLbyte* v) {
	if(ctx->glVertexAttrib4NbvProc == NULL) {
		ctx->glVertexAttrib4NbvProc = (PFNGLVERTEXATTRIB4NBVPROC)gl_wrap_get_pointer("glVertexAttrib4Nbv");
	}
	ctx->glVertexAttrib4NbvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4Niv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttrib4NivProc == NULL) {
		ctx->glVertexAttrib4NivProc = (PFNGLVERTEXATTRIB4NIVPROC)gl_wrap_get_pointer("glVertexAttrib4Niv");
	}
	ctx->glVertexAttrib4NivProc(index, v);
};
void gl_wrap_context_glVertexAttrib4Nsv(gl_wrap_context* ctx, GLuint index, GLshort* v) {
	if(ctx->glVertexAttrib4NsvProc == NULL) {
		ctx->glVertexAttrib4NsvProc = (PFNGLVERTEXATTRIB4NSVPROC)gl_wrap_get_pointer("glVertexAttrib4Nsv");
	}
	ctx->glVertexAttrib4NsvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4Nub(gl_wrap_context* ctx, GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
	if(ctx->glVertexAttrib4NubProc == NULL) {
		ctx->glVertexAttrib4NubProc = (PFNGLVERTEXATTRIB4NUBPROC)gl_wrap_get_pointer("glVertexAttrib4Nub");
	}
	ctx->glVertexAttrib4NubProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttrib4Nubv(gl_wrap_context* ctx, GLuint index, GLubyte* v) {
	if(ctx->glVertexAttrib4NubvProc == NULL) {
		ctx->glVertexAttrib4NubvProc = (PFNGLVERTEXATTRIB4NUBVPROC)gl_wrap_get_pointer("glVertexAttrib4Nubv");
	}
	ctx->glVertexAttrib4NubvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4Nuiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttrib4NuivProc == NULL) {
		ctx->glVertexAttrib4NuivProc = (PFNGLVERTEXATTRIB4NUIVPROC)gl_wrap_get_pointer("glVertexAttrib4Nuiv");
	}
	ctx->glVertexAttrib4NuivProc(index, v);
};
void gl_wrap_context_glVertexAttrib4Nusv(gl_wrap_context* ctx, GLuint index, GLushort* v) {
	if(ctx->glVertexAttrib4NusvProc == NULL) {
		ctx->glVertexAttrib4NusvProc = (PFNGLVERTEXATTRIB4NUSVPROC)gl_wrap_get_pointer("glVertexAttrib4Nusv");
	}
	ctx->glVertexAttrib4NusvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4bv(gl_wrap_context* ctx, GLuint index, GLbyte* v) {
	if(ctx->glVertexAttrib4bvProc == NULL) {
		ctx->glVertexAttrib4bvProc = (PFNGLVERTEXATTRIB4BVPROC)gl_wrap_get_pointer("glVertexAttrib4bv");
	}
	ctx->glVertexAttrib4bvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	if(ctx->glVertexAttrib4dProc == NULL) {
		ctx->glVertexAttrib4dProc = (PFNGLVERTEXATTRIB4DPROC)gl_wrap_get_pointer("glVertexAttrib4d");
	}
	ctx->glVertexAttrib4dProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttrib4dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttrib4dvProc == NULL) {
		ctx->glVertexAttrib4dvProc = (PFNGLVERTEXATTRIB4DVPROC)gl_wrap_get_pointer("glVertexAttrib4dv");
	}
	ctx->glVertexAttrib4dvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4f(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	if(ctx->glVertexAttrib4fProc == NULL) {
		ctx->glVertexAttrib4fProc = (PFNGLVERTEXATTRIB4FPROC)gl_wrap_get_pointer("glVertexAttrib4f");
	}
	ctx->glVertexAttrib4fProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttrib4fv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glVertexAttrib4fvProc == NULL) {
		ctx->glVertexAttrib4fvProc = (PFNGLVERTEXATTRIB4FVPROC)gl_wrap_get_pointer("glVertexAttrib4fv");
	}
	ctx->glVertexAttrib4fvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4iv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttrib4ivProc == NULL) {
		ctx->glVertexAttrib4ivProc = (PFNGLVERTEXATTRIB4IVPROC)gl_wrap_get_pointer("glVertexAttrib4iv");
	}
	ctx->glVertexAttrib4ivProc(index, v);
};
void gl_wrap_context_glVertexAttrib4s(gl_wrap_context* ctx, GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
	if(ctx->glVertexAttrib4sProc == NULL) {
		ctx->glVertexAttrib4sProc = (PFNGLVERTEXATTRIB4SPROC)gl_wrap_get_pointer("glVertexAttrib4s");
	}
	ctx->glVertexAttrib4sProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttrib4sv(gl_wrap_context* ctx, GLuint index, GLshort* v) {
	if(ctx->glVertexAttrib4svProc == NULL) {
		ctx->glVertexAttrib4svProc = (PFNGLVERTEXATTRIB4SVPROC)gl_wrap_get_pointer("glVertexAttrib4sv");
	}
	ctx->glVertexAttrib4svProc(index, v);
};
void gl_wrap_context_glVertexAttrib4ubv(gl_wrap_context* ctx, GLuint index, GLubyte* v) {
	if(ctx->glVertexAttrib4ubvProc == NULL) {
		ctx->glVertexAttrib4ubvProc = (PFNGLVERTEXATTRIB4UBVPROC)gl_wrap_get_pointer("glVertexAttrib4ubv");
	}
	ctx->glVertexAttrib4ubvProc(index, v);
};
void gl_wrap_context_glVertexAttrib4uiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttrib4uivProc == NULL) {
		ctx->glVertexAttrib4uivProc = (PFNGLVERTEXATTRIB4UIVPROC)gl_wrap_get_pointer("glVertexAttrib4uiv");
	}
	ctx->glVertexAttrib4uivProc(index, v);
};
void gl_wrap_context_glVertexAttrib4usv(gl_wrap_context* ctx, GLuint index, GLushort* v) {
	if(ctx->glVertexAttrib4usvProc == NULL) {
		ctx->glVertexAttrib4usvProc = (PFNGLVERTEXATTRIB4USVPROC)gl_wrap_get_pointer("glVertexAttrib4usv");
	}
	ctx->glVertexAttrib4usvProc(index, v);
};
void gl_wrap_context_glVertexAttribPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void* pointer) {
	if(ctx->glVertexAttribPointerProc == NULL) {
		ctx->glVertexAttribPointerProc = (PFNGLVERTEXATTRIBPOINTERPROC)gl_wrap_get_pointer("glVertexAttribPointer");
	}
	ctx->glVertexAttribPointerProc(index, size, type, normalized, stride, pointer);
};
void gl_wrap_context_glUniformMatrix2x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix2x3fvProc == NULL) {
		ctx->glUniformMatrix2x3fvProc = (PFNGLUNIFORMMATRIX2X3FVPROC)gl_wrap_get_pointer("glUniformMatrix2x3fv");
	}
	ctx->glUniformMatrix2x3fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix3x2fvProc == NULL) {
		ctx->glUniformMatrix3x2fvProc = (PFNGLUNIFORMMATRIX3X2FVPROC)gl_wrap_get_pointer("glUniformMatrix3x2fv");
	}
	ctx->glUniformMatrix3x2fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix2x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix2x4fvProc == NULL) {
		ctx->glUniformMatrix2x4fvProc = (PFNGLUNIFORMMATRIX2X4FVPROC)gl_wrap_get_pointer("glUniformMatrix2x4fv");
	}
	ctx->glUniformMatrix2x4fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4x2fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix4x2fvProc == NULL) {
		ctx->glUniformMatrix4x2fvProc = (PFNGLUNIFORMMATRIX4X2FVPROC)gl_wrap_get_pointer("glUniformMatrix4x2fv");
	}
	ctx->glUniformMatrix4x2fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3x4fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix3x4fvProc == NULL) {
		ctx->glUniformMatrix3x4fvProc = (PFNGLUNIFORMMATRIX3X4FVPROC)gl_wrap_get_pointer("glUniformMatrix3x4fv");
	}
	ctx->glUniformMatrix3x4fvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4x3fv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glUniformMatrix4x3fvProc == NULL) {
		ctx->glUniformMatrix4x3fvProc = (PFNGLUNIFORMMATRIX4X3FVPROC)gl_wrap_get_pointer("glUniformMatrix4x3fv");
	}
	ctx->glUniformMatrix4x3fvProc(location, count, transpose, value);
};
void gl_wrap_context_glColorMaski(gl_wrap_context* ctx, GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
	if(ctx->glColorMaskiProc == NULL) {
		ctx->glColorMaskiProc = (PFNGLCOLORMASKIPROC)gl_wrap_get_pointer("glColorMaski");
	}
	ctx->glColorMaskiProc(index, r, g, b, a);
};
void gl_wrap_context_glGetBooleani_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLboolean* data) {
	if(ctx->glGetBooleani_vProc == NULL) {
		ctx->glGetBooleani_vProc = (PFNGLGETBOOLEANI_VPROC)gl_wrap_get_pointer("glGetBooleani_v");
	}
	ctx->glGetBooleani_vProc(target, index, data);
};
void gl_wrap_context_glGetIntegeri_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint* data) {
	if(ctx->glGetIntegeri_vProc == NULL) {
		ctx->glGetIntegeri_vProc = (PFNGLGETINTEGERI_VPROC)gl_wrap_get_pointer("glGetIntegeri_v");
	}
	ctx->glGetIntegeri_vProc(target, index, data);
};
void gl_wrap_context_glEnablei(gl_wrap_context* ctx, GLenum target, GLuint index) {
	if(ctx->glEnableiProc == NULL) {
		ctx->glEnableiProc = (PFNGLENABLEIPROC)gl_wrap_get_pointer("glEnablei");
	}
	ctx->glEnableiProc(target, index);
};
void gl_wrap_context_glDisablei(gl_wrap_context* ctx, GLenum target, GLuint index) {
	if(ctx->glDisableiProc == NULL) {
		ctx->glDisableiProc = (PFNGLDISABLEIPROC)gl_wrap_get_pointer("glDisablei");
	}
	ctx->glDisableiProc(target, index);
};
GLboolean gl_wrap_context_glIsEnabledi(gl_wrap_context* ctx, GLenum target, GLuint index) {
	if(ctx->glIsEnablediProc == NULL) {
		ctx->glIsEnablediProc = (PFNGLISENABLEDIPROC)gl_wrap_get_pointer("glIsEnabledi");
	}
	return ctx->glIsEnablediProc(target, index);
};
void gl_wrap_context_glBeginTransformFeedback(gl_wrap_context* ctx, GLenum primitiveMode) {
	if(ctx->glBeginTransformFeedbackProc == NULL) {
		ctx->glBeginTransformFeedbackProc = (PFNGLBEGINTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glBeginTransformFeedback");
	}
	ctx->glBeginTransformFeedbackProc(primitiveMode);
};
void gl_wrap_context_glEndTransformFeedback(gl_wrap_context* ctx) {
	if(ctx->glEndTransformFeedbackProc == NULL) {
		ctx->glEndTransformFeedbackProc = (PFNGLENDTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glEndTransformFeedback");
	}
	ctx->glEndTransformFeedbackProc();
};
void gl_wrap_context_glBindBufferRange(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
	if(ctx->glBindBufferRangeProc == NULL) {
		ctx->glBindBufferRangeProc = (PFNGLBINDBUFFERRANGEPROC)gl_wrap_get_pointer("glBindBufferRange");
	}
	ctx->glBindBufferRangeProc(target, index, buffer, offset, size);
};
void gl_wrap_context_glBindBufferBase(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint buffer) {
	if(ctx->glBindBufferBaseProc == NULL) {
		ctx->glBindBufferBaseProc = (PFNGLBINDBUFFERBASEPROC)gl_wrap_get_pointer("glBindBufferBase");
	}
	ctx->glBindBufferBaseProc(target, index, buffer);
};
void gl_wrap_context_glTransformFeedbackVaryings(gl_wrap_context* ctx, GLuint program, GLsizei count, GLchar** varyings, GLenum bufferMode) {
	if(ctx->glTransformFeedbackVaryingsProc == NULL) {
		ctx->glTransformFeedbackVaryingsProc = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)gl_wrap_get_pointer("glTransformFeedbackVaryings");
	}
	ctx->glTransformFeedbackVaryingsProc(program, count, varyings, bufferMode);
};
void gl_wrap_context_glGetTransformFeedbackVarying(gl_wrap_context* ctx, GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) {
	if(ctx->glGetTransformFeedbackVaryingProc == NULL) {
		ctx->glGetTransformFeedbackVaryingProc = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)gl_wrap_get_pointer("glGetTransformFeedbackVarying");
	}
	ctx->glGetTransformFeedbackVaryingProc(program, index, bufSize, length, size, type, name);
};
void gl_wrap_context_glClampColor(gl_wrap_context* ctx, GLenum target, GLenum clamp) {
	if(ctx->glClampColorProc == NULL) {
		ctx->glClampColorProc = (PFNGLCLAMPCOLORPROC)gl_wrap_get_pointer("glClampColor");
	}
	ctx->glClampColorProc(target, clamp);
};
void gl_wrap_context_glBeginConditionalRender(gl_wrap_context* ctx, GLuint id, GLenum mode) {
	if(ctx->glBeginConditionalRenderProc == NULL) {
		ctx->glBeginConditionalRenderProc = (PFNGLBEGINCONDITIONALRENDERPROC)gl_wrap_get_pointer("glBeginConditionalRender");
	}
	ctx->glBeginConditionalRenderProc(id, mode);
};
void gl_wrap_context_glEndConditionalRender(gl_wrap_context* ctx) {
	if(ctx->glEndConditionalRenderProc == NULL) {
		ctx->glEndConditionalRenderProc = (PFNGLENDCONDITIONALRENDERPROC)gl_wrap_get_pointer("glEndConditionalRender");
	}
	ctx->glEndConditionalRenderProc();
};
void gl_wrap_context_glVertexAttribIPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glVertexAttribIPointerProc == NULL) {
		ctx->glVertexAttribIPointerProc = (PFNGLVERTEXATTRIBIPOINTERPROC)gl_wrap_get_pointer("glVertexAttribIPointer");
	}
	ctx->glVertexAttribIPointerProc(index, size, type, stride, pointer);
};
void gl_wrap_context_glGetVertexAttribIiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLint* params) {
	if(ctx->glGetVertexAttribIivProc == NULL) {
		ctx->glGetVertexAttribIivProc = (PFNGLGETVERTEXATTRIBIIVPROC)gl_wrap_get_pointer("glGetVertexAttribIiv");
	}
	ctx->glGetVertexAttribIivProc(index, pname, params);
};
void gl_wrap_context_glGetVertexAttribIuiv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLuint* params) {
	if(ctx->glGetVertexAttribIuivProc == NULL) {
		ctx->glGetVertexAttribIuivProc = (PFNGLGETVERTEXATTRIBIUIVPROC)gl_wrap_get_pointer("glGetVertexAttribIuiv");
	}
	ctx->glGetVertexAttribIuivProc(index, pname, params);
};
void gl_wrap_context_glVertexAttribI1i(gl_wrap_context* ctx, GLuint index, GLint x) {
	if(ctx->glVertexAttribI1iProc == NULL) {
		ctx->glVertexAttribI1iProc = (PFNGLVERTEXATTRIBI1IPROC)gl_wrap_get_pointer("glVertexAttribI1i");
	}
	ctx->glVertexAttribI1iProc(index, x);
};
void gl_wrap_context_glVertexAttribI2i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y) {
	if(ctx->glVertexAttribI2iProc == NULL) {
		ctx->glVertexAttribI2iProc = (PFNGLVERTEXATTRIBI2IPROC)gl_wrap_get_pointer("glVertexAttribI2i");
	}
	ctx->glVertexAttribI2iProc(index, x, y);
};
void gl_wrap_context_glVertexAttribI3i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y, GLint z) {
	if(ctx->glVertexAttribI3iProc == NULL) {
		ctx->glVertexAttribI3iProc = (PFNGLVERTEXATTRIBI3IPROC)gl_wrap_get_pointer("glVertexAttribI3i");
	}
	ctx->glVertexAttribI3iProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttribI4i(gl_wrap_context* ctx, GLuint index, GLint x, GLint y, GLint z, GLint w) {
	if(ctx->glVertexAttribI4iProc == NULL) {
		ctx->glVertexAttribI4iProc = (PFNGLVERTEXATTRIBI4IPROC)gl_wrap_get_pointer("glVertexAttribI4i");
	}
	ctx->glVertexAttribI4iProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttribI1ui(gl_wrap_context* ctx, GLuint index, GLuint x) {
	if(ctx->glVertexAttribI1uiProc == NULL) {
		ctx->glVertexAttribI1uiProc = (PFNGLVERTEXATTRIBI1UIPROC)gl_wrap_get_pointer("glVertexAttribI1ui");
	}
	ctx->glVertexAttribI1uiProc(index, x);
};
void gl_wrap_context_glVertexAttribI2ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y) {
	if(ctx->glVertexAttribI2uiProc == NULL) {
		ctx->glVertexAttribI2uiProc = (PFNGLVERTEXATTRIBI2UIPROC)gl_wrap_get_pointer("glVertexAttribI2ui");
	}
	ctx->glVertexAttribI2uiProc(index, x, y);
};
void gl_wrap_context_glVertexAttribI3ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y, GLuint z) {
	if(ctx->glVertexAttribI3uiProc == NULL) {
		ctx->glVertexAttribI3uiProc = (PFNGLVERTEXATTRIBI3UIPROC)gl_wrap_get_pointer("glVertexAttribI3ui");
	}
	ctx->glVertexAttribI3uiProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttribI4ui(gl_wrap_context* ctx, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
	if(ctx->glVertexAttribI4uiProc == NULL) {
		ctx->glVertexAttribI4uiProc = (PFNGLVERTEXATTRIBI4UIPROC)gl_wrap_get_pointer("glVertexAttribI4ui");
	}
	ctx->glVertexAttribI4uiProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttribI1iv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttribI1ivProc == NULL) {
		ctx->glVertexAttribI1ivProc = (PFNGLVERTEXATTRIBI1IVPROC)gl_wrap_get_pointer("glVertexAttribI1iv");
	}
	ctx->glVertexAttribI1ivProc(index, v);
};
void gl_wrap_context_glVertexAttribI2iv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttribI2ivProc == NULL) {
		ctx->glVertexAttribI2ivProc = (PFNGLVERTEXATTRIBI2IVPROC)gl_wrap_get_pointer("glVertexAttribI2iv");
	}
	ctx->glVertexAttribI2ivProc(index, v);
};
void gl_wrap_context_glVertexAttribI3iv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttribI3ivProc == NULL) {
		ctx->glVertexAttribI3ivProc = (PFNGLVERTEXATTRIBI3IVPROC)gl_wrap_get_pointer("glVertexAttribI3iv");
	}
	ctx->glVertexAttribI3ivProc(index, v);
};
void gl_wrap_context_glVertexAttribI4iv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glVertexAttribI4ivProc == NULL) {
		ctx->glVertexAttribI4ivProc = (PFNGLVERTEXATTRIBI4IVPROC)gl_wrap_get_pointer("glVertexAttribI4iv");
	}
	ctx->glVertexAttribI4ivProc(index, v);
};
void gl_wrap_context_glVertexAttribI1uiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttribI1uivProc == NULL) {
		ctx->glVertexAttribI1uivProc = (PFNGLVERTEXATTRIBI1UIVPROC)gl_wrap_get_pointer("glVertexAttribI1uiv");
	}
	ctx->glVertexAttribI1uivProc(index, v);
};
void gl_wrap_context_glVertexAttribI2uiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttribI2uivProc == NULL) {
		ctx->glVertexAttribI2uivProc = (PFNGLVERTEXATTRIBI2UIVPROC)gl_wrap_get_pointer("glVertexAttribI2uiv");
	}
	ctx->glVertexAttribI2uivProc(index, v);
};
void gl_wrap_context_glVertexAttribI3uiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttribI3uivProc == NULL) {
		ctx->glVertexAttribI3uivProc = (PFNGLVERTEXATTRIBI3UIVPROC)gl_wrap_get_pointer("glVertexAttribI3uiv");
	}
	ctx->glVertexAttribI3uivProc(index, v);
};
void gl_wrap_context_glVertexAttribI4uiv(gl_wrap_context* ctx, GLuint index, GLuint* v) {
	if(ctx->glVertexAttribI4uivProc == NULL) {
		ctx->glVertexAttribI4uivProc = (PFNGLVERTEXATTRIBI4UIVPROC)gl_wrap_get_pointer("glVertexAttribI4uiv");
	}
	ctx->glVertexAttribI4uivProc(index, v);
};
void gl_wrap_context_glVertexAttribI4bv(gl_wrap_context* ctx, GLuint index, GLbyte* v) {
	if(ctx->glVertexAttribI4bvProc == NULL) {
		ctx->glVertexAttribI4bvProc = (PFNGLVERTEXATTRIBI4BVPROC)gl_wrap_get_pointer("glVertexAttribI4bv");
	}
	ctx->glVertexAttribI4bvProc(index, v);
};
void gl_wrap_context_glVertexAttribI4sv(gl_wrap_context* ctx, GLuint index, GLshort* v) {
	if(ctx->glVertexAttribI4svProc == NULL) {
		ctx->glVertexAttribI4svProc = (PFNGLVERTEXATTRIBI4SVPROC)gl_wrap_get_pointer("glVertexAttribI4sv");
	}
	ctx->glVertexAttribI4svProc(index, v);
};
void gl_wrap_context_glVertexAttribI4ubv(gl_wrap_context* ctx, GLuint index, GLubyte* v) {
	if(ctx->glVertexAttribI4ubvProc == NULL) {
		ctx->glVertexAttribI4ubvProc = (PFNGLVERTEXATTRIBI4UBVPROC)gl_wrap_get_pointer("glVertexAttribI4ubv");
	}
	ctx->glVertexAttribI4ubvProc(index, v);
};
void gl_wrap_context_glVertexAttribI4usv(gl_wrap_context* ctx, GLuint index, GLushort* v) {
	if(ctx->glVertexAttribI4usvProc == NULL) {
		ctx->glVertexAttribI4usvProc = (PFNGLVERTEXATTRIBI4USVPROC)gl_wrap_get_pointer("glVertexAttribI4usv");
	}
	ctx->glVertexAttribI4usvProc(index, v);
};
void gl_wrap_context_glGetUniformuiv(gl_wrap_context* ctx, GLuint program, GLint location, GLuint* params) {
	if(ctx->glGetUniformuivProc == NULL) {
		ctx->glGetUniformuivProc = (PFNGLGETUNIFORMUIVPROC)gl_wrap_get_pointer("glGetUniformuiv");
	}
	ctx->glGetUniformuivProc(program, location, params);
};
void gl_wrap_context_glBindFragDataLocation(gl_wrap_context* ctx, GLuint program, GLuint color, GLchar* name) {
	if(ctx->glBindFragDataLocationProc == NULL) {
		ctx->glBindFragDataLocationProc = (PFNGLBINDFRAGDATALOCATIONPROC)gl_wrap_get_pointer("glBindFragDataLocation");
	}
	ctx->glBindFragDataLocationProc(program, color, name);
};
GLint gl_wrap_context_glGetFragDataLocation(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetFragDataLocationProc == NULL) {
		ctx->glGetFragDataLocationProc = (PFNGLGETFRAGDATALOCATIONPROC)gl_wrap_get_pointer("glGetFragDataLocation");
	}
	return ctx->glGetFragDataLocationProc(program, name);
};
void gl_wrap_context_glUniform1ui(gl_wrap_context* ctx, GLint location, GLuint v0) {
	if(ctx->glUniform1uiProc == NULL) {
		ctx->glUniform1uiProc = (PFNGLUNIFORM1UIPROC)gl_wrap_get_pointer("glUniform1ui");
	}
	ctx->glUniform1uiProc(location, v0);
};
void gl_wrap_context_glUniform2ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1) {
	if(ctx->glUniform2uiProc == NULL) {
		ctx->glUniform2uiProc = (PFNGLUNIFORM2UIPROC)gl_wrap_get_pointer("glUniform2ui");
	}
	ctx->glUniform2uiProc(location, v0, v1);
};
void gl_wrap_context_glUniform3ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2) {
	if(ctx->glUniform3uiProc == NULL) {
		ctx->glUniform3uiProc = (PFNGLUNIFORM3UIPROC)gl_wrap_get_pointer("glUniform3ui");
	}
	ctx->glUniform3uiProc(location, v0, v1, v2);
};
void gl_wrap_context_glUniform4ui(gl_wrap_context* ctx, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
	if(ctx->glUniform4uiProc == NULL) {
		ctx->glUniform4uiProc = (PFNGLUNIFORM4UIPROC)gl_wrap_get_pointer("glUniform4ui");
	}
	ctx->glUniform4uiProc(location, v0, v1, v2, v3);
};
void gl_wrap_context_glUniform1uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform1uivProc == NULL) {
		ctx->glUniform1uivProc = (PFNGLUNIFORM1UIVPROC)gl_wrap_get_pointer("glUniform1uiv");
	}
	ctx->glUniform1uivProc(location, count, value);
};
void gl_wrap_context_glUniform2uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform2uivProc == NULL) {
		ctx->glUniform2uivProc = (PFNGLUNIFORM2UIVPROC)gl_wrap_get_pointer("glUniform2uiv");
	}
	ctx->glUniform2uivProc(location, count, value);
};
void gl_wrap_context_glUniform3uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform3uivProc == NULL) {
		ctx->glUniform3uivProc = (PFNGLUNIFORM3UIVPROC)gl_wrap_get_pointer("glUniform3uiv");
	}
	ctx->glUniform3uivProc(location, count, value);
};
void gl_wrap_context_glUniform4uiv(gl_wrap_context* ctx, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glUniform4uivProc == NULL) {
		ctx->glUniform4uivProc = (PFNGLUNIFORM4UIVPROC)gl_wrap_get_pointer("glUniform4uiv");
	}
	ctx->glUniform4uivProc(location, count, value);
};
void gl_wrap_context_glTexParameterIiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glTexParameterIivProc == NULL) {
		ctx->glTexParameterIivProc = (PFNGLTEXPARAMETERIIVPROC)gl_wrap_get_pointer("glTexParameterIiv");
	}
	ctx->glTexParameterIivProc(target, pname, params);
};
void gl_wrap_context_glTexParameterIuiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLuint* params) {
	if(ctx->glTexParameterIuivProc == NULL) {
		ctx->glTexParameterIuivProc = (PFNGLTEXPARAMETERIUIVPROC)gl_wrap_get_pointer("glTexParameterIuiv");
	}
	ctx->glTexParameterIuivProc(target, pname, params);
};
void gl_wrap_context_glGetTexParameterIiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetTexParameterIivProc == NULL) {
		ctx->glGetTexParameterIivProc = (PFNGLGETTEXPARAMETERIIVPROC)gl_wrap_get_pointer("glGetTexParameterIiv");
	}
	ctx->glGetTexParameterIivProc(target, pname, params);
};
void gl_wrap_context_glGetTexParameterIuiv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLuint* params) {
	if(ctx->glGetTexParameterIuivProc == NULL) {
		ctx->glGetTexParameterIuivProc = (PFNGLGETTEXPARAMETERIUIVPROC)gl_wrap_get_pointer("glGetTexParameterIuiv");
	}
	ctx->glGetTexParameterIuivProc(target, pname, params);
};
void gl_wrap_context_glClearBufferiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLint* value) {
	if(ctx->glClearBufferivProc == NULL) {
		ctx->glClearBufferivProc = (PFNGLCLEARBUFFERIVPROC)gl_wrap_get_pointer("glClearBufferiv");
	}
	ctx->glClearBufferivProc(buffer, drawbuffer, value);
};
void gl_wrap_context_glClearBufferuiv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLuint* value) {
	if(ctx->glClearBufferuivProc == NULL) {
		ctx->glClearBufferuivProc = (PFNGLCLEARBUFFERUIVPROC)gl_wrap_get_pointer("glClearBufferuiv");
	}
	ctx->glClearBufferuivProc(buffer, drawbuffer, value);
};
void gl_wrap_context_glClearBufferfv(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat* value) {
	if(ctx->glClearBufferfvProc == NULL) {
		ctx->glClearBufferfvProc = (PFNGLCLEARBUFFERFVPROC)gl_wrap_get_pointer("glClearBufferfv");
	}
	ctx->glClearBufferfvProc(buffer, drawbuffer, value);
};
void gl_wrap_context_glClearBufferfi(gl_wrap_context* ctx, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
	if(ctx->glClearBufferfiProc == NULL) {
		ctx->glClearBufferfiProc = (PFNGLCLEARBUFFERFIPROC)gl_wrap_get_pointer("glClearBufferfi");
	}
	ctx->glClearBufferfiProc(buffer, drawbuffer, depth, stencil);
};
GLubyte* gl_wrap_context_glGetStringi(gl_wrap_context* ctx, GLenum name, GLuint index) {
	if(ctx->glGetStringiProc == NULL) {
		ctx->glGetStringiProc = (PFNGLGETSTRINGIPROC)gl_wrap_get_pointer("glGetStringi");
	}
	return ctx->glGetStringiProc(name, index);
};
GLboolean gl_wrap_context_glIsRenderbuffer(gl_wrap_context* ctx, GLuint renderbuffer) {
	if(ctx->glIsRenderbufferProc == NULL) {
		ctx->glIsRenderbufferProc = (PFNGLISRENDERBUFFERPROC)gl_wrap_get_pointer("glIsRenderbuffer");
	}
	return ctx->glIsRenderbufferProc(renderbuffer);
};
void gl_wrap_context_glBindRenderbuffer(gl_wrap_context* ctx, GLenum target, GLuint renderbuffer) {
	if(ctx->glBindRenderbufferProc == NULL) {
		ctx->glBindRenderbufferProc = (PFNGLBINDRENDERBUFFERPROC)gl_wrap_get_pointer("glBindRenderbuffer");
	}
	ctx->glBindRenderbufferProc(target, renderbuffer);
};
void gl_wrap_context_glDeleteRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers) {
	if(ctx->glDeleteRenderbuffersProc == NULL) {
		ctx->glDeleteRenderbuffersProc = (PFNGLDELETERENDERBUFFERSPROC)gl_wrap_get_pointer("glDeleteRenderbuffers");
	}
	ctx->glDeleteRenderbuffersProc(n, renderbuffers);
};
void gl_wrap_context_glGenRenderbuffers(gl_wrap_context* ctx, GLsizei n, GLuint* renderbuffers) {
	if(ctx->glGenRenderbuffersProc == NULL) {
		ctx->glGenRenderbuffersProc = (PFNGLGENRENDERBUFFERSPROC)gl_wrap_get_pointer("glGenRenderbuffers");
	}
	ctx->glGenRenderbuffersProc(n, renderbuffers);
};
void gl_wrap_context_glRenderbufferStorage(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
	if(ctx->glRenderbufferStorageProc == NULL) {
		ctx->glRenderbufferStorageProc = (PFNGLRENDERBUFFERSTORAGEPROC)gl_wrap_get_pointer("glRenderbufferStorage");
	}
	ctx->glRenderbufferStorageProc(target, internalformat, width, height);
};
void gl_wrap_context_glGetRenderbufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetRenderbufferParameterivProc == NULL) {
		ctx->glGetRenderbufferParameterivProc = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)gl_wrap_get_pointer("glGetRenderbufferParameteriv");
	}
	ctx->glGetRenderbufferParameterivProc(target, pname, params);
};
GLboolean gl_wrap_context_glIsFramebuffer(gl_wrap_context* ctx, GLuint framebuffer) {
	if(ctx->glIsFramebufferProc == NULL) {
		ctx->glIsFramebufferProc = (PFNGLISFRAMEBUFFERPROC)gl_wrap_get_pointer("glIsFramebuffer");
	}
	return ctx->glIsFramebufferProc(framebuffer);
};
void gl_wrap_context_glBindFramebuffer(gl_wrap_context* ctx, GLenum target, GLuint framebuffer) {
	if(ctx->glBindFramebufferProc == NULL) {
		ctx->glBindFramebufferProc = (PFNGLBINDFRAMEBUFFERPROC)gl_wrap_get_pointer("glBindFramebuffer");
	}
	ctx->glBindFramebufferProc(target, framebuffer);
};
void gl_wrap_context_glDeleteFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers) {
	if(ctx->glDeleteFramebuffersProc == NULL) {
		ctx->glDeleteFramebuffersProc = (PFNGLDELETEFRAMEBUFFERSPROC)gl_wrap_get_pointer("glDeleteFramebuffers");
	}
	ctx->glDeleteFramebuffersProc(n, framebuffers);
};
void gl_wrap_context_glGenFramebuffers(gl_wrap_context* ctx, GLsizei n, GLuint* framebuffers) {
	if(ctx->glGenFramebuffersProc == NULL) {
		ctx->glGenFramebuffersProc = (PFNGLGENFRAMEBUFFERSPROC)gl_wrap_get_pointer("glGenFramebuffers");
	}
	ctx->glGenFramebuffersProc(n, framebuffers);
};
GLenum gl_wrap_context_glCheckFramebufferStatus(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glCheckFramebufferStatusProc == NULL) {
		ctx->glCheckFramebufferStatusProc = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)gl_wrap_get_pointer("glCheckFramebufferStatus");
	}
	return ctx->glCheckFramebufferStatusProc(target);
};
void gl_wrap_context_glFramebufferTexture1D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
	if(ctx->glFramebufferTexture1DProc == NULL) {
		ctx->glFramebufferTexture1DProc = (PFNGLFRAMEBUFFERTEXTURE1DPROC)gl_wrap_get_pointer("glFramebufferTexture1D");
	}
	ctx->glFramebufferTexture1DProc(target, attachment, textarget, texture, level);
};
void gl_wrap_context_glFramebufferTexture2D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
	if(ctx->glFramebufferTexture2DProc == NULL) {
		ctx->glFramebufferTexture2DProc = (PFNGLFRAMEBUFFERTEXTURE2DPROC)gl_wrap_get_pointer("glFramebufferTexture2D");
	}
	ctx->glFramebufferTexture2DProc(target, attachment, textarget, texture, level);
};
void gl_wrap_context_glFramebufferTexture3D(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
	if(ctx->glFramebufferTexture3DProc == NULL) {
		ctx->glFramebufferTexture3DProc = (PFNGLFRAMEBUFFERTEXTURE3DPROC)gl_wrap_get_pointer("glFramebufferTexture3D");
	}
	ctx->glFramebufferTexture3DProc(target, attachment, textarget, texture, level, zoffset);
};
void gl_wrap_context_glFramebufferRenderbuffer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
	if(ctx->glFramebufferRenderbufferProc == NULL) {
		ctx->glFramebufferRenderbufferProc = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)gl_wrap_get_pointer("glFramebufferRenderbuffer");
	}
	ctx->glFramebufferRenderbufferProc(target, attachment, renderbuffertarget, renderbuffer);
};
void gl_wrap_context_glGetFramebufferAttachmentParameteriv(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLenum pname, GLint* params) {
	if(ctx->glGetFramebufferAttachmentParameterivProc == NULL) {
		ctx->glGetFramebufferAttachmentParameterivProc = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)gl_wrap_get_pointer("glGetFramebufferAttachmentParameteriv");
	}
	ctx->glGetFramebufferAttachmentParameterivProc(target, attachment, pname, params);
};
void gl_wrap_context_glGenerateMipmap(gl_wrap_context* ctx, GLenum target) {
	if(ctx->glGenerateMipmapProc == NULL) {
		ctx->glGenerateMipmapProc = (PFNGLGENERATEMIPMAPPROC)gl_wrap_get_pointer("glGenerateMipmap");
	}
	ctx->glGenerateMipmapProc(target);
};
void gl_wrap_context_glBlitFramebuffer(gl_wrap_context* ctx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
	if(ctx->glBlitFramebufferProc == NULL) {
		ctx->glBlitFramebufferProc = (PFNGLBLITFRAMEBUFFERPROC)gl_wrap_get_pointer("glBlitFramebuffer");
	}
	ctx->glBlitFramebufferProc(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
};
void gl_wrap_context_glRenderbufferStorageMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
	if(ctx->glRenderbufferStorageMultisampleProc == NULL) {
		ctx->glRenderbufferStorageMultisampleProc = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)gl_wrap_get_pointer("glRenderbufferStorageMultisample");
	}
	ctx->glRenderbufferStorageMultisampleProc(target, samples, internalformat, width, height);
};
void gl_wrap_context_glFramebufferTextureLayer(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
	if(ctx->glFramebufferTextureLayerProc == NULL) {
		ctx->glFramebufferTextureLayerProc = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)gl_wrap_get_pointer("glFramebufferTextureLayer");
	}
	ctx->glFramebufferTextureLayerProc(target, attachment, texture, level, layer);
};
void gl_wrap_context_glMapBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
	if(ctx->glMapBufferRangeProc == NULL) {
		ctx->glMapBufferRangeProc = (PFNGLMAPBUFFERRANGEPROC)gl_wrap_get_pointer("glMapBufferRange");
	}
	ctx->glMapBufferRangeProc(target, offset, length, access);
};
void gl_wrap_context_glFlushMappedBufferRange(gl_wrap_context* ctx, GLenum target, GLintptr offset, GLsizeiptr length) {
	if(ctx->glFlushMappedBufferRangeProc == NULL) {
		ctx->glFlushMappedBufferRangeProc = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)gl_wrap_get_pointer("glFlushMappedBufferRange");
	}
	ctx->glFlushMappedBufferRangeProc(target, offset, length);
};
void gl_wrap_context_glBindVertexArray(gl_wrap_context* ctx, GLuint array) {
	if(ctx->glBindVertexArrayProc == NULL) {
		ctx->glBindVertexArrayProc = (PFNGLBINDVERTEXARRAYPROC)gl_wrap_get_pointer("glBindVertexArray");
	}
	ctx->glBindVertexArrayProc(array);
};
void gl_wrap_context_glDeleteVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays) {
	if(ctx->glDeleteVertexArraysProc == NULL) {
		ctx->glDeleteVertexArraysProc = (PFNGLDELETEVERTEXARRAYSPROC)gl_wrap_get_pointer("glDeleteVertexArrays");
	}
	ctx->glDeleteVertexArraysProc(n, arrays);
};
void gl_wrap_context_glGenVertexArrays(gl_wrap_context* ctx, GLsizei n, GLuint* arrays) {
	if(ctx->glGenVertexArraysProc == NULL) {
		ctx->glGenVertexArraysProc = (PFNGLGENVERTEXARRAYSPROC)gl_wrap_get_pointer("glGenVertexArrays");
	}
	ctx->glGenVertexArraysProc(n, arrays);
};
GLboolean gl_wrap_context_glIsVertexArray(gl_wrap_context* ctx, GLuint array) {
	if(ctx->glIsVertexArrayProc == NULL) {
		ctx->glIsVertexArrayProc = (PFNGLISVERTEXARRAYPROC)gl_wrap_get_pointer("glIsVertexArray");
	}
	return ctx->glIsVertexArrayProc(array);
};
void gl_wrap_context_glDrawArraysInstanced(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
	if(ctx->glDrawArraysInstancedProc == NULL) {
		ctx->glDrawArraysInstancedProc = (PFNGLDRAWARRAYSINSTANCEDPROC)gl_wrap_get_pointer("glDrawArraysInstanced");
	}
	ctx->glDrawArraysInstancedProc(mode, first, count, instancecount);
};
void gl_wrap_context_glDrawElementsInstanced(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount) {
	if(ctx->glDrawElementsInstancedProc == NULL) {
		ctx->glDrawElementsInstancedProc = (PFNGLDRAWELEMENTSINSTANCEDPROC)gl_wrap_get_pointer("glDrawElementsInstanced");
	}
	ctx->glDrawElementsInstancedProc(mode, count, type, indices, instancecount);
};
void gl_wrap_context_glTexBuffer(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLuint buffer) {
	if(ctx->glTexBufferProc == NULL) {
		ctx->glTexBufferProc = (PFNGLTEXBUFFERPROC)gl_wrap_get_pointer("glTexBuffer");
	}
	ctx->glTexBufferProc(target, internalformat, buffer);
};
void gl_wrap_context_glPrimitiveRestartIndex(gl_wrap_context* ctx, GLuint index) {
	if(ctx->glPrimitiveRestartIndexProc == NULL) {
		ctx->glPrimitiveRestartIndexProc = (PFNGLPRIMITIVERESTARTINDEXPROC)gl_wrap_get_pointer("glPrimitiveRestartIndex");
	}
	ctx->glPrimitiveRestartIndexProc(index);
};
void gl_wrap_context_glCopyBufferSubData(gl_wrap_context* ctx, GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
	if(ctx->glCopyBufferSubDataProc == NULL) {
		ctx->glCopyBufferSubDataProc = (PFNGLCOPYBUFFERSUBDATAPROC)gl_wrap_get_pointer("glCopyBufferSubData");
	}
	ctx->glCopyBufferSubDataProc(readTarget, writeTarget, readOffset, writeOffset, size);
};
void gl_wrap_context_glGetUniformIndices(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLchar** uniformNames, GLuint* uniformIndices) {
	if(ctx->glGetUniformIndicesProc == NULL) {
		ctx->glGetUniformIndicesProc = (PFNGLGETUNIFORMINDICESPROC)gl_wrap_get_pointer("glGetUniformIndices");
	}
	ctx->glGetUniformIndicesProc(program, uniformCount, uniformNames, uniformIndices);
};
void gl_wrap_context_glGetActiveUniformsiv(gl_wrap_context* ctx, GLuint program, GLsizei uniformCount, GLuint* uniformIndices, GLenum pname, GLint* params) {
	if(ctx->glGetActiveUniformsivProc == NULL) {
		ctx->glGetActiveUniformsivProc = (PFNGLGETACTIVEUNIFORMSIVPROC)gl_wrap_get_pointer("glGetActiveUniformsiv");
	}
	ctx->glGetActiveUniformsivProc(program, uniformCount, uniformIndices, pname, params);
};
void gl_wrap_context_glGetActiveUniformName(gl_wrap_context* ctx, GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName) {
	if(ctx->glGetActiveUniformNameProc == NULL) {
		ctx->glGetActiveUniformNameProc = (PFNGLGETACTIVEUNIFORMNAMEPROC)gl_wrap_get_pointer("glGetActiveUniformName");
	}
	ctx->glGetActiveUniformNameProc(program, uniformIndex, bufSize, length, uniformName);
};
GLuint gl_wrap_context_glGetUniformBlockIndex(gl_wrap_context* ctx, GLuint program, GLchar* uniformBlockName) {
	if(ctx->glGetUniformBlockIndexProc == NULL) {
		ctx->glGetUniformBlockIndexProc = (PFNGLGETUNIFORMBLOCKINDEXPROC)gl_wrap_get_pointer("glGetUniformBlockIndex");
	}
	return ctx->glGetUniformBlockIndexProc(program, uniformBlockName);
};
void gl_wrap_context_glGetActiveUniformBlockiv(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params) {
	if(ctx->glGetActiveUniformBlockivProc == NULL) {
		ctx->glGetActiveUniformBlockivProc = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)gl_wrap_get_pointer("glGetActiveUniformBlockiv");
	}
	ctx->glGetActiveUniformBlockivProc(program, uniformBlockIndex, pname, params);
};
void gl_wrap_context_glGetActiveUniformBlockName(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) {
	if(ctx->glGetActiveUniformBlockNameProc == NULL) {
		ctx->glGetActiveUniformBlockNameProc = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)gl_wrap_get_pointer("glGetActiveUniformBlockName");
	}
	ctx->glGetActiveUniformBlockNameProc(program, uniformBlockIndex, bufSize, length, uniformBlockName);
};
void gl_wrap_context_glUniformBlockBinding(gl_wrap_context* ctx, GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
	if(ctx->glUniformBlockBindingProc == NULL) {
		ctx->glUniformBlockBindingProc = (PFNGLUNIFORMBLOCKBINDINGPROC)gl_wrap_get_pointer("glUniformBlockBinding");
	}
	ctx->glUniformBlockBindingProc(program, uniformBlockIndex, uniformBlockBinding);
};
void gl_wrap_context_glDrawElementsBaseVertex(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLint basevertex) {
	if(ctx->glDrawElementsBaseVertexProc == NULL) {
		ctx->glDrawElementsBaseVertexProc = (PFNGLDRAWELEMENTSBASEVERTEXPROC)gl_wrap_get_pointer("glDrawElementsBaseVertex");
	}
	ctx->glDrawElementsBaseVertexProc(mode, count, type, indices, basevertex);
};
void gl_wrap_context_glDrawRangeElementsBaseVertex(gl_wrap_context* ctx, GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, void* indices, GLint basevertex) {
	if(ctx->glDrawRangeElementsBaseVertexProc == NULL) {
		ctx->glDrawRangeElementsBaseVertexProc = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)gl_wrap_get_pointer("glDrawRangeElementsBaseVertex");
	}
	ctx->glDrawRangeElementsBaseVertexProc(mode, start, end, count, type, indices, basevertex);
};
void gl_wrap_context_glDrawElementsInstancedBaseVertex(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount, GLint basevertex) {
	if(ctx->glDrawElementsInstancedBaseVertexProc == NULL) {
		ctx->glDrawElementsInstancedBaseVertexProc = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)gl_wrap_get_pointer("glDrawElementsInstancedBaseVertex");
	}
	ctx->glDrawElementsInstancedBaseVertexProc(mode, count, type, indices, instancecount, basevertex);
};
void gl_wrap_context_glMultiDrawElementsBaseVertex(gl_wrap_context* ctx, GLenum mode, GLsizei* count, GLenum type, void** indices, GLsizei drawcount, GLint* basevertex) {
	if(ctx->glMultiDrawElementsBaseVertexProc == NULL) {
		ctx->glMultiDrawElementsBaseVertexProc = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)gl_wrap_get_pointer("glMultiDrawElementsBaseVertex");
	}
	ctx->glMultiDrawElementsBaseVertexProc(mode, count, type, indices, drawcount, basevertex);
};
void gl_wrap_context_glProvokingVertex(gl_wrap_context* ctx, GLenum mode) {
	if(ctx->glProvokingVertexProc == NULL) {
		ctx->glProvokingVertexProc = (PFNGLPROVOKINGVERTEXPROC)gl_wrap_get_pointer("glProvokingVertex");
	}
	ctx->glProvokingVertexProc(mode);
};
GLsync gl_wrap_context_glFenceSync(gl_wrap_context* ctx, GLenum condition, GLbitfield flags) {
	if(ctx->glFenceSyncProc == NULL) {
		ctx->glFenceSyncProc = (PFNGLFENCESYNCPROC)gl_wrap_get_pointer("glFenceSync");
	}
	return ctx->glFenceSyncProc(condition, flags);
};
GLboolean gl_wrap_context_glIsSync(gl_wrap_context* ctx, GLsync sync) {
	if(ctx->glIsSyncProc == NULL) {
		ctx->glIsSyncProc = (PFNGLISSYNCPROC)gl_wrap_get_pointer("glIsSync");
	}
	return ctx->glIsSyncProc(sync);
};
void gl_wrap_context_glDeleteSync(gl_wrap_context* ctx, GLsync sync) {
	if(ctx->glDeleteSyncProc == NULL) {
		ctx->glDeleteSyncProc = (PFNGLDELETESYNCPROC)gl_wrap_get_pointer("glDeleteSync");
	}
	ctx->glDeleteSyncProc(sync);
};
GLenum gl_wrap_context_glClientWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout) {
	if(ctx->glClientWaitSyncProc == NULL) {
		ctx->glClientWaitSyncProc = (PFNGLCLIENTWAITSYNCPROC)gl_wrap_get_pointer("glClientWaitSync");
	}
	return ctx->glClientWaitSyncProc(sync, flags, timeout);
};
void gl_wrap_context_glWaitSync(gl_wrap_context* ctx, GLsync sync, GLbitfield flags, GLuint64 timeout) {
	if(ctx->glWaitSyncProc == NULL) {
		ctx->glWaitSyncProc = (PFNGLWAITSYNCPROC)gl_wrap_get_pointer("glWaitSync");
	}
	ctx->glWaitSyncProc(sync, flags, timeout);
};
void gl_wrap_context_glGetInteger64v(gl_wrap_context* ctx, GLenum pname, GLint64* data) {
	if(ctx->glGetInteger64vProc == NULL) {
		ctx->glGetInteger64vProc = (PFNGLGETINTEGER64VPROC)gl_wrap_get_pointer("glGetInteger64v");
	}
	ctx->glGetInteger64vProc(pname, data);
};
void gl_wrap_context_glGetSynciv(gl_wrap_context* ctx, GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values) {
	if(ctx->glGetSyncivProc == NULL) {
		ctx->glGetSyncivProc = (PFNGLGETSYNCIVPROC)gl_wrap_get_pointer("glGetSynciv");
	}
	ctx->glGetSyncivProc(sync, pname, bufSize, length, values);
};
void gl_wrap_context_glGetInteger64i_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLint64* data) {
	if(ctx->glGetInteger64i_vProc == NULL) {
		ctx->glGetInteger64i_vProc = (PFNGLGETINTEGER64I_VPROC)gl_wrap_get_pointer("glGetInteger64i_v");
	}
	ctx->glGetInteger64i_vProc(target, index, data);
};
void gl_wrap_context_glGetBufferParameteri64v(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint64* params) {
	if(ctx->glGetBufferParameteri64vProc == NULL) {
		ctx->glGetBufferParameteri64vProc = (PFNGLGETBUFFERPARAMETERI64VPROC)gl_wrap_get_pointer("glGetBufferParameteri64v");
	}
	ctx->glGetBufferParameteri64vProc(target, pname, params);
};
void gl_wrap_context_glFramebufferTexture(gl_wrap_context* ctx, GLenum target, GLenum attachment, GLuint texture, GLint level) {
	if(ctx->glFramebufferTextureProc == NULL) {
		ctx->glFramebufferTextureProc = (PFNGLFRAMEBUFFERTEXTUREPROC)gl_wrap_get_pointer("glFramebufferTexture");
	}
	ctx->glFramebufferTextureProc(target, attachment, texture, level);
};
void gl_wrap_context_glTexImage2DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
	if(ctx->glTexImage2DMultisampleProc == NULL) {
		ctx->glTexImage2DMultisampleProc = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)gl_wrap_get_pointer("glTexImage2DMultisample");
	}
	ctx->glTexImage2DMultisampleProc(target, samples, internalformat, width, height, fixedsamplelocations);
};
void gl_wrap_context_glTexImage3DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
	if(ctx->glTexImage3DMultisampleProc == NULL) {
		ctx->glTexImage3DMultisampleProc = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)gl_wrap_get_pointer("glTexImage3DMultisample");
	}
	ctx->glTexImage3DMultisampleProc(target, samples, internalformat, width, height, depth, fixedsamplelocations);
};
void gl_wrap_context_glGetMultisamplefv(gl_wrap_context* ctx, GLenum pname, GLuint index, GLfloat* val) {
	if(ctx->glGetMultisamplefvProc == NULL) {
		ctx->glGetMultisamplefvProc = (PFNGLGETMULTISAMPLEFVPROC)gl_wrap_get_pointer("glGetMultisamplefv");
	}
	ctx->glGetMultisamplefvProc(pname, index, val);
};
void gl_wrap_context_glSampleMaski(gl_wrap_context* ctx, GLuint maskNumber, GLbitfield mask) {
	if(ctx->glSampleMaskiProc == NULL) {
		ctx->glSampleMaskiProc = (PFNGLSAMPLEMASKIPROC)gl_wrap_get_pointer("glSampleMaski");
	}
	ctx->glSampleMaskiProc(maskNumber, mask);
};
void gl_wrap_context_glBindFragDataLocationIndexed(gl_wrap_context* ctx, GLuint program, GLuint colorNumber, GLuint index, GLchar* name) {
	if(ctx->glBindFragDataLocationIndexedProc == NULL) {
		ctx->glBindFragDataLocationIndexedProc = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)gl_wrap_get_pointer("glBindFragDataLocationIndexed");
	}
	ctx->glBindFragDataLocationIndexedProc(program, colorNumber, index, name);
};
GLint gl_wrap_context_glGetFragDataIndex(gl_wrap_context* ctx, GLuint program, GLchar* name) {
	if(ctx->glGetFragDataIndexProc == NULL) {
		ctx->glGetFragDataIndexProc = (PFNGLGETFRAGDATAINDEXPROC)gl_wrap_get_pointer("glGetFragDataIndex");
	}
	return ctx->glGetFragDataIndexProc(program, name);
};
void gl_wrap_context_glGenSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers) {
	if(ctx->glGenSamplersProc == NULL) {
		ctx->glGenSamplersProc = (PFNGLGENSAMPLERSPROC)gl_wrap_get_pointer("glGenSamplers");
	}
	ctx->glGenSamplersProc(count, samplers);
};
void gl_wrap_context_glDeleteSamplers(gl_wrap_context* ctx, GLsizei count, GLuint* samplers) {
	if(ctx->glDeleteSamplersProc == NULL) {
		ctx->glDeleteSamplersProc = (PFNGLDELETESAMPLERSPROC)gl_wrap_get_pointer("glDeleteSamplers");
	}
	ctx->glDeleteSamplersProc(count, samplers);
};
GLboolean gl_wrap_context_glIsSampler(gl_wrap_context* ctx, GLuint sampler) {
	if(ctx->glIsSamplerProc == NULL) {
		ctx->glIsSamplerProc = (PFNGLISSAMPLERPROC)gl_wrap_get_pointer("glIsSampler");
	}
	return ctx->glIsSamplerProc(sampler);
};
void gl_wrap_context_glBindSampler(gl_wrap_context* ctx, GLuint unit, GLuint sampler) {
	if(ctx->glBindSamplerProc == NULL) {
		ctx->glBindSamplerProc = (PFNGLBINDSAMPLERPROC)gl_wrap_get_pointer("glBindSampler");
	}
	ctx->glBindSamplerProc(unit, sampler);
};
void gl_wrap_context_glSamplerParameteri(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint param) {
	if(ctx->glSamplerParameteriProc == NULL) {
		ctx->glSamplerParameteriProc = (PFNGLSAMPLERPARAMETERIPROC)gl_wrap_get_pointer("glSamplerParameteri");
	}
	ctx->glSamplerParameteriProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* param) {
	if(ctx->glSamplerParameterivProc == NULL) {
		ctx->glSamplerParameterivProc = (PFNGLSAMPLERPARAMETERIVPROC)gl_wrap_get_pointer("glSamplerParameteriv");
	}
	ctx->glSamplerParameterivProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameterf(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat param) {
	if(ctx->glSamplerParameterfProc == NULL) {
		ctx->glSamplerParameterfProc = (PFNGLSAMPLERPARAMETERFPROC)gl_wrap_get_pointer("glSamplerParameterf");
	}
	ctx->glSamplerParameterfProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* param) {
	if(ctx->glSamplerParameterfvProc == NULL) {
		ctx->glSamplerParameterfvProc = (PFNGLSAMPLERPARAMETERFVPROC)gl_wrap_get_pointer("glSamplerParameterfv");
	}
	ctx->glSamplerParameterfvProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameterIiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* param) {
	if(ctx->glSamplerParameterIivProc == NULL) {
		ctx->glSamplerParameterIivProc = (PFNGLSAMPLERPARAMETERIIVPROC)gl_wrap_get_pointer("glSamplerParameterIiv");
	}
	ctx->glSamplerParameterIivProc(sampler, pname, param);
};
void gl_wrap_context_glSamplerParameterIuiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLuint* param) {
	if(ctx->glSamplerParameterIuivProc == NULL) {
		ctx->glSamplerParameterIuivProc = (PFNGLSAMPLERPARAMETERIUIVPROC)gl_wrap_get_pointer("glSamplerParameterIuiv");
	}
	ctx->glSamplerParameterIuivProc(sampler, pname, param);
};
void gl_wrap_context_glGetSamplerParameteriv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* params) {
	if(ctx->glGetSamplerParameterivProc == NULL) {
		ctx->glGetSamplerParameterivProc = (PFNGLGETSAMPLERPARAMETERIVPROC)gl_wrap_get_pointer("glGetSamplerParameteriv");
	}
	ctx->glGetSamplerParameterivProc(sampler, pname, params);
};
void gl_wrap_context_glGetSamplerParameterIiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLint* params) {
	if(ctx->glGetSamplerParameterIivProc == NULL) {
		ctx->glGetSamplerParameterIivProc = (PFNGLGETSAMPLERPARAMETERIIVPROC)gl_wrap_get_pointer("glGetSamplerParameterIiv");
	}
	ctx->glGetSamplerParameterIivProc(sampler, pname, params);
};
void gl_wrap_context_glGetSamplerParameterfv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLfloat* params) {
	if(ctx->glGetSamplerParameterfvProc == NULL) {
		ctx->glGetSamplerParameterfvProc = (PFNGLGETSAMPLERPARAMETERFVPROC)gl_wrap_get_pointer("glGetSamplerParameterfv");
	}
	ctx->glGetSamplerParameterfvProc(sampler, pname, params);
};
void gl_wrap_context_glGetSamplerParameterIuiv(gl_wrap_context* ctx, GLuint sampler, GLenum pname, GLuint* params) {
	if(ctx->glGetSamplerParameterIuivProc == NULL) {
		ctx->glGetSamplerParameterIuivProc = (PFNGLGETSAMPLERPARAMETERIUIVPROC)gl_wrap_get_pointer("glGetSamplerParameterIuiv");
	}
	ctx->glGetSamplerParameterIuivProc(sampler, pname, params);
};
void gl_wrap_context_glQueryCounter(gl_wrap_context* ctx, GLuint id, GLenum target) {
	if(ctx->glQueryCounterProc == NULL) {
		ctx->glQueryCounterProc = (PFNGLQUERYCOUNTERPROC)gl_wrap_get_pointer("glQueryCounter");
	}
	ctx->glQueryCounterProc(id, target);
};
void gl_wrap_context_glGetQueryObjecti64v(gl_wrap_context* ctx, GLuint id, GLenum pname, GLint64* params) {
	if(ctx->glGetQueryObjecti64vProc == NULL) {
		ctx->glGetQueryObjecti64vProc = (PFNGLGETQUERYOBJECTI64VPROC)gl_wrap_get_pointer("glGetQueryObjecti64v");
	}
	ctx->glGetQueryObjecti64vProc(id, pname, params);
};
void gl_wrap_context_glGetQueryObjectui64v(gl_wrap_context* ctx, GLuint id, GLenum pname, GLuint64* params) {
	if(ctx->glGetQueryObjectui64vProc == NULL) {
		ctx->glGetQueryObjectui64vProc = (PFNGLGETQUERYOBJECTUI64VPROC)gl_wrap_get_pointer("glGetQueryObjectui64v");
	}
	ctx->glGetQueryObjectui64vProc(id, pname, params);
};
void gl_wrap_context_glVertexAttribDivisor(gl_wrap_context* ctx, GLuint index, GLuint divisor) {
	if(ctx->glVertexAttribDivisorProc == NULL) {
		ctx->glVertexAttribDivisorProc = (PFNGLVERTEXATTRIBDIVISORPROC)gl_wrap_get_pointer("glVertexAttribDivisor");
	}
	ctx->glVertexAttribDivisorProc(index, divisor);
};
void gl_wrap_context_glVertexAttribP1ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value) {
	if(ctx->glVertexAttribP1uiProc == NULL) {
		ctx->glVertexAttribP1uiProc = (PFNGLVERTEXATTRIBP1UIPROC)gl_wrap_get_pointer("glVertexAttribP1ui");
	}
	ctx->glVertexAttribP1uiProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP1uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value) {
	if(ctx->glVertexAttribP1uivProc == NULL) {
		ctx->glVertexAttribP1uivProc = (PFNGLVERTEXATTRIBP1UIVPROC)gl_wrap_get_pointer("glVertexAttribP1uiv");
	}
	ctx->glVertexAttribP1uivProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP2ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value) {
	if(ctx->glVertexAttribP2uiProc == NULL) {
		ctx->glVertexAttribP2uiProc = (PFNGLVERTEXATTRIBP2UIPROC)gl_wrap_get_pointer("glVertexAttribP2ui");
	}
	ctx->glVertexAttribP2uiProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP2uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value) {
	if(ctx->glVertexAttribP2uivProc == NULL) {
		ctx->glVertexAttribP2uivProc = (PFNGLVERTEXATTRIBP2UIVPROC)gl_wrap_get_pointer("glVertexAttribP2uiv");
	}
	ctx->glVertexAttribP2uivProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP3ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value) {
	if(ctx->glVertexAttribP3uiProc == NULL) {
		ctx->glVertexAttribP3uiProc = (PFNGLVERTEXATTRIBP3UIPROC)gl_wrap_get_pointer("glVertexAttribP3ui");
	}
	ctx->glVertexAttribP3uiProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP3uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value) {
	if(ctx->glVertexAttribP3uivProc == NULL) {
		ctx->glVertexAttribP3uivProc = (PFNGLVERTEXATTRIBP3UIVPROC)gl_wrap_get_pointer("glVertexAttribP3uiv");
	}
	ctx->glVertexAttribP3uivProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP4ui(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint value) {
	if(ctx->glVertexAttribP4uiProc == NULL) {
		ctx->glVertexAttribP4uiProc = (PFNGLVERTEXATTRIBP4UIPROC)gl_wrap_get_pointer("glVertexAttribP4ui");
	}
	ctx->glVertexAttribP4uiProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexAttribP4uiv(gl_wrap_context* ctx, GLuint index, GLenum type, GLboolean normalized, GLuint* value) {
	if(ctx->glVertexAttribP4uivProc == NULL) {
		ctx->glVertexAttribP4uivProc = (PFNGLVERTEXATTRIBP4UIVPROC)gl_wrap_get_pointer("glVertexAttribP4uiv");
	}
	ctx->glVertexAttribP4uivProc(index, type, normalized, value);
};
void gl_wrap_context_glVertexP2ui(gl_wrap_context* ctx, GLenum type, GLuint value) {
	if(ctx->glVertexP2uiProc == NULL) {
		ctx->glVertexP2uiProc = (PFNGLVERTEXP2UIPROC)gl_wrap_get_pointer("glVertexP2ui");
	}
	ctx->glVertexP2uiProc(type, value);
};
void gl_wrap_context_glVertexP2uiv(gl_wrap_context* ctx, GLenum type, GLuint* value) {
	if(ctx->glVertexP2uivProc == NULL) {
		ctx->glVertexP2uivProc = (PFNGLVERTEXP2UIVPROC)gl_wrap_get_pointer("glVertexP2uiv");
	}
	ctx->glVertexP2uivProc(type, value);
};
void gl_wrap_context_glVertexP3ui(gl_wrap_context* ctx, GLenum type, GLuint value) {
	if(ctx->glVertexP3uiProc == NULL) {
		ctx->glVertexP3uiProc = (PFNGLVERTEXP3UIPROC)gl_wrap_get_pointer("glVertexP3ui");
	}
	ctx->glVertexP3uiProc(type, value);
};
void gl_wrap_context_glVertexP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* value) {
	if(ctx->glVertexP3uivProc == NULL) {
		ctx->glVertexP3uivProc = (PFNGLVERTEXP3UIVPROC)gl_wrap_get_pointer("glVertexP3uiv");
	}
	ctx->glVertexP3uivProc(type, value);
};
void gl_wrap_context_glVertexP4ui(gl_wrap_context* ctx, GLenum type, GLuint value) {
	if(ctx->glVertexP4uiProc == NULL) {
		ctx->glVertexP4uiProc = (PFNGLVERTEXP4UIPROC)gl_wrap_get_pointer("glVertexP4ui");
	}
	ctx->glVertexP4uiProc(type, value);
};
void gl_wrap_context_glVertexP4uiv(gl_wrap_context* ctx, GLenum type, GLuint* value) {
	if(ctx->glVertexP4uivProc == NULL) {
		ctx->glVertexP4uivProc = (PFNGLVERTEXP4UIVPROC)gl_wrap_get_pointer("glVertexP4uiv");
	}
	ctx->glVertexP4uivProc(type, value);
};
void gl_wrap_context_glTexCoordP1ui(gl_wrap_context* ctx, GLenum type, GLuint coords) {
	if(ctx->glTexCoordP1uiProc == NULL) {
		ctx->glTexCoordP1uiProc = (PFNGLTEXCOORDP1UIPROC)gl_wrap_get_pointer("glTexCoordP1ui");
	}
	ctx->glTexCoordP1uiProc(type, coords);
};
void gl_wrap_context_glTexCoordP1uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords) {
	if(ctx->glTexCoordP1uivProc == NULL) {
		ctx->glTexCoordP1uivProc = (PFNGLTEXCOORDP1UIVPROC)gl_wrap_get_pointer("glTexCoordP1uiv");
	}
	ctx->glTexCoordP1uivProc(type, coords);
};
void gl_wrap_context_glTexCoordP2ui(gl_wrap_context* ctx, GLenum type, GLuint coords) {
	if(ctx->glTexCoordP2uiProc == NULL) {
		ctx->glTexCoordP2uiProc = (PFNGLTEXCOORDP2UIPROC)gl_wrap_get_pointer("glTexCoordP2ui");
	}
	ctx->glTexCoordP2uiProc(type, coords);
};
void gl_wrap_context_glTexCoordP2uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords) {
	if(ctx->glTexCoordP2uivProc == NULL) {
		ctx->glTexCoordP2uivProc = (PFNGLTEXCOORDP2UIVPROC)gl_wrap_get_pointer("glTexCoordP2uiv");
	}
	ctx->glTexCoordP2uivProc(type, coords);
};
void gl_wrap_context_glTexCoordP3ui(gl_wrap_context* ctx, GLenum type, GLuint coords) {
	if(ctx->glTexCoordP3uiProc == NULL) {
		ctx->glTexCoordP3uiProc = (PFNGLTEXCOORDP3UIPROC)gl_wrap_get_pointer("glTexCoordP3ui");
	}
	ctx->glTexCoordP3uiProc(type, coords);
};
void gl_wrap_context_glTexCoordP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords) {
	if(ctx->glTexCoordP3uivProc == NULL) {
		ctx->glTexCoordP3uivProc = (PFNGLTEXCOORDP3UIVPROC)gl_wrap_get_pointer("glTexCoordP3uiv");
	}
	ctx->glTexCoordP3uivProc(type, coords);
};
void gl_wrap_context_glTexCoordP4ui(gl_wrap_context* ctx, GLenum type, GLuint coords) {
	if(ctx->glTexCoordP4uiProc == NULL) {
		ctx->glTexCoordP4uiProc = (PFNGLTEXCOORDP4UIPROC)gl_wrap_get_pointer("glTexCoordP4ui");
	}
	ctx->glTexCoordP4uiProc(type, coords);
};
void gl_wrap_context_glTexCoordP4uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords) {
	if(ctx->glTexCoordP4uivProc == NULL) {
		ctx->glTexCoordP4uivProc = (PFNGLTEXCOORDP4UIVPROC)gl_wrap_get_pointer("glTexCoordP4uiv");
	}
	ctx->glTexCoordP4uivProc(type, coords);
};
void gl_wrap_context_glMultiTexCoordP1ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords) {
	if(ctx->glMultiTexCoordP1uiProc == NULL) {
		ctx->glMultiTexCoordP1uiProc = (PFNGLMULTITEXCOORDP1UIPROC)gl_wrap_get_pointer("glMultiTexCoordP1ui");
	}
	ctx->glMultiTexCoordP1uiProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP1uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords) {
	if(ctx->glMultiTexCoordP1uivProc == NULL) {
		ctx->glMultiTexCoordP1uivProc = (PFNGLMULTITEXCOORDP1UIVPROC)gl_wrap_get_pointer("glMultiTexCoordP1uiv");
	}
	ctx->glMultiTexCoordP1uivProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP2ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords) {
	if(ctx->glMultiTexCoordP2uiProc == NULL) {
		ctx->glMultiTexCoordP2uiProc = (PFNGLMULTITEXCOORDP2UIPROC)gl_wrap_get_pointer("glMultiTexCoordP2ui");
	}
	ctx->glMultiTexCoordP2uiProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP2uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords) {
	if(ctx->glMultiTexCoordP2uivProc == NULL) {
		ctx->glMultiTexCoordP2uivProc = (PFNGLMULTITEXCOORDP2UIVPROC)gl_wrap_get_pointer("glMultiTexCoordP2uiv");
	}
	ctx->glMultiTexCoordP2uivProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP3ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords) {
	if(ctx->glMultiTexCoordP3uiProc == NULL) {
		ctx->glMultiTexCoordP3uiProc = (PFNGLMULTITEXCOORDP3UIPROC)gl_wrap_get_pointer("glMultiTexCoordP3ui");
	}
	ctx->glMultiTexCoordP3uiProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP3uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords) {
	if(ctx->glMultiTexCoordP3uivProc == NULL) {
		ctx->glMultiTexCoordP3uivProc = (PFNGLMULTITEXCOORDP3UIVPROC)gl_wrap_get_pointer("glMultiTexCoordP3uiv");
	}
	ctx->glMultiTexCoordP3uivProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP4ui(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint coords) {
	if(ctx->glMultiTexCoordP4uiProc == NULL) {
		ctx->glMultiTexCoordP4uiProc = (PFNGLMULTITEXCOORDP4UIPROC)gl_wrap_get_pointer("glMultiTexCoordP4ui");
	}
	ctx->glMultiTexCoordP4uiProc(texture, type, coords);
};
void gl_wrap_context_glMultiTexCoordP4uiv(gl_wrap_context* ctx, GLenum texture, GLenum type, GLuint* coords) {
	if(ctx->glMultiTexCoordP4uivProc == NULL) {
		ctx->glMultiTexCoordP4uivProc = (PFNGLMULTITEXCOORDP4UIVPROC)gl_wrap_get_pointer("glMultiTexCoordP4uiv");
	}
	ctx->glMultiTexCoordP4uivProc(texture, type, coords);
};
void gl_wrap_context_glNormalP3ui(gl_wrap_context* ctx, GLenum type, GLuint coords) {
	if(ctx->glNormalP3uiProc == NULL) {
		ctx->glNormalP3uiProc = (PFNGLNORMALP3UIPROC)gl_wrap_get_pointer("glNormalP3ui");
	}
	ctx->glNormalP3uiProc(type, coords);
};
void gl_wrap_context_glNormalP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* coords) {
	if(ctx->glNormalP3uivProc == NULL) {
		ctx->glNormalP3uivProc = (PFNGLNORMALP3UIVPROC)gl_wrap_get_pointer("glNormalP3uiv");
	}
	ctx->glNormalP3uivProc(type, coords);
};
void gl_wrap_context_glColorP3ui(gl_wrap_context* ctx, GLenum type, GLuint color) {
	if(ctx->glColorP3uiProc == NULL) {
		ctx->glColorP3uiProc = (PFNGLCOLORP3UIPROC)gl_wrap_get_pointer("glColorP3ui");
	}
	ctx->glColorP3uiProc(type, color);
};
void gl_wrap_context_glColorP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* color) {
	if(ctx->glColorP3uivProc == NULL) {
		ctx->glColorP3uivProc = (PFNGLCOLORP3UIVPROC)gl_wrap_get_pointer("glColorP3uiv");
	}
	ctx->glColorP3uivProc(type, color);
};
void gl_wrap_context_glColorP4ui(gl_wrap_context* ctx, GLenum type, GLuint color) {
	if(ctx->glColorP4uiProc == NULL) {
		ctx->glColorP4uiProc = (PFNGLCOLORP4UIPROC)gl_wrap_get_pointer("glColorP4ui");
	}
	ctx->glColorP4uiProc(type, color);
};
void gl_wrap_context_glColorP4uiv(gl_wrap_context* ctx, GLenum type, GLuint* color) {
	if(ctx->glColorP4uivProc == NULL) {
		ctx->glColorP4uivProc = (PFNGLCOLORP4UIVPROC)gl_wrap_get_pointer("glColorP4uiv");
	}
	ctx->glColorP4uivProc(type, color);
};
void gl_wrap_context_glSecondaryColorP3ui(gl_wrap_context* ctx, GLenum type, GLuint color) {
	if(ctx->glSecondaryColorP3uiProc == NULL) {
		ctx->glSecondaryColorP3uiProc = (PFNGLSECONDARYCOLORP3UIPROC)gl_wrap_get_pointer("glSecondaryColorP3ui");
	}
	ctx->glSecondaryColorP3uiProc(type, color);
};
void gl_wrap_context_glSecondaryColorP3uiv(gl_wrap_context* ctx, GLenum type, GLuint* color) {
	if(ctx->glSecondaryColorP3uivProc == NULL) {
		ctx->glSecondaryColorP3uivProc = (PFNGLSECONDARYCOLORP3UIVPROC)gl_wrap_get_pointer("glSecondaryColorP3uiv");
	}
	ctx->glSecondaryColorP3uivProc(type, color);
};
void gl_wrap_context_glMinSampleShading(gl_wrap_context* ctx, GLfloat value) {
	if(ctx->glMinSampleShadingProc == NULL) {
		ctx->glMinSampleShadingProc = (PFNGLMINSAMPLESHADINGPROC)gl_wrap_get_pointer("glMinSampleShading");
	}
	ctx->glMinSampleShadingProc(value);
};
void gl_wrap_context_glBlendEquationi(gl_wrap_context* ctx, GLuint buf, GLenum mode) {
	if(ctx->glBlendEquationiProc == NULL) {
		ctx->glBlendEquationiProc = (PFNGLBLENDEQUATIONIPROC)gl_wrap_get_pointer("glBlendEquationi");
	}
	ctx->glBlendEquationiProc(buf, mode);
};
void gl_wrap_context_glBlendEquationSeparatei(gl_wrap_context* ctx, GLuint buf, GLenum modeRGB, GLenum modeAlpha) {
	if(ctx->glBlendEquationSeparateiProc == NULL) {
		ctx->glBlendEquationSeparateiProc = (PFNGLBLENDEQUATIONSEPARATEIPROC)gl_wrap_get_pointer("glBlendEquationSeparatei");
	}
	ctx->glBlendEquationSeparateiProc(buf, modeRGB, modeAlpha);
};
void gl_wrap_context_glBlendFunci(gl_wrap_context* ctx, GLuint buf, GLenum src, GLenum dst) {
	if(ctx->glBlendFunciProc == NULL) {
		ctx->glBlendFunciProc = (PFNGLBLENDFUNCIPROC)gl_wrap_get_pointer("glBlendFunci");
	}
	ctx->glBlendFunciProc(buf, src, dst);
};
void gl_wrap_context_glBlendFuncSeparatei(gl_wrap_context* ctx, GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
	if(ctx->glBlendFuncSeparateiProc == NULL) {
		ctx->glBlendFuncSeparateiProc = (PFNGLBLENDFUNCSEPARATEIPROC)gl_wrap_get_pointer("glBlendFuncSeparatei");
	}
	ctx->glBlendFuncSeparateiProc(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
};
void gl_wrap_context_glDrawArraysIndirect(gl_wrap_context* ctx, GLenum mode, void* indirect) {
	if(ctx->glDrawArraysIndirectProc == NULL) {
		ctx->glDrawArraysIndirectProc = (PFNGLDRAWARRAYSINDIRECTPROC)gl_wrap_get_pointer("glDrawArraysIndirect");
	}
	ctx->glDrawArraysIndirectProc(mode, indirect);
};
void gl_wrap_context_glDrawElementsIndirect(gl_wrap_context* ctx, GLenum mode, GLenum type, void* indirect) {
	if(ctx->glDrawElementsIndirectProc == NULL) {
		ctx->glDrawElementsIndirectProc = (PFNGLDRAWELEMENTSINDIRECTPROC)gl_wrap_get_pointer("glDrawElementsIndirect");
	}
	ctx->glDrawElementsIndirectProc(mode, type, indirect);
};
void gl_wrap_context_glUniform1d(gl_wrap_context* ctx, GLint location, GLdouble x) {
	if(ctx->glUniform1dProc == NULL) {
		ctx->glUniform1dProc = (PFNGLUNIFORM1DPROC)gl_wrap_get_pointer("glUniform1d");
	}
	ctx->glUniform1dProc(location, x);
};
void gl_wrap_context_glUniform2d(gl_wrap_context* ctx, GLint location, GLdouble x, GLdouble y) {
	if(ctx->glUniform2dProc == NULL) {
		ctx->glUniform2dProc = (PFNGLUNIFORM2DPROC)gl_wrap_get_pointer("glUniform2d");
	}
	ctx->glUniform2dProc(location, x, y);
};
void gl_wrap_context_glUniform3d(gl_wrap_context* ctx, GLint location, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glUniform3dProc == NULL) {
		ctx->glUniform3dProc = (PFNGLUNIFORM3DPROC)gl_wrap_get_pointer("glUniform3d");
	}
	ctx->glUniform3dProc(location, x, y, z);
};
void gl_wrap_context_glUniform4d(gl_wrap_context* ctx, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	if(ctx->glUniform4dProc == NULL) {
		ctx->glUniform4dProc = (PFNGLUNIFORM4DPROC)gl_wrap_get_pointer("glUniform4d");
	}
	ctx->glUniform4dProc(location, x, y, z, w);
};
void gl_wrap_context_glUniform1dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glUniform1dvProc == NULL) {
		ctx->glUniform1dvProc = (PFNGLUNIFORM1DVPROC)gl_wrap_get_pointer("glUniform1dv");
	}
	ctx->glUniform1dvProc(location, count, value);
};
void gl_wrap_context_glUniform2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glUniform2dvProc == NULL) {
		ctx->glUniform2dvProc = (PFNGLUNIFORM2DVPROC)gl_wrap_get_pointer("glUniform2dv");
	}
	ctx->glUniform2dvProc(location, count, value);
};
void gl_wrap_context_glUniform3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glUniform3dvProc == NULL) {
		ctx->glUniform3dvProc = (PFNGLUNIFORM3DVPROC)gl_wrap_get_pointer("glUniform3dv");
	}
	ctx->glUniform3dvProc(location, count, value);
};
void gl_wrap_context_glUniform4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glUniform4dvProc == NULL) {
		ctx->glUniform4dvProc = (PFNGLUNIFORM4DVPROC)gl_wrap_get_pointer("glUniform4dv");
	}
	ctx->glUniform4dvProc(location, count, value);
};
void gl_wrap_context_glUniformMatrix2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix2dvProc == NULL) {
		ctx->glUniformMatrix2dvProc = (PFNGLUNIFORMMATRIX2DVPROC)gl_wrap_get_pointer("glUniformMatrix2dv");
	}
	ctx->glUniformMatrix2dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix3dvProc == NULL) {
		ctx->glUniformMatrix3dvProc = (PFNGLUNIFORMMATRIX3DVPROC)gl_wrap_get_pointer("glUniformMatrix3dv");
	}
	ctx->glUniformMatrix3dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix4dvProc == NULL) {
		ctx->glUniformMatrix4dvProc = (PFNGLUNIFORMMATRIX4DVPROC)gl_wrap_get_pointer("glUniformMatrix4dv");
	}
	ctx->glUniformMatrix4dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix2x3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix2x3dvProc == NULL) {
		ctx->glUniformMatrix2x3dvProc = (PFNGLUNIFORMMATRIX2X3DVPROC)gl_wrap_get_pointer("glUniformMatrix2x3dv");
	}
	ctx->glUniformMatrix2x3dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix2x4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix2x4dvProc == NULL) {
		ctx->glUniformMatrix2x4dvProc = (PFNGLUNIFORMMATRIX2X4DVPROC)gl_wrap_get_pointer("glUniformMatrix2x4dv");
	}
	ctx->glUniformMatrix2x4dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3x2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix3x2dvProc == NULL) {
		ctx->glUniformMatrix3x2dvProc = (PFNGLUNIFORMMATRIX3X2DVPROC)gl_wrap_get_pointer("glUniformMatrix3x2dv");
	}
	ctx->glUniformMatrix3x2dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix3x4dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix3x4dvProc == NULL) {
		ctx->glUniformMatrix3x4dvProc = (PFNGLUNIFORMMATRIX3X4DVPROC)gl_wrap_get_pointer("glUniformMatrix3x4dv");
	}
	ctx->glUniformMatrix3x4dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4x2dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix4x2dvProc == NULL) {
		ctx->glUniformMatrix4x2dvProc = (PFNGLUNIFORMMATRIX4X2DVPROC)gl_wrap_get_pointer("glUniformMatrix4x2dv");
	}
	ctx->glUniformMatrix4x2dvProc(location, count, transpose, value);
};
void gl_wrap_context_glUniformMatrix4x3dv(gl_wrap_context* ctx, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glUniformMatrix4x3dvProc == NULL) {
		ctx->glUniformMatrix4x3dvProc = (PFNGLUNIFORMMATRIX4X3DVPROC)gl_wrap_get_pointer("glUniformMatrix4x3dv");
	}
	ctx->glUniformMatrix4x3dvProc(location, count, transpose, value);
};
void gl_wrap_context_glGetUniformdv(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble* params) {
	if(ctx->glGetUniformdvProc == NULL) {
		ctx->glGetUniformdvProc = (PFNGLGETUNIFORMDVPROC)gl_wrap_get_pointer("glGetUniformdv");
	}
	ctx->glGetUniformdvProc(program, location, params);
};
GLint gl_wrap_context_glGetSubroutineUniformLocation(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLchar* name) {
	if(ctx->glGetSubroutineUniformLocationProc == NULL) {
		ctx->glGetSubroutineUniformLocationProc = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)gl_wrap_get_pointer("glGetSubroutineUniformLocation");
	}
	return ctx->glGetSubroutineUniformLocationProc(program, shadertype, name);
};
GLuint gl_wrap_context_glGetSubroutineIndex(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLchar* name) {
	if(ctx->glGetSubroutineIndexProc == NULL) {
		ctx->glGetSubroutineIndexProc = (PFNGLGETSUBROUTINEINDEXPROC)gl_wrap_get_pointer("glGetSubroutineIndex");
	}
	return ctx->glGetSubroutineIndexProc(program, shadertype, name);
};
void gl_wrap_context_glGetActiveSubroutineUniformiv(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint* values) {
	if(ctx->glGetActiveSubroutineUniformivProc == NULL) {
		ctx->glGetActiveSubroutineUniformivProc = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)gl_wrap_get_pointer("glGetActiveSubroutineUniformiv");
	}
	ctx->glGetActiveSubroutineUniformivProc(program, shadertype, index, pname, values);
};
void gl_wrap_context_glGetActiveSubroutineUniformName(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name) {
	if(ctx->glGetActiveSubroutineUniformNameProc == NULL) {
		ctx->glGetActiveSubroutineUniformNameProc = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)gl_wrap_get_pointer("glGetActiveSubroutineUniformName");
	}
	ctx->glGetActiveSubroutineUniformNameProc(program, shadertype, index, bufsize, length, name);
};
void gl_wrap_context_glGetActiveSubroutineName(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei* length, GLchar* name) {
	if(ctx->glGetActiveSubroutineNameProc == NULL) {
		ctx->glGetActiveSubroutineNameProc = (PFNGLGETACTIVESUBROUTINENAMEPROC)gl_wrap_get_pointer("glGetActiveSubroutineName");
	}
	ctx->glGetActiveSubroutineNameProc(program, shadertype, index, bufsize, length, name);
};
void gl_wrap_context_glUniformSubroutinesuiv(gl_wrap_context* ctx, GLenum shadertype, GLsizei count, GLuint* indices) {
	if(ctx->glUniformSubroutinesuivProc == NULL) {
		ctx->glUniformSubroutinesuivProc = (PFNGLUNIFORMSUBROUTINESUIVPROC)gl_wrap_get_pointer("glUniformSubroutinesuiv");
	}
	ctx->glUniformSubroutinesuivProc(shadertype, count, indices);
};
void gl_wrap_context_glGetUniformSubroutineuiv(gl_wrap_context* ctx, GLenum shadertype, GLint location, GLuint* params) {
	if(ctx->glGetUniformSubroutineuivProc == NULL) {
		ctx->glGetUniformSubroutineuivProc = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)gl_wrap_get_pointer("glGetUniformSubroutineuiv");
	}
	ctx->glGetUniformSubroutineuivProc(shadertype, location, params);
};
void gl_wrap_context_glGetProgramStageiv(gl_wrap_context* ctx, GLuint program, GLenum shadertype, GLenum pname, GLint* values) {
	if(ctx->glGetProgramStageivProc == NULL) {
		ctx->glGetProgramStageivProc = (PFNGLGETPROGRAMSTAGEIVPROC)gl_wrap_get_pointer("glGetProgramStageiv");
	}
	ctx->glGetProgramStageivProc(program, shadertype, pname, values);
};
void gl_wrap_context_glPatchParameteri(gl_wrap_context* ctx, GLenum pname, GLint value) {
	if(ctx->glPatchParameteriProc == NULL) {
		ctx->glPatchParameteriProc = (PFNGLPATCHPARAMETERIPROC)gl_wrap_get_pointer("glPatchParameteri");
	}
	ctx->glPatchParameteriProc(pname, value);
};
void gl_wrap_context_glPatchParameterfv(gl_wrap_context* ctx, GLenum pname, GLfloat* values) {
	if(ctx->glPatchParameterfvProc == NULL) {
		ctx->glPatchParameterfvProc = (PFNGLPATCHPARAMETERFVPROC)gl_wrap_get_pointer("glPatchParameterfv");
	}
	ctx->glPatchParameterfvProc(pname, values);
};
void gl_wrap_context_glBindTransformFeedback(gl_wrap_context* ctx, GLenum target, GLuint id) {
	if(ctx->glBindTransformFeedbackProc == NULL) {
		ctx->glBindTransformFeedbackProc = (PFNGLBINDTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glBindTransformFeedback");
	}
	ctx->glBindTransformFeedbackProc(target, id);
};
void gl_wrap_context_glDeleteTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glDeleteTransformFeedbacksProc == NULL) {
		ctx->glDeleteTransformFeedbacksProc = (PFNGLDELETETRANSFORMFEEDBACKSPROC)gl_wrap_get_pointer("glDeleteTransformFeedbacks");
	}
	ctx->glDeleteTransformFeedbacksProc(n, ids);
};
void gl_wrap_context_glGenTransformFeedbacks(gl_wrap_context* ctx, GLsizei n, GLuint* ids) {
	if(ctx->glGenTransformFeedbacksProc == NULL) {
		ctx->glGenTransformFeedbacksProc = (PFNGLGENTRANSFORMFEEDBACKSPROC)gl_wrap_get_pointer("glGenTransformFeedbacks");
	}
	ctx->glGenTransformFeedbacksProc(n, ids);
};
GLboolean gl_wrap_context_glIsTransformFeedback(gl_wrap_context* ctx, GLuint id) {
	if(ctx->glIsTransformFeedbackProc == NULL) {
		ctx->glIsTransformFeedbackProc = (PFNGLISTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glIsTransformFeedback");
	}
	return ctx->glIsTransformFeedbackProc(id);
};
void gl_wrap_context_glPauseTransformFeedback(gl_wrap_context* ctx) {
	if(ctx->glPauseTransformFeedbackProc == NULL) {
		ctx->glPauseTransformFeedbackProc = (PFNGLPAUSETRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glPauseTransformFeedback");
	}
	ctx->glPauseTransformFeedbackProc();
};
void gl_wrap_context_glResumeTransformFeedback(gl_wrap_context* ctx) {
	if(ctx->glResumeTransformFeedbackProc == NULL) {
		ctx->glResumeTransformFeedbackProc = (PFNGLRESUMETRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glResumeTransformFeedback");
	}
	ctx->glResumeTransformFeedbackProc();
};
void gl_wrap_context_glDrawTransformFeedback(gl_wrap_context* ctx, GLenum mode, GLuint id) {
	if(ctx->glDrawTransformFeedbackProc == NULL) {
		ctx->glDrawTransformFeedbackProc = (PFNGLDRAWTRANSFORMFEEDBACKPROC)gl_wrap_get_pointer("glDrawTransformFeedback");
	}
	ctx->glDrawTransformFeedbackProc(mode, id);
};
void gl_wrap_context_glDrawTransformFeedbackStream(gl_wrap_context* ctx, GLenum mode, GLuint id, GLuint stream) {
	if(ctx->glDrawTransformFeedbackStreamProc == NULL) {
		ctx->glDrawTransformFeedbackStreamProc = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)gl_wrap_get_pointer("glDrawTransformFeedbackStream");
	}
	ctx->glDrawTransformFeedbackStreamProc(mode, id, stream);
};
void gl_wrap_context_glBeginQueryIndexed(gl_wrap_context* ctx, GLenum target, GLuint index, GLuint id) {
	if(ctx->glBeginQueryIndexedProc == NULL) {
		ctx->glBeginQueryIndexedProc = (PFNGLBEGINQUERYINDEXEDPROC)gl_wrap_get_pointer("glBeginQueryIndexed");
	}
	ctx->glBeginQueryIndexedProc(target, index, id);
};
void gl_wrap_context_glEndQueryIndexed(gl_wrap_context* ctx, GLenum target, GLuint index) {
	if(ctx->glEndQueryIndexedProc == NULL) {
		ctx->glEndQueryIndexedProc = (PFNGLENDQUERYINDEXEDPROC)gl_wrap_get_pointer("glEndQueryIndexed");
	}
	ctx->glEndQueryIndexedProc(target, index);
};
void gl_wrap_context_glGetQueryIndexediv(gl_wrap_context* ctx, GLenum target, GLuint index, GLenum pname, GLint* params) {
	if(ctx->glGetQueryIndexedivProc == NULL) {
		ctx->glGetQueryIndexedivProc = (PFNGLGETQUERYINDEXEDIVPROC)gl_wrap_get_pointer("glGetQueryIndexediv");
	}
	ctx->glGetQueryIndexedivProc(target, index, pname, params);
};
void gl_wrap_context_glReleaseShaderCompiler(gl_wrap_context* ctx) {
	if(ctx->glReleaseShaderCompilerProc == NULL) {
		ctx->glReleaseShaderCompilerProc = (PFNGLRELEASESHADERCOMPILERPROC)gl_wrap_get_pointer("glReleaseShaderCompiler");
	}
	ctx->glReleaseShaderCompilerProc();
};
void gl_wrap_context_glShaderBinary(gl_wrap_context* ctx, GLsizei count, GLuint* shaders, GLenum binaryformat, void* binary, GLsizei length) {
	if(ctx->glShaderBinaryProc == NULL) {
		ctx->glShaderBinaryProc = (PFNGLSHADERBINARYPROC)gl_wrap_get_pointer("glShaderBinary");
	}
	ctx->glShaderBinaryProc(count, shaders, binaryformat, binary, length);
};
void gl_wrap_context_glGetShaderPrecisionFormat(gl_wrap_context* ctx, GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision) {
	if(ctx->glGetShaderPrecisionFormatProc == NULL) {
		ctx->glGetShaderPrecisionFormatProc = (PFNGLGETSHADERPRECISIONFORMATPROC)gl_wrap_get_pointer("glGetShaderPrecisionFormat");
	}
	ctx->glGetShaderPrecisionFormatProc(shadertype, precisiontype, range, precision);
};
void gl_wrap_context_glDepthRangef(gl_wrap_context* ctx, GLfloat n, GLfloat f) {
	if(ctx->glDepthRangefProc == NULL) {
		ctx->glDepthRangefProc = (PFNGLDEPTHRANGEFPROC)gl_wrap_get_pointer("glDepthRangef");
	}
	ctx->glDepthRangefProc(n, f);
};
void gl_wrap_context_glClearDepthf(gl_wrap_context* ctx, GLfloat d) {
	if(ctx->glClearDepthfProc == NULL) {
		ctx->glClearDepthfProc = (PFNGLCLEARDEPTHFPROC)gl_wrap_get_pointer("glClearDepthf");
	}
	ctx->glClearDepthfProc(d);
};
void gl_wrap_context_glGetProgramBinary(gl_wrap_context* ctx, GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, void* binary) {
	if(ctx->glGetProgramBinaryProc == NULL) {
		ctx->glGetProgramBinaryProc = (PFNGLGETPROGRAMBINARYPROC)gl_wrap_get_pointer("glGetProgramBinary");
	}
	ctx->glGetProgramBinaryProc(program, bufSize, length, binaryFormat, binary);
};
void gl_wrap_context_glProgramBinary(gl_wrap_context* ctx, GLuint program, GLenum binaryFormat, void* binary, GLsizei length) {
	if(ctx->glProgramBinaryProc == NULL) {
		ctx->glProgramBinaryProc = (PFNGLPROGRAMBINARYPROC)gl_wrap_get_pointer("glProgramBinary");
	}
	ctx->glProgramBinaryProc(program, binaryFormat, binary, length);
};
void gl_wrap_context_glProgramParameteri(gl_wrap_context* ctx, GLuint program, GLenum pname, GLint value) {
	if(ctx->glProgramParameteriProc == NULL) {
		ctx->glProgramParameteriProc = (PFNGLPROGRAMPARAMETERIPROC)gl_wrap_get_pointer("glProgramParameteri");
	}
	ctx->glProgramParameteriProc(program, pname, value);
};
void gl_wrap_context_glUseProgramStages(gl_wrap_context* ctx, GLuint pipeline, GLbitfield stages, GLuint program) {
	if(ctx->glUseProgramStagesProc == NULL) {
		ctx->glUseProgramStagesProc = (PFNGLUSEPROGRAMSTAGESPROC)gl_wrap_get_pointer("glUseProgramStages");
	}
	ctx->glUseProgramStagesProc(pipeline, stages, program);
};
void gl_wrap_context_glActiveShaderProgram(gl_wrap_context* ctx, GLuint pipeline, GLuint program) {
	if(ctx->glActiveShaderProgramProc == NULL) {
		ctx->glActiveShaderProgramProc = (PFNGLACTIVESHADERPROGRAMPROC)gl_wrap_get_pointer("glActiveShaderProgram");
	}
	ctx->glActiveShaderProgramProc(pipeline, program);
};
GLuint gl_wrap_context_glCreateShaderProgramv(gl_wrap_context* ctx, GLenum type, GLsizei count, GLchar** strings) {
	if(ctx->glCreateShaderProgramvProc == NULL) {
		ctx->glCreateShaderProgramvProc = (PFNGLCREATESHADERPROGRAMVPROC)gl_wrap_get_pointer("glCreateShaderProgramv");
	}
	return ctx->glCreateShaderProgramvProc(type, count, strings);
};
void gl_wrap_context_glBindProgramPipeline(gl_wrap_context* ctx, GLuint pipeline) {
	if(ctx->glBindProgramPipelineProc == NULL) {
		ctx->glBindProgramPipelineProc = (PFNGLBINDPROGRAMPIPELINEPROC)gl_wrap_get_pointer("glBindProgramPipeline");
	}
	ctx->glBindProgramPipelineProc(pipeline);
};
void gl_wrap_context_glDeleteProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines) {
	if(ctx->glDeleteProgramPipelinesProc == NULL) {
		ctx->glDeleteProgramPipelinesProc = (PFNGLDELETEPROGRAMPIPELINESPROC)gl_wrap_get_pointer("glDeleteProgramPipelines");
	}
	ctx->glDeleteProgramPipelinesProc(n, pipelines);
};
void gl_wrap_context_glGenProgramPipelines(gl_wrap_context* ctx, GLsizei n, GLuint* pipelines) {
	if(ctx->glGenProgramPipelinesProc == NULL) {
		ctx->glGenProgramPipelinesProc = (PFNGLGENPROGRAMPIPELINESPROC)gl_wrap_get_pointer("glGenProgramPipelines");
	}
	ctx->glGenProgramPipelinesProc(n, pipelines);
};
GLboolean gl_wrap_context_glIsProgramPipeline(gl_wrap_context* ctx, GLuint pipeline) {
	if(ctx->glIsProgramPipelineProc == NULL) {
		ctx->glIsProgramPipelineProc = (PFNGLISPROGRAMPIPELINEPROC)gl_wrap_get_pointer("glIsProgramPipeline");
	}
	return ctx->glIsProgramPipelineProc(pipeline);
};
void gl_wrap_context_glGetProgramPipelineiv(gl_wrap_context* ctx, GLuint pipeline, GLenum pname, GLint* params) {
	if(ctx->glGetProgramPipelineivProc == NULL) {
		ctx->glGetProgramPipelineivProc = (PFNGLGETPROGRAMPIPELINEIVPROC)gl_wrap_get_pointer("glGetProgramPipelineiv");
	}
	ctx->glGetProgramPipelineivProc(pipeline, pname, params);
};
void gl_wrap_context_glProgramUniform1i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0) {
	if(ctx->glProgramUniform1iProc == NULL) {
		ctx->glProgramUniform1iProc = (PFNGLPROGRAMUNIFORM1IPROC)gl_wrap_get_pointer("glProgramUniform1i");
	}
	ctx->glProgramUniform1iProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform1iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform1ivProc == NULL) {
		ctx->glProgramUniform1ivProc = (PFNGLPROGRAMUNIFORM1IVPROC)gl_wrap_get_pointer("glProgramUniform1iv");
	}
	ctx->glProgramUniform1ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform1f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0) {
	if(ctx->glProgramUniform1fProc == NULL) {
		ctx->glProgramUniform1fProc = (PFNGLPROGRAMUNIFORM1FPROC)gl_wrap_get_pointer("glProgramUniform1f");
	}
	ctx->glProgramUniform1fProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform1fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform1fvProc == NULL) {
		ctx->glProgramUniform1fvProc = (PFNGLPROGRAMUNIFORM1FVPROC)gl_wrap_get_pointer("glProgramUniform1fv");
	}
	ctx->glProgramUniform1fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform1d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0) {
	if(ctx->glProgramUniform1dProc == NULL) {
		ctx->glProgramUniform1dProc = (PFNGLPROGRAMUNIFORM1DPROC)gl_wrap_get_pointer("glProgramUniform1d");
	}
	ctx->glProgramUniform1dProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform1dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glProgramUniform1dvProc == NULL) {
		ctx->glProgramUniform1dvProc = (PFNGLPROGRAMUNIFORM1DVPROC)gl_wrap_get_pointer("glProgramUniform1dv");
	}
	ctx->glProgramUniform1dvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform1ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0) {
	if(ctx->glProgramUniform1uiProc == NULL) {
		ctx->glProgramUniform1uiProc = (PFNGLPROGRAMUNIFORM1UIPROC)gl_wrap_get_pointer("glProgramUniform1ui");
	}
	ctx->glProgramUniform1uiProc(program, location, v0);
};
void gl_wrap_context_glProgramUniform1uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform1uivProc == NULL) {
		ctx->glProgramUniform1uivProc = (PFNGLPROGRAMUNIFORM1UIVPROC)gl_wrap_get_pointer("glProgramUniform1uiv");
	}
	ctx->glProgramUniform1uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1) {
	if(ctx->glProgramUniform2iProc == NULL) {
		ctx->glProgramUniform2iProc = (PFNGLPROGRAMUNIFORM2IPROC)gl_wrap_get_pointer("glProgramUniform2i");
	}
	ctx->glProgramUniform2iProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform2iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform2ivProc == NULL) {
		ctx->glProgramUniform2ivProc = (PFNGLPROGRAMUNIFORM2IVPROC)gl_wrap_get_pointer("glProgramUniform2iv");
	}
	ctx->glProgramUniform2ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1) {
	if(ctx->glProgramUniform2fProc == NULL) {
		ctx->glProgramUniform2fProc = (PFNGLPROGRAMUNIFORM2FPROC)gl_wrap_get_pointer("glProgramUniform2f");
	}
	ctx->glProgramUniform2fProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform2fvProc == NULL) {
		ctx->glProgramUniform2fvProc = (PFNGLPROGRAMUNIFORM2FVPROC)gl_wrap_get_pointer("glProgramUniform2fv");
	}
	ctx->glProgramUniform2fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0, GLdouble v1) {
	if(ctx->glProgramUniform2dProc == NULL) {
		ctx->glProgramUniform2dProc = (PFNGLPROGRAMUNIFORM2DPROC)gl_wrap_get_pointer("glProgramUniform2d");
	}
	ctx->glProgramUniform2dProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glProgramUniform2dvProc == NULL) {
		ctx->glProgramUniform2dvProc = (PFNGLPROGRAMUNIFORM2DVPROC)gl_wrap_get_pointer("glProgramUniform2dv");
	}
	ctx->glProgramUniform2dvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform2ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1) {
	if(ctx->glProgramUniform2uiProc == NULL) {
		ctx->glProgramUniform2uiProc = (PFNGLPROGRAMUNIFORM2UIPROC)gl_wrap_get_pointer("glProgramUniform2ui");
	}
	ctx->glProgramUniform2uiProc(program, location, v0, v1);
};
void gl_wrap_context_glProgramUniform2uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform2uivProc == NULL) {
		ctx->glProgramUniform2uivProc = (PFNGLPROGRAMUNIFORM2UIVPROC)gl_wrap_get_pointer("glProgramUniform2uiv");
	}
	ctx->glProgramUniform2uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {
	if(ctx->glProgramUniform3iProc == NULL) {
		ctx->glProgramUniform3iProc = (PFNGLPROGRAMUNIFORM3IPROC)gl_wrap_get_pointer("glProgramUniform3i");
	}
	ctx->glProgramUniform3iProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform3iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform3ivProc == NULL) {
		ctx->glProgramUniform3ivProc = (PFNGLPROGRAMUNIFORM3IVPROC)gl_wrap_get_pointer("glProgramUniform3iv");
	}
	ctx->glProgramUniform3ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
	if(ctx->glProgramUniform3fProc == NULL) {
		ctx->glProgramUniform3fProc = (PFNGLPROGRAMUNIFORM3FPROC)gl_wrap_get_pointer("glProgramUniform3f");
	}
	ctx->glProgramUniform3fProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform3fvProc == NULL) {
		ctx->glProgramUniform3fvProc = (PFNGLPROGRAMUNIFORM3FVPROC)gl_wrap_get_pointer("glProgramUniform3fv");
	}
	ctx->glProgramUniform3fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) {
	if(ctx->glProgramUniform3dProc == NULL) {
		ctx->glProgramUniform3dProc = (PFNGLPROGRAMUNIFORM3DPROC)gl_wrap_get_pointer("glProgramUniform3d");
	}
	ctx->glProgramUniform3dProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glProgramUniform3dvProc == NULL) {
		ctx->glProgramUniform3dvProc = (PFNGLPROGRAMUNIFORM3DVPROC)gl_wrap_get_pointer("glProgramUniform3dv");
	}
	ctx->glProgramUniform3dvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform3ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {
	if(ctx->glProgramUniform3uiProc == NULL) {
		ctx->glProgramUniform3uiProc = (PFNGLPROGRAMUNIFORM3UIPROC)gl_wrap_get_pointer("glProgramUniform3ui");
	}
	ctx->glProgramUniform3uiProc(program, location, v0, v1, v2);
};
void gl_wrap_context_glProgramUniform3uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform3uivProc == NULL) {
		ctx->glProgramUniform3uivProc = (PFNGLPROGRAMUNIFORM3UIVPROC)gl_wrap_get_pointer("glProgramUniform3uiv");
	}
	ctx->glProgramUniform3uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4i(gl_wrap_context* ctx, GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
	if(ctx->glProgramUniform4iProc == NULL) {
		ctx->glProgramUniform4iProc = (PFNGLPROGRAMUNIFORM4IPROC)gl_wrap_get_pointer("glProgramUniform4i");
	}
	ctx->glProgramUniform4iProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform4iv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLint* value) {
	if(ctx->glProgramUniform4ivProc == NULL) {
		ctx->glProgramUniform4ivProc = (PFNGLPROGRAMUNIFORM4IVPROC)gl_wrap_get_pointer("glProgramUniform4iv");
	}
	ctx->glProgramUniform4ivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4f(gl_wrap_context* ctx, GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
	if(ctx->glProgramUniform4fProc == NULL) {
		ctx->glProgramUniform4fProc = (PFNGLPROGRAMUNIFORM4FPROC)gl_wrap_get_pointer("glProgramUniform4f");
	}
	ctx->glProgramUniform4fProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLfloat* value) {
	if(ctx->glProgramUniform4fvProc == NULL) {
		ctx->glProgramUniform4fvProc = (PFNGLPROGRAMUNIFORM4FVPROC)gl_wrap_get_pointer("glProgramUniform4fv");
	}
	ctx->glProgramUniform4fvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4d(gl_wrap_context* ctx, GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) {
	if(ctx->glProgramUniform4dProc == NULL) {
		ctx->glProgramUniform4dProc = (PFNGLPROGRAMUNIFORM4DPROC)gl_wrap_get_pointer("glProgramUniform4d");
	}
	ctx->glProgramUniform4dProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLdouble* value) {
	if(ctx->glProgramUniform4dvProc == NULL) {
		ctx->glProgramUniform4dvProc = (PFNGLPROGRAMUNIFORM4DVPROC)gl_wrap_get_pointer("glProgramUniform4dv");
	}
	ctx->glProgramUniform4dvProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniform4ui(gl_wrap_context* ctx, GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
	if(ctx->glProgramUniform4uiProc == NULL) {
		ctx->glProgramUniform4uiProc = (PFNGLPROGRAMUNIFORM4UIPROC)gl_wrap_get_pointer("glProgramUniform4ui");
	}
	ctx->glProgramUniform4uiProc(program, location, v0, v1, v2, v3);
};
void gl_wrap_context_glProgramUniform4uiv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLuint* value) {
	if(ctx->glProgramUniform4uivProc == NULL) {
		ctx->glProgramUniform4uivProc = (PFNGLPROGRAMUNIFORM4UIVPROC)gl_wrap_get_pointer("glProgramUniform4uiv");
	}
	ctx->glProgramUniform4uivProc(program, location, count, value);
};
void gl_wrap_context_glProgramUniformMatrix2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix2fvProc == NULL) {
		ctx->glProgramUniformMatrix2fvProc = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2fv");
	}
	ctx->glProgramUniformMatrix2fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix3fvProc == NULL) {
		ctx->glProgramUniformMatrix3fvProc = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3fv");
	}
	ctx->glProgramUniformMatrix3fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix4fvProc == NULL) {
		ctx->glProgramUniformMatrix4fvProc = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4fv");
	}
	ctx->glProgramUniformMatrix4fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix2dvProc == NULL) {
		ctx->glProgramUniformMatrix2dvProc = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2dv");
	}
	ctx->glProgramUniformMatrix2dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix3dvProc == NULL) {
		ctx->glProgramUniformMatrix3dvProc = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3dv");
	}
	ctx->glProgramUniformMatrix3dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix4dvProc == NULL) {
		ctx->glProgramUniformMatrix4dvProc = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4dv");
	}
	ctx->glProgramUniformMatrix4dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix2x3fvProc == NULL) {
		ctx->glProgramUniformMatrix2x3fvProc = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2x3fv");
	}
	ctx->glProgramUniformMatrix2x3fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix3x2fvProc == NULL) {
		ctx->glProgramUniformMatrix3x2fvProc = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3x2fv");
	}
	ctx->glProgramUniformMatrix3x2fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix2x4fvProc == NULL) {
		ctx->glProgramUniformMatrix2x4fvProc = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2x4fv");
	}
	ctx->glProgramUniformMatrix2x4fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4x2fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix4x2fvProc == NULL) {
		ctx->glProgramUniformMatrix4x2fvProc = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4x2fv");
	}
	ctx->glProgramUniformMatrix4x2fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3x4fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix3x4fvProc == NULL) {
		ctx->glProgramUniformMatrix3x4fvProc = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3x4fv");
	}
	ctx->glProgramUniformMatrix3x4fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4x3fv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat* value) {
	if(ctx->glProgramUniformMatrix4x3fvProc == NULL) {
		ctx->glProgramUniformMatrix4x3fvProc = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4x3fv");
	}
	ctx->glProgramUniformMatrix4x3fvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2x3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix2x3dvProc == NULL) {
		ctx->glProgramUniformMatrix2x3dvProc = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2x3dv");
	}
	ctx->glProgramUniformMatrix2x3dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3x2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix3x2dvProc == NULL) {
		ctx->glProgramUniformMatrix3x2dvProc = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3x2dv");
	}
	ctx->glProgramUniformMatrix3x2dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix2x4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix2x4dvProc == NULL) {
		ctx->glProgramUniformMatrix2x4dvProc = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix2x4dv");
	}
	ctx->glProgramUniformMatrix2x4dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4x2dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix4x2dvProc == NULL) {
		ctx->glProgramUniformMatrix4x2dvProc = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4x2dv");
	}
	ctx->glProgramUniformMatrix4x2dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix3x4dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix3x4dvProc == NULL) {
		ctx->glProgramUniformMatrix3x4dvProc = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix3x4dv");
	}
	ctx->glProgramUniformMatrix3x4dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glProgramUniformMatrix4x3dv(gl_wrap_context* ctx, GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble* value) {
	if(ctx->glProgramUniformMatrix4x3dvProc == NULL) {
		ctx->glProgramUniformMatrix4x3dvProc = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)gl_wrap_get_pointer("glProgramUniformMatrix4x3dv");
	}
	ctx->glProgramUniformMatrix4x3dvProc(program, location, count, transpose, value);
};
void gl_wrap_context_glValidateProgramPipeline(gl_wrap_context* ctx, GLuint pipeline) {
	if(ctx->glValidateProgramPipelineProc == NULL) {
		ctx->glValidateProgramPipelineProc = (PFNGLVALIDATEPROGRAMPIPELINEPROC)gl_wrap_get_pointer("glValidateProgramPipeline");
	}
	ctx->glValidateProgramPipelineProc(pipeline);
};
void gl_wrap_context_glGetProgramPipelineInfoLog(gl_wrap_context* ctx, GLuint pipeline, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
	if(ctx->glGetProgramPipelineInfoLogProc == NULL) {
		ctx->glGetProgramPipelineInfoLogProc = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)gl_wrap_get_pointer("glGetProgramPipelineInfoLog");
	}
	ctx->glGetProgramPipelineInfoLogProc(pipeline, bufSize, length, infoLog);
};
void gl_wrap_context_glVertexAttribL1d(gl_wrap_context* ctx, GLuint index, GLdouble x) {
	if(ctx->glVertexAttribL1dProc == NULL) {
		ctx->glVertexAttribL1dProc = (PFNGLVERTEXATTRIBL1DPROC)gl_wrap_get_pointer("glVertexAttribL1d");
	}
	ctx->glVertexAttribL1dProc(index, x);
};
void gl_wrap_context_glVertexAttribL2d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y) {
	if(ctx->glVertexAttribL2dProc == NULL) {
		ctx->glVertexAttribL2dProc = (PFNGLVERTEXATTRIBL2DPROC)gl_wrap_get_pointer("glVertexAttribL2d");
	}
	ctx->glVertexAttribL2dProc(index, x, y);
};
void gl_wrap_context_glVertexAttribL3d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z) {
	if(ctx->glVertexAttribL3dProc == NULL) {
		ctx->glVertexAttribL3dProc = (PFNGLVERTEXATTRIBL3DPROC)gl_wrap_get_pointer("glVertexAttribL3d");
	}
	ctx->glVertexAttribL3dProc(index, x, y, z);
};
void gl_wrap_context_glVertexAttribL4d(gl_wrap_context* ctx, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	if(ctx->glVertexAttribL4dProc == NULL) {
		ctx->glVertexAttribL4dProc = (PFNGLVERTEXATTRIBL4DPROC)gl_wrap_get_pointer("glVertexAttribL4d");
	}
	ctx->glVertexAttribL4dProc(index, x, y, z, w);
};
void gl_wrap_context_glVertexAttribL1dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttribL1dvProc == NULL) {
		ctx->glVertexAttribL1dvProc = (PFNGLVERTEXATTRIBL1DVPROC)gl_wrap_get_pointer("glVertexAttribL1dv");
	}
	ctx->glVertexAttribL1dvProc(index, v);
};
void gl_wrap_context_glVertexAttribL2dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttribL2dvProc == NULL) {
		ctx->glVertexAttribL2dvProc = (PFNGLVERTEXATTRIBL2DVPROC)gl_wrap_get_pointer("glVertexAttribL2dv");
	}
	ctx->glVertexAttribL2dvProc(index, v);
};
void gl_wrap_context_glVertexAttribL3dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttribL3dvProc == NULL) {
		ctx->glVertexAttribL3dvProc = (PFNGLVERTEXATTRIBL3DVPROC)gl_wrap_get_pointer("glVertexAttribL3dv");
	}
	ctx->glVertexAttribL3dvProc(index, v);
};
void gl_wrap_context_glVertexAttribL4dv(gl_wrap_context* ctx, GLuint index, GLdouble* v) {
	if(ctx->glVertexAttribL4dvProc == NULL) {
		ctx->glVertexAttribL4dvProc = (PFNGLVERTEXATTRIBL4DVPROC)gl_wrap_get_pointer("glVertexAttribL4dv");
	}
	ctx->glVertexAttribL4dvProc(index, v);
};
void gl_wrap_context_glVertexAttribLPointer(gl_wrap_context* ctx, GLuint index, GLint size, GLenum type, GLsizei stride, void* pointer) {
	if(ctx->glVertexAttribLPointerProc == NULL) {
		ctx->glVertexAttribLPointerProc = (PFNGLVERTEXATTRIBLPOINTERPROC)gl_wrap_get_pointer("glVertexAttribLPointer");
	}
	ctx->glVertexAttribLPointerProc(index, size, type, stride, pointer);
};
void gl_wrap_context_glGetVertexAttribLdv(gl_wrap_context* ctx, GLuint index, GLenum pname, GLdouble* params) {
	if(ctx->glGetVertexAttribLdvProc == NULL) {
		ctx->glGetVertexAttribLdvProc = (PFNGLGETVERTEXATTRIBLDVPROC)gl_wrap_get_pointer("glGetVertexAttribLdv");
	}
	ctx->glGetVertexAttribLdvProc(index, pname, params);
};
void gl_wrap_context_glViewportArrayv(gl_wrap_context* ctx, GLuint first, GLsizei count, GLfloat* v) {
	if(ctx->glViewportArrayvProc == NULL) {
		ctx->glViewportArrayvProc = (PFNGLVIEWPORTARRAYVPROC)gl_wrap_get_pointer("glViewportArrayv");
	}
	ctx->glViewportArrayvProc(first, count, v);
};
void gl_wrap_context_glViewportIndexedf(gl_wrap_context* ctx, GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
	if(ctx->glViewportIndexedfProc == NULL) {
		ctx->glViewportIndexedfProc = (PFNGLVIEWPORTINDEXEDFPROC)gl_wrap_get_pointer("glViewportIndexedf");
	}
	ctx->glViewportIndexedfProc(index, x, y, w, h);
};
void gl_wrap_context_glViewportIndexedfv(gl_wrap_context* ctx, GLuint index, GLfloat* v) {
	if(ctx->glViewportIndexedfvProc == NULL) {
		ctx->glViewportIndexedfvProc = (PFNGLVIEWPORTINDEXEDFVPROC)gl_wrap_get_pointer("glViewportIndexedfv");
	}
	ctx->glViewportIndexedfvProc(index, v);
};
void gl_wrap_context_glScissorArrayv(gl_wrap_context* ctx, GLuint first, GLsizei count, GLint* v) {
	if(ctx->glScissorArrayvProc == NULL) {
		ctx->glScissorArrayvProc = (PFNGLSCISSORARRAYVPROC)gl_wrap_get_pointer("glScissorArrayv");
	}
	ctx->glScissorArrayvProc(first, count, v);
};
void gl_wrap_context_glScissorIndexed(gl_wrap_context* ctx, GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) {
	if(ctx->glScissorIndexedProc == NULL) {
		ctx->glScissorIndexedProc = (PFNGLSCISSORINDEXEDPROC)gl_wrap_get_pointer("glScissorIndexed");
	}
	ctx->glScissorIndexedProc(index, left, bottom, width, height);
};
void gl_wrap_context_glScissorIndexedv(gl_wrap_context* ctx, GLuint index, GLint* v) {
	if(ctx->glScissorIndexedvProc == NULL) {
		ctx->glScissorIndexedvProc = (PFNGLSCISSORINDEXEDVPROC)gl_wrap_get_pointer("glScissorIndexedv");
	}
	ctx->glScissorIndexedvProc(index, v);
};
void gl_wrap_context_glDepthRangeArrayv(gl_wrap_context* ctx, GLuint first, GLsizei count, GLdouble* v) {
	if(ctx->glDepthRangeArrayvProc == NULL) {
		ctx->glDepthRangeArrayvProc = (PFNGLDEPTHRANGEARRAYVPROC)gl_wrap_get_pointer("glDepthRangeArrayv");
	}
	ctx->glDepthRangeArrayvProc(first, count, v);
};
void gl_wrap_context_glDepthRangeIndexed(gl_wrap_context* ctx, GLuint index, GLdouble n, GLdouble f) {
	if(ctx->glDepthRangeIndexedProc == NULL) {
		ctx->glDepthRangeIndexedProc = (PFNGLDEPTHRANGEINDEXEDPROC)gl_wrap_get_pointer("glDepthRangeIndexed");
	}
	ctx->glDepthRangeIndexedProc(index, n, f);
};
void gl_wrap_context_glGetFloati_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLfloat* data) {
	if(ctx->glGetFloati_vProc == NULL) {
		ctx->glGetFloati_vProc = (PFNGLGETFLOATI_VPROC)gl_wrap_get_pointer("glGetFloati_v");
	}
	ctx->glGetFloati_vProc(target, index, data);
};
void gl_wrap_context_glGetDoublei_v(gl_wrap_context* ctx, GLenum target, GLuint index, GLdouble* data) {
	if(ctx->glGetDoublei_vProc == NULL) {
		ctx->glGetDoublei_vProc = (PFNGLGETDOUBLEI_VPROC)gl_wrap_get_pointer("glGetDoublei_v");
	}
	ctx->glGetDoublei_vProc(target, index, data);
};
void gl_wrap_context_glDrawArraysInstancedBaseInstance(gl_wrap_context* ctx, GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) {
	if(ctx->glDrawArraysInstancedBaseInstanceProc == NULL) {
		ctx->glDrawArraysInstancedBaseInstanceProc = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)gl_wrap_get_pointer("glDrawArraysInstancedBaseInstance");
	}
	ctx->glDrawArraysInstancedBaseInstanceProc(mode, first, count, instancecount, baseinstance);
};
void gl_wrap_context_glDrawElementsInstancedBaseInstance(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount, GLuint baseinstance) {
	if(ctx->glDrawElementsInstancedBaseInstanceProc == NULL) {
		ctx->glDrawElementsInstancedBaseInstanceProc = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)gl_wrap_get_pointer("glDrawElementsInstancedBaseInstance");
	}
	ctx->glDrawElementsInstancedBaseInstanceProc(mode, count, type, indices, instancecount, baseinstance);
};
void gl_wrap_context_glDrawElementsInstancedBaseVertexBaseInstance(gl_wrap_context* ctx, GLenum mode, GLsizei count, GLenum type, void* indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) {
	if(ctx->glDrawElementsInstancedBaseVertexBaseInstanceProc == NULL) {
		ctx->glDrawElementsInstancedBaseVertexBaseInstanceProc = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)gl_wrap_get_pointer("glDrawElementsInstancedBaseVertexBaseInstance");
	}
	ctx->glDrawElementsInstancedBaseVertexBaseInstanceProc(mode, count, type, indices, instancecount, basevertex, baseinstance);
};
void gl_wrap_context_glGetInternalformativ(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params) {
	if(ctx->glGetInternalformativProc == NULL) {
		ctx->glGetInternalformativProc = (PFNGLGETINTERNALFORMATIVPROC)gl_wrap_get_pointer("glGetInternalformativ");
	}
	ctx->glGetInternalformativProc(target, internalformat, pname, bufSize, params);
};
void gl_wrap_context_glGetActiveAtomicCounterBufferiv(gl_wrap_context* ctx, GLuint program, GLuint bufferIndex, GLenum pname, GLint* params) {
	if(ctx->glGetActiveAtomicCounterBufferivProc == NULL) {
		ctx->glGetActiveAtomicCounterBufferivProc = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)gl_wrap_get_pointer("glGetActiveAtomicCounterBufferiv");
	}
	ctx->glGetActiveAtomicCounterBufferivProc(program, bufferIndex, pname, params);
};
void gl_wrap_context_glBindImageTexture(gl_wrap_context* ctx, GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {
	if(ctx->glBindImageTextureProc == NULL) {
		ctx->glBindImageTextureProc = (PFNGLBINDIMAGETEXTUREPROC)gl_wrap_get_pointer("glBindImageTexture");
	}
	ctx->glBindImageTextureProc(unit, texture, level, layered, layer, access, format);
};
void gl_wrap_context_glMemoryBarrier(gl_wrap_context* ctx, GLbitfield barriers) {
	if(ctx->glMemoryBarrierProc == NULL) {
		ctx->glMemoryBarrierProc = (PFNGLMEMORYBARRIERPROC)gl_wrap_get_pointer("glMemoryBarrier");
	}
	ctx->glMemoryBarrierProc(barriers);
};
void gl_wrap_context_glTexStorage1D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) {
	if(ctx->glTexStorage1DProc == NULL) {
		ctx->glTexStorage1DProc = (PFNGLTEXSTORAGE1DPROC)gl_wrap_get_pointer("glTexStorage1D");
	}
	ctx->glTexStorage1DProc(target, levels, internalformat, width);
};
void gl_wrap_context_glTexStorage2D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
	if(ctx->glTexStorage2DProc == NULL) {
		ctx->glTexStorage2DProc = (PFNGLTEXSTORAGE2DPROC)gl_wrap_get_pointer("glTexStorage2D");
	}
	ctx->glTexStorage2DProc(target, levels, internalformat, width, height);
};
void gl_wrap_context_glTexStorage3D(gl_wrap_context* ctx, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
	if(ctx->glTexStorage3DProc == NULL) {
		ctx->glTexStorage3DProc = (PFNGLTEXSTORAGE3DPROC)gl_wrap_get_pointer("glTexStorage3D");
	}
	ctx->glTexStorage3DProc(target, levels, internalformat, width, height, depth);
};
void gl_wrap_context_glDrawTransformFeedbackInstanced(gl_wrap_context* ctx, GLenum mode, GLuint id, GLsizei instancecount) {
	if(ctx->glDrawTransformFeedbackInstancedProc == NULL) {
		ctx->glDrawTransformFeedbackInstancedProc = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)gl_wrap_get_pointer("glDrawTransformFeedbackInstanced");
	}
	ctx->glDrawTransformFeedbackInstancedProc(mode, id, instancecount);
};
void gl_wrap_context_glDrawTransformFeedbackStreamInstanced(gl_wrap_context* ctx, GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) {
	if(ctx->glDrawTransformFeedbackStreamInstancedProc == NULL) {
		ctx->glDrawTransformFeedbackStreamInstancedProc = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)gl_wrap_get_pointer("glDrawTransformFeedbackStreamInstanced");
	}
	ctx->glDrawTransformFeedbackStreamInstancedProc(mode, id, stream, instancecount);
};
void gl_wrap_context_glClearBufferData(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum format, GLenum type, void* data) {
	if(ctx->glClearBufferDataProc == NULL) {
		ctx->glClearBufferDataProc = (PFNGLCLEARBUFFERDATAPROC)gl_wrap_get_pointer("glClearBufferData");
	}
	ctx->glClearBufferDataProc(target, internalformat, format, type, data);
};
void gl_wrap_context_glClearBufferSubData(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, void* data) {
	if(ctx->glClearBufferSubDataProc == NULL) {
		ctx->glClearBufferSubDataProc = (PFNGLCLEARBUFFERSUBDATAPROC)gl_wrap_get_pointer("glClearBufferSubData");
	}
	ctx->glClearBufferSubDataProc(target, internalformat, offset, size, format, type, data);
};
void gl_wrap_context_glDispatchCompute(gl_wrap_context* ctx, GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {
	if(ctx->glDispatchComputeProc == NULL) {
		ctx->glDispatchComputeProc = (PFNGLDISPATCHCOMPUTEPROC)gl_wrap_get_pointer("glDispatchCompute");
	}
	ctx->glDispatchComputeProc(num_groups_x, num_groups_y, num_groups_z);
};
void gl_wrap_context_glDispatchComputeIndirect(gl_wrap_context* ctx, GLintptr indirect) {
	if(ctx->glDispatchComputeIndirectProc == NULL) {
		ctx->glDispatchComputeIndirectProc = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)gl_wrap_get_pointer("glDispatchComputeIndirect");
	}
	ctx->glDispatchComputeIndirectProc(indirect);
};
void gl_wrap_context_glCopyImageSubData(gl_wrap_context* ctx, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) {
	if(ctx->glCopyImageSubDataProc == NULL) {
		ctx->glCopyImageSubDataProc = (PFNGLCOPYIMAGESUBDATAPROC)gl_wrap_get_pointer("glCopyImageSubData");
	}
	ctx->glCopyImageSubDataProc(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
};
void gl_wrap_context_glFramebufferParameteri(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint param) {
	if(ctx->glFramebufferParameteriProc == NULL) {
		ctx->glFramebufferParameteriProc = (PFNGLFRAMEBUFFERPARAMETERIPROC)gl_wrap_get_pointer("glFramebufferParameteri");
	}
	ctx->glFramebufferParameteriProc(target, pname, param);
};
void gl_wrap_context_glGetFramebufferParameteriv(gl_wrap_context* ctx, GLenum target, GLenum pname, GLint* params) {
	if(ctx->glGetFramebufferParameterivProc == NULL) {
		ctx->glGetFramebufferParameterivProc = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)gl_wrap_get_pointer("glGetFramebufferParameteriv");
	}
	ctx->glGetFramebufferParameterivProc(target, pname, params);
};
void gl_wrap_context_glGetInternalformati64v(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64* params) {
	if(ctx->glGetInternalformati64vProc == NULL) {
		ctx->glGetInternalformati64vProc = (PFNGLGETINTERNALFORMATI64VPROC)gl_wrap_get_pointer("glGetInternalformati64v");
	}
	ctx->glGetInternalformati64vProc(target, internalformat, pname, bufSize, params);
};
void gl_wrap_context_glInvalidateTexSubImage(gl_wrap_context* ctx, GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) {
	if(ctx->glInvalidateTexSubImageProc == NULL) {
		ctx->glInvalidateTexSubImageProc = (PFNGLINVALIDATETEXSUBIMAGEPROC)gl_wrap_get_pointer("glInvalidateTexSubImage");
	}
	ctx->glInvalidateTexSubImageProc(texture, level, xoffset, yoffset, zoffset, width, height, depth);
};
void gl_wrap_context_glInvalidateTexImage(gl_wrap_context* ctx, GLuint texture, GLint level) {
	if(ctx->glInvalidateTexImageProc == NULL) {
		ctx->glInvalidateTexImageProc = (PFNGLINVALIDATETEXIMAGEPROC)gl_wrap_get_pointer("glInvalidateTexImage");
	}
	ctx->glInvalidateTexImageProc(texture, level);
};
void gl_wrap_context_glInvalidateBufferSubData(gl_wrap_context* ctx, GLuint buffer, GLintptr offset, GLsizeiptr length) {
	if(ctx->glInvalidateBufferSubDataProc == NULL) {
		ctx->glInvalidateBufferSubDataProc = (PFNGLINVALIDATEBUFFERSUBDATAPROC)gl_wrap_get_pointer("glInvalidateBufferSubData");
	}
	ctx->glInvalidateBufferSubDataProc(buffer, offset, length);
};
void gl_wrap_context_glInvalidateBufferData(gl_wrap_context* ctx, GLuint buffer) {
	if(ctx->glInvalidateBufferDataProc == NULL) {
		ctx->glInvalidateBufferDataProc = (PFNGLINVALIDATEBUFFERDATAPROC)gl_wrap_get_pointer("glInvalidateBufferData");
	}
	ctx->glInvalidateBufferDataProc(buffer);
};
void gl_wrap_context_glInvalidateFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments) {
	if(ctx->glInvalidateFramebufferProc == NULL) {
		ctx->glInvalidateFramebufferProc = (PFNGLINVALIDATEFRAMEBUFFERPROC)gl_wrap_get_pointer("glInvalidateFramebuffer");
	}
	ctx->glInvalidateFramebufferProc(target, numAttachments, attachments);
};
void gl_wrap_context_glInvalidateSubFramebuffer(gl_wrap_context* ctx, GLenum target, GLsizei numAttachments, GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height) {
	if(ctx->glInvalidateSubFramebufferProc == NULL) {
		ctx->glInvalidateSubFramebufferProc = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)gl_wrap_get_pointer("glInvalidateSubFramebuffer");
	}
	ctx->glInvalidateSubFramebufferProc(target, numAttachments, attachments, x, y, width, height);
};
void gl_wrap_context_glMultiDrawArraysIndirect(gl_wrap_context* ctx, GLenum mode, void* indirect, GLsizei drawcount, GLsizei stride) {
	if(ctx->glMultiDrawArraysIndirectProc == NULL) {
		ctx->glMultiDrawArraysIndirectProc = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)gl_wrap_get_pointer("glMultiDrawArraysIndirect");
	}
	ctx->glMultiDrawArraysIndirectProc(mode, indirect, drawcount, stride);
};
void gl_wrap_context_glMultiDrawElementsIndirect(gl_wrap_context* ctx, GLenum mode, GLenum type, void* indirect, GLsizei drawcount, GLsizei stride) {
	if(ctx->glMultiDrawElementsIndirectProc == NULL) {
		ctx->glMultiDrawElementsIndirectProc = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)gl_wrap_get_pointer("glMultiDrawElementsIndirect");
	}
	ctx->glMultiDrawElementsIndirectProc(mode, type, indirect, drawcount, stride);
};
void gl_wrap_context_glGetProgramInterfaceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLenum pname, GLint* params) {
	if(ctx->glGetProgramInterfaceivProc == NULL) {
		ctx->glGetProgramInterfaceivProc = (PFNGLGETPROGRAMINTERFACEIVPROC)gl_wrap_get_pointer("glGetProgramInterfaceiv");
	}
	ctx->glGetProgramInterfaceivProc(program, programInterface, pname, params);
};
GLuint gl_wrap_context_glGetProgramResourceIndex(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name) {
	if(ctx->glGetProgramResourceIndexProc == NULL) {
		ctx->glGetProgramResourceIndexProc = (PFNGLGETPROGRAMRESOURCEINDEXPROC)gl_wrap_get_pointer("glGetProgramResourceIndex");
	}
	return ctx->glGetProgramResourceIndexProc(program, programInterface, name);
};
void gl_wrap_context_glGetProgramResourceName(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei* length, GLchar* name) {
	if(ctx->glGetProgramResourceNameProc == NULL) {
		ctx->glGetProgramResourceNameProc = (PFNGLGETPROGRAMRESOURCENAMEPROC)gl_wrap_get_pointer("glGetProgramResourceName");
	}
	ctx->glGetProgramResourceNameProc(program, programInterface, index, bufSize, length, name);
};
void gl_wrap_context_glGetProgramResourceiv(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, GLenum* props, GLsizei bufSize, GLsizei* length, GLint* params) {
	if(ctx->glGetProgramResourceivProc == NULL) {
		ctx->glGetProgramResourceivProc = (PFNGLGETPROGRAMRESOURCEIVPROC)gl_wrap_get_pointer("glGetProgramResourceiv");
	}
	ctx->glGetProgramResourceivProc(program, programInterface, index, propCount, props, bufSize, length, params);
};
GLint gl_wrap_context_glGetProgramResourceLocation(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name) {
	if(ctx->glGetProgramResourceLocationProc == NULL) {
		ctx->glGetProgramResourceLocationProc = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)gl_wrap_get_pointer("glGetProgramResourceLocation");
	}
	return ctx->glGetProgramResourceLocationProc(program, programInterface, name);
};
GLint gl_wrap_context_glGetProgramResourceLocationIndex(gl_wrap_context* ctx, GLuint program, GLenum programInterface, GLchar* name) {
	if(ctx->glGetProgramResourceLocationIndexProc == NULL) {
		ctx->glGetProgramResourceLocationIndexProc = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)gl_wrap_get_pointer("glGetProgramResourceLocationIndex");
	}
	return ctx->glGetProgramResourceLocationIndexProc(program, programInterface, name);
};
void gl_wrap_context_glShaderStorageBlockBinding(gl_wrap_context* ctx, GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) {
	if(ctx->glShaderStorageBlockBindingProc == NULL) {
		ctx->glShaderStorageBlockBindingProc = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)gl_wrap_get_pointer("glShaderStorageBlockBinding");
	}
	ctx->glShaderStorageBlockBindingProc(program, storageBlockIndex, storageBlockBinding);
};
void gl_wrap_context_glTexBufferRange(gl_wrap_context* ctx, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {
	if(ctx->glTexBufferRangeProc == NULL) {
		ctx->glTexBufferRangeProc = (PFNGLTEXBUFFERRANGEPROC)gl_wrap_get_pointer("glTexBufferRange");
	}
	ctx->glTexBufferRangeProc(target, internalformat, buffer, offset, size);
};
void gl_wrap_context_glTexStorage2DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
	if(ctx->glTexStorage2DMultisampleProc == NULL) {
		ctx->glTexStorage2DMultisampleProc = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)gl_wrap_get_pointer("glTexStorage2DMultisample");
	}
	ctx->glTexStorage2DMultisampleProc(target, samples, internalformat, width, height, fixedsamplelocations);
};
void gl_wrap_context_glTexStorage3DMultisample(gl_wrap_context* ctx, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
	if(ctx->glTexStorage3DMultisampleProc == NULL) {
		ctx->glTexStorage3DMultisampleProc = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)gl_wrap_get_pointer("glTexStorage3DMultisample");
	}
	ctx->glTexStorage3DMultisampleProc(target, samples, internalformat, width, height, depth, fixedsamplelocations);
};
void gl_wrap_context_glTextureView(gl_wrap_context* ctx, GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) {
	if(ctx->glTextureViewProc == NULL) {
		ctx->glTextureViewProc = (PFNGLTEXTUREVIEWPROC)gl_wrap_get_pointer("glTextureView");
	}
	ctx->glTextureViewProc(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
};
void gl_wrap_context_glBindVertexBuffer(gl_wrap_context* ctx, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
	if(ctx->glBindVertexBufferProc == NULL) {
		ctx->glBindVertexBufferProc = (PFNGLBINDVERTEXBUFFERPROC)gl_wrap_get_pointer("glBindVertexBuffer");
	}
	ctx->glBindVertexBufferProc(bindingindex, buffer, offset, stride);
};
void gl_wrap_context_glVertexAttribFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {
	if(ctx->glVertexAttribFormatProc == NULL) {
		ctx->glVertexAttribFormatProc = (PFNGLVERTEXATTRIBFORMATPROC)gl_wrap_get_pointer("glVertexAttribFormat");
	}
	ctx->glVertexAttribFormatProc(attribindex, size, type, normalized, relativeoffset);
};
void gl_wrap_context_glVertexAttribIFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
	if(ctx->glVertexAttribIFormatProc == NULL) {
		ctx->glVertexAttribIFormatProc = (PFNGLVERTEXATTRIBIFORMATPROC)gl_wrap_get_pointer("glVertexAttribIFormat");
	}
	ctx->glVertexAttribIFormatProc(attribindex, size, type, relativeoffset);
};
void gl_wrap_context_glVertexAttribLFormat(gl_wrap_context* ctx, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
	if(ctx->glVertexAttribLFormatProc == NULL) {
		ctx->glVertexAttribLFormatProc = (PFNGLVERTEXATTRIBLFORMATPROC)gl_wrap_get_pointer("glVertexAttribLFormat");
	}
	ctx->glVertexAttribLFormatProc(attribindex, size, type, relativeoffset);
};
void gl_wrap_context_glVertexAttribBinding(gl_wrap_context* ctx, GLuint attribindex, GLuint bindingindex) {
	if(ctx->glVertexAttribBindingProc == NULL) {
		ctx->glVertexAttribBindingProc = (PFNGLVERTEXATTRIBBINDINGPROC)gl_wrap_get_pointer("glVertexAttribBinding");
	}
	ctx->glVertexAttribBindingProc(attribindex, bindingindex);
};
void gl_wrap_context_glVertexBindingDivisor(gl_wrap_context* ctx, GLuint bindingindex, GLuint divisor) {
	if(ctx->glVertexBindingDivisorProc == NULL) {
		ctx->glVertexBindingDivisorProc = (PFNGLVERTEXBINDINGDIVISORPROC)gl_wrap_get_pointer("glVertexBindingDivisor");
	}
	ctx->glVertexBindingDivisorProc(bindingindex, divisor);
};
void gl_wrap_context_glDebugMessageControl(gl_wrap_context* ctx, GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint* ids, GLboolean enabled) {
	if(ctx->glDebugMessageControlProc == NULL) {
		ctx->glDebugMessageControlProc = (PFNGLDEBUGMESSAGECONTROLPROC)gl_wrap_get_pointer("glDebugMessageControl");
	}
	ctx->glDebugMessageControlProc(source, type, severity, count, ids, enabled);
};
void gl_wrap_context_glDebugMessageInsert(gl_wrap_context* ctx, GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar* buf) {
	if(ctx->glDebugMessageInsertProc == NULL) {
		ctx->glDebugMessageInsertProc = (PFNGLDEBUGMESSAGEINSERTPROC)gl_wrap_get_pointer("glDebugMessageInsert");
	}
	ctx->glDebugMessageInsertProc(source, type, id, severity, length, buf);
};
void gl_wrap_context_glDebugMessageCallback(gl_wrap_context* ctx, GLDEBUGPROC callback, void* userParam) {
	if(ctx->glDebugMessageCallbackProc == NULL) {
		ctx->glDebugMessageCallbackProc = (PFNGLDEBUGMESSAGECALLBACKPROC)gl_wrap_get_pointer("glDebugMessageCallback");
	}
	ctx->glDebugMessageCallbackProc(callback, userParam);
};
GLuint gl_wrap_context_glGetDebugMessageLog(gl_wrap_context* ctx, GLuint count, GLsizei bufSize, GLenum* sources, GLenum* types, GLuint* ids, GLenum* severities, GLsizei* lengths, GLchar* messageLog) {
	if(ctx->glGetDebugMessageLogProc == NULL) {
		ctx->glGetDebugMessageLogProc = (PFNGLGETDEBUGMESSAGELOGPROC)gl_wrap_get_pointer("glGetDebugMessageLog");
	}
	return ctx->glGetDebugMessageLogProc(count, bufSize, sources, types, ids, severities, lengths, messageLog);
};
void gl_wrap_context_glPushDebugGroup(gl_wrap_context* ctx, GLenum source, GLuint id, GLsizei length, GLchar* message) {
	if(ctx->glPushDebugGroupProc == NULL) {
		ctx->glPushDebugGroupProc = (PFNGLPUSHDEBUGGROUPPROC)gl_wrap_get_pointer("glPushDebugGroup");
	}
	ctx->glPushDebugGroupProc(source, id, length, message);
};
void gl_wrap_context_glPopDebugGroup(gl_wrap_context* ctx) {
	if(ctx->glPopDebugGroupProc == NULL) {
		ctx->glPopDebugGroupProc = (PFNGLPOPDEBUGGROUPPROC)gl_wrap_get_pointer("glPopDebugGroup");
	}
	ctx->glPopDebugGroupProc();
};
void gl_wrap_context_glObjectLabel(gl_wrap_context* ctx, GLenum identifier, GLuint name, GLsizei length, GLchar* label) {
	if(ctx->glObjectLabelProc == NULL) {
		ctx->glObjectLabelProc = (PFNGLOBJECTLABELPROC)gl_wrap_get_pointer("glObjectLabel");
	}
	ctx->glObjectLabelProc(identifier, name, length, label);
};
void gl_wrap_context_glGetObjectLabel(gl_wrap_context* ctx, GLenum identifier, GLuint name, GLsizei bufSize, GLsizei* length, GLchar* label) {
	if(ctx->glGetObjectLabelProc == NULL) {
		ctx->glGetObjectLabelProc = (PFNGLGETOBJECTLABELPROC)gl_wrap_get_pointer("glGetObjectLabel");
	}
	ctx->glGetObjectLabelProc(identifier, name, bufSize, length, label);
};
void gl_wrap_context_glObjectPtrLabel(gl_wrap_context* ctx, void* ptr, GLsizei length, GLchar* label) {
	if(ctx->glObjectPtrLabelProc == NULL) {
		ctx->glObjectPtrLabelProc = (PFNGLOBJECTPTRLABELPROC)gl_wrap_get_pointer("glObjectPtrLabel");
	}
	ctx->glObjectPtrLabelProc(ptr, length, label);
};
void gl_wrap_context_glGetObjectPtrLabel(gl_wrap_context* ctx, void* ptr, GLsizei bufSize, GLsizei* length, GLchar* label) {
	if(ctx->glGetObjectPtrLabelProc == NULL) {
		ctx->glGetObjectPtrLabelProc = (PFNGLGETOBJECTPTRLABELPROC)gl_wrap_get_pointer("glGetObjectPtrLabel");
	}
	ctx->glGetObjectPtrLabelProc(ptr, bufSize, length, label);
};
void gl_wrap_context_glBufferStorage(gl_wrap_context* ctx, GLenum target, GLsizeiptr size, void* data, GLbitfield flags) {
	if(ctx->glBufferStorageProc == NULL) {
		ctx->glBufferStorageProc = (PFNGLBUFFERSTORAGEPROC)gl_wrap_get_pointer("glBufferStorage");
	}
	ctx->glBufferStorageProc(target, size, data, flags);
};
void gl_wrap_context_glClearTexImage(gl_wrap_context* ctx, GLuint texture, GLint level, GLenum format, GLenum type, void* data) {
	if(ctx->glClearTexImageProc == NULL) {
		ctx->glClearTexImageProc = (PFNGLCLEARTEXIMAGEPROC)gl_wrap_get_pointer("glClearTexImage");
	}
	ctx->glClearTexImageProc(texture, level, format, type, data);
};
void gl_wrap_context_glClearTexSubImage(gl_wrap_context* ctx, GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, void* data) {
	if(ctx->glClearTexSubImageProc == NULL) {
		ctx->glClearTexSubImageProc = (PFNGLCLEARTEXSUBIMAGEPROC)gl_wrap_get_pointer("glClearTexSubImage");
	}
	ctx->glClearTexSubImageProc(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
};
void gl_wrap_context_glBindBuffersBase(gl_wrap_context* ctx, GLenum target, GLuint first, GLsizei count, GLuint* buffers) {
	if(ctx->glBindBuffersBaseProc == NULL) {
		ctx->glBindBuffersBaseProc = (PFNGLBINDBUFFERSBASEPROC)gl_wrap_get_pointer("glBindBuffersBase");
	}
	ctx->glBindBuffersBaseProc(target, first, count, buffers);
};
void gl_wrap_context_glBindBuffersRange(gl_wrap_context* ctx, GLenum target, GLuint first, GLsizei count, GLuint* buffers, GLintptr* offsets, GLsizeiptr* sizes) {
	if(ctx->glBindBuffersRangeProc == NULL) {
		ctx->glBindBuffersRangeProc = (PFNGLBINDBUFFERSRANGEPROC)gl_wrap_get_pointer("glBindBuffersRange");
	}
	ctx->glBindBuffersRangeProc(target, first, count, buffers, offsets, sizes);
};
void gl_wrap_context_glBindTextures(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* textures) {
	if(ctx->glBindTexturesProc == NULL) {
		ctx->glBindTexturesProc = (PFNGLBINDTEXTURESPROC)gl_wrap_get_pointer("glBindTextures");
	}
	ctx->glBindTexturesProc(first, count, textures);
};
void gl_wrap_context_glBindSamplers(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* samplers) {
	if(ctx->glBindSamplersProc == NULL) {
		ctx->glBindSamplersProc = (PFNGLBINDSAMPLERSPROC)gl_wrap_get_pointer("glBindSamplers");
	}
	ctx->glBindSamplersProc(first, count, samplers);
};
void gl_wrap_context_glBindImageTextures(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* textures) {
	if(ctx->glBindImageTexturesProc == NULL) {
		ctx->glBindImageTexturesProc = (PFNGLBINDIMAGETEXTURESPROC)gl_wrap_get_pointer("glBindImageTextures");
	}
	ctx->glBindImageTexturesProc(first, count, textures);
};
void gl_wrap_context_glBindVertexBuffers(gl_wrap_context* ctx, GLuint first, GLsizei count, GLuint* buffers, GLintptr* offsets, GLsizei* strides) {
	if(ctx->glBindVertexBuffersProc == NULL) {
		ctx->glBindVertexBuffersProc = (PFNGLBINDVERTEXBUFFERSPROC)gl_wrap_get_pointer("glBindVertexBuffers");
	}
	ctx->glBindVertexBuffersProc(first, count, buffers, offsets, strides);
};



// Handler functions are defined for each OpenGL call; each handler function
// takes the OpenGL context struct and a pointer to the same OpenGL function's
// arguments stored in a struct.
//
// Each handler function is responsible for invoking the OpenGL function with
// the proper parameters.
//
// All function handlers are placed with respect to order in the defined jump
// table (see below), which allows batched OpenGL calls to be made without
// using a large (and costly) switch statement.
//
// Handler functions are not defined for OpenGL functions which return any
// value, as these function calls cannot be batched (see the Go documentation
// for this package, which explains this in more detail).
inline void gl_wrap_handler_glCullFace(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCullFace_args args = *(gl_wrap_handler_glCullFace_args*)argsPtr;
	gl_wrap_context_glCullFace(ctx, args.mode);
}

inline void gl_wrap_handler_glFrontFace(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFrontFace_args args = *(gl_wrap_handler_glFrontFace_args*)argsPtr;
	gl_wrap_context_glFrontFace(ctx, args.mode);
}

inline void gl_wrap_handler_glHint(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glHint_args args = *(gl_wrap_handler_glHint_args*)argsPtr;
	gl_wrap_context_glHint(ctx, args.target, args.mode);
}

inline void gl_wrap_handler_glLineWidth(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLineWidth_args args = *(gl_wrap_handler_glLineWidth_args*)argsPtr;
	gl_wrap_context_glLineWidth(ctx, args.width);
}

inline void gl_wrap_handler_glPointSize(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPointSize_args args = *(gl_wrap_handler_glPointSize_args*)argsPtr;
	gl_wrap_context_glPointSize(ctx, args.size);
}

inline void gl_wrap_handler_glPolygonMode(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPolygonMode_args args = *(gl_wrap_handler_glPolygonMode_args*)argsPtr;
	gl_wrap_context_glPolygonMode(ctx, args.face, args.mode);
}

inline void gl_wrap_handler_glScissor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScissor_args args = *(gl_wrap_handler_glScissor_args*)argsPtr;
	gl_wrap_context_glScissor(ctx, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glTexParameterf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameterf_args args = *(gl_wrap_handler_glTexParameterf_args*)argsPtr;
	gl_wrap_context_glTexParameterf(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glTexParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameterfv_args args = *(gl_wrap_handler_glTexParameterfv_args*)argsPtr;
	gl_wrap_context_glTexParameterfv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameteri_args args = *(gl_wrap_handler_glTexParameteri_args*)argsPtr;
	gl_wrap_context_glTexParameteri(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glTexParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameteriv_args args = *(gl_wrap_handler_glTexParameteriv_args*)argsPtr;
	gl_wrap_context_glTexParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexImage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage1D_args args = *(gl_wrap_handler_glTexImage1D_args*)argsPtr;
	gl_wrap_context_glTexImage1D(ctx, args.target, args.level, args.internalformat, args.width, args.border, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glTexImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage2D_args args = *(gl_wrap_handler_glTexImage2D_args*)argsPtr;
	gl_wrap_context_glTexImage2D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.border, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glDrawBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawBuffer_args args = *(gl_wrap_handler_glDrawBuffer_args*)argsPtr;
	gl_wrap_context_glDrawBuffer(ctx, args.mode);
}

inline void gl_wrap_handler_glClear(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClear_args args = *(gl_wrap_handler_glClear_args*)argsPtr;
	gl_wrap_context_glClear(ctx, args.mask);
}

inline void gl_wrap_handler_glClearColor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearColor_args args = *(gl_wrap_handler_glClearColor_args*)argsPtr;
	gl_wrap_context_glClearColor(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glClearStencil(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearStencil_args args = *(gl_wrap_handler_glClearStencil_args*)argsPtr;
	gl_wrap_context_glClearStencil(ctx, args.s);
}

inline void gl_wrap_handler_glClearDepth(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearDepth_args args = *(gl_wrap_handler_glClearDepth_args*)argsPtr;
	gl_wrap_context_glClearDepth(ctx, args.depth);
}

inline void gl_wrap_handler_glStencilMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilMask_args args = *(gl_wrap_handler_glStencilMask_args*)argsPtr;
	gl_wrap_context_glStencilMask(ctx, args.mask);
}

inline void gl_wrap_handler_glColorMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorMask_args args = *(gl_wrap_handler_glColorMask_args*)argsPtr;
	gl_wrap_context_glColorMask(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glDepthMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthMask_args args = *(gl_wrap_handler_glDepthMask_args*)argsPtr;
	gl_wrap_context_glDepthMask(ctx, args.flag);
}

inline void gl_wrap_handler_glDisable(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDisable_args args = *(gl_wrap_handler_glDisable_args*)argsPtr;
	gl_wrap_context_glDisable(ctx, args.cap);
}

inline void gl_wrap_handler_glEnable(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnable_args args = *(gl_wrap_handler_glEnable_args*)argsPtr;
	gl_wrap_context_glEnable(ctx, args.cap);
}

inline void gl_wrap_handler_glFinish(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFinish_args args = *(gl_wrap_handler_glFinish_args*)argsPtr;
	gl_wrap_context_glFinish(ctx);
}

inline void gl_wrap_handler_glFlush(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFlush_args args = *(gl_wrap_handler_glFlush_args*)argsPtr;
	gl_wrap_context_glFlush(ctx);
}

inline void gl_wrap_handler_glBlendFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendFunc_args args = *(gl_wrap_handler_glBlendFunc_args*)argsPtr;
	gl_wrap_context_glBlendFunc(ctx, args.sfactor, args.dfactor);
}

inline void gl_wrap_handler_glLogicOp(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLogicOp_args args = *(gl_wrap_handler_glLogicOp_args*)argsPtr;
	gl_wrap_context_glLogicOp(ctx, args.opcode);
}

inline void gl_wrap_handler_glStencilFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilFunc_args args = *(gl_wrap_handler_glStencilFunc_args*)argsPtr;
	gl_wrap_context_glStencilFunc(ctx, args.func, args.ref, args.mask);
}

inline void gl_wrap_handler_glStencilOp(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilOp_args args = *(gl_wrap_handler_glStencilOp_args*)argsPtr;
	gl_wrap_context_glStencilOp(ctx, args.fail, args.zfail, args.zpass);
}

inline void gl_wrap_handler_glDepthFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthFunc_args args = *(gl_wrap_handler_glDepthFunc_args*)argsPtr;
	gl_wrap_context_glDepthFunc(ctx, args.func);
}

inline void gl_wrap_handler_glPixelStoref(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelStoref_args args = *(gl_wrap_handler_glPixelStoref_args*)argsPtr;
	gl_wrap_context_glPixelStoref(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glPixelStorei(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelStorei_args args = *(gl_wrap_handler_glPixelStorei_args*)argsPtr;
	gl_wrap_context_glPixelStorei(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glReadBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glReadBuffer_args args = *(gl_wrap_handler_glReadBuffer_args*)argsPtr;
	gl_wrap_context_glReadBuffer(ctx, args.mode);
}

inline void gl_wrap_handler_glReadPixels(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glReadPixels_args args = *(gl_wrap_handler_glReadPixels_args*)argsPtr;
	gl_wrap_context_glReadPixels(ctx, args.x, args.y, args.width, args.height, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glGetBooleanv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBooleanv_args args = *(gl_wrap_handler_glGetBooleanv_args*)argsPtr;
	gl_wrap_context_glGetBooleanv(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetDoublev(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetDoublev_args args = *(gl_wrap_handler_glGetDoublev_args*)argsPtr;
	gl_wrap_context_glGetDoublev(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetFloatv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFloatv_args args = *(gl_wrap_handler_glGetFloatv_args*)argsPtr;
	gl_wrap_context_glGetFloatv(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetIntegerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetIntegerv_args args = *(gl_wrap_handler_glGetIntegerv_args*)argsPtr;
	gl_wrap_context_glGetIntegerv(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetTexImage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexImage_args args = *(gl_wrap_handler_glGetTexImage_args*)argsPtr;
	gl_wrap_context_glGetTexImage(ctx, args.target, args.level, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glGetTexParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexParameterfv_args args = *(gl_wrap_handler_glGetTexParameterfv_args*)argsPtr;
	gl_wrap_context_glGetTexParameterfv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexParameteriv_args args = *(gl_wrap_handler_glGetTexParameteriv_args*)argsPtr;
	gl_wrap_context_glGetTexParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexLevelParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexLevelParameterfv_args args = *(gl_wrap_handler_glGetTexLevelParameterfv_args*)argsPtr;
	gl_wrap_context_glGetTexLevelParameterfv(ctx, args.target, args.level, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexLevelParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexLevelParameteriv_args args = *(gl_wrap_handler_glGetTexLevelParameteriv_args*)argsPtr;
	gl_wrap_context_glGetTexLevelParameteriv(ctx, args.target, args.level, args.pname, args.params);
}

inline void gl_wrap_handler_glDepthRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthRange_args args = *(gl_wrap_handler_glDepthRange_args*)argsPtr;
	gl_wrap_context_glDepthRange(ctx, args.near, args.far);
}

inline void gl_wrap_handler_glViewport(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glViewport_args args = *(gl_wrap_handler_glViewport_args*)argsPtr;
	gl_wrap_context_glViewport(ctx, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glNewList(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNewList_args args = *(gl_wrap_handler_glNewList_args*)argsPtr;
	gl_wrap_context_glNewList(ctx, args.list, args.mode);
}

inline void gl_wrap_handler_glEndList(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndList_args args = *(gl_wrap_handler_glEndList_args*)argsPtr;
	gl_wrap_context_glEndList(ctx);
}

inline void gl_wrap_handler_glCallList(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCallList_args args = *(gl_wrap_handler_glCallList_args*)argsPtr;
	gl_wrap_context_glCallList(ctx, args.list);
}

inline void gl_wrap_handler_glCallLists(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCallLists_args args = *(gl_wrap_handler_glCallLists_args*)argsPtr;
	gl_wrap_context_glCallLists(ctx, args.n, args.type, args.lists);
}

inline void gl_wrap_handler_glDeleteLists(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteLists_args args = *(gl_wrap_handler_glDeleteLists_args*)argsPtr;
	gl_wrap_context_glDeleteLists(ctx, args.list, args.range);
}

inline void gl_wrap_handler_glListBase(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glListBase_args args = *(gl_wrap_handler_glListBase_args*)argsPtr;
	gl_wrap_context_glListBase(ctx, args.base);
}

inline void gl_wrap_handler_glBegin(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBegin_args args = *(gl_wrap_handler_glBegin_args*)argsPtr;
	gl_wrap_context_glBegin(ctx, args.mode);
}

inline void gl_wrap_handler_glBitmap(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBitmap_args args = *(gl_wrap_handler_glBitmap_args*)argsPtr;
	gl_wrap_context_glBitmap(ctx, args.width, args.height, args.xorig, args.yorig, args.xmove, args.ymove, args.bitmap);
}

inline void gl_wrap_handler_glColor3b(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3b_args args = *(gl_wrap_handler_glColor3b_args*)argsPtr;
	gl_wrap_context_glColor3b(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3bv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3bv_args args = *(gl_wrap_handler_glColor3bv_args*)argsPtr;
	gl_wrap_context_glColor3bv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3d_args args = *(gl_wrap_handler_glColor3d_args*)argsPtr;
	gl_wrap_context_glColor3d(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3dv_args args = *(gl_wrap_handler_glColor3dv_args*)argsPtr;
	gl_wrap_context_glColor3dv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3f_args args = *(gl_wrap_handler_glColor3f_args*)argsPtr;
	gl_wrap_context_glColor3f(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3fv_args args = *(gl_wrap_handler_glColor3fv_args*)argsPtr;
	gl_wrap_context_glColor3fv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3i_args args = *(gl_wrap_handler_glColor3i_args*)argsPtr;
	gl_wrap_context_glColor3i(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3iv_args args = *(gl_wrap_handler_glColor3iv_args*)argsPtr;
	gl_wrap_context_glColor3iv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3s_args args = *(gl_wrap_handler_glColor3s_args*)argsPtr;
	gl_wrap_context_glColor3s(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3sv_args args = *(gl_wrap_handler_glColor3sv_args*)argsPtr;
	gl_wrap_context_glColor3sv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3ub(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3ub_args args = *(gl_wrap_handler_glColor3ub_args*)argsPtr;
	gl_wrap_context_glColor3ub(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3ubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3ubv_args args = *(gl_wrap_handler_glColor3ubv_args*)argsPtr;
	gl_wrap_context_glColor3ubv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3ui_args args = *(gl_wrap_handler_glColor3ui_args*)argsPtr;
	gl_wrap_context_glColor3ui(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3uiv_args args = *(gl_wrap_handler_glColor3uiv_args*)argsPtr;
	gl_wrap_context_glColor3uiv(ctx, args.v);
}

inline void gl_wrap_handler_glColor3us(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3us_args args = *(gl_wrap_handler_glColor3us_args*)argsPtr;
	gl_wrap_context_glColor3us(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glColor3usv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor3usv_args args = *(gl_wrap_handler_glColor3usv_args*)argsPtr;
	gl_wrap_context_glColor3usv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4b(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4b_args args = *(gl_wrap_handler_glColor4b_args*)argsPtr;
	gl_wrap_context_glColor4b(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4bv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4bv_args args = *(gl_wrap_handler_glColor4bv_args*)argsPtr;
	gl_wrap_context_glColor4bv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4d_args args = *(gl_wrap_handler_glColor4d_args*)argsPtr;
	gl_wrap_context_glColor4d(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4dv_args args = *(gl_wrap_handler_glColor4dv_args*)argsPtr;
	gl_wrap_context_glColor4dv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4f_args args = *(gl_wrap_handler_glColor4f_args*)argsPtr;
	gl_wrap_context_glColor4f(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4fv_args args = *(gl_wrap_handler_glColor4fv_args*)argsPtr;
	gl_wrap_context_glColor4fv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4i_args args = *(gl_wrap_handler_glColor4i_args*)argsPtr;
	gl_wrap_context_glColor4i(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4iv_args args = *(gl_wrap_handler_glColor4iv_args*)argsPtr;
	gl_wrap_context_glColor4iv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4s_args args = *(gl_wrap_handler_glColor4s_args*)argsPtr;
	gl_wrap_context_glColor4s(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4sv_args args = *(gl_wrap_handler_glColor4sv_args*)argsPtr;
	gl_wrap_context_glColor4sv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4ub(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4ub_args args = *(gl_wrap_handler_glColor4ub_args*)argsPtr;
	gl_wrap_context_glColor4ub(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4ubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4ubv_args args = *(gl_wrap_handler_glColor4ubv_args*)argsPtr;
	gl_wrap_context_glColor4ubv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4ui_args args = *(gl_wrap_handler_glColor4ui_args*)argsPtr;
	gl_wrap_context_glColor4ui(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4uiv_args args = *(gl_wrap_handler_glColor4uiv_args*)argsPtr;
	gl_wrap_context_glColor4uiv(ctx, args.v);
}

inline void gl_wrap_handler_glColor4us(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4us_args args = *(gl_wrap_handler_glColor4us_args*)argsPtr;
	gl_wrap_context_glColor4us(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glColor4usv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColor4usv_args args = *(gl_wrap_handler_glColor4usv_args*)argsPtr;
	gl_wrap_context_glColor4usv(ctx, args.v);
}

inline void gl_wrap_handler_glEdgeFlag(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEdgeFlag_args args = *(gl_wrap_handler_glEdgeFlag_args*)argsPtr;
	gl_wrap_context_glEdgeFlag(ctx, args.flag);
}

inline void gl_wrap_handler_glEdgeFlagv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEdgeFlagv_args args = *(gl_wrap_handler_glEdgeFlagv_args*)argsPtr;
	gl_wrap_context_glEdgeFlagv(ctx, args.flag);
}

inline void gl_wrap_handler_glEnd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnd_args args = *(gl_wrap_handler_glEnd_args*)argsPtr;
	gl_wrap_context_glEnd(ctx);
}

inline void gl_wrap_handler_glIndexd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexd_args args = *(gl_wrap_handler_glIndexd_args*)argsPtr;
	gl_wrap_context_glIndexd(ctx, args.c);
}

inline void gl_wrap_handler_glIndexdv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexdv_args args = *(gl_wrap_handler_glIndexdv_args*)argsPtr;
	gl_wrap_context_glIndexdv(ctx, args.c);
}

inline void gl_wrap_handler_glIndexf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexf_args args = *(gl_wrap_handler_glIndexf_args*)argsPtr;
	gl_wrap_context_glIndexf(ctx, args.c);
}

inline void gl_wrap_handler_glIndexfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexfv_args args = *(gl_wrap_handler_glIndexfv_args*)argsPtr;
	gl_wrap_context_glIndexfv(ctx, args.c);
}

inline void gl_wrap_handler_glIndexi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexi_args args = *(gl_wrap_handler_glIndexi_args*)argsPtr;
	gl_wrap_context_glIndexi(ctx, args.c);
}

inline void gl_wrap_handler_glIndexiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexiv_args args = *(gl_wrap_handler_glIndexiv_args*)argsPtr;
	gl_wrap_context_glIndexiv(ctx, args.c);
}

inline void gl_wrap_handler_glIndexs(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexs_args args = *(gl_wrap_handler_glIndexs_args*)argsPtr;
	gl_wrap_context_glIndexs(ctx, args.c);
}

inline void gl_wrap_handler_glIndexsv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexsv_args args = *(gl_wrap_handler_glIndexsv_args*)argsPtr;
	gl_wrap_context_glIndexsv(ctx, args.c);
}

inline void gl_wrap_handler_glNormal3b(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3b_args args = *(gl_wrap_handler_glNormal3b_args*)argsPtr;
	gl_wrap_context_glNormal3b(ctx, args.nx, args.ny, args.nz);
}

inline void gl_wrap_handler_glNormal3bv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3bv_args args = *(gl_wrap_handler_glNormal3bv_args*)argsPtr;
	gl_wrap_context_glNormal3bv(ctx, args.v);
}

inline void gl_wrap_handler_glNormal3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3d_args args = *(gl_wrap_handler_glNormal3d_args*)argsPtr;
	gl_wrap_context_glNormal3d(ctx, args.nx, args.ny, args.nz);
}

inline void gl_wrap_handler_glNormal3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3dv_args args = *(gl_wrap_handler_glNormal3dv_args*)argsPtr;
	gl_wrap_context_glNormal3dv(ctx, args.v);
}

inline void gl_wrap_handler_glNormal3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3f_args args = *(gl_wrap_handler_glNormal3f_args*)argsPtr;
	gl_wrap_context_glNormal3f(ctx, args.nx, args.ny, args.nz);
}

inline void gl_wrap_handler_glNormal3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3fv_args args = *(gl_wrap_handler_glNormal3fv_args*)argsPtr;
	gl_wrap_context_glNormal3fv(ctx, args.v);
}

inline void gl_wrap_handler_glNormal3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3i_args args = *(gl_wrap_handler_glNormal3i_args*)argsPtr;
	gl_wrap_context_glNormal3i(ctx, args.nx, args.ny, args.nz);
}

inline void gl_wrap_handler_glNormal3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3iv_args args = *(gl_wrap_handler_glNormal3iv_args*)argsPtr;
	gl_wrap_context_glNormal3iv(ctx, args.v);
}

inline void gl_wrap_handler_glNormal3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3s_args args = *(gl_wrap_handler_glNormal3s_args*)argsPtr;
	gl_wrap_context_glNormal3s(ctx, args.nx, args.ny, args.nz);
}

inline void gl_wrap_handler_glNormal3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormal3sv_args args = *(gl_wrap_handler_glNormal3sv_args*)argsPtr;
	gl_wrap_context_glNormal3sv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2d_args args = *(gl_wrap_handler_glRasterPos2d_args*)argsPtr;
	gl_wrap_context_glRasterPos2d(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glRasterPos2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2dv_args args = *(gl_wrap_handler_glRasterPos2dv_args*)argsPtr;
	gl_wrap_context_glRasterPos2dv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2f_args args = *(gl_wrap_handler_glRasterPos2f_args*)argsPtr;
	gl_wrap_context_glRasterPos2f(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glRasterPos2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2fv_args args = *(gl_wrap_handler_glRasterPos2fv_args*)argsPtr;
	gl_wrap_context_glRasterPos2fv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2i_args args = *(gl_wrap_handler_glRasterPos2i_args*)argsPtr;
	gl_wrap_context_glRasterPos2i(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glRasterPos2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2iv_args args = *(gl_wrap_handler_glRasterPos2iv_args*)argsPtr;
	gl_wrap_context_glRasterPos2iv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos2s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2s_args args = *(gl_wrap_handler_glRasterPos2s_args*)argsPtr;
	gl_wrap_context_glRasterPos2s(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glRasterPos2sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos2sv_args args = *(gl_wrap_handler_glRasterPos2sv_args*)argsPtr;
	gl_wrap_context_glRasterPos2sv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3d_args args = *(gl_wrap_handler_glRasterPos3d_args*)argsPtr;
	gl_wrap_context_glRasterPos3d(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glRasterPos3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3dv_args args = *(gl_wrap_handler_glRasterPos3dv_args*)argsPtr;
	gl_wrap_context_glRasterPos3dv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3f_args args = *(gl_wrap_handler_glRasterPos3f_args*)argsPtr;
	gl_wrap_context_glRasterPos3f(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glRasterPos3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3fv_args args = *(gl_wrap_handler_glRasterPos3fv_args*)argsPtr;
	gl_wrap_context_glRasterPos3fv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3i_args args = *(gl_wrap_handler_glRasterPos3i_args*)argsPtr;
	gl_wrap_context_glRasterPos3i(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glRasterPos3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3iv_args args = *(gl_wrap_handler_glRasterPos3iv_args*)argsPtr;
	gl_wrap_context_glRasterPos3iv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3s_args args = *(gl_wrap_handler_glRasterPos3s_args*)argsPtr;
	gl_wrap_context_glRasterPos3s(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glRasterPos3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos3sv_args args = *(gl_wrap_handler_glRasterPos3sv_args*)argsPtr;
	gl_wrap_context_glRasterPos3sv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4d_args args = *(gl_wrap_handler_glRasterPos4d_args*)argsPtr;
	gl_wrap_context_glRasterPos4d(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glRasterPos4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4dv_args args = *(gl_wrap_handler_glRasterPos4dv_args*)argsPtr;
	gl_wrap_context_glRasterPos4dv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4f_args args = *(gl_wrap_handler_glRasterPos4f_args*)argsPtr;
	gl_wrap_context_glRasterPos4f(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glRasterPos4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4fv_args args = *(gl_wrap_handler_glRasterPos4fv_args*)argsPtr;
	gl_wrap_context_glRasterPos4fv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4i_args args = *(gl_wrap_handler_glRasterPos4i_args*)argsPtr;
	gl_wrap_context_glRasterPos4i(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glRasterPos4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4iv_args args = *(gl_wrap_handler_glRasterPos4iv_args*)argsPtr;
	gl_wrap_context_glRasterPos4iv(ctx, args.v);
}

inline void gl_wrap_handler_glRasterPos4s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4s_args args = *(gl_wrap_handler_glRasterPos4s_args*)argsPtr;
	gl_wrap_context_glRasterPos4s(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glRasterPos4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRasterPos4sv_args args = *(gl_wrap_handler_glRasterPos4sv_args*)argsPtr;
	gl_wrap_context_glRasterPos4sv(ctx, args.v);
}

inline void gl_wrap_handler_glRectd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRectd_args args = *(gl_wrap_handler_glRectd_args*)argsPtr;
	gl_wrap_context_glRectd(ctx, args.x1, args.y1, args.x2, args.y2);
}

inline void gl_wrap_handler_glRectdv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRectdv_args args = *(gl_wrap_handler_glRectdv_args*)argsPtr;
	gl_wrap_context_glRectdv(ctx, args.v1, args.v2);
}

inline void gl_wrap_handler_glRectf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRectf_args args = *(gl_wrap_handler_glRectf_args*)argsPtr;
	gl_wrap_context_glRectf(ctx, args.x1, args.y1, args.x2, args.y2);
}

inline void gl_wrap_handler_glRectfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRectfv_args args = *(gl_wrap_handler_glRectfv_args*)argsPtr;
	gl_wrap_context_glRectfv(ctx, args.v1, args.v2);
}

inline void gl_wrap_handler_glRecti(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRecti_args args = *(gl_wrap_handler_glRecti_args*)argsPtr;
	gl_wrap_context_glRecti(ctx, args.x1, args.y1, args.x2, args.y2);
}

inline void gl_wrap_handler_glRectiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRectiv_args args = *(gl_wrap_handler_glRectiv_args*)argsPtr;
	gl_wrap_context_glRectiv(ctx, args.v1, args.v2);
}

inline void gl_wrap_handler_glRects(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRects_args args = *(gl_wrap_handler_glRects_args*)argsPtr;
	gl_wrap_context_glRects(ctx, args.x1, args.y1, args.x2, args.y2);
}

inline void gl_wrap_handler_glRectsv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRectsv_args args = *(gl_wrap_handler_glRectsv_args*)argsPtr;
	gl_wrap_context_glRectsv(ctx, args.v1, args.v2);
}

inline void gl_wrap_handler_glTexCoord1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1d_args args = *(gl_wrap_handler_glTexCoord1d_args*)argsPtr;
	gl_wrap_context_glTexCoord1d(ctx, args.s);
}

inline void gl_wrap_handler_glTexCoord1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1dv_args args = *(gl_wrap_handler_glTexCoord1dv_args*)argsPtr;
	gl_wrap_context_glTexCoord1dv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1f_args args = *(gl_wrap_handler_glTexCoord1f_args*)argsPtr;
	gl_wrap_context_glTexCoord1f(ctx, args.s);
}

inline void gl_wrap_handler_glTexCoord1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1fv_args args = *(gl_wrap_handler_glTexCoord1fv_args*)argsPtr;
	gl_wrap_context_glTexCoord1fv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1i_args args = *(gl_wrap_handler_glTexCoord1i_args*)argsPtr;
	gl_wrap_context_glTexCoord1i(ctx, args.s);
}

inline void gl_wrap_handler_glTexCoord1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1iv_args args = *(gl_wrap_handler_glTexCoord1iv_args*)argsPtr;
	gl_wrap_context_glTexCoord1iv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord1s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1s_args args = *(gl_wrap_handler_glTexCoord1s_args*)argsPtr;
	gl_wrap_context_glTexCoord1s(ctx, args.s);
}

inline void gl_wrap_handler_glTexCoord1sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord1sv_args args = *(gl_wrap_handler_glTexCoord1sv_args*)argsPtr;
	gl_wrap_context_glTexCoord1sv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2d_args args = *(gl_wrap_handler_glTexCoord2d_args*)argsPtr;
	gl_wrap_context_glTexCoord2d(ctx, args.s, args.t);
}

inline void gl_wrap_handler_glTexCoord2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2dv_args args = *(gl_wrap_handler_glTexCoord2dv_args*)argsPtr;
	gl_wrap_context_glTexCoord2dv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2f_args args = *(gl_wrap_handler_glTexCoord2f_args*)argsPtr;
	gl_wrap_context_glTexCoord2f(ctx, args.s, args.t);
}

inline void gl_wrap_handler_glTexCoord2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2fv_args args = *(gl_wrap_handler_glTexCoord2fv_args*)argsPtr;
	gl_wrap_context_glTexCoord2fv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2i_args args = *(gl_wrap_handler_glTexCoord2i_args*)argsPtr;
	gl_wrap_context_glTexCoord2i(ctx, args.s, args.t);
}

inline void gl_wrap_handler_glTexCoord2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2iv_args args = *(gl_wrap_handler_glTexCoord2iv_args*)argsPtr;
	gl_wrap_context_glTexCoord2iv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord2s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2s_args args = *(gl_wrap_handler_glTexCoord2s_args*)argsPtr;
	gl_wrap_context_glTexCoord2s(ctx, args.s, args.t);
}

inline void gl_wrap_handler_glTexCoord2sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord2sv_args args = *(gl_wrap_handler_glTexCoord2sv_args*)argsPtr;
	gl_wrap_context_glTexCoord2sv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3d_args args = *(gl_wrap_handler_glTexCoord3d_args*)argsPtr;
	gl_wrap_context_glTexCoord3d(ctx, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glTexCoord3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3dv_args args = *(gl_wrap_handler_glTexCoord3dv_args*)argsPtr;
	gl_wrap_context_glTexCoord3dv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3f_args args = *(gl_wrap_handler_glTexCoord3f_args*)argsPtr;
	gl_wrap_context_glTexCoord3f(ctx, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glTexCoord3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3fv_args args = *(gl_wrap_handler_glTexCoord3fv_args*)argsPtr;
	gl_wrap_context_glTexCoord3fv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3i_args args = *(gl_wrap_handler_glTexCoord3i_args*)argsPtr;
	gl_wrap_context_glTexCoord3i(ctx, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glTexCoord3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3iv_args args = *(gl_wrap_handler_glTexCoord3iv_args*)argsPtr;
	gl_wrap_context_glTexCoord3iv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3s_args args = *(gl_wrap_handler_glTexCoord3s_args*)argsPtr;
	gl_wrap_context_glTexCoord3s(ctx, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glTexCoord3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord3sv_args args = *(gl_wrap_handler_glTexCoord3sv_args*)argsPtr;
	gl_wrap_context_glTexCoord3sv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4d_args args = *(gl_wrap_handler_glTexCoord4d_args*)argsPtr;
	gl_wrap_context_glTexCoord4d(ctx, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glTexCoord4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4dv_args args = *(gl_wrap_handler_glTexCoord4dv_args*)argsPtr;
	gl_wrap_context_glTexCoord4dv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4f_args args = *(gl_wrap_handler_glTexCoord4f_args*)argsPtr;
	gl_wrap_context_glTexCoord4f(ctx, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glTexCoord4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4fv_args args = *(gl_wrap_handler_glTexCoord4fv_args*)argsPtr;
	gl_wrap_context_glTexCoord4fv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4i_args args = *(gl_wrap_handler_glTexCoord4i_args*)argsPtr;
	gl_wrap_context_glTexCoord4i(ctx, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glTexCoord4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4iv_args args = *(gl_wrap_handler_glTexCoord4iv_args*)argsPtr;
	gl_wrap_context_glTexCoord4iv(ctx, args.v);
}

inline void gl_wrap_handler_glTexCoord4s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4s_args args = *(gl_wrap_handler_glTexCoord4s_args*)argsPtr;
	gl_wrap_context_glTexCoord4s(ctx, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glTexCoord4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoord4sv_args args = *(gl_wrap_handler_glTexCoord4sv_args*)argsPtr;
	gl_wrap_context_glTexCoord4sv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2d_args args = *(gl_wrap_handler_glVertex2d_args*)argsPtr;
	gl_wrap_context_glVertex2d(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glVertex2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2dv_args args = *(gl_wrap_handler_glVertex2dv_args*)argsPtr;
	gl_wrap_context_glVertex2dv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2f_args args = *(gl_wrap_handler_glVertex2f_args*)argsPtr;
	gl_wrap_context_glVertex2f(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glVertex2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2fv_args args = *(gl_wrap_handler_glVertex2fv_args*)argsPtr;
	gl_wrap_context_glVertex2fv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2i_args args = *(gl_wrap_handler_glVertex2i_args*)argsPtr;
	gl_wrap_context_glVertex2i(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glVertex2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2iv_args args = *(gl_wrap_handler_glVertex2iv_args*)argsPtr;
	gl_wrap_context_glVertex2iv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex2s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2s_args args = *(gl_wrap_handler_glVertex2s_args*)argsPtr;
	gl_wrap_context_glVertex2s(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glVertex2sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex2sv_args args = *(gl_wrap_handler_glVertex2sv_args*)argsPtr;
	gl_wrap_context_glVertex2sv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3d_args args = *(gl_wrap_handler_glVertex3d_args*)argsPtr;
	gl_wrap_context_glVertex3d(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertex3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3dv_args args = *(gl_wrap_handler_glVertex3dv_args*)argsPtr;
	gl_wrap_context_glVertex3dv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3f_args args = *(gl_wrap_handler_glVertex3f_args*)argsPtr;
	gl_wrap_context_glVertex3f(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertex3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3fv_args args = *(gl_wrap_handler_glVertex3fv_args*)argsPtr;
	gl_wrap_context_glVertex3fv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3i_args args = *(gl_wrap_handler_glVertex3i_args*)argsPtr;
	gl_wrap_context_glVertex3i(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertex3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3iv_args args = *(gl_wrap_handler_glVertex3iv_args*)argsPtr;
	gl_wrap_context_glVertex3iv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3s_args args = *(gl_wrap_handler_glVertex3s_args*)argsPtr;
	gl_wrap_context_glVertex3s(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertex3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex3sv_args args = *(gl_wrap_handler_glVertex3sv_args*)argsPtr;
	gl_wrap_context_glVertex3sv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4d_args args = *(gl_wrap_handler_glVertex4d_args*)argsPtr;
	gl_wrap_context_glVertex4d(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertex4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4dv_args args = *(gl_wrap_handler_glVertex4dv_args*)argsPtr;
	gl_wrap_context_glVertex4dv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4f_args args = *(gl_wrap_handler_glVertex4f_args*)argsPtr;
	gl_wrap_context_glVertex4f(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertex4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4fv_args args = *(gl_wrap_handler_glVertex4fv_args*)argsPtr;
	gl_wrap_context_glVertex4fv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4i_args args = *(gl_wrap_handler_glVertex4i_args*)argsPtr;
	gl_wrap_context_glVertex4i(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertex4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4iv_args args = *(gl_wrap_handler_glVertex4iv_args*)argsPtr;
	gl_wrap_context_glVertex4iv(ctx, args.v);
}

inline void gl_wrap_handler_glVertex4s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4s_args args = *(gl_wrap_handler_glVertex4s_args*)argsPtr;
	gl_wrap_context_glVertex4s(ctx, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertex4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertex4sv_args args = *(gl_wrap_handler_glVertex4sv_args*)argsPtr;
	gl_wrap_context_glVertex4sv(ctx, args.v);
}

inline void gl_wrap_handler_glClipPlane(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClipPlane_args args = *(gl_wrap_handler_glClipPlane_args*)argsPtr;
	gl_wrap_context_glClipPlane(ctx, args.plane, args.equation);
}

inline void gl_wrap_handler_glColorMaterial(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorMaterial_args args = *(gl_wrap_handler_glColorMaterial_args*)argsPtr;
	gl_wrap_context_glColorMaterial(ctx, args.face, args.mode);
}

inline void gl_wrap_handler_glFogf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogf_args args = *(gl_wrap_handler_glFogf_args*)argsPtr;
	gl_wrap_context_glFogf(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glFogfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogfv_args args = *(gl_wrap_handler_glFogfv_args*)argsPtr;
	gl_wrap_context_glFogfv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glFogi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogi_args args = *(gl_wrap_handler_glFogi_args*)argsPtr;
	gl_wrap_context_glFogi(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glFogiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogiv_args args = *(gl_wrap_handler_glFogiv_args*)argsPtr;
	gl_wrap_context_glFogiv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glLightf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightf_args args = *(gl_wrap_handler_glLightf_args*)argsPtr;
	gl_wrap_context_glLightf(ctx, args.light, args.pname, args.param);
}

inline void gl_wrap_handler_glLightfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightfv_args args = *(gl_wrap_handler_glLightfv_args*)argsPtr;
	gl_wrap_context_glLightfv(ctx, args.light, args.pname, args.params);
}

inline void gl_wrap_handler_glLighti(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLighti_args args = *(gl_wrap_handler_glLighti_args*)argsPtr;
	gl_wrap_context_glLighti(ctx, args.light, args.pname, args.param);
}

inline void gl_wrap_handler_glLightiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightiv_args args = *(gl_wrap_handler_glLightiv_args*)argsPtr;
	gl_wrap_context_glLightiv(ctx, args.light, args.pname, args.params);
}

inline void gl_wrap_handler_glLightModelf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightModelf_args args = *(gl_wrap_handler_glLightModelf_args*)argsPtr;
	gl_wrap_context_glLightModelf(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glLightModelfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightModelfv_args args = *(gl_wrap_handler_glLightModelfv_args*)argsPtr;
	gl_wrap_context_glLightModelfv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glLightModeli(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightModeli_args args = *(gl_wrap_handler_glLightModeli_args*)argsPtr;
	gl_wrap_context_glLightModeli(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glLightModeliv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLightModeliv_args args = *(gl_wrap_handler_glLightModeliv_args*)argsPtr;
	gl_wrap_context_glLightModeliv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glLineStipple(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLineStipple_args args = *(gl_wrap_handler_glLineStipple_args*)argsPtr;
	gl_wrap_context_glLineStipple(ctx, args.factor, args.pattern);
}

inline void gl_wrap_handler_glMaterialf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMaterialf_args args = *(gl_wrap_handler_glMaterialf_args*)argsPtr;
	gl_wrap_context_glMaterialf(ctx, args.face, args.pname, args.param);
}

inline void gl_wrap_handler_glMaterialfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMaterialfv_args args = *(gl_wrap_handler_glMaterialfv_args*)argsPtr;
	gl_wrap_context_glMaterialfv(ctx, args.face, args.pname, args.params);
}

inline void gl_wrap_handler_glMateriali(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMateriali_args args = *(gl_wrap_handler_glMateriali_args*)argsPtr;
	gl_wrap_context_glMateriali(ctx, args.face, args.pname, args.param);
}

inline void gl_wrap_handler_glMaterialiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMaterialiv_args args = *(gl_wrap_handler_glMaterialiv_args*)argsPtr;
	gl_wrap_context_glMaterialiv(ctx, args.face, args.pname, args.params);
}

inline void gl_wrap_handler_glPolygonStipple(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPolygonStipple_args args = *(gl_wrap_handler_glPolygonStipple_args*)argsPtr;
	gl_wrap_context_glPolygonStipple(ctx, args.mask);
}

inline void gl_wrap_handler_glShadeModel(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glShadeModel_args args = *(gl_wrap_handler_glShadeModel_args*)argsPtr;
	gl_wrap_context_glShadeModel(ctx, args.mode);
}

inline void gl_wrap_handler_glTexEnvf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexEnvf_args args = *(gl_wrap_handler_glTexEnvf_args*)argsPtr;
	gl_wrap_context_glTexEnvf(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glTexEnvfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexEnvfv_args args = *(gl_wrap_handler_glTexEnvfv_args*)argsPtr;
	gl_wrap_context_glTexEnvfv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexEnvi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexEnvi_args args = *(gl_wrap_handler_glTexEnvi_args*)argsPtr;
	gl_wrap_context_glTexEnvi(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glTexEnviv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexEnviv_args args = *(gl_wrap_handler_glTexEnviv_args*)argsPtr;
	gl_wrap_context_glTexEnviv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexGend(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexGend_args args = *(gl_wrap_handler_glTexGend_args*)argsPtr;
	gl_wrap_context_glTexGend(ctx, args.coord, args.pname, args.param);
}

inline void gl_wrap_handler_glTexGendv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexGendv_args args = *(gl_wrap_handler_glTexGendv_args*)argsPtr;
	gl_wrap_context_glTexGendv(ctx, args.coord, args.pname, args.params);
}

inline void gl_wrap_handler_glTexGenf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexGenf_args args = *(gl_wrap_handler_glTexGenf_args*)argsPtr;
	gl_wrap_context_glTexGenf(ctx, args.coord, args.pname, args.param);
}

inline void gl_wrap_handler_glTexGenfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexGenfv_args args = *(gl_wrap_handler_glTexGenfv_args*)argsPtr;
	gl_wrap_context_glTexGenfv(ctx, args.coord, args.pname, args.params);
}

inline void gl_wrap_handler_glTexGeni(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexGeni_args args = *(gl_wrap_handler_glTexGeni_args*)argsPtr;
	gl_wrap_context_glTexGeni(ctx, args.coord, args.pname, args.param);
}

inline void gl_wrap_handler_glTexGeniv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexGeniv_args args = *(gl_wrap_handler_glTexGeniv_args*)argsPtr;
	gl_wrap_context_glTexGeniv(ctx, args.coord, args.pname, args.params);
}

inline void gl_wrap_handler_glFeedbackBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFeedbackBuffer_args args = *(gl_wrap_handler_glFeedbackBuffer_args*)argsPtr;
	gl_wrap_context_glFeedbackBuffer(ctx, args.size, args.type, args.buffer);
}

inline void gl_wrap_handler_glSelectBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSelectBuffer_args args = *(gl_wrap_handler_glSelectBuffer_args*)argsPtr;
	gl_wrap_context_glSelectBuffer(ctx, args.size, args.buffer);
}

inline void gl_wrap_handler_glInitNames(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInitNames_args args = *(gl_wrap_handler_glInitNames_args*)argsPtr;
	gl_wrap_context_glInitNames(ctx);
}

inline void gl_wrap_handler_glLoadName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLoadName_args args = *(gl_wrap_handler_glLoadName_args*)argsPtr;
	gl_wrap_context_glLoadName(ctx, args.name);
}

inline void gl_wrap_handler_glPassThrough(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPassThrough_args args = *(gl_wrap_handler_glPassThrough_args*)argsPtr;
	gl_wrap_context_glPassThrough(ctx, args.token);
}

inline void gl_wrap_handler_glPopName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPopName_args args = *(gl_wrap_handler_glPopName_args*)argsPtr;
	gl_wrap_context_glPopName(ctx);
}

inline void gl_wrap_handler_glPushName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPushName_args args = *(gl_wrap_handler_glPushName_args*)argsPtr;
	gl_wrap_context_glPushName(ctx, args.name);
}

inline void gl_wrap_handler_glClearAccum(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearAccum_args args = *(gl_wrap_handler_glClearAccum_args*)argsPtr;
	gl_wrap_context_glClearAccum(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glClearIndex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearIndex_args args = *(gl_wrap_handler_glClearIndex_args*)argsPtr;
	gl_wrap_context_glClearIndex(ctx, args.c);
}

inline void gl_wrap_handler_glIndexMask(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexMask_args args = *(gl_wrap_handler_glIndexMask_args*)argsPtr;
	gl_wrap_context_glIndexMask(ctx, args.mask);
}

inline void gl_wrap_handler_glAccum(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glAccum_args args = *(gl_wrap_handler_glAccum_args*)argsPtr;
	gl_wrap_context_glAccum(ctx, args.op, args.value);
}

inline void gl_wrap_handler_glPopAttrib(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPopAttrib_args args = *(gl_wrap_handler_glPopAttrib_args*)argsPtr;
	gl_wrap_context_glPopAttrib(ctx);
}

inline void gl_wrap_handler_glPushAttrib(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPushAttrib_args args = *(gl_wrap_handler_glPushAttrib_args*)argsPtr;
	gl_wrap_context_glPushAttrib(ctx, args.mask);
}

inline void gl_wrap_handler_glMap1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMap1d_args args = *(gl_wrap_handler_glMap1d_args*)argsPtr;
	gl_wrap_context_glMap1d(ctx, args.target, args.u1, args.u2, args.stride, args.order, args.points);
}

inline void gl_wrap_handler_glMap1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMap1f_args args = *(gl_wrap_handler_glMap1f_args*)argsPtr;
	gl_wrap_context_glMap1f(ctx, args.target, args.u1, args.u2, args.stride, args.order, args.points);
}

inline void gl_wrap_handler_glMap2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMap2d_args args = *(gl_wrap_handler_glMap2d_args*)argsPtr;
	gl_wrap_context_glMap2d(ctx, args.target, args.u1, args.u2, args.ustride, args.uorder, args.v1, args.v2, args.vstride, args.vorder, args.points);
}

inline void gl_wrap_handler_glMap2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMap2f_args args = *(gl_wrap_handler_glMap2f_args*)argsPtr;
	gl_wrap_context_glMap2f(ctx, args.target, args.u1, args.u2, args.ustride, args.uorder, args.v1, args.v2, args.vstride, args.vorder, args.points);
}

inline void gl_wrap_handler_glMapGrid1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapGrid1d_args args = *(gl_wrap_handler_glMapGrid1d_args*)argsPtr;
	gl_wrap_context_glMapGrid1d(ctx, args.un, args.u1, args.u2);
}

inline void gl_wrap_handler_glMapGrid1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapGrid1f_args args = *(gl_wrap_handler_glMapGrid1f_args*)argsPtr;
	gl_wrap_context_glMapGrid1f(ctx, args.un, args.u1, args.u2);
}

inline void gl_wrap_handler_glMapGrid2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapGrid2d_args args = *(gl_wrap_handler_glMapGrid2d_args*)argsPtr;
	gl_wrap_context_glMapGrid2d(ctx, args.un, args.u1, args.u2, args.vn, args.v1, args.v2);
}

inline void gl_wrap_handler_glMapGrid2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapGrid2f_args args = *(gl_wrap_handler_glMapGrid2f_args*)argsPtr;
	gl_wrap_context_glMapGrid2f(ctx, args.un, args.u1, args.u2, args.vn, args.v1, args.v2);
}

inline void gl_wrap_handler_glEvalCoord1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord1d_args args = *(gl_wrap_handler_glEvalCoord1d_args*)argsPtr;
	gl_wrap_context_glEvalCoord1d(ctx, args.u);
}

inline void gl_wrap_handler_glEvalCoord1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord1dv_args args = *(gl_wrap_handler_glEvalCoord1dv_args*)argsPtr;
	gl_wrap_context_glEvalCoord1dv(ctx, args.u);
}

inline void gl_wrap_handler_glEvalCoord1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord1f_args args = *(gl_wrap_handler_glEvalCoord1f_args*)argsPtr;
	gl_wrap_context_glEvalCoord1f(ctx, args.u);
}

inline void gl_wrap_handler_glEvalCoord1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord1fv_args args = *(gl_wrap_handler_glEvalCoord1fv_args*)argsPtr;
	gl_wrap_context_glEvalCoord1fv(ctx, args.u);
}

inline void gl_wrap_handler_glEvalCoord2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord2d_args args = *(gl_wrap_handler_glEvalCoord2d_args*)argsPtr;
	gl_wrap_context_glEvalCoord2d(ctx, args.u, args.v);
}

inline void gl_wrap_handler_glEvalCoord2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord2dv_args args = *(gl_wrap_handler_glEvalCoord2dv_args*)argsPtr;
	gl_wrap_context_glEvalCoord2dv(ctx, args.u);
}

inline void gl_wrap_handler_glEvalCoord2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord2f_args args = *(gl_wrap_handler_glEvalCoord2f_args*)argsPtr;
	gl_wrap_context_glEvalCoord2f(ctx, args.u, args.v);
}

inline void gl_wrap_handler_glEvalCoord2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalCoord2fv_args args = *(gl_wrap_handler_glEvalCoord2fv_args*)argsPtr;
	gl_wrap_context_glEvalCoord2fv(ctx, args.u);
}

inline void gl_wrap_handler_glEvalMesh1(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalMesh1_args args = *(gl_wrap_handler_glEvalMesh1_args*)argsPtr;
	gl_wrap_context_glEvalMesh1(ctx, args.mode, args.i1, args.i2);
}

inline void gl_wrap_handler_glEvalPoint1(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalPoint1_args args = *(gl_wrap_handler_glEvalPoint1_args*)argsPtr;
	gl_wrap_context_glEvalPoint1(ctx, args.i);
}

inline void gl_wrap_handler_glEvalMesh2(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalMesh2_args args = *(gl_wrap_handler_glEvalMesh2_args*)argsPtr;
	gl_wrap_context_glEvalMesh2(ctx, args.mode, args.i1, args.i2, args.j1, args.j2);
}

inline void gl_wrap_handler_glEvalPoint2(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEvalPoint2_args args = *(gl_wrap_handler_glEvalPoint2_args*)argsPtr;
	gl_wrap_context_glEvalPoint2(ctx, args.i, args.j);
}

inline void gl_wrap_handler_glAlphaFunc(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glAlphaFunc_args args = *(gl_wrap_handler_glAlphaFunc_args*)argsPtr;
	gl_wrap_context_glAlphaFunc(ctx, args.func, args.ref);
}

inline void gl_wrap_handler_glPixelZoom(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelZoom_args args = *(gl_wrap_handler_glPixelZoom_args*)argsPtr;
	gl_wrap_context_glPixelZoom(ctx, args.xfactor, args.yfactor);
}

inline void gl_wrap_handler_glPixelTransferf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelTransferf_args args = *(gl_wrap_handler_glPixelTransferf_args*)argsPtr;
	gl_wrap_context_glPixelTransferf(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glPixelTransferi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelTransferi_args args = *(gl_wrap_handler_glPixelTransferi_args*)argsPtr;
	gl_wrap_context_glPixelTransferi(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glPixelMapfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelMapfv_args args = *(gl_wrap_handler_glPixelMapfv_args*)argsPtr;
	gl_wrap_context_glPixelMapfv(ctx, args.map, args.mapsize, args.values);
}

inline void gl_wrap_handler_glPixelMapuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelMapuiv_args args = *(gl_wrap_handler_glPixelMapuiv_args*)argsPtr;
	gl_wrap_context_glPixelMapuiv(ctx, args.map, args.mapsize, args.values);
}

inline void gl_wrap_handler_glPixelMapusv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPixelMapusv_args args = *(gl_wrap_handler_glPixelMapusv_args*)argsPtr;
	gl_wrap_context_glPixelMapusv(ctx, args.map, args.mapsize, args.values);
}

inline void gl_wrap_handler_glCopyPixels(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyPixels_args args = *(gl_wrap_handler_glCopyPixels_args*)argsPtr;
	gl_wrap_context_glCopyPixels(ctx, args.x, args.y, args.width, args.height, args.type);
}

inline void gl_wrap_handler_glDrawPixels(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawPixels_args args = *(gl_wrap_handler_glDrawPixels_args*)argsPtr;
	gl_wrap_context_glDrawPixels(ctx, args.width, args.height, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glGetClipPlane(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetClipPlane_args args = *(gl_wrap_handler_glGetClipPlane_args*)argsPtr;
	gl_wrap_context_glGetClipPlane(ctx, args.plane, args.equation);
}

inline void gl_wrap_handler_glGetLightfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetLightfv_args args = *(gl_wrap_handler_glGetLightfv_args*)argsPtr;
	gl_wrap_context_glGetLightfv(ctx, args.light, args.pname, args.params);
}

inline void gl_wrap_handler_glGetLightiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetLightiv_args args = *(gl_wrap_handler_glGetLightiv_args*)argsPtr;
	gl_wrap_context_glGetLightiv(ctx, args.light, args.pname, args.params);
}

inline void gl_wrap_handler_glGetMapdv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMapdv_args args = *(gl_wrap_handler_glGetMapdv_args*)argsPtr;
	gl_wrap_context_glGetMapdv(ctx, args.target, args.query, args.v);
}

inline void gl_wrap_handler_glGetMapfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMapfv_args args = *(gl_wrap_handler_glGetMapfv_args*)argsPtr;
	gl_wrap_context_glGetMapfv(ctx, args.target, args.query, args.v);
}

inline void gl_wrap_handler_glGetMapiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMapiv_args args = *(gl_wrap_handler_glGetMapiv_args*)argsPtr;
	gl_wrap_context_glGetMapiv(ctx, args.target, args.query, args.v);
}

inline void gl_wrap_handler_glGetMaterialfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMaterialfv_args args = *(gl_wrap_handler_glGetMaterialfv_args*)argsPtr;
	gl_wrap_context_glGetMaterialfv(ctx, args.face, args.pname, args.params);
}

inline void gl_wrap_handler_glGetMaterialiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMaterialiv_args args = *(gl_wrap_handler_glGetMaterialiv_args*)argsPtr;
	gl_wrap_context_glGetMaterialiv(ctx, args.face, args.pname, args.params);
}

inline void gl_wrap_handler_glGetPixelMapfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetPixelMapfv_args args = *(gl_wrap_handler_glGetPixelMapfv_args*)argsPtr;
	gl_wrap_context_glGetPixelMapfv(ctx, args.map, args.values);
}

inline void gl_wrap_handler_glGetPixelMapuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetPixelMapuiv_args args = *(gl_wrap_handler_glGetPixelMapuiv_args*)argsPtr;
	gl_wrap_context_glGetPixelMapuiv(ctx, args.map, args.values);
}

inline void gl_wrap_handler_glGetPixelMapusv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetPixelMapusv_args args = *(gl_wrap_handler_glGetPixelMapusv_args*)argsPtr;
	gl_wrap_context_glGetPixelMapusv(ctx, args.map, args.values);
}

inline void gl_wrap_handler_glGetPolygonStipple(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetPolygonStipple_args args = *(gl_wrap_handler_glGetPolygonStipple_args*)argsPtr;
	gl_wrap_context_glGetPolygonStipple(ctx, args.mask);
}

inline void gl_wrap_handler_glGetTexEnvfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexEnvfv_args args = *(gl_wrap_handler_glGetTexEnvfv_args*)argsPtr;
	gl_wrap_context_glGetTexEnvfv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexEnviv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexEnviv_args args = *(gl_wrap_handler_glGetTexEnviv_args*)argsPtr;
	gl_wrap_context_glGetTexEnviv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexGendv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexGendv_args args = *(gl_wrap_handler_glGetTexGendv_args*)argsPtr;
	gl_wrap_context_glGetTexGendv(ctx, args.coord, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexGenfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexGenfv_args args = *(gl_wrap_handler_glGetTexGenfv_args*)argsPtr;
	gl_wrap_context_glGetTexGenfv(ctx, args.coord, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexGeniv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexGeniv_args args = *(gl_wrap_handler_glGetTexGeniv_args*)argsPtr;
	gl_wrap_context_glGetTexGeniv(ctx, args.coord, args.pname, args.params);
}

inline void gl_wrap_handler_glFrustum(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFrustum_args args = *(gl_wrap_handler_glFrustum_args*)argsPtr;
	gl_wrap_context_glFrustum(ctx, args.left, args.right, args.bottom, args.top, args.zNear, args.zFar);
}

inline void gl_wrap_handler_glLoadIdentity(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLoadIdentity_args args = *(gl_wrap_handler_glLoadIdentity_args*)argsPtr;
	gl_wrap_context_glLoadIdentity(ctx);
}

inline void gl_wrap_handler_glLoadMatrixf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLoadMatrixf_args args = *(gl_wrap_handler_glLoadMatrixf_args*)argsPtr;
	gl_wrap_context_glLoadMatrixf(ctx, args.m);
}

inline void gl_wrap_handler_glLoadMatrixd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLoadMatrixd_args args = *(gl_wrap_handler_glLoadMatrixd_args*)argsPtr;
	gl_wrap_context_glLoadMatrixd(ctx, args.m);
}

inline void gl_wrap_handler_glMatrixMode(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMatrixMode_args args = *(gl_wrap_handler_glMatrixMode_args*)argsPtr;
	gl_wrap_context_glMatrixMode(ctx, args.mode);
}

inline void gl_wrap_handler_glMultMatrixf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultMatrixf_args args = *(gl_wrap_handler_glMultMatrixf_args*)argsPtr;
	gl_wrap_context_glMultMatrixf(ctx, args.m);
}

inline void gl_wrap_handler_glMultMatrixd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultMatrixd_args args = *(gl_wrap_handler_glMultMatrixd_args*)argsPtr;
	gl_wrap_context_glMultMatrixd(ctx, args.m);
}

inline void gl_wrap_handler_glOrtho(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glOrtho_args args = *(gl_wrap_handler_glOrtho_args*)argsPtr;
	gl_wrap_context_glOrtho(ctx, args.left, args.right, args.bottom, args.top, args.zNear, args.zFar);
}

inline void gl_wrap_handler_glPopMatrix(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPopMatrix_args args = *(gl_wrap_handler_glPopMatrix_args*)argsPtr;
	gl_wrap_context_glPopMatrix(ctx);
}

inline void gl_wrap_handler_glPushMatrix(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPushMatrix_args args = *(gl_wrap_handler_glPushMatrix_args*)argsPtr;
	gl_wrap_context_glPushMatrix(ctx);
}

inline void gl_wrap_handler_glRotated(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRotated_args args = *(gl_wrap_handler_glRotated_args*)argsPtr;
	gl_wrap_context_glRotated(ctx, args.angle, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glRotatef(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRotatef_args args = *(gl_wrap_handler_glRotatef_args*)argsPtr;
	gl_wrap_context_glRotatef(ctx, args.angle, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glScaled(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScaled_args args = *(gl_wrap_handler_glScaled_args*)argsPtr;
	gl_wrap_context_glScaled(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glScalef(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScalef_args args = *(gl_wrap_handler_glScalef_args*)argsPtr;
	gl_wrap_context_glScalef(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glTranslated(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTranslated_args args = *(gl_wrap_handler_glTranslated_args*)argsPtr;
	gl_wrap_context_glTranslated(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glTranslatef(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTranslatef_args args = *(gl_wrap_handler_glTranslatef_args*)argsPtr;
	gl_wrap_context_glTranslatef(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glDrawArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArrays_args args = *(gl_wrap_handler_glDrawArrays_args*)argsPtr;
	gl_wrap_context_glDrawArrays(ctx, args.mode, args.first, args.count);
}

inline void gl_wrap_handler_glDrawElements(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElements_args args = *(gl_wrap_handler_glDrawElements_args*)argsPtr;
	gl_wrap_context_glDrawElements(ctx, args.mode, args.count, args.type, args.indices);
}

inline void gl_wrap_handler_glGetPointerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetPointerv_args args = *(gl_wrap_handler_glGetPointerv_args*)argsPtr;
	gl_wrap_context_glGetPointerv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glPolygonOffset(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPolygonOffset_args args = *(gl_wrap_handler_glPolygonOffset_args*)argsPtr;
	gl_wrap_context_glPolygonOffset(ctx, args.factor, args.units);
}

inline void gl_wrap_handler_glCopyTexImage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexImage1D_args args = *(gl_wrap_handler_glCopyTexImage1D_args*)argsPtr;
	gl_wrap_context_glCopyTexImage1D(ctx, args.target, args.level, args.internalformat, args.x, args.y, args.width, args.border);
}

inline void gl_wrap_handler_glCopyTexImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexImage2D_args args = *(gl_wrap_handler_glCopyTexImage2D_args*)argsPtr;
	gl_wrap_context_glCopyTexImage2D(ctx, args.target, args.level, args.internalformat, args.x, args.y, args.width, args.height, args.border);
}

inline void gl_wrap_handler_glCopyTexSubImage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexSubImage1D_args args = *(gl_wrap_handler_glCopyTexSubImage1D_args*)argsPtr;
	gl_wrap_context_glCopyTexSubImage1D(ctx, args.target, args.level, args.xoffset, args.x, args.y, args.width);
}

inline void gl_wrap_handler_glCopyTexSubImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexSubImage2D_args args = *(gl_wrap_handler_glCopyTexSubImage2D_args*)argsPtr;
	gl_wrap_context_glCopyTexSubImage2D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glTexSubImage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexSubImage1D_args args = *(gl_wrap_handler_glTexSubImage1D_args*)argsPtr;
	gl_wrap_context_glTexSubImage1D(ctx, args.target, args.level, args.xoffset, args.width, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glTexSubImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexSubImage2D_args args = *(gl_wrap_handler_glTexSubImage2D_args*)argsPtr;
	gl_wrap_context_glTexSubImage2D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.width, args.height, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glBindTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindTexture_args args = *(gl_wrap_handler_glBindTexture_args*)argsPtr;
	gl_wrap_context_glBindTexture(ctx, args.target, args.texture);
}

inline void gl_wrap_handler_glDeleteTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteTextures_args args = *(gl_wrap_handler_glDeleteTextures_args*)argsPtr;
	gl_wrap_context_glDeleteTextures(ctx, args.n, args.textures);
}

inline void gl_wrap_handler_glGenTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenTextures_args args = *(gl_wrap_handler_glGenTextures_args*)argsPtr;
	gl_wrap_context_glGenTextures(ctx, args.n, args.textures);
}

inline void gl_wrap_handler_glArrayElement(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glArrayElement_args args = *(gl_wrap_handler_glArrayElement_args*)argsPtr;
	gl_wrap_context_glArrayElement(ctx, args.i);
}

inline void gl_wrap_handler_glColorPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorPointer_args args = *(gl_wrap_handler_glColorPointer_args*)argsPtr;
	gl_wrap_context_glColorPointer(ctx, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glDisableClientState(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDisableClientState_args args = *(gl_wrap_handler_glDisableClientState_args*)argsPtr;
	gl_wrap_context_glDisableClientState(ctx, args.array);
}

inline void gl_wrap_handler_glEdgeFlagPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEdgeFlagPointer_args args = *(gl_wrap_handler_glEdgeFlagPointer_args*)argsPtr;
	gl_wrap_context_glEdgeFlagPointer(ctx, args.stride, args.pointer);
}

inline void gl_wrap_handler_glEnableClientState(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnableClientState_args args = *(gl_wrap_handler_glEnableClientState_args*)argsPtr;
	gl_wrap_context_glEnableClientState(ctx, args.array);
}

inline void gl_wrap_handler_glIndexPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexPointer_args args = *(gl_wrap_handler_glIndexPointer_args*)argsPtr;
	gl_wrap_context_glIndexPointer(ctx, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glInterleavedArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInterleavedArrays_args args = *(gl_wrap_handler_glInterleavedArrays_args*)argsPtr;
	gl_wrap_context_glInterleavedArrays(ctx, args.format, args.stride, args.pointer);
}

inline void gl_wrap_handler_glNormalPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormalPointer_args args = *(gl_wrap_handler_glNormalPointer_args*)argsPtr;
	gl_wrap_context_glNormalPointer(ctx, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glTexCoordPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordPointer_args args = *(gl_wrap_handler_glTexCoordPointer_args*)argsPtr;
	gl_wrap_context_glTexCoordPointer(ctx, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glVertexPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexPointer_args args = *(gl_wrap_handler_glVertexPointer_args*)argsPtr;
	gl_wrap_context_glVertexPointer(ctx, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glPrioritizeTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPrioritizeTextures_args args = *(gl_wrap_handler_glPrioritizeTextures_args*)argsPtr;
	gl_wrap_context_glPrioritizeTextures(ctx, args.n, args.textures, args.priorities);
}

inline void gl_wrap_handler_glIndexub(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexub_args args = *(gl_wrap_handler_glIndexub_args*)argsPtr;
	gl_wrap_context_glIndexub(ctx, args.c);
}

inline void gl_wrap_handler_glIndexubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glIndexubv_args args = *(gl_wrap_handler_glIndexubv_args*)argsPtr;
	gl_wrap_context_glIndexubv(ctx, args.c);
}

inline void gl_wrap_handler_glPopClientAttrib(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPopClientAttrib_args args = *(gl_wrap_handler_glPopClientAttrib_args*)argsPtr;
	gl_wrap_context_glPopClientAttrib(ctx);
}

inline void gl_wrap_handler_glPushClientAttrib(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPushClientAttrib_args args = *(gl_wrap_handler_glPushClientAttrib_args*)argsPtr;
	gl_wrap_context_glPushClientAttrib(ctx, args.mask);
}

inline void gl_wrap_handler_glDrawRangeElements(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawRangeElements_args args = *(gl_wrap_handler_glDrawRangeElements_args*)argsPtr;
	gl_wrap_context_glDrawRangeElements(ctx, args.mode, args.start, args.end, args.count, args.type, args.indices);
}

inline void gl_wrap_handler_glTexImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage3D_args args = *(gl_wrap_handler_glTexImage3D_args*)argsPtr;
	gl_wrap_context_glTexImage3D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.depth, args.border, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glTexSubImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexSubImage3D_args args = *(gl_wrap_handler_glTexSubImage3D_args*)argsPtr;
	gl_wrap_context_glTexSubImage3D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.zoffset, args.width, args.height, args.depth, args.format, args.type, args.pixels);
}

inline void gl_wrap_handler_glCopyTexSubImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyTexSubImage3D_args args = *(gl_wrap_handler_glCopyTexSubImage3D_args*)argsPtr;
	gl_wrap_context_glCopyTexSubImage3D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.zoffset, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glActiveTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glActiveTexture_args args = *(gl_wrap_handler_glActiveTexture_args*)argsPtr;
	gl_wrap_context_glActiveTexture(ctx, args.texture);
}

inline void gl_wrap_handler_glSampleCoverage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSampleCoverage_args args = *(gl_wrap_handler_glSampleCoverage_args*)argsPtr;
	gl_wrap_context_glSampleCoverage(ctx, args.value, args.invert);
}

inline void gl_wrap_handler_glCompressedTexImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexImage3D_args args = *(gl_wrap_handler_glCompressedTexImage3D_args*)argsPtr;
	gl_wrap_context_glCompressedTexImage3D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.depth, args.border, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexImage2D_args args = *(gl_wrap_handler_glCompressedTexImage2D_args*)argsPtr;
	gl_wrap_context_glCompressedTexImage2D(ctx, args.target, args.level, args.internalformat, args.width, args.height, args.border, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexImage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexImage1D_args args = *(gl_wrap_handler_glCompressedTexImage1D_args*)argsPtr;
	gl_wrap_context_glCompressedTexImage1D(ctx, args.target, args.level, args.internalformat, args.width, args.border, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexSubImage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexSubImage3D_args args = *(gl_wrap_handler_glCompressedTexSubImage3D_args*)argsPtr;
	gl_wrap_context_glCompressedTexSubImage3D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.zoffset, args.width, args.height, args.depth, args.format, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexSubImage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexSubImage2D_args args = *(gl_wrap_handler_glCompressedTexSubImage2D_args*)argsPtr;
	gl_wrap_context_glCompressedTexSubImage2D(ctx, args.target, args.level, args.xoffset, args.yoffset, args.width, args.height, args.format, args.imageSize, args.data);
}

inline void gl_wrap_handler_glCompressedTexSubImage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompressedTexSubImage1D_args args = *(gl_wrap_handler_glCompressedTexSubImage1D_args*)argsPtr;
	gl_wrap_context_glCompressedTexSubImage1D(ctx, args.target, args.level, args.xoffset, args.width, args.format, args.imageSize, args.data);
}

inline void gl_wrap_handler_glGetCompressedTexImage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetCompressedTexImage_args args = *(gl_wrap_handler_glGetCompressedTexImage_args*)argsPtr;
	gl_wrap_context_glGetCompressedTexImage(ctx, args.target, args.level, args.img);
}

inline void gl_wrap_handler_glClientActiveTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClientActiveTexture_args args = *(gl_wrap_handler_glClientActiveTexture_args*)argsPtr;
	gl_wrap_context_glClientActiveTexture(ctx, args.texture);
}

inline void gl_wrap_handler_glMultiTexCoord1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1d_args args = *(gl_wrap_handler_glMultiTexCoord1d_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1d(ctx, args.target, args.s);
}

inline void gl_wrap_handler_glMultiTexCoord1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1dv_args args = *(gl_wrap_handler_glMultiTexCoord1dv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1dv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1f_args args = *(gl_wrap_handler_glMultiTexCoord1f_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1f(ctx, args.target, args.s);
}

inline void gl_wrap_handler_glMultiTexCoord1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1fv_args args = *(gl_wrap_handler_glMultiTexCoord1fv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1fv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1i_args args = *(gl_wrap_handler_glMultiTexCoord1i_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1i(ctx, args.target, args.s);
}

inline void gl_wrap_handler_glMultiTexCoord1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1iv_args args = *(gl_wrap_handler_glMultiTexCoord1iv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1iv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord1s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1s_args args = *(gl_wrap_handler_glMultiTexCoord1s_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1s(ctx, args.target, args.s);
}

inline void gl_wrap_handler_glMultiTexCoord1sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord1sv_args args = *(gl_wrap_handler_glMultiTexCoord1sv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord1sv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2d_args args = *(gl_wrap_handler_glMultiTexCoord2d_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2d(ctx, args.target, args.s, args.t);
}

inline void gl_wrap_handler_glMultiTexCoord2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2dv_args args = *(gl_wrap_handler_glMultiTexCoord2dv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2dv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2f_args args = *(gl_wrap_handler_glMultiTexCoord2f_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2f(ctx, args.target, args.s, args.t);
}

inline void gl_wrap_handler_glMultiTexCoord2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2fv_args args = *(gl_wrap_handler_glMultiTexCoord2fv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2fv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2i_args args = *(gl_wrap_handler_glMultiTexCoord2i_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2i(ctx, args.target, args.s, args.t);
}

inline void gl_wrap_handler_glMultiTexCoord2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2iv_args args = *(gl_wrap_handler_glMultiTexCoord2iv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2iv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord2s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2s_args args = *(gl_wrap_handler_glMultiTexCoord2s_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2s(ctx, args.target, args.s, args.t);
}

inline void gl_wrap_handler_glMultiTexCoord2sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord2sv_args args = *(gl_wrap_handler_glMultiTexCoord2sv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord2sv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3d_args args = *(gl_wrap_handler_glMultiTexCoord3d_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3d(ctx, args.target, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glMultiTexCoord3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3dv_args args = *(gl_wrap_handler_glMultiTexCoord3dv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3dv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3f_args args = *(gl_wrap_handler_glMultiTexCoord3f_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3f(ctx, args.target, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glMultiTexCoord3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3fv_args args = *(gl_wrap_handler_glMultiTexCoord3fv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3fv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3i_args args = *(gl_wrap_handler_glMultiTexCoord3i_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3i(ctx, args.target, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glMultiTexCoord3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3iv_args args = *(gl_wrap_handler_glMultiTexCoord3iv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3iv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3s_args args = *(gl_wrap_handler_glMultiTexCoord3s_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3s(ctx, args.target, args.s, args.t, args.r);
}

inline void gl_wrap_handler_glMultiTexCoord3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord3sv_args args = *(gl_wrap_handler_glMultiTexCoord3sv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord3sv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4d_args args = *(gl_wrap_handler_glMultiTexCoord4d_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4d(ctx, args.target, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glMultiTexCoord4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4dv_args args = *(gl_wrap_handler_glMultiTexCoord4dv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4dv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4f_args args = *(gl_wrap_handler_glMultiTexCoord4f_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4f(ctx, args.target, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glMultiTexCoord4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4fv_args args = *(gl_wrap_handler_glMultiTexCoord4fv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4fv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4i_args args = *(gl_wrap_handler_glMultiTexCoord4i_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4i(ctx, args.target, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glMultiTexCoord4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4iv_args args = *(gl_wrap_handler_glMultiTexCoord4iv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4iv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glMultiTexCoord4s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4s_args args = *(gl_wrap_handler_glMultiTexCoord4s_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4s(ctx, args.target, args.s, args.t, args.r, args.q);
}

inline void gl_wrap_handler_glMultiTexCoord4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoord4sv_args args = *(gl_wrap_handler_glMultiTexCoord4sv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoord4sv(ctx, args.target, args.v);
}

inline void gl_wrap_handler_glLoadTransposeMatrixf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLoadTransposeMatrixf_args args = *(gl_wrap_handler_glLoadTransposeMatrixf_args*)argsPtr;
	gl_wrap_context_glLoadTransposeMatrixf(ctx, args.m);
}

inline void gl_wrap_handler_glLoadTransposeMatrixd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLoadTransposeMatrixd_args args = *(gl_wrap_handler_glLoadTransposeMatrixd_args*)argsPtr;
	gl_wrap_context_glLoadTransposeMatrixd(ctx, args.m);
}

inline void gl_wrap_handler_glMultTransposeMatrixf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultTransposeMatrixf_args args = *(gl_wrap_handler_glMultTransposeMatrixf_args*)argsPtr;
	gl_wrap_context_glMultTransposeMatrixf(ctx, args.m);
}

inline void gl_wrap_handler_glMultTransposeMatrixd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultTransposeMatrixd_args args = *(gl_wrap_handler_glMultTransposeMatrixd_args*)argsPtr;
	gl_wrap_context_glMultTransposeMatrixd(ctx, args.m);
}

inline void gl_wrap_handler_glBlendFuncSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendFuncSeparate_args args = *(gl_wrap_handler_glBlendFuncSeparate_args*)argsPtr;
	gl_wrap_context_glBlendFuncSeparate(ctx, args.sfactorRGB, args.dfactorRGB, args.sfactorAlpha, args.dfactorAlpha);
}

inline void gl_wrap_handler_glMultiDrawArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiDrawArrays_args args = *(gl_wrap_handler_glMultiDrawArrays_args*)argsPtr;
	gl_wrap_context_glMultiDrawArrays(ctx, args.mode, args.first, args.count, args.drawcount);
}

inline void gl_wrap_handler_glMultiDrawElements(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiDrawElements_args args = *(gl_wrap_handler_glMultiDrawElements_args*)argsPtr;
	gl_wrap_context_glMultiDrawElements(ctx, args.mode, args.count, args.type, args.indices, args.drawcount);
}

inline void gl_wrap_handler_glPointParameterf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPointParameterf_args args = *(gl_wrap_handler_glPointParameterf_args*)argsPtr;
	gl_wrap_context_glPointParameterf(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glPointParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPointParameterfv_args args = *(gl_wrap_handler_glPointParameterfv_args*)argsPtr;
	gl_wrap_context_glPointParameterfv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glPointParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPointParameteri_args args = *(gl_wrap_handler_glPointParameteri_args*)argsPtr;
	gl_wrap_context_glPointParameteri(ctx, args.pname, args.param);
}

inline void gl_wrap_handler_glPointParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPointParameteriv_args args = *(gl_wrap_handler_glPointParameteriv_args*)argsPtr;
	gl_wrap_context_glPointParameteriv(ctx, args.pname, args.params);
}

inline void gl_wrap_handler_glFogCoordf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogCoordf_args args = *(gl_wrap_handler_glFogCoordf_args*)argsPtr;
	gl_wrap_context_glFogCoordf(ctx, args.coord);
}

inline void gl_wrap_handler_glFogCoordfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogCoordfv_args args = *(gl_wrap_handler_glFogCoordfv_args*)argsPtr;
	gl_wrap_context_glFogCoordfv(ctx, args.coord);
}

inline void gl_wrap_handler_glFogCoordd(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogCoordd_args args = *(gl_wrap_handler_glFogCoordd_args*)argsPtr;
	gl_wrap_context_glFogCoordd(ctx, args.coord);
}

inline void gl_wrap_handler_glFogCoorddv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogCoorddv_args args = *(gl_wrap_handler_glFogCoorddv_args*)argsPtr;
	gl_wrap_context_glFogCoorddv(ctx, args.coord);
}

inline void gl_wrap_handler_glFogCoordPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFogCoordPointer_args args = *(gl_wrap_handler_glFogCoordPointer_args*)argsPtr;
	gl_wrap_context_glFogCoordPointer(ctx, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glSecondaryColor3b(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3b_args args = *(gl_wrap_handler_glSecondaryColor3b_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3b(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3bv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3bv_args args = *(gl_wrap_handler_glSecondaryColor3bv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3bv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3d_args args = *(gl_wrap_handler_glSecondaryColor3d_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3d(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3dv_args args = *(gl_wrap_handler_glSecondaryColor3dv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3dv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3f_args args = *(gl_wrap_handler_glSecondaryColor3f_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3f(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3fv_args args = *(gl_wrap_handler_glSecondaryColor3fv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3fv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3i_args args = *(gl_wrap_handler_glSecondaryColor3i_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3i(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3iv_args args = *(gl_wrap_handler_glSecondaryColor3iv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3iv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3s_args args = *(gl_wrap_handler_glSecondaryColor3s_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3s(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3sv_args args = *(gl_wrap_handler_glSecondaryColor3sv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3sv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3ub(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3ub_args args = *(gl_wrap_handler_glSecondaryColor3ub_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3ub(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3ubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3ubv_args args = *(gl_wrap_handler_glSecondaryColor3ubv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3ubv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3ui_args args = *(gl_wrap_handler_glSecondaryColor3ui_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3ui(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3uiv_args args = *(gl_wrap_handler_glSecondaryColor3uiv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3uiv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColor3us(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3us_args args = *(gl_wrap_handler_glSecondaryColor3us_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3us(ctx, args.red, args.green, args.blue);
}

inline void gl_wrap_handler_glSecondaryColor3usv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColor3usv_args args = *(gl_wrap_handler_glSecondaryColor3usv_args*)argsPtr;
	gl_wrap_context_glSecondaryColor3usv(ctx, args.v);
}

inline void gl_wrap_handler_glSecondaryColorPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColorPointer_args args = *(gl_wrap_handler_glSecondaryColorPointer_args*)argsPtr;
	gl_wrap_context_glSecondaryColorPointer(ctx, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glWindowPos2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2d_args args = *(gl_wrap_handler_glWindowPos2d_args*)argsPtr;
	gl_wrap_context_glWindowPos2d(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glWindowPos2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2dv_args args = *(gl_wrap_handler_glWindowPos2dv_args*)argsPtr;
	gl_wrap_context_glWindowPos2dv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2f_args args = *(gl_wrap_handler_glWindowPos2f_args*)argsPtr;
	gl_wrap_context_glWindowPos2f(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glWindowPos2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2fv_args args = *(gl_wrap_handler_glWindowPos2fv_args*)argsPtr;
	gl_wrap_context_glWindowPos2fv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2i_args args = *(gl_wrap_handler_glWindowPos2i_args*)argsPtr;
	gl_wrap_context_glWindowPos2i(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glWindowPos2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2iv_args args = *(gl_wrap_handler_glWindowPos2iv_args*)argsPtr;
	gl_wrap_context_glWindowPos2iv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos2s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2s_args args = *(gl_wrap_handler_glWindowPos2s_args*)argsPtr;
	gl_wrap_context_glWindowPos2s(ctx, args.x, args.y);
}

inline void gl_wrap_handler_glWindowPos2sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos2sv_args args = *(gl_wrap_handler_glWindowPos2sv_args*)argsPtr;
	gl_wrap_context_glWindowPos2sv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3d_args args = *(gl_wrap_handler_glWindowPos3d_args*)argsPtr;
	gl_wrap_context_glWindowPos3d(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glWindowPos3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3dv_args args = *(gl_wrap_handler_glWindowPos3dv_args*)argsPtr;
	gl_wrap_context_glWindowPos3dv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3f_args args = *(gl_wrap_handler_glWindowPos3f_args*)argsPtr;
	gl_wrap_context_glWindowPos3f(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glWindowPos3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3fv_args args = *(gl_wrap_handler_glWindowPos3fv_args*)argsPtr;
	gl_wrap_context_glWindowPos3fv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3i_args args = *(gl_wrap_handler_glWindowPos3i_args*)argsPtr;
	gl_wrap_context_glWindowPos3i(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glWindowPos3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3iv_args args = *(gl_wrap_handler_glWindowPos3iv_args*)argsPtr;
	gl_wrap_context_glWindowPos3iv(ctx, args.v);
}

inline void gl_wrap_handler_glWindowPos3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3s_args args = *(gl_wrap_handler_glWindowPos3s_args*)argsPtr;
	gl_wrap_context_glWindowPos3s(ctx, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glWindowPos3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWindowPos3sv_args args = *(gl_wrap_handler_glWindowPos3sv_args*)argsPtr;
	gl_wrap_context_glWindowPos3sv(ctx, args.v);
}

inline void gl_wrap_handler_glBlendColor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendColor_args args = *(gl_wrap_handler_glBlendColor_args*)argsPtr;
	gl_wrap_context_glBlendColor(ctx, args.red, args.green, args.blue, args.alpha);
}

inline void gl_wrap_handler_glBlendEquation(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendEquation_args args = *(gl_wrap_handler_glBlendEquation_args*)argsPtr;
	gl_wrap_context_glBlendEquation(ctx, args.mode);
}

inline void gl_wrap_handler_glGenQueries(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenQueries_args args = *(gl_wrap_handler_glGenQueries_args*)argsPtr;
	gl_wrap_context_glGenQueries(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glDeleteQueries(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteQueries_args args = *(gl_wrap_handler_glDeleteQueries_args*)argsPtr;
	gl_wrap_context_glDeleteQueries(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glBeginQuery(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBeginQuery_args args = *(gl_wrap_handler_glBeginQuery_args*)argsPtr;
	gl_wrap_context_glBeginQuery(ctx, args.target, args.id);
}

inline void gl_wrap_handler_glEndQuery(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndQuery_args args = *(gl_wrap_handler_glEndQuery_args*)argsPtr;
	gl_wrap_context_glEndQuery(ctx, args.target);
}

inline void gl_wrap_handler_glGetQueryiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryiv_args args = *(gl_wrap_handler_glGetQueryiv_args*)argsPtr;
	gl_wrap_context_glGetQueryiv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetQueryObjectiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryObjectiv_args args = *(gl_wrap_handler_glGetQueryObjectiv_args*)argsPtr;
	gl_wrap_context_glGetQueryObjectiv(ctx, args.id, args.pname, args.params);
}

inline void gl_wrap_handler_glGetQueryObjectuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryObjectuiv_args args = *(gl_wrap_handler_glGetQueryObjectuiv_args*)argsPtr;
	gl_wrap_context_glGetQueryObjectuiv(ctx, args.id, args.pname, args.params);
}

inline void gl_wrap_handler_glBindBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBuffer_args args = *(gl_wrap_handler_glBindBuffer_args*)argsPtr;
	gl_wrap_context_glBindBuffer(ctx, args.target, args.buffer);
}

inline void gl_wrap_handler_glDeleteBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteBuffers_args args = *(gl_wrap_handler_glDeleteBuffers_args*)argsPtr;
	gl_wrap_context_glDeleteBuffers(ctx, args.n, args.buffers);
}

inline void gl_wrap_handler_glGenBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenBuffers_args args = *(gl_wrap_handler_glGenBuffers_args*)argsPtr;
	gl_wrap_context_glGenBuffers(ctx, args.n, args.buffers);
}

inline void gl_wrap_handler_glBufferData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBufferData_args args = *(gl_wrap_handler_glBufferData_args*)argsPtr;
	gl_wrap_context_glBufferData(ctx, args.target, args.size, args.data, args.usage);
}

inline void gl_wrap_handler_glBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBufferSubData_args args = *(gl_wrap_handler_glBufferSubData_args*)argsPtr;
	gl_wrap_context_glBufferSubData(ctx, args.target, args.offset, args.size, args.data);
}

inline void gl_wrap_handler_glGetBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferSubData_args args = *(gl_wrap_handler_glGetBufferSubData_args*)argsPtr;
	gl_wrap_context_glGetBufferSubData(ctx, args.target, args.offset, args.size, args.data);
}

inline void gl_wrap_handler_glMapBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapBuffer_args args = *(gl_wrap_handler_glMapBuffer_args*)argsPtr;
	gl_wrap_context_glMapBuffer(ctx, args.target, args.access);
}

inline void gl_wrap_handler_glGetBufferParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferParameteriv_args args = *(gl_wrap_handler_glGetBufferParameteriv_args*)argsPtr;
	gl_wrap_context_glGetBufferParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetBufferPointerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferPointerv_args args = *(gl_wrap_handler_glGetBufferPointerv_args*)argsPtr;
	gl_wrap_context_glGetBufferPointerv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glBlendEquationSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendEquationSeparate_args args = *(gl_wrap_handler_glBlendEquationSeparate_args*)argsPtr;
	gl_wrap_context_glBlendEquationSeparate(ctx, args.modeRGB, args.modeAlpha);
}

inline void gl_wrap_handler_glDrawBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawBuffers_args args = *(gl_wrap_handler_glDrawBuffers_args*)argsPtr;
	gl_wrap_context_glDrawBuffers(ctx, args.n, args.bufs);
}

inline void gl_wrap_handler_glStencilOpSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilOpSeparate_args args = *(gl_wrap_handler_glStencilOpSeparate_args*)argsPtr;
	gl_wrap_context_glStencilOpSeparate(ctx, args.face, args.sfail, args.dpfail, args.dppass);
}

inline void gl_wrap_handler_glStencilFuncSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilFuncSeparate_args args = *(gl_wrap_handler_glStencilFuncSeparate_args*)argsPtr;
	gl_wrap_context_glStencilFuncSeparate(ctx, args.face, args.func, args.ref, args.mask);
}

inline void gl_wrap_handler_glStencilMaskSeparate(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glStencilMaskSeparate_args args = *(gl_wrap_handler_glStencilMaskSeparate_args*)argsPtr;
	gl_wrap_context_glStencilMaskSeparate(ctx, args.face, args.mask);
}

inline void gl_wrap_handler_glAttachShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glAttachShader_args args = *(gl_wrap_handler_glAttachShader_args*)argsPtr;
	gl_wrap_context_glAttachShader(ctx, args.program, args.shader);
}

inline void gl_wrap_handler_glBindAttribLocation(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindAttribLocation_args args = *(gl_wrap_handler_glBindAttribLocation_args*)argsPtr;
	gl_wrap_context_glBindAttribLocation(ctx, args.program, args.index, args.name);
}

inline void gl_wrap_handler_glCompileShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCompileShader_args args = *(gl_wrap_handler_glCompileShader_args*)argsPtr;
	gl_wrap_context_glCompileShader(ctx, args.shader);
}

inline void gl_wrap_handler_glDeleteProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteProgram_args args = *(gl_wrap_handler_glDeleteProgram_args*)argsPtr;
	gl_wrap_context_glDeleteProgram(ctx, args.program);
}

inline void gl_wrap_handler_glDeleteShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteShader_args args = *(gl_wrap_handler_glDeleteShader_args*)argsPtr;
	gl_wrap_context_glDeleteShader(ctx, args.shader);
}

inline void gl_wrap_handler_glDetachShader(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDetachShader_args args = *(gl_wrap_handler_glDetachShader_args*)argsPtr;
	gl_wrap_context_glDetachShader(ctx, args.program, args.shader);
}

inline void gl_wrap_handler_glDisableVertexAttribArray(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDisableVertexAttribArray_args args = *(gl_wrap_handler_glDisableVertexAttribArray_args*)argsPtr;
	gl_wrap_context_glDisableVertexAttribArray(ctx, args.index);
}

inline void gl_wrap_handler_glEnableVertexAttribArray(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnableVertexAttribArray_args args = *(gl_wrap_handler_glEnableVertexAttribArray_args*)argsPtr;
	gl_wrap_context_glEnableVertexAttribArray(ctx, args.index);
}

inline void gl_wrap_handler_glGetActiveAttrib(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveAttrib_args args = *(gl_wrap_handler_glGetActiveAttrib_args*)argsPtr;
	gl_wrap_context_glGetActiveAttrib(ctx, args.program, args.index, args.bufSize, args.length, args.size, args.type, args.name);
}

inline void gl_wrap_handler_glGetActiveUniform(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniform_args args = *(gl_wrap_handler_glGetActiveUniform_args*)argsPtr;
	gl_wrap_context_glGetActiveUniform(ctx, args.program, args.index, args.bufSize, args.length, args.size, args.type, args.name);
}

inline void gl_wrap_handler_glGetAttachedShaders(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetAttachedShaders_args args = *(gl_wrap_handler_glGetAttachedShaders_args*)argsPtr;
	gl_wrap_context_glGetAttachedShaders(ctx, args.program, args.maxCount, args.count, args.shaders);
}

inline void gl_wrap_handler_glGetProgramiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramiv_args args = *(gl_wrap_handler_glGetProgramiv_args*)argsPtr;
	gl_wrap_context_glGetProgramiv(ctx, args.program, args.pname, args.params);
}

inline void gl_wrap_handler_glGetProgramInfoLog(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramInfoLog_args args = *(gl_wrap_handler_glGetProgramInfoLog_args*)argsPtr;
	gl_wrap_context_glGetProgramInfoLog(ctx, args.program, args.bufSize, args.length, args.infoLog);
}

inline void gl_wrap_handler_glGetShaderiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderiv_args args = *(gl_wrap_handler_glGetShaderiv_args*)argsPtr;
	gl_wrap_context_glGetShaderiv(ctx, args.shader, args.pname, args.params);
}

inline void gl_wrap_handler_glGetShaderInfoLog(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderInfoLog_args args = *(gl_wrap_handler_glGetShaderInfoLog_args*)argsPtr;
	gl_wrap_context_glGetShaderInfoLog(ctx, args.shader, args.bufSize, args.length, args.infoLog);
}

inline void gl_wrap_handler_glGetShaderSource(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderSource_args args = *(gl_wrap_handler_glGetShaderSource_args*)argsPtr;
	gl_wrap_context_glGetShaderSource(ctx, args.shader, args.bufSize, args.length, args.source);
}

inline void gl_wrap_handler_glGetUniformfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformfv_args args = *(gl_wrap_handler_glGetUniformfv_args*)argsPtr;
	gl_wrap_context_glGetUniformfv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glGetUniformiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformiv_args args = *(gl_wrap_handler_glGetUniformiv_args*)argsPtr;
	gl_wrap_context_glGetUniformiv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribdv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribdv_args args = *(gl_wrap_handler_glGetVertexAttribdv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribdv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribfv_args args = *(gl_wrap_handler_glGetVertexAttribfv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribfv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribiv_args args = *(gl_wrap_handler_glGetVertexAttribiv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribiv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribPointerv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribPointerv_args args = *(gl_wrap_handler_glGetVertexAttribPointerv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribPointerv(ctx, args.index, args.pname, args.pointer);
}

inline void gl_wrap_handler_glLinkProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glLinkProgram_args args = *(gl_wrap_handler_glLinkProgram_args*)argsPtr;
	gl_wrap_context_glLinkProgram(ctx, args.program);
}

inline void gl_wrap_handler_glShaderSource(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glShaderSource_args args = *(gl_wrap_handler_glShaderSource_args*)argsPtr;
	gl_wrap_context_glShaderSource(ctx, args.shader, args.count, args.string, args.length);
}

inline void gl_wrap_handler_glUseProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUseProgram_args args = *(gl_wrap_handler_glUseProgram_args*)argsPtr;
	gl_wrap_context_glUseProgram(ctx, args.program);
}

inline void gl_wrap_handler_glUniform1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1f_args args = *(gl_wrap_handler_glUniform1f_args*)argsPtr;
	gl_wrap_context_glUniform1f(ctx, args.location, args.v0);
}

inline void gl_wrap_handler_glUniform2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2f_args args = *(gl_wrap_handler_glUniform2f_args*)argsPtr;
	gl_wrap_context_glUniform2f(ctx, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glUniform3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3f_args args = *(gl_wrap_handler_glUniform3f_args*)argsPtr;
	gl_wrap_context_glUniform3f(ctx, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glUniform4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4f_args args = *(gl_wrap_handler_glUniform4f_args*)argsPtr;
	gl_wrap_context_glUniform4f(ctx, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glUniform1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1i_args args = *(gl_wrap_handler_glUniform1i_args*)argsPtr;
	gl_wrap_context_glUniform1i(ctx, args.location, args.v0);
}

inline void gl_wrap_handler_glUniform2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2i_args args = *(gl_wrap_handler_glUniform2i_args*)argsPtr;
	gl_wrap_context_glUniform2i(ctx, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glUniform3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3i_args args = *(gl_wrap_handler_glUniform3i_args*)argsPtr;
	gl_wrap_context_glUniform3i(ctx, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glUniform4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4i_args args = *(gl_wrap_handler_glUniform4i_args*)argsPtr;
	gl_wrap_context_glUniform4i(ctx, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glUniform1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1fv_args args = *(gl_wrap_handler_glUniform1fv_args*)argsPtr;
	gl_wrap_context_glUniform1fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2fv_args args = *(gl_wrap_handler_glUniform2fv_args*)argsPtr;
	gl_wrap_context_glUniform2fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3fv_args args = *(gl_wrap_handler_glUniform3fv_args*)argsPtr;
	gl_wrap_context_glUniform3fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4fv_args args = *(gl_wrap_handler_glUniform4fv_args*)argsPtr;
	gl_wrap_context_glUniform4fv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1iv_args args = *(gl_wrap_handler_glUniform1iv_args*)argsPtr;
	gl_wrap_context_glUniform1iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2iv_args args = *(gl_wrap_handler_glUniform2iv_args*)argsPtr;
	gl_wrap_context_glUniform2iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3iv_args args = *(gl_wrap_handler_glUniform3iv_args*)argsPtr;
	gl_wrap_context_glUniform3iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4iv_args args = *(gl_wrap_handler_glUniform4iv_args*)argsPtr;
	gl_wrap_context_glUniform4iv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2fv_args args = *(gl_wrap_handler_glUniformMatrix2fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3fv_args args = *(gl_wrap_handler_glUniformMatrix3fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4fv_args args = *(gl_wrap_handler_glUniformMatrix4fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glValidateProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glValidateProgram_args args = *(gl_wrap_handler_glValidateProgram_args*)argsPtr;
	gl_wrap_context_glValidateProgram(ctx, args.program);
}

inline void gl_wrap_handler_glVertexAttrib1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1d_args args = *(gl_wrap_handler_glVertexAttrib1d_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1d(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttrib1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1dv_args args = *(gl_wrap_handler_glVertexAttrib1dv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1f_args args = *(gl_wrap_handler_glVertexAttrib1f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1f(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttrib1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1fv_args args = *(gl_wrap_handler_glVertexAttrib1fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib1s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1s_args args = *(gl_wrap_handler_glVertexAttrib1s_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1s(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttrib1sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib1sv_args args = *(gl_wrap_handler_glVertexAttrib1sv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib1sv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2d_args args = *(gl_wrap_handler_glVertexAttrib2d_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2d(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttrib2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2dv_args args = *(gl_wrap_handler_glVertexAttrib2dv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2f_args args = *(gl_wrap_handler_glVertexAttrib2f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2f(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttrib2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2fv_args args = *(gl_wrap_handler_glVertexAttrib2fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib2s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2s_args args = *(gl_wrap_handler_glVertexAttrib2s_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2s(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttrib2sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib2sv_args args = *(gl_wrap_handler_glVertexAttrib2sv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib2sv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3d_args args = *(gl_wrap_handler_glVertexAttrib3d_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3d(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttrib3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3dv_args args = *(gl_wrap_handler_glVertexAttrib3dv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3f_args args = *(gl_wrap_handler_glVertexAttrib3f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3f(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttrib3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3fv_args args = *(gl_wrap_handler_glVertexAttrib3fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib3s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3s_args args = *(gl_wrap_handler_glVertexAttrib3s_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3s(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttrib3sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib3sv_args args = *(gl_wrap_handler_glVertexAttrib3sv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib3sv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4Nbv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Nbv_args args = *(gl_wrap_handler_glVertexAttrib4Nbv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Nbv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4Niv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Niv_args args = *(gl_wrap_handler_glVertexAttrib4Niv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Niv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4Nsv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Nsv_args args = *(gl_wrap_handler_glVertexAttrib4Nsv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Nsv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4Nub(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Nub_args args = *(gl_wrap_handler_glVertexAttrib4Nub_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Nub(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttrib4Nubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Nubv_args args = *(gl_wrap_handler_glVertexAttrib4Nubv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Nubv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4Nuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Nuiv_args args = *(gl_wrap_handler_glVertexAttrib4Nuiv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Nuiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4Nusv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4Nusv_args args = *(gl_wrap_handler_glVertexAttrib4Nusv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4Nusv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4bv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4bv_args args = *(gl_wrap_handler_glVertexAttrib4bv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4bv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4d_args args = *(gl_wrap_handler_glVertexAttrib4d_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4d(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttrib4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4dv_args args = *(gl_wrap_handler_glVertexAttrib4dv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4f_args args = *(gl_wrap_handler_glVertexAttrib4f_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4f(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttrib4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4fv_args args = *(gl_wrap_handler_glVertexAttrib4fv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4fv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4iv_args args = *(gl_wrap_handler_glVertexAttrib4iv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4iv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4s(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4s_args args = *(gl_wrap_handler_glVertexAttrib4s_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4s(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttrib4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4sv_args args = *(gl_wrap_handler_glVertexAttrib4sv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4sv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4ubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4ubv_args args = *(gl_wrap_handler_glVertexAttrib4ubv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4ubv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4uiv_args args = *(gl_wrap_handler_glVertexAttrib4uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4uiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttrib4usv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttrib4usv_args args = *(gl_wrap_handler_glVertexAttrib4usv_args*)argsPtr;
	gl_wrap_context_glVertexAttrib4usv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribPointer_args args = *(gl_wrap_handler_glVertexAttribPointer_args*)argsPtr;
	gl_wrap_context_glVertexAttribPointer(ctx, args.index, args.size, args.type, args.normalized, args.stride, args.pointer);
}

inline void gl_wrap_handler_glUniformMatrix2x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2x3fv_args args = *(gl_wrap_handler_glUniformMatrix2x3fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2x3fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3x2fv_args args = *(gl_wrap_handler_glUniformMatrix3x2fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3x2fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2x4fv_args args = *(gl_wrap_handler_glUniformMatrix2x4fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2x4fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4x2fv_args args = *(gl_wrap_handler_glUniformMatrix4x2fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4x2fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3x4fv_args args = *(gl_wrap_handler_glUniformMatrix3x4fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3x4fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4x3fv_args args = *(gl_wrap_handler_glUniformMatrix4x3fv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4x3fv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glColorMaski(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorMaski_args args = *(gl_wrap_handler_glColorMaski_args*)argsPtr;
	gl_wrap_context_glColorMaski(ctx, args.index, args.r, args.g, args.b, args.a);
}

inline void gl_wrap_handler_glGetBooleani_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBooleani_v_args args = *(gl_wrap_handler_glGetBooleani_v_args*)argsPtr;
	gl_wrap_context_glGetBooleani_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glGetIntegeri_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetIntegeri_v_args args = *(gl_wrap_handler_glGetIntegeri_v_args*)argsPtr;
	gl_wrap_context_glGetIntegeri_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glEnablei(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEnablei_args args = *(gl_wrap_handler_glEnablei_args*)argsPtr;
	gl_wrap_context_glEnablei(ctx, args.target, args.index);
}

inline void gl_wrap_handler_glDisablei(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDisablei_args args = *(gl_wrap_handler_glDisablei_args*)argsPtr;
	gl_wrap_context_glDisablei(ctx, args.target, args.index);
}

inline void gl_wrap_handler_glBeginTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBeginTransformFeedback_args args = *(gl_wrap_handler_glBeginTransformFeedback_args*)argsPtr;
	gl_wrap_context_glBeginTransformFeedback(ctx, args.primitiveMode);
}

inline void gl_wrap_handler_glEndTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndTransformFeedback_args args = *(gl_wrap_handler_glEndTransformFeedback_args*)argsPtr;
	gl_wrap_context_glEndTransformFeedback(ctx);
}

inline void gl_wrap_handler_glBindBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBufferRange_args args = *(gl_wrap_handler_glBindBufferRange_args*)argsPtr;
	gl_wrap_context_glBindBufferRange(ctx, args.target, args.index, args.buffer, args.offset, args.size);
}

inline void gl_wrap_handler_glBindBufferBase(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBufferBase_args args = *(gl_wrap_handler_glBindBufferBase_args*)argsPtr;
	gl_wrap_context_glBindBufferBase(ctx, args.target, args.index, args.buffer);
}

inline void gl_wrap_handler_glTransformFeedbackVaryings(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTransformFeedbackVaryings_args args = *(gl_wrap_handler_glTransformFeedbackVaryings_args*)argsPtr;
	gl_wrap_context_glTransformFeedbackVaryings(ctx, args.program, args.count, args.varyings, args.bufferMode);
}

inline void gl_wrap_handler_glGetTransformFeedbackVarying(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTransformFeedbackVarying_args args = *(gl_wrap_handler_glGetTransformFeedbackVarying_args*)argsPtr;
	gl_wrap_context_glGetTransformFeedbackVarying(ctx, args.program, args.index, args.bufSize, args.length, args.size, args.type, args.name);
}

inline void gl_wrap_handler_glClampColor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClampColor_args args = *(gl_wrap_handler_glClampColor_args*)argsPtr;
	gl_wrap_context_glClampColor(ctx, args.target, args.clamp);
}

inline void gl_wrap_handler_glBeginConditionalRender(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBeginConditionalRender_args args = *(gl_wrap_handler_glBeginConditionalRender_args*)argsPtr;
	gl_wrap_context_glBeginConditionalRender(ctx, args.id, args.mode);
}

inline void gl_wrap_handler_glEndConditionalRender(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndConditionalRender_args args = *(gl_wrap_handler_glEndConditionalRender_args*)argsPtr;
	gl_wrap_context_glEndConditionalRender(ctx);
}

inline void gl_wrap_handler_glVertexAttribIPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribIPointer_args args = *(gl_wrap_handler_glVertexAttribIPointer_args*)argsPtr;
	gl_wrap_context_glVertexAttribIPointer(ctx, args.index, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glGetVertexAttribIiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribIiv_args args = *(gl_wrap_handler_glGetVertexAttribIiv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribIiv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glGetVertexAttribIuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribIuiv_args args = *(gl_wrap_handler_glGetVertexAttribIuiv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribIuiv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glVertexAttribI1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI1i_args args = *(gl_wrap_handler_glVertexAttribI1i_args*)argsPtr;
	gl_wrap_context_glVertexAttribI1i(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttribI2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI2i_args args = *(gl_wrap_handler_glVertexAttribI2i_args*)argsPtr;
	gl_wrap_context_glVertexAttribI2i(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttribI3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI3i_args args = *(gl_wrap_handler_glVertexAttribI3i_args*)argsPtr;
	gl_wrap_context_glVertexAttribI3i(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttribI4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4i_args args = *(gl_wrap_handler_glVertexAttribI4i_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4i(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttribI1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI1ui_args args = *(gl_wrap_handler_glVertexAttribI1ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribI1ui(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttribI2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI2ui_args args = *(gl_wrap_handler_glVertexAttribI2ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribI2ui(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttribI3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI3ui_args args = *(gl_wrap_handler_glVertexAttribI3ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribI3ui(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttribI4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4ui_args args = *(gl_wrap_handler_glVertexAttribI4ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4ui(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttribI1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI1iv_args args = *(gl_wrap_handler_glVertexAttribI1iv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI1iv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI2iv_args args = *(gl_wrap_handler_glVertexAttribI2iv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI2iv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI3iv_args args = *(gl_wrap_handler_glVertexAttribI3iv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI3iv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4iv_args args = *(gl_wrap_handler_glVertexAttribI4iv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4iv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI1uiv_args args = *(gl_wrap_handler_glVertexAttribI1uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI1uiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI2uiv_args args = *(gl_wrap_handler_glVertexAttribI2uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI2uiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI3uiv_args args = *(gl_wrap_handler_glVertexAttribI3uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI3uiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4uiv_args args = *(gl_wrap_handler_glVertexAttribI4uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4uiv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4bv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4bv_args args = *(gl_wrap_handler_glVertexAttribI4bv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4bv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4sv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4sv_args args = *(gl_wrap_handler_glVertexAttribI4sv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4sv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4ubv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4ubv_args args = *(gl_wrap_handler_glVertexAttribI4ubv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4ubv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribI4usv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribI4usv_args args = *(gl_wrap_handler_glVertexAttribI4usv_args*)argsPtr;
	gl_wrap_context_glVertexAttribI4usv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glGetUniformuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformuiv_args args = *(gl_wrap_handler_glGetUniformuiv_args*)argsPtr;
	gl_wrap_context_glGetUniformuiv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glBindFragDataLocation(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindFragDataLocation_args args = *(gl_wrap_handler_glBindFragDataLocation_args*)argsPtr;
	gl_wrap_context_glBindFragDataLocation(ctx, args.program, args.color, args.name);
}

inline void gl_wrap_handler_glUniform1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1ui_args args = *(gl_wrap_handler_glUniform1ui_args*)argsPtr;
	gl_wrap_context_glUniform1ui(ctx, args.location, args.v0);
}

inline void gl_wrap_handler_glUniform2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2ui_args args = *(gl_wrap_handler_glUniform2ui_args*)argsPtr;
	gl_wrap_context_glUniform2ui(ctx, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glUniform3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3ui_args args = *(gl_wrap_handler_glUniform3ui_args*)argsPtr;
	gl_wrap_context_glUniform3ui(ctx, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glUniform4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4ui_args args = *(gl_wrap_handler_glUniform4ui_args*)argsPtr;
	gl_wrap_context_glUniform4ui(ctx, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glUniform1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1uiv_args args = *(gl_wrap_handler_glUniform1uiv_args*)argsPtr;
	gl_wrap_context_glUniform1uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2uiv_args args = *(gl_wrap_handler_glUniform2uiv_args*)argsPtr;
	gl_wrap_context_glUniform2uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3uiv_args args = *(gl_wrap_handler_glUniform3uiv_args*)argsPtr;
	gl_wrap_context_glUniform3uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4uiv_args args = *(gl_wrap_handler_glUniform4uiv_args*)argsPtr;
	gl_wrap_context_glUniform4uiv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glTexParameterIiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameterIiv_args args = *(gl_wrap_handler_glTexParameterIiv_args*)argsPtr;
	gl_wrap_context_glTexParameterIiv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glTexParameterIuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexParameterIuiv_args args = *(gl_wrap_handler_glTexParameterIuiv_args*)argsPtr;
	gl_wrap_context_glTexParameterIuiv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexParameterIiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexParameterIiv_args args = *(gl_wrap_handler_glGetTexParameterIiv_args*)argsPtr;
	gl_wrap_context_glGetTexParameterIiv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetTexParameterIuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetTexParameterIuiv_args args = *(gl_wrap_handler_glGetTexParameterIuiv_args*)argsPtr;
	gl_wrap_context_glGetTexParameterIuiv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glClearBufferiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferiv_args args = *(gl_wrap_handler_glClearBufferiv_args*)argsPtr;
	gl_wrap_context_glClearBufferiv(ctx, args.buffer, args.drawbuffer, args.value);
}

inline void gl_wrap_handler_glClearBufferuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferuiv_args args = *(gl_wrap_handler_glClearBufferuiv_args*)argsPtr;
	gl_wrap_context_glClearBufferuiv(ctx, args.buffer, args.drawbuffer, args.value);
}

inline void gl_wrap_handler_glClearBufferfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferfv_args args = *(gl_wrap_handler_glClearBufferfv_args*)argsPtr;
	gl_wrap_context_glClearBufferfv(ctx, args.buffer, args.drawbuffer, args.value);
}

inline void gl_wrap_handler_glClearBufferfi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferfi_args args = *(gl_wrap_handler_glClearBufferfi_args*)argsPtr;
	gl_wrap_context_glClearBufferfi(ctx, args.buffer, args.drawbuffer, args.depth, args.stencil);
}

inline void gl_wrap_handler_glBindRenderbuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindRenderbuffer_args args = *(gl_wrap_handler_glBindRenderbuffer_args*)argsPtr;
	gl_wrap_context_glBindRenderbuffer(ctx, args.target, args.renderbuffer);
}

inline void gl_wrap_handler_glDeleteRenderbuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteRenderbuffers_args args = *(gl_wrap_handler_glDeleteRenderbuffers_args*)argsPtr;
	gl_wrap_context_glDeleteRenderbuffers(ctx, args.n, args.renderbuffers);
}

inline void gl_wrap_handler_glGenRenderbuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenRenderbuffers_args args = *(gl_wrap_handler_glGenRenderbuffers_args*)argsPtr;
	gl_wrap_context_glGenRenderbuffers(ctx, args.n, args.renderbuffers);
}

inline void gl_wrap_handler_glRenderbufferStorage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRenderbufferStorage_args args = *(gl_wrap_handler_glRenderbufferStorage_args*)argsPtr;
	gl_wrap_context_glRenderbufferStorage(ctx, args.target, args.internalformat, args.width, args.height);
}

inline void gl_wrap_handler_glGetRenderbufferParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetRenderbufferParameteriv_args args = *(gl_wrap_handler_glGetRenderbufferParameteriv_args*)argsPtr;
	gl_wrap_context_glGetRenderbufferParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glBindFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindFramebuffer_args args = *(gl_wrap_handler_glBindFramebuffer_args*)argsPtr;
	gl_wrap_context_glBindFramebuffer(ctx, args.target, args.framebuffer);
}

inline void gl_wrap_handler_glDeleteFramebuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteFramebuffers_args args = *(gl_wrap_handler_glDeleteFramebuffers_args*)argsPtr;
	gl_wrap_context_glDeleteFramebuffers(ctx, args.n, args.framebuffers);
}

inline void gl_wrap_handler_glGenFramebuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenFramebuffers_args args = *(gl_wrap_handler_glGenFramebuffers_args*)argsPtr;
	gl_wrap_context_glGenFramebuffers(ctx, args.n, args.framebuffers);
}

inline void gl_wrap_handler_glFramebufferTexture1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTexture1D_args args = *(gl_wrap_handler_glFramebufferTexture1D_args*)argsPtr;
	gl_wrap_context_glFramebufferTexture1D(ctx, args.target, args.attachment, args.textarget, args.texture, args.level);
}

inline void gl_wrap_handler_glFramebufferTexture2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTexture2D_args args = *(gl_wrap_handler_glFramebufferTexture2D_args*)argsPtr;
	gl_wrap_context_glFramebufferTexture2D(ctx, args.target, args.attachment, args.textarget, args.texture, args.level);
}

inline void gl_wrap_handler_glFramebufferTexture3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTexture3D_args args = *(gl_wrap_handler_glFramebufferTexture3D_args*)argsPtr;
	gl_wrap_context_glFramebufferTexture3D(ctx, args.target, args.attachment, args.textarget, args.texture, args.level, args.zoffset);
}

inline void gl_wrap_handler_glFramebufferRenderbuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferRenderbuffer_args args = *(gl_wrap_handler_glFramebufferRenderbuffer_args*)argsPtr;
	gl_wrap_context_glFramebufferRenderbuffer(ctx, args.target, args.attachment, args.renderbuffertarget, args.renderbuffer);
}

inline void gl_wrap_handler_glGetFramebufferAttachmentParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args args = *(gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args*)argsPtr;
	gl_wrap_context_glGetFramebufferAttachmentParameteriv(ctx, args.target, args.attachment, args.pname, args.params);
}

inline void gl_wrap_handler_glGenerateMipmap(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenerateMipmap_args args = *(gl_wrap_handler_glGenerateMipmap_args*)argsPtr;
	gl_wrap_context_glGenerateMipmap(ctx, args.target);
}

inline void gl_wrap_handler_glBlitFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlitFramebuffer_args args = *(gl_wrap_handler_glBlitFramebuffer_args*)argsPtr;
	gl_wrap_context_glBlitFramebuffer(ctx, args.srcX0, args.srcY0, args.srcX1, args.srcY1, args.dstX0, args.dstY0, args.dstX1, args.dstY1, args.mask, args.filter);
}

inline void gl_wrap_handler_glRenderbufferStorageMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glRenderbufferStorageMultisample_args args = *(gl_wrap_handler_glRenderbufferStorageMultisample_args*)argsPtr;
	gl_wrap_context_glRenderbufferStorageMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height);
}

inline void gl_wrap_handler_glFramebufferTextureLayer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTextureLayer_args args = *(gl_wrap_handler_glFramebufferTextureLayer_args*)argsPtr;
	gl_wrap_context_glFramebufferTextureLayer(ctx, args.target, args.attachment, args.texture, args.level, args.layer);
}

inline void gl_wrap_handler_glMapBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMapBufferRange_args args = *(gl_wrap_handler_glMapBufferRange_args*)argsPtr;
	gl_wrap_context_glMapBufferRange(ctx, args.target, args.offset, args.length, args.access);
}

inline void gl_wrap_handler_glFlushMappedBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFlushMappedBufferRange_args args = *(gl_wrap_handler_glFlushMappedBufferRange_args*)argsPtr;
	gl_wrap_context_glFlushMappedBufferRange(ctx, args.target, args.offset, args.length);
}

inline void gl_wrap_handler_glBindVertexArray(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindVertexArray_args args = *(gl_wrap_handler_glBindVertexArray_args*)argsPtr;
	gl_wrap_context_glBindVertexArray(ctx, args.array);
}

inline void gl_wrap_handler_glDeleteVertexArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteVertexArrays_args args = *(gl_wrap_handler_glDeleteVertexArrays_args*)argsPtr;
	gl_wrap_context_glDeleteVertexArrays(ctx, args.n, args.arrays);
}

inline void gl_wrap_handler_glGenVertexArrays(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenVertexArrays_args args = *(gl_wrap_handler_glGenVertexArrays_args*)argsPtr;
	gl_wrap_context_glGenVertexArrays(ctx, args.n, args.arrays);
}

inline void gl_wrap_handler_glDrawArraysInstanced(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArraysInstanced_args args = *(gl_wrap_handler_glDrawArraysInstanced_args*)argsPtr;
	gl_wrap_context_glDrawArraysInstanced(ctx, args.mode, args.first, args.count, args.instancecount);
}

inline void gl_wrap_handler_glDrawElementsInstanced(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsInstanced_args args = *(gl_wrap_handler_glDrawElementsInstanced_args*)argsPtr;
	gl_wrap_context_glDrawElementsInstanced(ctx, args.mode, args.count, args.type, args.indices, args.instancecount);
}

inline void gl_wrap_handler_glTexBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexBuffer_args args = *(gl_wrap_handler_glTexBuffer_args*)argsPtr;
	gl_wrap_context_glTexBuffer(ctx, args.target, args.internalformat, args.buffer);
}

inline void gl_wrap_handler_glPrimitiveRestartIndex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPrimitiveRestartIndex_args args = *(gl_wrap_handler_glPrimitiveRestartIndex_args*)argsPtr;
	gl_wrap_context_glPrimitiveRestartIndex(ctx, args.index);
}

inline void gl_wrap_handler_glCopyBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyBufferSubData_args args = *(gl_wrap_handler_glCopyBufferSubData_args*)argsPtr;
	gl_wrap_context_glCopyBufferSubData(ctx, args.readTarget, args.writeTarget, args.readOffset, args.writeOffset, args.size);
}

inline void gl_wrap_handler_glGetUniformIndices(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformIndices_args args = *(gl_wrap_handler_glGetUniformIndices_args*)argsPtr;
	gl_wrap_context_glGetUniformIndices(ctx, args.program, args.uniformCount, args.uniformNames, args.uniformIndices);
}

inline void gl_wrap_handler_glGetActiveUniformsiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformsiv_args args = *(gl_wrap_handler_glGetActiveUniformsiv_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformsiv(ctx, args.program, args.uniformCount, args.uniformIndices, args.pname, args.params);
}

inline void gl_wrap_handler_glGetActiveUniformName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformName_args args = *(gl_wrap_handler_glGetActiveUniformName_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformName(ctx, args.program, args.uniformIndex, args.bufSize, args.length, args.uniformName);
}

inline void gl_wrap_handler_glGetActiveUniformBlockiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformBlockiv_args args = *(gl_wrap_handler_glGetActiveUniformBlockiv_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformBlockiv(ctx, args.program, args.uniformBlockIndex, args.pname, args.params);
}

inline void gl_wrap_handler_glGetActiveUniformBlockName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveUniformBlockName_args args = *(gl_wrap_handler_glGetActiveUniformBlockName_args*)argsPtr;
	gl_wrap_context_glGetActiveUniformBlockName(ctx, args.program, args.uniformBlockIndex, args.bufSize, args.length, args.uniformBlockName);
}

inline void gl_wrap_handler_glUniformBlockBinding(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformBlockBinding_args args = *(gl_wrap_handler_glUniformBlockBinding_args*)argsPtr;
	gl_wrap_context_glUniformBlockBinding(ctx, args.program, args.uniformBlockIndex, args.uniformBlockBinding);
}

inline void gl_wrap_handler_glDrawElementsBaseVertex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsBaseVertex_args args = *(gl_wrap_handler_glDrawElementsBaseVertex_args*)argsPtr;
	gl_wrap_context_glDrawElementsBaseVertex(ctx, args.mode, args.count, args.type, args.indices, args.basevertex);
}

inline void gl_wrap_handler_glDrawRangeElementsBaseVertex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawRangeElementsBaseVertex_args args = *(gl_wrap_handler_glDrawRangeElementsBaseVertex_args*)argsPtr;
	gl_wrap_context_glDrawRangeElementsBaseVertex(ctx, args.mode, args.start, args.end, args.count, args.type, args.indices, args.basevertex);
}

inline void gl_wrap_handler_glDrawElementsInstancedBaseVertex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsInstancedBaseVertex_args args = *(gl_wrap_handler_glDrawElementsInstancedBaseVertex_args*)argsPtr;
	gl_wrap_context_glDrawElementsInstancedBaseVertex(ctx, args.mode, args.count, args.type, args.indices, args.instancecount, args.basevertex);
}

inline void gl_wrap_handler_glMultiDrawElementsBaseVertex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiDrawElementsBaseVertex_args args = *(gl_wrap_handler_glMultiDrawElementsBaseVertex_args*)argsPtr;
	gl_wrap_context_glMultiDrawElementsBaseVertex(ctx, args.mode, args.count, args.type, args.indices, args.drawcount, args.basevertex);
}

inline void gl_wrap_handler_glProvokingVertex(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProvokingVertex_args args = *(gl_wrap_handler_glProvokingVertex_args*)argsPtr;
	gl_wrap_context_glProvokingVertex(ctx, args.mode);
}

inline void gl_wrap_handler_glDeleteSync(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteSync_args args = *(gl_wrap_handler_glDeleteSync_args*)argsPtr;
	gl_wrap_context_glDeleteSync(ctx, args.sync);
}

inline void gl_wrap_handler_glWaitSync(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glWaitSync_args args = *(gl_wrap_handler_glWaitSync_args*)argsPtr;
	gl_wrap_context_glWaitSync(ctx, args.sync, args.flags, args.timeout);
}

inline void gl_wrap_handler_glGetInteger64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInteger64v_args args = *(gl_wrap_handler_glGetInteger64v_args*)argsPtr;
	gl_wrap_context_glGetInteger64v(ctx, args.pname, args.data);
}

inline void gl_wrap_handler_glGetSynciv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSynciv_args args = *(gl_wrap_handler_glGetSynciv_args*)argsPtr;
	gl_wrap_context_glGetSynciv(ctx, args.sync, args.pname, args.bufSize, args.length, args.values);
}

inline void gl_wrap_handler_glGetInteger64i_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInteger64i_v_args args = *(gl_wrap_handler_glGetInteger64i_v_args*)argsPtr;
	gl_wrap_context_glGetInteger64i_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glGetBufferParameteri64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetBufferParameteri64v_args args = *(gl_wrap_handler_glGetBufferParameteri64v_args*)argsPtr;
	gl_wrap_context_glGetBufferParameteri64v(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glFramebufferTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferTexture_args args = *(gl_wrap_handler_glFramebufferTexture_args*)argsPtr;
	gl_wrap_context_glFramebufferTexture(ctx, args.target, args.attachment, args.texture, args.level);
}

inline void gl_wrap_handler_glTexImage2DMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage2DMultisample_args args = *(gl_wrap_handler_glTexImage2DMultisample_args*)argsPtr;
	gl_wrap_context_glTexImage2DMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height, args.fixedsamplelocations);
}

inline void gl_wrap_handler_glTexImage3DMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexImage3DMultisample_args args = *(gl_wrap_handler_glTexImage3DMultisample_args*)argsPtr;
	gl_wrap_context_glTexImage3DMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height, args.depth, args.fixedsamplelocations);
}

inline void gl_wrap_handler_glGetMultisamplefv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetMultisamplefv_args args = *(gl_wrap_handler_glGetMultisamplefv_args*)argsPtr;
	gl_wrap_context_glGetMultisamplefv(ctx, args.pname, args.index, args.val);
}

inline void gl_wrap_handler_glSampleMaski(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSampleMaski_args args = *(gl_wrap_handler_glSampleMaski_args*)argsPtr;
	gl_wrap_context_glSampleMaski(ctx, args.maskNumber, args.mask);
}

inline void gl_wrap_handler_glBindFragDataLocationIndexed(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindFragDataLocationIndexed_args args = *(gl_wrap_handler_glBindFragDataLocationIndexed_args*)argsPtr;
	gl_wrap_context_glBindFragDataLocationIndexed(ctx, args.program, args.colorNumber, args.index, args.name);
}

inline void gl_wrap_handler_glGenSamplers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenSamplers_args args = *(gl_wrap_handler_glGenSamplers_args*)argsPtr;
	gl_wrap_context_glGenSamplers(ctx, args.count, args.samplers);
}

inline void gl_wrap_handler_glDeleteSamplers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteSamplers_args args = *(gl_wrap_handler_glDeleteSamplers_args*)argsPtr;
	gl_wrap_context_glDeleteSamplers(ctx, args.count, args.samplers);
}

inline void gl_wrap_handler_glBindSampler(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindSampler_args args = *(gl_wrap_handler_glBindSampler_args*)argsPtr;
	gl_wrap_context_glBindSampler(ctx, args.unit, args.sampler);
}

inline void gl_wrap_handler_glSamplerParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameteri_args args = *(gl_wrap_handler_glSamplerParameteri_args*)argsPtr;
	gl_wrap_context_glSamplerParameteri(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameteriv_args args = *(gl_wrap_handler_glSamplerParameteriv_args*)argsPtr;
	gl_wrap_context_glSamplerParameteriv(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameterf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameterf_args args = *(gl_wrap_handler_glSamplerParameterf_args*)argsPtr;
	gl_wrap_context_glSamplerParameterf(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameterfv_args args = *(gl_wrap_handler_glSamplerParameterfv_args*)argsPtr;
	gl_wrap_context_glSamplerParameterfv(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameterIiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameterIiv_args args = *(gl_wrap_handler_glSamplerParameterIiv_args*)argsPtr;
	gl_wrap_context_glSamplerParameterIiv(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glSamplerParameterIuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSamplerParameterIuiv_args args = *(gl_wrap_handler_glSamplerParameterIuiv_args*)argsPtr;
	gl_wrap_context_glSamplerParameterIuiv(ctx, args.sampler, args.pname, args.param);
}

inline void gl_wrap_handler_glGetSamplerParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSamplerParameteriv_args args = *(gl_wrap_handler_glGetSamplerParameteriv_args*)argsPtr;
	gl_wrap_context_glGetSamplerParameteriv(ctx, args.sampler, args.pname, args.params);
}

inline void gl_wrap_handler_glGetSamplerParameterIiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSamplerParameterIiv_args args = *(gl_wrap_handler_glGetSamplerParameterIiv_args*)argsPtr;
	gl_wrap_context_glGetSamplerParameterIiv(ctx, args.sampler, args.pname, args.params);
}

inline void gl_wrap_handler_glGetSamplerParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSamplerParameterfv_args args = *(gl_wrap_handler_glGetSamplerParameterfv_args*)argsPtr;
	gl_wrap_context_glGetSamplerParameterfv(ctx, args.sampler, args.pname, args.params);
}

inline void gl_wrap_handler_glGetSamplerParameterIuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetSamplerParameterIuiv_args args = *(gl_wrap_handler_glGetSamplerParameterIuiv_args*)argsPtr;
	gl_wrap_context_glGetSamplerParameterIuiv(ctx, args.sampler, args.pname, args.params);
}

inline void gl_wrap_handler_glQueryCounter(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glQueryCounter_args args = *(gl_wrap_handler_glQueryCounter_args*)argsPtr;
	gl_wrap_context_glQueryCounter(ctx, args.id, args.target);
}

inline void gl_wrap_handler_glGetQueryObjecti64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryObjecti64v_args args = *(gl_wrap_handler_glGetQueryObjecti64v_args*)argsPtr;
	gl_wrap_context_glGetQueryObjecti64v(ctx, args.id, args.pname, args.params);
}

inline void gl_wrap_handler_glGetQueryObjectui64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryObjectui64v_args args = *(gl_wrap_handler_glGetQueryObjectui64v_args*)argsPtr;
	gl_wrap_context_glGetQueryObjectui64v(ctx, args.id, args.pname, args.params);
}

inline void gl_wrap_handler_glVertexAttribDivisor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribDivisor_args args = *(gl_wrap_handler_glVertexAttribDivisor_args*)argsPtr;
	gl_wrap_context_glVertexAttribDivisor(ctx, args.index, args.divisor);
}

inline void gl_wrap_handler_glVertexAttribP1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP1ui_args args = *(gl_wrap_handler_glVertexAttribP1ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribP1ui(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP1uiv_args args = *(gl_wrap_handler_glVertexAttribP1uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribP1uiv(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP2ui_args args = *(gl_wrap_handler_glVertexAttribP2ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribP2ui(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP2uiv_args args = *(gl_wrap_handler_glVertexAttribP2uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribP2uiv(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP3ui_args args = *(gl_wrap_handler_glVertexAttribP3ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribP3ui(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP3uiv_args args = *(gl_wrap_handler_glVertexAttribP3uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribP3uiv(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP4ui_args args = *(gl_wrap_handler_glVertexAttribP4ui_args*)argsPtr;
	gl_wrap_context_glVertexAttribP4ui(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexAttribP4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribP4uiv_args args = *(gl_wrap_handler_glVertexAttribP4uiv_args*)argsPtr;
	gl_wrap_context_glVertexAttribP4uiv(ctx, args.index, args.type, args.normalized, args.value);
}

inline void gl_wrap_handler_glVertexP2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexP2ui_args args = *(gl_wrap_handler_glVertexP2ui_args*)argsPtr;
	gl_wrap_context_glVertexP2ui(ctx, args.type, args.value);
}

inline void gl_wrap_handler_glVertexP2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexP2uiv_args args = *(gl_wrap_handler_glVertexP2uiv_args*)argsPtr;
	gl_wrap_context_glVertexP2uiv(ctx, args.type, args.value);
}

inline void gl_wrap_handler_glVertexP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexP3ui_args args = *(gl_wrap_handler_glVertexP3ui_args*)argsPtr;
	gl_wrap_context_glVertexP3ui(ctx, args.type, args.value);
}

inline void gl_wrap_handler_glVertexP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexP3uiv_args args = *(gl_wrap_handler_glVertexP3uiv_args*)argsPtr;
	gl_wrap_context_glVertexP3uiv(ctx, args.type, args.value);
}

inline void gl_wrap_handler_glVertexP4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexP4ui_args args = *(gl_wrap_handler_glVertexP4ui_args*)argsPtr;
	gl_wrap_context_glVertexP4ui(ctx, args.type, args.value);
}

inline void gl_wrap_handler_glVertexP4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexP4uiv_args args = *(gl_wrap_handler_glVertexP4uiv_args*)argsPtr;
	gl_wrap_context_glVertexP4uiv(ctx, args.type, args.value);
}

inline void gl_wrap_handler_glTexCoordP1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP1ui_args args = *(gl_wrap_handler_glTexCoordP1ui_args*)argsPtr;
	gl_wrap_context_glTexCoordP1ui(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP1uiv_args args = *(gl_wrap_handler_glTexCoordP1uiv_args*)argsPtr;
	gl_wrap_context_glTexCoordP1uiv(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP2ui_args args = *(gl_wrap_handler_glTexCoordP2ui_args*)argsPtr;
	gl_wrap_context_glTexCoordP2ui(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP2uiv_args args = *(gl_wrap_handler_glTexCoordP2uiv_args*)argsPtr;
	gl_wrap_context_glTexCoordP2uiv(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP3ui_args args = *(gl_wrap_handler_glTexCoordP3ui_args*)argsPtr;
	gl_wrap_context_glTexCoordP3ui(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP3uiv_args args = *(gl_wrap_handler_glTexCoordP3uiv_args*)argsPtr;
	gl_wrap_context_glTexCoordP3uiv(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP4ui_args args = *(gl_wrap_handler_glTexCoordP4ui_args*)argsPtr;
	gl_wrap_context_glTexCoordP4ui(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glTexCoordP4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexCoordP4uiv_args args = *(gl_wrap_handler_glTexCoordP4uiv_args*)argsPtr;
	gl_wrap_context_glTexCoordP4uiv(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP1ui_args args = *(gl_wrap_handler_glMultiTexCoordP1ui_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP1ui(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP1uiv_args args = *(gl_wrap_handler_glMultiTexCoordP1uiv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP1uiv(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP2ui_args args = *(gl_wrap_handler_glMultiTexCoordP2ui_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP2ui(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP2uiv_args args = *(gl_wrap_handler_glMultiTexCoordP2uiv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP2uiv(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP3ui_args args = *(gl_wrap_handler_glMultiTexCoordP3ui_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP3ui(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP3uiv_args args = *(gl_wrap_handler_glMultiTexCoordP3uiv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP3uiv(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP4ui_args args = *(gl_wrap_handler_glMultiTexCoordP4ui_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP4ui(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glMultiTexCoordP4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiTexCoordP4uiv_args args = *(gl_wrap_handler_glMultiTexCoordP4uiv_args*)argsPtr;
	gl_wrap_context_glMultiTexCoordP4uiv(ctx, args.texture, args.type, args.coords);
}

inline void gl_wrap_handler_glNormalP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormalP3ui_args args = *(gl_wrap_handler_glNormalP3ui_args*)argsPtr;
	gl_wrap_context_glNormalP3ui(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glNormalP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glNormalP3uiv_args args = *(gl_wrap_handler_glNormalP3uiv_args*)argsPtr;
	gl_wrap_context_glNormalP3uiv(ctx, args.type, args.coords);
}

inline void gl_wrap_handler_glColorP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorP3ui_args args = *(gl_wrap_handler_glColorP3ui_args*)argsPtr;
	gl_wrap_context_glColorP3ui(ctx, args.type, args.color);
}

inline void gl_wrap_handler_glColorP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorP3uiv_args args = *(gl_wrap_handler_glColorP3uiv_args*)argsPtr;
	gl_wrap_context_glColorP3uiv(ctx, args.type, args.color);
}

inline void gl_wrap_handler_glColorP4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorP4ui_args args = *(gl_wrap_handler_glColorP4ui_args*)argsPtr;
	gl_wrap_context_glColorP4ui(ctx, args.type, args.color);
}

inline void gl_wrap_handler_glColorP4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glColorP4uiv_args args = *(gl_wrap_handler_glColorP4uiv_args*)argsPtr;
	gl_wrap_context_glColorP4uiv(ctx, args.type, args.color);
}

inline void gl_wrap_handler_glSecondaryColorP3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColorP3ui_args args = *(gl_wrap_handler_glSecondaryColorP3ui_args*)argsPtr;
	gl_wrap_context_glSecondaryColorP3ui(ctx, args.type, args.color);
}

inline void gl_wrap_handler_glSecondaryColorP3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glSecondaryColorP3uiv_args args = *(gl_wrap_handler_glSecondaryColorP3uiv_args*)argsPtr;
	gl_wrap_context_glSecondaryColorP3uiv(ctx, args.type, args.color);
}

inline void gl_wrap_handler_glMinSampleShading(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMinSampleShading_args args = *(gl_wrap_handler_glMinSampleShading_args*)argsPtr;
	gl_wrap_context_glMinSampleShading(ctx, args.value);
}

inline void gl_wrap_handler_glBlendEquationi(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendEquationi_args args = *(gl_wrap_handler_glBlendEquationi_args*)argsPtr;
	gl_wrap_context_glBlendEquationi(ctx, args.buf, args.mode);
}

inline void gl_wrap_handler_glBlendEquationSeparatei(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendEquationSeparatei_args args = *(gl_wrap_handler_glBlendEquationSeparatei_args*)argsPtr;
	gl_wrap_context_glBlendEquationSeparatei(ctx, args.buf, args.modeRGB, args.modeAlpha);
}

inline void gl_wrap_handler_glBlendFunci(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendFunci_args args = *(gl_wrap_handler_glBlendFunci_args*)argsPtr;
	gl_wrap_context_glBlendFunci(ctx, args.buf, args.src, args.dst);
}

inline void gl_wrap_handler_glBlendFuncSeparatei(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBlendFuncSeparatei_args args = *(gl_wrap_handler_glBlendFuncSeparatei_args*)argsPtr;
	gl_wrap_context_glBlendFuncSeparatei(ctx, args.buf, args.srcRGB, args.dstRGB, args.srcAlpha, args.dstAlpha);
}

inline void gl_wrap_handler_glDrawArraysIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArraysIndirect_args args = *(gl_wrap_handler_glDrawArraysIndirect_args*)argsPtr;
	gl_wrap_context_glDrawArraysIndirect(ctx, args.mode, args.indirect);
}

inline void gl_wrap_handler_glDrawElementsIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsIndirect_args args = *(gl_wrap_handler_glDrawElementsIndirect_args*)argsPtr;
	gl_wrap_context_glDrawElementsIndirect(ctx, args.mode, args.type, args.indirect);
}

inline void gl_wrap_handler_glUniform1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1d_args args = *(gl_wrap_handler_glUniform1d_args*)argsPtr;
	gl_wrap_context_glUniform1d(ctx, args.location, args.x);
}

inline void gl_wrap_handler_glUniform2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2d_args args = *(gl_wrap_handler_glUniform2d_args*)argsPtr;
	gl_wrap_context_glUniform2d(ctx, args.location, args.x, args.y);
}

inline void gl_wrap_handler_glUniform3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3d_args args = *(gl_wrap_handler_glUniform3d_args*)argsPtr;
	gl_wrap_context_glUniform3d(ctx, args.location, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glUniform4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4d_args args = *(gl_wrap_handler_glUniform4d_args*)argsPtr;
	gl_wrap_context_glUniform4d(ctx, args.location, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glUniform1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform1dv_args args = *(gl_wrap_handler_glUniform1dv_args*)argsPtr;
	gl_wrap_context_glUniform1dv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform2dv_args args = *(gl_wrap_handler_glUniform2dv_args*)argsPtr;
	gl_wrap_context_glUniform2dv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform3dv_args args = *(gl_wrap_handler_glUniform3dv_args*)argsPtr;
	gl_wrap_context_glUniform3dv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniform4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniform4dv_args args = *(gl_wrap_handler_glUniform4dv_args*)argsPtr;
	gl_wrap_context_glUniform4dv(ctx, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2dv_args args = *(gl_wrap_handler_glUniformMatrix2dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3dv_args args = *(gl_wrap_handler_glUniformMatrix3dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4dv_args args = *(gl_wrap_handler_glUniformMatrix4dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2x3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2x3dv_args args = *(gl_wrap_handler_glUniformMatrix2x3dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2x3dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix2x4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix2x4dv_args args = *(gl_wrap_handler_glUniformMatrix2x4dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix2x4dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3x2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3x2dv_args args = *(gl_wrap_handler_glUniformMatrix3x2dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3x2dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix3x4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix3x4dv_args args = *(gl_wrap_handler_glUniformMatrix3x4dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix3x4dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4x2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4x2dv_args args = *(gl_wrap_handler_glUniformMatrix4x2dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4x2dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glUniformMatrix4x3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformMatrix4x3dv_args args = *(gl_wrap_handler_glUniformMatrix4x3dv_args*)argsPtr;
	gl_wrap_context_glUniformMatrix4x3dv(ctx, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glGetUniformdv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformdv_args args = *(gl_wrap_handler_glGetUniformdv_args*)argsPtr;
	gl_wrap_context_glGetUniformdv(ctx, args.program, args.location, args.params);
}

inline void gl_wrap_handler_glGetActiveSubroutineUniformiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveSubroutineUniformiv_args args = *(gl_wrap_handler_glGetActiveSubroutineUniformiv_args*)argsPtr;
	gl_wrap_context_glGetActiveSubroutineUniformiv(ctx, args.program, args.shadertype, args.index, args.pname, args.values);
}

inline void gl_wrap_handler_glGetActiveSubroutineUniformName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveSubroutineUniformName_args args = *(gl_wrap_handler_glGetActiveSubroutineUniformName_args*)argsPtr;
	gl_wrap_context_glGetActiveSubroutineUniformName(ctx, args.program, args.shadertype, args.index, args.bufsize, args.length, args.name);
}

inline void gl_wrap_handler_glGetActiveSubroutineName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveSubroutineName_args args = *(gl_wrap_handler_glGetActiveSubroutineName_args*)argsPtr;
	gl_wrap_context_glGetActiveSubroutineName(ctx, args.program, args.shadertype, args.index, args.bufsize, args.length, args.name);
}

inline void gl_wrap_handler_glUniformSubroutinesuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUniformSubroutinesuiv_args args = *(gl_wrap_handler_glUniformSubroutinesuiv_args*)argsPtr;
	gl_wrap_context_glUniformSubroutinesuiv(ctx, args.shadertype, args.count, args.indices);
}

inline void gl_wrap_handler_glGetUniformSubroutineuiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetUniformSubroutineuiv_args args = *(gl_wrap_handler_glGetUniformSubroutineuiv_args*)argsPtr;
	gl_wrap_context_glGetUniformSubroutineuiv(ctx, args.shadertype, args.location, args.params);
}

inline void gl_wrap_handler_glGetProgramStageiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramStageiv_args args = *(gl_wrap_handler_glGetProgramStageiv_args*)argsPtr;
	gl_wrap_context_glGetProgramStageiv(ctx, args.program, args.shadertype, args.pname, args.values);
}

inline void gl_wrap_handler_glPatchParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPatchParameteri_args args = *(gl_wrap_handler_glPatchParameteri_args*)argsPtr;
	gl_wrap_context_glPatchParameteri(ctx, args.pname, args.value);
}

inline void gl_wrap_handler_glPatchParameterfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPatchParameterfv_args args = *(gl_wrap_handler_glPatchParameterfv_args*)argsPtr;
	gl_wrap_context_glPatchParameterfv(ctx, args.pname, args.values);
}

inline void gl_wrap_handler_glBindTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindTransformFeedback_args args = *(gl_wrap_handler_glBindTransformFeedback_args*)argsPtr;
	gl_wrap_context_glBindTransformFeedback(ctx, args.target, args.id);
}

inline void gl_wrap_handler_glDeleteTransformFeedbacks(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteTransformFeedbacks_args args = *(gl_wrap_handler_glDeleteTransformFeedbacks_args*)argsPtr;
	gl_wrap_context_glDeleteTransformFeedbacks(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glGenTransformFeedbacks(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenTransformFeedbacks_args args = *(gl_wrap_handler_glGenTransformFeedbacks_args*)argsPtr;
	gl_wrap_context_glGenTransformFeedbacks(ctx, args.n, args.ids);
}

inline void gl_wrap_handler_glPauseTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPauseTransformFeedback_args args = *(gl_wrap_handler_glPauseTransformFeedback_args*)argsPtr;
	gl_wrap_context_glPauseTransformFeedback(ctx);
}

inline void gl_wrap_handler_glResumeTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glResumeTransformFeedback_args args = *(gl_wrap_handler_glResumeTransformFeedback_args*)argsPtr;
	gl_wrap_context_glResumeTransformFeedback(ctx);
}

inline void gl_wrap_handler_glDrawTransformFeedback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawTransformFeedback_args args = *(gl_wrap_handler_glDrawTransformFeedback_args*)argsPtr;
	gl_wrap_context_glDrawTransformFeedback(ctx, args.mode, args.id);
}

inline void gl_wrap_handler_glDrawTransformFeedbackStream(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawTransformFeedbackStream_args args = *(gl_wrap_handler_glDrawTransformFeedbackStream_args*)argsPtr;
	gl_wrap_context_glDrawTransformFeedbackStream(ctx, args.mode, args.id, args.stream);
}

inline void gl_wrap_handler_glBeginQueryIndexed(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBeginQueryIndexed_args args = *(gl_wrap_handler_glBeginQueryIndexed_args*)argsPtr;
	gl_wrap_context_glBeginQueryIndexed(ctx, args.target, args.index, args.id);
}

inline void gl_wrap_handler_glEndQueryIndexed(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glEndQueryIndexed_args args = *(gl_wrap_handler_glEndQueryIndexed_args*)argsPtr;
	gl_wrap_context_glEndQueryIndexed(ctx, args.target, args.index);
}

inline void gl_wrap_handler_glGetQueryIndexediv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetQueryIndexediv_args args = *(gl_wrap_handler_glGetQueryIndexediv_args*)argsPtr;
	gl_wrap_context_glGetQueryIndexediv(ctx, args.target, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glReleaseShaderCompiler(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glReleaseShaderCompiler_args args = *(gl_wrap_handler_glReleaseShaderCompiler_args*)argsPtr;
	gl_wrap_context_glReleaseShaderCompiler(ctx);
}

inline void gl_wrap_handler_glShaderBinary(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glShaderBinary_args args = *(gl_wrap_handler_glShaderBinary_args*)argsPtr;
	gl_wrap_context_glShaderBinary(ctx, args.count, args.shaders, args.binaryformat, args.binary, args.length);
}

inline void gl_wrap_handler_glGetShaderPrecisionFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetShaderPrecisionFormat_args args = *(gl_wrap_handler_glGetShaderPrecisionFormat_args*)argsPtr;
	gl_wrap_context_glGetShaderPrecisionFormat(ctx, args.shadertype, args.precisiontype, args.range, args.precision);
}

inline void gl_wrap_handler_glDepthRangef(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthRangef_args args = *(gl_wrap_handler_glDepthRangef_args*)argsPtr;
	gl_wrap_context_glDepthRangef(ctx, args.n, args.f);
}

inline void gl_wrap_handler_glClearDepthf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearDepthf_args args = *(gl_wrap_handler_glClearDepthf_args*)argsPtr;
	gl_wrap_context_glClearDepthf(ctx, args.d);
}

inline void gl_wrap_handler_glGetProgramBinary(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramBinary_args args = *(gl_wrap_handler_glGetProgramBinary_args*)argsPtr;
	gl_wrap_context_glGetProgramBinary(ctx, args.program, args.bufSize, args.length, args.binaryFormat, args.binary);
}

inline void gl_wrap_handler_glProgramBinary(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramBinary_args args = *(gl_wrap_handler_glProgramBinary_args*)argsPtr;
	gl_wrap_context_glProgramBinary(ctx, args.program, args.binaryFormat, args.binary, args.length);
}

inline void gl_wrap_handler_glProgramParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramParameteri_args args = *(gl_wrap_handler_glProgramParameteri_args*)argsPtr;
	gl_wrap_context_glProgramParameteri(ctx, args.program, args.pname, args.value);
}

inline void gl_wrap_handler_glUseProgramStages(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glUseProgramStages_args args = *(gl_wrap_handler_glUseProgramStages_args*)argsPtr;
	gl_wrap_context_glUseProgramStages(ctx, args.pipeline, args.stages, args.program);
}

inline void gl_wrap_handler_glActiveShaderProgram(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glActiveShaderProgram_args args = *(gl_wrap_handler_glActiveShaderProgram_args*)argsPtr;
	gl_wrap_context_glActiveShaderProgram(ctx, args.pipeline, args.program);
}

inline void gl_wrap_handler_glBindProgramPipeline(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindProgramPipeline_args args = *(gl_wrap_handler_glBindProgramPipeline_args*)argsPtr;
	gl_wrap_context_glBindProgramPipeline(ctx, args.pipeline);
}

inline void gl_wrap_handler_glDeleteProgramPipelines(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDeleteProgramPipelines_args args = *(gl_wrap_handler_glDeleteProgramPipelines_args*)argsPtr;
	gl_wrap_context_glDeleteProgramPipelines(ctx, args.n, args.pipelines);
}

inline void gl_wrap_handler_glGenProgramPipelines(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGenProgramPipelines_args args = *(gl_wrap_handler_glGenProgramPipelines_args*)argsPtr;
	gl_wrap_context_glGenProgramPipelines(ctx, args.n, args.pipelines);
}

inline void gl_wrap_handler_glGetProgramPipelineiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramPipelineiv_args args = *(gl_wrap_handler_glGetProgramPipelineiv_args*)argsPtr;
	gl_wrap_context_glGetProgramPipelineiv(ctx, args.pipeline, args.pname, args.params);
}

inline void gl_wrap_handler_glProgramUniform1i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1i_args args = *(gl_wrap_handler_glProgramUniform1i_args*)argsPtr;
	gl_wrap_context_glProgramUniform1i(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform1iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1iv_args args = *(gl_wrap_handler_glProgramUniform1iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform1f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1f_args args = *(gl_wrap_handler_glProgramUniform1f_args*)argsPtr;
	gl_wrap_context_glProgramUniform1f(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform1fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1fv_args args = *(gl_wrap_handler_glProgramUniform1fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1d_args args = *(gl_wrap_handler_glProgramUniform1d_args*)argsPtr;
	gl_wrap_context_glProgramUniform1d(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1dv_args args = *(gl_wrap_handler_glProgramUniform1dv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1dv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform1ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1ui_args args = *(gl_wrap_handler_glProgramUniform1ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform1ui(ctx, args.program, args.location, args.v0);
}

inline void gl_wrap_handler_glProgramUniform1uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform1uiv_args args = *(gl_wrap_handler_glProgramUniform1uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform1uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2i_args args = *(gl_wrap_handler_glProgramUniform2i_args*)argsPtr;
	gl_wrap_context_glProgramUniform2i(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform2iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2iv_args args = *(gl_wrap_handler_glProgramUniform2iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2f_args args = *(gl_wrap_handler_glProgramUniform2f_args*)argsPtr;
	gl_wrap_context_glProgramUniform2f(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2fv_args args = *(gl_wrap_handler_glProgramUniform2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2d_args args = *(gl_wrap_handler_glProgramUniform2d_args*)argsPtr;
	gl_wrap_context_glProgramUniform2d(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2dv_args args = *(gl_wrap_handler_glProgramUniform2dv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2dv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform2ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2ui_args args = *(gl_wrap_handler_glProgramUniform2ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform2ui(ctx, args.program, args.location, args.v0, args.v1);
}

inline void gl_wrap_handler_glProgramUniform2uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform2uiv_args args = *(gl_wrap_handler_glProgramUniform2uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform2uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3i_args args = *(gl_wrap_handler_glProgramUniform3i_args*)argsPtr;
	gl_wrap_context_glProgramUniform3i(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform3iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3iv_args args = *(gl_wrap_handler_glProgramUniform3iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3f_args args = *(gl_wrap_handler_glProgramUniform3f_args*)argsPtr;
	gl_wrap_context_glProgramUniform3f(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3fv_args args = *(gl_wrap_handler_glProgramUniform3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3d_args args = *(gl_wrap_handler_glProgramUniform3d_args*)argsPtr;
	gl_wrap_context_glProgramUniform3d(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3dv_args args = *(gl_wrap_handler_glProgramUniform3dv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3dv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform3ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3ui_args args = *(gl_wrap_handler_glProgramUniform3ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform3ui(ctx, args.program, args.location, args.v0, args.v1, args.v2);
}

inline void gl_wrap_handler_glProgramUniform3uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform3uiv_args args = *(gl_wrap_handler_glProgramUniform3uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform3uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4i(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4i_args args = *(gl_wrap_handler_glProgramUniform4i_args*)argsPtr;
	gl_wrap_context_glProgramUniform4i(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform4iv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4iv_args args = *(gl_wrap_handler_glProgramUniform4iv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4iv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4f(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4f_args args = *(gl_wrap_handler_glProgramUniform4f_args*)argsPtr;
	gl_wrap_context_glProgramUniform4f(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4fv_args args = *(gl_wrap_handler_glProgramUniform4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4fv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4d_args args = *(gl_wrap_handler_glProgramUniform4d_args*)argsPtr;
	gl_wrap_context_glProgramUniform4d(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4dv_args args = *(gl_wrap_handler_glProgramUniform4dv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4dv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniform4ui(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4ui_args args = *(gl_wrap_handler_glProgramUniform4ui_args*)argsPtr;
	gl_wrap_context_glProgramUniform4ui(ctx, args.program, args.location, args.v0, args.v1, args.v2, args.v3);
}

inline void gl_wrap_handler_glProgramUniform4uiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniform4uiv_args args = *(gl_wrap_handler_glProgramUniform4uiv_args*)argsPtr;
	gl_wrap_context_glProgramUniform4uiv(ctx, args.program, args.location, args.count, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2fv_args args = *(gl_wrap_handler_glProgramUniformMatrix2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3fv_args args = *(gl_wrap_handler_glProgramUniformMatrix3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4fv_args args = *(gl_wrap_handler_glProgramUniformMatrix4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2dv_args args = *(gl_wrap_handler_glProgramUniformMatrix2dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3dv_args args = *(gl_wrap_handler_glProgramUniformMatrix3dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4dv_args args = *(gl_wrap_handler_glProgramUniformMatrix4dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2x3fv_args args = *(gl_wrap_handler_glProgramUniformMatrix2x3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2x3fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3x2fv_args args = *(gl_wrap_handler_glProgramUniformMatrix3x2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3x2fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2x4fv_args args = *(gl_wrap_handler_glProgramUniformMatrix2x4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2x4fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4x2fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4x2fv_args args = *(gl_wrap_handler_glProgramUniformMatrix4x2fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4x2fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3x4fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3x4fv_args args = *(gl_wrap_handler_glProgramUniformMatrix3x4fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3x4fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4x3fv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4x3fv_args args = *(gl_wrap_handler_glProgramUniformMatrix4x3fv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4x3fv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2x3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2x3dv_args args = *(gl_wrap_handler_glProgramUniformMatrix2x3dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2x3dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3x2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3x2dv_args args = *(gl_wrap_handler_glProgramUniformMatrix3x2dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3x2dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix2x4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix2x4dv_args args = *(gl_wrap_handler_glProgramUniformMatrix2x4dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix2x4dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4x2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4x2dv_args args = *(gl_wrap_handler_glProgramUniformMatrix4x2dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4x2dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix3x4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix3x4dv_args args = *(gl_wrap_handler_glProgramUniformMatrix3x4dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix3x4dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glProgramUniformMatrix4x3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glProgramUniformMatrix4x3dv_args args = *(gl_wrap_handler_glProgramUniformMatrix4x3dv_args*)argsPtr;
	gl_wrap_context_glProgramUniformMatrix4x3dv(ctx, args.program, args.location, args.count, args.transpose, args.value);
}

inline void gl_wrap_handler_glValidateProgramPipeline(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glValidateProgramPipeline_args args = *(gl_wrap_handler_glValidateProgramPipeline_args*)argsPtr;
	gl_wrap_context_glValidateProgramPipeline(ctx, args.pipeline);
}

inline void gl_wrap_handler_glGetProgramPipelineInfoLog(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramPipelineInfoLog_args args = *(gl_wrap_handler_glGetProgramPipelineInfoLog_args*)argsPtr;
	gl_wrap_context_glGetProgramPipelineInfoLog(ctx, args.pipeline, args.bufSize, args.length, args.infoLog);
}

inline void gl_wrap_handler_glVertexAttribL1d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL1d_args args = *(gl_wrap_handler_glVertexAttribL1d_args*)argsPtr;
	gl_wrap_context_glVertexAttribL1d(ctx, args.index, args.x);
}

inline void gl_wrap_handler_glVertexAttribL2d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL2d_args args = *(gl_wrap_handler_glVertexAttribL2d_args*)argsPtr;
	gl_wrap_context_glVertexAttribL2d(ctx, args.index, args.x, args.y);
}

inline void gl_wrap_handler_glVertexAttribL3d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL3d_args args = *(gl_wrap_handler_glVertexAttribL3d_args*)argsPtr;
	gl_wrap_context_glVertexAttribL3d(ctx, args.index, args.x, args.y, args.z);
}

inline void gl_wrap_handler_glVertexAttribL4d(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL4d_args args = *(gl_wrap_handler_glVertexAttribL4d_args*)argsPtr;
	gl_wrap_context_glVertexAttribL4d(ctx, args.index, args.x, args.y, args.z, args.w);
}

inline void gl_wrap_handler_glVertexAttribL1dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL1dv_args args = *(gl_wrap_handler_glVertexAttribL1dv_args*)argsPtr;
	gl_wrap_context_glVertexAttribL1dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribL2dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL2dv_args args = *(gl_wrap_handler_glVertexAttribL2dv_args*)argsPtr;
	gl_wrap_context_glVertexAttribL2dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribL3dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL3dv_args args = *(gl_wrap_handler_glVertexAttribL3dv_args*)argsPtr;
	gl_wrap_context_glVertexAttribL3dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribL4dv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribL4dv_args args = *(gl_wrap_handler_glVertexAttribL4dv_args*)argsPtr;
	gl_wrap_context_glVertexAttribL4dv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glVertexAttribLPointer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribLPointer_args args = *(gl_wrap_handler_glVertexAttribLPointer_args*)argsPtr;
	gl_wrap_context_glVertexAttribLPointer(ctx, args.index, args.size, args.type, args.stride, args.pointer);
}

inline void gl_wrap_handler_glGetVertexAttribLdv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetVertexAttribLdv_args args = *(gl_wrap_handler_glGetVertexAttribLdv_args*)argsPtr;
	gl_wrap_context_glGetVertexAttribLdv(ctx, args.index, args.pname, args.params);
}

inline void gl_wrap_handler_glViewportArrayv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glViewportArrayv_args args = *(gl_wrap_handler_glViewportArrayv_args*)argsPtr;
	gl_wrap_context_glViewportArrayv(ctx, args.first, args.count, args.v);
}

inline void gl_wrap_handler_glViewportIndexedf(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glViewportIndexedf_args args = *(gl_wrap_handler_glViewportIndexedf_args*)argsPtr;
	gl_wrap_context_glViewportIndexedf(ctx, args.index, args.x, args.y, args.w, args.h);
}

inline void gl_wrap_handler_glViewportIndexedfv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glViewportIndexedfv_args args = *(gl_wrap_handler_glViewportIndexedfv_args*)argsPtr;
	gl_wrap_context_glViewportIndexedfv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glScissorArrayv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScissorArrayv_args args = *(gl_wrap_handler_glScissorArrayv_args*)argsPtr;
	gl_wrap_context_glScissorArrayv(ctx, args.first, args.count, args.v);
}

inline void gl_wrap_handler_glScissorIndexed(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScissorIndexed_args args = *(gl_wrap_handler_glScissorIndexed_args*)argsPtr;
	gl_wrap_context_glScissorIndexed(ctx, args.index, args.left, args.bottom, args.width, args.height);
}

inline void gl_wrap_handler_glScissorIndexedv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glScissorIndexedv_args args = *(gl_wrap_handler_glScissorIndexedv_args*)argsPtr;
	gl_wrap_context_glScissorIndexedv(ctx, args.index, args.v);
}

inline void gl_wrap_handler_glDepthRangeArrayv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthRangeArrayv_args args = *(gl_wrap_handler_glDepthRangeArrayv_args*)argsPtr;
	gl_wrap_context_glDepthRangeArrayv(ctx, args.first, args.count, args.v);
}

inline void gl_wrap_handler_glDepthRangeIndexed(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDepthRangeIndexed_args args = *(gl_wrap_handler_glDepthRangeIndexed_args*)argsPtr;
	gl_wrap_context_glDepthRangeIndexed(ctx, args.index, args.n, args.f);
}

inline void gl_wrap_handler_glGetFloati_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFloati_v_args args = *(gl_wrap_handler_glGetFloati_v_args*)argsPtr;
	gl_wrap_context_glGetFloati_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glGetDoublei_v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetDoublei_v_args args = *(gl_wrap_handler_glGetDoublei_v_args*)argsPtr;
	gl_wrap_context_glGetDoublei_v(ctx, args.target, args.index, args.data);
}

inline void gl_wrap_handler_glDrawArraysInstancedBaseInstance(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawArraysInstancedBaseInstance_args args = *(gl_wrap_handler_glDrawArraysInstancedBaseInstance_args*)argsPtr;
	gl_wrap_context_glDrawArraysInstancedBaseInstance(ctx, args.mode, args.first, args.count, args.instancecount, args.baseinstance);
}

inline void gl_wrap_handler_glDrawElementsInstancedBaseInstance(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsInstancedBaseInstance_args args = *(gl_wrap_handler_glDrawElementsInstancedBaseInstance_args*)argsPtr;
	gl_wrap_context_glDrawElementsInstancedBaseInstance(ctx, args.mode, args.count, args.type, args.indices, args.instancecount, args.baseinstance);
}

inline void gl_wrap_handler_glDrawElementsInstancedBaseVertexBaseInstance(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawElementsInstancedBaseVertexBaseInstance_args args = *(gl_wrap_handler_glDrawElementsInstancedBaseVertexBaseInstance_args*)argsPtr;
	gl_wrap_context_glDrawElementsInstancedBaseVertexBaseInstance(ctx, args.mode, args.count, args.type, args.indices, args.instancecount, args.basevertex, args.baseinstance);
}

inline void gl_wrap_handler_glGetInternalformativ(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInternalformativ_args args = *(gl_wrap_handler_glGetInternalformativ_args*)argsPtr;
	gl_wrap_context_glGetInternalformativ(ctx, args.target, args.internalformat, args.pname, args.bufSize, args.params);
}

inline void gl_wrap_handler_glGetActiveAtomicCounterBufferiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetActiveAtomicCounterBufferiv_args args = *(gl_wrap_handler_glGetActiveAtomicCounterBufferiv_args*)argsPtr;
	gl_wrap_context_glGetActiveAtomicCounterBufferiv(ctx, args.program, args.bufferIndex, args.pname, args.params);
}

inline void gl_wrap_handler_glBindImageTexture(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindImageTexture_args args = *(gl_wrap_handler_glBindImageTexture_args*)argsPtr;
	gl_wrap_context_glBindImageTexture(ctx, args.unit, args.texture, args.level, args.layered, args.layer, args.access, args.format);
}

inline void gl_wrap_handler_glMemoryBarrier(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMemoryBarrier_args args = *(gl_wrap_handler_glMemoryBarrier_args*)argsPtr;
	gl_wrap_context_glMemoryBarrier(ctx, args.barriers);
}

inline void gl_wrap_handler_glTexStorage1D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage1D_args args = *(gl_wrap_handler_glTexStorage1D_args*)argsPtr;
	gl_wrap_context_glTexStorage1D(ctx, args.target, args.levels, args.internalformat, args.width);
}

inline void gl_wrap_handler_glTexStorage2D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage2D_args args = *(gl_wrap_handler_glTexStorage2D_args*)argsPtr;
	gl_wrap_context_glTexStorage2D(ctx, args.target, args.levels, args.internalformat, args.width, args.height);
}

inline void gl_wrap_handler_glTexStorage3D(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage3D_args args = *(gl_wrap_handler_glTexStorage3D_args*)argsPtr;
	gl_wrap_context_glTexStorage3D(ctx, args.target, args.levels, args.internalformat, args.width, args.height, args.depth);
}

inline void gl_wrap_handler_glDrawTransformFeedbackInstanced(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawTransformFeedbackInstanced_args args = *(gl_wrap_handler_glDrawTransformFeedbackInstanced_args*)argsPtr;
	gl_wrap_context_glDrawTransformFeedbackInstanced(ctx, args.mode, args.id, args.instancecount);
}

inline void gl_wrap_handler_glDrawTransformFeedbackStreamInstanced(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDrawTransformFeedbackStreamInstanced_args args = *(gl_wrap_handler_glDrawTransformFeedbackStreamInstanced_args*)argsPtr;
	gl_wrap_context_glDrawTransformFeedbackStreamInstanced(ctx, args.mode, args.id, args.stream, args.instancecount);
}

inline void gl_wrap_handler_glClearBufferData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferData_args args = *(gl_wrap_handler_glClearBufferData_args*)argsPtr;
	gl_wrap_context_glClearBufferData(ctx, args.target, args.internalformat, args.format, args.type, args.data);
}

inline void gl_wrap_handler_glClearBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearBufferSubData_args args = *(gl_wrap_handler_glClearBufferSubData_args*)argsPtr;
	gl_wrap_context_glClearBufferSubData(ctx, args.target, args.internalformat, args.offset, args.size, args.format, args.type, args.data);
}

inline void gl_wrap_handler_glDispatchCompute(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDispatchCompute_args args = *(gl_wrap_handler_glDispatchCompute_args*)argsPtr;
	gl_wrap_context_glDispatchCompute(ctx, args.num_groups_x, args.num_groups_y, args.num_groups_z);
}

inline void gl_wrap_handler_glDispatchComputeIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDispatchComputeIndirect_args args = *(gl_wrap_handler_glDispatchComputeIndirect_args*)argsPtr;
	gl_wrap_context_glDispatchComputeIndirect(ctx, args.indirect);
}

inline void gl_wrap_handler_glCopyImageSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glCopyImageSubData_args args = *(gl_wrap_handler_glCopyImageSubData_args*)argsPtr;
	gl_wrap_context_glCopyImageSubData(ctx, args.srcName, args.srcTarget, args.srcLevel, args.srcX, args.srcY, args.srcZ, args.dstName, args.dstTarget, args.dstLevel, args.dstX, args.dstY, args.dstZ, args.srcWidth, args.srcHeight, args.srcDepth);
}

inline void gl_wrap_handler_glFramebufferParameteri(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glFramebufferParameteri_args args = *(gl_wrap_handler_glFramebufferParameteri_args*)argsPtr;
	gl_wrap_context_glFramebufferParameteri(ctx, args.target, args.pname, args.param);
}

inline void gl_wrap_handler_glGetFramebufferParameteriv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetFramebufferParameteriv_args args = *(gl_wrap_handler_glGetFramebufferParameteriv_args*)argsPtr;
	gl_wrap_context_glGetFramebufferParameteriv(ctx, args.target, args.pname, args.params);
}

inline void gl_wrap_handler_glGetInternalformati64v(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetInternalformati64v_args args = *(gl_wrap_handler_glGetInternalformati64v_args*)argsPtr;
	gl_wrap_context_glGetInternalformati64v(ctx, args.target, args.internalformat, args.pname, args.bufSize, args.params);
}

inline void gl_wrap_handler_glInvalidateTexSubImage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateTexSubImage_args args = *(gl_wrap_handler_glInvalidateTexSubImage_args*)argsPtr;
	gl_wrap_context_glInvalidateTexSubImage(ctx, args.texture, args.level, args.xoffset, args.yoffset, args.zoffset, args.width, args.height, args.depth);
}

inline void gl_wrap_handler_glInvalidateTexImage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateTexImage_args args = *(gl_wrap_handler_glInvalidateTexImage_args*)argsPtr;
	gl_wrap_context_glInvalidateTexImage(ctx, args.texture, args.level);
}

inline void gl_wrap_handler_glInvalidateBufferSubData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateBufferSubData_args args = *(gl_wrap_handler_glInvalidateBufferSubData_args*)argsPtr;
	gl_wrap_context_glInvalidateBufferSubData(ctx, args.buffer, args.offset, args.length);
}

inline void gl_wrap_handler_glInvalidateBufferData(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateBufferData_args args = *(gl_wrap_handler_glInvalidateBufferData_args*)argsPtr;
	gl_wrap_context_glInvalidateBufferData(ctx, args.buffer);
}

inline void gl_wrap_handler_glInvalidateFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateFramebuffer_args args = *(gl_wrap_handler_glInvalidateFramebuffer_args*)argsPtr;
	gl_wrap_context_glInvalidateFramebuffer(ctx, args.target, args.numAttachments, args.attachments);
}

inline void gl_wrap_handler_glInvalidateSubFramebuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glInvalidateSubFramebuffer_args args = *(gl_wrap_handler_glInvalidateSubFramebuffer_args*)argsPtr;
	gl_wrap_context_glInvalidateSubFramebuffer(ctx, args.target, args.numAttachments, args.attachments, args.x, args.y, args.width, args.height);
}

inline void gl_wrap_handler_glMultiDrawArraysIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiDrawArraysIndirect_args args = *(gl_wrap_handler_glMultiDrawArraysIndirect_args*)argsPtr;
	gl_wrap_context_glMultiDrawArraysIndirect(ctx, args.mode, args.indirect, args.drawcount, args.stride);
}

inline void gl_wrap_handler_glMultiDrawElementsIndirect(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glMultiDrawElementsIndirect_args args = *(gl_wrap_handler_glMultiDrawElementsIndirect_args*)argsPtr;
	gl_wrap_context_glMultiDrawElementsIndirect(ctx, args.mode, args.type, args.indirect, args.drawcount, args.stride);
}

inline void gl_wrap_handler_glGetProgramInterfaceiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramInterfaceiv_args args = *(gl_wrap_handler_glGetProgramInterfaceiv_args*)argsPtr;
	gl_wrap_context_glGetProgramInterfaceiv(ctx, args.program, args.programInterface, args.pname, args.params);
}

inline void gl_wrap_handler_glGetProgramResourceName(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramResourceName_args args = *(gl_wrap_handler_glGetProgramResourceName_args*)argsPtr;
	gl_wrap_context_glGetProgramResourceName(ctx, args.program, args.programInterface, args.index, args.bufSize, args.length, args.name);
}

inline void gl_wrap_handler_glGetProgramResourceiv(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetProgramResourceiv_args args = *(gl_wrap_handler_glGetProgramResourceiv_args*)argsPtr;
	gl_wrap_context_glGetProgramResourceiv(ctx, args.program, args.programInterface, args.index, args.propCount, args.props, args.bufSize, args.length, args.params);
}

inline void gl_wrap_handler_glShaderStorageBlockBinding(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glShaderStorageBlockBinding_args args = *(gl_wrap_handler_glShaderStorageBlockBinding_args*)argsPtr;
	gl_wrap_context_glShaderStorageBlockBinding(ctx, args.program, args.storageBlockIndex, args.storageBlockBinding);
}

inline void gl_wrap_handler_glTexBufferRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexBufferRange_args args = *(gl_wrap_handler_glTexBufferRange_args*)argsPtr;
	gl_wrap_context_glTexBufferRange(ctx, args.target, args.internalformat, args.buffer, args.offset, args.size);
}

inline void gl_wrap_handler_glTexStorage2DMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage2DMultisample_args args = *(gl_wrap_handler_glTexStorage2DMultisample_args*)argsPtr;
	gl_wrap_context_glTexStorage2DMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height, args.fixedsamplelocations);
}

inline void gl_wrap_handler_glTexStorage3DMultisample(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTexStorage3DMultisample_args args = *(gl_wrap_handler_glTexStorage3DMultisample_args*)argsPtr;
	gl_wrap_context_glTexStorage3DMultisample(ctx, args.target, args.samples, args.internalformat, args.width, args.height, args.depth, args.fixedsamplelocations);
}

inline void gl_wrap_handler_glTextureView(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glTextureView_args args = *(gl_wrap_handler_glTextureView_args*)argsPtr;
	gl_wrap_context_glTextureView(ctx, args.texture, args.target, args.origtexture, args.internalformat, args.minlevel, args.numlevels, args.minlayer, args.numlayers);
}

inline void gl_wrap_handler_glBindVertexBuffer(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindVertexBuffer_args args = *(gl_wrap_handler_glBindVertexBuffer_args*)argsPtr;
	gl_wrap_context_glBindVertexBuffer(ctx, args.bindingindex, args.buffer, args.offset, args.stride);
}

inline void gl_wrap_handler_glVertexAttribFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribFormat_args args = *(gl_wrap_handler_glVertexAttribFormat_args*)argsPtr;
	gl_wrap_context_glVertexAttribFormat(ctx, args.attribindex, args.size, args.type, args.normalized, args.relativeoffset);
}

inline void gl_wrap_handler_glVertexAttribIFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribIFormat_args args = *(gl_wrap_handler_glVertexAttribIFormat_args*)argsPtr;
	gl_wrap_context_glVertexAttribIFormat(ctx, args.attribindex, args.size, args.type, args.relativeoffset);
}

inline void gl_wrap_handler_glVertexAttribLFormat(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribLFormat_args args = *(gl_wrap_handler_glVertexAttribLFormat_args*)argsPtr;
	gl_wrap_context_glVertexAttribLFormat(ctx, args.attribindex, args.size, args.type, args.relativeoffset);
}

inline void gl_wrap_handler_glVertexAttribBinding(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexAttribBinding_args args = *(gl_wrap_handler_glVertexAttribBinding_args*)argsPtr;
	gl_wrap_context_glVertexAttribBinding(ctx, args.attribindex, args.bindingindex);
}

inline void gl_wrap_handler_glVertexBindingDivisor(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glVertexBindingDivisor_args args = *(gl_wrap_handler_glVertexBindingDivisor_args*)argsPtr;
	gl_wrap_context_glVertexBindingDivisor(ctx, args.bindingindex, args.divisor);
}

inline void gl_wrap_handler_glDebugMessageControl(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDebugMessageControl_args args = *(gl_wrap_handler_glDebugMessageControl_args*)argsPtr;
	gl_wrap_context_glDebugMessageControl(ctx, args.source, args.type, args.severity, args.count, args.ids, args.enabled);
}

inline void gl_wrap_handler_glDebugMessageInsert(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDebugMessageInsert_args args = *(gl_wrap_handler_glDebugMessageInsert_args*)argsPtr;
	gl_wrap_context_glDebugMessageInsert(ctx, args.source, args.type, args.id, args.severity, args.length, args.buf);
}

inline void gl_wrap_handler_glDebugMessageCallback(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glDebugMessageCallback_args args = *(gl_wrap_handler_glDebugMessageCallback_args*)argsPtr;
	gl_wrap_context_glDebugMessageCallback(ctx, args.callback, args.userParam);
}

inline void gl_wrap_handler_glPushDebugGroup(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPushDebugGroup_args args = *(gl_wrap_handler_glPushDebugGroup_args*)argsPtr;
	gl_wrap_context_glPushDebugGroup(ctx, args.source, args.id, args.length, args.message);
}

inline void gl_wrap_handler_glPopDebugGroup(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glPopDebugGroup_args args = *(gl_wrap_handler_glPopDebugGroup_args*)argsPtr;
	gl_wrap_context_glPopDebugGroup(ctx);
}

inline void gl_wrap_handler_glObjectLabel(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glObjectLabel_args args = *(gl_wrap_handler_glObjectLabel_args*)argsPtr;
	gl_wrap_context_glObjectLabel(ctx, args.identifier, args.name, args.length, args.label);
}

inline void gl_wrap_handler_glGetObjectLabel(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetObjectLabel_args args = *(gl_wrap_handler_glGetObjectLabel_args*)argsPtr;
	gl_wrap_context_glGetObjectLabel(ctx, args.identifier, args.name, args.bufSize, args.length, args.label);
}

inline void gl_wrap_handler_glObjectPtrLabel(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glObjectPtrLabel_args args = *(gl_wrap_handler_glObjectPtrLabel_args*)argsPtr;
	gl_wrap_context_glObjectPtrLabel(ctx, args.ptr, args.length, args.label);
}

inline void gl_wrap_handler_glGetObjectPtrLabel(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glGetObjectPtrLabel_args args = *(gl_wrap_handler_glGetObjectPtrLabel_args*)argsPtr;
	gl_wrap_context_glGetObjectPtrLabel(ctx, args.ptr, args.bufSize, args.length, args.label);
}

inline void gl_wrap_handler_glBufferStorage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBufferStorage_args args = *(gl_wrap_handler_glBufferStorage_args*)argsPtr;
	gl_wrap_context_glBufferStorage(ctx, args.target, args.size, args.data, args.flags);
}

inline void gl_wrap_handler_glClearTexImage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearTexImage_args args = *(gl_wrap_handler_glClearTexImage_args*)argsPtr;
	gl_wrap_context_glClearTexImage(ctx, args.texture, args.level, args.format, args.type, args.data);
}

inline void gl_wrap_handler_glClearTexSubImage(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glClearTexSubImage_args args = *(gl_wrap_handler_glClearTexSubImage_args*)argsPtr;
	gl_wrap_context_glClearTexSubImage(ctx, args.texture, args.level, args.xoffset, args.yoffset, args.zoffset, args.width, args.height, args.depth, args.format, args.type, args.data);
}

inline void gl_wrap_handler_glBindBuffersBase(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBuffersBase_args args = *(gl_wrap_handler_glBindBuffersBase_args*)argsPtr;
	gl_wrap_context_glBindBuffersBase(ctx, args.target, args.first, args.count, args.buffers);
}

inline void gl_wrap_handler_glBindBuffersRange(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindBuffersRange_args args = *(gl_wrap_handler_glBindBuffersRange_args*)argsPtr;
	gl_wrap_context_glBindBuffersRange(ctx, args.target, args.first, args.count, args.buffers, args.offsets, args.sizes);
}

inline void gl_wrap_handler_glBindTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindTextures_args args = *(gl_wrap_handler_glBindTextures_args*)argsPtr;
	gl_wrap_context_glBindTextures(ctx, args.first, args.count, args.textures);
}

inline void gl_wrap_handler_glBindSamplers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindSamplers_args args = *(gl_wrap_handler_glBindSamplers_args*)argsPtr;
	gl_wrap_context_glBindSamplers(ctx, args.first, args.count, args.samplers);
}

inline void gl_wrap_handler_glBindImageTextures(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindImageTextures_args args = *(gl_wrap_handler_glBindImageTextures_args*)argsPtr;
	gl_wrap_context_glBindImageTextures(ctx, args.first, args.count, args.textures);
}

inline void gl_wrap_handler_glBindVertexBuffers(gl_wrap_context* ctx, void* argsPtr) {
	gl_wrap_handler_glBindVertexBuffers_args args = *(gl_wrap_handler_glBindVertexBuffers_args*)argsPtr;
	gl_wrap_context_glBindVertexBuffers(ctx, args.first, args.count, args.buffers, args.offsets, args.strides);
}

// This is the jump table used for executing each batched OpenGL function
// without doing a large (approx. 1k cases) and costly switch statement.
gl_wrap_jump_handler gl_wrap_jump_table[] = {
	gl_wrap_handler_glCullFace,
	gl_wrap_handler_glFrontFace,
	gl_wrap_handler_glHint,
	gl_wrap_handler_glLineWidth,
	gl_wrap_handler_glPointSize,
	gl_wrap_handler_glPolygonMode,
	gl_wrap_handler_glScissor,
	gl_wrap_handler_glTexParameterf,
	gl_wrap_handler_glTexParameterfv,
	gl_wrap_handler_glTexParameteri,
	gl_wrap_handler_glTexParameteriv,
	gl_wrap_handler_glTexImage1D,
	gl_wrap_handler_glTexImage2D,
	gl_wrap_handler_glDrawBuffer,
	gl_wrap_handler_glClear,
	gl_wrap_handler_glClearColor,
	gl_wrap_handler_glClearStencil,
	gl_wrap_handler_glClearDepth,
	gl_wrap_handler_glStencilMask,
	gl_wrap_handler_glColorMask,
	gl_wrap_handler_glDepthMask,
	gl_wrap_handler_glDisable,
	gl_wrap_handler_glEnable,
	gl_wrap_handler_glFinish,
	gl_wrap_handler_glFlush,
	gl_wrap_handler_glBlendFunc,
	gl_wrap_handler_glLogicOp,
	gl_wrap_handler_glStencilFunc,
	gl_wrap_handler_glStencilOp,
	gl_wrap_handler_glDepthFunc,
	gl_wrap_handler_glPixelStoref,
	gl_wrap_handler_glPixelStorei,
	gl_wrap_handler_glReadBuffer,
	gl_wrap_handler_glReadPixels,
	gl_wrap_handler_glGetBooleanv,
	gl_wrap_handler_glGetDoublev,
	gl_wrap_handler_glGetFloatv,
	gl_wrap_handler_glGetIntegerv,
	gl_wrap_handler_glGetTexImage,
	gl_wrap_handler_glGetTexParameterfv,
	gl_wrap_handler_glGetTexParameteriv,
	gl_wrap_handler_glGetTexLevelParameterfv,
	gl_wrap_handler_glGetTexLevelParameteriv,
	gl_wrap_handler_glDepthRange,
	gl_wrap_handler_glViewport,
	gl_wrap_handler_glNewList,
	gl_wrap_handler_glEndList,
	gl_wrap_handler_glCallList,
	gl_wrap_handler_glCallLists,
	gl_wrap_handler_glDeleteLists,
	gl_wrap_handler_glListBase,
	gl_wrap_handler_glBegin,
	gl_wrap_handler_glBitmap,
	gl_wrap_handler_glColor3b,
	gl_wrap_handler_glColor3bv,
	gl_wrap_handler_glColor3d,
	gl_wrap_handler_glColor3dv,
	gl_wrap_handler_glColor3f,
	gl_wrap_handler_glColor3fv,
	gl_wrap_handler_glColor3i,
	gl_wrap_handler_glColor3iv,
	gl_wrap_handler_glColor3s,
	gl_wrap_handler_glColor3sv,
	gl_wrap_handler_glColor3ub,
	gl_wrap_handler_glColor3ubv,
	gl_wrap_handler_glColor3ui,
	gl_wrap_handler_glColor3uiv,
	gl_wrap_handler_glColor3us,
	gl_wrap_handler_glColor3usv,
	gl_wrap_handler_glColor4b,
	gl_wrap_handler_glColor4bv,
	gl_wrap_handler_glColor4d,
	gl_wrap_handler_glColor4dv,
	gl_wrap_handler_glColor4f,
	gl_wrap_handler_glColor4fv,
	gl_wrap_handler_glColor4i,
	gl_wrap_handler_glColor4iv,
	gl_wrap_handler_glColor4s,
	gl_wrap_handler_glColor4sv,
	gl_wrap_handler_glColor4ub,
	gl_wrap_handler_glColor4ubv,
	gl_wrap_handler_glColor4ui,
	gl_wrap_handler_glColor4uiv,
	gl_wrap_handler_glColor4us,
	gl_wrap_handler_glColor4usv,
	gl_wrap_handler_glEdgeFlag,
	gl_wrap_handler_glEdgeFlagv,
	gl_wrap_handler_glEnd,
	gl_wrap_handler_glIndexd,
	gl_wrap_handler_glIndexdv,
	gl_wrap_handler_glIndexf,
	gl_wrap_handler_glIndexfv,
	gl_wrap_handler_glIndexi,
	gl_wrap_handler_glIndexiv,
	gl_wrap_handler_glIndexs,
	gl_wrap_handler_glIndexsv,
	gl_wrap_handler_glNormal3b,
	gl_wrap_handler_glNormal3bv,
	gl_wrap_handler_glNormal3d,
	gl_wrap_handler_glNormal3dv,
	gl_wrap_handler_glNormal3f,
	gl_wrap_handler_glNormal3fv,
	gl_wrap_handler_glNormal3i,
	gl_wrap_handler_glNormal3iv,
	gl_wrap_handler_glNormal3s,
	gl_wrap_handler_glNormal3sv,
	gl_wrap_handler_glRasterPos2d,
	gl_wrap_handler_glRasterPos2dv,
	gl_wrap_handler_glRasterPos2f,
	gl_wrap_handler_glRasterPos2fv,
	gl_wrap_handler_glRasterPos2i,
	gl_wrap_handler_glRasterPos2iv,
	gl_wrap_handler_glRasterPos2s,
	gl_wrap_handler_glRasterPos2sv,
	gl_wrap_handler_glRasterPos3d,
	gl_wrap_handler_glRasterPos3dv,
	gl_wrap_handler_glRasterPos3f,
	gl_wrap_handler_glRasterPos3fv,
	gl_wrap_handler_glRasterPos3i,
	gl_wrap_handler_glRasterPos3iv,
	gl_wrap_handler_glRasterPos3s,
	gl_wrap_handler_glRasterPos3sv,
	gl_wrap_handler_glRasterPos4d,
	gl_wrap_handler_glRasterPos4dv,
	gl_wrap_handler_glRasterPos4f,
	gl_wrap_handler_glRasterPos4fv,
	gl_wrap_handler_glRasterPos4i,
	gl_wrap_handler_glRasterPos4iv,
	gl_wrap_handler_glRasterPos4s,
	gl_wrap_handler_glRasterPos4sv,
	gl_wrap_handler_glRectd,
	gl_wrap_handler_glRectdv,
	gl_wrap_handler_glRectf,
	gl_wrap_handler_glRectfv,
	gl_wrap_handler_glRecti,
	gl_wrap_handler_glRectiv,
	gl_wrap_handler_glRects,
	gl_wrap_handler_glRectsv,
	gl_wrap_handler_glTexCoord1d,
	gl_wrap_handler_glTexCoord1dv,
	gl_wrap_handler_glTexCoord1f,
	gl_wrap_handler_glTexCoord1fv,
	gl_wrap_handler_glTexCoord1i,
	gl_wrap_handler_glTexCoord1iv,
	gl_wrap_handler_glTexCoord1s,
	gl_wrap_handler_glTexCoord1sv,
	gl_wrap_handler_glTexCoord2d,
	gl_wrap_handler_glTexCoord2dv,
	gl_wrap_handler_glTexCoord2f,
	gl_wrap_handler_glTexCoord2fv,
	gl_wrap_handler_glTexCoord2i,
	gl_wrap_handler_glTexCoord2iv,
	gl_wrap_handler_glTexCoord2s,
	gl_wrap_handler_glTexCoord2sv,
	gl_wrap_handler_glTexCoord3d,
	gl_wrap_handler_glTexCoord3dv,
	gl_wrap_handler_glTexCoord3f,
	gl_wrap_handler_glTexCoord3fv,
	gl_wrap_handler_glTexCoord3i,
	gl_wrap_handler_glTexCoord3iv,
	gl_wrap_handler_glTexCoord3s,
	gl_wrap_handler_glTexCoord3sv,
	gl_wrap_handler_glTexCoord4d,
	gl_wrap_handler_glTexCoord4dv,
	gl_wrap_handler_glTexCoord4f,
	gl_wrap_handler_glTexCoord4fv,
	gl_wrap_handler_glTexCoord4i,
	gl_wrap_handler_glTexCoord4iv,
	gl_wrap_handler_glTexCoord4s,
	gl_wrap_handler_glTexCoord4sv,
	gl_wrap_handler_glVertex2d,
	gl_wrap_handler_glVertex2dv,
	gl_wrap_handler_glVertex2f,
	gl_wrap_handler_glVertex2fv,
	gl_wrap_handler_glVertex2i,
	gl_wrap_handler_glVertex2iv,
	gl_wrap_handler_glVertex2s,
	gl_wrap_handler_glVertex2sv,
	gl_wrap_handler_glVertex3d,
	gl_wrap_handler_glVertex3dv,
	gl_wrap_handler_glVertex3f,
	gl_wrap_handler_glVertex3fv,
	gl_wrap_handler_glVertex3i,
	gl_wrap_handler_glVertex3iv,
	gl_wrap_handler_glVertex3s,
	gl_wrap_handler_glVertex3sv,
	gl_wrap_handler_glVertex4d,
	gl_wrap_handler_glVertex4dv,
	gl_wrap_handler_glVertex4f,
	gl_wrap_handler_glVertex4fv,
	gl_wrap_handler_glVertex4i,
	gl_wrap_handler_glVertex4iv,
	gl_wrap_handler_glVertex4s,
	gl_wrap_handler_glVertex4sv,
	gl_wrap_handler_glClipPlane,
	gl_wrap_handler_glColorMaterial,
	gl_wrap_handler_glFogf,
	gl_wrap_handler_glFogfv,
	gl_wrap_handler_glFogi,
	gl_wrap_handler_glFogiv,
	gl_wrap_handler_glLightf,
	gl_wrap_handler_glLightfv,
	gl_wrap_handler_glLighti,
	gl_wrap_handler_glLightiv,
	gl_wrap_handler_glLightModelf,
	gl_wrap_handler_glLightModelfv,
	gl_wrap_handler_glLightModeli,
	gl_wrap_handler_glLightModeliv,
	gl_wrap_handler_glLineStipple,
	gl_wrap_handler_glMaterialf,
	gl_wrap_handler_glMaterialfv,
	gl_wrap_handler_glMateriali,
	gl_wrap_handler_glMaterialiv,
	gl_wrap_handler_glPolygonStipple,
	gl_wrap_handler_glShadeModel,
	gl_wrap_handler_glTexEnvf,
	gl_wrap_handler_glTexEnvfv,
	gl_wrap_handler_glTexEnvi,
	gl_wrap_handler_glTexEnviv,
	gl_wrap_handler_glTexGend,
	gl_wrap_handler_glTexGendv,
	gl_wrap_handler_glTexGenf,
	gl_wrap_handler_glTexGenfv,
	gl_wrap_handler_glTexGeni,
	gl_wrap_handler_glTexGeniv,
	gl_wrap_handler_glFeedbackBuffer,
	gl_wrap_handler_glSelectBuffer,
	gl_wrap_handler_glInitNames,
	gl_wrap_handler_glLoadName,
	gl_wrap_handler_glPassThrough,
	gl_wrap_handler_glPopName,
	gl_wrap_handler_glPushName,
	gl_wrap_handler_glClearAccum,
	gl_wrap_handler_glClearIndex,
	gl_wrap_handler_glIndexMask,
	gl_wrap_handler_glAccum,
	gl_wrap_handler_glPopAttrib,
	gl_wrap_handler_glPushAttrib,
	gl_wrap_handler_glMap1d,
	gl_wrap_handler_glMap1f,
	gl_wrap_handler_glMap2d,
	gl_wrap_handler_glMap2f,
	gl_wrap_handler_glMapGrid1d,
	gl_wrap_handler_glMapGrid1f,
	gl_wrap_handler_glMapGrid2d,
	gl_wrap_handler_glMapGrid2f,
	gl_wrap_handler_glEvalCoord1d,
	gl_wrap_handler_glEvalCoord1dv,
	gl_wrap_handler_glEvalCoord1f,
	gl_wrap_handler_glEvalCoord1fv,
	gl_wrap_handler_glEvalCoord2d,
	gl_wrap_handler_glEvalCoord2dv,
	gl_wrap_handler_glEvalCoord2f,
	gl_wrap_handler_glEvalCoord2fv,
	gl_wrap_handler_glEvalMesh1,
	gl_wrap_handler_glEvalPoint1,
	gl_wrap_handler_glEvalMesh2,
	gl_wrap_handler_glEvalPoint2,
	gl_wrap_handler_glAlphaFunc,
	gl_wrap_handler_glPixelZoom,
	gl_wrap_handler_glPixelTransferf,
	gl_wrap_handler_glPixelTransferi,
	gl_wrap_handler_glPixelMapfv,
	gl_wrap_handler_glPixelMapuiv,
	gl_wrap_handler_glPixelMapusv,
	gl_wrap_handler_glCopyPixels,
	gl_wrap_handler_glDrawPixels,
	gl_wrap_handler_glGetClipPlane,
	gl_wrap_handler_glGetLightfv,
	gl_wrap_handler_glGetLightiv,
	gl_wrap_handler_glGetMapdv,
	gl_wrap_handler_glGetMapfv,
	gl_wrap_handler_glGetMapiv,
	gl_wrap_handler_glGetMaterialfv,
	gl_wrap_handler_glGetMaterialiv,
	gl_wrap_handler_glGetPixelMapfv,
	gl_wrap_handler_glGetPixelMapuiv,
	gl_wrap_handler_glGetPixelMapusv,
	gl_wrap_handler_glGetPolygonStipple,
	gl_wrap_handler_glGetTexEnvfv,
	gl_wrap_handler_glGetTexEnviv,
	gl_wrap_handler_glGetTexGendv,
	gl_wrap_handler_glGetTexGenfv,
	gl_wrap_handler_glGetTexGeniv,
	gl_wrap_handler_glFrustum,
	gl_wrap_handler_glLoadIdentity,
	gl_wrap_handler_glLoadMatrixf,
	gl_wrap_handler_glLoadMatrixd,
	gl_wrap_handler_glMatrixMode,
	gl_wrap_handler_glMultMatrixf,
	gl_wrap_handler_glMultMatrixd,
	gl_wrap_handler_glOrtho,
	gl_wrap_handler_glPopMatrix,
	gl_wrap_handler_glPushMatrix,
	gl_wrap_handler_glRotated,
	gl_wrap_handler_glRotatef,
	gl_wrap_handler_glScaled,
	gl_wrap_handler_glScalef,
	gl_wrap_handler_glTranslated,
	gl_wrap_handler_glTranslatef,
	gl_wrap_handler_glDrawArrays,
	gl_wrap_handler_glDrawElements,
	gl_wrap_handler_glGetPointerv,
	gl_wrap_handler_glPolygonOffset,
	gl_wrap_handler_glCopyTexImage1D,
	gl_wrap_handler_glCopyTexImage2D,
	gl_wrap_handler_glCopyTexSubImage1D,
	gl_wrap_handler_glCopyTexSubImage2D,
	gl_wrap_handler_glTexSubImage1D,
	gl_wrap_handler_glTexSubImage2D,
	gl_wrap_handler_glBindTexture,
	gl_wrap_handler_glDeleteTextures,
	gl_wrap_handler_glGenTextures,
	gl_wrap_handler_glArrayElement,
	gl_wrap_handler_glColorPointer,
	gl_wrap_handler_glDisableClientState,
	gl_wrap_handler_glEdgeFlagPointer,
	gl_wrap_handler_glEnableClientState,
	gl_wrap_handler_glIndexPointer,
	gl_wrap_handler_glInterleavedArrays,
	gl_wrap_handler_glNormalPointer,
	gl_wrap_handler_glTexCoordPointer,
	gl_wrap_handler_glVertexPointer,
	gl_wrap_handler_glPrioritizeTextures,
	gl_wrap_handler_glIndexub,
	gl_wrap_handler_glIndexubv,
	gl_wrap_handler_glPopClientAttrib,
	gl_wrap_handler_glPushClientAttrib,
	gl_wrap_handler_glDrawRangeElements,
	gl_wrap_handler_glTexImage3D,
	gl_wrap_handler_glTexSubImage3D,
	gl_wrap_handler_glCopyTexSubImage3D,
	gl_wrap_handler_glActiveTexture,
	gl_wrap_handler_glSampleCoverage,
	gl_wrap_handler_glCompressedTexImage3D,
	gl_wrap_handler_glCompressedTexImage2D,
	gl_wrap_handler_glCompressedTexImage1D,
	gl_wrap_handler_glCompressedTexSubImage3D,
	gl_wrap_handler_glCompressedTexSubImage2D,
	gl_wrap_handler_glCompressedTexSubImage1D,
	gl_wrap_handler_glGetCompressedTexImage,
	gl_wrap_handler_glClientActiveTexture,
	gl_wrap_handler_glMultiTexCoord1d,
	gl_wrap_handler_glMultiTexCoord1dv,
	gl_wrap_handler_glMultiTexCoord1f,
	gl_wrap_handler_glMultiTexCoord1fv,
	gl_wrap_handler_glMultiTexCoord1i,
	gl_wrap_handler_glMultiTexCoord1iv,
	gl_wrap_handler_glMultiTexCoord1s,
	gl_wrap_handler_glMultiTexCoord1sv,
	gl_wrap_handler_glMultiTexCoord2d,
	gl_wrap_handler_glMultiTexCoord2dv,
	gl_wrap_handler_glMultiTexCoord2f,
	gl_wrap_handler_glMultiTexCoord2fv,
	gl_wrap_handler_glMultiTexCoord2i,
	gl_wrap_handler_glMultiTexCoord2iv,
	gl_wrap_handler_glMultiTexCoord2s,
	gl_wrap_handler_glMultiTexCoord2sv,
	gl_wrap_handler_glMultiTexCoord3d,
	gl_wrap_handler_glMultiTexCoord3dv,
	gl_wrap_handler_glMultiTexCoord3f,
	gl_wrap_handler_glMultiTexCoord3fv,
	gl_wrap_handler_glMultiTexCoord3i,
	gl_wrap_handler_glMultiTexCoord3iv,
	gl_wrap_handler_glMultiTexCoord3s,
	gl_wrap_handler_glMultiTexCoord3sv,
	gl_wrap_handler_glMultiTexCoord4d,
	gl_wrap_handler_glMultiTexCoord4dv,
	gl_wrap_handler_glMultiTexCoord4f,
	gl_wrap_handler_glMultiTexCoord4fv,
	gl_wrap_handler_glMultiTexCoord4i,
	gl_wrap_handler_glMultiTexCoord4iv,
	gl_wrap_handler_glMultiTexCoord4s,
	gl_wrap_handler_glMultiTexCoord4sv,
	gl_wrap_handler_glLoadTransposeMatrixf,
	gl_wrap_handler_glLoadTransposeMatrixd,
	gl_wrap_handler_glMultTransposeMatrixf,
	gl_wrap_handler_glMultTransposeMatrixd,
	gl_wrap_handler_glBlendFuncSeparate,
	gl_wrap_handler_glMultiDrawArrays,
	gl_wrap_handler_glMultiDrawElements,
	gl_wrap_handler_glPointParameterf,
	gl_wrap_handler_glPointParameterfv,
	gl_wrap_handler_glPointParameteri,
	gl_wrap_handler_glPointParameteriv,
	gl_wrap_handler_glFogCoordf,
	gl_wrap_handler_glFogCoordfv,
	gl_wrap_handler_glFogCoordd,
	gl_wrap_handler_glFogCoorddv,
	gl_wrap_handler_glFogCoordPointer,
	gl_wrap_handler_glSecondaryColor3b,
	gl_wrap_handler_glSecondaryColor3bv,
	gl_wrap_handler_glSecondaryColor3d,
	gl_wrap_handler_glSecondaryColor3dv,
	gl_wrap_handler_glSecondaryColor3f,
	gl_wrap_handler_glSecondaryColor3fv,
	gl_wrap_handler_glSecondaryColor3i,
	gl_wrap_handler_glSecondaryColor3iv,
	gl_wrap_handler_glSecondaryColor3s,
	gl_wrap_handler_glSecondaryColor3sv,
	gl_wrap_handler_glSecondaryColor3ub,
	gl_wrap_handler_glSecondaryColor3ubv,
	gl_wrap_handler_glSecondaryColor3ui,
	gl_wrap_handler_glSecondaryColor3uiv,
	gl_wrap_handler_glSecondaryColor3us,
	gl_wrap_handler_glSecondaryColor3usv,
	gl_wrap_handler_glSecondaryColorPointer,
	gl_wrap_handler_glWindowPos2d,
	gl_wrap_handler_glWindowPos2dv,
	gl_wrap_handler_glWindowPos2f,
	gl_wrap_handler_glWindowPos2fv,
	gl_wrap_handler_glWindowPos2i,
	gl_wrap_handler_glWindowPos2iv,
	gl_wrap_handler_glWindowPos2s,
	gl_wrap_handler_glWindowPos2sv,
	gl_wrap_handler_glWindowPos3d,
	gl_wrap_handler_glWindowPos3dv,
	gl_wrap_handler_glWindowPos3f,
	gl_wrap_handler_glWindowPos3fv,
	gl_wrap_handler_glWindowPos3i,
	gl_wrap_handler_glWindowPos3iv,
	gl_wrap_handler_glWindowPos3s,
	gl_wrap_handler_glWindowPos3sv,
	gl_wrap_handler_glBlendColor,
	gl_wrap_handler_glBlendEquation,
	gl_wrap_handler_glGenQueries,
	gl_wrap_handler_glDeleteQueries,
	gl_wrap_handler_glBeginQuery,
	gl_wrap_handler_glEndQuery,
	gl_wrap_handler_glGetQueryiv,
	gl_wrap_handler_glGetQueryObjectiv,
	gl_wrap_handler_glGetQueryObjectuiv,
	gl_wrap_handler_glBindBuffer,
	gl_wrap_handler_glDeleteBuffers,
	gl_wrap_handler_glGenBuffers,
	gl_wrap_handler_glBufferData,
	gl_wrap_handler_glBufferSubData,
	gl_wrap_handler_glGetBufferSubData,
	gl_wrap_handler_glMapBuffer,
	gl_wrap_handler_glGetBufferParameteriv,
	gl_wrap_handler_glGetBufferPointerv,
	gl_wrap_handler_glBlendEquationSeparate,
	gl_wrap_handler_glDrawBuffers,
	gl_wrap_handler_glStencilOpSeparate,
	gl_wrap_handler_glStencilFuncSeparate,
	gl_wrap_handler_glStencilMaskSeparate,
	gl_wrap_handler_glAttachShader,
	gl_wrap_handler_glBindAttribLocation,
	gl_wrap_handler_glCompileShader,
	gl_wrap_handler_glDeleteProgram,
	gl_wrap_handler_glDeleteShader,
	gl_wrap_handler_glDetachShader,
	gl_wrap_handler_glDisableVertexAttribArray,
	gl_wrap_handler_glEnableVertexAttribArray,
	gl_wrap_handler_glGetActiveAttrib,
	gl_wrap_handler_glGetActiveUniform,
	gl_wrap_handler_glGetAttachedShaders,
	gl_wrap_handler_glGetProgramiv,
	gl_wrap_handler_glGetProgramInfoLog,
	gl_wrap_handler_glGetShaderiv,
	gl_wrap_handler_glGetShaderInfoLog,
	gl_wrap_handler_glGetShaderSource,
	gl_wrap_handler_glGetUniformfv,
	gl_wrap_handler_glGetUniformiv,
	gl_wrap_handler_glGetVertexAttribdv,
	gl_wrap_handler_glGetVertexAttribfv,
	gl_wrap_handler_glGetVertexAttribiv,
	gl_wrap_handler_glGetVertexAttribPointerv,
	gl_wrap_handler_glLinkProgram,
	gl_wrap_handler_glShaderSource,
	gl_wrap_handler_glUseProgram,
	gl_wrap_handler_glUniform1f,
	gl_wrap_handler_glUniform2f,
	gl_wrap_handler_glUniform3f,
	gl_wrap_handler_glUniform4f,
	gl_wrap_handler_glUniform1i,
	gl_wrap_handler_glUniform2i,
	gl_wrap_handler_glUniform3i,
	gl_wrap_handler_glUniform4i,
	gl_wrap_handler_glUniform1fv,
	gl_wrap_handler_glUniform2fv,
	gl_wrap_handler_glUniform3fv,
	gl_wrap_handler_glUniform4fv,
	gl_wrap_handler_glUniform1iv,
	gl_wrap_handler_glUniform2iv,
	gl_wrap_handler_glUniform3iv,
	gl_wrap_handler_glUniform4iv,
	gl_wrap_handler_glUniformMatrix2fv,
	gl_wrap_handler_glUniformMatrix3fv,
	gl_wrap_handler_glUniformMatrix4fv,
	gl_wrap_handler_glValidateProgram,
	gl_wrap_handler_glVertexAttrib1d,
	gl_wrap_handler_glVertexAttrib1dv,
	gl_wrap_handler_glVertexAttrib1f,
	gl_wrap_handler_glVertexAttrib1fv,
	gl_wrap_handler_glVertexAttrib1s,
	gl_wrap_handler_glVertexAttrib1sv,
	gl_wrap_handler_glVertexAttrib2d,
	gl_wrap_handler_glVertexAttrib2dv,
	gl_wrap_handler_glVertexAttrib2f,
	gl_wrap_handler_glVertexAttrib2fv,
	gl_wrap_handler_glVertexAttrib2s,
	gl_wrap_handler_glVertexAttrib2sv,
	gl_wrap_handler_glVertexAttrib3d,
	gl_wrap_handler_glVertexAttrib3dv,
	gl_wrap_handler_glVertexAttrib3f,
	gl_wrap_handler_glVertexAttrib3fv,
	gl_wrap_handler_glVertexAttrib3s,
	gl_wrap_handler_glVertexAttrib3sv,
	gl_wrap_handler_glVertexAttrib4Nbv,
	gl_wrap_handler_glVertexAttrib4Niv,
	gl_wrap_handler_glVertexAttrib4Nsv,
	gl_wrap_handler_glVertexAttrib4Nub,
	gl_wrap_handler_glVertexAttrib4Nubv,
	gl_wrap_handler_glVertexAttrib4Nuiv,
	gl_wrap_handler_glVertexAttrib4Nusv,
	gl_wrap_handler_glVertexAttrib4bv,
	gl_wrap_handler_glVertexAttrib4d,
	gl_wrap_handler_glVertexAttrib4dv,
	gl_wrap_handler_glVertexAttrib4f,
	gl_wrap_handler_glVertexAttrib4fv,
	gl_wrap_handler_glVertexAttrib4iv,
	gl_wrap_handler_glVertexAttrib4s,
	gl_wrap_handler_glVertexAttrib4sv,
	gl_wrap_handler_glVertexAttrib4ubv,
	gl_wrap_handler_glVertexAttrib4uiv,
	gl_wrap_handler_glVertexAttrib4usv,
	gl_wrap_handler_glVertexAttribPointer,
	gl_wrap_handler_glUniformMatrix2x3fv,
	gl_wrap_handler_glUniformMatrix3x2fv,
	gl_wrap_handler_glUniformMatrix2x4fv,
	gl_wrap_handler_glUniformMatrix4x2fv,
	gl_wrap_handler_glUniformMatrix3x4fv,
	gl_wrap_handler_glUniformMatrix4x3fv,
	gl_wrap_handler_glColorMaski,
	gl_wrap_handler_glGetBooleani_v,
	gl_wrap_handler_glGetIntegeri_v,
	gl_wrap_handler_glEnablei,
	gl_wrap_handler_glDisablei,
	gl_wrap_handler_glBeginTransformFeedback,
	gl_wrap_handler_glEndTransformFeedback,
	gl_wrap_handler_glBindBufferRange,
	gl_wrap_handler_glBindBufferBase,
	gl_wrap_handler_glTransformFeedbackVaryings,
	gl_wrap_handler_glGetTransformFeedbackVarying,
	gl_wrap_handler_glClampColor,
	gl_wrap_handler_glBeginConditionalRender,
	gl_wrap_handler_glEndConditionalRender,
	gl_wrap_handler_glVertexAttribIPointer,
	gl_wrap_handler_glGetVertexAttribIiv,
	gl_wrap_handler_glGetVertexAttribIuiv,
	gl_wrap_handler_glVertexAttribI1i,
	gl_wrap_handler_glVertexAttribI2i,
	gl_wrap_handler_glVertexAttribI3i,
	gl_wrap_handler_glVertexAttribI4i,
	gl_wrap_handler_glVertexAttribI1ui,
	gl_wrap_handler_glVertexAttribI2ui,
	gl_wrap_handler_glVertexAttribI3ui,
	gl_wrap_handler_glVertexAttribI4ui,
	gl_wrap_handler_glVertexAttribI1iv,
	gl_wrap_handler_glVertexAttribI2iv,
	gl_wrap_handler_glVertexAttribI3iv,
	gl_wrap_handler_glVertexAttribI4iv,
	gl_wrap_handler_glVertexAttribI1uiv,
	gl_wrap_handler_glVertexAttribI2uiv,
	gl_wrap_handler_glVertexAttribI3uiv,
	gl_wrap_handler_glVertexAttribI4uiv,
	gl_wrap_handler_glVertexAttribI4bv,
	gl_wrap_handler_glVertexAttribI4sv,
	gl_wrap_handler_glVertexAttribI4ubv,
	gl_wrap_handler_glVertexAttribI4usv,
	gl_wrap_handler_glGetUniformuiv,
	gl_wrap_handler_glBindFragDataLocation,
	gl_wrap_handler_glUniform1ui,
	gl_wrap_handler_glUniform2ui,
	gl_wrap_handler_glUniform3ui,
	gl_wrap_handler_glUniform4ui,
	gl_wrap_handler_glUniform1uiv,
	gl_wrap_handler_glUniform2uiv,
	gl_wrap_handler_glUniform3uiv,
	gl_wrap_handler_glUniform4uiv,
	gl_wrap_handler_glTexParameterIiv,
	gl_wrap_handler_glTexParameterIuiv,
	gl_wrap_handler_glGetTexParameterIiv,
	gl_wrap_handler_glGetTexParameterIuiv,
	gl_wrap_handler_glClearBufferiv,
	gl_wrap_handler_glClearBufferuiv,
	gl_wrap_handler_glClearBufferfv,
	gl_wrap_handler_glClearBufferfi,
	gl_wrap_handler_glBindRenderbuffer,
	gl_wrap_handler_glDeleteRenderbuffers,
	gl_wrap_handler_glGenRenderbuffers,
	gl_wrap_handler_glRenderbufferStorage,
	gl_wrap_handler_glGetRenderbufferParameteriv,
	gl_wrap_handler_glBindFramebuffer,
	gl_wrap_handler_glDeleteFramebuffers,
	gl_wrap_handler_glGenFramebuffers,
	gl_wrap_handler_glFramebufferTexture1D,
	gl_wrap_handler_glFramebufferTexture2D,
	gl_wrap_handler_glFramebufferTexture3D,
	gl_wrap_handler_glFramebufferRenderbuffer,
	gl_wrap_handler_glGetFramebufferAttachmentParameteriv,
	gl_wrap_handler_glGenerateMipmap,
	gl_wrap_handler_glBlitFramebuffer,
	gl_wrap_handler_glRenderbufferStorageMultisample,
	gl_wrap_handler_glFramebufferTextureLayer,
	gl_wrap_handler_glMapBufferRange,
	gl_wrap_handler_glFlushMappedBufferRange,
	gl_wrap_handler_glBindVertexArray,
	gl_wrap_handler_glDeleteVertexArrays,
	gl_wrap_handler_glGenVertexArrays,
	gl_wrap_handler_glDrawArraysInstanced,
	gl_wrap_handler_glDrawElementsInstanced,
	gl_wrap_handler_glTexBuffer,
	gl_wrap_handler_glPrimitiveRestartIndex,
	gl_wrap_handler_glCopyBufferSubData,
	gl_wrap_handler_glGetUniformIndices,
	gl_wrap_handler_glGetActiveUniformsiv,
	gl_wrap_handler_glGetActiveUniformName,
	gl_wrap_handler_glGetActiveUniformBlockiv,
	gl_wrap_handler_glGetActiveUniformBlockName,
	gl_wrap_handler_glUniformBlockBinding,
	gl_wrap_handler_glDrawElementsBaseVertex,
	gl_wrap_handler_glDrawRangeElementsBaseVertex,
	gl_wrap_handler_glDrawElementsInstancedBaseVertex,
	gl_wrap_handler_glMultiDrawElementsBaseVertex,
	gl_wrap_handler_glProvokingVertex,
	gl_wrap_handler_glDeleteSync,
	gl_wrap_handler_glWaitSync,
	gl_wrap_handler_glGetInteger64v,
	gl_wrap_handler_glGetSynciv,
	gl_wrap_handler_glGetInteger64i_v,
	gl_wrap_handler_glGetBufferParameteri64v,
	gl_wrap_handler_glFramebufferTexture,
	gl_wrap_handler_glTexImage2DMultisample,
	gl_wrap_handler_glTexImage3DMultisample,
	gl_wrap_handler_glGetMultisamplefv,
	gl_wrap_handler_glSampleMaski,
	gl_wrap_handler_glBindFragDataLocationIndexed,
	gl_wrap_handler_glGenSamplers,
	gl_wrap_handler_glDeleteSamplers,
	gl_wrap_handler_glBindSampler,
	gl_wrap_handler_glSamplerParameteri,
	gl_wrap_handler_glSamplerParameteriv,
	gl_wrap_handler_glSamplerParameterf,
	gl_wrap_handler_glSamplerParameterfv,
	gl_wrap_handler_glSamplerParameterIiv,
	gl_wrap_handler_glSamplerParameterIuiv,
	gl_wrap_handler_glGetSamplerParameteriv,
	gl_wrap_handler_glGetSamplerParameterIiv,
	gl_wrap_handler_glGetSamplerParameterfv,
	gl_wrap_handler_glGetSamplerParameterIuiv,
	gl_wrap_handler_glQueryCounter,
	gl_wrap_handler_glGetQueryObjecti64v,
	gl_wrap_handler_glGetQueryObjectui64v,
	gl_wrap_handler_glVertexAttribDivisor,
	gl_wrap_handler_glVertexAttribP1ui,
	gl_wrap_handler_glVertexAttribP1uiv,
	gl_wrap_handler_glVertexAttribP2ui,
	gl_wrap_handler_glVertexAttribP2uiv,
	gl_wrap_handler_glVertexAttribP3ui,
	gl_wrap_handler_glVertexAttribP3uiv,
	gl_wrap_handler_glVertexAttribP4ui,
	gl_wrap_handler_glVertexAttribP4uiv,
	gl_wrap_handler_glVertexP2ui,
	gl_wrap_handler_glVertexP2uiv,
	gl_wrap_handler_glVertexP3ui,
	gl_wrap_handler_glVertexP3uiv,
	gl_wrap_handler_glVertexP4ui,
	gl_wrap_handler_glVertexP4uiv,
	gl_wrap_handler_glTexCoordP1ui,
	gl_wrap_handler_glTexCoordP1uiv,
	gl_wrap_handler_glTexCoordP2ui,
	gl_wrap_handler_glTexCoordP2uiv,
	gl_wrap_handler_glTexCoordP3ui,
	gl_wrap_handler_glTexCoordP3uiv,
	gl_wrap_handler_glTexCoordP4ui,
	gl_wrap_handler_glTexCoordP4uiv,
	gl_wrap_handler_glMultiTexCoordP1ui,
	gl_wrap_handler_glMultiTexCoordP1uiv,
	gl_wrap_handler_glMultiTexCoordP2ui,
	gl_wrap_handler_glMultiTexCoordP2uiv,
	gl_wrap_handler_glMultiTexCoordP3ui,
	gl_wrap_handler_glMultiTexCoordP3uiv,
	gl_wrap_handler_glMultiTexCoordP4ui,
	gl_wrap_handler_glMultiTexCoordP4uiv,
	gl_wrap_handler_glNormalP3ui,
	gl_wrap_handler_glNormalP3uiv,
	gl_wrap_handler_glColorP3ui,
	gl_wrap_handler_glColorP3uiv,
	gl_wrap_handler_glColorP4ui,
	gl_wrap_handler_glColorP4uiv,
	gl_wrap_handler_glSecondaryColorP3ui,
	gl_wrap_handler_glSecondaryColorP3uiv,
	gl_wrap_handler_glMinSampleShading,
	gl_wrap_handler_glBlendEquationi,
	gl_wrap_handler_glBlendEquationSeparatei,
	gl_wrap_handler_glBlendFunci,
	gl_wrap_handler_glBlendFuncSeparatei,
	gl_wrap_handler_glDrawArraysIndirect,
	gl_wrap_handler_glDrawElementsIndirect,
	gl_wrap_handler_glUniform1d,
	gl_wrap_handler_glUniform2d,
	gl_wrap_handler_glUniform3d,
	gl_wrap_handler_glUniform4d,
	gl_wrap_handler_glUniform1dv,
	gl_wrap_handler_glUniform2dv,
	gl_wrap_handler_glUniform3dv,
	gl_wrap_handler_glUniform4dv,
	gl_wrap_handler_glUniformMatrix2dv,
	gl_wrap_handler_glUniformMatrix3dv,
	gl_wrap_handler_glUniformMatrix4dv,
	gl_wrap_handler_glUniformMatrix2x3dv,
	gl_wrap_handler_glUniformMatrix2x4dv,
	gl_wrap_handler_glUniformMatrix3x2dv,
	gl_wrap_handler_glUniformMatrix3x4dv,
	gl_wrap_handler_glUniformMatrix4x2dv,
	gl_wrap_handler_glUniformMatrix4x3dv,
	gl_wrap_handler_glGetUniformdv,
	gl_wrap_handler_glGetActiveSubroutineUniformiv,
	gl_wrap_handler_glGetActiveSubroutineUniformName,
	gl_wrap_handler_glGetActiveSubroutineName,
	gl_wrap_handler_glUniformSubroutinesuiv,
	gl_wrap_handler_glGetUniformSubroutineuiv,
	gl_wrap_handler_glGetProgramStageiv,
	gl_wrap_handler_glPatchParameteri,
	gl_wrap_handler_glPatchParameterfv,
	gl_wrap_handler_glBindTransformFeedback,
	gl_wrap_handler_glDeleteTransformFeedbacks,
	gl_wrap_handler_glGenTransformFeedbacks,
	gl_wrap_handler_glPauseTransformFeedback,
	gl_wrap_handler_glResumeTransformFeedback,
	gl_wrap_handler_glDrawTransformFeedback,
	gl_wrap_handler_glDrawTransformFeedbackStream,
	gl_wrap_handler_glBeginQueryIndexed,
	gl_wrap_handler_glEndQueryIndexed,
	gl_wrap_handler_glGetQueryIndexediv,
	gl_wrap_handler_glReleaseShaderCompiler,
	gl_wrap_handler_glShaderBinary,
	gl_wrap_handler_glGetShaderPrecisionFormat,
	gl_wrap_handler_glDepthRangef,
	gl_wrap_handler_glClearDepthf,
	gl_wrap_handler_glGetProgramBinary,
	gl_wrap_handler_glProgramBinary,
	gl_wrap_handler_glProgramParameteri,
	gl_wrap_handler_glUseProgramStages,
	gl_wrap_handler_glActiveShaderProgram,
	gl_wrap_handler_glBindProgramPipeline,
	gl_wrap_handler_glDeleteProgramPipelines,
	gl_wrap_handler_glGenProgramPipelines,
	gl_wrap_handler_glGetProgramPipelineiv,
	gl_wrap_handler_glProgramUniform1i,
	gl_wrap_handler_glProgramUniform1iv,
	gl_wrap_handler_glProgramUniform1f,
	gl_wrap_handler_glProgramUniform1fv,
	gl_wrap_handler_glProgramUniform1d,
	gl_wrap_handler_glProgramUniform1dv,
	gl_wrap_handler_glProgramUniform1ui,
	gl_wrap_handler_glProgramUniform1uiv,
	gl_wrap_handler_glProgramUniform2i,
	gl_wrap_handler_glProgramUniform2iv,
	gl_wrap_handler_glProgramUniform2f,
	gl_wrap_handler_glProgramUniform2fv,
	gl_wrap_handler_glProgramUniform2d,
	gl_wrap_handler_glProgramUniform2dv,
	gl_wrap_handler_glProgramUniform2ui,
	gl_wrap_handler_glProgramUniform2uiv,
	gl_wrap_handler_glProgramUniform3i,
	gl_wrap_handler_glProgramUniform3iv,
	gl_wrap_handler_glProgramUniform3f,
	gl_wrap_handler_glProgramUniform3fv,
	gl_wrap_handler_glProgramUniform3d,
	gl_wrap_handler_glProgramUniform3dv,
	gl_wrap_handler_glProgramUniform3ui,
	gl_wrap_handler_glProgramUniform3uiv,
	gl_wrap_handler_glProgramUniform4i,
	gl_wrap_handler_glProgramUniform4iv,
	gl_wrap_handler_glProgramUniform4f,
	gl_wrap_handler_glProgramUniform4fv,
	gl_wrap_handler_glProgramUniform4d,
	gl_wrap_handler_glProgramUniform4dv,
	gl_wrap_handler_glProgramUniform4ui,
	gl_wrap_handler_glProgramUniform4uiv,
	gl_wrap_handler_glProgramUniformMatrix2fv,
	gl_wrap_handler_glProgramUniformMatrix3fv,
	gl_wrap_handler_glProgramUniformMatrix4fv,
	gl_wrap_handler_glProgramUniformMatrix2dv,
	gl_wrap_handler_glProgramUniformMatrix3dv,
	gl_wrap_handler_glProgramUniformMatrix4dv,
	gl_wrap_handler_glProgramUniformMatrix2x3fv,
	gl_wrap_handler_glProgramUniformMatrix3x2fv,
	gl_wrap_handler_glProgramUniformMatrix2x4fv,
	gl_wrap_handler_glProgramUniformMatrix4x2fv,
	gl_wrap_handler_glProgramUniformMatrix3x4fv,
	gl_wrap_handler_glProgramUniformMatrix4x3fv,
	gl_wrap_handler_glProgramUniformMatrix2x3dv,
	gl_wrap_handler_glProgramUniformMatrix3x2dv,
	gl_wrap_handler_glProgramUniformMatrix2x4dv,
	gl_wrap_handler_glProgramUniformMatrix4x2dv,
	gl_wrap_handler_glProgramUniformMatrix3x4dv,
	gl_wrap_handler_glProgramUniformMatrix4x3dv,
	gl_wrap_handler_glValidateProgramPipeline,
	gl_wrap_handler_glGetProgramPipelineInfoLog,
	gl_wrap_handler_glVertexAttribL1d,
	gl_wrap_handler_glVertexAttribL2d,
	gl_wrap_handler_glVertexAttribL3d,
	gl_wrap_handler_glVertexAttribL4d,
	gl_wrap_handler_glVertexAttribL1dv,
	gl_wrap_handler_glVertexAttribL2dv,
	gl_wrap_handler_glVertexAttribL3dv,
	gl_wrap_handler_glVertexAttribL4dv,
	gl_wrap_handler_glVertexAttribLPointer,
	gl_wrap_handler_glGetVertexAttribLdv,
	gl_wrap_handler_glViewportArrayv,
	gl_wrap_handler_glViewportIndexedf,
	gl_wrap_handler_glViewportIndexedfv,
	gl_wrap_handler_glScissorArrayv,
	gl_wrap_handler_glScissorIndexed,
	gl_wrap_handler_glScissorIndexedv,
	gl_wrap_handler_glDepthRangeArrayv,
	gl_wrap_handler_glDepthRangeIndexed,
	gl_wrap_handler_glGetFloati_v,
	gl_wrap_handler_glGetDoublei_v,
	gl_wrap_handler_glDrawArraysInstancedBaseInstance,
	gl_wrap_handler_glDrawElementsInstancedBaseInstance,
	gl_wrap_handler_glDrawElementsInstancedBaseVertexBaseInstance,
	gl_wrap_handler_glGetInternalformativ,
	gl_wrap_handler_glGetActiveAtomicCounterBufferiv,
	gl_wrap_handler_glBindImageTexture,
	gl_wrap_handler_glMemoryBarrier,
	gl_wrap_handler_glTexStorage1D,
	gl_wrap_handler_glTexStorage2D,
	gl_wrap_handler_glTexStorage3D,
	gl_wrap_handler_glDrawTransformFeedbackInstanced,
	gl_wrap_handler_glDrawTransformFeedbackStreamInstanced,
	gl_wrap_handler_glClearBufferData,
	gl_wrap_handler_glClearBufferSubData,
	gl_wrap_handler_glDispatchCompute,
	gl_wrap_handler_glDispatchComputeIndirect,
	gl_wrap_handler_glCopyImageSubData,
	gl_wrap_handler_glFramebufferParameteri,
	gl_wrap_handler_glGetFramebufferParameteriv,
	gl_wrap_handler_glGetInternalformati64v,
	gl_wrap_handler_glInvalidateTexSubImage,
	gl_wrap_handler_glInvalidateTexImage,
	gl_wrap_handler_glInvalidateBufferSubData,
	gl_wrap_handler_glInvalidateBufferData,
	gl_wrap_handler_glInvalidateFramebuffer,
	gl_wrap_handler_glInvalidateSubFramebuffer,
	gl_wrap_handler_glMultiDrawArraysIndirect,
	gl_wrap_handler_glMultiDrawElementsIndirect,
	gl_wrap_handler_glGetProgramInterfaceiv,
	gl_wrap_handler_glGetProgramResourceName,
	gl_wrap_handler_glGetProgramResourceiv,
	gl_wrap_handler_glShaderStorageBlockBinding,
	gl_wrap_handler_glTexBufferRange,
	gl_wrap_handler_glTexStorage2DMultisample,
	gl_wrap_handler_glTexStorage3DMultisample,
	gl_wrap_handler_glTextureView,
	gl_wrap_handler_glBindVertexBuffer,
	gl_wrap_handler_glVertexAttribFormat,
	gl_wrap_handler_glVertexAttribIFormat,
	gl_wrap_handler_glVertexAttribLFormat,
	gl_wrap_handler_glVertexAttribBinding,
	gl_wrap_handler_glVertexBindingDivisor,
	gl_wrap_handler_glDebugMessageControl,
	gl_wrap_handler_glDebugMessageInsert,
	gl_wrap_handler_glDebugMessageCallback,
	gl_wrap_handler_glPushDebugGroup,
	gl_wrap_handler_glPopDebugGroup,
	gl_wrap_handler_glObjectLabel,
	gl_wrap_handler_glGetObjectLabel,
	gl_wrap_handler_glObjectPtrLabel,
	gl_wrap_handler_glGetObjectPtrLabel,
	gl_wrap_handler_glBufferStorage,
	gl_wrap_handler_glClearTexImage,
	gl_wrap_handler_glClearTexSubImage,
	gl_wrap_handler_glBindBuffersBase,
	gl_wrap_handler_glBindBuffersRange,
	gl_wrap_handler_glBindTextures,
	gl_wrap_handler_glBindSamplers,
	gl_wrap_handler_glBindImageTextures,
	gl_wrap_handler_glBindVertexBuffers,
};

// Executes the functions in a batch for a given context.
void gl_wrap_batch_exec(gl_wrap_context* ctx, gl_wrap_batch_func* funcs, int numFuncs) {
	int i;
	for(i = 0; i < numFuncs; i++) {
		// Grab the function from the array
		gl_wrap_batch_func func = funcs[i];

		// Locate the handler function in the jump table at jump_index, execute
		// it using the context and function arguments.
		gl_wrap_jump_table[func.jump_index](ctx, func.args);
	}
}
