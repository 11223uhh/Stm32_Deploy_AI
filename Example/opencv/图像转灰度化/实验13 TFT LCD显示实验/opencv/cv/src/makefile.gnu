TARGET := cv
BINTYPE := DLL
SRC_ROOT := ../../cv/src
INC_ROOT := ../../cv/include
CXCORE_INC := ../../cxcore/include
SRC_DIRS := . ../include ../../cxcore/include

CXXFLAGS := -D"CVAPI_EXPORTS" -I"$(INC_ROOT)" -I"$(SRC_ROOT)" -I"$(CXCORE_INC)"

INCS := cv.h cv.hpp cvcompat.h cvtypes.h \
   _cv.h _cvgeom.h _cvimgproc.h _cvipp.h _cvlist.h _cvmatrix.h \
   cxcore.h cxcore.hpp cxerror.h cxmisc.h cxtypes.h cvver.h

LIBS := -lcxcore$(DBG)

include ../../_make/make_module_gnu.mak
