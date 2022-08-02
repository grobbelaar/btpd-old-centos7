//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_NANOTIME_HPP
#define FAS_XTIME_NANOTIME_HPP

#include <fas/system/system.hpp>
#include <fas/xtime/nanospan.hpp>
#include <time.h>

namespace fas {

inline nanospan nanotime()
{

#if defined(HAVE_CLOCK_GETTIME_FUNC)
  timespec ts;
  if ( -1 == clock_gettime(CLOCK_MONOTONIC, &ts) )
    return nanospan();
  return nanospan(ts.tv_sec, ts.tv_nsec);
#elif defined(HAVE_GETTIMEOFDAY_FUNC)
  timeval tv;
  ::gettimeofday(&tv, 0);
  return nanospan(tv.tv_sec, tv.tv_usec*1000L);
#elif defined(HAVE__FTIME_S_FUNC)
  struct _timeb timebuffer;
  _ftime_s( &timebuffer );
  return millispan(static_cast<xsec_t>(timebuffer.time), static_cast<xsec_t>(timebuffer.millitm) );
#elif defined(HAVE__FTIME_FUNC)
  struct _timeb timebuffer;
  _ftime( &timebuffer );
  return millispan(static_cast<xsec_t>(timebuffer.time), static_cast<xsec_t>(timebuffer.millitm) );
#elif defined(HAVE_FTIME_FUNC)
	struct timeb timebuffer;
	ftime( &timebuffer );
	return millispan(static_cast<xsec_t>(timebuffer.time), static_cast<xsec_t>(timebuffer.millitm) );
#else
#error FAIL
  return nanospan(0, 0);
#endif //HAVE_CLOCK_GETTIME_FUNC
}

}

#endif
