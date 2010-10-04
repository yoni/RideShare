# output directories
OBJECTS=$(PWD)/objects
RELEASE=$(PWD)/release
I_RELEASE=$(RELEASE)/include
L_RELEASE=$(RELEASE)/lib

# handle libraries here 
N_LIBS = $(RLIBS:lib%=-l%)

# add directories to files
OFILES := $(OTARGET:%=$(OBJECTS)/%)
UFILES := $(OUNITTEST:%=$(OBJECTS)/%)
TARGET := $(TARGET:%=$(RELEASE)/%)
UTARGET := $(UTARGET:%=$(RELEASE)/%)

L_OFILES := $(L_OTARGET:%=$(OBJECTS)/%)
L_TARGET:= $(L_TARGET:%=$(L_RELEASE)/%)


# define compile and linking options
#TODO: make bottom RLIBS a foreach
INCLUDESDIR+=-I/usr/local/include $(if $(RLIBS), -I$(PWD)/../$(RLIBS)/release/include)
INCLUDESDIR+=-I/usr/include/mysql

LIBSDIR+=-L/usr/local/lib $(if $(RLIBS), -L$(PWD)/../$(RLIBS)/release/lib) -L/usr/lib

CC=/usr/bin/g++ 
CFLAGS= -DMQUNIX -g -c -Wall -DMYSQLPP_MYSQL_HEADERS_BURIED $(INCLUDESDIR) -I$(I_RELEASE)
LIBS += -lboost_date_time -lmysqlpp $(N_LIBS)
# mq libs
LIBS+=-lnsl -lpthread -mt -Xlinker -Bstatic -lmqexec -lmqif -lmqosutil -lxml2 -Xlinker -Bdynamic
LDFLAGS=-w -L$(L_RELEASE) $(LIBSDIR)
LD=/usr/bin/g++
AR=/usr/bin/ar
LINK=$(LD)

# copy include files to release
IFILES := $(I_TARGET:%=$(I_RELEASE)/%)

.PHONY: all
ifdef RLIBS
all: prep_work prep_libs $(L_TARGET) $(TARGET) $(UTARGET)
else
all: prep_work $(IFILES) $(L_TARGET) $(TARGET) $(UTARGET)
endif

.PHONY: clean
clean: 
	-rm $(OBJECTS)/*.o

.PHONY: nuke
nuke:
ifdef RLIBS
	cd $(PWD)/../$(RLIBS) && make nuke
	-rm -rf $(OBJECTS) $(RELEASE) 
else
	-rm -rf $(OBJECTS) $(RELEASE) 
endif



# make controller library and copy headers to release
$(L_TARGET): $(L_OFILES) 
	$(AR) rvs $@ $(L_OFILES)

# make executable
$(TARGET): $(OFILES)
	$(LINK) $(LDFLAGS) $(OFILES) -o $@ $(LIBS)

# make unit test executable
$(UTARGET): $(UFILES) $(L_TARGET)
	$(LINK) $(LDFLAGS) $(UFILES) -o $@ $(LIBS)

# make object files
$(OBJECTS)/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(L_DEPFILES): 

# copy hpp files to release 
$(I_RELEASE)/%.hpp: %.hpp 
	cp $< $@

# this needs to be changed to support multiple libs
prep_libs:
	cd $(PWD)/../$(RLIBS) && make

# create directories 
prep_work:
ifdef L_TARGET
	for dir in $(OBJECTS) $(RELEASE) $(I_RELEASE) $(L_RELEASE); do \
		if [ ! -d $$dir ]; then \
			mkdir $$dir; \
		fi; \
	done
#	-mkdir $(OBJECTS) $(RELEASE) $(I_RELEASE) $(L_RELEASE)
else
	for dir in $(OBJECTS) $(RELEASE) ; do \
		if [ ! -d $$dir ]; then \
			mkdir $$dir; \
		fi; \
	done
#-mkdir $(OBJECTS) $(RELEASE)
endif

