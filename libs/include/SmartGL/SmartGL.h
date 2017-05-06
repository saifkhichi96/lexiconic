#include <stdexcept>
#include <iostream>
#include <cassert>
#include <memory>
#include <string>
#include <cmath>
#include <map>


using std::map;
using std::cout;
using std::string;
using std::exception;
using std::unique_ptr;
using std::logic_error;


#ifndef HEADER_SIMPLE_OPENGL_IMAGE_LIBRARY
#define HEADER_SIMPLE_OPENGL_IMAGE_LIBRARY

#ifdef __cplusplus
extern "C" {
#endif

	/**
	The format of images that may be loaded (force_channels).
	SOIL_LOAD_AUTO leaves the image in whatever format it was found.
	SOIL_LOAD_L forces the image to load as Luminous (greyscale)
	SOIL_LOAD_LA forces the image to load as Luminous with Alpha
	SOIL_LOAD_RGB forces the image to load as Red Green Blue
	SOIL_LOAD_RGBA forces the image to load as Red Green Blue Alpha
	**/
	enum
	{
		SOIL_LOAD_AUTO = 0,
		SOIL_LOAD_L = 1,
		SOIL_LOAD_LA = 2,
		SOIL_LOAD_RGB = 3,
		SOIL_LOAD_RGBA = 4
	};

	/**
	Passed in as reuse_texture_ID, will cause SOIL to
	register a new texture ID using glGenTextures().
	If the value passed into reuse_texture_ID > 0 then
	SOIL will just re-use that texture ID (great for
	reloading image assets in-game!)
	**/
	enum
	{
		SOIL_CREATE_NEW_ID = 0
	};

	/**
	flags you can pass into SOIL_load_OGL_texture()
	and SOIL_create_OGL_texture().
	(note that if SOIL_FLAG_DDS_LOAD_DIRECT is used
	the rest of the flags with the exception of
	SOIL_FLAG_TEXTURE_REPEATS will be ignored while
	loading already-compressed DDS files.)

	SOIL_FLAG_POWER_OF_TWO: force the image to be POT
	SOIL_FLAG_MIPMAPS: generate mipmaps for the texture
	SOIL_FLAG_TEXTURE_REPEATS: otherwise will clamp
	SOIL_FLAG_MULTIPLY_ALPHA: for using (GL_ONE,GL_ONE_MINUS_SRC_ALPHA) blending
	SOIL_FLAG_INVERT_Y: flip the image vertically
	SOIL_FLAG_COMPRESS_TO_DXT: if the card can display them, will convert RGB to DXT1, RGBA to DXT5
	SOIL_FLAG_DDS_LOAD_DIRECT: will load DDS files directly without _ANY_ additional processing
	SOIL_FLAG_NTSC_SAFE_RGB: clamps RGB components to the range [16,235]
	SOIL_FLAG_CoCg_Y: Google YCoCg; RGB=>CoYCg, RGBA=>CoCgAY
	SOIL_FLAG_TEXTURE_RECTANGE: uses ARB_texture_rectangle ; pixel indexed & no repeat or MIPmaps or cubemaps
	**/
	enum
	{
		SOIL_FLAG_POWER_OF_TWO = 1,
		SOIL_FLAG_MIPMAPS = 2,
		SOIL_FLAG_TEXTURE_REPEATS = 4,
		SOIL_FLAG_MULTIPLY_ALPHA = 8,
		SOIL_FLAG_INVERT_Y = 16,
		SOIL_FLAG_COMPRESS_TO_DXT = 32,
		SOIL_FLAG_DDS_LOAD_DIRECT = 64,
		SOIL_FLAG_NTSC_SAFE_RGB = 128,
		SOIL_FLAG_CoCg_Y = 256,
		SOIL_FLAG_TEXTURE_RECTANGLE = 512
	};

	/**
	The types of images that may be saved.
	(TGA supports uncompressed RGB / RGBA)
	(BMP supports uncompressed RGB)
	(DDS supports DXT1 and DXT5)
	**/
	enum
	{
		SOIL_SAVE_TYPE_TGA = 0,
		SOIL_SAVE_TYPE_BMP = 1,
		SOIL_SAVE_TYPE_DDS = 2
	};

	/**
	Defines the order of faces in a DDS cubemap.
	I recommend that you use the same order in single
	image cubemap files, so they will be interchangeable
	with DDS cubemaps when using SOIL.
	**/
#define SOIL_DDS_CUBEMAP_FACE_ORDER "EWUDNS"

	/**
	The types of internal fake HDR representations

	SOIL_HDR_RGBE:		RGB * pow( 2.0, A - 128.0 )
	SOIL_HDR_RGBdivA:	RGB / A
	SOIL_HDR_RGBdivA2:	RGB / (A*A)
	**/
	enum
	{
		SOIL_HDR_RGBE = 0,
		SOIL_HDR_RGBdivA = 1,
		SOIL_HDR_RGBdivA2 = 2
	};

	/**
	Loads an image from disk into an OpenGL texture.
	\param filename the name of the file to upload as a texture
	\param force_channels 0-image format, 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_texture
		(
		const char *filename,
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Loads 6 images from disk into an OpenGL cubemap texture.
	\param x_pos_file the name of the file to upload as the +x cube face
	\param x_neg_file the name of the file to upload as the -x cube face
	\param y_pos_file the name of the file to upload as the +y cube face
	\param y_neg_file the name of the file to upload as the -y cube face
	\param z_pos_file the name of the file to upload as the +z cube face
	\param z_neg_file the name of the file to upload as the -z cube face
	\param force_channels 0-image format, 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_cubemap
		(
		const char *x_pos_file,
		const char *x_neg_file,
		const char *y_pos_file,
		const char *y_neg_file,
		const char *z_pos_file,
		const char *z_neg_file,
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Loads 1 image from disk and splits it into an OpenGL cubemap texture.
	\param filename the name of the file to upload as a texture
	\param face_order the order of the faces in the file, any combination of NSWEUD, for North, South, Up, etc.
	\param force_channels 0-image format, 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_single_cubemap
		(
		const char *filename,
		const char face_order[6],
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Loads an HDR image from disk into an OpenGL texture.
	\param filename the name of the file to upload as a texture
	\param fake_HDR_format SOIL_HDR_RGBE, SOIL_HDR_RGBdivA, SOIL_HDR_RGBdivA2
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_HDR_texture
		(
		const char *filename,
		int fake_HDR_format,
		int rescale_to_max,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Loads an image from RAM into an OpenGL texture.
	\param buffer the image data in RAM just as if it were still in a file
	\param buffer_length the size of the buffer in bytes
	\param force_channels 0-image format, 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_texture_from_memory
		(
		const unsigned char *const buffer,
		int buffer_length,
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Loads 6 images from memory into an OpenGL cubemap texture.
	\param x_pos_buffer the image data in RAM to upload as the +x cube face
	\param x_pos_buffer_length the size of the above buffer
	\param x_neg_buffer the image data in RAM to upload as the +x cube face
	\param x_neg_buffer_length the size of the above buffer
	\param y_pos_buffer the image data in RAM to upload as the +x cube face
	\param y_pos_buffer_length the size of the above buffer
	\param y_neg_buffer the image data in RAM to upload as the +x cube face
	\param y_neg_buffer_length the size of the above buffer
	\param z_pos_buffer the image data in RAM to upload as the +x cube face
	\param z_pos_buffer_length the size of the above buffer
	\param z_neg_buffer the image data in RAM to upload as the +x cube face
	\param z_neg_buffer_length the size of the above buffer
	\param force_channels 0-image format, 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_cubemap_from_memory
		(
		const unsigned char *const x_pos_buffer,
		int x_pos_buffer_length,
		const unsigned char *const x_neg_buffer,
		int x_neg_buffer_length,
		const unsigned char *const y_pos_buffer,
		int y_pos_buffer_length,
		const unsigned char *const y_neg_buffer,
		int y_neg_buffer_length,
		const unsigned char *const z_pos_buffer,
		int z_pos_buffer_length,
		const unsigned char *const z_neg_buffer,
		int z_neg_buffer_length,
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Loads 1 image from RAM and splits it into an OpenGL cubemap texture.
	\param buffer the image data in RAM just as if it were still in a file
	\param buffer_length the size of the buffer in bytes
	\param face_order the order of the faces in the file, any combination of NSWEUD, for North, South, Up, etc.
	\param force_channels 0-image format, 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_load_OGL_single_cubemap_from_memory
		(
		const unsigned char *const buffer,
		int buffer_length,
		const char face_order[6],
		int force_channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Creates a 2D OpenGL texture from raw image data.  Note that the raw data is
	_NOT_ freed after the upload (so the user can load various versions).
	\param data the raw data to be uploaded as an OpenGL texture
	\param width the width of the image in pixels
	\param height the height of the image in pixels
	\param channels the number of channels: 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_create_OGL_texture
		(
		const unsigned char *const data,
		int width, int height, int channels,
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Creates an OpenGL cubemap texture by splitting up 1 image into 6 parts.
	\param data the raw data to be uploaded as an OpenGL texture
	\param width the width of the image in pixels
	\param height the height of the image in pixels
	\param channels the number of channels: 1-luminous, 2-luminous/alpha, 3-RGB, 4-RGBA
	\param face_order the order of the faces in the file, and combination of NSWEUD, for North, South, Up, etc.
	\param reuse_texture_ID 0-generate a new texture ID, otherwise reuse the texture ID (overwriting the old texture)
	\param flags can be any of SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT
	\return 0-failed, otherwise returns the OpenGL texture handle
	**/
	unsigned int
		SOIL_create_OGL_single_cubemap
		(
		const unsigned char *const data,
		int width, int height, int channels,
		const char face_order[6],
		unsigned int reuse_texture_ID,
		unsigned int flags
		);

	/**
	Captures the OpenGL window (RGB) and saves it to disk
	\return 0 if it failed, otherwise returns 1
	**/
	int
		SOIL_save_screenshot
		(
		const char *filename,
		int image_type,
		int x, int y,
		int width, int height
		);

	/**
	Loads an image from disk into an array of unsigned chars.
	Note that *channels return the original channel count of the
	image.  If force_channels was other than SOIL_LOAD_AUTO,
	the resulting image has force_channels, but *channels may be
	different (if the original image had a different channel
	count).
	\return 0 if failed, otherwise returns 1
	**/
	unsigned char*
		SOIL_load_image
		(
		const char *filename,
		int *width, int *height, int *channels,
		int force_channels
		);

	/**
	Loads an image from memory into an array of unsigned chars.
	Note that *channels return the original channel count of the
	image.  If force_channels was other than SOIL_LOAD_AUTO,
	the resulting image has force_channels, but *channels may be
	different (if the original image had a different channel
	count).
	\return 0 if failed, otherwise returns 1
	**/
	unsigned char*
		SOIL_load_image_from_memory
		(
		const unsigned char *const buffer,
		int buffer_length,
		int *width, int *height, int *channels,
		int force_channels
		);

	/**
	Saves an image from an array of unsigned chars (RGBA) to disk
	\return 0 if failed, otherwise returns 1
	**/
	int
		SOIL_save_image
		(
		const char *filename,
		int image_type,
		int width, int height, int channels,
		const unsigned char *const data
		);

	/**
	Frees the image data (note, this is just C's "free()"...this function is
	present mostly so C++ programmers don't forget to use "free()" and call
	"delete []" instead [8^)
	**/
	void
		SOIL_free_image_data
		(
		unsigned char *img_data
		);

	/**
	This function resturn a pointer to a string describing the last thing
	that happened inside SOIL.  It can be used to determine why an image
	failed to load.
	**/
	const char*
		SOIL_last_result
		(
		void
		);


#ifdef __cplusplus
}
#endif

#endif /* HEADER_SIMPLE_OPENGL_IMAGE_LIBRARY	*/


#ifndef __glut_h__
#define __glut_h__

/* Copyright (c) Mark J. Kilgard, 1994, 1995, 1996, 1998. */

/* This program is freely distributable without licensing fees  and is
provided without guarantee or warrantee expressed or  implied. This
program is -not- in the public domain. */

#if defined(_WIN32)

/* GLUT 3.7 now tries to avoid including <windows.h>
to avoid name space pollution, but Win32's <GL/gl.h> 
needs APIENTRY and WINGDIAPI defined properly. */
# if 0
/* This would put tons of macros and crap in our clean name space. */
#  define  WIN32_LEAN_AND_MEAN
#  include <windows.h>
# else
/* XXX This is from Win32's <windef.h> */
#  ifndef APIENTRY
#   define GLUT_APIENTRY_DEFINED
#   if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__) || defined(__LCC__)
#    define APIENTRY    __stdcall
#   else
#    define APIENTRY
#   endif
#  endif
/* XXX This is from Win32's <winnt.h> */
#  ifndef CALLBACK
#   if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS) || defined(__LCC__)
#    define CALLBACK __stdcall
#   else
#    define CALLBACK
#   endif
#  endif
/* XXX Hack for lcc compiler.  It doesn't support __declspec(dllimport), just __stdcall. */
#  if defined( __LCC__ )
#   undef WINGDIAPI
#   define WINGDIAPI __stdcall
#  else
/* XXX This is from Win32's <wingdi.h> and <winnt.h> */
#   ifndef WINGDIAPI
#    define GLUT_WINGDIAPI_DEFINED
#    define WINGDIAPI __declspec(dllimport)
#   endif
#  endif
/* XXX This is from Win32's <ctype.h> */
#  ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#   define _WCHAR_T_DEFINED
#  endif
# endif

/* To disable automatic library usage for GLUT, define GLUT_NO_LIB_PRAGMA
in your compile preprocessor options. */
# if !defined(GLUT_BUILDING_LIB) && !defined(GLUT_NO_LIB_PRAGMA)
#  pragma comment (lib, "winmm.lib")      /* link with Windows MultiMedia lib */
/* To enable automatic SGI OpenGL for Windows library usage for GLUT,
define GLUT_USE_SGI_OPENGL in your compile preprocessor options.  */
#  ifdef GLUT_USE_SGI_OPENGL
#   pragma comment (lib, "opengl.lib")    /* link with SGI OpenGL for Windows lib */
#   pragma comment (lib, "glu.lib")       /* link with SGI OpenGL Utility lib */
#   pragma comment (lib, "glut.lib")      /* link with Win32 GLUT for SGI OpenGL lib */
#  else
#   pragma comment (lib, "opengl32.lib")  /* link with Microsoft OpenGL lib */
#   pragma comment (lib, "glu32.lib")     /* link with Microsoft OpenGL Utility lib */
#   pragma comment (lib, "glut32.lib")    /* link with Win32 GLUT lib */
#  endif
# endif

/* To disable supression of annoying warnings about floats being promoted
to doubles, define GLUT_NO_WARNING_DISABLE in your compile preprocessor
options. */
# ifndef GLUT_NO_WARNING_DISABLE
#  pragma warning (disable:4244)  /* Disable bogus VC++ 4.2 conversion warnings. */
#  pragma warning (disable:4305)  /* VC++ 5.0 version of above warning. */
# endif

/* Win32 has an annoying issue where there are multiple C run-time
libraries (CRTs).  If the executable is linked with a different CRT
from the GLUT DLL, the GLUT DLL will not share the same CRT static
data seen by the executable.  In particular, atexit callbacks registered
in the executable will not be called if GLUT calls its (different)
exit routine).  GLUT is typically built with the
"/MD" option (the CRT with multithreading DLL support), but the Visual
C++ linker default is "/ML" (the single threaded CRT).

One workaround to this issue is requiring users to always link with
the same CRT as GLUT is compiled with.  That requires users supply a
non-standard option.  GLUT 3.7 has its own built-in workaround where
the executable's "exit" function pointer is covertly passed to GLUT.
GLUT then calls the executable's exit function pointer to ensure that
any "atexit" calls registered by the application are called if GLUT
needs to exit.

Note that the __glut*WithExit routines should NEVER be called directly.
To avoid the atexit workaround, #define GLUT_DISABLE_ATEXIT_HACK. */

/* XXX This is from Win32's <process.h> */
# if !defined(_MSC_VER) && !defined(__cdecl)
/* Define __cdecl for non-Microsoft compilers. */
#  define __cdecl
#  define GLUT_DEFINED___CDECL
# endif
# ifndef _CRTIMP
#  ifdef _NTSDK
/* Definition compatible with NT SDK */
#   define _CRTIMP
#  else
/* Current definition */
#   ifdef _DLL
#    define _CRTIMP __declspec(dllimport)
#   else
#    define _CRTIMP
#   endif
#  endif
#  define GLUT_DEFINED__CRTIMP
# endif

/* GLUT API entry point declarations for Win32. */
# ifdef GLUT_BUILDING_LIB
#  define GLUTAPI __declspec(dllexport)
# else
#  ifdef _DLL
#   define GLUTAPI __declspec(dllimport)
#  else
#   define GLUTAPI extern
#  endif
# endif

/* GLUT callback calling convention for Win32. */
# define GLUTCALLBACK __cdecl

#endif  /* _WIN32 */

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
# ifndef GLUT_BUILDING_LIB
	extern _CRTIMP void __cdecl exit(int);
# endif
#else
	/* non-Win32 case. */
	/* Define APIENTRY and CALLBACK to nothing if we aren't on Win32. */
# define APIENTRY
# define GLUT_APIENTRY_DEFINED
# define CALLBACK
	/* Define GLUTAPI and GLUTCALLBACK as below if we aren't on Win32. */
# define GLUTAPI extern
# define GLUTCALLBACK
	/* Prototype exit for the non-Win32 case (see above). */
	extern void exit(int);
#endif

	/**
	GLUT API revision history:

	GLUT_API_VERSION is updated to reflect incompatible GLUT
	API changes (interface changes, semantic changes, deletions,
	or additions).

	GLUT_API_VERSION=1  First public release of GLUT.  11/29/94

	GLUT_API_VERSION=2  Added support for OpenGL/GLX multisampling,
	extension.  Supports new input devices like tablet, dial and button
	box, and Spaceball.  Easy to query OpenGL extensions.

	GLUT_API_VERSION=3  glutMenuStatus added.

	GLUT_API_VERSION=4  glutInitDisplayString, glutWarpPointer,
	glutBitmapLength, glutStrokeLength, glutWindowStatusFunc, dynamic
	video resize subAPI, glutPostWindowRedisplay, glutKeyboardUpFunc,
	glutSpecialUpFunc, glutIgnoreKeyRepeat, glutSetKeyRepeat,
	glutJoystickFunc, glutForceJoystickFunc (NOT FINALIZED!).
	**/
#ifndef GLUT_API_VERSION  /* allow this to be overriden */
#define GLUT_API_VERSION		3
#endif

	/**
	GLUT implementation revision history:

	GLUT_XLIB_IMPLEMENTATION is updated to reflect both GLUT
	API revisions and implementation revisions (ie, bug fixes).

	GLUT_XLIB_IMPLEMENTATION=1  mjk's first public release of
	GLUT Xlib-based implementation.  11/29/94

	GLUT_XLIB_IMPLEMENTATION=2  mjk's second public release of
	GLUT Xlib-based implementation providing GLUT version 2 
	interfaces.

	GLUT_XLIB_IMPLEMENTATION=3  mjk's GLUT 2.2 images. 4/17/95

	GLUT_XLIB_IMPLEMENTATION=4  mjk's GLUT 2.3 images. 6/?/95

	GLUT_XLIB_IMPLEMENTATION=5  mjk's GLUT 3.0 images. 10/?/95

	GLUT_XLIB_IMPLEMENTATION=7  mjk's GLUT 3.1+ with glutWarpPoitner.  7/24/96

	GLUT_XLIB_IMPLEMENTATION=8  mjk's GLUT 3.1+ with glutWarpPoitner
	and video resize.  1/3/97

	GLUT_XLIB_IMPLEMENTATION=9 mjk's GLUT 3.4 release with early GLUT 4 routines.

	GLUT_XLIB_IMPLEMENTATION=11 Mesa 2.5's GLUT 3.6 release.

	GLUT_XLIB_IMPLEMENTATION=12 mjk's GLUT 3.6 release with early GLUT 4 routines + signal handling.

	GLUT_XLIB_IMPLEMENTATION=13 mjk's GLUT 3.7 beta with GameGLUT support.

	GLUT_XLIB_IMPLEMENTATION=14 mjk's GLUT 3.7 beta with f90gl friend interface.

	GLUT_XLIB_IMPLEMENTATION=15 mjk's GLUT 3.7 beta sync'ed with Mesa <GL/glut.h>
	**/
#ifndef GLUT_XLIB_IMPLEMENTATION  /* Allow this to be overriden. */
#define GLUT_XLIB_IMPLEMENTATION	15
#endif

	/* Display mode bit masks. */
#define GLUT_RGB			0
#define GLUT_RGBA			GLUT_RGB
#define GLUT_INDEX			1
#define GLUT_SINGLE			0
#define GLUT_DOUBLE			2
#define GLUT_ACCUM			4
#define GLUT_ALPHA			8
#define GLUT_DEPTH			16
#define GLUT_STENCIL			32
#if (GLUT_API_VERSION >= 2)
#define GLUT_MULTISAMPLE		128
#define GLUT_STEREO			256
#endif
#if (GLUT_API_VERSION >= 3)
#define GLUT_LUMINANCE			512
#endif

	/* Mouse buttons. */
#define GLUT_LEFT_BUTTON		0
#define GLUT_MIDDLE_BUTTON		1
#define GLUT_RIGHT_BUTTON		2

	/* Mouse button  state. */
#define GLUT_DOWN			0
#define GLUT_UP				1

#if (GLUT_API_VERSION >= 2)
	/* function keys */
#define GLUT_KEY_F1			1
#define GLUT_KEY_F2			2
#define GLUT_KEY_F3			3
#define GLUT_KEY_F4			4
#define GLUT_KEY_F5			5
#define GLUT_KEY_F6			6
#define GLUT_KEY_F7			7
#define GLUT_KEY_F8			8
#define GLUT_KEY_F9			9
#define GLUT_KEY_F10			10
#define GLUT_KEY_F11			11
#define GLUT_KEY_F12			12
	/* directional keys */
#define GLUT_KEY_LEFT			100
#define GLUT_KEY_UP			101
#define GLUT_KEY_RIGHT			102
#define GLUT_KEY_DOWN			103
#define GLUT_KEY_PAGE_UP		104
#define GLUT_KEY_PAGE_DOWN		105
#define GLUT_KEY_HOME			106
#define GLUT_KEY_END			107
#define GLUT_KEY_INSERT			108
#endif

	/* Entry/exit  state. */
#define GLUT_LEFT			0
#define GLUT_ENTERED			1

	/* Menu usage  state. */
#define GLUT_MENU_NOT_IN_USE		0
#define GLUT_MENU_IN_USE		1

	/* Visibility  state. */
#define GLUT_NOT_VISIBLE		0
#define GLUT_VISIBLE			1

	/* Window status  state. */
#define GLUT_HIDDEN			0
#define GLUT_FULLY_RETAINED		1
#define GLUT_PARTIALLY_RETAINED		2
#define GLUT_FULLY_COVERED		3

	/* Color index component selection values. */
#define GLUT_RED			0
#define GLUT_GREEN			1
#define GLUT_BLUE			2

#if defined(_WIN32)
	/* Stroke font constants (use these in GLUT program). */
#define GLUT_STROKE_ROMAN		((void*)0)
#define GLUT_STROKE_MONO_ROMAN		((void*)1)

	/* Bitmap font constants (use these in GLUT program). */
#define GLUT_BITMAP_9_BY_15		((void*)2)
#define GLUT_BITMAP_8_BY_13		((void*)3)
#define GLUT_BITMAP_TIMES_ROMAN_10	((void*)4)
#define GLUT_BITMAP_TIMES_ROMAN_24	((void*)5)
#if (GLUT_API_VERSION >= 3)
#define GLUT_BITMAP_HELVETICA_10	((void*)6)
#define GLUT_BITMAP_HELVETICA_12	((void*)7)
#define GLUT_BITMAP_HELVETICA_18	((void*)8)
#endif
#else
	/* Stroke font opaque addresses (use constants instead in source code). */
	GLUTAPI void *glutStrokeRoman;
	GLUTAPI void *glutStrokeMonoRoman;

	/* Stroke font constants (use these in GLUT program). */
#define GLUT_STROKE_ROMAN		(&glutStrokeRoman)
#define GLUT_STROKE_MONO_ROMAN		(&glutStrokeMonoRoman)

	/* Bitmap font opaque addresses (use constants instead in source code). */
	GLUTAPI void *glutBitmap9By15;
	GLUTAPI void *glutBitmap8By13;
	GLUTAPI void *glutBitmapTimesRoman10;
	GLUTAPI void *glutBitmapTimesRoman24;
	GLUTAPI void *glutBitmapHelvetica10;
	GLUTAPI void *glutBitmapHelvetica12;
	GLUTAPI void *glutBitmapHelvetica18;

	/* Bitmap font constants (use these in GLUT program). */
#define GLUT_BITMAP_9_BY_15		(&glutBitmap9By15)
#define GLUT_BITMAP_8_BY_13		(&glutBitmap8By13)
#define GLUT_BITMAP_TIMES_ROMAN_10	(&glutBitmapTimesRoman10)
#define GLUT_BITMAP_TIMES_ROMAN_24	(&glutBitmapTimesRoman24)
#if (GLUT_API_VERSION >= 3)
#define GLUT_BITMAP_HELVETICA_10	(&glutBitmapHelvetica10)
#define GLUT_BITMAP_HELVETICA_12	(&glutBitmapHelvetica12)
#define GLUT_BITMAP_HELVETICA_18	(&glutBitmapHelvetica18)
#endif
#endif

	/* glutGet parameters. */
#define GLUT_WINDOW_X			((GLenum) 100)
#define GLUT_WINDOW_Y			((GLenum) 101)
#define GLUT_WINDOW_WIDTH		((GLenum) 102)
#define GLUT_WINDOW_HEIGHT		((GLenum) 103)
#define GLUT_WINDOW_BUFFER_SIZE		((GLenum) 104)
#define GLUT_WINDOW_STENCIL_SIZE	((GLenum) 105)
#define GLUT_WINDOW_DEPTH_SIZE		((GLenum) 106)
#define GLUT_WINDOW_RED_SIZE		((GLenum) 107)
#define GLUT_WINDOW_GREEN_SIZE		((GLenum) 108)
#define GLUT_WINDOW_BLUE_SIZE		((GLenum) 109)
#define GLUT_WINDOW_ALPHA_SIZE		((GLenum) 110)
#define GLUT_WINDOW_ACCUM_RED_SIZE	((GLenum) 111)
#define GLUT_WINDOW_ACCUM_GREEN_SIZE	((GLenum) 112)
#define GLUT_WINDOW_ACCUM_BLUE_SIZE	((GLenum) 113)
#define GLUT_WINDOW_ACCUM_ALPHA_SIZE	((GLenum) 114)
#define GLUT_WINDOW_DOUBLEBUFFER	((GLenum) 115)
#define GLUT_WINDOW_RGBA		((GLenum) 116)
#define GLUT_WINDOW_PARENT		((GLenum) 117)
#define GLUT_WINDOW_NUM_CHILDREN	((GLenum) 118)
#define GLUT_WINDOW_COLORMAP_SIZE	((GLenum) 119)
#if (GLUT_API_VERSION >= 2)
#define GLUT_WINDOW_NUM_SAMPLES		((GLenum) 120)
#define GLUT_WINDOW_STEREO		((GLenum) 121)
#endif
#if (GLUT_API_VERSION >= 3)
#define GLUT_WINDOW_CURSOR		((GLenum) 122)
#endif
#define GLUT_SCREEN_WIDTH		((GLenum) 200)
#define GLUT_SCREEN_HEIGHT		((GLenum) 201)
#define GLUT_SCREEN_WIDTH_MM		((GLenum) 202)
#define GLUT_SCREEN_HEIGHT_MM		((GLenum) 203)
#define GLUT_MENU_NUM_ITEMS		((GLenum) 300)
#define GLUT_DISPLAY_MODE_POSSIBLE	((GLenum) 400)
#define GLUT_INIT_WINDOW_X		((GLenum) 500)
#define GLUT_INIT_WINDOW_Y		((GLenum) 501)
#define GLUT_INIT_WINDOW_WIDTH		((GLenum) 502)
#define GLUT_INIT_WINDOW_HEIGHT		((GLenum) 503)
#define GLUT_INIT_DISPLAY_MODE		((GLenum) 504)
#if (GLUT_API_VERSION >= 2)
#define GLUT_ELAPSED_TIME		((GLenum) 700)
#endif
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 13)
#define GLUT_WINDOW_FORMAT_ID		((GLenum) 123)
#endif

#if (GLUT_API_VERSION >= 2)
	/* glutDeviceGet parameters. */
#define GLUT_HAS_KEYBOARD		((GLenum) 600)
#define GLUT_HAS_MOUSE			((GLenum) 601)
#define GLUT_HAS_SPACEBALL		((GLenum) 602)
#define GLUT_HAS_DIAL_AND_BUTTON_BOX	((GLenum) 603)
#define GLUT_HAS_TABLET			((GLenum) 604)
#define GLUT_NUM_MOUSE_BUTTONS		((GLenum) 605)
#define GLUT_NUM_SPACEBALL_BUTTONS	((GLenum) 606)
#define GLUT_NUM_BUTTON_BOX_BUTTONS	((GLenum) 607)
#define GLUT_NUM_DIALS			((GLenum) 608)
#define GLUT_NUM_TABLET_BUTTONS		((GLenum) 609)
#endif
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 13)
#define GLUT_DEVICE_IGNORE_KEY_REPEAT   ((GLenum) 610)
#define GLUT_DEVICE_KEY_REPEAT          ((GLenum) 611)
#define GLUT_HAS_JOYSTICK		((GLenum) 612)
#define GLUT_OWNS_JOYSTICK		((GLenum) 613)
#define GLUT_JOYSTICK_BUTTONS		((GLenum) 614)
#define GLUT_JOYSTICK_AXES		((GLenum) 615)
#define GLUT_JOYSTICK_POLL_RATE		((GLenum) 616)
#endif

#if (GLUT_API_VERSION >= 3)
	/* glutLayerGet parameters. */
#define GLUT_OVERLAY_POSSIBLE           ((GLenum) 800)
#define GLUT_LAYER_IN_USE		((GLenum) 801)
#define GLUT_HAS_OVERLAY		((GLenum) 802)
#define GLUT_TRANSPARENT_INDEX		((GLenum) 803)
#define GLUT_NORMAL_DAMAGED		((GLenum) 804)
#define GLUT_OVERLAY_DAMAGED		((GLenum) 805)

#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
	/* glutVideoResizeGet parameters. */
#define GLUT_VIDEO_RESIZE_POSSIBLE	((GLenum) 900)
#define GLUT_VIDEO_RESIZE_IN_USE	((GLenum) 901)
#define GLUT_VIDEO_RESIZE_X_DELTA	((GLenum) 902)
#define GLUT_VIDEO_RESIZE_Y_DELTA	((GLenum) 903)
#define GLUT_VIDEO_RESIZE_WIDTH_DELTA	((GLenum) 904)
#define GLUT_VIDEO_RESIZE_HEIGHT_DELTA	((GLenum) 905)
#define GLUT_VIDEO_RESIZE_X		((GLenum) 906)
#define GLUT_VIDEO_RESIZE_Y		((GLenum) 907)
#define GLUT_VIDEO_RESIZE_WIDTH		((GLenum) 908)
#define GLUT_VIDEO_RESIZE_HEIGHT	((GLenum) 909)
#endif

	/* glutUseLayer parameters. */
#define GLUT_NORMAL			((GLenum) 0)
#define GLUT_OVERLAY			((GLenum) 1)

	/* glutGetModifiers return mask. */
#define GLUT_ACTIVE_SHIFT               1
#define GLUT_ACTIVE_CTRL                2
#define GLUT_ACTIVE_ALT                 4

	/* glutSetCursor parameters. */
	/* Basic arrows. */
#define GLUT_CURSOR_RIGHT_ARROW		0
#define GLUT_CURSOR_LEFT_ARROW		1
	/* Symbolic cursor shapes. */
#define GLUT_CURSOR_INFO		2
#define GLUT_CURSOR_DESTROY		3
#define GLUT_CURSOR_HELP		4
#define GLUT_CURSOR_CYCLE		5
#define GLUT_CURSOR_SPRAY		6
#define GLUT_CURSOR_WAIT		7
#define GLUT_CURSOR_TEXT		8
#define GLUT_CURSOR_CROSSHAIR		9
	/* Directional cursors. */
#define GLUT_CURSOR_UP_DOWN		10
#define GLUT_CURSOR_LEFT_RIGHT		11
	/* Sizing cursors. */
#define GLUT_CURSOR_TOP_SIDE		12
#define GLUT_CURSOR_BOTTOM_SIDE		13
#define GLUT_CURSOR_LEFT_SIDE		14
#define GLUT_CURSOR_RIGHT_SIDE		15
#define GLUT_CURSOR_TOP_LEFT_CORNER	16
#define GLUT_CURSOR_TOP_RIGHT_CORNER	17
#define GLUT_CURSOR_BOTTOM_RIGHT_CORNER	18
#define GLUT_CURSOR_BOTTOM_LEFT_CORNER	19
	/* Inherit from parent window. */
#define GLUT_CURSOR_INHERIT		100
	/* Blank cursor. */
#define GLUT_CURSOR_NONE		101
	/* Fullscreen crosshair (if available). */
#define GLUT_CURSOR_FULL_CROSSHAIR	102
#endif

	/* GLUT initialization sub-API. */
	GLUTAPI void APIENTRY glutInit(int *argcp, char **argv);
#if defined(_WIN32) && !defined(GLUT_DISABLE_ATEXIT_HACK)
	GLUTAPI void APIENTRY __glutInitWithExit(int *argcp, char **argv, void (__cdecl *exitfunc)(int));
#ifndef GLUT_BUILDING_LIB
	static void APIENTRY glutInit_ATEXIT_HACK(int *argcp, char **argv) { __glutInitWithExit(argcp, argv, exit); }
#define glutInit glutInit_ATEXIT_HACK
#endif
#endif
	GLUTAPI void APIENTRY glutInitDisplayMode(unsigned int mode);
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
	GLUTAPI void APIENTRY glutInitDisplayString(const char *string);
#endif
	GLUTAPI void APIENTRY glutInitWindowPosition(int x, int y);
	GLUTAPI void APIENTRY glutInitWindowSize(int width, int height);
	GLUTAPI void APIENTRY glutMainLoop(void);

	/* GLUT window sub-API. */
	GLUTAPI int APIENTRY glutCreateWindow(const char *title);
#if defined(_WIN32) && !defined(GLUT_DISABLE_ATEXIT_HACK)
	GLUTAPI int APIENTRY __glutCreateWindowWithExit(const char *title, void (__cdecl *exitfunc)(int));
#ifndef GLUT_BUILDING_LIB
	static int APIENTRY glutCreateWindow_ATEXIT_HACK(const char *title) { return __glutCreateWindowWithExit(title, exit); }
#define glutCreateWindow glutCreateWindow_ATEXIT_HACK
#endif
#endif
	GLUTAPI int APIENTRY glutCreateSubWindow(int win, int x, int y, int width, int height);
	GLUTAPI void APIENTRY glutDestroyWindow(int win);
	GLUTAPI void APIENTRY glutPostRedisplay(void);
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 11)
	GLUTAPI void APIENTRY glutPostWindowRedisplay(int win);
#endif
	GLUTAPI void APIENTRY glutSwapBuffers(void);
	GLUTAPI int APIENTRY glutGetWindow(void);
	GLUTAPI void APIENTRY glutSetWindow(int win);
	GLUTAPI void APIENTRY glutSetWindowTitle(const char *title);
	GLUTAPI void APIENTRY glutSetIconTitle(const char *title);
	GLUTAPI void APIENTRY glutPositionWindow(int x, int y);
	GLUTAPI void APIENTRY glutReshapeWindow(int width, int height);
	GLUTAPI void APIENTRY glutPopWindow(void);
	GLUTAPI void APIENTRY glutPushWindow(void);
	GLUTAPI void APIENTRY glutIconifyWindow(void);
	GLUTAPI void APIENTRY glutShowWindow(void);
	GLUTAPI void APIENTRY glutHideWindow(void);
#if (GLUT_API_VERSION >= 3)
	GLUTAPI void APIENTRY glutFullScreen(void);
	GLUTAPI void APIENTRY glutSetCursor(int cursor);
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
	GLUTAPI void APIENTRY glutWarpPointer(int x, int y);
#endif

	/* GLUT overlay sub-API. */
	GLUTAPI void APIENTRY glutEstablishOverlay(void);
	GLUTAPI void APIENTRY glutRemoveOverlay(void);
	GLUTAPI void APIENTRY glutUseLayer(GLenum layer);
	GLUTAPI void APIENTRY glutPostOverlayRedisplay(void);
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 11)
	GLUTAPI void APIENTRY glutPostWindowOverlayRedisplay(int win);
#endif
	GLUTAPI void APIENTRY glutShowOverlay(void);
	GLUTAPI void APIENTRY glutHideOverlay(void);
#endif

	/* GLUT menu sub-API. */
	GLUTAPI int APIENTRY glutCreateMenu(void (GLUTCALLBACK *func)(int));
#if defined(_WIN32) && !defined(GLUT_DISABLE_ATEXIT_HACK)
	GLUTAPI int APIENTRY __glutCreateMenuWithExit(void (GLUTCALLBACK *func)(int), void (__cdecl *exitfunc)(int));
#ifndef GLUT_BUILDING_LIB
	static int APIENTRY glutCreateMenu_ATEXIT_HACK(void (GLUTCALLBACK *func)(int)) { return __glutCreateMenuWithExit(func, exit); }
#define glutCreateMenu glutCreateMenu_ATEXIT_HACK
#endif
#endif
	GLUTAPI void APIENTRY glutDestroyMenu(int menu);
	GLUTAPI int APIENTRY glutGetMenu(void);
	GLUTAPI void APIENTRY glutSetMenu(int menu);
	GLUTAPI void APIENTRY glutAddMenuEntry(const char *label, int value);
	GLUTAPI void APIENTRY glutAddSubMenu(const char *label, int submenu);
	GLUTAPI void APIENTRY glutChangeToMenuEntry(int item, const char *label, int value);
	GLUTAPI void APIENTRY glutChangeToSubMenu(int item, const char *label, int submenu);
	GLUTAPI void APIENTRY glutRemoveMenuItem(int item);
	GLUTAPI void APIENTRY glutAttachMenu(int button);
	GLUTAPI void APIENTRY glutDetachMenu(int button);

	/* GLUT window callback sub-API. */
	GLUTAPI void APIENTRY glutDisplayFunc(void (GLUTCALLBACK *func)(void));
	GLUTAPI void APIENTRY glutReshapeFunc(void (GLUTCALLBACK *func)(int width, int height));
	GLUTAPI void APIENTRY glutKeyboardFunc(void (GLUTCALLBACK *func)(unsigned char key, int x, int y));
	GLUTAPI void APIENTRY glutMouseFunc(void (GLUTCALLBACK *func)(int button, int state, int x, int y));
	GLUTAPI void APIENTRY glutMotionFunc(void (GLUTCALLBACK *func)(int x, int y));
	GLUTAPI void APIENTRY glutPassiveMotionFunc(void (GLUTCALLBACK *func)(int x, int y));
	GLUTAPI void APIENTRY glutEntryFunc(void (GLUTCALLBACK *func)(int state));
	GLUTAPI void APIENTRY glutVisibilityFunc(void (GLUTCALLBACK *func)(int state));
	GLUTAPI void APIENTRY glutIdleFunc(void (GLUTCALLBACK *func)(void));
	GLUTAPI void APIENTRY glutTimerFunc(unsigned int millis, void (GLUTCALLBACK *func)(int value), int value);
	GLUTAPI void APIENTRY glutMenuStateFunc(void (GLUTCALLBACK *func)(int state));
#if (GLUT_API_VERSION >= 2)
	GLUTAPI void APIENTRY glutSpecialFunc(void (GLUTCALLBACK *func)(int key, int x, int y));
	GLUTAPI void APIENTRY glutSpaceballMotionFunc(void (GLUTCALLBACK *func)(int x, int y, int z));
	GLUTAPI void APIENTRY glutSpaceballRotateFunc(void (GLUTCALLBACK *func)(int x, int y, int z));
	GLUTAPI void APIENTRY glutSpaceballButtonFunc(void (GLUTCALLBACK *func)(int button, int state));
	GLUTAPI void APIENTRY glutButtonBoxFunc(void (GLUTCALLBACK *func)(int button, int state));
	GLUTAPI void APIENTRY glutDialsFunc(void (GLUTCALLBACK *func)(int dial, int value));
	GLUTAPI void APIENTRY glutTabletMotionFunc(void (GLUTCALLBACK *func)(int x, int y));
	GLUTAPI void APIENTRY glutTabletButtonFunc(void (GLUTCALLBACK *func)(int button, int state, int x, int y));
#if (GLUT_API_VERSION >= 3)
	GLUTAPI void APIENTRY glutMenuStatusFunc(void (GLUTCALLBACK *func)(int status, int x, int y));
	GLUTAPI void APIENTRY glutOverlayDisplayFunc(void (GLUTCALLBACK *func)(void));
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
	GLUTAPI void APIENTRY glutWindowStatusFunc(void (GLUTCALLBACK *func)(int state));
#endif
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 13)
	GLUTAPI void APIENTRY glutKeyboardUpFunc(void (GLUTCALLBACK *func)(unsigned char key, int x, int y));
	GLUTAPI void APIENTRY glutSpecialUpFunc(void (GLUTCALLBACK *func)(int key, int x, int y));
	GLUTAPI void APIENTRY glutJoystickFunc(void (GLUTCALLBACK *func)(unsigned int buttonMask, int x, int y, int z), int pollInterval);
#endif
#endif
#endif

	/* GLUT color index sub-API. */
	GLUTAPI void APIENTRY glutSetColor(int, GLfloat red, GLfloat green, GLfloat blue);
	GLUTAPI GLfloat APIENTRY glutGetColor(int ndx, int component);
	GLUTAPI void APIENTRY glutCopyColormap(int win);

	/* GLUT state retrieval sub-API. */
	GLUTAPI int APIENTRY glutGet(GLenum type);
	GLUTAPI int APIENTRY glutDeviceGet(GLenum type);
#if (GLUT_API_VERSION >= 2)
	/* GLUT extension support sub-API */
	GLUTAPI int APIENTRY glutExtensionSupported(const char *name);
#endif
#if (GLUT_API_VERSION >= 3)
	GLUTAPI int APIENTRY glutGetModifiers(void);
	GLUTAPI int APIENTRY glutLayerGet(GLenum type);
#endif

	/* GLUT font sub-API */
	GLUTAPI void APIENTRY glutBitmapCharacter(void *font, int character);
	GLUTAPI int APIENTRY glutBitmapWidth(void *font, int character);
	GLUTAPI void APIENTRY glutStrokeCharacter(void *font, int character);
	GLUTAPI int APIENTRY glutStrokeWidth(void *font, int character);
#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
	GLUTAPI int APIENTRY glutBitmapLength(void *font, const unsigned char *string);
	GLUTAPI int APIENTRY glutStrokeLength(void *font, const unsigned char *string);
#endif

	/* GLUT pre-built models sub-API */
	GLUTAPI void APIENTRY glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
	GLUTAPI void APIENTRY glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
	GLUTAPI void APIENTRY glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	GLUTAPI void APIENTRY glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	GLUTAPI void APIENTRY glutWireCube(GLdouble size);
	GLUTAPI void APIENTRY glutSolidCube(GLdouble size);
	GLUTAPI void APIENTRY glutWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
	GLUTAPI void APIENTRY glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
	GLUTAPI void APIENTRY glutWireDodecahedron(void);
	GLUTAPI void APIENTRY glutSolidDodecahedron(void);
	GLUTAPI void APIENTRY glutWireTeapot(GLdouble size);
	GLUTAPI void APIENTRY glutSolidTeapot(GLdouble size);
	GLUTAPI void APIENTRY glutWireOctahedron(void);
	GLUTAPI void APIENTRY glutSolidOctahedron(void);
	GLUTAPI void APIENTRY glutWireTetrahedron(void);
	GLUTAPI void APIENTRY glutSolidTetrahedron(void);
	GLUTAPI void APIENTRY glutWireIcosahedron(void);
	GLUTAPI void APIENTRY glutSolidIcosahedron(void);

#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
	/* GLUT video resize sub-API. */
	GLUTAPI int APIENTRY glutVideoResizeGet(GLenum param);
	GLUTAPI void APIENTRY glutSetupVideoResizing(void);
	GLUTAPI void APIENTRY glutStopVideoResizing(void);
	GLUTAPI void APIENTRY glutVideoResize(int x, int y, int width, int height);
	GLUTAPI void APIENTRY glutVideoPan(int x, int y, int width, int height);

	/* GLUT debugging sub-API. */
	GLUTAPI void APIENTRY glutReportErrors(void);
#endif

#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 13)
	/* GLUT device control sub-API. */
	/* glutSetKeyRepeat modes. */
#define GLUT_KEY_REPEAT_OFF		0
#define GLUT_KEY_REPEAT_ON		1
#define GLUT_KEY_REPEAT_DEFAULT		2

	/* Joystick button masks. */
#define GLUT_JOYSTICK_BUTTON_A		1
#define GLUT_JOYSTICK_BUTTON_B		2
#define GLUT_JOYSTICK_BUTTON_C		4
#define GLUT_JOYSTICK_BUTTON_D		8

	GLUTAPI void APIENTRY glutIgnoreKeyRepeat(int ignore);
	GLUTAPI void APIENTRY glutSetKeyRepeat(int repeatMode);
	GLUTAPI void APIENTRY glutForceJoystickFunc(void);

	/* GLUT game mode sub-API. */
	/* glutGameModeGet. */
#define GLUT_GAME_MODE_ACTIVE           ((GLenum) 0)
#define GLUT_GAME_MODE_POSSIBLE         ((GLenum) 1)
#define GLUT_GAME_MODE_WIDTH            ((GLenum) 2)
#define GLUT_GAME_MODE_HEIGHT           ((GLenum) 3)
#define GLUT_GAME_MODE_PIXEL_DEPTH      ((GLenum) 4)
#define GLUT_GAME_MODE_REFRESH_RATE     ((GLenum) 5)
#define GLUT_GAME_MODE_DISPLAY_CHANGED  ((GLenum) 6)

	GLUTAPI void APIENTRY glutGameModeString(const char *string);
	GLUTAPI int APIENTRY glutEnterGameMode(void);
	GLUTAPI void APIENTRY glutLeaveGameMode(void);
	GLUTAPI int APIENTRY glutGameModeGet(GLenum mode);
#endif

#ifdef __cplusplus
}

#endif

#ifdef GLUT_APIENTRY_DEFINED
# undef GLUT_APIENTRY_DEFINED
# undef APIENTRY
#endif

#ifdef GLUT_WINGDIAPI_DEFINED
# undef GLUT_WINGDIAPI_DEFINED
# undef WINGDIAPI
#endif

#ifdef GLUT_DEFINED___CDECL
# undef GLUT_DEFINED___CDECL
# undef __cdecl
#endif

#ifdef GLUT_DEFINED__CRTIMP
# undef GLUT_DEFINED__CRTIMP
# undef _CRTIMP
#endif

#endif                  /* __glut_h__ */


#ifndef __gl_h_
#ifndef __GL_H__

#define __gl_h_
#define __GL_H__

#ifdef __cplusplus
extern "C" {
#endif

	/*
	** Copyright 1996 Silicon Graphics, Inc.
	** All Rights Reserved.
	**
	** This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
	** the contents of this file may not be disclosed to third parties, copied or
	** duplicated in any form, in whole or in part, without the prior written
	** permission of Silicon Graphics, Inc.
	**
	** RESTRICTED RIGHTS LEGEND:
	** Use, duplication or disclosure by the Government is subject to restrictions
	** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
	** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
	** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
	** rights reserved under the Copyright Laws of the United States.
	*/

	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef int GLint;
	typedef int GLsizei;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned int GLuint;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef void GLvoid;

	/*************************************************************/

	/* Version */
#define GL_VERSION_1_1                    1

	/* AccumOp */
#define GL_ACCUM                          0x0100
#define GL_LOAD                           0x0101
#define GL_RETURN                         0x0102
#define GL_MULT                           0x0103
#define GL_ADD                            0x0104

	/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

	/* AttribMask */
#define GL_CURRENT_BIT                    0x00000001
#define GL_POINT_BIT                      0x00000002
#define GL_LINE_BIT                       0x00000004
#define GL_POLYGON_BIT                    0x00000008
#define GL_POLYGON_STIPPLE_BIT            0x00000010
#define GL_PIXEL_MODE_BIT                 0x00000020
#define GL_LIGHTING_BIT                   0x00000040
#define GL_FOG_BIT                        0x00000080
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_ACCUM_BUFFER_BIT               0x00000200
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_VIEWPORT_BIT                   0x00000800
#define GL_TRANSFORM_BIT                  0x00001000
#define GL_ENABLE_BIT                     0x00002000
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_HINT_BIT                       0x00008000
#define GL_EVAL_BIT                       0x00010000
#define GL_LIST_BIT                       0x00020000
#define GL_TEXTURE_BIT                    0x00040000
#define GL_SCISSOR_BIT                    0x00080000
#define GL_ALL_ATTRIB_BITS                0x000fffff

	/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_QUAD_STRIP                     0x0008
#define GL_POLYGON                        0x0009

	/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

	/* BlendingFactorSrc */
	/*      GL_ZERO */
	/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
	/*      GL_SRC_ALPHA */
	/*      GL_ONE_MINUS_SRC_ALPHA */
	/*      GL_DST_ALPHA */
	/*      GL_ONE_MINUS_DST_ALPHA */

	/* Boolean */
#define GL_TRUE                           1
#define GL_FALSE                          0

	/* ClearBufferMask */
	/*      GL_COLOR_BUFFER_BIT */
	/*      GL_ACCUM_BUFFER_BIT */
	/*      GL_STENCIL_BUFFER_BIT */
	/*      GL_DEPTH_BUFFER_BIT */

	/* ClientArrayType */
	/*      GL_VERTEX_ARRAY */
	/*      GL_NORMAL_ARRAY */
	/*      GL_COLOR_ARRAY */
	/*      GL_INDEX_ARRAY */
	/*      GL_TEXTURE_COORD_ARRAY */
	/*      GL_EDGE_FLAG_ARRAY */

	/* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

	/* ColorMaterialFace */
	/*      GL_FRONT */
	/*      GL_BACK */
	/*      GL_FRONT_AND_BACK */

	/* ColorMaterialParameter */
	/*      GL_AMBIENT */
	/*      GL_DIFFUSE */
	/*      GL_SPECULAR */
	/*      GL_EMISSION */
	/*      GL_AMBIENT_AND_DIFFUSE */

	/* ColorPointerType */
	/*      GL_BYTE */
	/*      GL_UNSIGNED_BYTE */
	/*      GL_SHORT */
	/*      GL_UNSIGNED_SHORT */
	/*      GL_INT */
	/*      GL_UNSIGNED_INT */
	/*      GL_FLOAT */
	/*      GL_DOUBLE */

	/* CullFaceMode */
	/*      GL_FRONT */
	/*      GL_BACK */
	/*      GL_FRONT_AND_BACK */

	/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_2_BYTES                        0x1407
#define GL_3_BYTES                        0x1408
#define GL_4_BYTES                        0x1409
#define GL_DOUBLE                         0x140A

	/* DepthFunction */
	/*      GL_NEVER */
	/*      GL_LESS */
	/*      GL_EQUAL */
	/*      GL_LEQUAL */
	/*      GL_GREATER */
	/*      GL_NOTEQUAL */
	/*      GL_GEQUAL */
	/*      GL_ALWAYS */

	/* DrawBufferMode */
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_AUX0                           0x0409
#define GL_AUX1                           0x040A
#define GL_AUX2                           0x040B
#define GL_AUX3                           0x040C

	/* Enable */
	/*      GL_FOG */
	/*      GL_LIGHTING */
	/*      GL_TEXTURE_1D */
	/*      GL_TEXTURE_2D */
	/*      GL_LINE_STIPPLE */
	/*      GL_POLYGON_STIPPLE */
	/*      GL_CULL_FACE */
	/*      GL_ALPHA_TEST */
	/*      GL_BLEND */
	/*      GL_INDEX_LOGIC_OP */
	/*      GL_COLOR_LOGIC_OP */
	/*      GL_DITHER */
	/*      GL_STENCIL_TEST */
	/*      GL_DEPTH_TEST */
	/*      GL_CLIP_PLANE0 */
	/*      GL_CLIP_PLANE1 */
	/*      GL_CLIP_PLANE2 */
	/*      GL_CLIP_PLANE3 */
	/*      GL_CLIP_PLANE4 */
	/*      GL_CLIP_PLANE5 */
	/*      GL_LIGHT0 */
	/*      GL_LIGHT1 */
	/*      GL_LIGHT2 */
	/*      GL_LIGHT3 */
	/*      GL_LIGHT4 */
	/*      GL_LIGHT5 */
	/*      GL_LIGHT6 */
	/*      GL_LIGHT7 */
	/*      GL_TEXTURE_GEN_S */
	/*      GL_TEXTURE_GEN_T */
	/*      GL_TEXTURE_GEN_R */
	/*      GL_TEXTURE_GEN_Q */
	/*      GL_MAP1_VERTEX_3 */
	/*      GL_MAP1_VERTEX_4 */
	/*      GL_MAP1_COLOR_4 */
	/*      GL_MAP1_INDEX */
	/*      GL_MAP1_NORMAL */
	/*      GL_MAP1_TEXTURE_COORD_1 */
	/*      GL_MAP1_TEXTURE_COORD_2 */
	/*      GL_MAP1_TEXTURE_COORD_3 */
	/*      GL_MAP1_TEXTURE_COORD_4 */
	/*      GL_MAP2_VERTEX_3 */
	/*      GL_MAP2_VERTEX_4 */
	/*      GL_MAP2_COLOR_4 */
	/*      GL_MAP2_INDEX */
	/*      GL_MAP2_NORMAL */
	/*      GL_MAP2_TEXTURE_COORD_1 */
	/*      GL_MAP2_TEXTURE_COORD_2 */
	/*      GL_MAP2_TEXTURE_COORD_3 */
	/*      GL_MAP2_TEXTURE_COORD_4 */
	/*      GL_POINT_SMOOTH */
	/*      GL_LINE_SMOOTH */
	/*      GL_POLYGON_SMOOTH */
	/*      GL_SCISSOR_TEST */
	/*      GL_COLOR_MATERIAL */
	/*      GL_NORMALIZE */
	/*      GL_AUTO_NORMAL */
	/*      GL_VERTEX_ARRAY */
	/*      GL_NORMAL_ARRAY */
	/*      GL_COLOR_ARRAY */
	/*      GL_INDEX_ARRAY */
	/*      GL_TEXTURE_COORD_ARRAY */
	/*      GL_EDGE_FLAG_ARRAY */
	/*      GL_POLYGON_OFFSET_POINT */
	/*      GL_POLYGON_OFFSET_LINE */
	/*      GL_POLYGON_OFFSET_FILL */

	/* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505

	/* FeedBackMode */
#define GL_2D                             0x0600
#define GL_3D                             0x0601
#define GL_3D_COLOR                       0x0602
#define GL_3D_COLOR_TEXTURE               0x0603
#define GL_4D_COLOR_TEXTURE               0x0604

	/* FeedBackToken */
#define GL_PASS_THROUGH_TOKEN             0x0700
#define GL_POINT_TOKEN                    0x0701
#define GL_LINE_TOKEN                     0x0702
#define GL_POLYGON_TOKEN                  0x0703
#define GL_BITMAP_TOKEN                   0x0704
#define GL_DRAW_PIXEL_TOKEN               0x0705
#define GL_COPY_PIXEL_TOKEN               0x0706
#define GL_LINE_RESET_TOKEN               0x0707

	/* FogMode */
	/*      GL_LINEAR */
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801


	/* FogParameter */
	/*      GL_FOG_COLOR */
	/*      GL_FOG_DENSITY */
	/*      GL_FOG_END */
	/*      GL_FOG_INDEX */
	/*      GL_FOG_MODE */
	/*      GL_FOG_START */

	/* FrontFaceDirection */
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

	/* GetMapTarget */
#define GL_COEFF                          0x0A00
#define GL_ORDER                          0x0A01
#define GL_DOMAIN                         0x0A02

	/* GetPixelMap */
	/*      GL_PIXEL_MAP_I_TO_I */
	/*      GL_PIXEL_MAP_S_TO_S */
	/*      GL_PIXEL_MAP_I_TO_R */
	/*      GL_PIXEL_MAP_I_TO_G */
	/*      GL_PIXEL_MAP_I_TO_B */
	/*      GL_PIXEL_MAP_I_TO_A */
	/*      GL_PIXEL_MAP_R_TO_R */
	/*      GL_PIXEL_MAP_G_TO_G */
	/*      GL_PIXEL_MAP_B_TO_B */
	/*      GL_PIXEL_MAP_A_TO_A */

	/* GetPointerTarget */
	/*      GL_VERTEX_ARRAY_POINTER */
	/*      GL_NORMAL_ARRAY_POINTER */
	/*      GL_COLOR_ARRAY_POINTER */
	/*      GL_INDEX_ARRAY_POINTER */
	/*      GL_TEXTURE_COORD_ARRAY_POINTER */
	/*      GL_EDGE_FLAG_ARRAY_POINTER */

	/* GetTarget */
#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_INDEX                  0x0B01
#define GL_CURRENT_NORMAL                 0x0B02
#define GL_CURRENT_TEXTURE_COORDS         0x0B03
#define GL_CURRENT_RASTER_COLOR           0x0B04
#define GL_CURRENT_RASTER_INDEX           0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS  0x0B06
#define GL_CURRENT_RASTER_POSITION        0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID  0x0B08
#define GL_CURRENT_RASTER_DISTANCE        0x0B09
#define GL_POINT_SMOOTH                   0x0B10
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_LINE_STIPPLE                   0x0B24
#define GL_LINE_STIPPLE_PATTERN           0x0B25
#define GL_LINE_STIPPLE_REPEAT            0x0B26
#define GL_LIST_MODE                      0x0B30
#define GL_MAX_LIST_NESTING               0x0B31
#define GL_LIST_BASE                      0x0B32
#define GL_LIST_INDEX                     0x0B33
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_POLYGON_STIPPLE                0x0B42
#define GL_EDGE_FLAG                      0x0B43
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_LIGHTING                       0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GL_SHADE_MODEL                    0x0B54
#define GL_COLOR_MATERIAL_FACE            0x0B55
#define GL_COLOR_MATERIAL_PARAMETER       0x0B56
#define GL_COLOR_MATERIAL                 0x0B57
#define GL_FOG                            0x0B60
#define GL_FOG_INDEX                      0x0B61
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_ACCUM_CLEAR_VALUE              0x0B80
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_MATRIX_MODE                    0x0BA0
#define GL_NORMALIZE                      0x0BA1
#define GL_VIEWPORT                       0x0BA2
#define GL_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL_PROJECTION_STACK_DEPTH         0x0BA4
#define GL_TEXTURE_STACK_DEPTH            0x0BA5
#define GL_MODELVIEW_MATRIX               0x0BA6
#define GL_PROJECTION_MATRIX              0x0BA7
#define GL_TEXTURE_MATRIX                 0x0BA8
#define GL_ATTRIB_STACK_DEPTH             0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH      0x0BB1
#define GL_ALPHA_TEST                     0x0BC0
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_INDEX_LOGIC_OP                 0x0BF1
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_AUX_BUFFERS                    0x0C00
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_INDEX_CLEAR_VALUE              0x0C20
#define GL_INDEX_WRITEMASK                0x0C21
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_INDEX_MODE                     0x0C30
#define GL_RGBA_MODE                      0x0C31
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_RENDER_MODE                    0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL_POINT_SMOOTH_HINT              0x0C51
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_FOG_HINT                       0x0C54
#define GL_TEXTURE_GEN_S                  0x0C60
#define GL_TEXTURE_GEN_T                  0x0C61
#define GL_TEXTURE_GEN_R                  0x0C62
#define GL_TEXTURE_GEN_Q                  0x0C63
#define GL_PIXEL_MAP_I_TO_I               0x0C70
#define GL_PIXEL_MAP_S_TO_S               0x0C71
#define GL_PIXEL_MAP_I_TO_R               0x0C72
#define GL_PIXEL_MAP_I_TO_G               0x0C73
#define GL_PIXEL_MAP_I_TO_B               0x0C74
#define GL_PIXEL_MAP_I_TO_A               0x0C75
#define GL_PIXEL_MAP_R_TO_R               0x0C76
#define GL_PIXEL_MAP_G_TO_G               0x0C77
#define GL_PIXEL_MAP_B_TO_B               0x0C78
#define GL_PIXEL_MAP_A_TO_A               0x0C79
#define GL_PIXEL_MAP_I_TO_I_SIZE          0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE          0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE          0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE          0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE          0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE          0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE          0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE          0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE          0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE          0x0CB9
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAP_COLOR                      0x0D10
#define GL_MAP_STENCIL                    0x0D11
#define GL_INDEX_SHIFT                    0x0D12
#define GL_INDEX_OFFSET                   0x0D13
#define GL_RED_SCALE                      0x0D14
#define GL_RED_BIAS                       0x0D15
#define GL_ZOOM_X                         0x0D16
#define GL_ZOOM_Y                         0x0D17
#define GL_GREEN_SCALE                    0x0D18
#define GL_GREEN_BIAS                     0x0D19
#define GL_BLUE_SCALE                     0x0D1A
#define GL_BLUE_BIAS                      0x0D1B
#define GL_ALPHA_SCALE                    0x0D1C
#define GL_ALPHA_BIAS                     0x0D1D
#define GL_DEPTH_SCALE                    0x0D1E
#define GL_DEPTH_BIAS                     0x0D1F
#define GL_MAX_EVAL_ORDER                 0x0D30
#define GL_MAX_LIGHTS                     0x0D31
#define GL_MAX_CLIP_PLANES                0x0D32
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_PIXEL_MAP_TABLE            0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH         0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL_MAX_NAME_STACK_DEPTH           0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH  0x0D3B
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_INDEX_BITS                     0x0D51
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_ACCUM_RED_BITS                 0x0D58
#define GL_ACCUM_GREEN_BITS               0x0D59
#define GL_ACCUM_BLUE_BITS                0x0D5A
#define GL_ACCUM_ALPHA_BITS               0x0D5B
#define GL_NAME_STACK_DEPTH               0x0D70
#define GL_AUTO_NORMAL                    0x0D80
#define GL_MAP1_COLOR_4                   0x0D90
#define GL_MAP1_INDEX                     0x0D91
#define GL_MAP1_NORMAL                    0x0D92
#define GL_MAP1_TEXTURE_COORD_1           0x0D93
#define GL_MAP1_TEXTURE_COORD_2           0x0D94
#define GL_MAP1_TEXTURE_COORD_3           0x0D95
#define GL_MAP1_TEXTURE_COORD_4           0x0D96
#define GL_MAP1_VERTEX_3                  0x0D97
#define GL_MAP1_VERTEX_4                  0x0D98
#define GL_MAP2_COLOR_4                   0x0DB0
#define GL_MAP2_INDEX                     0x0DB1
#define GL_MAP2_NORMAL                    0x0DB2
#define GL_MAP2_TEXTURE_COORD_1           0x0DB3
#define GL_MAP2_TEXTURE_COORD_2           0x0DB4
#define GL_MAP2_TEXTURE_COORD_3           0x0DB5
#define GL_MAP2_TEXTURE_COORD_4           0x0DB6
#define GL_MAP2_VERTEX_3                  0x0DB7
#define GL_MAP2_VERTEX_4                  0x0DB8
#define GL_MAP1_GRID_DOMAIN               0x0DD0
#define GL_MAP1_GRID_SEGMENTS             0x0DD1
#define GL_MAP2_GRID_DOMAIN               0x0DD2
#define GL_MAP2_GRID_SEGMENTS             0x0DD3
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER        0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE           0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE           0x0DF2
#define GL_SELECTION_BUFFER_POINTER       0x0DF3
#define GL_SELECTION_BUFFER_SIZE          0x0DF4
	/*      GL_TEXTURE_BINDING_1D */
	/*      GL_TEXTURE_BINDING_2D */
	/*      GL_VERTEX_ARRAY */
	/*      GL_NORMAL_ARRAY */
	/*      GL_COLOR_ARRAY */
	/*      GL_INDEX_ARRAY */
	/*      GL_TEXTURE_COORD_ARRAY */
	/*      GL_EDGE_FLAG_ARRAY */
	/*      GL_VERTEX_ARRAY_SIZE */
	/*      GL_VERTEX_ARRAY_TYPE */
	/*      GL_VERTEX_ARRAY_STRIDE */
	/*      GL_NORMAL_ARRAY_TYPE */
	/*      GL_NORMAL_ARRAY_STRIDE */
	/*      GL_COLOR_ARRAY_SIZE */
	/*      GL_COLOR_ARRAY_TYPE */
	/*      GL_COLOR_ARRAY_STRIDE */
	/*      GL_INDEX_ARRAY_TYPE */
	/*      GL_INDEX_ARRAY_STRIDE */
	/*      GL_TEXTURE_COORD_ARRAY_SIZE */
	/*      GL_TEXTURE_COORD_ARRAY_TYPE */
	/*      GL_TEXTURE_COORD_ARRAY_STRIDE */
	/*      GL_EDGE_FLAG_ARRAY_STRIDE */
	/*      GL_POLYGON_OFFSET_FACTOR */
	/*      GL_POLYGON_OFFSET_UNITS */

	/* GetTextureParameter */
	/*      GL_TEXTURE_MAG_FILTER */
	/*      GL_TEXTURE_MIN_FILTER */
	/*      GL_TEXTURE_WRAP_S */
	/*      GL_TEXTURE_WRAP_T */
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_TEXTURE_BORDER                 0x1005
	/*      GL_TEXTURE_RED_SIZE */
	/*      GL_TEXTURE_GREEN_SIZE */
	/*      GL_TEXTURE_BLUE_SIZE */
	/*      GL_TEXTURE_ALPHA_SIZE */
	/*      GL_TEXTURE_LUMINANCE_SIZE */
	/*      GL_TEXTURE_INTENSITY_SIZE */
	/*      GL_TEXTURE_PRIORITY */
	/*      GL_TEXTURE_RESIDENT */

	/* HintMode */
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102

	/* HintTarget */
	/*      GL_PERSPECTIVE_CORRECTION_HINT */
	/*      GL_POINT_SMOOTH_HINT */
	/*      GL_LINE_SMOOTH_HINT */
	/*      GL_POLYGON_SMOOTH_HINT */
	/*      GL_FOG_HINT */
	/*      GL_PHONG_HINT */

	/* IndexPointerType */
	/*      GL_SHORT */
	/*      GL_INT */
	/*      GL_FLOAT */
	/*      GL_DOUBLE */

	/* LightModelParameter */
	/*      GL_LIGHT_MODEL_AMBIENT */
	/*      GL_LIGHT_MODEL_LOCAL_VIEWER */
	/*      GL_LIGHT_MODEL_TWO_SIDE */

	/* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

	/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

	/* InterleavedArrays */
	/*      GL_V2F */
	/*      GL_V3F */
	/*      GL_C4UB_V2F */
	/*      GL_C4UB_V3F */
	/*      GL_C3F_V3F */
	/*      GL_N3F_V3F */
	/*      GL_C4F_N3F_V3F */
	/*      GL_T2F_V3F */
	/*      GL_T4F_V4F */
	/*      GL_T2F_C4UB_V3F */
	/*      GL_T2F_C3F_V3F */
	/*      GL_T2F_N3F_V3F */
	/*      GL_T2F_C4F_N3F_V3F */
	/*      GL_T4F_C4F_N3F_V4F */

	/* ListMode */
#define GL_COMPILE                        0x1300
#define GL_COMPILE_AND_EXECUTE            0x1301

	/* ListNameType */
	/*      GL_BYTE */
	/*      GL_UNSIGNED_BYTE */
	/*      GL_SHORT */
	/*      GL_UNSIGNED_SHORT */
	/*      GL_INT */
	/*      GL_UNSIGNED_INT */
	/*      GL_FLOAT */
	/*      GL_2_BYTES */
	/*      GL_3_BYTES */
	/*      GL_4_BYTES */

	/* LogicOp */
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

	/* MapTarget */
	/*      GL_MAP1_COLOR_4 */
	/*      GL_MAP1_INDEX */
	/*      GL_MAP1_NORMAL */
	/*      GL_MAP1_TEXTURE_COORD_1 */
	/*      GL_MAP1_TEXTURE_COORD_2 */
	/*      GL_MAP1_TEXTURE_COORD_3 */
	/*      GL_MAP1_TEXTURE_COORD_4 */
	/*      GL_MAP1_VERTEX_3 */
	/*      GL_MAP1_VERTEX_4 */
	/*      GL_MAP2_COLOR_4 */
	/*      GL_MAP2_INDEX */
	/*      GL_MAP2_NORMAL */
	/*      GL_MAP2_TEXTURE_COORD_1 */
	/*      GL_MAP2_TEXTURE_COORD_2 */
	/*      GL_MAP2_TEXTURE_COORD_3 */
	/*      GL_MAP2_TEXTURE_COORD_4 */
	/*      GL_MAP2_VERTEX_3 */
	/*      GL_MAP2_VERTEX_4 */

	/* MaterialFace */
	/*      GL_FRONT */
	/*      GL_BACK */
	/*      GL_FRONT_AND_BACK */

	/* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
#define GL_COLOR_INDEXES                  0x1603
	/*      GL_AMBIENT */
	/*      GL_DIFFUSE */
	/*      GL_SPECULAR */

	/* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

	/* MeshMode1 */
	/*      GL_POINT */
	/*      GL_LINE */

	/* MeshMode2 */
	/*      GL_POINT */
	/*      GL_LINE */
	/*      GL_FILL */

	/* NormalPointerType */
	/*      GL_BYTE */
	/*      GL_SHORT */
	/*      GL_INT */
	/*      GL_FLOAT */
	/*      GL_DOUBLE */

	/* PixelCopyType */
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802

	/* PixelFormat */
#define GL_COLOR_INDEX                    0x1900
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

	/* PixelMap */
	/*      GL_PIXEL_MAP_I_TO_I */
	/*      GL_PIXEL_MAP_S_TO_S */
	/*      GL_PIXEL_MAP_I_TO_R */
	/*      GL_PIXEL_MAP_I_TO_G */
	/*      GL_PIXEL_MAP_I_TO_B */
	/*      GL_PIXEL_MAP_I_TO_A */
	/*      GL_PIXEL_MAP_R_TO_R */
	/*      GL_PIXEL_MAP_G_TO_G */
	/*      GL_PIXEL_MAP_B_TO_B */
	/*      GL_PIXEL_MAP_A_TO_A */

	/* PixelStore */
	/*      GL_UNPACK_SWAP_BYTES */
	/*      GL_UNPACK_LSB_FIRST */
	/*      GL_UNPACK_ROW_LENGTH */
	/*      GL_UNPACK_SKIP_ROWS */
	/*      GL_UNPACK_SKIP_PIXELS */
	/*      GL_UNPACK_ALIGNMENT */
	/*      GL_PACK_SWAP_BYTES */
	/*      GL_PACK_LSB_FIRST */
	/*      GL_PACK_ROW_LENGTH */
	/*      GL_PACK_SKIP_ROWS */
	/*      GL_PACK_SKIP_PIXELS */
	/*      GL_PACK_ALIGNMENT */

	/* PixelTransfer */
	/*      GL_MAP_COLOR */
	/*      GL_MAP_STENCIL */
	/*      GL_INDEX_SHIFT */
	/*      GL_INDEX_OFFSET */
	/*      GL_RED_SCALE */
	/*      GL_RED_BIAS */
	/*      GL_GREEN_SCALE */
	/*      GL_GREEN_BIAS */
	/*      GL_BLUE_SCALE */
	/*      GL_BLUE_BIAS */
	/*      GL_ALPHA_SCALE */
	/*      GL_ALPHA_BIAS */
	/*      GL_DEPTH_SCALE */
	/*      GL_DEPTH_BIAS */

	/* PixelType */
#define GL_BITMAP                         0x1A00
	/*      GL_BYTE */
	/*      GL_UNSIGNED_BYTE */
	/*      GL_SHORT */
	/*      GL_UNSIGNED_SHORT */
	/*      GL_INT */
	/*      GL_UNSIGNED_INT */
	/*      GL_FLOAT */

	/* PolygonMode */
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

	/* ReadBufferMode */
	/*      GL_FRONT_LEFT */
	/*      GL_FRONT_RIGHT */
	/*      GL_BACK_LEFT */
	/*      GL_BACK_RIGHT */
	/*      GL_FRONT */
	/*      GL_BACK */
	/*      GL_LEFT */
	/*      GL_RIGHT */
	/*      GL_AUX0 */
	/*      GL_AUX1 */
	/*      GL_AUX2 */
	/*      GL_AUX3 */

	/* RenderingMode */
#define GL_RENDER                         0x1C00
#define GL_FEEDBACK                       0x1C01
#define GL_SELECT                         0x1C02

	/* ShadingModel */
#define GL_FLAT                           0x1D00
#define GL_SMOOTH                         0x1D01


	/* StencilFunction */
	/*      GL_NEVER */
	/*      GL_LESS */
	/*      GL_EQUAL */
	/*      GL_LEQUAL */
	/*      GL_GREATER */
	/*      GL_NOTEQUAL */
	/*      GL_GEQUAL */
	/*      GL_ALWAYS */

	/* StencilOp */
	/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
	/*      GL_INVERT */

	/* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

	/* TextureCoordName */
#define GL_S                              0x2000
#define GL_T                              0x2001
#define GL_R                              0x2002
#define GL_Q                              0x2003

	/* TexCoordPointerType */
	/*      GL_SHORT */
	/*      GL_INT */
	/*      GL_FLOAT */
	/*      GL_DOUBLE */

	/* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
	/*      GL_BLEND */
	/*      GL_REPLACE */

	/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

	/* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

	/* TextureGenMode */
#define GL_EYE_LINEAR                     0x2400
#define GL_OBJECT_LINEAR                  0x2401
#define GL_SPHERE_MAP                     0x2402

	/* TextureGenParameter */
#define GL_TEXTURE_GEN_MODE               0x2500
#define GL_OBJECT_PLANE                   0x2501
#define GL_EYE_PLANE                      0x2502

	/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

	/* TextureMinFilter */
	/*      GL_NEAREST */
	/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

	/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
	/*      GL_TEXTURE_BORDER_COLOR */
	/*      GL_TEXTURE_PRIORITY */

	/* TextureTarget */
	/*      GL_TEXTURE_1D */
	/*      GL_TEXTURE_2D */
	/*      GL_PROXY_TEXTURE_1D */
	/*      GL_PROXY_TEXTURE_2D */

	/* TextureWrapMode */
#define GL_CLAMP                          0x2900
#define GL_REPEAT                         0x2901

	/* VertexPointerType */
	/*      GL_SHORT */
	/*      GL_INT */
	/*      GL_FLOAT */
	/*      GL_DOUBLE */

	/* ClientAttribMask */
#define GL_CLIENT_PIXEL_STORE_BIT         0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT        0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS         0xffffffff

	/* polygon_offset */
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037

	/* texture */
#define GL_ALPHA4                         0x803B
#define GL_ALPHA8                         0x803C
#define GL_ALPHA12                        0x803D
#define GL_ALPHA16                        0x803E
#define GL_LUMINANCE4                     0x803F
#define GL_LUMINANCE8                     0x8040
#define GL_LUMINANCE12                    0x8041
#define GL_LUMINANCE16                    0x8042
#define GL_LUMINANCE4_ALPHA4              0x8043
#define GL_LUMINANCE6_ALPHA2              0x8044
#define GL_LUMINANCE8_ALPHA8              0x8045
#define GL_LUMINANCE12_ALPHA4             0x8046
#define GL_LUMINANCE12_ALPHA12            0x8047
#define GL_LUMINANCE16_ALPHA16            0x8048
#define GL_INTENSITY                      0x8049
#define GL_INTENSITY4                     0x804A
#define GL_INTENSITY8                     0x804B
#define GL_INTENSITY12                    0x804C
#define GL_INTENSITY16                    0x804D
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_TEXTURE_LUMINANCE_SIZE         0x8060
#define GL_TEXTURE_INTENSITY_SIZE         0x8061
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064

	/* texture_object */
#define GL_TEXTURE_PRIORITY               0x8066
#define GL_TEXTURE_RESIDENT               0x8067
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069

	/* vertex_array */
#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_INDEX_ARRAY                    0x8077
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_EDGE_FLAG_ARRAY                0x8079
#define GL_VERTEX_ARRAY_SIZE              0x807A
#define GL_VERTEX_ARRAY_TYPE              0x807B
#define GL_VERTEX_ARRAY_STRIDE            0x807C
#define GL_NORMAL_ARRAY_TYPE              0x807E
#define GL_NORMAL_ARRAY_STRIDE            0x807F
#define GL_COLOR_ARRAY_SIZE               0x8081
#define GL_COLOR_ARRAY_TYPE               0x8082
#define GL_COLOR_ARRAY_STRIDE             0x8083
#define GL_INDEX_ARRAY_TYPE               0x8085
#define GL_INDEX_ARRAY_STRIDE             0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE         0x808C
#define GL_VERTEX_ARRAY_POINTER           0x808E
#define GL_NORMAL_ARRAY_POINTER           0x808F
#define GL_COLOR_ARRAY_POINTER            0x8090
#define GL_INDEX_ARRAY_POINTER            0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER        0x8093
#define GL_V2F                            0x2A20
#define GL_V3F                            0x2A21
#define GL_C4UB_V2F                       0x2A22
#define GL_C4UB_V3F                       0x2A23
#define GL_C3F_V3F                        0x2A24
#define GL_N3F_V3F                        0x2A25
#define GL_C4F_N3F_V3F                    0x2A26
#define GL_T2F_V3F                        0x2A27
#define GL_T4F_V4F                        0x2A28
#define GL_T2F_C4UB_V3F                   0x2A29
#define GL_T2F_C3F_V3F                    0x2A2A
#define GL_T2F_N3F_V3F                    0x2A2B
#define GL_T2F_C4F_N3F_V3F                0x2A2C
#define GL_T4F_C4F_N3F_V4F                0x2A2D

	/* Extensions */
#define GL_EXT_vertex_array               1
#define GL_EXT_bgra                       1
#define GL_EXT_paletted_texture           1
#define GL_WIN_swap_hint                  1
#define GL_WIN_draw_range_elements        1
	// #define GL_WIN_phong_shading              1
	// #define GL_WIN_specular_fog               1

	/* EXT_vertex_array */
#define GL_VERTEX_ARRAY_EXT               0x8074
#define GL_NORMAL_ARRAY_EXT               0x8075
#define GL_COLOR_ARRAY_EXT                0x8076
#define GL_INDEX_ARRAY_EXT                0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT        0x8078
#define GL_EDGE_FLAG_ARRAY_EXT            0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT          0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT          0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT        0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT         0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT          0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT        0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT         0x8080
#define GL_COLOR_ARRAY_SIZE_EXT           0x8081
#define GL_COLOR_ARRAY_TYPE_EXT           0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT         0x8083
#define GL_COLOR_ARRAY_COUNT_EXT          0x8084
#define GL_INDEX_ARRAY_TYPE_EXT           0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT         0x8086
#define GL_INDEX_ARRAY_COUNT_EXT          0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT   0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT   0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT  0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT     0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT      0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT       0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT       0x808F
#define GL_COLOR_ARRAY_POINTER_EXT        0x8090
#define GL_INDEX_ARRAY_POINTER_EXT        0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT    0x8093
#define GL_DOUBLE_EXT                     GL_DOUBLE

	/* EXT_bgra */
#define GL_BGR_EXT                        0x80E0
#define GL_BGRA_EXT                       0x80E1

	/* EXT_paletted_texture */

	/* These must match the GL_COLOR_TABLE_*_SGI enumerants */
#define GL_COLOR_TABLE_FORMAT_EXT         0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT          0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT       0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT     0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT      0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT     0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT 0x80DF

#define GL_COLOR_INDEX1_EXT               0x80E2
#define GL_COLOR_INDEX2_EXT               0x80E3
#define GL_COLOR_INDEX4_EXT               0x80E4
#define GL_COLOR_INDEX8_EXT               0x80E5
#define GL_COLOR_INDEX12_EXT              0x80E6
#define GL_COLOR_INDEX16_EXT              0x80E7

	/* WIN_draw_range_elements */
#define GL_MAX_ELEMENTS_VERTICES_WIN      0x80E8
#define GL_MAX_ELEMENTS_INDICES_WIN       0x80E9

	/* WIN_phong_shading */
#define GL_PHONG_WIN                      0x80EA 
#define GL_PHONG_HINT_WIN                 0x80EB 

	/* WIN_specular_fog */
#define GL_FOG_SPECULAR_TEXTURE_WIN       0x80EC

	/* For compatibility with OpenGL v1.0 */
#define GL_LOGIC_OP GL_INDEX_LOGIC_OP
#define GL_TEXTURE_COMPONENTS GL_TEXTURE_INTERNAL_FORMAT

	/*************************************************************/

	WINGDIAPI void APIENTRY glAccum(GLenum op, GLfloat value);
	WINGDIAPI void APIENTRY glAlphaFunc(GLenum func, GLclampf ref);
	WINGDIAPI GLboolean APIENTRY glAreTexturesResident(GLsizei n, const GLuint *textures, GLboolean *residences);
	WINGDIAPI void APIENTRY glArrayElement(GLint i);
	WINGDIAPI void APIENTRY glBegin(GLenum mode);
	WINGDIAPI void APIENTRY glBindTexture(GLenum target, GLuint texture);
	WINGDIAPI void APIENTRY glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
	WINGDIAPI void APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor);
	WINGDIAPI void APIENTRY glCallList(GLuint list);
	WINGDIAPI void APIENTRY glCallLists(GLsizei n, GLenum type, const GLvoid *lists);
	WINGDIAPI void APIENTRY glClear(GLbitfield mask);
	WINGDIAPI void APIENTRY glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	WINGDIAPI void APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	WINGDIAPI void APIENTRY glClearDepth(GLclampd depth);
	WINGDIAPI void APIENTRY glClearIndex(GLfloat c);
	WINGDIAPI void APIENTRY glClearStencil(GLint s);
	WINGDIAPI void APIENTRY glClipPlane(GLenum plane, const GLdouble *equation);
	WINGDIAPI void APIENTRY glColor3b(GLbyte red, GLbyte green, GLbyte blue);
	WINGDIAPI void APIENTRY glColor3bv(const GLbyte *v);
	WINGDIAPI void APIENTRY glColor3d(GLdouble red, GLdouble green, GLdouble blue);
	WINGDIAPI void APIENTRY glColor3dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glColor3f(GLfloat red, GLfloat green, GLfloat blue);
	WINGDIAPI void APIENTRY glColor3fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glColor3i(GLint red, GLint green, GLint blue);
	WINGDIAPI void APIENTRY glColor3iv(const GLint *v);
	WINGDIAPI void APIENTRY glColor3s(GLshort red, GLshort green, GLshort blue);
	WINGDIAPI void APIENTRY glColor3sv(const GLshort *v);
	WINGDIAPI void APIENTRY glColor3ub(GLubyte red, GLubyte green, GLubyte blue);
	WINGDIAPI void APIENTRY glColor3ubv(const GLubyte *v);
	WINGDIAPI void APIENTRY glColor3ui(GLuint red, GLuint green, GLuint blue);
	WINGDIAPI void APIENTRY glColor3uiv(const GLuint *v);
	WINGDIAPI void APIENTRY glColor3us(GLushort red, GLushort green, GLushort blue);
	WINGDIAPI void APIENTRY glColor3usv(const GLushort *v);
	WINGDIAPI void APIENTRY glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
	WINGDIAPI void APIENTRY glColor4bv(const GLbyte *v);
	WINGDIAPI void APIENTRY glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
	WINGDIAPI void APIENTRY glColor4dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	WINGDIAPI void APIENTRY glColor4fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glColor4i(GLint red, GLint green, GLint blue, GLint alpha);
	WINGDIAPI void APIENTRY glColor4iv(const GLint *v);
	WINGDIAPI void APIENTRY glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha);
	WINGDIAPI void APIENTRY glColor4sv(const GLshort *v);
	WINGDIAPI void APIENTRY glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
	WINGDIAPI void APIENTRY glColor4ubv(const GLubyte *v);
	WINGDIAPI void APIENTRY glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha);
	WINGDIAPI void APIENTRY glColor4uiv(const GLuint *v);
	WINGDIAPI void APIENTRY glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha);
	WINGDIAPI void APIENTRY glColor4usv(const GLushort *v);
	WINGDIAPI void APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	WINGDIAPI void APIENTRY glColorMaterial(GLenum face, GLenum mode);
	WINGDIAPI void APIENTRY glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
	WINGDIAPI void APIENTRY glCopyTexImage1D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
	WINGDIAPI void APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	WINGDIAPI void APIENTRY glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	WINGDIAPI void APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	WINGDIAPI void APIENTRY glCullFace(GLenum mode);
	WINGDIAPI void APIENTRY glDeleteLists(GLuint list, GLsizei range);
	WINGDIAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures);
	WINGDIAPI void APIENTRY glDepthFunc(GLenum func);
	WINGDIAPI void APIENTRY glDepthMask(GLboolean flag);
	WINGDIAPI void APIENTRY glDepthRange(GLclampd zNear, GLclampd zFar);
	WINGDIAPI void APIENTRY glDisable(GLenum cap);
	WINGDIAPI void APIENTRY glDisableClientState(GLenum array);
	WINGDIAPI void APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count);
	WINGDIAPI void APIENTRY glDrawBuffer(GLenum mode);
	WINGDIAPI void APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
	WINGDIAPI void APIENTRY glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glEdgeFlag(GLboolean flag);
	WINGDIAPI void APIENTRY glEdgeFlagPointer(GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glEdgeFlagv(const GLboolean *flag);
	WINGDIAPI void APIENTRY glEnable(GLenum cap);
	WINGDIAPI void APIENTRY glEnableClientState(GLenum array);
	WINGDIAPI void APIENTRY glEnd(void);
	WINGDIAPI void APIENTRY glEndList(void);
	WINGDIAPI void APIENTRY glEvalCoord1d(GLdouble u);
	WINGDIAPI void APIENTRY glEvalCoord1dv(const GLdouble *u);
	WINGDIAPI void APIENTRY glEvalCoord1f(GLfloat u);
	WINGDIAPI void APIENTRY glEvalCoord1fv(const GLfloat *u);
	WINGDIAPI void APIENTRY glEvalCoord2d(GLdouble u, GLdouble v);
	WINGDIAPI void APIENTRY glEvalCoord2dv(const GLdouble *u);
	WINGDIAPI void APIENTRY glEvalCoord2f(GLfloat u, GLfloat v);
	WINGDIAPI void APIENTRY glEvalCoord2fv(const GLfloat *u);
	WINGDIAPI void APIENTRY glEvalMesh1(GLenum mode, GLint i1, GLint i2);
	WINGDIAPI void APIENTRY glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
	WINGDIAPI void APIENTRY glEvalPoint1(GLint i);
	WINGDIAPI void APIENTRY glEvalPoint2(GLint i, GLint j);
	WINGDIAPI void APIENTRY glFeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer);
	WINGDIAPI void APIENTRY glFinish(void);
	WINGDIAPI void APIENTRY glFlush(void);
	WINGDIAPI void APIENTRY glFogf(GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glFogfv(GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glFogi(GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glFogiv(GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glFrontFace(GLenum mode);
	WINGDIAPI void APIENTRY glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	WINGDIAPI GLuint APIENTRY glGenLists(GLsizei range);
	WINGDIAPI void APIENTRY glGenTextures(GLsizei n, GLuint *textures);
	WINGDIAPI void APIENTRY glGetBooleanv(GLenum pname, GLboolean *params);
	WINGDIAPI void APIENTRY glGetClipPlane(GLenum plane, GLdouble *equation);
	WINGDIAPI void APIENTRY glGetDoublev(GLenum pname, GLdouble *params);
	WINGDIAPI GLenum APIENTRY glGetError(void);
	WINGDIAPI void APIENTRY glGetFloatv(GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetIntegerv(GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetLightfv(GLenum light, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetLightiv(GLenum light, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetMapdv(GLenum target, GLenum query, GLdouble *v);
	WINGDIAPI void APIENTRY glGetMapfv(GLenum target, GLenum query, GLfloat *v);
	WINGDIAPI void APIENTRY glGetMapiv(GLenum target, GLenum query, GLint *v);
	WINGDIAPI void APIENTRY glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetMaterialiv(GLenum face, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetPixelMapfv(GLenum map, GLfloat *values);
	WINGDIAPI void APIENTRY glGetPixelMapuiv(GLenum map, GLuint *values);
	WINGDIAPI void APIENTRY glGetPixelMapusv(GLenum map, GLushort *values);
	WINGDIAPI void APIENTRY glGetPointerv(GLenum pname, GLvoid* *params);
	WINGDIAPI void APIENTRY glGetPolygonStipple(GLubyte *mask);
	WINGDIAPI const GLubyte * APIENTRY glGetString(GLenum name);
	WINGDIAPI void APIENTRY glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexEnviv(GLenum target, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetTexGendv(GLenum coord, GLenum pname, GLdouble *params);
	WINGDIAPI void APIENTRY glGetTexGenfv(GLenum coord, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexGeniv(GLenum coord, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
	WINGDIAPI void APIENTRY glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glHint(GLenum target, GLenum mode);
	WINGDIAPI void APIENTRY glIndexMask(GLuint mask);
	WINGDIAPI void APIENTRY glIndexPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glIndexd(GLdouble c);
	WINGDIAPI void APIENTRY glIndexdv(const GLdouble *c);
	WINGDIAPI void APIENTRY glIndexf(GLfloat c);
	WINGDIAPI void APIENTRY glIndexfv(const GLfloat *c);
	WINGDIAPI void APIENTRY glIndexi(GLint c);
	WINGDIAPI void APIENTRY glIndexiv(const GLint *c);
	WINGDIAPI void APIENTRY glIndexs(GLshort c);
	WINGDIAPI void APIENTRY glIndexsv(const GLshort *c);
	WINGDIAPI void APIENTRY glIndexub(GLubyte c);
	WINGDIAPI void APIENTRY glIndexubv(const GLubyte *c);
	WINGDIAPI void APIENTRY glInitNames(void);
	WINGDIAPI void APIENTRY glInterleavedArrays(GLenum format, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI GLboolean APIENTRY glIsEnabled(GLenum cap);
	WINGDIAPI GLboolean APIENTRY glIsList(GLuint list);
	WINGDIAPI GLboolean APIENTRY glIsTexture(GLuint texture);
	WINGDIAPI void APIENTRY glLightModelf(GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glLightModelfv(GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glLightModeli(GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glLightModeliv(GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glLightf(GLenum light, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glLighti(GLenum light, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glLightiv(GLenum light, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glLineStipple(GLint factor, GLushort pattern);
	WINGDIAPI void APIENTRY glLineWidth(GLfloat width);
	WINGDIAPI void APIENTRY glListBase(GLuint base);
	WINGDIAPI void APIENTRY glLoadIdentity(void);
	WINGDIAPI void APIENTRY glLoadMatrixd(const GLdouble *m);
	WINGDIAPI void APIENTRY glLoadMatrixf(const GLfloat *m);
	WINGDIAPI void APIENTRY glLoadName(GLuint name);
	WINGDIAPI void APIENTRY glLogicOp(GLenum opcode);
	WINGDIAPI void APIENTRY glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
	WINGDIAPI void APIENTRY glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
	WINGDIAPI void APIENTRY glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
	WINGDIAPI void APIENTRY glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
	WINGDIAPI void APIENTRY glMapGrid1d(GLint un, GLdouble u1, GLdouble u2);
	WINGDIAPI void APIENTRY glMapGrid1f(GLint un, GLfloat u1, GLfloat u2);
	WINGDIAPI void APIENTRY glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
	WINGDIAPI void APIENTRY glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
	WINGDIAPI void APIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glMateriali(GLenum face, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glMaterialiv(GLenum face, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glMatrixMode(GLenum mode);
	WINGDIAPI void APIENTRY glMultMatrixd(const GLdouble *m);
	WINGDIAPI void APIENTRY glMultMatrixf(const GLfloat *m);
	WINGDIAPI void APIENTRY glNewList(GLuint list, GLenum mode);
	WINGDIAPI void APIENTRY glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz);
	WINGDIAPI void APIENTRY glNormal3bv(const GLbyte *v);
	WINGDIAPI void APIENTRY glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz);
	WINGDIAPI void APIENTRY glNormal3dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
	WINGDIAPI void APIENTRY glNormal3fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glNormal3i(GLint nx, GLint ny, GLint nz);
	WINGDIAPI void APIENTRY glNormal3iv(const GLint *v);
	WINGDIAPI void APIENTRY glNormal3s(GLshort nx, GLshort ny, GLshort nz);
	WINGDIAPI void APIENTRY glNormal3sv(const GLshort *v);
	WINGDIAPI void APIENTRY glNormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	WINGDIAPI void APIENTRY glPassThrough(GLfloat token);
	WINGDIAPI void APIENTRY glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat *values);
	WINGDIAPI void APIENTRY glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint *values);
	WINGDIAPI void APIENTRY glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort *values);
	WINGDIAPI void APIENTRY glPixelStoref(GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glPixelStorei(GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glPixelTransferf(GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glPixelTransferi(GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glPixelZoom(GLfloat xfactor, GLfloat yfactor);
	WINGDIAPI void APIENTRY glPointSize(GLfloat size);
	WINGDIAPI void APIENTRY glPolygonMode(GLenum face, GLenum mode);
	WINGDIAPI void APIENTRY glPolygonOffset(GLfloat factor, GLfloat units);
	WINGDIAPI void APIENTRY glPolygonStipple(const GLubyte *mask);
	WINGDIAPI void APIENTRY glPopAttrib(void);
	WINGDIAPI void APIENTRY glPopClientAttrib(void);
	WINGDIAPI void APIENTRY glPopMatrix(void);
	WINGDIAPI void APIENTRY glPopName(void);
	WINGDIAPI void APIENTRY glPrioritizeTextures(GLsizei n, const GLuint *textures, const GLclampf *priorities);
	WINGDIAPI void APIENTRY glPushAttrib(GLbitfield mask);
	WINGDIAPI void APIENTRY glPushClientAttrib(GLbitfield mask);
	WINGDIAPI void APIENTRY glPushMatrix(void);
	WINGDIAPI void APIENTRY glPushName(GLuint name);
	WINGDIAPI void APIENTRY glRasterPos2d(GLdouble x, GLdouble y);
	WINGDIAPI void APIENTRY glRasterPos2dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glRasterPos2f(GLfloat x, GLfloat y);
	WINGDIAPI void APIENTRY glRasterPos2fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glRasterPos2i(GLint x, GLint y);
	WINGDIAPI void APIENTRY glRasterPos2iv(const GLint *v);
	WINGDIAPI void APIENTRY glRasterPos2s(GLshort x, GLshort y);
	WINGDIAPI void APIENTRY glRasterPos2sv(const GLshort *v);
	WINGDIAPI void APIENTRY glRasterPos3d(GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glRasterPos3dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glRasterPos3f(GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glRasterPos3fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glRasterPos3i(GLint x, GLint y, GLint z);
	WINGDIAPI void APIENTRY glRasterPos3iv(const GLint *v);
	WINGDIAPI void APIENTRY glRasterPos3s(GLshort x, GLshort y, GLshort z);
	WINGDIAPI void APIENTRY glRasterPos3sv(const GLshort *v);
	WINGDIAPI void APIENTRY glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	WINGDIAPI void APIENTRY glRasterPos4dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	WINGDIAPI void APIENTRY glRasterPos4fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glRasterPos4i(GLint x, GLint y, GLint z, GLint w);
	WINGDIAPI void APIENTRY glRasterPos4iv(const GLint *v);
	WINGDIAPI void APIENTRY glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w);
	WINGDIAPI void APIENTRY glRasterPos4sv(const GLshort *v);
	WINGDIAPI void APIENTRY glReadBuffer(GLenum mode);
	WINGDIAPI void APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
	WINGDIAPI void APIENTRY glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	WINGDIAPI void APIENTRY glRectdv(const GLdouble *v1, const GLdouble *v2);
	WINGDIAPI void APIENTRY glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	WINGDIAPI void APIENTRY glRectfv(const GLfloat *v1, const GLfloat *v2);
	WINGDIAPI void APIENTRY glRecti(GLint x1, GLint y1, GLint x2, GLint y2);
	WINGDIAPI void APIENTRY glRectiv(const GLint *v1, const GLint *v2);
	WINGDIAPI void APIENTRY glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
	WINGDIAPI void APIENTRY glRectsv(const GLshort *v1, const GLshort *v2);
	WINGDIAPI GLint APIENTRY glRenderMode(GLenum mode);
	WINGDIAPI void APIENTRY glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glScaled(GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
	WINGDIAPI void APIENTRY glSelectBuffer(GLsizei size, GLuint *buffer);
	WINGDIAPI void APIENTRY glShadeModel(GLenum mode);
	WINGDIAPI void APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask);
	WINGDIAPI void APIENTRY glStencilMask(GLuint mask);
	WINGDIAPI void APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	WINGDIAPI void APIENTRY glTexCoord1d(GLdouble s);
	WINGDIAPI void APIENTRY glTexCoord1dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord1f(GLfloat s);
	WINGDIAPI void APIENTRY glTexCoord1fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord1i(GLint s);
	WINGDIAPI void APIENTRY glTexCoord1iv(const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord1s(GLshort s);
	WINGDIAPI void APIENTRY glTexCoord1sv(const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoord2d(GLdouble s, GLdouble t);
	WINGDIAPI void APIENTRY glTexCoord2dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord2f(GLfloat s, GLfloat t);
	WINGDIAPI void APIENTRY glTexCoord2fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord2i(GLint s, GLint t);
	WINGDIAPI void APIENTRY glTexCoord2iv(const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord2s(GLshort s, GLshort t);
	WINGDIAPI void APIENTRY glTexCoord2sv(const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoord3d(GLdouble s, GLdouble t, GLdouble r);
	WINGDIAPI void APIENTRY glTexCoord3dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord3f(GLfloat s, GLfloat t, GLfloat r);
	WINGDIAPI void APIENTRY glTexCoord3fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord3i(GLint s, GLint t, GLint r);
	WINGDIAPI void APIENTRY glTexCoord3iv(const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord3s(GLshort s, GLshort t, GLshort r);
	WINGDIAPI void APIENTRY glTexCoord3sv(const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	WINGDIAPI void APIENTRY glTexCoord4dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	WINGDIAPI void APIENTRY glTexCoord4fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord4i(GLint s, GLint t, GLint r, GLint q);
	WINGDIAPI void APIENTRY glTexCoord4iv(const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q);
	WINGDIAPI void APIENTRY glTexCoord4sv(const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glTexEnvf(GLenum target, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glTexGend(GLenum coord, GLenum pname, GLdouble param);
	WINGDIAPI void APIENTRY glTexGendv(GLenum coord, GLenum pname, const GLdouble *params);
	WINGDIAPI void APIENTRY glTexGenf(GLenum coord, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glTexGenfv(GLenum coord, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glTexGeni(GLenum coord, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glTexGeniv(GLenum coord, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTranslated(GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glVertex2d(GLdouble x, GLdouble y);
	WINGDIAPI void APIENTRY glVertex2dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glVertex2f(GLfloat x, GLfloat y);
	WINGDIAPI void APIENTRY glVertex2fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glVertex2i(GLint x, GLint y);
	WINGDIAPI void APIENTRY glVertex2iv(const GLint *v);
	WINGDIAPI void APIENTRY glVertex2s(GLshort x, GLshort y);
	WINGDIAPI void APIENTRY glVertex2sv(const GLshort *v);
	WINGDIAPI void APIENTRY glVertex3d(GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glVertex3dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glVertex3fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glVertex3i(GLint x, GLint y, GLint z);
	WINGDIAPI void APIENTRY glVertex3iv(const GLint *v);
	WINGDIAPI void APIENTRY glVertex3s(GLshort x, GLshort y, GLshort z);
	WINGDIAPI void APIENTRY glVertex3sv(const GLshort *v);
	WINGDIAPI void APIENTRY glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	WINGDIAPI void APIENTRY glVertex4dv(const GLdouble *v);
	WINGDIAPI void APIENTRY glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	WINGDIAPI void APIENTRY glVertex4fv(const GLfloat *v);
	WINGDIAPI void APIENTRY glVertex4i(GLint x, GLint y, GLint z, GLint w);
	WINGDIAPI void APIENTRY glVertex4iv(const GLint *v);
	WINGDIAPI void APIENTRY glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w);
	WINGDIAPI void APIENTRY glVertex4sv(const GLshort *v);
	WINGDIAPI void APIENTRY glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

	/* EXT_vertex_array */
	typedef void (APIENTRY * PFNGLARRAYELEMENTEXTPROC) (GLint i);
	typedef void (APIENTRY * PFNGLDRAWARRAYSEXTPROC) (GLenum mode, GLint first, GLsizei count);
	typedef void (APIENTRY * PFNGLVERTEXPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLNORMALPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLINDEXPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLTEXCOORDPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLEDGEFLAGPOINTEREXTPROC) (GLsizei stride, GLsizei count, const GLboolean *pointer);
	typedef void (APIENTRY * PFNGLGETPOINTERVEXTPROC) (GLenum pname, GLvoid* *params);
	typedef void (APIENTRY * PFNGLARRAYELEMENTARRAYEXTPROC)(GLenum mode, GLsizei count, const GLvoid* pi);

	/* WIN_draw_range_elements */
	typedef void (APIENTRY * PFNGLDRAWRANGEELEMENTSWINPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

	/* WIN_swap_hint */
	typedef void (APIENTRY * PFNGLADDSWAPHINTRECTWINPROC)  (GLint x, GLint y, GLsizei width, GLsizei height);

	/* EXT_paletted_texture */
	typedef void (APIENTRY * PFNGLCOLORTABLEEXTPROC)
		(GLenum target, GLenum internalFormat, GLsizei width, GLenum format,
		GLenum type, const GLvoid *data);
	typedef void (APIENTRY * PFNGLCOLORSUBTABLEEXTPROC)
		(GLenum target, GLsizei start, GLsizei count, GLenum format,
		GLenum type, const GLvoid *data);
	typedef void (APIENTRY * PFNGLGETCOLORTABLEEXTPROC)
		(GLenum target, GLenum format, GLenum type, GLvoid *data);
	typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)
		(GLenum target, GLenum pname, GLint *params);
	typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)
		(GLenum target, GLenum pname, GLfloat *params);

#ifdef __cplusplus
}
#endif

#endif /* __GL_H__ */
#endif /* __gl_h_ */


#ifndef RGB_COLORS_H
#define RGB_COLORS_H

//--------------------------------------------------------------------------------------------------//
//		Colors.h																					//
//																									//
//			 Author: Muhammad Saifullah Khan														//
//		Description: RGB values (in type double) for different colors. These definitions will be	//
//					 used to change the red, green, and blue color channels of Graphic objects.		//
//			   Date: Friday, May 22, 2015.															//
//																									//
//--------------------------------------------------------------------------------------------------//

#define Aquamarine			0.439216, 0.858824, 0.576471
#define BakersChoc			0.360000, 0.200000, 0.090000
#define Black				0.000000, 0.000000, 0.000000
#define Blue_Clr			0.000000, 0.000000, 1.000000
#define BlueViolet			0.623520, 0.372549, 0.623529
#define Brass				0.710000, 0.650000, 0.260000
#define BrightGold			0.850000, 0.850000, 0.100000
#define BronzeDark			0.550000, 0.470000, 0.140000
#define BronzeLight			0.650000, 0.490000, 0.240000
#define Brown				0.647059, 0.164706, 0.164706
#define CadetBlue			0.372549, 0.623529, 0.623529
#define CoolCopper			0.850000, 0.530000, 0.100000
#define Copper				0.720000, 0.450000, 0.200000
#define Coral				1.000000, 0.498039, 0.000000
#define CornflowerBlue		0.258824, 0.258824, 0.435294
#define Cyan				0.000000, 1.000000, 1.000000
#define DarkBrown			0.360000, 0.250000, 0.200000
#define DarkGreen			0.184314, 0.309804, 0.184314
#define DarkOliveGreen		0.309804, 0.309804, 0.184314
#define DarkOrchid			0.600000, 0.196078, 0.800000
#define DarkPurple			0.530000, 0.120000, 0.470000
#define DarkSlateBlue		0.419608, 0.137255, 0.556863
#define DarkSlateGrey		0.184314, 0.309804, 0.309804
#define DarkTurquoise		0.439216, 0.576471, 0.858824
#define DarkWood			0.520000, 0.370000, 0.260000
#define DkGreenCopper		0.290000, 0.460000, 0.430000
#define DustyRose			0.520000, 0.390000, 0.390000
#define Feldspar			0.820000, 0.570000, 0.460000
#define Firebrick			0.556863, 0.137255, 0.137255
#define Flesh				0.960000, 0.800000, 0.690000
#define ForestGreen			0.137255, 0.556863, 0.137255
#define Gold				0.800000, 0.498039, 0.196078
#define Goldenrod			0.858824, 0.858824, 0.439216
#define Green_Clr			0.000000, 1.000000, 0.000000
#define GreenCopper			0.320000, 0.490000, 0.460000
#define GreenishYellow		0.500000, 1.000000, 0.000000
#define GreenYellow			0.576471, 0.858824, 0.439216
#define HuntersGreen		0.130000, 0.370000, 0.310000
#define Indian				0.309804, 0.184314, 0.184314
#define Khaki				0.623529, 0.623529, 0.372549
#define LightBlue			0.749029, 0.847059, 0.847059
#define LightGreen			0.500000, 1.000000, 0.500000
#define LightPurple			0.870000, 0.580000, 0.980000
#define LightSteelBlue		0.560784, 0.560784, 0.737255
#define LightWood			0.910000, 0.760000, 0.650000
#define LimeGreen			0.196078, 0.800000, 0.196078
#define MandarinOrange		0.890000, 0.470000, 0.200000
#define Maroon				0.556863, 0.137255, 0.419608
#define MediumPurple		0.730000, 0.160000, 0.960000
#define MediumAquamarine	0.196078, 0.800000, 0.600000
#define MediumBlue			0.196078, 0.196078, 0.800000
#define MediumForestGreen	0.419608, 0.556863, 0.137255
#define MediumGoldenrod		0.917647, 0.917647, 0.678431
#define MediumOrchid		0.576471, 0.439216, 0.858824
#define MediumSeaGreen		0.258824, 0.435294, 0.258824
#define MediumSlateBlue		0.498039, 0.000000, 1.000000
#define MediumTurquoise		0.439216, 0.858824, 0.858824
#define MediumViolet		0.858824, 0.439216, 0.576471
#define MediumWood			0.650000, 0.500000, 0.390000
#define MidnightBlue		0.184314, 0.184314, 0.309804
#define NavyBlue			0.137255, 0.137255, 0.556863
#define NeonBlue			0.300000, 0.300000, 1.000000
#define NeonPink			1.000000, 0.430000, 0.780000
#define NewMidnightBlue		0.000000, 0.000000, 0.610000
#define NewTan				0.920000, 0.780000, 0.620000
#define OldGold				0.810000, 0.710000, 0.230000
#define Orange				1.000000, 0.500000, 0.000000
#define Orchid				0.858824, 0.439216, 0.858824
#define PaleGreen			0.560784, 0.737255, 0.560784
#define Pink				0.737255, 0.560784, 0.560784
#define Plum				0.917647, 0.678431, 0.917647
#define Purple				1.000000, 0.000000, 1.000000
#define Quartz				0.850000, 0.850000, 0.950000
#define Red_Clr				1.000000, 0.000000, 0.000000
#define RichBlue			0.350000, 0.350000, 0.670000
#define Salmon				0.435294, 0.258824, 0.258824
#define Scarlet				0.550000, 0.090000, 0.090000
#define SeaGreen			0.137255, 0.556863, 0.419608
#define SemiSweetChoc		0.420000, 0.260000, 0.150000
#define Sienna				0.556863, 0.419608, 0.137255
#define Silver				0.900000, 0.910000, 0.980000
#define SkyBlue				0.196078, 0.600000, 0.800000
#define SpicyPink			1.000000, 0.110000, 0.680000
#define SteelBlue			0.137255, 0.419608, 0.556863
#define SummerSky			0.220000, 0.690000, 0.870000
#define Tan					0.858824, 0.576471, 0.439216
#define Thistle				0.847059, 0.749020, 0.847059
#define Turquoise			0.678431, 0.917647, 0.917647
#define VeryDarkBrown		0.350000, 0.160000, 0.140000
#define VeryLightPurple		0.940000, 0.810000, 0.990000
#define Violet				0.800000, 0.196078, 0.600000
#define Wheat				0.847059, 0.847059, 0.749020
#define White				1.000000, 1.000000, 1.000000
#define Yellow				1.000000, 1.000000, 0.000000
#define YellowGreen			0.600000, 0.800000, 0.196078

#endif


#ifndef GRAPHIC_H
#define GRAPHIC_H

class Graphic
{
public:
	Graphic();

	void			setColor(const double, const double, const double);
	void			setAlpha(const double);

	const double&	getRed() const;
	const double&	getGreen() const;
	const double&	getBlue() const;
	const double&	getAlpha() const;

	virtual void	Display() = 0;

protected:
	double			rColor;
	double			gColor;
	double			bColor;
	double			aColor;
};

#endif


#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

class Transformable
{
public:
	explicit		Transformable();

	void			setSize(const double&, const double&);
	void			setPosition(const double&, const double&);
	void			setRelativePosition(const Transformable&, const double&, const double&);

	Transformable&	get();
	const double&	getX() const;
	const double&	getY() const;
	const double&	getWidth() const;
	const double&	getHeight() const;
	const double	getRelativeX(const Transformable&) const;
	const double	getRelativeY(const Transformable&) const;
	const double	getDistance(const Transformable&, const char& = ' ');

	void			translate(const char&, const double&);

protected:
	double			xPosition, yPosition;
	double			width, height;
};

#endif


#ifndef TEXTURE_H
#define TEXTURE_H

class Texture : public Graphic, public Transformable
{
public:
	~Texture();

	virtual void	Display();
	bool			loadFromFile(const string&);


private:
	int				loadPNG(const string&, GLuint&);
	int				loadTGA(const string&, GLuint&);
	bool			checkSize(int&);

	char*			GetData(FILE&, int&, int&);
	unsigned char*	GetRGBA(FILE&, int&);
	unsigned char*	GetRGB(FILE&, int&);
	unsigned char*	GetGray(FILE&, int&);

	GLuint			TexID;
	GLenum			texFormat;
};

#endif


#ifndef TEXT_H
#define TEXT_H

/*
A class to provide bitmap text functionality in OpenGL. Will be used to print text in GLUT windows.
*/
class Text : public Transformable, public Graphic
{
public:
	Text();
	void	Display();

	void	setFont(void*);
	void	setLineWidth(int);

	void	operator << (char);
	void	operator << (const char*);
	void	operator << (string&);

private:
	void*	font;
	int		lineWidth;
};

#endif


#ifndef RESOURCEHOLDER_H
#define RSOURCEHOLDER_H

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void				load(Identifier id, const string& filename);

	Resource&			get(Identifier id);
	const Resource&		get(Identifier id) const;

	void				remove(Identifier id);
	void				clear();

private:
	void				insertResource(Identifier id, unique_ptr<Resource> resource);

	std::map<Identifier, unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

#endif


#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

class UIElement : public Transformable, public Graphic
{
protected:
	bool	active;
	string	id;

	void RoundBox(int x, int y, int w, int h);
public:
	UIElement()
		: id(""), active(false)
	{

	}

	bool isActive()
	{
		return active;
	}
	void select()
	{
		active = true;
	}
	void deselect()
	{
		active = false;
	}

	void setID(const string& _id);
	const string getID();
	bool isClicked(const int x, const int y);
};

#endif


#ifndef BUTTON_H
#define BUTTON_H

class Button : public UIElement
{
public:
	Button(string label = "");

	Button(string label, GLuint x, GLuint y, GLfloat width, GLfloat height,
		GLfloat red = 1.f, GLfloat green = 1.f, GLfloat blue = 1.f, GLfloat alpha = 1.f);

	Button(Texture *img, GLuint x, GLuint y, GLfloat width, GLfloat height,
		GLfloat red = 1.f, GLfloat green = 1.f, GLfloat blue = 1.f, GLfloat alpha = 1.f);

	void setLabel(const string& label);
	const string& getLabel();
	void removeLabel();
	bool hasLabel();

	void setImage(Texture* image);
	const Texture& getImage();
	void removeImage();
	bool hasImage();

	void Display();
private:
	string		label;
	Texture*	image;
};

#endif


#ifndef ACTIVITY_H
#define ACTIVITY_H

//--------------------------------------------------------------------------------------------------//
//		Activity.h																					//
//																									//
//			 Author: Muhammad Saifullah Khan														//
//		Description: Definition of the Activity class. This is an abstract class and and each of	//
//					 its derived classes will represent one screen or activity of the program.		//
//					 Dependencies: Texture, ResourceHolder, std::string.							//
//			   Date: Sunday, October 25, 2015.														//
//																									//
//--------------------------------------------------------------------------------------------------//



/*
An activity is a single, focused thing that the user can do. Almost all activities interact with the user,
so the Activity class takes care of displaying a GLUT window whose GUI is defined in its Display() method.
Activity is an abstract class and each of its derived classes must override the Display() method.

There are two other methods almost all subclasses of Activity will override:

1) KeyboardEvents(unsigned char&, int&, int&) :: This method processes events generated by keyboard input.
It can be overriden to define how a particular Activity responds to keyboard input.

2) MouseEvents(int&, int&, int&, int&) :: This method processes events generated by mouse input. It can be
overriden to define how a particular Activity responds to keyboard input.

Activity class has a data member 'graphics', a container object for holding Textures (images). Textures can
be loaded into it using its load() method and later retrieved by the get() method. Generally, textures will
be loaded in the constructor of the subclass and accessed while drawing in the Display() method.
*/
class Activity
{
public:
	//--------------------------------------------------------------------------------------------------//
	//							PUBLIC INTERFACE OF THE ACTIVITY CLASS									//
	//--------------------------------------------------------------------------------------------------//

	/*
	Pure virtual method, must be overriden. Defines screen layout of the Activity.
	*/
	virtual void	Display() = 0;


	/*
	Virtual method, can be overriden if the Activity uses keyboard input. Handles input from character keys
	of the keyboard. Events generated on key press are handled here.
	*/
	virtual void	KeyboardEvents(unsigned char&, int&, int&);


	/*
	Virtual method, can be overriden if the Activity uses keyboard input. Handles input from character keys
	of the keyboard. Events generated on key release are handled here.
	*/
	virtual void	KeyboardUpEvents(unsigned char&, int&, int&);


	/*
	Virtual method, can be overriden if the Activity uses keyboard input. Handles input from special keys of
	the keyboard (i.e. the arrow keys, Home, Tab, Shift, Ctrl, Delete, etc). Events generated on key press
	are handled here.
	*/
	virtual void	KeyboardSpecialEvents(int&, int&, int&);


	/*
	Virtual method, can be overriden if the Activity uses keyboard input. Handles input from special keys of
	the keyboard (i.e. the arrow keys, Home, Tab, Shift, Ctrl, Delete, etc). Events generated on key release
	are handled here.
	*/
	virtual void	KeyboardSpecialUpEvents(int&, int&, int&);


	/*
	Virtual method, can be overriden if the Activity uses mouse input. Handles input from mouse clicks.
	*/
	virtual void	MouseEvents(int&, int&, int&, int&);


	/*
	Virtual method, can be overriden if the Activity uses mouse input. Handles events generated when mouse
	enters or exits a particular location on screen.
	*/
	virtual void	PassiveMotionEvents(int& x, int& y);


	/*
	Virtual method, can be overriden if the Activity uses mouse input. Handles events generated when mouse
	enters or exits a particular location on screen while clicking the mouse button.
	*/
	virtual void	ActiveMotionEvents(int&, int&);


	/*
	Virtual method, can be overriden if the Activity needs to perform background operations. This function
	is auto-called repeatedly, with a specified delay in between each call.
	*/
	virtual	void	TimerGL(int&);


	/*
	Virtual method, can be overriden if the Activity needs to perform background operations. This function
	is auto-called repeatedly, with a new call starting as soon as last call finishes.
	*/
	virtual void	IdleGL();


	/*
	Virtual method, can be overriden if the Activity needs to perform background operations. This function
	is called when an activity is marked as active.
	*/
	virtual void	onStart();


	/*
	Virtual method, can be overriden if the Activity needs to perform background operations. This function
	is called when active activity is changed from this one to some other activity.
	*/
	virtual void	onStop();


	/*
	Virtual method, can be overriden. Should be re-implemented in the child classes if mouse to handle mouse
	clicks on Buttons.
	*/
	virtual void	onClick(UIElement&);


	/*
	Virtual method, can be overriden. Should be re-implemented in the child classes to specify behavior of
	application when mouse pointer hovers above a Button.
	*/
	virtual void	onHover(UIElement&);

	// Virtual destructor
	virtual			~Activity();

	map<string, unique_ptr<Button>>& Buttons(){ return buttons; }
protected:
	//--------------------------------------------------------------------------------------------------//
	//						     PROTECTED METHODS OF THE ACTIVITY CLASS								//
	//--------------------------------------------------------------------------------------------------//
	void			addButton(const string& id, Button& button);

	void			showButtons();

	Button&			getButton(string id);

	void			deleteButtons();

	void			deleteButton(string id)
	{
		buttons.erase(id);
	}
	//--------------------------------------------------------------------------------------------------//
	//						  PROTECTED DATA MEMBERS OF THE ACTIVITY CLASS								//
	//--------------------------------------------------------------------------------------------------//

	/*
	Container object to hold Textures (images). Use load() method to add, get() method to access, and
	remove() method to destroy a Texture object. Each object is distinguished with a unique ID of the
	type std::string and must be referenced through this ID.
	*/
	ResourceHolder<Texture, string>		textures;

private:
	//--------------------------------------------------------------------------------------------------//
	//							PRIVATE DATA MEMBERS OF THE ACTIVITY CLASS								//
	//--------------------------------------------------------------------------------------------------//

	/*
	Container object to hold Buttons. Use addButton() method to add new Buttons, getButton() to access a
	Button, showButtons() to display all Buttons, and deleteButtons() to remove all Buttons.
	*/
	map<string, unique_ptr<Button>>		buttons;
};


#endif


#ifndef WINDOW_H
#define WINDOW_H

class Window
{
private:
	int id;
	int width, height;
	std::string name;
public:
	Window(int wd, int ht, std::string title)
		: width(wd), height(ht), name(title), id(0)
	{

	}

	/*
	Creates the GLUT window and gives it an initial state
	*/
	int Create()
	{
		// Set GLUT window mode
		glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

		// Set GLUT window Size
		glutInitWindowSize(width, height);

		// Position GLUT window in middle of the screen
		int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
		int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);
		glutInitWindowPosition((iScreenWidth - width) / 2, (iScreenHeight - height) / 2);

		// Create the GLUT window
		id = glutCreateWindow(name.c_str());

		// Setup initial GL State
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glClearDepth(1.0f);
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, 0.0, height, -1.0, 5.0);
		glViewport(0, 0, width, height);

		return  id;
	}

	int Width(){ return width; }

	int Height(){ return height; }

	int ID(){ return id; }

	std::string Name(){ return name; }
};

#endif


#ifndef SMARTGL_H
#define SMARTGL_H

class SmartGL
{
private:
	Window*		GLUT_Window;
public:
	SmartGL()
		: fps(33)
	{
	}
	SmartGL(int, int, std::string);

	void		Initialize(int wd, int ht, std::string name)
	{
		width = wd;
		height = ht;

		GLUT_Window = new Window(wd, ht, name);
		id = GLUT_Window->Create();
		registerCallbacks();
	}

	void		addActivity(Activity* activity, std::string id);
	void		removeActivity(std::string id);
	void		setActive(std::string id);

	void		run();
	int			ID() { return GLUT_Window->ID(); }
	int			width, height, id;
private:
	static Activity* activeScene;
	std::map<std::string, Activity*>	allScenes;

	std::string	title;
	double		fps;

	void		registerCallbacks();

	static void	Display();
	static void	ReshapeGL(int, int);

	static void	KeyboardEvents(unsigned char, int, int);
	static void	KeyboardUpEvents(unsigned char, int, int);
	static void	KeyboardSpecialEvents(int, int, int);
	static void	KeyboardSpecialUpEvents(int, int, int);

	static void	MouseEvents(int, int, int, int);
	static void	PassiveMotionEvents(int, int);
	static void	ActiveMotionEvents(int, int);

	static void	TimerGL(int);
	static void	IdleGL();
};
#endif


#ifndef GLOBAL_DATA
#define GLOBAL_DATA

extern SmartGL App;
extern Text gout;

#endif