TARGET=fp
UNAME	:=	$(shell uname -s)

ifneq (,$(findstring MINGW,$(UNAME)))
	PLATFORM	:= win32
	EXEEXT		:= .exe
	CFLAGS		+= -mno-cygwin
	LDFLAGS		+= -mno-cygwin -s
	OS	:=	win32
endif

ifneq (,$(findstring CYGWIN,$(UNAME)))
	LDFLAGS		+= -s
	CFLAGS	+= -DWIN32
	EXEEXT		:= .exe
	OS	:=	win32
endif

all: crc.l crc.y
	yacc -d crc.y
	flex crc.l
	gcc lex.yy.c y.tab.c -o $(TARGET)$(EXEEXT)
	
clean:
	@echo clean ...
	@rm -fr $(TARGET)$(EXEEXT)
	
install: all
	@echo Installing $(TARGET)$(EXEEXT)
	@[ -d $(PS3DEV)/bin ] || mkdir -p $(PS3DEV)/bin
	@install -m 755  $(TARGET)$(EXEEXT) $(PS3DEV)/bin
