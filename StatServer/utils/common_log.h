
#ifndef _UTILS_COMMON_LOG_H
#define _UTILS_COMMON_LOG_H

#include "servant/Application.h"
#include "servant/TarsLogger.h"

#define TROLLLOG 		(LOG->debug()<< "[dbg][" << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << "]")
#define ERRLOG (LOG->debug()<< "[err][" << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << "]")
#define CACHELOG (LOG->debug()<< "[cache][" << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << "]")
#define TIMELOG (LOG->debug()<< "[tm][" << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << "]")
#define RDEBUGLOG (LOG->debug()<< "[rd][" << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << "]")
#define INFOLOG (LOG->debug()<< "[inf][" << __FILE__ << "(" << __LINE__ << "):" << __FUNCTION__ << "]")

#endif
