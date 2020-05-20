#if defined(__WIN32__) || defined(_WIN32) || defined(__WIN64) || defined(__WIN64__) || defined(WIN32) || defined(WIN64)
#define SF_PLATFORM_WIN
#elif defined(linux) || defined(__linux__) || defined(__LINUX) || defined(__LINUX__)
#define SF_PLATFORM_LINUX
#endif

#ifdef SF_PLATFORM_WIN
#include <winsock2.h>
#include <windows.h>
#include <winerror.h>
#include <ws2tcpip.h>
#include <process.h>
#include <crtdbg.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#endif

#ifdef SF_PLATFORM_WIN
int gettimeofday(struct timeval* tp, void* tzp);
typedef DWORD		TID;
#define sf_snprintf	sprintf_s
#define sf_stricmp	stricmp
#define sf_sleep(s)	Sleep(s) //millisecond
#define sf_getpid()	_getpid()
#define sf_sscanf	sscanf_s
#define	tvsnprintf	_vsnprintf
#define	tsnprintf	_snprintf
#else
typedef pthread_t	TID;
#define sf_snprintf	snprintf
#define sf_stricmp	strcasecmp
#define sf_sleep(s)	usleep(s*1000) //millisecond
#define sf_getpid()	getpid()
#define	tvsnprintf	vsnprintf
#define	tsnprintf	snprintf
#define sf_sscanf	sscanf
void	SetResource();
#endif

void LocalTime(const time_t* timep, struct tm* result);
