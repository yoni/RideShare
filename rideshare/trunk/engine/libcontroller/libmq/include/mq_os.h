/*****************************************************************************
*  Copyright (C) 1992-2002 MapQuest.com/America Online/Time Warner, Inc.
*  All Rights Reserved.
*-----------------------------------------------------------------------------
*  This software is the confidential and proprietary information of
*  MapQuest.com and America Online ("Confidential Information"). You shall
*  not disclose such Confidential Information and shall use it only in
*  accordance with the terms of the license agreement you entered into with
*  MapQuest.com.
*-----------------------------------------------------------------------------
*  MAPQUEST.COM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
*  OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
*  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
*  PURPOSE, OR NON-INFRINGEMENT.  MAPQUEST.COM SHALL NOT BE LIABLE FOR ANY
*  DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
*  DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
*-----------------------------------------------------------------------------
*****************************************************************************/
#ifndef MQ_OS_H
// {secret}
#define MQ_OS_H

#ifdef _MSC_VER
#define MAXHOSTNAMELEN  256
#endif

#include<stdio.h>
#include<signal.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<ctype.h>

#ifndef _MSC_VER
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/param.h>
#include<sys/time.h>
#include<sys/uio.h>
#include<stdarg.h>
#else
#include <io.h>
#include <process.h>

#ifdef MQUNIX
#include <sys/timeb.h>
#endif

#include <stdarg.h>
#include <winsock2.h>

#define strcasecmp   stricmp
#define strncasecmp  strnicmp


#endif

#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#ifdef MQWIN32
#pragma warning( disable : 4018 )
#endif

#include <fstream>

#ifndef STD
#define STD std
#endif


#endif

