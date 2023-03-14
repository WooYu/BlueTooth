#ifndef AUTEL_C478E46E_6240_4479_BDA6_381ACFBB050E__CROSSPLATDEF__INCLUDED_
#define AUTEL_C478E46E_6240_4479_BDA6_381ACFBB050E__CROSSPLATDEF__INCLUDED_

#ifndef _WIN32
//#include "public.h"
#define sprintf_s snprintf
#define _stricmp   strcasecmp
#define _strnicmp  strncasecmp
typedef __int64_t  __int64;


#else
#define LOGI
#define usleep(x) Sleep(x/1000)
#define pthread_self() GetCurrentThreadId()
#define  snprintf     sprintf_s
#define  strcasecmp   _stricmp
#define  strncasecmp  _strnicmp  
#endif

#endif // !defined(AUTEL_C478E46E_6240_4479_BDA6_381ACFBB050E__CROSSPLAT__INCLUDED_)
