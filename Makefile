# -----------------------------------------------------
# Makefile for dBase package ...
# (c) 2021 Jens Kallup - paule32 <kallup.jens@web.de>
# All rights reserved.
# -----------------------------------------------------
PROJECT = jittest
LANG    = DEU
VERSION = 1.0

EXE_EXT = .exe
DIR_SEP = /

TMP_DIR = .$(DIR_SEP)tmp$(DIR_SEP)
SRC_DIR = .$(DIR_SEP)src$(DIR_SEP)
LIB_DIR = .$(DIR_SEP)lib$(DIR_SEP)
LOC_DIR = .$(DIR_SEP)loc$(DIR_SEP)

LOC_DEU =  $(LOC_DIR)$(PROJECT)DEU
LOC_ENG =  $(LOC_DIR)$(PROJECT)ENG

# ---------------------------------------
# common source file for the application
# ---------------------------------------
src_files =                  \
	$(SRC_DIR)test.cc        \
	$(SRC_DIR)translator.cc

# ---------------------------------------
# source files for asmjit.dll:
# ---------------------------------------
asmjit_srcfiles = \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)archtraits.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)constpool.cpp        \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)errorhandler.cpp     \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)jitallocator.cpp     \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)rapass.cpp           \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)virtmem.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonevector.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)assembler.cpp        \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)cpuinfo.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)formatter.cpp        \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)jitruntime.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)rastack.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zone.cpp             \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)builder.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)emithelper.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)func.cpp             \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)logger.cpp           \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)string.cpp           \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonehash.cpp         \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)codeholder.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)emitter.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)funcargscontext.cpp  \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)operand.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)support.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonelist.cpp         \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)codewriter.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)emitterutils.cpp     \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)globals.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)osutils.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)target.cpp           \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonestack.cpp        \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)compiler.cpp         \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)environment.cpp      \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)inst.cpp             \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)ralocal.cpp          \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)type.cpp             \
	$(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonetree.cpp         \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86assembler.cpp      \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86compiler.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86features.cpp       \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86func.cpp           \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86instdb.cpp         \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86rapass.cpp         \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86builder.cpp        \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86emithelper.cpp     \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86formatter.cpp      \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86instapi.cpp        \
	$(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86operand.cpp

# ---------------------------------------
# xbase++ mingw64 source files:
# ---------------------------------------
xbase_srcfiles = \
	$(SRC_DIR)xbase64$(DIR_SEP)xbase64.cpp  \
	$(SRC_DIR)xbase64$(DIR_SEP)xbcdx.cpp    \
	$(SRC_DIR)xbase64$(DIR_SEP)xbdate.cpp   \
	$(SRC_DIR)xbase64$(DIR_SEP)xbdbf.cpp    \
	$(SRC_DIR)xbase64$(DIR_SEP)xbexp.cpp    \
	$(SRC_DIR)xbase64$(DIR_SEP)xbexpfnc.cpp \
	$(SRC_DIR)xbase64$(DIR_SEP)xbexpprc.cpp \
	$(SRC_DIR)xbase64$(DIR_SEP)xbfields.cpp \
	$(SRC_DIR)xbase64$(DIR_SEP)xbfile.cpp   \
	$(SRC_DIR)xbase64$(DIR_SEP)xbfilter.cpp \
	$(SRC_DIR)xbase64$(DIR_SEP)xbindex.cpp  \
	$(SRC_DIR)xbase64$(DIR_SEP)xblock.cpp   \
	$(SRC_DIR)xbase64$(DIR_SEP)xbmemo.cpp   \
	$(SRC_DIR)xbase64$(DIR_SEP)xbndx.cpp    \
	$(SRC_DIR)xbase64$(DIR_SEP)xbnode.cpp   \
	$(SRC_DIR)xbase64$(DIR_SEP)xbntx.cpp    \
	$(SRC_DIR)xbase64$(DIR_SEP)xbstring.cpp
# ---------------------------------------
# xbase++ dll mingw64 object files:
# ---------------------------------------
xbase_objfiles = \
	$(TMP_DIR)xbase64$(DIR_SEP)xbase64.o  \
	$(TMP_DIR)xbase64$(DIR_SEP)xbcdx.o    \
	$(TMP_DIR)xbase64$(DIR_SEP)xbdate.o   \
	$(TMP_DIR)xbase64$(DIR_SEP)xbdbf.o    \
	$(TMP_DIR)xbase64$(DIR_SEP)xbexp.o    \
	$(TMP_DIR)xbase64$(DIR_SEP)xbexpfnc.o \
	$(TMP_DIR)xbase64$(DIR_SEP)xbexpprc.o \
	$(TMP_DIR)xbase64$(DIR_SEP)xbfields.o \
	$(TMP_DIR)xbase64$(DIR_SEP)xbfile.o   \
	$(TMP_DIR)xbase64$(DIR_SEP)xbfilter.o \
	$(TMP_DIR)xbase64$(DIR_SEP)xbindex.o  \
	$(TMP_DIR)xbase64$(DIR_SEP)xblock.o   \
	$(TMP_DIR)xbase64$(DIR_SEP)xbmemo.o   \
	$(TMP_DIR)xbase64$(DIR_SEP)xbndx.o    \
	$(TMP_DIR)xbase64$(DIR_SEP)xbnode.o   \
	$(TMP_DIR)xbase64$(DIR_SEP)xbntx.o    \
	$(TMP_DIR)xbase64$(DIR_SEP)xbstring.o

# ---------------------------------------
# boost: program_options .dll objects:
# ---------------------------------------
boost_objpo_files = \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)cmdline.o             \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)config_file.o         \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)convert.o             \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)options_description.o \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)parsers.o             \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)positional_options.o  \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)split.o               \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)utf8_codecvt_facet.o  \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)value_semantic.o      \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)variables_map.o       \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)winmain.o             \
	$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)dummy.o
boost_srcpo_files = \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)cmdline.cpp             \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)config_file.cpp         \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)convert.cpp             \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)options_description.cpp \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)parsers.cpp             \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)positional_options.cpp  \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)split.cpp               \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)utf8_codecvt_facet.cpp  \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)value_semantic.cpp      \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)variables_map.cpp       \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)winmain.cpp             \
	$(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)dummy.cpp

# ---------------------------------------
# common object file for the application
# ---------------------------------------
obj_files =                  \
	$(TMP_DIR)test.o         \
	$(TMP_DIR)translator.o

# ---------------------------------------
# object files for asmjit.dll:
# ---------------------------------------
asmjit_objfiles =                \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)archtraits.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)constpool.o        \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)errorhandler.o     \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)jitallocator.o     \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)rapass.o           \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)virtmem.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonevector.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)assembler.o        \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)cpuinfo.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)formatter.o        \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)jitruntime.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)rastack.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zone.o             \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)builder.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)emithelper.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)func.o             \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)logger.o           \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)string.o           \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonehash.o         \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)codeholder.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)emitter.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)funcargscontext.o  \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)operand.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)support.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonelist.o         \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)codewriter.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)emitterutils.o     \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)globals.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)osutils.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)target.o           \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonestack.o        \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)compiler.o         \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)environment.o      \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)inst.o             \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)ralocal.o          \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)type.o             \
	$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)zonetree.o         \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86assembler.o      \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86compiler.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86features.o       \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86func.o           \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86instdb.o         \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86rapass.o         \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86builder.o        \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86emithelper.o     \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86formatter.o      \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86instapi.o        \
	$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)x86operand.o

# ---------------------------------------
# translation for the application locale
# ---------------------------------------
pot_files =           \
	$(LOC_DEU).po \
	$(LOC_ENG).po
pmo_files =           \
	$(LOC_DEU).mo \
	$(LOC_ENG).mo

COMPILE_PARTS =\
	$(src_files) $(obj_files) \
	$(pmo_files)

# ---------------------------------------------------
# optimized for using into the msys64 MinGW64 shell:
# ---------------------------------------------------
GCC_DIR = $(DIR_SEP)mingw64$(DIR_SEP)bin$(DIR_SEP)
GXX_DIR = $(DIR_SEP)mingw64$(DIR_SEP)bin$(DIR_SEP)

GCC_BIN = $(GCC_DIR)x86_64-w64-mingw32-gcc$(PRG_EXT)
GXX_BIN = $(GXX_DIR)x86_64-w64-mingw32-g++$(PRG_EXT)

# mingw64 stuff:
ECHO    = echo
RMDIR   = rm -rf
MKDIR   = mkdir -p
STRIP   = strip

# gnu linker directives:
LIB_PATH += \
	-L/E/Projekte/boost_1_77_0/stage/lib \
	-L.$(DIR_SEP)lib                     \
	-L $(DIR_SEP)mingw64$(DIR_SEP)lib    \
	-L $(DIR_SEP)mingw64$(DIR_SEP)x86_64-w64-mingw32$(DIR_SEP)lib

LIB_LINK +=  \
	-lkernel32 -luser32 -lwinmm \
	-lintl -lpthread

LIB_LINK_ASMJIT_DLL   = -lasmjit
LIB_LINK_BOOST_PO_DLL = -lboost.program_options
#
LIB_LINK_BOOST_PO_LIB = -lboost_program_options-mgw10-mt-s-x64-1_77
	
# gnu c compiler directives:
GCC_DEF = \
	-DLANG=$(LANG)                         \
	-D_GLIBCXX_USE_CXX11_ABI=0             \
	-fno-ident -fopenmp -m64 -fconcepts-ts \
	-fdata-sections -ffunction-sections    \
	-Wl,--gc-sections                      \
	-Wno-deprecated                        \
	-Wno-write-strings                     \
	-O3 -std=c++2a

INC_DIR = \
	-I.                                            \
	-I.$(DIR_SEP)inc                               \
	-I.$(DIR_SEP)inc$(DIR_SEP)asmjit               \
	-I$(DIR_SEP)E$(DIR_SEP)Projekte$(DIR_SEP)boost_1_77_0

JIT_DEF = \
	-DASMJIT_STATIC=1 $(INC_DIR) -shared -fPIC $(GCC_DEF)

GCC_OPTS = -fopenmp -MD $(LIB_PATH) $(LIB_LINK)
JIT_OPTS = \
	-DASMJIT_STATIC=1           \
	-shared -fPIC               \
	$(GCC_OPTS)

# ---------------------------
# Windows 10 based stuff ...
# ---------------------------
# all: asmjit_dll compile
# all: welcome asmjit_dll xbase_dll boost_podll compile
all: boost_static_archive
#compile

$(TMP_DIR)%.o: $(SRC_DIR)%.c
	$(ECHO) "compile c file: $^"
	$(GCC_BIN) $(INC_DIR) $(GCC_DEF) -o $@ -c $^

$(TMP_DIR)%.o: $(SRC_DIR)%.cc
	$(ECHO) "compile c++ file: $^"
	$(GXX_BIN) $(INC_DIR) $(GCC_DEF) -o $@ -c $^

$(TMP_DIR)xbase64$(DIR_SEP)%.o: $(SRC_DIR)xbase64$(DIR_SEP)%.cpp
	@$(ECHO) "compile xbase64 c++ file: $^"
	@$(GXX_BIN) $(INC_DIR) $(GCC_DEF) -shared -fPIC -o $@ -c $^

$(TMP_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)%.o: $(SRC_DIR)asmjit$(DIR_SEP)core$(DIR_SEP)%.cpp
	@$(ECHO) "compile asmjit core c++ file: $^"
	@$(GXX_BIN) $(INC_DIR) $(GCC_DEF) -shared -fPIC -o $@ -c $^

$(TMP_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)%.o: $(SRC_DIR)asmjit$(DIR_SEP)x86$(DIR_SEP)%.cpp
	@$(ECHO) "compile asmjit x86 c++ file: $^"
	@$(GXX_BIN) $(INC_DIR) $(GCC_DEF) -shared -fPIC -o $@ -c $^

$(TMP_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)%.o: $(SRC_DIR)boost$(DIR_SEP)program_options$(DIR_SEP)%.cpp
	@$(ECHO) "compile boost.program_options c++ file: $^"
	@$(GXX_BIN) $(INC_DIR) $(GCC_DEF) -shared -fPIC -o $@ -c $^

# ----------------------------------------------------------
# WARNING: translation file could be override !
# ----------------------------------------------------------
ifeq ($(shell test -e $(LOC_DEU).po && echo -n yes),yes)
$(LOC_DEU).po:
	$(ECHO) "locale for '$(LOC_DEU).po' exists."
	$(ECHO) "skip create it."
else
$(LOC_DEU).po: $(src_files)
	xgettext --language=C++ -d $(PROJECT)DEU \
			 --package-version=$(VERSION)    \
			 --output-dir=$(LOC_DIR)         \
			 -k_tr $^
endif
ifeq ($(shell test -e $(LOC_ENG).po && echo -n yes),yes)
$(LOC_ENG).po:
	$(ECHO) "locale for '$(LOC_ENG).po' exists."
	$(ECHO) "skip create it."
else
$(LOC_ENG).po: $(src_files)
	xgettext --language=C++ -d $(PROJECT)ENG \
			 --package-version=$(VERSION)    \
			 --output-dir=.$(LOC_DIR)        \
			 -k_tr $^
endif

# create the translation binary files:
$(LOC_DEU).mo: $(LOC_DEU).po ; msgfmt $^ -o $@
$(LOC_ENG).mo: $(LOC_ENG).po ; msgfmt $^ -o $@

# create asmjit.dll:
asmjit_dll: $(asmjit_srcfiles) $(asmjit_objfiles)
	$(GXX_BIN) $(JIT_DEF)  -o $(TMP_DIR)dllmain.o $(SRC_DIR)dllmain.cc
	$(GXX_BIN) $(JIT_OPTS) -o $(LIB_DIR)libasmjit.dll \
	$(asmjit_objfiles) $(TMP_DIR)dllmain.o
	gendef - $(LIB_DIR)libasmjit.dll > $(LIB_DIR)libasmjit.def
	dlltool -d $(LIB_DIR)libasmjit.def -l $(LIB_DIR)libasmjit.a
	strip $(LIB_DIR)libasmjit.dll
	upx   $(LIB_DIR)libasmjit.dll

# xbase64 - database dll:
xbase_dll: $(xbase_srcfiles) $(xbase_objfiles)
	$(GXX_BIN) $(JIT_DEF)  -o $(TMP_DIR)dllmain.o $(SRC_DIR)dllmain.cc
	$(GXX_BIN) $(JIT_OPTS) -o $(LIB_DIR)libxbase64.dll \
	$(xbase_objfiles) $(TMP_DIR)dllmain.o
	gendef - $(LIB_DIR)libxbase64.dll > $(LIB_DIR)libxbase64.def
	dlltool -d $(LIB_DIR)libxbase64.def -l $(LIB_DIR)libxbase64.a
	strip $(LIB_DIR)libxbase64.dll
	upx   $(LIB_DIR)libxbase64.dll

# boost.program_options.dll:
boost_podll: $(boost_srcpo_files) $(boost_objpo_files)
	$(GXX_BIN) $(JIT_DEF)  -o $(TMP_DIR)dllmain.o $(SRC_DIR)dllmain.cc
	$(GXX_BIN) $(JIT_OPTS) -o $(LIB_DIR)libboost.program_options.dll \
	$(LIB_LINK_BOOST_PO_LIB) \
	$(boost_objpo_files) $(TMP_DIR)dllmain.o
	gendef - $(LIB_DIR)libboost.program_options.dll > $(LIB_DIR)libboost.program_options.def
	dlltool -d $(LIB_DIR)libboost.program_options.def -l $(LIB_DIR)libboost.program_options.a
	strip $(LIB_DIR)libboost.program_options.dll
	upx   $(LIB_DIR)libboost.program_options.dll

boost_static_archive: $(SRC_DIR)boost$(DIR_SEP)ado$(DIR_SEP)boost.cc
	$(GXX_BIN) $(JIT_DEF) -c -o                     \
	$(TMP_DIR)boost$(DIR_SEP)ado$(DIR_SEP)boost.o   \
	$(SRC_DIR)boost$(DIR_SEP)ado$(DIR_SEP)boost.cc
	$(GXX_BIN) -o                                   \
	$(TMP_DIR)boost$(DIR_SEP)ado$(DIR_SEP)boost.exe \
	$(TMP_DIR)boost$(DIR_SEP)ado$(DIR_SEP)boost.o   \
	$(GCC_OPTS)
	strip $(TMP_DIR)boost$(DIR_SEP)ado$(DIR_SEP)boost.exe

#	objdump -x $(LIB_DIR)libboost.program_options.dll | \
#	egrep "^\s*\[[ [:digit:]]{4}\] \w{1,}"            | \
#	sed 's/^\s*\[//'                                  | \
#	sed 's/.*\] //' > $(LIB_DIR)libboost.program_options.exports

#objdump -x libboost.program_options.dll | egrep "^\s*\[[ [:digit:]]{4}\] \w{1,}" | sed 's/^\s*//' | sed 's/\[ \([[:digit:]]*\)\]/[\1]/' | sed 's/^\[//' | sed 's/\]//' | sed 's/^\s*//'


compile: $(COMPILE_PARTS)
	$(GXX_BIN) -o $(PROJECT)$(EXE_EXT) \
	$(obj_files)  $(GCC_OPTS) \
	$(LIB_LINK_ASMJIT_DLL)    \
	$(LIB_LINK_BOOST_PO_DLL)
	$(STRIP) $(PROJECT)$(EXE_EXT)

welcome:
	@$(ECHO) "compile Project for Windows 10 Pro 64-Bit ..."
	@$(ECHO) "create tmp folders"
	@$(MKDIR) -p $(TMP_DIR)boost$(DIR_SEP)program_options
	@$(MKDIR) -p $(TMP_DIR)boost$(DIR_SEP)ado
	@$(MKDIR) -p $(TMP_DIR)asmjit$(DIR_SEP)core
	@$(MKDIR) -p $(TMP_DIR)asmjit$(DIR_SEP)x86
	@$(MKDIR) -p $(TMP_DIR)xbase64

clean:
	@$(ECHO) "clean output folder."
	@$(RMDIR) $(LOC_DIR)*.mo
	@$(RMDIR) $(TMP_DIR)
	@$(ECHO) "create tmp folders..."
	@$(MKDIR) -p $(TMP_DIR)boost$(DIR_SEP)program_options
	@$(MKDIR) -p $(TMP_DIR)boost$(DIR_SEP)ado
	@$(MKDIR) -p $(TMP_DIR)asmjit$(DIR_SEP)core
	@$(MKDIR) -p $(TMP_DIR)asmjit$(DIR_SEP)x86
	@$(MKDIR) -p $(TMP_DIR)xbase64
