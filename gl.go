// Copyright 2014 The Azul3D Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.
//
// This source file was automatically generated using glwrap.
// +build 386 amd64
// +build !opengl_debug

// Package gl implements Go bindings to OpenGL.
//
// Debugging OpenGL applications is made easy by using the build tag for this
// package "opengl_debug", that is:
//
// go install -tags "opengl_debug" my/package/path
//
// Debugging using this build tag has both advantages and disadvantages:
//
// Advantage: glGetError() is ran directly after each OpenGL function call for
// you, and in the event of an error a panic will occur in addition to a full
// OpenGL stack trace being dumped to stdout before the panic occurs.
//
// Advantage: Batching cannot be turned on, this can help identify batching
// related bugs (due to incorrect memory management).
//
// Disadvantage: Applications compiled with the opengl_debug build tag are slow
// and will not run at full speed due to both disabled batching and the
// additional glGetError call for each OpenGL call.
//
package gl

/*
#cgo linux LDFLAGS: -lGL
#include "gl.h"
*/
import "C"

import (
	"strconv"
	"strings"
	"unsafe"
)

// Context represents a single OpenGL context's API access.
//
// Since CGO (Go to C) calls are expensive in large quantities as they require
// a context switch due to Go's and C's incompatibile ABI, and since even
// modern OpenGL applications can make several hundred thousands of calls per
// frame, it can become a large bottleneck.
//
// To help remedy this specific bottleneck, batching can be used. When OpenGL
// calls are made and batching is turned on, instead of calls being executed
// immedietly they are stored in a queue and executed later upon a single call
// to the Execute() method.
//
// When batching is turned off and OpenGL calls are made, they are executed
// immedietly, the Execute() method is no-op, and large amounts of OpenGL calls
// will suffer from the performance degration described above.
//
// Additionally, batching may be turned on or off at runtime (even in-between
// OpenGL calls) using the SetBatching() method at runtime.
//
// Note that since batched OpenGL calls are only truly made upon invocation of
// the Execute() method, the memory for pointer arguments to OpenGL function
// calls must remain valid at least untill Execute() is called or else memory
// corruption is possible.
//
// Also note that OpenGL functions which return anything, such as the GetString
// function, cannot be queued for batching because they require that the value
// be immedietly returned. Also, if the function in question relies on previous
// OpenGL commands being executed first, you are responsible for calling the
// Execute() method.
//
// Since batching requires some extra effort on the programmer's side, and
// since debugging applications with batching turned on is more difficult, it
// is by default turned off.
type Context struct {
	c                                       *C.gl_wrap_context
	batch                                   []C.gl_wrap_batch_func
	batching                                bool
	loadedShaderVersion, loadedVersion      bool
	major, minor, release                   int
	shaderMajor, shaderMinor, shaderRelease int
	vendorVersion, vendorShaderVersion      string
	extensions                              map[string]bool
}

// New returns a new initialized Context with batching turned on.
func New() *Context {
	c := new(Context)
	c.c = new(C.gl_wrap_context)
	c.batching = false
	return c
}

// SetBatching turns on or off batching of this Context.
//
// If turning off batching using SetBatching(false), then an implicit call to
// Execute() which executes all the currently pending OpenGL function calls on
// this Context occurs.
//
// Default value is off (false).
func (c *Context) SetBatching(batching bool) {
	if !batching && len(c.batch) > 0 {
		c.Execute()
	}
	c.batching = batching
}

// Batching tells whether or not batching is on or off for this Context.
func (c *Context) Batching() bool {
	return c.batching
}

func (c *Context) push(f C.gl_wrap_batch_func) {
	c.batch = append(c.batch, f)
}

// Execute executes all the currently pending OpenGL function calls for this
// Context.
//
// This function executes pending calls regardless of whether or not batching
// is turned on.
func (c *Context) Execute() {
	if len(c.batch) > 0 {
		C.gl_wrap_batch_exec(
			c.c,
			(*C.gl_wrap_batch_func)(unsafe.Pointer(&c.batch[0])),
			C.int(len(c.batch)),
		)

		// Re-slice the batch
		c.batch = c.batch[:0]
	}
}

func (c *Context) parseVersionString(ver string) (major, minor, release int, vendor string) {
	if len(ver) == 0 {
		// Version string must not be empty
		return
	}

	// According to http://www.opengl.org/sdk/docs/man/xhtml/glGetString.xml
	//
	// the string returned may be 'major.minor' or 'major.minor.release'
	// and may be following by a space and any vendor specific information.

	// First locate a proper version string without vendor specific
	// information.
	var (
		versionString string
		err           error
	)
	if strings.Contains(ver, " ") {
		// It must have vendor information
		split := strings.Split(ver, " ")
		if len(split) > 0 || len(split[0]) > 0 {
			// Everything looks good.
			versionString = split[0]
		} else {
			// Something must be wrong with their vendor string.
			return
		}

		// Store the vendor version information.
		vendor = ver[len(versionString):]
	} else {
		// No vendor information.
		versionString = ver
	}

	// We have a proper version string now without vendor information.
	dots := strings.Count(versionString, ".")
	if dots == 1 {
		// It's a 'major.minor' style string
		versions := strings.Split(versionString, ".")
		if len(versions) == 2 {
			major, err = strconv.Atoi(versions[0])
			if err != nil {
				return
			}

			minor, err = strconv.Atoi(versions[1])
			if err != nil {
				return
			}

		} else {
			return
		}

	} else if dots == 2 {
		// It's a 'major.minor.release' style string
		versions := strings.Split(versionString, ".")
		if len(versions) == 3 {
			major, err = strconv.Atoi(versions[0])
			if err != nil {
				return
			}

			minor, err = strconv.Atoi(versions[1])
			if err != nil {
				return
			}

			release, err = strconv.Atoi(versions[2])
			if err != nil {
				return
			}
		} else {
			return
		}
	}
	return
}

func (c *Context) initVersion() {
	c.loadedVersion = true
	versionString := String(c.GetString(VERSION))
	c.major, c.minor, c.release, c.vendorVersion = c.parseVersionString(versionString)
}

func (c *Context) initShaderVersion() {
	c.loadedShaderVersion = true
	versionString := String(c.GetString(SHADING_LANGUAGE_VERSION))
	c.shaderMajor, c.shaderMinor, c.shaderRelease, c.vendorShaderVersion = c.parseVersionString(versionString)
}

// Version returns the major and minor OpenGL version supported by the
// implementation.
//
// Additionally provided is the vendor-specific release version (E.g. a driver
// version number).
func (c *Context) Version() (major, minor, release int) {
	if !c.loadedVersion {
		c.initVersion()
	}
	return c.major, c.minor, c.release
}

// AtLeastVersion tells if the major and minor OpenGL version reported by
// c.Version() is at least minMajor, minMinor.
//
// It is implemented as:
//
//  if major > minMajor {
//      return true
//  } else if major == minMajor && minor >= minMinor {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastVersion(minMajor, minMinor int) bool {
	if !c.loadedVersion {
		c.initVersion()
	}
	major, minor := c.major, c.minor
	if major > minMajor {
		return true
	} else if major == minMajor && minor >= minMinor {
		return true
	}
	return false
}

// AtLeastRelease tells if the release OpenGL version reported by c.Version()
// is at least minRelease.
//
// It is implemented as:
//
//  if release == 0 {
//      return true
//  } else if release >= minRelease {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastRelease(minRelease int) bool {
	if !c.loadedVersion {
		c.initVersion()
	}
	release := c.release
	if release == 0 {
		return true
	} else if release >= minRelease {
		return true
	}
	return false
}

// VendorVersion returns the vendor-specific OpenGL version information.
//
// This string depends on the vendor of the graphics card/driver.
func (c *Context) VendorVersion() string {
	if !c.loadedVersion {
		c.initVersion()
	}
	return c.vendorVersion
}

// ShaderVersion returns the major and minor version of the supported GLSL
// shading language per the OpenGL implementation.
//
// Additionally provided is the vendor-specific release version (E.g. a driver
// version number).
func (c *Context) ShaderVersion() (major, minor, release int) {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	return c.shaderMajor, c.shaderMinor, c.shaderRelease
}

// AtLeastShaderVersion tells if the major and minor GLSL version reported by
// c.ShaderVersion() is at least minMajor, minMinor.
//
// It is implemented as:
//
//  if major > minMajor {
//      return true
//  } else if major == minMajor && minor >= minMinor {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastShaderVersion(minMajor, minMinor int) bool {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	major, minor := c.shaderMajor, c.shaderMinor
	if major > minMajor {
		return true
	} else if major == minMajor && minor >= minMinor {
		return true
	}
	return false
}

// AtLeastShaderRelease tells if the release GLSL version reported by
// c.ShaderVersion() is at least minRelease.
//
// It is implemented as:
//
//  if release == 0 {
//      return true
//  } else if release >= minRelease {
//      return true
//  }
//  return false
//
func (c *Context) AtLeastShaderRelease(minRelease int) bool {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	release := c.shaderRelease
	if release == 0 {
		return true
	} else if release >= minRelease {
		return true
	}
	return false
}

// VendorShaderVersion returns the vendor-specific shading language version
// information.
//
// This string depends on the vendor of the graphics card/driver.
func (c *Context) VendorShaderVersion() string {
	if !c.loadedShaderVersion {
		c.initShaderVersion()
	}
	return c.vendorShaderVersion
}

func (c *Context) initExtensions() {
	// Initialize extensions map
	extString := String(c.GetString(EXTENSIONS))
	if len(extString) > 0 {
		split := strings.Split(extString, " ")
		c.extensions = make(map[string]bool, len(split))
		for _, ext := range split {
			if len(ext) > 0 {
				c.extensions[ext] = true
			}
		}
	} else {
		c.extensions = make(map[string]bool)
	}
}

// Extensions returns a slice of strings which represents all the extensions
// supported by the OpenGL implementation.
//
// Internally a map is used to store them, so a copy in the form of a slice is
// returned.
func (c *Context) Extensions() []string {
	if c.extensions == nil {
		c.initExtensions()
	}
	cpy := make([]string, len(c.extensions))
	i := 0
	for ext, _ := range c.extensions {
		cpy[i] = ext
		i++
	}
	return cpy
}

// Extension tells if the specified extension is supported by the OpenGL
// implementation.
func (c *Context) Extension(name string) (supported bool) {
	if c.extensions == nil {
		c.initExtensions()
	}
	_, supported = c.extensions[name]
	return
}

// Declare non-batchable functions

func (c *Context) GetError() int32 {
	return int32(C.gl_wrap_context_glGetError(c.c))
}

func (c *Context) GetString(name int32) *uint8 {
	return (*uint8)(unsafe.Pointer(C.gl_wrap_context_glGetString(c.c, C.GLenum(name))))
}

func (c *Context) IsEnabled(cap int32) uint8 {
	return uint8(C.gl_wrap_context_glIsEnabled(c.c, C.GLenum(cap)))
}

func (c *Context) GenLists(pRange uint32) uint32 {
	return uint32(C.gl_wrap_context_glGenLists(c.c, C.GLsizei(pRange)))
}

func (c *Context) RenderMode(mode int32) int32 {
	return int32(C.gl_wrap_context_glRenderMode(c.c, C.GLenum(mode)))
}

func (c *Context) IsList(list uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsList(c.c, C.GLuint(list)))
}

func (c *Context) IsTexture(texture uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsTexture(c.c, C.GLuint(texture)))
}

func (c *Context) AreTexturesResident(n uint32, textures *uint32, residences *uint8) uint8 {
	return uint8(C.gl_wrap_context_glAreTexturesResident(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(textures)), (*C.GLboolean)(unsafe.Pointer(residences))))
}

func (c *Context) IsQuery(id uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsQuery(c.c, C.GLuint(id)))
}

func (c *Context) IsBuffer(buffer uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsBuffer(c.c, C.GLuint(buffer)))
}

func (c *Context) UnmapBuffer(target int32) uint8 {
	return uint8(C.gl_wrap_context_glUnmapBuffer(c.c, C.GLenum(target)))
}

func (c *Context) CreateProgram() uint32 {
	return uint32(C.gl_wrap_context_glCreateProgram(c.c))
}

func (c *Context) CreateShader(pType int32) uint32 {
	return uint32(C.gl_wrap_context_glCreateShader(c.c, C.GLenum(pType)))
}

func (c *Context) GetAttribLocation(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetAttribLocation(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetUniformLocation(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetUniformLocation(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) IsProgram(program uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsProgram(c.c, C.GLuint(program)))
}

func (c *Context) IsShader(shader uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsShader(c.c, C.GLuint(shader)))
}

func (c *Context) IsEnabledi(target int32, index uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsEnabledi(c.c, C.GLenum(target), C.GLuint(index)))
}

func (c *Context) GetFragDataLocation(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetFragDataLocation(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetStringi(name int32, index uint32) *uint8 {
	return (*uint8)(unsafe.Pointer(C.gl_wrap_context_glGetStringi(c.c, C.GLenum(name), C.GLuint(index))))
}

func (c *Context) IsRenderbuffer(renderbuffer uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsRenderbuffer(c.c, C.GLuint(renderbuffer)))
}

func (c *Context) IsFramebuffer(framebuffer uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsFramebuffer(c.c, C.GLuint(framebuffer)))
}

func (c *Context) CheckFramebufferStatus(target int32) int32 {
	return int32(C.gl_wrap_context_glCheckFramebufferStatus(c.c, C.GLenum(target)))
}

func (c *Context) IsVertexArray(array uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsVertexArray(c.c, C.GLuint(array)))
}

func (c *Context) GetUniformBlockIndex(program uint32, uniformBlockName *byte) uint32 {
	return uint32(C.gl_wrap_context_glGetUniformBlockIndex(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(uniformBlockName))))
}

func (c *Context) FenceSync(condition int32, flags uint32) Sync {
	return Sync(C.gl_wrap_context_glFenceSync(c.c, C.GLenum(condition), C.GLbitfield(flags)))
}

func (c *Context) IsSync(sync Sync) uint8 {
	return uint8(C.gl_wrap_context_glIsSync(c.c, C.GLsync(sync)))
}

func (c *Context) ClientWaitSync(sync Sync, flags uint32, timeout uint64) int32 {
	return int32(C.gl_wrap_context_glClientWaitSync(c.c, C.GLsync(sync), C.GLbitfield(flags), C.GLuint64(timeout)))
}

func (c *Context) GetFragDataIndex(program uint32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetFragDataIndex(c.c, C.GLuint(program), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) IsSampler(sampler uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsSampler(c.c, C.GLuint(sampler)))
}

func (c *Context) GetSubroutineUniformLocation(program uint32, shadertype int32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetSubroutineUniformLocation(c.c, C.GLuint(program), C.GLenum(shadertype), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetSubroutineIndex(program uint32, shadertype int32, name *byte) uint32 {
	return uint32(C.gl_wrap_context_glGetSubroutineIndex(c.c, C.GLuint(program), C.GLenum(shadertype), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) IsTransformFeedback(id uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsTransformFeedback(c.c, C.GLuint(id)))
}

func (c *Context) CreateShaderProgramv(pType int32, count uint32, strings **byte) uint32 {
	return uint32(C.gl_wrap_context_glCreateShaderProgramv(c.c, C.GLenum(pType), C.GLsizei(count), (**C.GLchar)(unsafe.Pointer(strings))))
}

func (c *Context) IsProgramPipeline(pipeline uint32) uint8 {
	return uint8(C.gl_wrap_context_glIsProgramPipeline(c.c, C.GLuint(pipeline)))
}

func (c *Context) GetProgramResourceIndex(program uint32, programInterface int32, name *byte) uint32 {
	return uint32(C.gl_wrap_context_glGetProgramResourceIndex(c.c, C.GLuint(program), C.GLenum(programInterface), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetProgramResourceLocation(program uint32, programInterface int32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetProgramResourceLocation(c.c, C.GLuint(program), C.GLenum(programInterface), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetProgramResourceLocationIndex(program uint32, programInterface int32, name *byte) int32 {
	return int32(C.gl_wrap_context_glGetProgramResourceLocationIndex(c.c, C.GLuint(program), C.GLenum(programInterface), (*C.GLchar)(unsafe.Pointer(name))))
}

func (c *Context) GetDebugMessageLog(count uint32, bufSize uint32, sources *int32, types *int32, ids *uint32, severities *int32, lengths *uint32, messageLog *byte) uint32 {
	return uint32(C.gl_wrap_context_glGetDebugMessageLog(c.c, C.GLuint(count), C.GLsizei(bufSize), (*C.GLenum)(unsafe.Pointer(sources)), (*C.GLenum)(unsafe.Pointer(types)), (*C.GLuint)(unsafe.Pointer(ids)), (*C.GLenum)(unsafe.Pointer(severities)), (*C.GLsizei)(unsafe.Pointer(lengths)), (*C.GLchar)(unsafe.Pointer(messageLog))))
}

// Declare batchable functions

func (c *Context) CullFace(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCullFace_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 0,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCullFace(c.c, C.GLenum(mode))
	}
}

func (c *Context) FrontFace(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFrontFace_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 1,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFrontFace(c.c, C.GLenum(mode))
	}
}

func (c *Context) Hint(target int32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glHint_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 2,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glHint(c.c, C.GLenum(target), C.GLenum(mode))
	}
}

func (c *Context) LineWidth(width float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLineWidth_args
		glWrapHandlerArgs.width = C.GLfloat(width)

		c.push(C.gl_wrap_batch_func{
			jump_index: 3,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLineWidth(c.c, C.GLfloat(width))
	}
}

func (c *Context) PointSize(size float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPointSize_args
		glWrapHandlerArgs.size = C.GLfloat(size)

		c.push(C.gl_wrap_batch_func{
			jump_index: 4,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPointSize(c.c, C.GLfloat(size))
	}
}

func (c *Context) PolygonMode(face int32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPolygonMode_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 5,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPolygonMode(c.c, C.GLenum(face), C.GLenum(mode))
	}
}

func (c *Context) Scissor(x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScissor_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 6,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScissor(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) TexParameterf(target int32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameterf_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 7,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameterf(c.c, C.GLenum(target), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) TexParameterfv(target int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameterfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 8,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameterfv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexParameteri(target int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameteri_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 9,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameteri(c.c, C.GLenum(target), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) TexParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 10,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexImage1D(target int32, level int32, internalformat int32, width uint32, border int32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLint(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 11,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage1D(c.c, C.GLenum(target), C.GLint(level), C.GLint(internalformat), C.GLsizei(width), C.GLint(border), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) TexImage2D(target int32, level int32, internalformat int32, width uint32, height uint32, border int32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLint(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 12,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLint(border), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) DrawBuffer(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawBuffer_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 13,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawBuffer(c.c, C.GLenum(mode))
	}
}

func (c *Context) Clear(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClear_args
		glWrapHandlerArgs.mask = C.GLbitfield(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 14,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClear(c.c, C.GLbitfield(mask))
	}
}

func (c *Context) ClearColor(red float32, green float32, blue float32, alpha float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearColor_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)
		glWrapHandlerArgs.alpha = C.GLfloat(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 15,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearColor(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue), C.GLfloat(alpha))
	}
}

func (c *Context) ClearStencil(s int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearStencil_args
		glWrapHandlerArgs.s = C.GLint(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 16,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearStencil(c.c, C.GLint(s))
	}
}

func (c *Context) ClearDepth(depth float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearDepth_args
		glWrapHandlerArgs.depth = C.GLdouble(depth)

		c.push(C.gl_wrap_batch_func{
			jump_index: 17,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearDepth(c.c, C.GLdouble(depth))
	}
}

func (c *Context) StencilMask(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilMask_args
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 18,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilMask(c.c, C.GLuint(mask))
	}
}

func (c *Context) ColorMask(red uint8, green uint8, blue uint8, alpha uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorMask_args
		glWrapHandlerArgs.red = C.GLboolean(red)
		glWrapHandlerArgs.green = C.GLboolean(green)
		glWrapHandlerArgs.blue = C.GLboolean(blue)
		glWrapHandlerArgs.alpha = C.GLboolean(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 19,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorMask(c.c, C.GLboolean(red), C.GLboolean(green), C.GLboolean(blue), C.GLboolean(alpha))
	}
}

func (c *Context) DepthMask(flag uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthMask_args
		glWrapHandlerArgs.flag = C.GLboolean(flag)

		c.push(C.gl_wrap_batch_func{
			jump_index: 20,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthMask(c.c, C.GLboolean(flag))
	}
}

func (c *Context) Disable(cap int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDisable_args
		glWrapHandlerArgs.cap = C.GLenum(cap)

		c.push(C.gl_wrap_batch_func{
			jump_index: 21,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDisable(c.c, C.GLenum(cap))
	}
}

func (c *Context) Enable(cap int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnable_args
		glWrapHandlerArgs.cap = C.GLenum(cap)

		c.push(C.gl_wrap_batch_func{
			jump_index: 22,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnable(c.c, C.GLenum(cap))
	}
}

func (c *Context) Finish() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFinish_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 23,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFinish(c.c)
	}
}

func (c *Context) Flush() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFlush_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 24,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFlush(c.c)
	}
}

func (c *Context) BlendFunc(sfactor int32, dfactor int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendFunc_args
		glWrapHandlerArgs.sfactor = C.GLenum(sfactor)
		glWrapHandlerArgs.dfactor = C.GLenum(dfactor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 25,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendFunc(c.c, C.GLenum(sfactor), C.GLenum(dfactor))
	}
}

func (c *Context) LogicOp(opcode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLogicOp_args
		glWrapHandlerArgs.opcode = C.GLenum(opcode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 26,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLogicOp(c.c, C.GLenum(opcode))
	}
}

func (c *Context) StencilFunc(pFunc int32, ref int32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilFunc_args
		glWrapHandlerArgs._func = C.GLenum(pFunc)
		glWrapHandlerArgs.ref = C.GLint(ref)
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 27,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilFunc(c.c, C.GLenum(pFunc), C.GLint(ref), C.GLuint(mask))
	}
}

func (c *Context) StencilOp(fail int32, zfail int32, zpass int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilOp_args
		glWrapHandlerArgs.fail = C.GLenum(fail)
		glWrapHandlerArgs.zfail = C.GLenum(zfail)
		glWrapHandlerArgs.zpass = C.GLenum(zpass)

		c.push(C.gl_wrap_batch_func{
			jump_index: 28,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilOp(c.c, C.GLenum(fail), C.GLenum(zfail), C.GLenum(zpass))
	}
}

func (c *Context) DepthFunc(pFunc int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthFunc_args
		glWrapHandlerArgs._func = C.GLenum(pFunc)

		c.push(C.gl_wrap_batch_func{
			jump_index: 29,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthFunc(c.c, C.GLenum(pFunc))
	}
}

func (c *Context) PixelStoref(pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelStoref_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 30,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelStoref(c.c, C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) PixelStorei(pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelStorei_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 31,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelStorei(c.c, C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) ReadBuffer(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glReadBuffer_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 32,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glReadBuffer(c.c, C.GLenum(mode))
	}
}

func (c *Context) ReadPixels(x int32, y int32, width uint32, height uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glReadPixels_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 33,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glReadPixels(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) GetBooleanv(pname int32, data *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBooleanv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLboolean)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 34,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBooleanv(c.c, C.GLenum(pname), (*C.GLboolean)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetDoublev(pname int32, data *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetDoublev_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLdouble)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 35,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetDoublev(c.c, C.GLenum(pname), (*C.GLdouble)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetFloatv(pname int32, data *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFloatv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLfloat)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 36,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFloatv(c.c, C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetIntegerv(pname int32, data *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetIntegerv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLint)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 37,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetIntegerv(c.c, C.GLenum(pname), (*C.GLint)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetTexImage(target int32, level int32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexImage_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 38,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexImage(c.c, C.GLenum(target), C.GLint(level), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) GetTexParameterfv(target int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexParameterfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 39,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexParameterfv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 40,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexLevelParameterfv(target int32, level int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexLevelParameterfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 41,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexLevelParameterfv(c.c, C.GLenum(target), C.GLint(level), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexLevelParameteriv(target int32, level int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexLevelParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 42,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexLevelParameteriv(c.c, C.GLenum(target), C.GLint(level), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) DepthRange(near float64, far float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthRange_args
		glWrapHandlerArgs.near = C.GLdouble(near)
		glWrapHandlerArgs.far = C.GLdouble(far)

		c.push(C.gl_wrap_batch_func{
			jump_index: 43,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthRange(c.c, C.GLdouble(near), C.GLdouble(far))
	}
}

func (c *Context) Viewport(x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glViewport_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 44,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glViewport(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) NewList(list uint32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNewList_args
		glWrapHandlerArgs.list = C.GLuint(list)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 45,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNewList(c.c, C.GLuint(list), C.GLenum(mode))
	}
}

func (c *Context) EndList() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndList_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 46,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndList(c.c)
	}
}

func (c *Context) CallList(list uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCallList_args
		glWrapHandlerArgs.list = C.GLuint(list)

		c.push(C.gl_wrap_batch_func{
			jump_index: 47,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCallList(c.c, C.GLuint(list))
	}
}

func (c *Context) CallLists(n uint32, pType int32, lists unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCallLists_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.lists = lists

		c.push(C.gl_wrap_batch_func{
			jump_index: 48,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCallLists(c.c, C.GLsizei(n), C.GLenum(pType), lists)
	}
}

func (c *Context) DeleteLists(list uint32, pRange uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteLists_args
		glWrapHandlerArgs.list = C.GLuint(list)
		glWrapHandlerArgs._range = C.GLsizei(pRange)

		c.push(C.gl_wrap_batch_func{
			jump_index: 49,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteLists(c.c, C.GLuint(list), C.GLsizei(pRange))
	}
}

func (c *Context) ListBase(base uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glListBase_args
		glWrapHandlerArgs.base = C.GLuint(base)

		c.push(C.gl_wrap_batch_func{
			jump_index: 50,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glListBase(c.c, C.GLuint(base))
	}
}

func (c *Context) Begin(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBegin_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 51,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBegin(c.c, C.GLenum(mode))
	}
}

func (c *Context) Bitmap(width uint32, height uint32, xorig float32, yorig float32, xmove float32, ymove float32, bitmap *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBitmap_args
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.xorig = C.GLfloat(xorig)
		glWrapHandlerArgs.yorig = C.GLfloat(yorig)
		glWrapHandlerArgs.xmove = C.GLfloat(xmove)
		glWrapHandlerArgs.ymove = C.GLfloat(ymove)
		glWrapHandlerArgs.bitmap = (*C.GLubyte)(unsafe.Pointer(bitmap))

		c.push(C.gl_wrap_batch_func{
			jump_index: 52,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBitmap(c.c, C.GLsizei(width), C.GLsizei(height), C.GLfloat(xorig), C.GLfloat(yorig), C.GLfloat(xmove), C.GLfloat(ymove), (*C.GLubyte)(unsafe.Pointer(bitmap)))
	}
}

func (c *Context) Color3b(red byte, green byte, blue byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3b_args
		glWrapHandlerArgs.red = C.GLbyte(red)
		glWrapHandlerArgs.green = C.GLbyte(green)
		glWrapHandlerArgs.blue = C.GLbyte(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 53,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3b(c.c, C.GLbyte(red), C.GLbyte(green), C.GLbyte(blue))
	}
}

func (c *Context) Color3bv(v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3bv_args
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 54,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3bv(c.c, (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3d(red float64, green float64, blue float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3d_args
		glWrapHandlerArgs.red = C.GLdouble(red)
		glWrapHandlerArgs.green = C.GLdouble(green)
		glWrapHandlerArgs.blue = C.GLdouble(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 55,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3d(c.c, C.GLdouble(red), C.GLdouble(green), C.GLdouble(blue))
	}
}

func (c *Context) Color3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 56,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3f(red float32, green float32, blue float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3f_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 57,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3f(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue))
	}
}

func (c *Context) Color3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 58,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3i(red int32, green int32, blue int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3i_args
		glWrapHandlerArgs.red = C.GLint(red)
		glWrapHandlerArgs.green = C.GLint(green)
		glWrapHandlerArgs.blue = C.GLint(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 59,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3i(c.c, C.GLint(red), C.GLint(green), C.GLint(blue))
	}
}

func (c *Context) Color3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 60,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3s(red int16, green int16, blue int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3s_args
		glWrapHandlerArgs.red = C.GLshort(red)
		glWrapHandlerArgs.green = C.GLshort(green)
		glWrapHandlerArgs.blue = C.GLshort(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 61,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3s(c.c, C.GLshort(red), C.GLshort(green), C.GLshort(blue))
	}
}

func (c *Context) Color3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 62,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3ub(red uint8, green uint8, blue uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3ub_args
		glWrapHandlerArgs.red = C.GLubyte(red)
		glWrapHandlerArgs.green = C.GLubyte(green)
		glWrapHandlerArgs.blue = C.GLubyte(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 63,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3ub(c.c, C.GLubyte(red), C.GLubyte(green), C.GLubyte(blue))
	}
}

func (c *Context) Color3ubv(v *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3ubv_args
		glWrapHandlerArgs.v = (*C.GLubyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 64,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3ubv(c.c, (*C.GLubyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3ui(red uint32, green uint32, blue uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3ui_args
		glWrapHandlerArgs.red = C.GLuint(red)
		glWrapHandlerArgs.green = C.GLuint(green)
		glWrapHandlerArgs.blue = C.GLuint(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 65,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3ui(c.c, C.GLuint(red), C.GLuint(green), C.GLuint(blue))
	}
}

func (c *Context) Color3uiv(v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3uiv_args
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 66,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3uiv(c.c, (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color3us(red uint16, green uint16, blue uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3us_args
		glWrapHandlerArgs.red = C.GLushort(red)
		glWrapHandlerArgs.green = C.GLushort(green)
		glWrapHandlerArgs.blue = C.GLushort(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 67,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3us(c.c, C.GLushort(red), C.GLushort(green), C.GLushort(blue))
	}
}

func (c *Context) Color3usv(v *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor3usv_args
		glWrapHandlerArgs.v = (*C.GLushort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 68,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor3usv(c.c, (*C.GLushort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4b(red byte, green byte, blue byte, alpha byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4b_args
		glWrapHandlerArgs.red = C.GLbyte(red)
		glWrapHandlerArgs.green = C.GLbyte(green)
		glWrapHandlerArgs.blue = C.GLbyte(blue)
		glWrapHandlerArgs.alpha = C.GLbyte(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 69,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4b(c.c, C.GLbyte(red), C.GLbyte(green), C.GLbyte(blue), C.GLbyte(alpha))
	}
}

func (c *Context) Color4bv(v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4bv_args
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 70,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4bv(c.c, (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4d(red float64, green float64, blue float64, alpha float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4d_args
		glWrapHandlerArgs.red = C.GLdouble(red)
		glWrapHandlerArgs.green = C.GLdouble(green)
		glWrapHandlerArgs.blue = C.GLdouble(blue)
		glWrapHandlerArgs.alpha = C.GLdouble(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 71,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4d(c.c, C.GLdouble(red), C.GLdouble(green), C.GLdouble(blue), C.GLdouble(alpha))
	}
}

func (c *Context) Color4dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 72,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4f(red float32, green float32, blue float32, alpha float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4f_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)
		glWrapHandlerArgs.alpha = C.GLfloat(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 73,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4f(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue), C.GLfloat(alpha))
	}
}

func (c *Context) Color4fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 74,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4i(red int32, green int32, blue int32, alpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4i_args
		glWrapHandlerArgs.red = C.GLint(red)
		glWrapHandlerArgs.green = C.GLint(green)
		glWrapHandlerArgs.blue = C.GLint(blue)
		glWrapHandlerArgs.alpha = C.GLint(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 75,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4i(c.c, C.GLint(red), C.GLint(green), C.GLint(blue), C.GLint(alpha))
	}
}

func (c *Context) Color4iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 76,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4s(red int16, green int16, blue int16, alpha int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4s_args
		glWrapHandlerArgs.red = C.GLshort(red)
		glWrapHandlerArgs.green = C.GLshort(green)
		glWrapHandlerArgs.blue = C.GLshort(blue)
		glWrapHandlerArgs.alpha = C.GLshort(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 77,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4s(c.c, C.GLshort(red), C.GLshort(green), C.GLshort(blue), C.GLshort(alpha))
	}
}

func (c *Context) Color4sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 78,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4ub(red uint8, green uint8, blue uint8, alpha uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4ub_args
		glWrapHandlerArgs.red = C.GLubyte(red)
		glWrapHandlerArgs.green = C.GLubyte(green)
		glWrapHandlerArgs.blue = C.GLubyte(blue)
		glWrapHandlerArgs.alpha = C.GLubyte(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 79,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4ub(c.c, C.GLubyte(red), C.GLubyte(green), C.GLubyte(blue), C.GLubyte(alpha))
	}
}

func (c *Context) Color4ubv(v *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4ubv_args
		glWrapHandlerArgs.v = (*C.GLubyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 80,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4ubv(c.c, (*C.GLubyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4ui(red uint32, green uint32, blue uint32, alpha uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4ui_args
		glWrapHandlerArgs.red = C.GLuint(red)
		glWrapHandlerArgs.green = C.GLuint(green)
		glWrapHandlerArgs.blue = C.GLuint(blue)
		glWrapHandlerArgs.alpha = C.GLuint(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 81,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4ui(c.c, C.GLuint(red), C.GLuint(green), C.GLuint(blue), C.GLuint(alpha))
	}
}

func (c *Context) Color4uiv(v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4uiv_args
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 82,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4uiv(c.c, (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Color4us(red uint16, green uint16, blue uint16, alpha uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4us_args
		glWrapHandlerArgs.red = C.GLushort(red)
		glWrapHandlerArgs.green = C.GLushort(green)
		glWrapHandlerArgs.blue = C.GLushort(blue)
		glWrapHandlerArgs.alpha = C.GLushort(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 83,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4us(c.c, C.GLushort(red), C.GLushort(green), C.GLushort(blue), C.GLushort(alpha))
	}
}

func (c *Context) Color4usv(v *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColor4usv_args
		glWrapHandlerArgs.v = (*C.GLushort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 84,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColor4usv(c.c, (*C.GLushort)(unsafe.Pointer(v)))
	}
}

func (c *Context) EdgeFlag(flag uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEdgeFlag_args
		glWrapHandlerArgs.flag = C.GLboolean(flag)

		c.push(C.gl_wrap_batch_func{
			jump_index: 85,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEdgeFlag(c.c, C.GLboolean(flag))
	}
}

func (c *Context) EdgeFlagv(flag *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEdgeFlagv_args
		glWrapHandlerArgs.flag = (*C.GLboolean)(unsafe.Pointer(flag))

		c.push(C.gl_wrap_batch_func{
			jump_index: 86,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEdgeFlagv(c.c, (*C.GLboolean)(unsafe.Pointer(flag)))
	}
}

func (c *Context) End() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnd_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 87,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnd(c.c)
	}
}

func (c *Context) Indexd(pC float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexd_args
		glWrapHandlerArgs.c = C.GLdouble(pC)

		c.push(C.gl_wrap_batch_func{
			jump_index: 88,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexd(c.c, C.GLdouble(pC))
	}
}

func (c *Context) Indexdv(pC *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexdv_args
		glWrapHandlerArgs.c = (*C.GLdouble)(unsafe.Pointer(pC))

		c.push(C.gl_wrap_batch_func{
			jump_index: 89,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexdv(c.c, (*C.GLdouble)(unsafe.Pointer(pC)))
	}
}

func (c *Context) Indexf(pC float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexf_args
		glWrapHandlerArgs.c = C.GLfloat(pC)

		c.push(C.gl_wrap_batch_func{
			jump_index: 90,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexf(c.c, C.GLfloat(pC))
	}
}

func (c *Context) Indexfv(pC *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexfv_args
		glWrapHandlerArgs.c = (*C.GLfloat)(unsafe.Pointer(pC))

		c.push(C.gl_wrap_batch_func{
			jump_index: 91,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexfv(c.c, (*C.GLfloat)(unsafe.Pointer(pC)))
	}
}

func (c *Context) Indexi(pC int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexi_args
		glWrapHandlerArgs.c = C.GLint(pC)

		c.push(C.gl_wrap_batch_func{
			jump_index: 92,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexi(c.c, C.GLint(pC))
	}
}

func (c *Context) Indexiv(pC *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexiv_args
		glWrapHandlerArgs.c = (*C.GLint)(unsafe.Pointer(pC))

		c.push(C.gl_wrap_batch_func{
			jump_index: 93,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexiv(c.c, (*C.GLint)(unsafe.Pointer(pC)))
	}
}

func (c *Context) Indexs(pC int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexs_args
		glWrapHandlerArgs.c = C.GLshort(pC)

		c.push(C.gl_wrap_batch_func{
			jump_index: 94,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexs(c.c, C.GLshort(pC))
	}
}

func (c *Context) Indexsv(pC *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexsv_args
		glWrapHandlerArgs.c = (*C.GLshort)(unsafe.Pointer(pC))

		c.push(C.gl_wrap_batch_func{
			jump_index: 95,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexsv(c.c, (*C.GLshort)(unsafe.Pointer(pC)))
	}
}

func (c *Context) Normal3b(nx byte, ny byte, nz byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3b_args
		glWrapHandlerArgs.nx = C.GLbyte(nx)
		glWrapHandlerArgs.ny = C.GLbyte(ny)
		glWrapHandlerArgs.nz = C.GLbyte(nz)

		c.push(C.gl_wrap_batch_func{
			jump_index: 96,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3b(c.c, C.GLbyte(nx), C.GLbyte(ny), C.GLbyte(nz))
	}
}

func (c *Context) Normal3bv(v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3bv_args
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 97,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3bv(c.c, (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) Normal3d(nx float64, ny float64, nz float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3d_args
		glWrapHandlerArgs.nx = C.GLdouble(nx)
		glWrapHandlerArgs.ny = C.GLdouble(ny)
		glWrapHandlerArgs.nz = C.GLdouble(nz)

		c.push(C.gl_wrap_batch_func{
			jump_index: 98,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3d(c.c, C.GLdouble(nx), C.GLdouble(ny), C.GLdouble(nz))
	}
}

func (c *Context) Normal3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 99,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) Normal3f(nx float32, ny float32, nz float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3f_args
		glWrapHandlerArgs.nx = C.GLfloat(nx)
		glWrapHandlerArgs.ny = C.GLfloat(ny)
		glWrapHandlerArgs.nz = C.GLfloat(nz)

		c.push(C.gl_wrap_batch_func{
			jump_index: 100,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3f(c.c, C.GLfloat(nx), C.GLfloat(ny), C.GLfloat(nz))
	}
}

func (c *Context) Normal3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 101,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) Normal3i(nx int32, ny int32, nz int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3i_args
		glWrapHandlerArgs.nx = C.GLint(nx)
		glWrapHandlerArgs.ny = C.GLint(ny)
		glWrapHandlerArgs.nz = C.GLint(nz)

		c.push(C.gl_wrap_batch_func{
			jump_index: 102,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3i(c.c, C.GLint(nx), C.GLint(ny), C.GLint(nz))
	}
}

func (c *Context) Normal3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 103,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Normal3s(nx int16, ny int16, nz int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3s_args
		glWrapHandlerArgs.nx = C.GLshort(nx)
		glWrapHandlerArgs.ny = C.GLshort(ny)
		glWrapHandlerArgs.nz = C.GLshort(nz)

		c.push(C.gl_wrap_batch_func{
			jump_index: 104,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3s(c.c, C.GLshort(nx), C.GLshort(ny), C.GLshort(nz))
	}
}

func (c *Context) Normal3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormal3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 105,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormal3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos2d(x float64, y float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 106,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2d(c.c, C.GLdouble(x), C.GLdouble(y))
	}
}

func (c *Context) RasterPos2dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 107,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos2f(x float32, y float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 108,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2f(c.c, C.GLfloat(x), C.GLfloat(y))
	}
}

func (c *Context) RasterPos2fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 109,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos2i(x int32, y int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 110,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2i(c.c, C.GLint(x), C.GLint(y))
	}
}

func (c *Context) RasterPos2iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 111,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos2s(x int16, y int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 112,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2s(c.c, C.GLshort(x), C.GLshort(y))
	}
}

func (c *Context) RasterPos2sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos2sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 113,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos2sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos3d(x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 114,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3d(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) RasterPos3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 115,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos3f(x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 116,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3f(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) RasterPos3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 117,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos3i(x int32, y int32, z int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 118,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3i(c.c, C.GLint(x), C.GLint(y), C.GLint(z))
	}
}

func (c *Context) RasterPos3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 119,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos3s(x int16, y int16, z int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 120,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3s(c.c, C.GLshort(x), C.GLshort(y), C.GLshort(z))
	}
}

func (c *Context) RasterPos3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 121,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos4d(x float64, y float64, z float64, w float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)
		glWrapHandlerArgs.w = C.GLdouble(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 122,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4d(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z), C.GLdouble(w))
	}
}

func (c *Context) RasterPos4dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 123,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos4f(x float32, y float32, z float32, w float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)
		glWrapHandlerArgs.w = C.GLfloat(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 124,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4f(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z), C.GLfloat(w))
	}
}

func (c *Context) RasterPos4fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 125,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos4i(x int32, y int32, z int32, w int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)
		glWrapHandlerArgs.w = C.GLint(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 126,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4i(c.c, C.GLint(x), C.GLint(y), C.GLint(z), C.GLint(w))
	}
}

func (c *Context) RasterPos4iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 127,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) RasterPos4s(x int16, y int16, z int16, w int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)
		glWrapHandlerArgs.w = C.GLshort(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 128,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4s(c.c, C.GLshort(x), C.GLshort(y), C.GLshort(z), C.GLshort(w))
	}
}

func (c *Context) RasterPos4sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRasterPos4sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 129,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRasterPos4sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Rectd(x1 float64, y1 float64, x2 float64, y2 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRectd_args
		glWrapHandlerArgs.x1 = C.GLdouble(x1)
		glWrapHandlerArgs.y1 = C.GLdouble(y1)
		glWrapHandlerArgs.x2 = C.GLdouble(x2)
		glWrapHandlerArgs.y2 = C.GLdouble(y2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 130,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRectd(c.c, C.GLdouble(x1), C.GLdouble(y1), C.GLdouble(x2), C.GLdouble(y2))
	}
}

func (c *Context) Rectdv(v1 *float64, v2 *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRectdv_args
		glWrapHandlerArgs.v1 = (*C.GLdouble)(unsafe.Pointer(v1))
		glWrapHandlerArgs.v2 = (*C.GLdouble)(unsafe.Pointer(v2))

		c.push(C.gl_wrap_batch_func{
			jump_index: 131,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRectdv(c.c, (*C.GLdouble)(unsafe.Pointer(v1)), (*C.GLdouble)(unsafe.Pointer(v2)))
	}
}

func (c *Context) Rectf(x1 float32, y1 float32, x2 float32, y2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRectf_args
		glWrapHandlerArgs.x1 = C.GLfloat(x1)
		glWrapHandlerArgs.y1 = C.GLfloat(y1)
		glWrapHandlerArgs.x2 = C.GLfloat(x2)
		glWrapHandlerArgs.y2 = C.GLfloat(y2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 132,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRectf(c.c, C.GLfloat(x1), C.GLfloat(y1), C.GLfloat(x2), C.GLfloat(y2))
	}
}

func (c *Context) Rectfv(v1 *float32, v2 *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRectfv_args
		glWrapHandlerArgs.v1 = (*C.GLfloat)(unsafe.Pointer(v1))
		glWrapHandlerArgs.v2 = (*C.GLfloat)(unsafe.Pointer(v2))

		c.push(C.gl_wrap_batch_func{
			jump_index: 133,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRectfv(c.c, (*C.GLfloat)(unsafe.Pointer(v1)), (*C.GLfloat)(unsafe.Pointer(v2)))
	}
}

func (c *Context) Recti(x1 int32, y1 int32, x2 int32, y2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRecti_args
		glWrapHandlerArgs.x1 = C.GLint(x1)
		glWrapHandlerArgs.y1 = C.GLint(y1)
		glWrapHandlerArgs.x2 = C.GLint(x2)
		glWrapHandlerArgs.y2 = C.GLint(y2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 134,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRecti(c.c, C.GLint(x1), C.GLint(y1), C.GLint(x2), C.GLint(y2))
	}
}

func (c *Context) Rectiv(v1 *int32, v2 *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRectiv_args
		glWrapHandlerArgs.v1 = (*C.GLint)(unsafe.Pointer(v1))
		glWrapHandlerArgs.v2 = (*C.GLint)(unsafe.Pointer(v2))

		c.push(C.gl_wrap_batch_func{
			jump_index: 135,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRectiv(c.c, (*C.GLint)(unsafe.Pointer(v1)), (*C.GLint)(unsafe.Pointer(v2)))
	}
}

func (c *Context) Rects(x1 int16, y1 int16, x2 int16, y2 int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRects_args
		glWrapHandlerArgs.x1 = C.GLshort(x1)
		glWrapHandlerArgs.y1 = C.GLshort(y1)
		glWrapHandlerArgs.x2 = C.GLshort(x2)
		glWrapHandlerArgs.y2 = C.GLshort(y2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 136,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRects(c.c, C.GLshort(x1), C.GLshort(y1), C.GLshort(x2), C.GLshort(y2))
	}
}

func (c *Context) Rectsv(v1 *int16, v2 *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRectsv_args
		glWrapHandlerArgs.v1 = (*C.GLshort)(unsafe.Pointer(v1))
		glWrapHandlerArgs.v2 = (*C.GLshort)(unsafe.Pointer(v2))

		c.push(C.gl_wrap_batch_func{
			jump_index: 137,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRectsv(c.c, (*C.GLshort)(unsafe.Pointer(v1)), (*C.GLshort)(unsafe.Pointer(v2)))
	}
}

func (c *Context) TexCoord1d(s float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1d_args
		glWrapHandlerArgs.s = C.GLdouble(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 138,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1d(c.c, C.GLdouble(s))
	}
}

func (c *Context) TexCoord1dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 139,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord1f(s float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1f_args
		glWrapHandlerArgs.s = C.GLfloat(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 140,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1f(c.c, C.GLfloat(s))
	}
}

func (c *Context) TexCoord1fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 141,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord1i(s int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1i_args
		glWrapHandlerArgs.s = C.GLint(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 142,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1i(c.c, C.GLint(s))
	}
}

func (c *Context) TexCoord1iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 143,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord1s(s int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1s_args
		glWrapHandlerArgs.s = C.GLshort(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 144,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1s(c.c, C.GLshort(s))
	}
}

func (c *Context) TexCoord1sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord1sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 145,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord1sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord2d(s float64, t float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2d_args
		glWrapHandlerArgs.s = C.GLdouble(s)
		glWrapHandlerArgs.t = C.GLdouble(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 146,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2d(c.c, C.GLdouble(s), C.GLdouble(t))
	}
}

func (c *Context) TexCoord2dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 147,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord2f(s float32, t float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2f_args
		glWrapHandlerArgs.s = C.GLfloat(s)
		glWrapHandlerArgs.t = C.GLfloat(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 148,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2f(c.c, C.GLfloat(s), C.GLfloat(t))
	}
}

func (c *Context) TexCoord2fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 149,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord2i(s int32, t int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2i_args
		glWrapHandlerArgs.s = C.GLint(s)
		glWrapHandlerArgs.t = C.GLint(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 150,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2i(c.c, C.GLint(s), C.GLint(t))
	}
}

func (c *Context) TexCoord2iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 151,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord2s(s int16, t int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2s_args
		glWrapHandlerArgs.s = C.GLshort(s)
		glWrapHandlerArgs.t = C.GLshort(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 152,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2s(c.c, C.GLshort(s), C.GLshort(t))
	}
}

func (c *Context) TexCoord2sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord2sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 153,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord2sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord3d(s float64, t float64, r float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3d_args
		glWrapHandlerArgs.s = C.GLdouble(s)
		glWrapHandlerArgs.t = C.GLdouble(t)
		glWrapHandlerArgs.r = C.GLdouble(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 154,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3d(c.c, C.GLdouble(s), C.GLdouble(t), C.GLdouble(r))
	}
}

func (c *Context) TexCoord3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 155,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord3f(s float32, t float32, r float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3f_args
		glWrapHandlerArgs.s = C.GLfloat(s)
		glWrapHandlerArgs.t = C.GLfloat(t)
		glWrapHandlerArgs.r = C.GLfloat(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 156,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3f(c.c, C.GLfloat(s), C.GLfloat(t), C.GLfloat(r))
	}
}

func (c *Context) TexCoord3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 157,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord3i(s int32, t int32, r int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3i_args
		glWrapHandlerArgs.s = C.GLint(s)
		glWrapHandlerArgs.t = C.GLint(t)
		glWrapHandlerArgs.r = C.GLint(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 158,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3i(c.c, C.GLint(s), C.GLint(t), C.GLint(r))
	}
}

func (c *Context) TexCoord3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 159,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord3s(s int16, t int16, r int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3s_args
		glWrapHandlerArgs.s = C.GLshort(s)
		glWrapHandlerArgs.t = C.GLshort(t)
		glWrapHandlerArgs.r = C.GLshort(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 160,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3s(c.c, C.GLshort(s), C.GLshort(t), C.GLshort(r))
	}
}

func (c *Context) TexCoord3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 161,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord4d(s float64, t float64, r float64, q float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4d_args
		glWrapHandlerArgs.s = C.GLdouble(s)
		glWrapHandlerArgs.t = C.GLdouble(t)
		glWrapHandlerArgs.r = C.GLdouble(r)
		glWrapHandlerArgs.q = C.GLdouble(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 162,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4d(c.c, C.GLdouble(s), C.GLdouble(t), C.GLdouble(r), C.GLdouble(q))
	}
}

func (c *Context) TexCoord4dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 163,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord4f(s float32, t float32, r float32, q float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4f_args
		glWrapHandlerArgs.s = C.GLfloat(s)
		glWrapHandlerArgs.t = C.GLfloat(t)
		glWrapHandlerArgs.r = C.GLfloat(r)
		glWrapHandlerArgs.q = C.GLfloat(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 164,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4f(c.c, C.GLfloat(s), C.GLfloat(t), C.GLfloat(r), C.GLfloat(q))
	}
}

func (c *Context) TexCoord4fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 165,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord4i(s int32, t int32, r int32, q int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4i_args
		glWrapHandlerArgs.s = C.GLint(s)
		glWrapHandlerArgs.t = C.GLint(t)
		glWrapHandlerArgs.r = C.GLint(r)
		glWrapHandlerArgs.q = C.GLint(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 166,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4i(c.c, C.GLint(s), C.GLint(t), C.GLint(r), C.GLint(q))
	}
}

func (c *Context) TexCoord4iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 167,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) TexCoord4s(s int16, t int16, r int16, q int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4s_args
		glWrapHandlerArgs.s = C.GLshort(s)
		glWrapHandlerArgs.t = C.GLshort(t)
		glWrapHandlerArgs.r = C.GLshort(r)
		glWrapHandlerArgs.q = C.GLshort(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 168,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4s(c.c, C.GLshort(s), C.GLshort(t), C.GLshort(r), C.GLshort(q))
	}
}

func (c *Context) TexCoord4sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoord4sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 169,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoord4sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex2d(x float64, y float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 170,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2d(c.c, C.GLdouble(x), C.GLdouble(y))
	}
}

func (c *Context) Vertex2dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 171,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex2f(x float32, y float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 172,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2f(c.c, C.GLfloat(x), C.GLfloat(y))
	}
}

func (c *Context) Vertex2fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 173,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex2i(x int32, y int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 174,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2i(c.c, C.GLint(x), C.GLint(y))
	}
}

func (c *Context) Vertex2iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 175,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex2s(x int16, y int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 176,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2s(c.c, C.GLshort(x), C.GLshort(y))
	}
}

func (c *Context) Vertex2sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex2sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 177,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex2sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex3d(x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 178,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3d(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) Vertex3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 179,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex3f(x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 180,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3f(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) Vertex3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 181,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex3i(x int32, y int32, z int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 182,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3i(c.c, C.GLint(x), C.GLint(y), C.GLint(z))
	}
}

func (c *Context) Vertex3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 183,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex3s(x int16, y int16, z int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 184,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3s(c.c, C.GLshort(x), C.GLshort(y), C.GLshort(z))
	}
}

func (c *Context) Vertex3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 185,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex4d(x float64, y float64, z float64, w float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)
		glWrapHandlerArgs.w = C.GLdouble(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 186,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4d(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z), C.GLdouble(w))
	}
}

func (c *Context) Vertex4dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 187,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex4f(x float32, y float32, z float32, w float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)
		glWrapHandlerArgs.w = C.GLfloat(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 188,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4f(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z), C.GLfloat(w))
	}
}

func (c *Context) Vertex4fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 189,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex4i(x int32, y int32, z int32, w int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)
		glWrapHandlerArgs.w = C.GLint(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 190,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4i(c.c, C.GLint(x), C.GLint(y), C.GLint(z), C.GLint(w))
	}
}

func (c *Context) Vertex4iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 191,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) Vertex4s(x int16, y int16, z int16, w int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)
		glWrapHandlerArgs.w = C.GLshort(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 192,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4s(c.c, C.GLshort(x), C.GLshort(y), C.GLshort(z), C.GLshort(w))
	}
}

func (c *Context) Vertex4sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertex4sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 193,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertex4sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) ClipPlane(plane int32, equation *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClipPlane_args
		glWrapHandlerArgs.plane = C.GLenum(plane)
		glWrapHandlerArgs.equation = (*C.GLdouble)(unsafe.Pointer(equation))

		c.push(C.gl_wrap_batch_func{
			jump_index: 194,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClipPlane(c.c, C.GLenum(plane), (*C.GLdouble)(unsafe.Pointer(equation)))
	}
}

func (c *Context) ColorMaterial(face int32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorMaterial_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 195,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorMaterial(c.c, C.GLenum(face), C.GLenum(mode))
	}
}

func (c *Context) Fogf(pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogf_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 196,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogf(c.c, C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) Fogfv(pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogfv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 197,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogfv(c.c, C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) Fogi(pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogi_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 198,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogi(c.c, C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) Fogiv(pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogiv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 199,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogiv(c.c, C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) Lightf(light int32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightf_args
		glWrapHandlerArgs.light = C.GLenum(light)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 200,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightf(c.c, C.GLenum(light), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) Lightfv(light int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightfv_args
		glWrapHandlerArgs.light = C.GLenum(light)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 201,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightfv(c.c, C.GLenum(light), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) Lighti(light int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLighti_args
		glWrapHandlerArgs.light = C.GLenum(light)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 202,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLighti(c.c, C.GLenum(light), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) Lightiv(light int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightiv_args
		glWrapHandlerArgs.light = C.GLenum(light)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 203,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightiv(c.c, C.GLenum(light), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) LightModelf(pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightModelf_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 204,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightModelf(c.c, C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) LightModelfv(pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightModelfv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 205,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightModelfv(c.c, C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) LightModeli(pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightModeli_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 206,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightModeli(c.c, C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) LightModeliv(pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLightModeliv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 207,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLightModeliv(c.c, C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) LineStipple(factor int32, pattern uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLineStipple_args
		glWrapHandlerArgs.factor = C.GLint(factor)
		glWrapHandlerArgs.pattern = C.GLushort(pattern)

		c.push(C.gl_wrap_batch_func{
			jump_index: 208,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLineStipple(c.c, C.GLint(factor), C.GLushort(pattern))
	}
}

func (c *Context) Materialf(face int32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMaterialf_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 209,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMaterialf(c.c, C.GLenum(face), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) Materialfv(face int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMaterialfv_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 210,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMaterialfv(c.c, C.GLenum(face), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) Materiali(face int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMateriali_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 211,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMateriali(c.c, C.GLenum(face), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) Materialiv(face int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMaterialiv_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 212,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMaterialiv(c.c, C.GLenum(face), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) PolygonStipple(mask *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPolygonStipple_args
		glWrapHandlerArgs.mask = (*C.GLubyte)(unsafe.Pointer(mask))

		c.push(C.gl_wrap_batch_func{
			jump_index: 213,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPolygonStipple(c.c, (*C.GLubyte)(unsafe.Pointer(mask)))
	}
}

func (c *Context) ShadeModel(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glShadeModel_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 214,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glShadeModel(c.c, C.GLenum(mode))
	}
}

func (c *Context) TexEnvf(target int32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexEnvf_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 215,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexEnvf(c.c, C.GLenum(target), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) TexEnvfv(target int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexEnvfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 216,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexEnvfv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexEnvi(target int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexEnvi_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 217,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexEnvi(c.c, C.GLenum(target), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) TexEnviv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexEnviv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 218,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexEnviv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexGend(coord int32, pname int32, param float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexGend_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLdouble(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 219,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexGend(c.c, C.GLenum(coord), C.GLenum(pname), C.GLdouble(param))
	}
}

func (c *Context) TexGendv(coord int32, pname int32, params *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexGendv_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLdouble)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 220,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexGendv(c.c, C.GLenum(coord), C.GLenum(pname), (*C.GLdouble)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexGenf(coord int32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexGenf_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 221,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexGenf(c.c, C.GLenum(coord), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) TexGenfv(coord int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexGenfv_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 222,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexGenfv(c.c, C.GLenum(coord), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexGeni(coord int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexGeni_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 223,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexGeni(c.c, C.GLenum(coord), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) TexGeniv(coord int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexGeniv_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 224,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexGeniv(c.c, C.GLenum(coord), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) FeedbackBuffer(size uint32, pType int32, buffer *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFeedbackBuffer_args
		glWrapHandlerArgs.size = C.GLsizei(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.buffer = (*C.GLfloat)(unsafe.Pointer(buffer))

		c.push(C.gl_wrap_batch_func{
			jump_index: 225,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFeedbackBuffer(c.c, C.GLsizei(size), C.GLenum(pType), (*C.GLfloat)(unsafe.Pointer(buffer)))
	}
}

func (c *Context) SelectBuffer(size uint32, buffer *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSelectBuffer_args
		glWrapHandlerArgs.size = C.GLsizei(size)
		glWrapHandlerArgs.buffer = (*C.GLuint)(unsafe.Pointer(buffer))

		c.push(C.gl_wrap_batch_func{
			jump_index: 226,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSelectBuffer(c.c, C.GLsizei(size), (*C.GLuint)(unsafe.Pointer(buffer)))
	}
}

func (c *Context) InitNames() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInitNames_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 227,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInitNames(c.c)
	}
}

func (c *Context) LoadName(name uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLoadName_args
		glWrapHandlerArgs.name = C.GLuint(name)

		c.push(C.gl_wrap_batch_func{
			jump_index: 228,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLoadName(c.c, C.GLuint(name))
	}
}

func (c *Context) PassThrough(token float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPassThrough_args
		glWrapHandlerArgs.token = C.GLfloat(token)

		c.push(C.gl_wrap_batch_func{
			jump_index: 229,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPassThrough(c.c, C.GLfloat(token))
	}
}

func (c *Context) PopName() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPopName_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 230,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPopName(c.c)
	}
}

func (c *Context) PushName(name uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPushName_args
		glWrapHandlerArgs.name = C.GLuint(name)

		c.push(C.gl_wrap_batch_func{
			jump_index: 231,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPushName(c.c, C.GLuint(name))
	}
}

func (c *Context) ClearAccum(red float32, green float32, blue float32, alpha float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearAccum_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)
		glWrapHandlerArgs.alpha = C.GLfloat(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 232,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearAccum(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue), C.GLfloat(alpha))
	}
}

func (c *Context) ClearIndex(pC float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearIndex_args
		glWrapHandlerArgs.c = C.GLfloat(pC)

		c.push(C.gl_wrap_batch_func{
			jump_index: 233,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearIndex(c.c, C.GLfloat(pC))
	}
}

func (c *Context) IndexMask(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexMask_args
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 234,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexMask(c.c, C.GLuint(mask))
	}
}

func (c *Context) Accum(op int32, value float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glAccum_args
		glWrapHandlerArgs.op = C.GLenum(op)
		glWrapHandlerArgs.value = C.GLfloat(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 235,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glAccum(c.c, C.GLenum(op), C.GLfloat(value))
	}
}

func (c *Context) PopAttrib() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPopAttrib_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 236,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPopAttrib(c.c)
	}
}

func (c *Context) PushAttrib(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPushAttrib_args
		glWrapHandlerArgs.mask = C.GLbitfield(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 237,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPushAttrib(c.c, C.GLbitfield(mask))
	}
}

func (c *Context) Map1d(target int32, u1 float64, u2 float64, stride int32, order int32, points *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMap1d_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.u1 = C.GLdouble(u1)
		glWrapHandlerArgs.u2 = C.GLdouble(u2)
		glWrapHandlerArgs.stride = C.GLint(stride)
		glWrapHandlerArgs.order = C.GLint(order)
		glWrapHandlerArgs.points = (*C.GLdouble)(unsafe.Pointer(points))

		c.push(C.gl_wrap_batch_func{
			jump_index: 238,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMap1d(c.c, C.GLenum(target), C.GLdouble(u1), C.GLdouble(u2), C.GLint(stride), C.GLint(order), (*C.GLdouble)(unsafe.Pointer(points)))
	}
}

func (c *Context) Map1f(target int32, u1 float32, u2 float32, stride int32, order int32, points *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMap1f_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.u1 = C.GLfloat(u1)
		glWrapHandlerArgs.u2 = C.GLfloat(u2)
		glWrapHandlerArgs.stride = C.GLint(stride)
		glWrapHandlerArgs.order = C.GLint(order)
		glWrapHandlerArgs.points = (*C.GLfloat)(unsafe.Pointer(points))

		c.push(C.gl_wrap_batch_func{
			jump_index: 239,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMap1f(c.c, C.GLenum(target), C.GLfloat(u1), C.GLfloat(u2), C.GLint(stride), C.GLint(order), (*C.GLfloat)(unsafe.Pointer(points)))
	}
}

func (c *Context) Map2d(target int32, u1 float64, u2 float64, ustride int32, uorder int32, v1 float64, v2 float64, vstride int32, vorder int32, points *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMap2d_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.u1 = C.GLdouble(u1)
		glWrapHandlerArgs.u2 = C.GLdouble(u2)
		glWrapHandlerArgs.ustride = C.GLint(ustride)
		glWrapHandlerArgs.uorder = C.GLint(uorder)
		glWrapHandlerArgs.v1 = C.GLdouble(v1)
		glWrapHandlerArgs.v2 = C.GLdouble(v2)
		glWrapHandlerArgs.vstride = C.GLint(vstride)
		glWrapHandlerArgs.vorder = C.GLint(vorder)
		glWrapHandlerArgs.points = (*C.GLdouble)(unsafe.Pointer(points))

		c.push(C.gl_wrap_batch_func{
			jump_index: 240,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMap2d(c.c, C.GLenum(target), C.GLdouble(u1), C.GLdouble(u2), C.GLint(ustride), C.GLint(uorder), C.GLdouble(v1), C.GLdouble(v2), C.GLint(vstride), C.GLint(vorder), (*C.GLdouble)(unsafe.Pointer(points)))
	}
}

func (c *Context) Map2f(target int32, u1 float32, u2 float32, ustride int32, uorder int32, v1 float32, v2 float32, vstride int32, vorder int32, points *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMap2f_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.u1 = C.GLfloat(u1)
		glWrapHandlerArgs.u2 = C.GLfloat(u2)
		glWrapHandlerArgs.ustride = C.GLint(ustride)
		glWrapHandlerArgs.uorder = C.GLint(uorder)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)
		glWrapHandlerArgs.vstride = C.GLint(vstride)
		glWrapHandlerArgs.vorder = C.GLint(vorder)
		glWrapHandlerArgs.points = (*C.GLfloat)(unsafe.Pointer(points))

		c.push(C.gl_wrap_batch_func{
			jump_index: 241,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMap2f(c.c, C.GLenum(target), C.GLfloat(u1), C.GLfloat(u2), C.GLint(ustride), C.GLint(uorder), C.GLfloat(v1), C.GLfloat(v2), C.GLint(vstride), C.GLint(vorder), (*C.GLfloat)(unsafe.Pointer(points)))
	}
}

func (c *Context) MapGrid1d(un int32, u1 float64, u2 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapGrid1d_args
		glWrapHandlerArgs.un = C.GLint(un)
		glWrapHandlerArgs.u1 = C.GLdouble(u1)
		glWrapHandlerArgs.u2 = C.GLdouble(u2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 242,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapGrid1d(c.c, C.GLint(un), C.GLdouble(u1), C.GLdouble(u2))
	}
}

func (c *Context) MapGrid1f(un int32, u1 float32, u2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapGrid1f_args
		glWrapHandlerArgs.un = C.GLint(un)
		glWrapHandlerArgs.u1 = C.GLfloat(u1)
		glWrapHandlerArgs.u2 = C.GLfloat(u2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 243,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapGrid1f(c.c, C.GLint(un), C.GLfloat(u1), C.GLfloat(u2))
	}
}

func (c *Context) MapGrid2d(un int32, u1 float64, u2 float64, vn int32, v1 float64, v2 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapGrid2d_args
		glWrapHandlerArgs.un = C.GLint(un)
		glWrapHandlerArgs.u1 = C.GLdouble(u1)
		glWrapHandlerArgs.u2 = C.GLdouble(u2)
		glWrapHandlerArgs.vn = C.GLint(vn)
		glWrapHandlerArgs.v1 = C.GLdouble(v1)
		glWrapHandlerArgs.v2 = C.GLdouble(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 244,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapGrid2d(c.c, C.GLint(un), C.GLdouble(u1), C.GLdouble(u2), C.GLint(vn), C.GLdouble(v1), C.GLdouble(v2))
	}
}

func (c *Context) MapGrid2f(un int32, u1 float32, u2 float32, vn int32, v1 float32, v2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapGrid2f_args
		glWrapHandlerArgs.un = C.GLint(un)
		glWrapHandlerArgs.u1 = C.GLfloat(u1)
		glWrapHandlerArgs.u2 = C.GLfloat(u2)
		glWrapHandlerArgs.vn = C.GLint(vn)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 245,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapGrid2f(c.c, C.GLint(un), C.GLfloat(u1), C.GLfloat(u2), C.GLint(vn), C.GLfloat(v1), C.GLfloat(v2))
	}
}

func (c *Context) EvalCoord1d(u float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord1d_args
		glWrapHandlerArgs.u = C.GLdouble(u)

		c.push(C.gl_wrap_batch_func{
			jump_index: 246,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord1d(c.c, C.GLdouble(u))
	}
}

func (c *Context) EvalCoord1dv(u *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord1dv_args
		glWrapHandlerArgs.u = (*C.GLdouble)(unsafe.Pointer(u))

		c.push(C.gl_wrap_batch_func{
			jump_index: 247,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord1dv(c.c, (*C.GLdouble)(unsafe.Pointer(u)))
	}
}

func (c *Context) EvalCoord1f(u float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord1f_args
		glWrapHandlerArgs.u = C.GLfloat(u)

		c.push(C.gl_wrap_batch_func{
			jump_index: 248,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord1f(c.c, C.GLfloat(u))
	}
}

func (c *Context) EvalCoord1fv(u *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord1fv_args
		glWrapHandlerArgs.u = (*C.GLfloat)(unsafe.Pointer(u))

		c.push(C.gl_wrap_batch_func{
			jump_index: 249,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord1fv(c.c, (*C.GLfloat)(unsafe.Pointer(u)))
	}
}

func (c *Context) EvalCoord2d(u float64, v float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord2d_args
		glWrapHandlerArgs.u = C.GLdouble(u)
		glWrapHandlerArgs.v = C.GLdouble(v)

		c.push(C.gl_wrap_batch_func{
			jump_index: 250,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord2d(c.c, C.GLdouble(u), C.GLdouble(v))
	}
}

func (c *Context) EvalCoord2dv(u *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord2dv_args
		glWrapHandlerArgs.u = (*C.GLdouble)(unsafe.Pointer(u))

		c.push(C.gl_wrap_batch_func{
			jump_index: 251,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord2dv(c.c, (*C.GLdouble)(unsafe.Pointer(u)))
	}
}

func (c *Context) EvalCoord2f(u float32, v float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord2f_args
		glWrapHandlerArgs.u = C.GLfloat(u)
		glWrapHandlerArgs.v = C.GLfloat(v)

		c.push(C.gl_wrap_batch_func{
			jump_index: 252,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord2f(c.c, C.GLfloat(u), C.GLfloat(v))
	}
}

func (c *Context) EvalCoord2fv(u *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalCoord2fv_args
		glWrapHandlerArgs.u = (*C.GLfloat)(unsafe.Pointer(u))

		c.push(C.gl_wrap_batch_func{
			jump_index: 253,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalCoord2fv(c.c, (*C.GLfloat)(unsafe.Pointer(u)))
	}
}

func (c *Context) EvalMesh1(mode int32, i1 int32, i2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalMesh1_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.i1 = C.GLint(i1)
		glWrapHandlerArgs.i2 = C.GLint(i2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 254,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalMesh1(c.c, C.GLenum(mode), C.GLint(i1), C.GLint(i2))
	}
}

func (c *Context) EvalPoint1(i int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalPoint1_args
		glWrapHandlerArgs.i = C.GLint(i)

		c.push(C.gl_wrap_batch_func{
			jump_index: 255,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalPoint1(c.c, C.GLint(i))
	}
}

func (c *Context) EvalMesh2(mode int32, i1 int32, i2 int32, j1 int32, j2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalMesh2_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.i1 = C.GLint(i1)
		glWrapHandlerArgs.i2 = C.GLint(i2)
		glWrapHandlerArgs.j1 = C.GLint(j1)
		glWrapHandlerArgs.j2 = C.GLint(j2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 256,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalMesh2(c.c, C.GLenum(mode), C.GLint(i1), C.GLint(i2), C.GLint(j1), C.GLint(j2))
	}
}

func (c *Context) EvalPoint2(i int32, j int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEvalPoint2_args
		glWrapHandlerArgs.i = C.GLint(i)
		glWrapHandlerArgs.j = C.GLint(j)

		c.push(C.gl_wrap_batch_func{
			jump_index: 257,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEvalPoint2(c.c, C.GLint(i), C.GLint(j))
	}
}

func (c *Context) AlphaFunc(pFunc int32, ref float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glAlphaFunc_args
		glWrapHandlerArgs._func = C.GLenum(pFunc)
		glWrapHandlerArgs.ref = C.GLfloat(ref)

		c.push(C.gl_wrap_batch_func{
			jump_index: 258,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glAlphaFunc(c.c, C.GLenum(pFunc), C.GLfloat(ref))
	}
}

func (c *Context) PixelZoom(xfactor float32, yfactor float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelZoom_args
		glWrapHandlerArgs.xfactor = C.GLfloat(xfactor)
		glWrapHandlerArgs.yfactor = C.GLfloat(yfactor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 259,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelZoom(c.c, C.GLfloat(xfactor), C.GLfloat(yfactor))
	}
}

func (c *Context) PixelTransferf(pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelTransferf_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 260,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelTransferf(c.c, C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) PixelTransferi(pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelTransferi_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 261,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelTransferi(c.c, C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) PixelMapfv(pMap int32, mapsize uint32, values *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelMapfv_args
		glWrapHandlerArgs._map = C.GLenum(pMap)
		glWrapHandlerArgs.mapsize = C.GLsizei(mapsize)
		glWrapHandlerArgs.values = (*C.GLfloat)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 262,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelMapfv(c.c, C.GLenum(pMap), C.GLsizei(mapsize), (*C.GLfloat)(unsafe.Pointer(values)))
	}
}

func (c *Context) PixelMapuiv(pMap int32, mapsize uint32, values *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelMapuiv_args
		glWrapHandlerArgs._map = C.GLenum(pMap)
		glWrapHandlerArgs.mapsize = C.GLsizei(mapsize)
		glWrapHandlerArgs.values = (*C.GLuint)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 263,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelMapuiv(c.c, C.GLenum(pMap), C.GLsizei(mapsize), (*C.GLuint)(unsafe.Pointer(values)))
	}
}

func (c *Context) PixelMapusv(pMap int32, mapsize uint32, values *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPixelMapusv_args
		glWrapHandlerArgs._map = C.GLenum(pMap)
		glWrapHandlerArgs.mapsize = C.GLsizei(mapsize)
		glWrapHandlerArgs.values = (*C.GLushort)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 264,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPixelMapusv(c.c, C.GLenum(pMap), C.GLsizei(mapsize), (*C.GLushort)(unsafe.Pointer(values)))
	}
}

func (c *Context) CopyPixels(x int32, y int32, width uint32, height uint32, pType int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyPixels_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs._type = C.GLenum(pType)

		c.push(C.gl_wrap_batch_func{
			jump_index: 265,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyPixels(c.c, C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height), C.GLenum(pType))
	}
}

func (c *Context) DrawPixels(width uint32, height uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawPixels_args
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 266,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawPixels(c.c, C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) GetClipPlane(plane int32, equation *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetClipPlane_args
		glWrapHandlerArgs.plane = C.GLenum(plane)
		glWrapHandlerArgs.equation = (*C.GLdouble)(unsafe.Pointer(equation))

		c.push(C.gl_wrap_batch_func{
			jump_index: 267,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetClipPlane(c.c, C.GLenum(plane), (*C.GLdouble)(unsafe.Pointer(equation)))
	}
}

func (c *Context) GetLightfv(light int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetLightfv_args
		glWrapHandlerArgs.light = C.GLenum(light)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 268,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetLightfv(c.c, C.GLenum(light), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetLightiv(light int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetLightiv_args
		glWrapHandlerArgs.light = C.GLenum(light)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 269,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetLightiv(c.c, C.GLenum(light), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetMapdv(target int32, query int32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMapdv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.query = C.GLenum(query)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 270,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMapdv(c.c, C.GLenum(target), C.GLenum(query), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) GetMapfv(target int32, query int32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMapfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.query = C.GLenum(query)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 271,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMapfv(c.c, C.GLenum(target), C.GLenum(query), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) GetMapiv(target int32, query int32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMapiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.query = C.GLenum(query)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 272,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMapiv(c.c, C.GLenum(target), C.GLenum(query), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) GetMaterialfv(face int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMaterialfv_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 273,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMaterialfv(c.c, C.GLenum(face), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetMaterialiv(face int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMaterialiv_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 274,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMaterialiv(c.c, C.GLenum(face), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetPixelMapfv(pMap int32, values *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetPixelMapfv_args
		glWrapHandlerArgs._map = C.GLenum(pMap)
		glWrapHandlerArgs.values = (*C.GLfloat)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 275,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetPixelMapfv(c.c, C.GLenum(pMap), (*C.GLfloat)(unsafe.Pointer(values)))
	}
}

func (c *Context) GetPixelMapuiv(pMap int32, values *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetPixelMapuiv_args
		glWrapHandlerArgs._map = C.GLenum(pMap)
		glWrapHandlerArgs.values = (*C.GLuint)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 276,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetPixelMapuiv(c.c, C.GLenum(pMap), (*C.GLuint)(unsafe.Pointer(values)))
	}
}

func (c *Context) GetPixelMapusv(pMap int32, values *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetPixelMapusv_args
		glWrapHandlerArgs._map = C.GLenum(pMap)
		glWrapHandlerArgs.values = (*C.GLushort)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 277,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetPixelMapusv(c.c, C.GLenum(pMap), (*C.GLushort)(unsafe.Pointer(values)))
	}
}

func (c *Context) GetPolygonStipple(mask *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetPolygonStipple_args
		glWrapHandlerArgs.mask = (*C.GLubyte)(unsafe.Pointer(mask))

		c.push(C.gl_wrap_batch_func{
			jump_index: 278,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetPolygonStipple(c.c, (*C.GLubyte)(unsafe.Pointer(mask)))
	}
}

func (c *Context) GetTexEnvfv(target int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexEnvfv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 279,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexEnvfv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexEnviv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexEnviv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 280,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexEnviv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexGendv(coord int32, pname int32, params *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexGendv_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLdouble)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 281,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexGendv(c.c, C.GLenum(coord), C.GLenum(pname), (*C.GLdouble)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexGenfv(coord int32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexGenfv_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 282,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexGenfv(c.c, C.GLenum(coord), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexGeniv(coord int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexGeniv_args
		glWrapHandlerArgs.coord = C.GLenum(coord)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 283,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexGeniv(c.c, C.GLenum(coord), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) Frustum(left float64, right float64, bottom float64, top float64, zNear float64, zFar float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFrustum_args
		glWrapHandlerArgs.left = C.GLdouble(left)
		glWrapHandlerArgs.right = C.GLdouble(right)
		glWrapHandlerArgs.bottom = C.GLdouble(bottom)
		glWrapHandlerArgs.top = C.GLdouble(top)
		glWrapHandlerArgs.zNear = C.GLdouble(zNear)
		glWrapHandlerArgs.zFar = C.GLdouble(zFar)

		c.push(C.gl_wrap_batch_func{
			jump_index: 284,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFrustum(c.c, C.GLdouble(left), C.GLdouble(right), C.GLdouble(bottom), C.GLdouble(top), C.GLdouble(zNear), C.GLdouble(zFar))
	}
}

func (c *Context) LoadIdentity() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLoadIdentity_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 285,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLoadIdentity(c.c)
	}
}

func (c *Context) LoadMatrixf(m *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLoadMatrixf_args
		glWrapHandlerArgs.m = (*C.GLfloat)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 286,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLoadMatrixf(c.c, (*C.GLfloat)(unsafe.Pointer(m)))
	}
}

func (c *Context) LoadMatrixd(m *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLoadMatrixd_args
		glWrapHandlerArgs.m = (*C.GLdouble)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 287,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLoadMatrixd(c.c, (*C.GLdouble)(unsafe.Pointer(m)))
	}
}

func (c *Context) MatrixMode(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMatrixMode_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 288,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMatrixMode(c.c, C.GLenum(mode))
	}
}

func (c *Context) MultMatrixf(m *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultMatrixf_args
		glWrapHandlerArgs.m = (*C.GLfloat)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 289,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultMatrixf(c.c, (*C.GLfloat)(unsafe.Pointer(m)))
	}
}

func (c *Context) MultMatrixd(m *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultMatrixd_args
		glWrapHandlerArgs.m = (*C.GLdouble)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 290,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultMatrixd(c.c, (*C.GLdouble)(unsafe.Pointer(m)))
	}
}

func (c *Context) Ortho(left float64, right float64, bottom float64, top float64, zNear float64, zFar float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glOrtho_args
		glWrapHandlerArgs.left = C.GLdouble(left)
		glWrapHandlerArgs.right = C.GLdouble(right)
		glWrapHandlerArgs.bottom = C.GLdouble(bottom)
		glWrapHandlerArgs.top = C.GLdouble(top)
		glWrapHandlerArgs.zNear = C.GLdouble(zNear)
		glWrapHandlerArgs.zFar = C.GLdouble(zFar)

		c.push(C.gl_wrap_batch_func{
			jump_index: 291,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glOrtho(c.c, C.GLdouble(left), C.GLdouble(right), C.GLdouble(bottom), C.GLdouble(top), C.GLdouble(zNear), C.GLdouble(zFar))
	}
}

func (c *Context) PopMatrix() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPopMatrix_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 292,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPopMatrix(c.c)
	}
}

func (c *Context) PushMatrix() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPushMatrix_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 293,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPushMatrix(c.c)
	}
}

func (c *Context) Rotated(angle float64, x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRotated_args
		glWrapHandlerArgs.angle = C.GLdouble(angle)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 294,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRotated(c.c, C.GLdouble(angle), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) Rotatef(angle float32, x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRotatef_args
		glWrapHandlerArgs.angle = C.GLfloat(angle)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 295,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRotatef(c.c, C.GLfloat(angle), C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) Scaled(x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScaled_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 296,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScaled(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) Scalef(x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScalef_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 297,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScalef(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) Translated(x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTranslated_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 298,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTranslated(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) Translatef(x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTranslatef_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 299,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTranslatef(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) DrawArrays(mode int32, first int32, count uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArrays_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.first = C.GLint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)

		c.push(C.gl_wrap_batch_func{
			jump_index: 300,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArrays(c.c, C.GLenum(mode), C.GLint(first), C.GLsizei(count))
	}
}

func (c *Context) DrawElements(mode int32, count uint32, pType int32, indices unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElements_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices

		c.push(C.gl_wrap_batch_func{
			jump_index: 301,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElements(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices)
	}
}

func (c *Context) GetPointerv(pname int32, params *unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetPointerv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = params

		c.push(C.gl_wrap_batch_func{
			jump_index: 302,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetPointerv(c.c, C.GLenum(pname), params)
	}
}

func (c *Context) PolygonOffset(factor float32, units float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPolygonOffset_args
		glWrapHandlerArgs.factor = C.GLfloat(factor)
		glWrapHandlerArgs.units = C.GLfloat(units)

		c.push(C.gl_wrap_batch_func{
			jump_index: 303,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPolygonOffset(c.c, C.GLfloat(factor), C.GLfloat(units))
	}
}

func (c *Context) CopyTexImage1D(target int32, level int32, internalformat int32, x int32, y int32, width uint32, border int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexImage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.border = C.GLint(border)

		c.push(C.gl_wrap_batch_func{
			jump_index: 304,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexImage1D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLint(border))
	}
}

func (c *Context) CopyTexImage2D(target int32, level int32, internalformat int32, x int32, y int32, width uint32, height uint32, border int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.border = C.GLint(border)

		c.push(C.gl_wrap_batch_func{
			jump_index: 305,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height), C.GLint(border))
	}
}

func (c *Context) CopyTexSubImage1D(target int32, level int32, xoffset int32, x int32, y int32, width uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexSubImage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)

		c.push(C.gl_wrap_batch_func{
			jump_index: 306,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexSubImage1D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(x), C.GLint(y), C.GLsizei(width))
	}
}

func (c *Context) CopyTexSubImage2D(target int32, level int32, xoffset int32, yoffset int32, x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexSubImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 307,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexSubImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) TexSubImage1D(target int32, level int32, xoffset int32, width uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexSubImage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 308,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexSubImage1D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLsizei(width), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) TexSubImage2D(target int32, level int32, xoffset int32, yoffset int32, width uint32, height uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexSubImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 309,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexSubImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) BindTexture(target int32, texture uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindTexture_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.texture = C.GLuint(texture)

		c.push(C.gl_wrap_batch_func{
			jump_index: 310,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindTexture(c.c, C.GLenum(target), C.GLuint(texture))
	}
}

func (c *Context) DeleteTextures(n uint32, textures *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteTextures_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))

		c.push(C.gl_wrap_batch_func{
			jump_index: 311,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteTextures(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(textures)))
	}
}

func (c *Context) GenTextures(n uint32, textures *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenTextures_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))

		c.push(C.gl_wrap_batch_func{
			jump_index: 312,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenTextures(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(textures)))
	}
}

func (c *Context) ArrayElement(i int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glArrayElement_args
		glWrapHandlerArgs.i = C.GLint(i)

		c.push(C.gl_wrap_batch_func{
			jump_index: 313,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glArrayElement(c.c, C.GLint(i))
	}
}

func (c *Context) ColorPointer(size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorPointer_args
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 314,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorPointer(c.c, C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) DisableClientState(array int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDisableClientState_args
		glWrapHandlerArgs.array = C.GLenum(array)

		c.push(C.gl_wrap_batch_func{
			jump_index: 315,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDisableClientState(c.c, C.GLenum(array))
	}
}

func (c *Context) EdgeFlagPointer(stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEdgeFlagPointer_args
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 316,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEdgeFlagPointer(c.c, C.GLsizei(stride), pointer)
	}
}

func (c *Context) EnableClientState(array int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnableClientState_args
		glWrapHandlerArgs.array = C.GLenum(array)

		c.push(C.gl_wrap_batch_func{
			jump_index: 317,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnableClientState(c.c, C.GLenum(array))
	}
}

func (c *Context) IndexPointer(pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexPointer_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 318,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexPointer(c.c, C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) InterleavedArrays(format int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInterleavedArrays_args
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 319,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInterleavedArrays(c.c, C.GLenum(format), C.GLsizei(stride), pointer)
	}
}

func (c *Context) NormalPointer(pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormalPointer_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 320,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormalPointer(c.c, C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) TexCoordPointer(size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordPointer_args
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 321,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordPointer(c.c, C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) VertexPointer(size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexPointer_args
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 322,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexPointer(c.c, C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) PrioritizeTextures(n uint32, textures *uint32, priorities *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPrioritizeTextures_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))
		glWrapHandlerArgs.priorities = (*C.GLfloat)(unsafe.Pointer(priorities))

		c.push(C.gl_wrap_batch_func{
			jump_index: 323,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPrioritizeTextures(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(textures)), (*C.GLfloat)(unsafe.Pointer(priorities)))
	}
}

func (c *Context) Indexub(pC uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexub_args
		glWrapHandlerArgs.c = C.GLubyte(pC)

		c.push(C.gl_wrap_batch_func{
			jump_index: 324,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexub(c.c, C.GLubyte(pC))
	}
}

func (c *Context) Indexubv(pC *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glIndexubv_args
		glWrapHandlerArgs.c = (*C.GLubyte)(unsafe.Pointer(pC))

		c.push(C.gl_wrap_batch_func{
			jump_index: 325,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glIndexubv(c.c, (*C.GLubyte)(unsafe.Pointer(pC)))
	}
}

func (c *Context) PopClientAttrib() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPopClientAttrib_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 326,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPopClientAttrib(c.c)
	}
}

func (c *Context) PushClientAttrib(mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPushClientAttrib_args
		glWrapHandlerArgs.mask = C.GLbitfield(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 327,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPushClientAttrib(c.c, C.GLbitfield(mask))
	}
}

func (c *Context) DrawRangeElements(mode int32, start uint32, end uint32, count uint32, pType int32, indices unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawRangeElements_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.start = C.GLuint(start)
		glWrapHandlerArgs.end = C.GLuint(end)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices

		c.push(C.gl_wrap_batch_func{
			jump_index: 328,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawRangeElements(c.c, C.GLenum(mode), C.GLuint(start), C.GLuint(end), C.GLsizei(count), C.GLenum(pType), indices)
	}
}

func (c *Context) TexImage3D(target int32, level int32, internalformat int32, width uint32, height uint32, depth uint32, border int32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLint(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 329,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLint(border), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) TexSubImage3D(target int32, level int32, xoffset int32, yoffset int32, zoffset int32, width uint32, height uint32, depth uint32, format int32, pType int32, pixels unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexSubImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.pixels = pixels

		c.push(C.gl_wrap_batch_func{
			jump_index: 330,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexSubImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLenum(format), C.GLenum(pType), pixels)
	}
}

func (c *Context) CopyTexSubImage3D(target int32, level int32, xoffset int32, yoffset int32, zoffset int32, x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyTexSubImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 331,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyTexSubImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) ActiveTexture(texture int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glActiveTexture_args
		glWrapHandlerArgs.texture = C.GLenum(texture)

		c.push(C.gl_wrap_batch_func{
			jump_index: 332,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glActiveTexture(c.c, C.GLenum(texture))
	}
}

func (c *Context) SampleCoverage(value float32, invert uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSampleCoverage_args
		glWrapHandlerArgs.value = C.GLfloat(value)
		glWrapHandlerArgs.invert = C.GLboolean(invert)

		c.push(C.gl_wrap_batch_func{
			jump_index: 333,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSampleCoverage(c.c, C.GLfloat(value), C.GLboolean(invert))
	}
}

func (c *Context) CompressedTexImage3D(target int32, level int32, internalformat int32, width uint32, height uint32, depth uint32, border int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 334,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLint(border), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexImage2D(target int32, level int32, internalformat int32, width uint32, height uint32, border int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 335,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLint(border), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexImage1D(target int32, level int32, internalformat int32, width uint32, border int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexImage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.border = C.GLint(border)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 336,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexImage1D(c.c, C.GLenum(target), C.GLint(level), C.GLenum(internalformat), C.GLsizei(width), C.GLint(border), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexSubImage3D(target int32, level int32, xoffset int32, yoffset int32, zoffset int32, width uint32, height uint32, depth uint32, format int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexSubImage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 337,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexSubImage3D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLenum(format), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexSubImage2D(target int32, level int32, xoffset int32, yoffset int32, width uint32, height uint32, format int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexSubImage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 338,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexSubImage2D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLsizei(width), C.GLsizei(height), C.GLenum(format), C.GLsizei(imageSize), data)
	}
}

func (c *Context) CompressedTexSubImage1D(target int32, level int32, xoffset int32, width uint32, format int32, imageSize uint32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompressedTexSubImage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs.imageSize = C.GLsizei(imageSize)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 339,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompressedTexSubImage1D(c.c, C.GLenum(target), C.GLint(level), C.GLint(xoffset), C.GLsizei(width), C.GLenum(format), C.GLsizei(imageSize), data)
	}
}

func (c *Context) GetCompressedTexImage(target int32, level int32, img unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetCompressedTexImage_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.img = img

		c.push(C.gl_wrap_batch_func{
			jump_index: 340,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetCompressedTexImage(c.c, C.GLenum(target), C.GLint(level), img)
	}
}

func (c *Context) ClientActiveTexture(texture int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClientActiveTexture_args
		glWrapHandlerArgs.texture = C.GLenum(texture)

		c.push(C.gl_wrap_batch_func{
			jump_index: 341,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClientActiveTexture(c.c, C.GLenum(texture))
	}
}

func (c *Context) MultiTexCoord1d(target int32, s float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1d_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLdouble(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 342,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1d(c.c, C.GLenum(target), C.GLdouble(s))
	}
}

func (c *Context) MultiTexCoord1dv(target int32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1dv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 343,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1dv(c.c, C.GLenum(target), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord1f(target int32, s float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1f_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLfloat(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 344,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1f(c.c, C.GLenum(target), C.GLfloat(s))
	}
}

func (c *Context) MultiTexCoord1fv(target int32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1fv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 345,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1fv(c.c, C.GLenum(target), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord1i(target int32, s int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1i_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLint(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 346,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1i(c.c, C.GLenum(target), C.GLint(s))
	}
}

func (c *Context) MultiTexCoord1iv(target int32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1iv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 347,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1iv(c.c, C.GLenum(target), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord1s(target int32, s int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1s_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLshort(s)

		c.push(C.gl_wrap_batch_func{
			jump_index: 348,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1s(c.c, C.GLenum(target), C.GLshort(s))
	}
}

func (c *Context) MultiTexCoord1sv(target int32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord1sv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 349,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord1sv(c.c, C.GLenum(target), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord2d(target int32, s float64, t float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2d_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLdouble(s)
		glWrapHandlerArgs.t = C.GLdouble(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 350,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2d(c.c, C.GLenum(target), C.GLdouble(s), C.GLdouble(t))
	}
}

func (c *Context) MultiTexCoord2dv(target int32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2dv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 351,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2dv(c.c, C.GLenum(target), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord2f(target int32, s float32, t float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2f_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLfloat(s)
		glWrapHandlerArgs.t = C.GLfloat(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 352,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2f(c.c, C.GLenum(target), C.GLfloat(s), C.GLfloat(t))
	}
}

func (c *Context) MultiTexCoord2fv(target int32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2fv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 353,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2fv(c.c, C.GLenum(target), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord2i(target int32, s int32, t int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2i_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLint(s)
		glWrapHandlerArgs.t = C.GLint(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 354,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2i(c.c, C.GLenum(target), C.GLint(s), C.GLint(t))
	}
}

func (c *Context) MultiTexCoord2iv(target int32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2iv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 355,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2iv(c.c, C.GLenum(target), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord2s(target int32, s int16, t int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2s_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLshort(s)
		glWrapHandlerArgs.t = C.GLshort(t)

		c.push(C.gl_wrap_batch_func{
			jump_index: 356,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2s(c.c, C.GLenum(target), C.GLshort(s), C.GLshort(t))
	}
}

func (c *Context) MultiTexCoord2sv(target int32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord2sv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 357,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord2sv(c.c, C.GLenum(target), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord3d(target int32, s float64, t float64, r float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3d_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLdouble(s)
		glWrapHandlerArgs.t = C.GLdouble(t)
		glWrapHandlerArgs.r = C.GLdouble(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 358,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3d(c.c, C.GLenum(target), C.GLdouble(s), C.GLdouble(t), C.GLdouble(r))
	}
}

func (c *Context) MultiTexCoord3dv(target int32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3dv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 359,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3dv(c.c, C.GLenum(target), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord3f(target int32, s float32, t float32, r float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3f_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLfloat(s)
		glWrapHandlerArgs.t = C.GLfloat(t)
		glWrapHandlerArgs.r = C.GLfloat(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 360,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3f(c.c, C.GLenum(target), C.GLfloat(s), C.GLfloat(t), C.GLfloat(r))
	}
}

func (c *Context) MultiTexCoord3fv(target int32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3fv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 361,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3fv(c.c, C.GLenum(target), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord3i(target int32, s int32, t int32, r int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3i_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLint(s)
		glWrapHandlerArgs.t = C.GLint(t)
		glWrapHandlerArgs.r = C.GLint(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 362,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3i(c.c, C.GLenum(target), C.GLint(s), C.GLint(t), C.GLint(r))
	}
}

func (c *Context) MultiTexCoord3iv(target int32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3iv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 363,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3iv(c.c, C.GLenum(target), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord3s(target int32, s int16, t int16, r int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3s_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLshort(s)
		glWrapHandlerArgs.t = C.GLshort(t)
		glWrapHandlerArgs.r = C.GLshort(r)

		c.push(C.gl_wrap_batch_func{
			jump_index: 364,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3s(c.c, C.GLenum(target), C.GLshort(s), C.GLshort(t), C.GLshort(r))
	}
}

func (c *Context) MultiTexCoord3sv(target int32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord3sv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 365,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord3sv(c.c, C.GLenum(target), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord4d(target int32, s float64, t float64, r float64, q float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4d_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLdouble(s)
		glWrapHandlerArgs.t = C.GLdouble(t)
		glWrapHandlerArgs.r = C.GLdouble(r)
		glWrapHandlerArgs.q = C.GLdouble(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 366,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4d(c.c, C.GLenum(target), C.GLdouble(s), C.GLdouble(t), C.GLdouble(r), C.GLdouble(q))
	}
}

func (c *Context) MultiTexCoord4dv(target int32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4dv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 367,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4dv(c.c, C.GLenum(target), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord4f(target int32, s float32, t float32, r float32, q float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4f_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLfloat(s)
		glWrapHandlerArgs.t = C.GLfloat(t)
		glWrapHandlerArgs.r = C.GLfloat(r)
		glWrapHandlerArgs.q = C.GLfloat(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 368,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4f(c.c, C.GLenum(target), C.GLfloat(s), C.GLfloat(t), C.GLfloat(r), C.GLfloat(q))
	}
}

func (c *Context) MultiTexCoord4fv(target int32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4fv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 369,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4fv(c.c, C.GLenum(target), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord4i(target int32, s int32, t int32, r int32, q int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4i_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLint(s)
		glWrapHandlerArgs.t = C.GLint(t)
		glWrapHandlerArgs.r = C.GLint(r)
		glWrapHandlerArgs.q = C.GLint(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 370,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4i(c.c, C.GLenum(target), C.GLint(s), C.GLint(t), C.GLint(r), C.GLint(q))
	}
}

func (c *Context) MultiTexCoord4iv(target int32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4iv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 371,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4iv(c.c, C.GLenum(target), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) MultiTexCoord4s(target int32, s int16, t int16, r int16, q int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4s_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.s = C.GLshort(s)
		glWrapHandlerArgs.t = C.GLshort(t)
		glWrapHandlerArgs.r = C.GLshort(r)
		glWrapHandlerArgs.q = C.GLshort(q)

		c.push(C.gl_wrap_batch_func{
			jump_index: 372,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4s(c.c, C.GLenum(target), C.GLshort(s), C.GLshort(t), C.GLshort(r), C.GLshort(q))
	}
}

func (c *Context) MultiTexCoord4sv(target int32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoord4sv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 373,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoord4sv(c.c, C.GLenum(target), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) LoadTransposeMatrixf(m *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLoadTransposeMatrixf_args
		glWrapHandlerArgs.m = (*C.GLfloat)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 374,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLoadTransposeMatrixf(c.c, (*C.GLfloat)(unsafe.Pointer(m)))
	}
}

func (c *Context) LoadTransposeMatrixd(m *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLoadTransposeMatrixd_args
		glWrapHandlerArgs.m = (*C.GLdouble)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 375,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLoadTransposeMatrixd(c.c, (*C.GLdouble)(unsafe.Pointer(m)))
	}
}

func (c *Context) MultTransposeMatrixf(m *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultTransposeMatrixf_args
		glWrapHandlerArgs.m = (*C.GLfloat)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 376,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultTransposeMatrixf(c.c, (*C.GLfloat)(unsafe.Pointer(m)))
	}
}

func (c *Context) MultTransposeMatrixd(m *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultTransposeMatrixd_args
		glWrapHandlerArgs.m = (*C.GLdouble)(unsafe.Pointer(m))

		c.push(C.gl_wrap_batch_func{
			jump_index: 377,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultTransposeMatrixd(c.c, (*C.GLdouble)(unsafe.Pointer(m)))
	}
}

func (c *Context) BlendFuncSeparate(sfactorRGB int32, dfactorRGB int32, sfactorAlpha int32, dfactorAlpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendFuncSeparate_args
		glWrapHandlerArgs.sfactorRGB = C.GLenum(sfactorRGB)
		glWrapHandlerArgs.dfactorRGB = C.GLenum(dfactorRGB)
		glWrapHandlerArgs.sfactorAlpha = C.GLenum(sfactorAlpha)
		glWrapHandlerArgs.dfactorAlpha = C.GLenum(dfactorAlpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 378,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendFuncSeparate(c.c, C.GLenum(sfactorRGB), C.GLenum(dfactorRGB), C.GLenum(sfactorAlpha), C.GLenum(dfactorAlpha))
	}
}

func (c *Context) MultiDrawArrays(mode int32, first *int32, count *uint32, drawcount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiDrawArrays_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.first = (*C.GLint)(unsafe.Pointer(first))
		glWrapHandlerArgs.count = (*C.GLsizei)(unsafe.Pointer(count))
		glWrapHandlerArgs.drawcount = C.GLsizei(drawcount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 379,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiDrawArrays(c.c, C.GLenum(mode), (*C.GLint)(unsafe.Pointer(first)), (*C.GLsizei)(unsafe.Pointer(count)), C.GLsizei(drawcount))
	}
}

func (c *Context) MultiDrawElements(mode int32, count *uint32, pType int32, indices *unsafe.Pointer, drawcount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiDrawElements_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = (*C.GLsizei)(unsafe.Pointer(count))
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.drawcount = C.GLsizei(drawcount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 380,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiDrawElements(c.c, C.GLenum(mode), (*C.GLsizei)(unsafe.Pointer(count)), C.GLenum(pType), indices, C.GLsizei(drawcount))
	}
}

func (c *Context) PointParameterf(pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPointParameterf_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 381,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPointParameterf(c.c, C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) PointParameterfv(pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPointParameterfv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 382,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPointParameterfv(c.c, C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) PointParameteri(pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPointParameteri_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 383,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPointParameteri(c.c, C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) PointParameteriv(pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPointParameteriv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 384,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPointParameteriv(c.c, C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) FogCoordf(coord float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogCoordf_args
		glWrapHandlerArgs.coord = C.GLfloat(coord)

		c.push(C.gl_wrap_batch_func{
			jump_index: 385,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogCoordf(c.c, C.GLfloat(coord))
	}
}

func (c *Context) FogCoordfv(coord *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogCoordfv_args
		glWrapHandlerArgs.coord = (*C.GLfloat)(unsafe.Pointer(coord))

		c.push(C.gl_wrap_batch_func{
			jump_index: 386,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogCoordfv(c.c, (*C.GLfloat)(unsafe.Pointer(coord)))
	}
}

func (c *Context) FogCoordd(coord float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogCoordd_args
		glWrapHandlerArgs.coord = C.GLdouble(coord)

		c.push(C.gl_wrap_batch_func{
			jump_index: 387,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogCoordd(c.c, C.GLdouble(coord))
	}
}

func (c *Context) FogCoorddv(coord *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogCoorddv_args
		glWrapHandlerArgs.coord = (*C.GLdouble)(unsafe.Pointer(coord))

		c.push(C.gl_wrap_batch_func{
			jump_index: 388,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogCoorddv(c.c, (*C.GLdouble)(unsafe.Pointer(coord)))
	}
}

func (c *Context) FogCoordPointer(pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFogCoordPointer_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 389,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFogCoordPointer(c.c, C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) SecondaryColor3b(red byte, green byte, blue byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3b_args
		glWrapHandlerArgs.red = C.GLbyte(red)
		glWrapHandlerArgs.green = C.GLbyte(green)
		glWrapHandlerArgs.blue = C.GLbyte(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 390,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3b(c.c, C.GLbyte(red), C.GLbyte(green), C.GLbyte(blue))
	}
}

func (c *Context) SecondaryColor3bv(v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3bv_args
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 391,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3bv(c.c, (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3d(red float64, green float64, blue float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3d_args
		glWrapHandlerArgs.red = C.GLdouble(red)
		glWrapHandlerArgs.green = C.GLdouble(green)
		glWrapHandlerArgs.blue = C.GLdouble(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 392,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3d(c.c, C.GLdouble(red), C.GLdouble(green), C.GLdouble(blue))
	}
}

func (c *Context) SecondaryColor3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 393,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3f(red float32, green float32, blue float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3f_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 394,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3f(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue))
	}
}

func (c *Context) SecondaryColor3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 395,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3i(red int32, green int32, blue int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3i_args
		glWrapHandlerArgs.red = C.GLint(red)
		glWrapHandlerArgs.green = C.GLint(green)
		glWrapHandlerArgs.blue = C.GLint(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 396,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3i(c.c, C.GLint(red), C.GLint(green), C.GLint(blue))
	}
}

func (c *Context) SecondaryColor3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 397,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3s(red int16, green int16, blue int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3s_args
		glWrapHandlerArgs.red = C.GLshort(red)
		glWrapHandlerArgs.green = C.GLshort(green)
		glWrapHandlerArgs.blue = C.GLshort(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 398,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3s(c.c, C.GLshort(red), C.GLshort(green), C.GLshort(blue))
	}
}

func (c *Context) SecondaryColor3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 399,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3ub(red uint8, green uint8, blue uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3ub_args
		glWrapHandlerArgs.red = C.GLubyte(red)
		glWrapHandlerArgs.green = C.GLubyte(green)
		glWrapHandlerArgs.blue = C.GLubyte(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 400,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3ub(c.c, C.GLubyte(red), C.GLubyte(green), C.GLubyte(blue))
	}
}

func (c *Context) SecondaryColor3ubv(v *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3ubv_args
		glWrapHandlerArgs.v = (*C.GLubyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 401,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3ubv(c.c, (*C.GLubyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3ui(red uint32, green uint32, blue uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3ui_args
		glWrapHandlerArgs.red = C.GLuint(red)
		glWrapHandlerArgs.green = C.GLuint(green)
		glWrapHandlerArgs.blue = C.GLuint(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 402,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3ui(c.c, C.GLuint(red), C.GLuint(green), C.GLuint(blue))
	}
}

func (c *Context) SecondaryColor3uiv(v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3uiv_args
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 403,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3uiv(c.c, (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColor3us(red uint16, green uint16, blue uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3us_args
		glWrapHandlerArgs.red = C.GLushort(red)
		glWrapHandlerArgs.green = C.GLushort(green)
		glWrapHandlerArgs.blue = C.GLushort(blue)

		c.push(C.gl_wrap_batch_func{
			jump_index: 404,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3us(c.c, C.GLushort(red), C.GLushort(green), C.GLushort(blue))
	}
}

func (c *Context) SecondaryColor3usv(v *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColor3usv_args
		glWrapHandlerArgs.v = (*C.GLushort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 405,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColor3usv(c.c, (*C.GLushort)(unsafe.Pointer(v)))
	}
}

func (c *Context) SecondaryColorPointer(size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColorPointer_args
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 406,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColorPointer(c.c, C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) WindowPos2d(x float64, y float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 407,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2d(c.c, C.GLdouble(x), C.GLdouble(y))
	}
}

func (c *Context) WindowPos2dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 408,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos2f(x float32, y float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 409,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2f(c.c, C.GLfloat(x), C.GLfloat(y))
	}
}

func (c *Context) WindowPos2fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 410,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos2i(x int32, y int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 411,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2i(c.c, C.GLint(x), C.GLint(y))
	}
}

func (c *Context) WindowPos2iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 412,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos2s(x int16, y int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 413,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2s(c.c, C.GLshort(x), C.GLshort(y))
	}
}

func (c *Context) WindowPos2sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos2sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 414,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos2sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos3d(x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3d_args
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 415,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3d(c.c, C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) WindowPos3dv(v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3dv_args
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 416,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3dv(c.c, (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos3f(x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3f_args
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 417,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3f(c.c, C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) WindowPos3fv(v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3fv_args
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 418,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3fv(c.c, (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos3i(x int32, y int32, z int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3i_args
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 419,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3i(c.c, C.GLint(x), C.GLint(y), C.GLint(z))
	}
}

func (c *Context) WindowPos3iv(v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3iv_args
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 420,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3iv(c.c, (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) WindowPos3s(x int16, y int16, z int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3s_args
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 421,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3s(c.c, C.GLshort(x), C.GLshort(y), C.GLshort(z))
	}
}

func (c *Context) WindowPos3sv(v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWindowPos3sv_args
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 422,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWindowPos3sv(c.c, (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) BlendColor(red float32, green float32, blue float32, alpha float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendColor_args
		glWrapHandlerArgs.red = C.GLfloat(red)
		glWrapHandlerArgs.green = C.GLfloat(green)
		glWrapHandlerArgs.blue = C.GLfloat(blue)
		glWrapHandlerArgs.alpha = C.GLfloat(alpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 423,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendColor(c.c, C.GLfloat(red), C.GLfloat(green), C.GLfloat(blue), C.GLfloat(alpha))
	}
}

func (c *Context) BlendEquation(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendEquation_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 424,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendEquation(c.c, C.GLenum(mode))
	}
}

func (c *Context) GenQueries(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenQueries_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 425,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenQueries(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) DeleteQueries(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteQueries_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 426,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteQueries(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) BeginQuery(target int32, id uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBeginQuery_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.id = C.GLuint(id)

		c.push(C.gl_wrap_batch_func{
			jump_index: 427,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBeginQuery(c.c, C.GLenum(target), C.GLuint(id))
	}
}

func (c *Context) EndQuery(target int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndQuery_args
		glWrapHandlerArgs.target = C.GLenum(target)

		c.push(C.gl_wrap_batch_func{
			jump_index: 428,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndQuery(c.c, C.GLenum(target))
	}
}

func (c *Context) GetQueryiv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 429,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryiv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetQueryObjectiv(id uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryObjectiv_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 430,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryObjectiv(c.c, C.GLuint(id), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetQueryObjectuiv(id uint32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryObjectuiv_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 431,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryObjectuiv(c.c, C.GLuint(id), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) BindBuffer(target int32, buffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 432,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBuffer(c.c, C.GLenum(target), C.GLuint(buffer))
	}
}

func (c *Context) DeleteBuffers(n uint32, buffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteBuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 433,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteBuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(buffers)))
	}
}

func (c *Context) GenBuffers(n uint32, buffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenBuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 434,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenBuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(buffers)))
	}
}

func (c *Context) BufferData(target int32, size uintptr, data unsafe.Pointer, usage int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBufferData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.data = data
		glWrapHandlerArgs.usage = C.GLenum(usage)

		c.push(C.gl_wrap_batch_func{
			jump_index: 435,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBufferData(c.c, C.GLenum(target), C.GLsizeiptr(size), data, C.GLenum(usage))
	}
}

func (c *Context) BufferSubData(target int32, offset uintptr, size uintptr, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBufferSubData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 436,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBufferSubData(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(size), data)
	}
}

func (c *Context) GetBufferSubData(target int32, offset uintptr, size uintptr, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferSubData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 437,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferSubData(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(size), data)
	}
}

func (c *Context) MapBuffer(target int32, access int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapBuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.access = C.GLenum(access)

		c.push(C.gl_wrap_batch_func{
			jump_index: 438,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapBuffer(c.c, C.GLenum(target), C.GLenum(access))
	}
}

func (c *Context) GetBufferParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 439,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetBufferPointerv(target int32, pname int32, params *unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferPointerv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = params

		c.push(C.gl_wrap_batch_func{
			jump_index: 440,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferPointerv(c.c, C.GLenum(target), C.GLenum(pname), params)
	}
}

func (c *Context) BlendEquationSeparate(modeRGB int32, modeAlpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendEquationSeparate_args
		glWrapHandlerArgs.modeRGB = C.GLenum(modeRGB)
		glWrapHandlerArgs.modeAlpha = C.GLenum(modeAlpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 441,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendEquationSeparate(c.c, C.GLenum(modeRGB), C.GLenum(modeAlpha))
	}
}

func (c *Context) DrawBuffers(n uint32, bufs *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawBuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.bufs = (*C.GLenum)(unsafe.Pointer(bufs))

		c.push(C.gl_wrap_batch_func{
			jump_index: 442,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawBuffers(c.c, C.GLsizei(n), (*C.GLenum)(unsafe.Pointer(bufs)))
	}
}

func (c *Context) StencilOpSeparate(face int32, sfail int32, dpfail int32, dppass int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilOpSeparate_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.sfail = C.GLenum(sfail)
		glWrapHandlerArgs.dpfail = C.GLenum(dpfail)
		glWrapHandlerArgs.dppass = C.GLenum(dppass)

		c.push(C.gl_wrap_batch_func{
			jump_index: 443,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilOpSeparate(c.c, C.GLenum(face), C.GLenum(sfail), C.GLenum(dpfail), C.GLenum(dppass))
	}
}

func (c *Context) StencilFuncSeparate(face int32, pFunc int32, ref int32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilFuncSeparate_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs._func = C.GLenum(pFunc)
		glWrapHandlerArgs.ref = C.GLint(ref)
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 444,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilFuncSeparate(c.c, C.GLenum(face), C.GLenum(pFunc), C.GLint(ref), C.GLuint(mask))
	}
}

func (c *Context) StencilMaskSeparate(face int32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glStencilMaskSeparate_args
		glWrapHandlerArgs.face = C.GLenum(face)
		glWrapHandlerArgs.mask = C.GLuint(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 445,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glStencilMaskSeparate(c.c, C.GLenum(face), C.GLuint(mask))
	}
}

func (c *Context) AttachShader(program uint32, shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glAttachShader_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 446,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glAttachShader(c.c, C.GLuint(program), C.GLuint(shader))
	}
}

func (c *Context) BindAttribLocation(program uint32, index uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindAttribLocation_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 447,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindAttribLocation(c.c, C.GLuint(program), C.GLuint(index), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) CompileShader(shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCompileShader_args
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 448,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCompileShader(c.c, C.GLuint(shader))
	}
}

func (c *Context) DeleteProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 449,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) DeleteShader(shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteShader_args
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 450,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteShader(c.c, C.GLuint(shader))
	}
}

func (c *Context) DetachShader(program uint32, shader uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDetachShader_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shader = C.GLuint(shader)

		c.push(C.gl_wrap_batch_func{
			jump_index: 451,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDetachShader(c.c, C.GLuint(program), C.GLuint(shader))
	}
}

func (c *Context) DisableVertexAttribArray(index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDisableVertexAttribArray_args
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 452,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDisableVertexAttribArray(c.c, C.GLuint(index))
	}
}

func (c *Context) EnableVertexAttribArray(index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnableVertexAttribArray_args
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 453,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnableVertexAttribArray(c.c, C.GLuint(index))
	}
}

func (c *Context) GetActiveAttrib(program uint32, index uint32, bufSize uint32, length *uint32, size *int32, pType *int32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveAttrib_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.size = (*C.GLint)(unsafe.Pointer(size))
		glWrapHandlerArgs._type = (*C.GLenum)(unsafe.Pointer(pType))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 454,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveAttrib(c.c, C.GLuint(program), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(size)), (*C.GLenum)(unsafe.Pointer(pType)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetActiveUniform(program uint32, index uint32, bufSize uint32, length *uint32, size *int32, pType *int32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniform_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.size = (*C.GLint)(unsafe.Pointer(size))
		glWrapHandlerArgs._type = (*C.GLenum)(unsafe.Pointer(pType))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 455,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniform(c.c, C.GLuint(program), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(size)), (*C.GLenum)(unsafe.Pointer(pType)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetAttachedShaders(program uint32, maxCount uint32, count *uint32, shaders *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetAttachedShaders_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.maxCount = C.GLsizei(maxCount)
		glWrapHandlerArgs.count = (*C.GLsizei)(unsafe.Pointer(count))
		glWrapHandlerArgs.shaders = (*C.GLuint)(unsafe.Pointer(shaders))

		c.push(C.gl_wrap_batch_func{
			jump_index: 456,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetAttachedShaders(c.c, C.GLuint(program), C.GLsizei(maxCount), (*C.GLsizei)(unsafe.Pointer(count)), (*C.GLuint)(unsafe.Pointer(shaders)))
	}
}

func (c *Context) GetProgramiv(program uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 457,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramiv(c.c, C.GLuint(program), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetProgramInfoLog(program uint32, bufSize uint32, length *uint32, infoLog *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramInfoLog_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.infoLog = (*C.GLchar)(unsafe.Pointer(infoLog))

		c.push(C.gl_wrap_batch_func{
			jump_index: 458,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramInfoLog(c.c, C.GLuint(program), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(infoLog)))
	}
}

func (c *Context) GetShaderiv(shader uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderiv_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 459,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderiv(c.c, C.GLuint(shader), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetShaderInfoLog(shader uint32, bufSize uint32, length *uint32, infoLog *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderInfoLog_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.infoLog = (*C.GLchar)(unsafe.Pointer(infoLog))

		c.push(C.gl_wrap_batch_func{
			jump_index: 460,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderInfoLog(c.c, C.GLuint(shader), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(infoLog)))
	}
}

func (c *Context) GetShaderSource(shader uint32, bufSize uint32, length *uint32, source *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderSource_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.source = (*C.GLchar)(unsafe.Pointer(source))

		c.push(C.gl_wrap_batch_func{
			jump_index: 461,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderSource(c.c, C.GLuint(shader), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(source)))
	}
}

func (c *Context) GetUniformfv(program uint32, location int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformfv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 462,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformfv(c.c, C.GLuint(program), C.GLint(location), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetUniformiv(program uint32, location int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 463,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformiv(c.c, C.GLuint(program), C.GLint(location), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribdv(index uint32, pname int32, params *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribdv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLdouble)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 464,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribdv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLdouble)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribfv(index uint32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribfv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 465,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribfv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribiv(index uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 466,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribiv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribPointerv(index uint32, pname int32, pointer *unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribPointerv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 467,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribPointerv(c.c, C.GLuint(index), C.GLenum(pname), pointer)
	}
}

func (c *Context) LinkProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glLinkProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 468,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glLinkProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) ShaderSource(shader uint32, count uint32, string **byte, length *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glShaderSource_args
		glWrapHandlerArgs.shader = C.GLuint(shader)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.string = (**C.GLchar)(unsafe.Pointer(string))
		glWrapHandlerArgs.length = (*C.GLint)(unsafe.Pointer(length))

		c.push(C.gl_wrap_batch_func{
			jump_index: 469,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glShaderSource(c.c, C.GLuint(shader), C.GLsizei(count), (**C.GLchar)(unsafe.Pointer(string)), (*C.GLint)(unsafe.Pointer(length)))
	}
}

func (c *Context) UseProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUseProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 470,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUseProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) Uniform1f(location int32, v0 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 471,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1f(c.c, C.GLint(location), C.GLfloat(v0))
	}
}

func (c *Context) Uniform2f(location int32, v0 float32, v1 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 472,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2f(c.c, C.GLint(location), C.GLfloat(v0), C.GLfloat(v1))
	}
}

func (c *Context) Uniform3f(location int32, v0 float32, v1 float32, v2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 473,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3f(c.c, C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2))
	}
}

func (c *Context) Uniform4f(location int32, v0 float32, v1 float32, v2 float32, v3 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4f_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)
		glWrapHandlerArgs.v3 = C.GLfloat(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 474,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4f(c.c, C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2), C.GLfloat(v3))
	}
}

func (c *Context) Uniform1i(location int32, v0 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 475,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1i(c.c, C.GLint(location), C.GLint(v0))
	}
}

func (c *Context) Uniform2i(location int32, v0 int32, v1 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 476,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2i(c.c, C.GLint(location), C.GLint(v0), C.GLint(v1))
	}
}

func (c *Context) Uniform3i(location int32, v0 int32, v1 int32, v2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 477,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3i(c.c, C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2))
	}
}

func (c *Context) Uniform4i(location int32, v0 int32, v1 int32, v2 int32, v3 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4i_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)
		glWrapHandlerArgs.v3 = C.GLint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 478,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4i(c.c, C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2), C.GLint(v3))
	}
}

func (c *Context) Uniform1fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 479,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 480,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 481,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4fv(location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 482,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4fv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform1iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 483,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 484,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 485,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4iv(location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4iv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 486,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4iv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 487,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 488,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 489,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ValidateProgram(program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glValidateProgram_args
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 490,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glValidateProgram(c.c, C.GLuint(program))
	}
}

func (c *Context) VertexAttrib1d(index uint32, x float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 491,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1d(c.c, C.GLuint(index), C.GLdouble(x))
	}
}

func (c *Context) VertexAttrib1dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 492,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib1f(index uint32, x float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 493,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1f(c.c, C.GLuint(index), C.GLfloat(x))
	}
}

func (c *Context) VertexAttrib1fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 494,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib1s(index uint32, x int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1s_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLshort(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 495,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1s(c.c, C.GLuint(index), C.GLshort(x))
	}
}

func (c *Context) VertexAttrib1sv(index uint32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib1sv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 496,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib1sv(c.c, C.GLuint(index), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib2d(index uint32, x float64, y float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 497,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2d(c.c, C.GLuint(index), C.GLdouble(x), C.GLdouble(y))
	}
}

func (c *Context) VertexAttrib2dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 498,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib2f(index uint32, x float32, y float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 499,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2f(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y))
	}
}

func (c *Context) VertexAttrib2fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 500,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib2s(index uint32, x int16, y int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2s_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 501,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2s(c.c, C.GLuint(index), C.GLshort(x), C.GLshort(y))
	}
}

func (c *Context) VertexAttrib2sv(index uint32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib2sv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 502,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib2sv(c.c, C.GLuint(index), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib3d(index uint32, x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 503,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3d(c.c, C.GLuint(index), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) VertexAttrib3dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 504,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib3f(index uint32, x float32, y float32, z float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 505,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3f(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y), C.GLfloat(z))
	}
}

func (c *Context) VertexAttrib3fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 506,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib3s(index uint32, x int16, y int16, z int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3s_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 507,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3s(c.c, C.GLuint(index), C.GLshort(x), C.GLshort(y), C.GLshort(z))
	}
}

func (c *Context) VertexAttrib3sv(index uint32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib3sv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 508,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib3sv(c.c, C.GLuint(index), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4Nbv(index uint32, v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Nbv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 509,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Nbv(c.c, C.GLuint(index), (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4Niv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Niv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 510,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Niv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4Nsv(index uint32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Nsv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 511,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Nsv(c.c, C.GLuint(index), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4Nub(index uint32, x uint8, y uint8, z uint8, w uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Nub_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLubyte(x)
		glWrapHandlerArgs.y = C.GLubyte(y)
		glWrapHandlerArgs.z = C.GLubyte(z)
		glWrapHandlerArgs.w = C.GLubyte(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 512,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Nub(c.c, C.GLuint(index), C.GLubyte(x), C.GLubyte(y), C.GLubyte(z), C.GLubyte(w))
	}
}

func (c *Context) VertexAttrib4Nubv(index uint32, v *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Nubv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLubyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 513,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Nubv(c.c, C.GLuint(index), (*C.GLubyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4Nuiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Nuiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 514,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Nuiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4Nusv(index uint32, v *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4Nusv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLushort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 515,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4Nusv(c.c, C.GLuint(index), (*C.GLushort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4bv(index uint32, v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4bv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 516,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4bv(c.c, C.GLuint(index), (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4d(index uint32, x float64, y float64, z float64, w float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)
		glWrapHandlerArgs.w = C.GLdouble(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 517,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4d(c.c, C.GLuint(index), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z), C.GLdouble(w))
	}
}

func (c *Context) VertexAttrib4dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 518,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4f(index uint32, x float32, y float32, z float32, w float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4f_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.z = C.GLfloat(z)
		glWrapHandlerArgs.w = C.GLfloat(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 519,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4f(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y), C.GLfloat(z), C.GLfloat(w))
	}
}

func (c *Context) VertexAttrib4fv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4fv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 520,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4fv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4iv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4iv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 521,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4iv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4s(index uint32, x int16, y int16, z int16, w int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4s_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLshort(x)
		glWrapHandlerArgs.y = C.GLshort(y)
		glWrapHandlerArgs.z = C.GLshort(z)
		glWrapHandlerArgs.w = C.GLshort(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 522,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4s(c.c, C.GLuint(index), C.GLshort(x), C.GLshort(y), C.GLshort(z), C.GLshort(w))
	}
}

func (c *Context) VertexAttrib4sv(index uint32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4sv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 523,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4sv(c.c, C.GLuint(index), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4ubv(index uint32, v *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4ubv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLubyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 524,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4ubv(c.c, C.GLuint(index), (*C.GLubyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4uiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 525,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4uiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttrib4usv(index uint32, v *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttrib4usv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLushort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 526,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttrib4usv(c.c, C.GLuint(index), (*C.GLushort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribPointer(index uint32, size int32, pType int32, normalized uint8, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribPointer_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 527,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribPointer(c.c, C.GLuint(index), C.GLint(size), C.GLenum(pType), C.GLboolean(normalized), C.GLsizei(stride), pointer)
	}
}

func (c *Context) UniformMatrix2x3fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2x3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 528,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2x3fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3x2fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3x2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 529,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3x2fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2x4fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2x4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 530,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2x4fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4x2fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4x2fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 531,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4x2fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3x4fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3x4fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 532,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3x4fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4x3fv(location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4x3fv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 533,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4x3fv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ColorMaski(index uint32, r uint8, g uint8, b uint8, a uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorMaski_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.r = C.GLboolean(r)
		glWrapHandlerArgs.g = C.GLboolean(g)
		glWrapHandlerArgs.b = C.GLboolean(b)
		glWrapHandlerArgs.a = C.GLboolean(a)

		c.push(C.gl_wrap_batch_func{
			jump_index: 534,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorMaski(c.c, C.GLuint(index), C.GLboolean(r), C.GLboolean(g), C.GLboolean(b), C.GLboolean(a))
	}
}

func (c *Context) GetBooleani_v(target int32, index uint32, data *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBooleani_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLboolean)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 535,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBooleani_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLboolean)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetIntegeri_v(target int32, index uint32, data *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetIntegeri_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLint)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 536,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetIntegeri_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLint)(unsafe.Pointer(data)))
	}
}

func (c *Context) Enablei(target int32, index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEnablei_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 537,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEnablei(c.c, C.GLenum(target), C.GLuint(index))
	}
}

func (c *Context) Disablei(target int32, index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDisablei_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 538,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDisablei(c.c, C.GLenum(target), C.GLuint(index))
	}
}

func (c *Context) BeginTransformFeedback(primitiveMode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBeginTransformFeedback_args
		glWrapHandlerArgs.primitiveMode = C.GLenum(primitiveMode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 539,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBeginTransformFeedback(c.c, C.GLenum(primitiveMode))
	}
}

func (c *Context) EndTransformFeedback() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndTransformFeedback_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 540,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndTransformFeedback(c.c)
	}
}

func (c *Context) BindBufferRange(target int32, index uint32, buffer uint32, offset uintptr, size uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)

		c.push(C.gl_wrap_batch_func{
			jump_index: 541,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBufferRange(c.c, C.GLenum(target), C.GLuint(index), C.GLuint(buffer), C.GLintptr(offset), C.GLsizeiptr(size))
	}
}

func (c *Context) BindBufferBase(target int32, index uint32, buffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBufferBase_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 542,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBufferBase(c.c, C.GLenum(target), C.GLuint(index), C.GLuint(buffer))
	}
}

func (c *Context) TransformFeedbackVaryings(program uint32, count uint32, varyings **byte, bufferMode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTransformFeedbackVaryings_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.varyings = (**C.GLchar)(unsafe.Pointer(varyings))
		glWrapHandlerArgs.bufferMode = C.GLenum(bufferMode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 543,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTransformFeedbackVaryings(c.c, C.GLuint(program), C.GLsizei(count), (**C.GLchar)(unsafe.Pointer(varyings)), C.GLenum(bufferMode))
	}
}

func (c *Context) GetTransformFeedbackVarying(program uint32, index uint32, bufSize uint32, length *uint32, size *uint32, pType *int32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTransformFeedbackVarying_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.size = (*C.GLsizei)(unsafe.Pointer(size))
		glWrapHandlerArgs._type = (*C.GLenum)(unsafe.Pointer(pType))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 544,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTransformFeedbackVarying(c.c, C.GLuint(program), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLsizei)(unsafe.Pointer(size)), (*C.GLenum)(unsafe.Pointer(pType)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) ClampColor(target int32, clamp int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClampColor_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.clamp = C.GLenum(clamp)

		c.push(C.gl_wrap_batch_func{
			jump_index: 545,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClampColor(c.c, C.GLenum(target), C.GLenum(clamp))
	}
}

func (c *Context) BeginConditionalRender(id uint32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBeginConditionalRender_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 546,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBeginConditionalRender(c.c, C.GLuint(id), C.GLenum(mode))
	}
}

func (c *Context) EndConditionalRender() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndConditionalRender_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 547,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndConditionalRender(c.c)
	}
}

func (c *Context) VertexAttribIPointer(index uint32, size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribIPointer_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 548,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribIPointer(c.c, C.GLuint(index), C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) GetVertexAttribIiv(index uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribIiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 549,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribIiv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetVertexAttribIuiv(index uint32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribIuiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 550,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribIuiv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) VertexAttribI1i(index uint32, x int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI1i_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLint(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 551,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI1i(c.c, C.GLuint(index), C.GLint(x))
	}
}

func (c *Context) VertexAttribI2i(index uint32, x int32, y int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI2i_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 552,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI2i(c.c, C.GLuint(index), C.GLint(x), C.GLint(y))
	}
}

func (c *Context) VertexAttribI3i(index uint32, x int32, y int32, z int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI3i_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 553,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI3i(c.c, C.GLuint(index), C.GLint(x), C.GLint(y), C.GLint(z))
	}
}

func (c *Context) VertexAttribI4i(index uint32, x int32, y int32, z int32, w int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4i_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.z = C.GLint(z)
		glWrapHandlerArgs.w = C.GLint(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 554,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4i(c.c, C.GLuint(index), C.GLint(x), C.GLint(y), C.GLint(z), C.GLint(w))
	}
}

func (c *Context) VertexAttribI1ui(index uint32, x uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI1ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLuint(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 555,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI1ui(c.c, C.GLuint(index), C.GLuint(x))
	}
}

func (c *Context) VertexAttribI2ui(index uint32, x uint32, y uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI2ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLuint(x)
		glWrapHandlerArgs.y = C.GLuint(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 556,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI2ui(c.c, C.GLuint(index), C.GLuint(x), C.GLuint(y))
	}
}

func (c *Context) VertexAttribI3ui(index uint32, x uint32, y uint32, z uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI3ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLuint(x)
		glWrapHandlerArgs.y = C.GLuint(y)
		glWrapHandlerArgs.z = C.GLuint(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 557,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI3ui(c.c, C.GLuint(index), C.GLuint(x), C.GLuint(y), C.GLuint(z))
	}
}

func (c *Context) VertexAttribI4ui(index uint32, x uint32, y uint32, z uint32, w uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLuint(x)
		glWrapHandlerArgs.y = C.GLuint(y)
		glWrapHandlerArgs.z = C.GLuint(z)
		glWrapHandlerArgs.w = C.GLuint(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 558,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4ui(c.c, C.GLuint(index), C.GLuint(x), C.GLuint(y), C.GLuint(z), C.GLuint(w))
	}
}

func (c *Context) VertexAttribI1iv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI1iv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 559,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI1iv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI2iv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI2iv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 560,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI2iv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI3iv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI3iv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 561,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI3iv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4iv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4iv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 562,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4iv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI1uiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI1uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 563,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI1uiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI2uiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI2uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 564,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI2uiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI3uiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI3uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 565,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI3uiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4uiv(index uint32, v *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLuint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 566,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4uiv(c.c, C.GLuint(index), (*C.GLuint)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4bv(index uint32, v *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4bv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLbyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 567,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4bv(c.c, C.GLuint(index), (*C.GLbyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4sv(index uint32, v *int16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4sv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLshort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 568,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4sv(c.c, C.GLuint(index), (*C.GLshort)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4ubv(index uint32, v *uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4ubv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLubyte)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 569,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4ubv(c.c, C.GLuint(index), (*C.GLubyte)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribI4usv(index uint32, v *uint16) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribI4usv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLushort)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 570,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribI4usv(c.c, C.GLuint(index), (*C.GLushort)(unsafe.Pointer(v)))
	}
}

func (c *Context) GetUniformuiv(program uint32, location int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformuiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 571,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformuiv(c.c, C.GLuint(program), C.GLint(location), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) BindFragDataLocation(program uint32, color uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindFragDataLocation_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.color = C.GLuint(color)
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 572,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindFragDataLocation(c.c, C.GLuint(program), C.GLuint(color), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) Uniform1ui(location int32, v0 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 573,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1ui(c.c, C.GLint(location), C.GLuint(v0))
	}
}

func (c *Context) Uniform2ui(location int32, v0 uint32, v1 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 574,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2ui(c.c, C.GLint(location), C.GLuint(v0), C.GLuint(v1))
	}
}

func (c *Context) Uniform3ui(location int32, v0 uint32, v1 uint32, v2 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 575,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3ui(c.c, C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2))
	}
}

func (c *Context) Uniform4ui(location int32, v0 uint32, v1 uint32, v2 uint32, v3 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4ui_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)
		glWrapHandlerArgs.v3 = C.GLuint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 576,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4ui(c.c, C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2), C.GLuint(v3))
	}
}

func (c *Context) Uniform1uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 577,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 578,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 579,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4uiv(location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4uiv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 580,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4uiv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) TexParameterIiv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameterIiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 581,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameterIiv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) TexParameterIuiv(target int32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexParameterIuiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 582,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexParameterIuiv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexParameterIiv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexParameterIiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 583,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexParameterIiv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetTexParameterIuiv(target int32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetTexParameterIuiv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 584,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetTexParameterIuiv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) ClearBufferiv(buffer int32, drawbuffer int32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferiv_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 585,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferiv(c.c, C.GLenum(buffer), C.GLint(drawbuffer), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferuiv(buffer int32, drawbuffer int32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferuiv_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 586,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferuiv(c.c, C.GLenum(buffer), C.GLint(drawbuffer), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferfv(buffer int32, drawbuffer int32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferfv_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 587,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferfv(c.c, C.GLenum(buffer), C.GLint(drawbuffer), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ClearBufferfi(buffer int32, drawbuffer int32, depth float32, stencil int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferfi_args
		glWrapHandlerArgs.buffer = C.GLenum(buffer)
		glWrapHandlerArgs.drawbuffer = C.GLint(drawbuffer)
		glWrapHandlerArgs.depth = C.GLfloat(depth)
		glWrapHandlerArgs.stencil = C.GLint(stencil)

		c.push(C.gl_wrap_batch_func{
			jump_index: 588,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferfi(c.c, C.GLenum(buffer), C.GLint(drawbuffer), C.GLfloat(depth), C.GLint(stencil))
	}
}

func (c *Context) BindRenderbuffer(target int32, renderbuffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindRenderbuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.renderbuffer = C.GLuint(renderbuffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 589,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindRenderbuffer(c.c, C.GLenum(target), C.GLuint(renderbuffer))
	}
}

func (c *Context) DeleteRenderbuffers(n uint32, renderbuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteRenderbuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.renderbuffers = (*C.GLuint)(unsafe.Pointer(renderbuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 590,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteRenderbuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(renderbuffers)))
	}
}

func (c *Context) GenRenderbuffers(n uint32, renderbuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenRenderbuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.renderbuffers = (*C.GLuint)(unsafe.Pointer(renderbuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 591,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenRenderbuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(renderbuffers)))
	}
}

func (c *Context) RenderbufferStorage(target int32, internalformat int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRenderbufferStorage_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 592,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRenderbufferStorage(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) GetRenderbufferParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetRenderbufferParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 593,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetRenderbufferParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) BindFramebuffer(target int32, framebuffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindFramebuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.framebuffer = C.GLuint(framebuffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 594,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindFramebuffer(c.c, C.GLenum(target), C.GLuint(framebuffer))
	}
}

func (c *Context) DeleteFramebuffers(n uint32, framebuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteFramebuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.framebuffers = (*C.GLuint)(unsafe.Pointer(framebuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 595,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteFramebuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(framebuffers)))
	}
}

func (c *Context) GenFramebuffers(n uint32, framebuffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenFramebuffers_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.framebuffers = (*C.GLuint)(unsafe.Pointer(framebuffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 596,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenFramebuffers(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(framebuffers)))
	}
}

func (c *Context) FramebufferTexture1D(target int32, attachment int32, textarget int32, texture uint32, level int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTexture1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.textarget = C.GLenum(textarget)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)

		c.push(C.gl_wrap_batch_func{
			jump_index: 597,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTexture1D(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(textarget), C.GLuint(texture), C.GLint(level))
	}
}

func (c *Context) FramebufferTexture2D(target int32, attachment int32, textarget int32, texture uint32, level int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTexture2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.textarget = C.GLenum(textarget)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)

		c.push(C.gl_wrap_batch_func{
			jump_index: 598,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTexture2D(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(textarget), C.GLuint(texture), C.GLint(level))
	}
}

func (c *Context) FramebufferTexture3D(target int32, attachment int32, textarget int32, texture uint32, level int32, zoffset int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTexture3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.textarget = C.GLenum(textarget)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)

		c.push(C.gl_wrap_batch_func{
			jump_index: 599,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTexture3D(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(textarget), C.GLuint(texture), C.GLint(level), C.GLint(zoffset))
	}
}

func (c *Context) FramebufferRenderbuffer(target int32, attachment int32, renderbuffertarget int32, renderbuffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferRenderbuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.renderbuffertarget = C.GLenum(renderbuffertarget)
		glWrapHandlerArgs.renderbuffer = C.GLuint(renderbuffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 600,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferRenderbuffer(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(renderbuffertarget), C.GLuint(renderbuffer))
	}
}

func (c *Context) GetFramebufferAttachmentParameteriv(target int32, attachment int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFramebufferAttachmentParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 601,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFramebufferAttachmentParameteriv(c.c, C.GLenum(target), C.GLenum(attachment), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GenerateMipmap(target int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenerateMipmap_args
		glWrapHandlerArgs.target = C.GLenum(target)

		c.push(C.gl_wrap_batch_func{
			jump_index: 602,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenerateMipmap(c.c, C.GLenum(target))
	}
}

func (c *Context) BlitFramebuffer(srcX0 int32, srcY0 int32, srcX1 int32, srcY1 int32, dstX0 int32, dstY0 int32, dstX1 int32, dstY1 int32, mask uint32, filter int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlitFramebuffer_args
		glWrapHandlerArgs.srcX0 = C.GLint(srcX0)
		glWrapHandlerArgs.srcY0 = C.GLint(srcY0)
		glWrapHandlerArgs.srcX1 = C.GLint(srcX1)
		glWrapHandlerArgs.srcY1 = C.GLint(srcY1)
		glWrapHandlerArgs.dstX0 = C.GLint(dstX0)
		glWrapHandlerArgs.dstY0 = C.GLint(dstY0)
		glWrapHandlerArgs.dstX1 = C.GLint(dstX1)
		glWrapHandlerArgs.dstY1 = C.GLint(dstY1)
		glWrapHandlerArgs.mask = C.GLbitfield(mask)
		glWrapHandlerArgs.filter = C.GLenum(filter)

		c.push(C.gl_wrap_batch_func{
			jump_index: 603,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlitFramebuffer(c.c, C.GLint(srcX0), C.GLint(srcY0), C.GLint(srcX1), C.GLint(srcY1), C.GLint(dstX0), C.GLint(dstY0), C.GLint(dstX1), C.GLint(dstY1), C.GLbitfield(mask), C.GLenum(filter))
	}
}

func (c *Context) RenderbufferStorageMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glRenderbufferStorageMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 604,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glRenderbufferStorageMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) FramebufferTextureLayer(target int32, attachment int32, texture uint32, level int32, layer int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTextureLayer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.layer = C.GLint(layer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 605,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTextureLayer(c.c, C.GLenum(target), C.GLenum(attachment), C.GLuint(texture), C.GLint(level), C.GLint(layer))
	}
}

func (c *Context) MapBufferRange(target int32, offset uintptr, length uintptr, access uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMapBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.length = C.GLsizeiptr(length)
		glWrapHandlerArgs.access = C.GLbitfield(access)

		c.push(C.gl_wrap_batch_func{
			jump_index: 606,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMapBufferRange(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(length), C.GLbitfield(access))
	}
}

func (c *Context) FlushMappedBufferRange(target int32, offset uintptr, length uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFlushMappedBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.length = C.GLsizeiptr(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 607,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFlushMappedBufferRange(c.c, C.GLenum(target), C.GLintptr(offset), C.GLsizeiptr(length))
	}
}

func (c *Context) BindVertexArray(array uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindVertexArray_args
		glWrapHandlerArgs.array = C.GLuint(array)

		c.push(C.gl_wrap_batch_func{
			jump_index: 608,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindVertexArray(c.c, C.GLuint(array))
	}
}

func (c *Context) DeleteVertexArrays(n uint32, arrays *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteVertexArrays_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.arrays = (*C.GLuint)(unsafe.Pointer(arrays))

		c.push(C.gl_wrap_batch_func{
			jump_index: 609,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteVertexArrays(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(arrays)))
	}
}

func (c *Context) GenVertexArrays(n uint32, arrays *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenVertexArrays_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.arrays = (*C.GLuint)(unsafe.Pointer(arrays))

		c.push(C.gl_wrap_batch_func{
			jump_index: 610,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenVertexArrays(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(arrays)))
	}
}

func (c *Context) DrawArraysInstanced(mode int32, first int32, count uint32, instancecount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArraysInstanced_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.first = C.GLint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 611,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArraysInstanced(c.c, C.GLenum(mode), C.GLint(first), C.GLsizei(count), C.GLsizei(instancecount))
	}
}

func (c *Context) DrawElementsInstanced(mode int32, count uint32, pType int32, indices unsafe.Pointer, instancecount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsInstanced_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 612,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsInstanced(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices, C.GLsizei(instancecount))
	}
}

func (c *Context) TexBuffer(target int32, internalformat int32, buffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexBuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 613,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexBuffer(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLuint(buffer))
	}
}

func (c *Context) PrimitiveRestartIndex(index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPrimitiveRestartIndex_args
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 614,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPrimitiveRestartIndex(c.c, C.GLuint(index))
	}
}

func (c *Context) CopyBufferSubData(readTarget int32, writeTarget int32, readOffset uintptr, writeOffset uintptr, size uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyBufferSubData_args
		glWrapHandlerArgs.readTarget = C.GLenum(readTarget)
		glWrapHandlerArgs.writeTarget = C.GLenum(writeTarget)
		glWrapHandlerArgs.readOffset = C.GLintptr(readOffset)
		glWrapHandlerArgs.writeOffset = C.GLintptr(writeOffset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)

		c.push(C.gl_wrap_batch_func{
			jump_index: 615,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyBufferSubData(c.c, C.GLenum(readTarget), C.GLenum(writeTarget), C.GLintptr(readOffset), C.GLintptr(writeOffset), C.GLsizeiptr(size))
	}
}

func (c *Context) GetUniformIndices(program uint32, uniformCount uint32, uniformNames **byte, uniformIndices *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformIndices_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformCount = C.GLsizei(uniformCount)
		glWrapHandlerArgs.uniformNames = (**C.GLchar)(unsafe.Pointer(uniformNames))
		glWrapHandlerArgs.uniformIndices = (*C.GLuint)(unsafe.Pointer(uniformIndices))

		c.push(C.gl_wrap_batch_func{
			jump_index: 616,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformIndices(c.c, C.GLuint(program), C.GLsizei(uniformCount), (**C.GLchar)(unsafe.Pointer(uniformNames)), (*C.GLuint)(unsafe.Pointer(uniformIndices)))
	}
}

func (c *Context) GetActiveUniformsiv(program uint32, uniformCount uint32, uniformIndices *uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformsiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformCount = C.GLsizei(uniformCount)
		glWrapHandlerArgs.uniformIndices = (*C.GLuint)(unsafe.Pointer(uniformIndices))
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 617,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformsiv(c.c, C.GLuint(program), C.GLsizei(uniformCount), (*C.GLuint)(unsafe.Pointer(uniformIndices)), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetActiveUniformName(program uint32, uniformIndex uint32, bufSize uint32, length *uint32, uniformName *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformIndex = C.GLuint(uniformIndex)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.uniformName = (*C.GLchar)(unsafe.Pointer(uniformName))

		c.push(C.gl_wrap_batch_func{
			jump_index: 618,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformName(c.c, C.GLuint(program), C.GLuint(uniformIndex), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(uniformName)))
	}
}

func (c *Context) GetActiveUniformBlockiv(program uint32, uniformBlockIndex uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformBlockiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformBlockIndex = C.GLuint(uniformBlockIndex)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 619,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformBlockiv(c.c, C.GLuint(program), C.GLuint(uniformBlockIndex), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetActiveUniformBlockName(program uint32, uniformBlockIndex uint32, bufSize uint32, length *uint32, uniformBlockName *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveUniformBlockName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformBlockIndex = C.GLuint(uniformBlockIndex)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.uniformBlockName = (*C.GLchar)(unsafe.Pointer(uniformBlockName))

		c.push(C.gl_wrap_batch_func{
			jump_index: 620,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveUniformBlockName(c.c, C.GLuint(program), C.GLuint(uniformBlockIndex), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(uniformBlockName)))
	}
}

func (c *Context) UniformBlockBinding(program uint32, uniformBlockIndex uint32, uniformBlockBinding uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformBlockBinding_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.uniformBlockIndex = C.GLuint(uniformBlockIndex)
		glWrapHandlerArgs.uniformBlockBinding = C.GLuint(uniformBlockBinding)

		c.push(C.gl_wrap_batch_func{
			jump_index: 621,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformBlockBinding(c.c, C.GLuint(program), C.GLuint(uniformBlockIndex), C.GLuint(uniformBlockBinding))
	}
}

func (c *Context) DrawElementsBaseVertex(mode int32, count uint32, pType int32, indices unsafe.Pointer, basevertex int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsBaseVertex_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.basevertex = C.GLint(basevertex)

		c.push(C.gl_wrap_batch_func{
			jump_index: 622,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsBaseVertex(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices, C.GLint(basevertex))
	}
}

func (c *Context) DrawRangeElementsBaseVertex(mode int32, start uint32, end uint32, count uint32, pType int32, indices unsafe.Pointer, basevertex int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawRangeElementsBaseVertex_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.start = C.GLuint(start)
		glWrapHandlerArgs.end = C.GLuint(end)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.basevertex = C.GLint(basevertex)

		c.push(C.gl_wrap_batch_func{
			jump_index: 623,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawRangeElementsBaseVertex(c.c, C.GLenum(mode), C.GLuint(start), C.GLuint(end), C.GLsizei(count), C.GLenum(pType), indices, C.GLint(basevertex))
	}
}

func (c *Context) DrawElementsInstancedBaseVertex(mode int32, count uint32, pType int32, indices unsafe.Pointer, instancecount uint32, basevertex int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsInstancedBaseVertex_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)
		glWrapHandlerArgs.basevertex = C.GLint(basevertex)

		c.push(C.gl_wrap_batch_func{
			jump_index: 624,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsInstancedBaseVertex(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices, C.GLsizei(instancecount), C.GLint(basevertex))
	}
}

func (c *Context) MultiDrawElementsBaseVertex(mode int32, count *uint32, pType int32, indices *unsafe.Pointer, drawcount uint32, basevertex *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiDrawElementsBaseVertex_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = (*C.GLsizei)(unsafe.Pointer(count))
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.drawcount = C.GLsizei(drawcount)
		glWrapHandlerArgs.basevertex = (*C.GLint)(unsafe.Pointer(basevertex))

		c.push(C.gl_wrap_batch_func{
			jump_index: 625,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiDrawElementsBaseVertex(c.c, C.GLenum(mode), (*C.GLsizei)(unsafe.Pointer(count)), C.GLenum(pType), indices, C.GLsizei(drawcount), (*C.GLint)(unsafe.Pointer(basevertex)))
	}
}

func (c *Context) ProvokingVertex(mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProvokingVertex_args
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 626,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProvokingVertex(c.c, C.GLenum(mode))
	}
}

func (c *Context) DeleteSync(sync Sync) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteSync_args
		glWrapHandlerArgs.sync = C.GLsync(sync)

		c.push(C.gl_wrap_batch_func{
			jump_index: 627,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteSync(c.c, C.GLsync(sync))
	}
}

func (c *Context) WaitSync(sync Sync, flags uint32, timeout uint64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glWaitSync_args
		glWrapHandlerArgs.sync = C.GLsync(sync)
		glWrapHandlerArgs.flags = C.GLbitfield(flags)
		glWrapHandlerArgs.timeout = C.GLuint64(timeout)

		c.push(C.gl_wrap_batch_func{
			jump_index: 628,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glWaitSync(c.c, C.GLsync(sync), C.GLbitfield(flags), C.GLuint64(timeout))
	}
}

func (c *Context) GetInteger64v(pname int32, data *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInteger64v_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.data = (*C.GLint64)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 629,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInteger64v(c.c, C.GLenum(pname), (*C.GLint64)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetSynciv(sync Sync, pname int32, bufSize uint32, length *uint32, values *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSynciv_args
		glWrapHandlerArgs.sync = C.GLsync(sync)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.values = (*C.GLint)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 630,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSynciv(c.c, C.GLsync(sync), C.GLenum(pname), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(values)))
	}
}

func (c *Context) GetInteger64i_v(target int32, index uint32, data *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInteger64i_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLint64)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 631,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInteger64i_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLint64)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetBufferParameteri64v(target int32, pname int32, params *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetBufferParameteri64v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint64)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 632,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetBufferParameteri64v(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint64)(unsafe.Pointer(params)))
	}
}

func (c *Context) FramebufferTexture(target int32, attachment int32, texture uint32, level int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferTexture_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.attachment = C.GLenum(attachment)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)

		c.push(C.gl_wrap_batch_func{
			jump_index: 633,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferTexture(c.c, C.GLenum(target), C.GLenum(attachment), C.GLuint(texture), C.GLint(level))
	}
}

func (c *Context) TexImage2DMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32, fixedsamplelocations uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage2DMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.fixedsamplelocations = C.GLboolean(fixedsamplelocations)

		c.push(C.gl_wrap_batch_func{
			jump_index: 634,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage2DMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLboolean(fixedsamplelocations))
	}
}

func (c *Context) TexImage3DMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32, depth uint32, fixedsamplelocations uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexImage3DMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.fixedsamplelocations = C.GLboolean(fixedsamplelocations)

		c.push(C.gl_wrap_batch_func{
			jump_index: 635,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexImage3DMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLboolean(fixedsamplelocations))
	}
}

func (c *Context) GetMultisamplefv(pname int32, index uint32, val *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetMultisamplefv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.val = (*C.GLfloat)(unsafe.Pointer(val))

		c.push(C.gl_wrap_batch_func{
			jump_index: 636,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetMultisamplefv(c.c, C.GLenum(pname), C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(val)))
	}
}

func (c *Context) SampleMaski(maskNumber uint32, mask uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSampleMaski_args
		glWrapHandlerArgs.maskNumber = C.GLuint(maskNumber)
		glWrapHandlerArgs.mask = C.GLbitfield(mask)

		c.push(C.gl_wrap_batch_func{
			jump_index: 637,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSampleMaski(c.c, C.GLuint(maskNumber), C.GLbitfield(mask))
	}
}

func (c *Context) BindFragDataLocationIndexed(program uint32, colorNumber uint32, index uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindFragDataLocationIndexed_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.colorNumber = C.GLuint(colorNumber)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 638,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindFragDataLocationIndexed(c.c, C.GLuint(program), C.GLuint(colorNumber), C.GLuint(index), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GenSamplers(count uint32, samplers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenSamplers_args
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.samplers = (*C.GLuint)(unsafe.Pointer(samplers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 639,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenSamplers(c.c, C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(samplers)))
	}
}

func (c *Context) DeleteSamplers(count uint32, samplers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteSamplers_args
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.samplers = (*C.GLuint)(unsafe.Pointer(samplers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 640,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteSamplers(c.c, C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(samplers)))
	}
}

func (c *Context) BindSampler(unit uint32, sampler uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindSampler_args
		glWrapHandlerArgs.unit = C.GLuint(unit)
		glWrapHandlerArgs.sampler = C.GLuint(sampler)

		c.push(C.gl_wrap_batch_func{
			jump_index: 641,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindSampler(c.c, C.GLuint(unit), C.GLuint(sampler))
	}
}

func (c *Context) SamplerParameteri(sampler uint32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameteri_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 642,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameteri(c.c, C.GLuint(sampler), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) SamplerParameteriv(sampler uint32, pname int32, param *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameteriv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = (*C.GLint)(unsafe.Pointer(param))

		c.push(C.gl_wrap_batch_func{
			jump_index: 643,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameteriv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(param)))
	}
}

func (c *Context) SamplerParameterf(sampler uint32, pname int32, param float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameterf_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLfloat(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 644,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameterf(c.c, C.GLuint(sampler), C.GLenum(pname), C.GLfloat(param))
	}
}

func (c *Context) SamplerParameterfv(sampler uint32, pname int32, param *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameterfv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = (*C.GLfloat)(unsafe.Pointer(param))

		c.push(C.gl_wrap_batch_func{
			jump_index: 645,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameterfv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(param)))
	}
}

func (c *Context) SamplerParameterIiv(sampler uint32, pname int32, param *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameterIiv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = (*C.GLint)(unsafe.Pointer(param))

		c.push(C.gl_wrap_batch_func{
			jump_index: 646,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameterIiv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(param)))
	}
}

func (c *Context) SamplerParameterIuiv(sampler uint32, pname int32, param *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSamplerParameterIuiv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = (*C.GLuint)(unsafe.Pointer(param))

		c.push(C.gl_wrap_batch_func{
			jump_index: 647,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSamplerParameterIuiv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(param)))
	}
}

func (c *Context) GetSamplerParameteriv(sampler uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSamplerParameteriv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 648,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSamplerParameteriv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetSamplerParameterIiv(sampler uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSamplerParameterIiv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 649,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSamplerParameterIiv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetSamplerParameterfv(sampler uint32, pname int32, params *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSamplerParameterfv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLfloat)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 650,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSamplerParameterfv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetSamplerParameterIuiv(sampler uint32, pname int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetSamplerParameterIuiv_args
		glWrapHandlerArgs.sampler = C.GLuint(sampler)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 651,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetSamplerParameterIuiv(c.c, C.GLuint(sampler), C.GLenum(pname), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) QueryCounter(id uint32, target int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glQueryCounter_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.target = C.GLenum(target)

		c.push(C.gl_wrap_batch_func{
			jump_index: 652,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glQueryCounter(c.c, C.GLuint(id), C.GLenum(target))
	}
}

func (c *Context) GetQueryObjecti64v(id uint32, pname int32, params *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryObjecti64v_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint64)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 653,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryObjecti64v(c.c, C.GLuint(id), C.GLenum(pname), (*C.GLint64)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetQueryObjectui64v(id uint32, pname int32, params *uint64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryObjectui64v_args
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLuint64)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 654,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryObjectui64v(c.c, C.GLuint(id), C.GLenum(pname), (*C.GLuint64)(unsafe.Pointer(params)))
	}
}

func (c *Context) VertexAttribDivisor(index uint32, divisor uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribDivisor_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.divisor = C.GLuint(divisor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 655,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribDivisor(c.c, C.GLuint(index), C.GLuint(divisor))
	}
}

func (c *Context) VertexAttribP1ui(index uint32, pType int32, normalized uint8, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP1ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 656,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP1ui(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), C.GLuint(value))
	}
}

func (c *Context) VertexAttribP1uiv(index uint32, pType int32, normalized uint8, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP1uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 657,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP1uiv(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) VertexAttribP2ui(index uint32, pType int32, normalized uint8, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP2ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 658,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP2ui(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), C.GLuint(value))
	}
}

func (c *Context) VertexAttribP2uiv(index uint32, pType int32, normalized uint8, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP2uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 659,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP2uiv(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) VertexAttribP3ui(index uint32, pType int32, normalized uint8, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP3ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 660,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP3ui(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), C.GLuint(value))
	}
}

func (c *Context) VertexAttribP3uiv(index uint32, pType int32, normalized uint8, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP3uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 661,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP3uiv(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) VertexAttribP4ui(index uint32, pType int32, normalized uint8, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP4ui_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 662,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP4ui(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), C.GLuint(value))
	}
}

func (c *Context) VertexAttribP4uiv(index uint32, pType int32, normalized uint8, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribP4uiv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 663,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribP4uiv(c.c, C.GLuint(index), C.GLenum(pType), C.GLboolean(normalized), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) VertexP2ui(pType int32, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexP2ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 664,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexP2ui(c.c, C.GLenum(pType), C.GLuint(value))
	}
}

func (c *Context) VertexP2uiv(pType int32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexP2uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 665,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexP2uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) VertexP3ui(pType int32, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexP3ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 666,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexP3ui(c.c, C.GLenum(pType), C.GLuint(value))
	}
}

func (c *Context) VertexP3uiv(pType int32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexP3uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 667,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexP3uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) VertexP4ui(pType int32, value uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexP4ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.value = C.GLuint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 668,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexP4ui(c.c, C.GLenum(pType), C.GLuint(value))
	}
}

func (c *Context) VertexP4uiv(pType int32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexP4uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 669,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexP4uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) TexCoordP1ui(pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP1ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 670,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP1ui(c.c, C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) TexCoordP1uiv(pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP1uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 671,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP1uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) TexCoordP2ui(pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP2ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 672,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP2ui(c.c, C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) TexCoordP2uiv(pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP2uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 673,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP2uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) TexCoordP3ui(pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP3ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 674,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP3ui(c.c, C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) TexCoordP3uiv(pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP3uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 675,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP3uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) TexCoordP4ui(pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP4ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 676,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP4ui(c.c, C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) TexCoordP4uiv(pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexCoordP4uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 677,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexCoordP4uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) MultiTexCoordP1ui(texture int32, pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP1ui_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 678,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP1ui(c.c, C.GLenum(texture), C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) MultiTexCoordP1uiv(texture int32, pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP1uiv_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 679,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP1uiv(c.c, C.GLenum(texture), C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) MultiTexCoordP2ui(texture int32, pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP2ui_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 680,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP2ui(c.c, C.GLenum(texture), C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) MultiTexCoordP2uiv(texture int32, pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP2uiv_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 681,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP2uiv(c.c, C.GLenum(texture), C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) MultiTexCoordP3ui(texture int32, pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP3ui_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 682,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP3ui(c.c, C.GLenum(texture), C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) MultiTexCoordP3uiv(texture int32, pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP3uiv_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 683,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP3uiv(c.c, C.GLenum(texture), C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) MultiTexCoordP4ui(texture int32, pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP4ui_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 684,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP4ui(c.c, C.GLenum(texture), C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) MultiTexCoordP4uiv(texture int32, pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiTexCoordP4uiv_args
		glWrapHandlerArgs.texture = C.GLenum(texture)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 685,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiTexCoordP4uiv(c.c, C.GLenum(texture), C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) NormalP3ui(pType int32, coords uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormalP3ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = C.GLuint(coords)

		c.push(C.gl_wrap_batch_func{
			jump_index: 686,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormalP3ui(c.c, C.GLenum(pType), C.GLuint(coords))
	}
}

func (c *Context) NormalP3uiv(pType int32, coords *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glNormalP3uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.coords = (*C.GLuint)(unsafe.Pointer(coords))

		c.push(C.gl_wrap_batch_func{
			jump_index: 687,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glNormalP3uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(coords)))
	}
}

func (c *Context) ColorP3ui(pType int32, color uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorP3ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.color = C.GLuint(color)

		c.push(C.gl_wrap_batch_func{
			jump_index: 688,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorP3ui(c.c, C.GLenum(pType), C.GLuint(color))
	}
}

func (c *Context) ColorP3uiv(pType int32, color *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorP3uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.color = (*C.GLuint)(unsafe.Pointer(color))

		c.push(C.gl_wrap_batch_func{
			jump_index: 689,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorP3uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(color)))
	}
}

func (c *Context) ColorP4ui(pType int32, color uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorP4ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.color = C.GLuint(color)

		c.push(C.gl_wrap_batch_func{
			jump_index: 690,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorP4ui(c.c, C.GLenum(pType), C.GLuint(color))
	}
}

func (c *Context) ColorP4uiv(pType int32, color *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glColorP4uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.color = (*C.GLuint)(unsafe.Pointer(color))

		c.push(C.gl_wrap_batch_func{
			jump_index: 691,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glColorP4uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(color)))
	}
}

func (c *Context) SecondaryColorP3ui(pType int32, color uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColorP3ui_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.color = C.GLuint(color)

		c.push(C.gl_wrap_batch_func{
			jump_index: 692,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColorP3ui(c.c, C.GLenum(pType), C.GLuint(color))
	}
}

func (c *Context) SecondaryColorP3uiv(pType int32, color *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glSecondaryColorP3uiv_args
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.color = (*C.GLuint)(unsafe.Pointer(color))

		c.push(C.gl_wrap_batch_func{
			jump_index: 693,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glSecondaryColorP3uiv(c.c, C.GLenum(pType), (*C.GLuint)(unsafe.Pointer(color)))
	}
}

func (c *Context) MinSampleShading(value float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMinSampleShading_args
		glWrapHandlerArgs.value = C.GLfloat(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 694,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMinSampleShading(c.c, C.GLfloat(value))
	}
}

func (c *Context) BlendEquationi(buf uint32, mode int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendEquationi_args
		glWrapHandlerArgs.buf = C.GLuint(buf)
		glWrapHandlerArgs.mode = C.GLenum(mode)

		c.push(C.gl_wrap_batch_func{
			jump_index: 695,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendEquationi(c.c, C.GLuint(buf), C.GLenum(mode))
	}
}

func (c *Context) BlendEquationSeparatei(buf uint32, modeRGB int32, modeAlpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendEquationSeparatei_args
		glWrapHandlerArgs.buf = C.GLuint(buf)
		glWrapHandlerArgs.modeRGB = C.GLenum(modeRGB)
		glWrapHandlerArgs.modeAlpha = C.GLenum(modeAlpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 696,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendEquationSeparatei(c.c, C.GLuint(buf), C.GLenum(modeRGB), C.GLenum(modeAlpha))
	}
}

func (c *Context) BlendFunci(buf uint32, src int32, dst int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendFunci_args
		glWrapHandlerArgs.buf = C.GLuint(buf)
		glWrapHandlerArgs.src = C.GLenum(src)
		glWrapHandlerArgs.dst = C.GLenum(dst)

		c.push(C.gl_wrap_batch_func{
			jump_index: 697,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendFunci(c.c, C.GLuint(buf), C.GLenum(src), C.GLenum(dst))
	}
}

func (c *Context) BlendFuncSeparatei(buf uint32, srcRGB int32, dstRGB int32, srcAlpha int32, dstAlpha int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBlendFuncSeparatei_args
		glWrapHandlerArgs.buf = C.GLuint(buf)
		glWrapHandlerArgs.srcRGB = C.GLenum(srcRGB)
		glWrapHandlerArgs.dstRGB = C.GLenum(dstRGB)
		glWrapHandlerArgs.srcAlpha = C.GLenum(srcAlpha)
		glWrapHandlerArgs.dstAlpha = C.GLenum(dstAlpha)

		c.push(C.gl_wrap_batch_func{
			jump_index: 698,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBlendFuncSeparatei(c.c, C.GLuint(buf), C.GLenum(srcRGB), C.GLenum(dstRGB), C.GLenum(srcAlpha), C.GLenum(dstAlpha))
	}
}

func (c *Context) DrawArraysIndirect(mode int32, indirect unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArraysIndirect_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.indirect = indirect

		c.push(C.gl_wrap_batch_func{
			jump_index: 699,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArraysIndirect(c.c, C.GLenum(mode), indirect)
	}
}

func (c *Context) DrawElementsIndirect(mode int32, pType int32, indirect unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsIndirect_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indirect = indirect

		c.push(C.gl_wrap_batch_func{
			jump_index: 700,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsIndirect(c.c, C.GLenum(mode), C.GLenum(pType), indirect)
	}
}

func (c *Context) Uniform1d(location int32, x float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1d_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.x = C.GLdouble(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 701,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1d(c.c, C.GLint(location), C.GLdouble(x))
	}
}

func (c *Context) Uniform2d(location int32, x float64, y float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2d_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 702,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2d(c.c, C.GLint(location), C.GLdouble(x), C.GLdouble(y))
	}
}

func (c *Context) Uniform3d(location int32, x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3d_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 703,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3d(c.c, C.GLint(location), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) Uniform4d(location int32, x float64, y float64, z float64, w float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4d_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)
		glWrapHandlerArgs.w = C.GLdouble(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 704,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4d(c.c, C.GLint(location), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z), C.GLdouble(w))
	}
}

func (c *Context) Uniform1dv(location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform1dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 705,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform1dv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform2dv(location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform2dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 706,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform2dv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform3dv(location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform3dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 707,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform3dv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) Uniform4dv(location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniform4dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 708,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniform4dv(c.c, C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 709,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 710,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 711,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2x3dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2x3dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 712,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2x3dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix2x4dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix2x4dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 713,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix2x4dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3x2dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3x2dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 714,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3x2dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix3x4dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix3x4dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 715,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix3x4dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4x2dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4x2dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 716,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4x2dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) UniformMatrix4x3dv(location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformMatrix4x3dv_args
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 717,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformMatrix4x3dv(c.c, C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) GetUniformdv(program uint32, location int32, params *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformdv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLdouble)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 718,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformdv(c.c, C.GLuint(program), C.GLint(location), (*C.GLdouble)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetActiveSubroutineUniformiv(program uint32, shadertype int32, index uint32, pname int32, values *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveSubroutineUniformiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.values = (*C.GLint)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 719,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveSubroutineUniformiv(c.c, C.GLuint(program), C.GLenum(shadertype), C.GLuint(index), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(values)))
	}
}

func (c *Context) GetActiveSubroutineUniformName(program uint32, shadertype int32, index uint32, bufsize uint32, length *uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveSubroutineUniformName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufsize = C.GLsizei(bufsize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 720,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveSubroutineUniformName(c.c, C.GLuint(program), C.GLenum(shadertype), C.GLuint(index), C.GLsizei(bufsize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetActiveSubroutineName(program uint32, shadertype int32, index uint32, bufsize uint32, length *uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveSubroutineName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufsize = C.GLsizei(bufsize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 721,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveSubroutineName(c.c, C.GLuint(program), C.GLenum(shadertype), C.GLuint(index), C.GLsizei(bufsize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) UniformSubroutinesuiv(shadertype int32, count uint32, indices *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUniformSubroutinesuiv_args
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.indices = (*C.GLuint)(unsafe.Pointer(indices))

		c.push(C.gl_wrap_batch_func{
			jump_index: 722,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUniformSubroutinesuiv(c.c, C.GLenum(shadertype), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(indices)))
	}
}

func (c *Context) GetUniformSubroutineuiv(shadertype int32, location int32, params *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetUniformSubroutineuiv_args
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.params = (*C.GLuint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 723,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetUniformSubroutineuiv(c.c, C.GLenum(shadertype), C.GLint(location), (*C.GLuint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetProgramStageiv(program uint32, shadertype int32, pname int32, values *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramStageiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.values = (*C.GLint)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 724,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramStageiv(c.c, C.GLuint(program), C.GLenum(shadertype), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(values)))
	}
}

func (c *Context) PatchParameteri(pname int32, value int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPatchParameteri_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.value = C.GLint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 725,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPatchParameteri(c.c, C.GLenum(pname), C.GLint(value))
	}
}

func (c *Context) PatchParameterfv(pname int32, values *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPatchParameterfv_args
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.values = (*C.GLfloat)(unsafe.Pointer(values))

		c.push(C.gl_wrap_batch_func{
			jump_index: 726,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPatchParameterfv(c.c, C.GLenum(pname), (*C.GLfloat)(unsafe.Pointer(values)))
	}
}

func (c *Context) BindTransformFeedback(target int32, id uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindTransformFeedback_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.id = C.GLuint(id)

		c.push(C.gl_wrap_batch_func{
			jump_index: 727,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindTransformFeedback(c.c, C.GLenum(target), C.GLuint(id))
	}
}

func (c *Context) DeleteTransformFeedbacks(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteTransformFeedbacks_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 728,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteTransformFeedbacks(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) GenTransformFeedbacks(n uint32, ids *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenTransformFeedbacks_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))

		c.push(C.gl_wrap_batch_func{
			jump_index: 729,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenTransformFeedbacks(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(ids)))
	}
}

func (c *Context) PauseTransformFeedback() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPauseTransformFeedback_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 730,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPauseTransformFeedback(c.c)
	}
}

func (c *Context) ResumeTransformFeedback() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glResumeTransformFeedback_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 731,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glResumeTransformFeedback(c.c)
	}
}

func (c *Context) DrawTransformFeedback(mode int32, id uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawTransformFeedback_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.id = C.GLuint(id)

		c.push(C.gl_wrap_batch_func{
			jump_index: 732,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawTransformFeedback(c.c, C.GLenum(mode), C.GLuint(id))
	}
}

func (c *Context) DrawTransformFeedbackStream(mode int32, id uint32, stream uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawTransformFeedbackStream_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.stream = C.GLuint(stream)

		c.push(C.gl_wrap_batch_func{
			jump_index: 733,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawTransformFeedbackStream(c.c, C.GLenum(mode), C.GLuint(id), C.GLuint(stream))
	}
}

func (c *Context) BeginQueryIndexed(target int32, index uint32, id uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBeginQueryIndexed_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.id = C.GLuint(id)

		c.push(C.gl_wrap_batch_func{
			jump_index: 734,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBeginQueryIndexed(c.c, C.GLenum(target), C.GLuint(index), C.GLuint(id))
	}
}

func (c *Context) EndQueryIndexed(target int32, index uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glEndQueryIndexed_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)

		c.push(C.gl_wrap_batch_func{
			jump_index: 735,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glEndQueryIndexed(c.c, C.GLenum(target), C.GLuint(index))
	}
}

func (c *Context) GetQueryIndexediv(target int32, index uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetQueryIndexediv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 736,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetQueryIndexediv(c.c, C.GLenum(target), C.GLuint(index), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) ReleaseShaderCompiler() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glReleaseShaderCompiler_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 737,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glReleaseShaderCompiler(c.c)
	}
}

func (c *Context) ShaderBinary(count uint32, shaders *uint32, binaryformat int32, binary unsafe.Pointer, length uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glShaderBinary_args
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.shaders = (*C.GLuint)(unsafe.Pointer(shaders))
		glWrapHandlerArgs.binaryformat = C.GLenum(binaryformat)
		glWrapHandlerArgs.binary = binary
		glWrapHandlerArgs.length = C.GLsizei(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 738,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glShaderBinary(c.c, C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(shaders)), C.GLenum(binaryformat), binary, C.GLsizei(length))
	}
}

func (c *Context) GetShaderPrecisionFormat(shadertype int32, precisiontype int32, pRange *int32, precision *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetShaderPrecisionFormat_args
		glWrapHandlerArgs.shadertype = C.GLenum(shadertype)
		glWrapHandlerArgs.precisiontype = C.GLenum(precisiontype)
		glWrapHandlerArgs._range = (*C.GLint)(unsafe.Pointer(pRange))
		glWrapHandlerArgs.precision = (*C.GLint)(unsafe.Pointer(precision))

		c.push(C.gl_wrap_batch_func{
			jump_index: 739,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetShaderPrecisionFormat(c.c, C.GLenum(shadertype), C.GLenum(precisiontype), (*C.GLint)(unsafe.Pointer(pRange)), (*C.GLint)(unsafe.Pointer(precision)))
	}
}

func (c *Context) DepthRangef(n float32, f float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthRangef_args
		glWrapHandlerArgs.n = C.GLfloat(n)
		glWrapHandlerArgs.f = C.GLfloat(f)

		c.push(C.gl_wrap_batch_func{
			jump_index: 740,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthRangef(c.c, C.GLfloat(n), C.GLfloat(f))
	}
}

func (c *Context) ClearDepthf(d float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearDepthf_args
		glWrapHandlerArgs.d = C.GLfloat(d)

		c.push(C.gl_wrap_batch_func{
			jump_index: 741,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearDepthf(c.c, C.GLfloat(d))
	}
}

func (c *Context) GetProgramBinary(program uint32, bufSize uint32, length *uint32, binaryFormat *int32, binary unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramBinary_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.binaryFormat = (*C.GLenum)(unsafe.Pointer(binaryFormat))
		glWrapHandlerArgs.binary = binary

		c.push(C.gl_wrap_batch_func{
			jump_index: 742,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramBinary(c.c, C.GLuint(program), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLenum)(unsafe.Pointer(binaryFormat)), binary)
	}
}

func (c *Context) ProgramBinary(program uint32, binaryFormat int32, binary unsafe.Pointer, length uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramBinary_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.binaryFormat = C.GLenum(binaryFormat)
		glWrapHandlerArgs.binary = binary
		glWrapHandlerArgs.length = C.GLsizei(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 743,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramBinary(c.c, C.GLuint(program), C.GLenum(binaryFormat), binary, C.GLsizei(length))
	}
}

func (c *Context) ProgramParameteri(program uint32, pname int32, value int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramParameteri_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.value = C.GLint(value)

		c.push(C.gl_wrap_batch_func{
			jump_index: 744,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramParameteri(c.c, C.GLuint(program), C.GLenum(pname), C.GLint(value))
	}
}

func (c *Context) UseProgramStages(pipeline uint32, stages uint32, program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glUseProgramStages_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.stages = C.GLbitfield(stages)
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 745,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glUseProgramStages(c.c, C.GLuint(pipeline), C.GLbitfield(stages), C.GLuint(program))
	}
}

func (c *Context) ActiveShaderProgram(pipeline uint32, program uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glActiveShaderProgram_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.program = C.GLuint(program)

		c.push(C.gl_wrap_batch_func{
			jump_index: 746,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glActiveShaderProgram(c.c, C.GLuint(pipeline), C.GLuint(program))
	}
}

func (c *Context) BindProgramPipeline(pipeline uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindProgramPipeline_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)

		c.push(C.gl_wrap_batch_func{
			jump_index: 747,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindProgramPipeline(c.c, C.GLuint(pipeline))
	}
}

func (c *Context) DeleteProgramPipelines(n uint32, pipelines *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDeleteProgramPipelines_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.pipelines = (*C.GLuint)(unsafe.Pointer(pipelines))

		c.push(C.gl_wrap_batch_func{
			jump_index: 748,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDeleteProgramPipelines(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(pipelines)))
	}
}

func (c *Context) GenProgramPipelines(n uint32, pipelines *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGenProgramPipelines_args
		glWrapHandlerArgs.n = C.GLsizei(n)
		glWrapHandlerArgs.pipelines = (*C.GLuint)(unsafe.Pointer(pipelines))

		c.push(C.gl_wrap_batch_func{
			jump_index: 749,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGenProgramPipelines(c.c, C.GLsizei(n), (*C.GLuint)(unsafe.Pointer(pipelines)))
	}
}

func (c *Context) GetProgramPipelineiv(pipeline uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramPipelineiv_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 750,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramPipelineiv(c.c, C.GLuint(pipeline), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) ProgramUniform1i(program uint32, location int32, v0 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 751,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0))
	}
}

func (c *Context) ProgramUniform1iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 752,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform1f(program uint32, location int32, v0 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 753,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0))
	}
}

func (c *Context) ProgramUniform1fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 754,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform1d(program uint32, location int32, v0 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1d_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLdouble(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 755,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1d(c.c, C.GLuint(program), C.GLint(location), C.GLdouble(v0))
	}
}

func (c *Context) ProgramUniform1dv(program uint32, location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 756,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform1ui(program uint32, location int32, v0 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)

		c.push(C.gl_wrap_batch_func{
			jump_index: 757,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0))
	}
}

func (c *Context) ProgramUniform1uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform1uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 758,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform1uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2i(program uint32, location int32, v0 int32, v1 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 759,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0), C.GLint(v1))
	}
}

func (c *Context) ProgramUniform2iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 760,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2f(program uint32, location int32, v0 float32, v1 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 761,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0), C.GLfloat(v1))
	}
}

func (c *Context) ProgramUniform2fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 762,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2d(program uint32, location int32, v0 float64, v1 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2d_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLdouble(v0)
		glWrapHandlerArgs.v1 = C.GLdouble(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 763,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2d(c.c, C.GLuint(program), C.GLint(location), C.GLdouble(v0), C.GLdouble(v1))
	}
}

func (c *Context) ProgramUniform2dv(program uint32, location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 764,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform2ui(program uint32, location int32, v0 uint32, v1 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)

		c.push(C.gl_wrap_batch_func{
			jump_index: 765,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0), C.GLuint(v1))
	}
}

func (c *Context) ProgramUniform2uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform2uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 766,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform2uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3i(program uint32, location int32, v0 int32, v1 int32, v2 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 767,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2))
	}
}

func (c *Context) ProgramUniform3iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 768,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3f(program uint32, location int32, v0 float32, v1 float32, v2 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 769,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2))
	}
}

func (c *Context) ProgramUniform3fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 770,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3d(program uint32, location int32, v0 float64, v1 float64, v2 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3d_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLdouble(v0)
		glWrapHandlerArgs.v1 = C.GLdouble(v1)
		glWrapHandlerArgs.v2 = C.GLdouble(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 771,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3d(c.c, C.GLuint(program), C.GLint(location), C.GLdouble(v0), C.GLdouble(v1), C.GLdouble(v2))
	}
}

func (c *Context) ProgramUniform3dv(program uint32, location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 772,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform3ui(program uint32, location int32, v0 uint32, v1 uint32, v2 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)

		c.push(C.gl_wrap_batch_func{
			jump_index: 773,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2))
	}
}

func (c *Context) ProgramUniform3uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform3uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 774,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform3uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4i(program uint32, location int32, v0 int32, v1 int32, v2 int32, v3 int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4i_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLint(v0)
		glWrapHandlerArgs.v1 = C.GLint(v1)
		glWrapHandlerArgs.v2 = C.GLint(v2)
		glWrapHandlerArgs.v3 = C.GLint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 775,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4i(c.c, C.GLuint(program), C.GLint(location), C.GLint(v0), C.GLint(v1), C.GLint(v2), C.GLint(v3))
	}
}

func (c *Context) ProgramUniform4iv(program uint32, location int32, count uint32, value *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4iv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 776,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4iv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4f(program uint32, location int32, v0 float32, v1 float32, v2 float32, v3 float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4f_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLfloat(v0)
		glWrapHandlerArgs.v1 = C.GLfloat(v1)
		glWrapHandlerArgs.v2 = C.GLfloat(v2)
		glWrapHandlerArgs.v3 = C.GLfloat(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 777,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4f(c.c, C.GLuint(program), C.GLint(location), C.GLfloat(v0), C.GLfloat(v1), C.GLfloat(v2), C.GLfloat(v3))
	}
}

func (c *Context) ProgramUniform4fv(program uint32, location int32, count uint32, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 778,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4d(program uint32, location int32, v0 float64, v1 float64, v2 float64, v3 float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4d_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLdouble(v0)
		glWrapHandlerArgs.v1 = C.GLdouble(v1)
		glWrapHandlerArgs.v2 = C.GLdouble(v2)
		glWrapHandlerArgs.v3 = C.GLdouble(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 779,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4d(c.c, C.GLuint(program), C.GLint(location), C.GLdouble(v0), C.GLdouble(v1), C.GLdouble(v2), C.GLdouble(v3))
	}
}

func (c *Context) ProgramUniform4dv(program uint32, location int32, count uint32, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 780,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniform4ui(program uint32, location int32, v0 uint32, v1 uint32, v2 uint32, v3 uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4ui_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.v0 = C.GLuint(v0)
		glWrapHandlerArgs.v1 = C.GLuint(v1)
		glWrapHandlerArgs.v2 = C.GLuint(v2)
		glWrapHandlerArgs.v3 = C.GLuint(v3)

		c.push(C.gl_wrap_batch_func{
			jump_index: 781,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4ui(c.c, C.GLuint(program), C.GLint(location), C.GLuint(v0), C.GLuint(v1), C.GLuint(v2), C.GLuint(v3))
	}
}

func (c *Context) ProgramUniform4uiv(program uint32, location int32, count uint32, value *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniform4uiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.value = (*C.GLuint)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 782,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniform4uiv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 783,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 784,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 785,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 786,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 787,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 788,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2x3fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2x3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 789,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2x3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3x2fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3x2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 790,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3x2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2x4fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2x4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 791,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2x4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4x2fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4x2fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 792,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4x2fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3x4fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3x4fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 793,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3x4fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4x3fv(program uint32, location int32, count uint32, transpose uint8, value *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4x3fv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLfloat)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 794,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4x3fv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLfloat)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2x3dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2x3dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 795,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2x3dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3x2dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3x2dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 796,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3x2dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix2x4dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix2x4dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 797,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix2x4dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4x2dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4x2dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 798,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4x2dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix3x4dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix3x4dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 799,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix3x4dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ProgramUniformMatrix4x3dv(program uint32, location int32, count uint32, transpose uint8, value *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glProgramUniformMatrix4x3dv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.location = C.GLint(location)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.transpose = C.GLboolean(transpose)
		glWrapHandlerArgs.value = (*C.GLdouble)(unsafe.Pointer(value))

		c.push(C.gl_wrap_batch_func{
			jump_index: 800,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glProgramUniformMatrix4x3dv(c.c, C.GLuint(program), C.GLint(location), C.GLsizei(count), C.GLboolean(transpose), (*C.GLdouble)(unsafe.Pointer(value)))
	}
}

func (c *Context) ValidateProgramPipeline(pipeline uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glValidateProgramPipeline_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)

		c.push(C.gl_wrap_batch_func{
			jump_index: 801,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glValidateProgramPipeline(c.c, C.GLuint(pipeline))
	}
}

func (c *Context) GetProgramPipelineInfoLog(pipeline uint32, bufSize uint32, length *uint32, infoLog *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramPipelineInfoLog_args
		glWrapHandlerArgs.pipeline = C.GLuint(pipeline)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.infoLog = (*C.GLchar)(unsafe.Pointer(infoLog))

		c.push(C.gl_wrap_batch_func{
			jump_index: 802,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramPipelineInfoLog(c.c, C.GLuint(pipeline), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(infoLog)))
	}
}

func (c *Context) VertexAttribL1d(index uint32, x float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL1d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)

		c.push(C.gl_wrap_batch_func{
			jump_index: 803,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL1d(c.c, C.GLuint(index), C.GLdouble(x))
	}
}

func (c *Context) VertexAttribL2d(index uint32, x float64, y float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL2d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)

		c.push(C.gl_wrap_batch_func{
			jump_index: 804,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL2d(c.c, C.GLuint(index), C.GLdouble(x), C.GLdouble(y))
	}
}

func (c *Context) VertexAttribL3d(index uint32, x float64, y float64, z float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL3d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 805,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL3d(c.c, C.GLuint(index), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z))
	}
}

func (c *Context) VertexAttribL4d(index uint32, x float64, y float64, z float64, w float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL4d_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLdouble(x)
		glWrapHandlerArgs.y = C.GLdouble(y)
		glWrapHandlerArgs.z = C.GLdouble(z)
		glWrapHandlerArgs.w = C.GLdouble(w)

		c.push(C.gl_wrap_batch_func{
			jump_index: 806,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL4d(c.c, C.GLuint(index), C.GLdouble(x), C.GLdouble(y), C.GLdouble(z), C.GLdouble(w))
	}
}

func (c *Context) VertexAttribL1dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL1dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 807,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL1dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribL2dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL2dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 808,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL2dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribL3dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL3dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 809,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL3dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribL4dv(index uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribL4dv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 810,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribL4dv(c.c, C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) VertexAttribLPointer(index uint32, size int32, pType int32, stride uint32, pointer unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribLPointer_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.stride = C.GLsizei(stride)
		glWrapHandlerArgs.pointer = pointer

		c.push(C.gl_wrap_batch_func{
			jump_index: 811,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribLPointer(c.c, C.GLuint(index), C.GLint(size), C.GLenum(pType), C.GLsizei(stride), pointer)
	}
}

func (c *Context) GetVertexAttribLdv(index uint32, pname int32, params *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetVertexAttribLdv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLdouble)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 812,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetVertexAttribLdv(c.c, C.GLuint(index), C.GLenum(pname), (*C.GLdouble)(unsafe.Pointer(params)))
	}
}

func (c *Context) ViewportArrayv(first uint32, count uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glViewportArrayv_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 813,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glViewportArrayv(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) ViewportIndexedf(index uint32, x float32, y float32, w float32, h float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glViewportIndexedf_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.x = C.GLfloat(x)
		glWrapHandlerArgs.y = C.GLfloat(y)
		glWrapHandlerArgs.w = C.GLfloat(w)
		glWrapHandlerArgs.h = C.GLfloat(h)

		c.push(C.gl_wrap_batch_func{
			jump_index: 814,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glViewportIndexedf(c.c, C.GLuint(index), C.GLfloat(x), C.GLfloat(y), C.GLfloat(w), C.GLfloat(h))
	}
}

func (c *Context) ViewportIndexedfv(index uint32, v *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glViewportIndexedfv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLfloat)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 815,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glViewportIndexedfv(c.c, C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(v)))
	}
}

func (c *Context) ScissorArrayv(first uint32, count uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScissorArrayv_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 816,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScissorArrayv(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) ScissorIndexed(index uint32, left int32, bottom int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScissorIndexed_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.left = C.GLint(left)
		glWrapHandlerArgs.bottom = C.GLint(bottom)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 817,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScissorIndexed(c.c, C.GLuint(index), C.GLint(left), C.GLint(bottom), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) ScissorIndexedv(index uint32, v *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glScissorIndexedv_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.v = (*C.GLint)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 818,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glScissorIndexedv(c.c, C.GLuint(index), (*C.GLint)(unsafe.Pointer(v)))
	}
}

func (c *Context) DepthRangeArrayv(first uint32, count uint32, v *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthRangeArrayv_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.v = (*C.GLdouble)(unsafe.Pointer(v))

		c.push(C.gl_wrap_batch_func{
			jump_index: 819,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthRangeArrayv(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLdouble)(unsafe.Pointer(v)))
	}
}

func (c *Context) DepthRangeIndexed(index uint32, n float64, f float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDepthRangeIndexed_args
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.n = C.GLdouble(n)
		glWrapHandlerArgs.f = C.GLdouble(f)

		c.push(C.gl_wrap_batch_func{
			jump_index: 820,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDepthRangeIndexed(c.c, C.GLuint(index), C.GLdouble(n), C.GLdouble(f))
	}
}

func (c *Context) GetFloati_v(target int32, index uint32, data *float32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFloati_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLfloat)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 821,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFloati_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLfloat)(unsafe.Pointer(data)))
	}
}

func (c *Context) GetDoublei_v(target int32, index uint32, data *float64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetDoublei_v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.data = (*C.GLdouble)(unsafe.Pointer(data))

		c.push(C.gl_wrap_batch_func{
			jump_index: 822,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetDoublei_v(c.c, C.GLenum(target), C.GLuint(index), (*C.GLdouble)(unsafe.Pointer(data)))
	}
}

func (c *Context) DrawArraysInstancedBaseInstance(mode int32, first int32, count uint32, instancecount uint32, baseinstance uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawArraysInstancedBaseInstance_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.first = C.GLint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)
		glWrapHandlerArgs.baseinstance = C.GLuint(baseinstance)

		c.push(C.gl_wrap_batch_func{
			jump_index: 823,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawArraysInstancedBaseInstance(c.c, C.GLenum(mode), C.GLint(first), C.GLsizei(count), C.GLsizei(instancecount), C.GLuint(baseinstance))
	}
}

func (c *Context) DrawElementsInstancedBaseInstance(mode int32, count uint32, pType int32, indices unsafe.Pointer, instancecount uint32, baseinstance uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsInstancedBaseInstance_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)
		glWrapHandlerArgs.baseinstance = C.GLuint(baseinstance)

		c.push(C.gl_wrap_batch_func{
			jump_index: 824,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsInstancedBaseInstance(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices, C.GLsizei(instancecount), C.GLuint(baseinstance))
	}
}

func (c *Context) DrawElementsInstancedBaseVertexBaseInstance(mode int32, count uint32, pType int32, indices unsafe.Pointer, instancecount uint32, basevertex int32, baseinstance uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawElementsInstancedBaseVertexBaseInstance_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indices = indices
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)
		glWrapHandlerArgs.basevertex = C.GLint(basevertex)
		glWrapHandlerArgs.baseinstance = C.GLuint(baseinstance)

		c.push(C.gl_wrap_batch_func{
			jump_index: 825,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawElementsInstancedBaseVertexBaseInstance(c.c, C.GLenum(mode), C.GLsizei(count), C.GLenum(pType), indices, C.GLsizei(instancecount), C.GLint(basevertex), C.GLuint(baseinstance))
	}
}

func (c *Context) GetInternalformativ(target int32, internalformat int32, pname int32, bufSize uint32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInternalformativ_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 826,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInternalformativ(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLenum(pname), C.GLsizei(bufSize), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetActiveAtomicCounterBufferiv(program uint32, bufferIndex uint32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetActiveAtomicCounterBufferiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.bufferIndex = C.GLuint(bufferIndex)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 827,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetActiveAtomicCounterBufferiv(c.c, C.GLuint(program), C.GLuint(bufferIndex), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) BindImageTexture(unit uint32, texture uint32, level int32, layered uint8, layer int32, access int32, format int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindImageTexture_args
		glWrapHandlerArgs.unit = C.GLuint(unit)
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.layered = C.GLboolean(layered)
		glWrapHandlerArgs.layer = C.GLint(layer)
		glWrapHandlerArgs.access = C.GLenum(access)
		glWrapHandlerArgs.format = C.GLenum(format)

		c.push(C.gl_wrap_batch_func{
			jump_index: 828,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindImageTexture(c.c, C.GLuint(unit), C.GLuint(texture), C.GLint(level), C.GLboolean(layered), C.GLint(layer), C.GLenum(access), C.GLenum(format))
	}
}

func (c *Context) MemoryBarrier(barriers uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMemoryBarrier_args
		glWrapHandlerArgs.barriers = C.GLbitfield(barriers)

		c.push(C.gl_wrap_batch_func{
			jump_index: 829,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMemoryBarrier(c.c, C.GLbitfield(barriers))
	}
}

func (c *Context) TexStorage1D(target int32, levels uint32, internalformat int32, width uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage1D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.levels = C.GLsizei(levels)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)

		c.push(C.gl_wrap_batch_func{
			jump_index: 830,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage1D(c.c, C.GLenum(target), C.GLsizei(levels), C.GLenum(internalformat), C.GLsizei(width))
	}
}

func (c *Context) TexStorage2D(target int32, levels uint32, internalformat int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage2D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.levels = C.GLsizei(levels)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 831,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage2D(c.c, C.GLenum(target), C.GLsizei(levels), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) TexStorage3D(target int32, levels uint32, internalformat int32, width uint32, height uint32, depth uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage3D_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.levels = C.GLsizei(levels)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)

		c.push(C.gl_wrap_batch_func{
			jump_index: 832,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage3D(c.c, C.GLenum(target), C.GLsizei(levels), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth))
	}
}

func (c *Context) DrawTransformFeedbackInstanced(mode int32, id uint32, instancecount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawTransformFeedbackInstanced_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 833,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawTransformFeedbackInstanced(c.c, C.GLenum(mode), C.GLuint(id), C.GLsizei(instancecount))
	}
}

func (c *Context) DrawTransformFeedbackStreamInstanced(mode int32, id uint32, stream uint32, instancecount uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDrawTransformFeedbackStreamInstanced_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.stream = C.GLuint(stream)
		glWrapHandlerArgs.instancecount = C.GLsizei(instancecount)

		c.push(C.gl_wrap_batch_func{
			jump_index: 834,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDrawTransformFeedbackStreamInstanced(c.c, C.GLenum(mode), C.GLuint(id), C.GLuint(stream), C.GLsizei(instancecount))
	}
}

func (c *Context) ClearBufferData(target int32, internalformat int32, format int32, pType int32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 835,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferData(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLenum(format), C.GLenum(pType), data)
	}
}

func (c *Context) ClearBufferSubData(target int32, internalformat int32, offset uintptr, size uintptr, format int32, pType int32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearBufferSubData_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 836,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearBufferSubData(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLintptr(offset), C.GLsizeiptr(size), C.GLenum(format), C.GLenum(pType), data)
	}
}

func (c *Context) DispatchCompute(num_groups_x uint32, num_groups_y uint32, num_groups_z uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDispatchCompute_args
		glWrapHandlerArgs.num_groups_x = C.GLuint(num_groups_x)
		glWrapHandlerArgs.num_groups_y = C.GLuint(num_groups_y)
		glWrapHandlerArgs.num_groups_z = C.GLuint(num_groups_z)

		c.push(C.gl_wrap_batch_func{
			jump_index: 837,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDispatchCompute(c.c, C.GLuint(num_groups_x), C.GLuint(num_groups_y), C.GLuint(num_groups_z))
	}
}

func (c *Context) DispatchComputeIndirect(indirect uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDispatchComputeIndirect_args
		glWrapHandlerArgs.indirect = C.GLintptr(indirect)

		c.push(C.gl_wrap_batch_func{
			jump_index: 838,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDispatchComputeIndirect(c.c, C.GLintptr(indirect))
	}
}

func (c *Context) CopyImageSubData(srcName uint32, srcTarget int32, srcLevel int32, srcX int32, srcY int32, srcZ int32, dstName uint32, dstTarget int32, dstLevel int32, dstX int32, dstY int32, dstZ int32, srcWidth uint32, srcHeight uint32, srcDepth uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glCopyImageSubData_args
		glWrapHandlerArgs.srcName = C.GLuint(srcName)
		glWrapHandlerArgs.srcTarget = C.GLenum(srcTarget)
		glWrapHandlerArgs.srcLevel = C.GLint(srcLevel)
		glWrapHandlerArgs.srcX = C.GLint(srcX)
		glWrapHandlerArgs.srcY = C.GLint(srcY)
		glWrapHandlerArgs.srcZ = C.GLint(srcZ)
		glWrapHandlerArgs.dstName = C.GLuint(dstName)
		glWrapHandlerArgs.dstTarget = C.GLenum(dstTarget)
		glWrapHandlerArgs.dstLevel = C.GLint(dstLevel)
		glWrapHandlerArgs.dstX = C.GLint(dstX)
		glWrapHandlerArgs.dstY = C.GLint(dstY)
		glWrapHandlerArgs.dstZ = C.GLint(dstZ)
		glWrapHandlerArgs.srcWidth = C.GLsizei(srcWidth)
		glWrapHandlerArgs.srcHeight = C.GLsizei(srcHeight)
		glWrapHandlerArgs.srcDepth = C.GLsizei(srcDepth)

		c.push(C.gl_wrap_batch_func{
			jump_index: 839,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glCopyImageSubData(c.c, C.GLuint(srcName), C.GLenum(srcTarget), C.GLint(srcLevel), C.GLint(srcX), C.GLint(srcY), C.GLint(srcZ), C.GLuint(dstName), C.GLenum(dstTarget), C.GLint(dstLevel), C.GLint(dstX), C.GLint(dstY), C.GLint(dstZ), C.GLsizei(srcWidth), C.GLsizei(srcHeight), C.GLsizei(srcDepth))
	}
}

func (c *Context) FramebufferParameteri(target int32, pname int32, param int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glFramebufferParameteri_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.param = C.GLint(param)

		c.push(C.gl_wrap_batch_func{
			jump_index: 840,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glFramebufferParameteri(c.c, C.GLenum(target), C.GLenum(pname), C.GLint(param))
	}
}

func (c *Context) GetFramebufferParameteriv(target int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetFramebufferParameteriv_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 841,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetFramebufferParameteriv(c.c, C.GLenum(target), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetInternalformati64v(target int32, internalformat int32, pname int32, bufSize uint32, params *int64) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetInternalformati64v_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.params = (*C.GLint64)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 842,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetInternalformati64v(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLenum(pname), C.GLsizei(bufSize), (*C.GLint64)(unsafe.Pointer(params)))
	}
}

func (c *Context) InvalidateTexSubImage(texture uint32, level int32, xoffset int32, yoffset int32, zoffset int32, width uint32, height uint32, depth uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateTexSubImage_args
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)

		c.push(C.gl_wrap_batch_func{
			jump_index: 843,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateTexSubImage(c.c, C.GLuint(texture), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth))
	}
}

func (c *Context) InvalidateTexImage(texture uint32, level int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateTexImage_args
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)

		c.push(C.gl_wrap_batch_func{
			jump_index: 844,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateTexImage(c.c, C.GLuint(texture), C.GLint(level))
	}
}

func (c *Context) InvalidateBufferSubData(buffer uint32, offset uintptr, length uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateBufferSubData_args
		glWrapHandlerArgs.buffer = C.GLuint(buffer)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.length = C.GLsizeiptr(length)

		c.push(C.gl_wrap_batch_func{
			jump_index: 845,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateBufferSubData(c.c, C.GLuint(buffer), C.GLintptr(offset), C.GLsizeiptr(length))
	}
}

func (c *Context) InvalidateBufferData(buffer uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateBufferData_args
		glWrapHandlerArgs.buffer = C.GLuint(buffer)

		c.push(C.gl_wrap_batch_func{
			jump_index: 846,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateBufferData(c.c, C.GLuint(buffer))
	}
}

func (c *Context) InvalidateFramebuffer(target int32, numAttachments uint32, attachments *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateFramebuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.numAttachments = C.GLsizei(numAttachments)
		glWrapHandlerArgs.attachments = (*C.GLenum)(unsafe.Pointer(attachments))

		c.push(C.gl_wrap_batch_func{
			jump_index: 847,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateFramebuffer(c.c, C.GLenum(target), C.GLsizei(numAttachments), (*C.GLenum)(unsafe.Pointer(attachments)))
	}
}

func (c *Context) InvalidateSubFramebuffer(target int32, numAttachments uint32, attachments *int32, x int32, y int32, width uint32, height uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glInvalidateSubFramebuffer_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.numAttachments = C.GLsizei(numAttachments)
		glWrapHandlerArgs.attachments = (*C.GLenum)(unsafe.Pointer(attachments))
		glWrapHandlerArgs.x = C.GLint(x)
		glWrapHandlerArgs.y = C.GLint(y)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)

		c.push(C.gl_wrap_batch_func{
			jump_index: 848,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glInvalidateSubFramebuffer(c.c, C.GLenum(target), C.GLsizei(numAttachments), (*C.GLenum)(unsafe.Pointer(attachments)), C.GLint(x), C.GLint(y), C.GLsizei(width), C.GLsizei(height))
	}
}

func (c *Context) MultiDrawArraysIndirect(mode int32, indirect unsafe.Pointer, drawcount uint32, stride uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiDrawArraysIndirect_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs.indirect = indirect
		glWrapHandlerArgs.drawcount = C.GLsizei(drawcount)
		glWrapHandlerArgs.stride = C.GLsizei(stride)

		c.push(C.gl_wrap_batch_func{
			jump_index: 849,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiDrawArraysIndirect(c.c, C.GLenum(mode), indirect, C.GLsizei(drawcount), C.GLsizei(stride))
	}
}

func (c *Context) MultiDrawElementsIndirect(mode int32, pType int32, indirect unsafe.Pointer, drawcount uint32, stride uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glMultiDrawElementsIndirect_args
		glWrapHandlerArgs.mode = C.GLenum(mode)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.indirect = indirect
		glWrapHandlerArgs.drawcount = C.GLsizei(drawcount)
		glWrapHandlerArgs.stride = C.GLsizei(stride)

		c.push(C.gl_wrap_batch_func{
			jump_index: 850,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glMultiDrawElementsIndirect(c.c, C.GLenum(mode), C.GLenum(pType), indirect, C.GLsizei(drawcount), C.GLsizei(stride))
	}
}

func (c *Context) GetProgramInterfaceiv(program uint32, programInterface int32, pname int32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramInterfaceiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.programInterface = C.GLenum(programInterface)
		glWrapHandlerArgs.pname = C.GLenum(pname)
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 851,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramInterfaceiv(c.c, C.GLuint(program), C.GLenum(programInterface), C.GLenum(pname), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) GetProgramResourceName(program uint32, programInterface int32, index uint32, bufSize uint32, length *uint32, name *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramResourceName_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.programInterface = C.GLenum(programInterface)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.name = (*C.GLchar)(unsafe.Pointer(name))

		c.push(C.gl_wrap_batch_func{
			jump_index: 852,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramResourceName(c.c, C.GLuint(program), C.GLenum(programInterface), C.GLuint(index), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(name)))
	}
}

func (c *Context) GetProgramResourceiv(program uint32, programInterface int32, index uint32, propCount uint32, props *int32, bufSize uint32, length *uint32, params *int32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetProgramResourceiv_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.programInterface = C.GLenum(programInterface)
		glWrapHandlerArgs.index = C.GLuint(index)
		glWrapHandlerArgs.propCount = C.GLsizei(propCount)
		glWrapHandlerArgs.props = (*C.GLenum)(unsafe.Pointer(props))
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.params = (*C.GLint)(unsafe.Pointer(params))

		c.push(C.gl_wrap_batch_func{
			jump_index: 853,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetProgramResourceiv(c.c, C.GLuint(program), C.GLenum(programInterface), C.GLuint(index), C.GLsizei(propCount), (*C.GLenum)(unsafe.Pointer(props)), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLint)(unsafe.Pointer(params)))
	}
}

func (c *Context) ShaderStorageBlockBinding(program uint32, storageBlockIndex uint32, storageBlockBinding uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glShaderStorageBlockBinding_args
		glWrapHandlerArgs.program = C.GLuint(program)
		glWrapHandlerArgs.storageBlockIndex = C.GLuint(storageBlockIndex)
		glWrapHandlerArgs.storageBlockBinding = C.GLuint(storageBlockBinding)

		c.push(C.gl_wrap_batch_func{
			jump_index: 854,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glShaderStorageBlockBinding(c.c, C.GLuint(program), C.GLuint(storageBlockIndex), C.GLuint(storageBlockBinding))
	}
}

func (c *Context) TexBufferRange(target int32, internalformat int32, buffer uint32, offset uintptr, size uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexBufferRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)

		c.push(C.gl_wrap_batch_func{
			jump_index: 855,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexBufferRange(c.c, C.GLenum(target), C.GLenum(internalformat), C.GLuint(buffer), C.GLintptr(offset), C.GLsizeiptr(size))
	}
}

func (c *Context) TexStorage2DMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32, fixedsamplelocations uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage2DMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.fixedsamplelocations = C.GLboolean(fixedsamplelocations)

		c.push(C.gl_wrap_batch_func{
			jump_index: 856,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage2DMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLboolean(fixedsamplelocations))
	}
}

func (c *Context) TexStorage3DMultisample(target int32, samples uint32, internalformat int32, width uint32, height uint32, depth uint32, fixedsamplelocations uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTexStorage3DMultisample_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.samples = C.GLsizei(samples)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.fixedsamplelocations = C.GLboolean(fixedsamplelocations)

		c.push(C.gl_wrap_batch_func{
			jump_index: 857,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTexStorage3DMultisample(c.c, C.GLenum(target), C.GLsizei(samples), C.GLenum(internalformat), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLboolean(fixedsamplelocations))
	}
}

func (c *Context) TextureView(texture uint32, target int32, origtexture uint32, internalformat int32, minlevel uint32, numlevels uint32, minlayer uint32, numlayers uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glTextureView_args
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.origtexture = C.GLuint(origtexture)
		glWrapHandlerArgs.internalformat = C.GLenum(internalformat)
		glWrapHandlerArgs.minlevel = C.GLuint(minlevel)
		glWrapHandlerArgs.numlevels = C.GLuint(numlevels)
		glWrapHandlerArgs.minlayer = C.GLuint(minlayer)
		glWrapHandlerArgs.numlayers = C.GLuint(numlayers)

		c.push(C.gl_wrap_batch_func{
			jump_index: 858,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glTextureView(c.c, C.GLuint(texture), C.GLenum(target), C.GLuint(origtexture), C.GLenum(internalformat), C.GLuint(minlevel), C.GLuint(numlevels), C.GLuint(minlayer), C.GLuint(numlayers))
	}
}

func (c *Context) BindVertexBuffer(bindingindex uint32, buffer uint32, offset uintptr, stride uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindVertexBuffer_args
		glWrapHandlerArgs.bindingindex = C.GLuint(bindingindex)
		glWrapHandlerArgs.buffer = C.GLuint(buffer)
		glWrapHandlerArgs.offset = C.GLintptr(offset)
		glWrapHandlerArgs.stride = C.GLsizei(stride)

		c.push(C.gl_wrap_batch_func{
			jump_index: 859,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindVertexBuffer(c.c, C.GLuint(bindingindex), C.GLuint(buffer), C.GLintptr(offset), C.GLsizei(stride))
	}
}

func (c *Context) VertexAttribFormat(attribindex uint32, size int32, pType int32, normalized uint8, relativeoffset uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribFormat_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.normalized = C.GLboolean(normalized)
		glWrapHandlerArgs.relativeoffset = C.GLuint(relativeoffset)

		c.push(C.gl_wrap_batch_func{
			jump_index: 860,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribFormat(c.c, C.GLuint(attribindex), C.GLint(size), C.GLenum(pType), C.GLboolean(normalized), C.GLuint(relativeoffset))
	}
}

func (c *Context) VertexAttribIFormat(attribindex uint32, size int32, pType int32, relativeoffset uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribIFormat_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.relativeoffset = C.GLuint(relativeoffset)

		c.push(C.gl_wrap_batch_func{
			jump_index: 861,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribIFormat(c.c, C.GLuint(attribindex), C.GLint(size), C.GLenum(pType), C.GLuint(relativeoffset))
	}
}

func (c *Context) VertexAttribLFormat(attribindex uint32, size int32, pType int32, relativeoffset uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribLFormat_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.size = C.GLint(size)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.relativeoffset = C.GLuint(relativeoffset)

		c.push(C.gl_wrap_batch_func{
			jump_index: 862,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribLFormat(c.c, C.GLuint(attribindex), C.GLint(size), C.GLenum(pType), C.GLuint(relativeoffset))
	}
}

func (c *Context) VertexAttribBinding(attribindex uint32, bindingindex uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexAttribBinding_args
		glWrapHandlerArgs.attribindex = C.GLuint(attribindex)
		glWrapHandlerArgs.bindingindex = C.GLuint(bindingindex)

		c.push(C.gl_wrap_batch_func{
			jump_index: 863,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexAttribBinding(c.c, C.GLuint(attribindex), C.GLuint(bindingindex))
	}
}

func (c *Context) VertexBindingDivisor(bindingindex uint32, divisor uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glVertexBindingDivisor_args
		glWrapHandlerArgs.bindingindex = C.GLuint(bindingindex)
		glWrapHandlerArgs.divisor = C.GLuint(divisor)

		c.push(C.gl_wrap_batch_func{
			jump_index: 864,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glVertexBindingDivisor(c.c, C.GLuint(bindingindex), C.GLuint(divisor))
	}
}

func (c *Context) DebugMessageControl(source int32, pType int32, severity int32, count uint32, ids *uint32, enabled uint8) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDebugMessageControl_args
		glWrapHandlerArgs.source = C.GLenum(source)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.severity = C.GLenum(severity)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.ids = (*C.GLuint)(unsafe.Pointer(ids))
		glWrapHandlerArgs.enabled = C.GLboolean(enabled)

		c.push(C.gl_wrap_batch_func{
			jump_index: 865,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDebugMessageControl(c.c, C.GLenum(source), C.GLenum(pType), C.GLenum(severity), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(ids)), C.GLboolean(enabled))
	}
}

func (c *Context) DebugMessageInsert(source int32, pType int32, id uint32, severity int32, length uint32, buf *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDebugMessageInsert_args
		glWrapHandlerArgs.source = C.GLenum(source)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.severity = C.GLenum(severity)
		glWrapHandlerArgs.length = C.GLsizei(length)
		glWrapHandlerArgs.buf = (*C.GLchar)(unsafe.Pointer(buf))

		c.push(C.gl_wrap_batch_func{
			jump_index: 866,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDebugMessageInsert(c.c, C.GLenum(source), C.GLenum(pType), C.GLuint(id), C.GLenum(severity), C.GLsizei(length), (*C.GLchar)(unsafe.Pointer(buf)))
	}
}

func (c *Context) DebugMessageCallback(callback DEBUGPROC, userParam unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glDebugMessageCallback_args
		glWrapHandlerArgs.callback = C.GLDEBUGPROC(callback)
		glWrapHandlerArgs.userParam = userParam

		c.push(C.gl_wrap_batch_func{
			jump_index: 867,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glDebugMessageCallback(c.c, C.GLDEBUGPROC(callback), userParam)
	}
}

func (c *Context) PushDebugGroup(source int32, id uint32, length uint32, message *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPushDebugGroup_args
		glWrapHandlerArgs.source = C.GLenum(source)
		glWrapHandlerArgs.id = C.GLuint(id)
		glWrapHandlerArgs.length = C.GLsizei(length)
		glWrapHandlerArgs.message = (*C.GLchar)(unsafe.Pointer(message))

		c.push(C.gl_wrap_batch_func{
			jump_index: 868,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPushDebugGroup(c.c, C.GLenum(source), C.GLuint(id), C.GLsizei(length), (*C.GLchar)(unsafe.Pointer(message)))
	}
}

func (c *Context) PopDebugGroup() {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glPopDebugGroup_args

		c.push(C.gl_wrap_batch_func{
			jump_index: 869,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glPopDebugGroup(c.c)
	}
}

func (c *Context) ObjectLabel(identifier int32, name uint32, length uint32, label *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glObjectLabel_args
		glWrapHandlerArgs.identifier = C.GLenum(identifier)
		glWrapHandlerArgs.name = C.GLuint(name)
		glWrapHandlerArgs.length = C.GLsizei(length)
		glWrapHandlerArgs.label = (*C.GLchar)(unsafe.Pointer(label))

		c.push(C.gl_wrap_batch_func{
			jump_index: 870,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glObjectLabel(c.c, C.GLenum(identifier), C.GLuint(name), C.GLsizei(length), (*C.GLchar)(unsafe.Pointer(label)))
	}
}

func (c *Context) GetObjectLabel(identifier int32, name uint32, bufSize uint32, length *uint32, label *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetObjectLabel_args
		glWrapHandlerArgs.identifier = C.GLenum(identifier)
		glWrapHandlerArgs.name = C.GLuint(name)
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.label = (*C.GLchar)(unsafe.Pointer(label))

		c.push(C.gl_wrap_batch_func{
			jump_index: 871,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetObjectLabel(c.c, C.GLenum(identifier), C.GLuint(name), C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(label)))
	}
}

func (c *Context) ObjectPtrLabel(ptr unsafe.Pointer, length uint32, label *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glObjectPtrLabel_args
		glWrapHandlerArgs.ptr = ptr
		glWrapHandlerArgs.length = C.GLsizei(length)
		glWrapHandlerArgs.label = (*C.GLchar)(unsafe.Pointer(label))

		c.push(C.gl_wrap_batch_func{
			jump_index: 872,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glObjectPtrLabel(c.c, ptr, C.GLsizei(length), (*C.GLchar)(unsafe.Pointer(label)))
	}
}

func (c *Context) GetObjectPtrLabel(ptr unsafe.Pointer, bufSize uint32, length *uint32, label *byte) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glGetObjectPtrLabel_args
		glWrapHandlerArgs.ptr = ptr
		glWrapHandlerArgs.bufSize = C.GLsizei(bufSize)
		glWrapHandlerArgs.length = (*C.GLsizei)(unsafe.Pointer(length))
		glWrapHandlerArgs.label = (*C.GLchar)(unsafe.Pointer(label))

		c.push(C.gl_wrap_batch_func{
			jump_index: 873,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glGetObjectPtrLabel(c.c, ptr, C.GLsizei(bufSize), (*C.GLsizei)(unsafe.Pointer(length)), (*C.GLchar)(unsafe.Pointer(label)))
	}
}

func (c *Context) BufferStorage(target int32, size uintptr, data unsafe.Pointer, flags uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBufferStorage_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.size = C.GLsizeiptr(size)
		glWrapHandlerArgs.data = data
		glWrapHandlerArgs.flags = C.GLbitfield(flags)

		c.push(C.gl_wrap_batch_func{
			jump_index: 874,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBufferStorage(c.c, C.GLenum(target), C.GLsizeiptr(size), data, C.GLbitfield(flags))
	}
}

func (c *Context) ClearTexImage(texture uint32, level int32, format int32, pType int32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearTexImage_args
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 875,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearTexImage(c.c, C.GLuint(texture), C.GLint(level), C.GLenum(format), C.GLenum(pType), data)
	}
}

func (c *Context) ClearTexSubImage(texture uint32, level int32, xoffset int32, yoffset int32, zoffset int32, width uint32, height uint32, depth uint32, format int32, pType int32, data unsafe.Pointer) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glClearTexSubImage_args
		glWrapHandlerArgs.texture = C.GLuint(texture)
		glWrapHandlerArgs.level = C.GLint(level)
		glWrapHandlerArgs.xoffset = C.GLint(xoffset)
		glWrapHandlerArgs.yoffset = C.GLint(yoffset)
		glWrapHandlerArgs.zoffset = C.GLint(zoffset)
		glWrapHandlerArgs.width = C.GLsizei(width)
		glWrapHandlerArgs.height = C.GLsizei(height)
		glWrapHandlerArgs.depth = C.GLsizei(depth)
		glWrapHandlerArgs.format = C.GLenum(format)
		glWrapHandlerArgs._type = C.GLenum(pType)
		glWrapHandlerArgs.data = data

		c.push(C.gl_wrap_batch_func{
			jump_index: 876,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glClearTexSubImage(c.c, C.GLuint(texture), C.GLint(level), C.GLint(xoffset), C.GLint(yoffset), C.GLint(zoffset), C.GLsizei(width), C.GLsizei(height), C.GLsizei(depth), C.GLenum(format), C.GLenum(pType), data)
	}
}

func (c *Context) BindBuffersBase(target int32, first uint32, count uint32, buffers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBuffersBase_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 877,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBuffersBase(c.c, C.GLenum(target), C.GLuint(first), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(buffers)))
	}
}

func (c *Context) BindBuffersRange(target int32, first uint32, count uint32, buffers *uint32, offsets *uintptr, sizes *uintptr) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindBuffersRange_args
		glWrapHandlerArgs.target = C.GLenum(target)
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))
		glWrapHandlerArgs.offsets = (*C.GLintptr)(unsafe.Pointer(offsets))
		glWrapHandlerArgs.sizes = (*C.GLsizeiptr)(unsafe.Pointer(sizes))

		c.push(C.gl_wrap_batch_func{
			jump_index: 878,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindBuffersRange(c.c, C.GLenum(target), C.GLuint(first), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(buffers)), (*C.GLintptr)(unsafe.Pointer(offsets)), (*C.GLsizeiptr)(unsafe.Pointer(sizes)))
	}
}

func (c *Context) BindTextures(first uint32, count uint32, textures *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindTextures_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))

		c.push(C.gl_wrap_batch_func{
			jump_index: 879,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindTextures(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(textures)))
	}
}

func (c *Context) BindSamplers(first uint32, count uint32, samplers *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindSamplers_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.samplers = (*C.GLuint)(unsafe.Pointer(samplers))

		c.push(C.gl_wrap_batch_func{
			jump_index: 880,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindSamplers(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(samplers)))
	}
}

func (c *Context) BindImageTextures(first uint32, count uint32, textures *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindImageTextures_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.textures = (*C.GLuint)(unsafe.Pointer(textures))

		c.push(C.gl_wrap_batch_func{
			jump_index: 881,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindImageTextures(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(textures)))
	}
}

func (c *Context) BindVertexBuffers(first uint32, count uint32, buffers *uint32, offsets *uintptr, strides *uint32) {
	if c.batching {
		var glWrapHandlerArgs C.gl_wrap_handler_glBindVertexBuffers_args
		glWrapHandlerArgs.first = C.GLuint(first)
		glWrapHandlerArgs.count = C.GLsizei(count)
		glWrapHandlerArgs.buffers = (*C.GLuint)(unsafe.Pointer(buffers))
		glWrapHandlerArgs.offsets = (*C.GLintptr)(unsafe.Pointer(offsets))
		glWrapHandlerArgs.strides = (*C.GLsizei)(unsafe.Pointer(strides))

		c.push(C.gl_wrap_batch_func{
			jump_index: 882,
			args:       unsafe.Pointer(&glWrapHandlerArgs),
		})
	} else {
		C.gl_wrap_context_glBindVertexBuffers(c.c, C.GLuint(first), C.GLsizei(count), (*C.GLuint)(unsafe.Pointer(buffers)), (*C.GLintptr)(unsafe.Pointer(offsets)), (*C.GLsizei)(unsafe.Pointer(strides)))
	}
}
