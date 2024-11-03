#ifdef __MINGW32__

#ifdef VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#endif // VC_EXTRALEAN

#include <windows.h>
#include <tchar.h>

#define strcpy_s( dest, src ) (strcpy(dest, src))

#include "CWinThread.h"

#endif
