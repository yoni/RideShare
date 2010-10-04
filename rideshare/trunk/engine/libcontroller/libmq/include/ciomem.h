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
#ifndef _CMQIOMEM_H_
// {secret}
#define _CMQIOMEM_H_

#include "cio.h"

/**
 * MQIO class that writes to a memory buffer
 * @ingroup Mapquest
 */
class CMQIOMem : public CMQIO
{
public:
   /**
    * Constructor
    * @param maxSize  Max size this IOMem can grow to
    */
   CMQIOMem(size_t maxSize = MAX_ALLOC_SIZE);

   /**
    * Destructor
    */
   virtual ~CMQIOMem();

   /**
    * Attach IO formatter class
    * @param aIOFormatter io formatter to attach
    */
   void setFormatter(CMQIOFormatter& aIOFormatter);

   /**
    * Close and delete IO buffers
    */
   virtual void close();

   /**
    * Seek IO to a position
    * @param offset  amount to offset position from whence
    * @param whence  position to seek to
    * @return the new position in buffer
    */
   virtual off_t lseek(off_t offset, int whence);

   /**
    * Report the position of the IO pointer
    * @return current position in buffer
    */
   virtual off_t tell();

   /**
    * Pre-create buffer
    * @param maxSize  Max size this IOMem can grow to
    */
   int    create(size_t maxSize = MAX_ALLOC_SIZE);

   /**
    * Report the current used size of the IO buffer
    * @return used buffer size
    */
   size_t size();

   /**
    * Clear IO buffers for re-use
    */
   void   clear();

   /**
    * Access buffer.  Read only!
    */
   operator const char*() const; // cast operator

   /**
    * Hexdump of current contents
    */
   void dump() const;

   /**
    * Hexdump any data block
    * @param data pointer to data block to dump
    * @param len  length of data to dump
    */
   static void dump(void* data, unsigned long len);

   /**
    * Hexdump any data block to a string
    * @param data pointer to data block to dump
    * @param len  length of data to dump
    * @param strDump  Buffer to append output to.
    */
   static void dump(void* data, unsigned long len, CMQString& strDump);

protected:
   // {secret}
   virtual int llread(void* buf, size_t len);
   // {secret}
   virtual int llwrite(const void* buf, size_t len);

private:
   // {secret}
   static const size_t MIN_ALLOC_SIZE;
   // {secret}
   static const size_t MAX_ALLOC_SIZE;

   // {secret}
   char*  buffer;
   // {secret}
   size_t bufSize;
   // {secret}
   size_t maxSize;
   // {secret}
   size_t pos;
   // {secret}
   size_t endPos;

   // {secret}
   size_t Grow(size_t len);
};

#endif   // _CMQIOMEM_H_

