#ifndef _TESTER_UTIL_
#define _TESTER_UTIL_
#include <cassert>
#include <iostream>
#include <iomanip>

namespace UnitTests
{
    using std::cerr;
    using std::cout;
    using std::endl;
    using std::setw;

    static uint64_t numAssertions;

    #define CERR cout << "[ " << __FILE__ << ", " << setw(3) << std::right << __LINE__ << " ] "
    #define FATAL_ERROR(t) cout << endl; CERR << "FATAL ERROR : " << t << endl
    #define ASSERT_EQ(predicate)    \
    if (predicate)                  \
    {                               \
         numAssertions++;           \
    }                               \
    else                            \
    {                               \
         cout<< endl << "expecting true but got false" ; \
         assert(predicate);         \
    }

    #define ASSERT_APPROX(lhs,rhs)  \
    {                               \
    double diff = lhs - rhs;        \
    if (diff < 0) diff *= -1;       \
    if (diff < .001)                \
    {                               \
         numAssertions++;           \
    }                               \
    else                            \
    {                               \
         cout<< endl << "expecting approx "    \
        <<  rhs << " but got " << lhs << endl; \
         assert((lhs) == (rhs));    \
    }                               \
    }                               \

    #define ASSERT(lhs,rhs)         \
    if ((lhs) == (rhs))             \
    {                               \
         numAssertions++;           \
    }                               \
    else                            \
    {                               \
         cout<< endl << "expecting " << rhs << " but got " << lhs << endl; \
         assert((lhs) == (rhs));    \
    }

    #define ASSERT_LT(lhs,rhs)      \
    if ((lhs) < (rhs))              \
    {                               \
         numAssertions++;           \
    }                               \
    else                            \
    {                               \
         cout<< endl << "expecting " << rhs << " <  " << lhs << endl; \
         assert((lhs) < (rhs));    \
    }

    #define ASSERT_GT(lhs,rhs)             \
    if ((lhs) > (rhs))             \
    {                               \
         numAssertions++;\
    }                               \
    else                            \
    {                               \
         cout<< endl << "expecting " << rhs << " < " << lhs << endl; \
         assert((lhs) > (rhs));    \
    }
}
#endif
