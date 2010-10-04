
Building the C++ Simple Samples:

Reference readme.txt files within each platform directory for the C++ client 
information regarding the compiler versions used/supported.

Please Note: Server references are contained in a separate file mqservers.h.
These values may need to be edited from the default values depending on 
where the servers are installed/configured before compiling the samples.

Windows Environment:

   Execute "nmake -f makefile.win32"

Linux Environment:

   Execute the dos2unix command: dos2unix *
   Execute "make -f makefile.unix"

***Please Note: If you are using RHEL AS 4.0, you need to update the 
makefile.unix to use RHEL AS 4.0 gnu 3.4.5.

Comment out the following line in the makefile.unix file:

   LIBDIRS=-L../../clients/cpp/linux/gnu.3_2_3/release  #  RHEL AS 3.0 gnu 3.2.3 support 

Uncomment the following line in the makefile.unix file:

   LIBDIRS=-L../../clients/cpp/linux/gnu.3_4_5/release  #  RHEL AS 4.0 gnu 3.4.5 support 

The following samples will generate a gif file of the map image in addition to
screen output:

mapIt
mapWithPOI
mapItWithPrimitives
SearchAndDisplayIt
routeItWithServerSession
routeItNoServerSession

GeocodeIt and SearchIt will generate output to the screen only.

