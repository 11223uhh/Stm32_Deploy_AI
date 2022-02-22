TARGET := cvaux
BINTYPE := DLL
SRC_ROOT := ../../cvaux/src
INC_ROOT := ../../cvaux/include
CXCORE_INC := ../../cxcore/include
CV_INC := ../../cv/include
CV_SRC := ../../cv/src
SRC_DIRS := . ./vs ../include ../../cxcore/include ../../cv/include

CXXFLAGS := -D"CVAPI_EXPORTS" -I"$(INC_ROOT)" -I"$(SRC_ROOT)" \
   -I"$(CXCORE_INC)" -I"$(CV_INC)" -I"$(CV_SRC)"

INCS := cvaux.h cvaux.hpp cvmat.hpp cvvidsurv.hpp cvface.h cvfacedetection.h  \
   cvfacetemplate.h _cvaux.h _cvfacedetection.h _cvvectrack.h _cvvm.h \
   cv.h cv.hpp cvcompat.h cvtypes.h $(CV_SRC)/_cvmatrix.h \
   cxcore.h cxcore.hpp cxerror.h cxmisc.h cxtypes.h cvver.h

LIBS := -lcxcore$(DBG) -lcv$(DBG)

include ../../_make/make_module_gnu.mak
