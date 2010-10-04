
PWD=.
TARGET=main
UTARGET=
OUNITTEST=
OTARGET=main.o util.o


CC=/usr/bin/g++ 
CFLAGS= -c -Wall -DMYSQLPP_MYSQL_HEADERS_BURIED
LIBS=-lmysqlpp
LDFLAGS=-O -w 
LD=/usr/bin/g++
LINK=$(LD)

OBJECTS=$(PWD)/objects
RELEASE=$(PWD)/release

OFILES := $(OTARGET:%=$(OBJECTS)/%)
UFILES := $(OUNITTEST:%=$(OBJECTS)/%)

all: $(TARGET) $(UTARGET)

# make executable
$(TARGET): $(OFILES) 
	$(LINK) $(LDFLAGS) $(OFILES) -o $(RELEASE)/$@ $(LIBS)

# make unit test executable
$(UTARGET): $(UFILES) 
	$(LINK) $(LDFLAGS) $(UFILES) -o $(RELEASE)/$@ $(LIBS)

# make object files
$(OBJECTS)/%.o: %.cpp prep_work
	$(CC) $(CFLAGS) $< -o $@

# create directories 
prep_work:
	-mkdir $(OBJECTS) $(RELEASE)

nuke: 
	-rm -rf $(OBJECTS) $(RELEASE)

clean: 
	-rm $(OBJECTS)/*.o


