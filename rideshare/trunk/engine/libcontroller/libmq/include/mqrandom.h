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
#ifndef _MQENCRYPTION_H_
// {secret}
#define _MQENCRYPTION_H_


/*
 * This class will generate random numbers used in encryption
 * @ingroup Mapquest
 */
class CMQRandom
{
 public:
  /**
   * Constructor
   * @param seed  Generator starting number.  Normally the current time
   */
  CMQRandom(unsigned int seed = GOOD_SEED);

  /**
   * Destructor
   */
  virtual ~CMQRandom() { delete [] _state; }

  /**
   * Generate a random number
   *
   * @return  A random number in the range 0 to 2^32 - 1
   */
  unsigned int rand();

  /**
   * Generate a random number
   *
   * @param n  Range, from 0, of the generated random number.  For instance,
   *           if n = 5, then random numbers are generated in the range
   *           of [0, 5)
   *
   * @return  The next random number as an integer in the range [0, n)
   */
  unsigned int rand(unsigned int n) { return(rand() % n); }

  /**
   * Seed the random number generator.  This should only be called ONCE
   *
   * @param seed  Generator starting number.  Normally the current time
   */
  void srand(unsigned int seed);

private:
  /**
   * Reload the random number generator.  Called after the cached random
   * numbers are exhausted
   *
   * @return  A random number in the range 0 to 2^32 - 1
   */
  unsigned int reload();

  /**
   * The number of random numbers to cache
   */
  static const unsigned int N;

  /**
   * The period used by the RNG
   */
  static const unsigned int M;

  /**
   * A magic number used by the RNG algorithm
   */
  static const unsigned int MAGIC_NUMBER;

  /**
   * The random number generator's potency
   */
  static const unsigned int POTENCY;

  /**
   * Mask used in random number generation
   */
  static const unsigned int TEMPERING_MASK_B;

  /**
   * Mask used in random number generation
   */
  static const unsigned int TEMPERING_MASK_C;

  /**
   * Seed used on a reload of the cache -- good, initial seed
   */
  static const unsigned int GOOD_SEED;

  /**
   * State vector that holds the random numbers
   */
  unsigned int *_state;

  /**
   * The next random number
   */
  unsigned int *_next;

  /**
   * The number of random numbers remaining in the cache
   */
  int _left;
};

inline void shuffle(const char* cfirst,int len, CMQRandom& myRand)
{
   char *first = (char*)cfirst;

   if (len == 0)
   {
      return;
   }

   for ( char* i = first+1; i < (first+len); ++i)
   {
      char tmp = *(i);
      char *tmpptr = first + myRand.rand((i - first) + 1);
      *(i) = *(tmpptr);
      *(tmpptr) = tmp;
      //std::iter_swap(i, first + myRand.rand((i - first) + 1));
   }
}

/*
template <class Iterator>
void shuffle(Iterator first, Iterator last, CMQRandom& myRand)
{
   if (first == last)
   {
      return;
   }

   for (Iterator i = first + 1; i != last; ++i)
   {
      std::iter_swap(i, first + myRand.rand((i - first) + 1));
   }
}
*/

#endif // _MQENCRYPTION_H_
