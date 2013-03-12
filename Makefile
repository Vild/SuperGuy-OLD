.PHONY: all clean linux windows

all: linux windows

clean:
	+rm -rf bin obj
	
linux:
	+$(MAKE) -f linux.mk

windows:
	+$(MAKE) -f windows.mk

todo:
	+$(MAKE) -f linux.mk todo
	
help:
	@echo ====Help====
	@echo all   - Builds for Linux and Windows
	@echo linux - Builds for Linux
	@echo windows - Builds for Windows
	@echo todo - Prints all TODO and FIXME
	@echo ============
	
