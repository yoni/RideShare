
PWD=.
RLIBS=libcontroller
TARGET=controller
OTARGET=main.o
VISUALIZERTB=visualizer.tar.gz
VISUALIZERREL=visualizer
VISUALIZER_DEP=style.css images/ visualizer.html image_pool/ solution_control.js
VISUALIZER_DEP+=solution_data.js

include $(PWD)/../Makefiles/std.mk

all: copy_visualizer
copy_visualizer: $(VISUALIZERTB)
	-mv $(VISUALIZERTB) $(RELEASE)

$(VISUALIZERTB):
	-mkdir -p $(RELEASE)/$(VISUALIZERREL)
	-cp -rf $(VISUALIZER_DEP) $(RELEASE)/$(VISUALIZERREL)
	-tar czf $(VISUALIZERREL).tar.gz $(RELEASE)/$(VISUALIZERREL)

