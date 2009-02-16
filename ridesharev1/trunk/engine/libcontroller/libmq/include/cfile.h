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
#ifndef _CMQFILE_H_
// {secret}
#define _CMQFILE_H_

#include "mq_os.h"
#include "cio.h"
#include "ioformat.h"

////////////////////////////////////////////////////////////////////////////////
// CMQFile

class CMQFile : public CMQIO
{
public:
   CMQFile();
   virtual ~CMQFile();

   virtual int open(const char* filename, int oflag, int pmode=-1);
   virtual off_t lseek(off_t offset, int whence);
   virtual void close();
   void setFormatter(CMQIOFormatter& aIOFormatter);

protected:
   virtual int llread(void* buf, size_t len);
   virtual int llwrite(const void* buf, size_t len);

private:
   int IsOpen();
   CMQFile(const CMQFile&);
   int   fd;
};

#endif   // _CMQFILE_H_

