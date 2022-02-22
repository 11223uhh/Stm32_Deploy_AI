TARGET = cv
BINTYPE = DLL
ROOT = ..\..
PCH = _cv.h
PCH_STARTER = cvprecomp

OBJS = $(OBJPATH)/cvaccum.obj        $(OBJPATH)/cvadapthresh.obj \
    $(OBJPATH)/cvapprox.obj  $(OBJPATH)/cvcalccontrasthistogram.obj \
    $(OBJPATH)/cvcalcimagehomography.obj     $(OBJPATH)/cvcalibinit.obj \
    $(OBJPATH)/cvcalibration.obj     $(OBJPATH)/cvcamshift.obj \
    $(OBJPATH)/cvcanny.obj   $(OBJPATH)/cvcolor.obj \
    $(OBJPATH)/cvcondens.obj         $(OBJPATH)/cvcontours.obj \
    $(OBJPATH)/cvcontourtree.obj     $(OBJPATH)/cvconvhull.obj \
    $(OBJPATH)/cvconvolve.obj        $(OBJPATH)/cvcorner.obj \
    $(OBJPATH)/cvcornersubpix.obj    $(OBJPATH)/cvderiv.obj \
    $(OBJPATH)/cvdistransform.obj    $(OBJPATH)/cvdominants.obj \
    $(OBJPATH)/cvemd.obj     $(OBJPATH)/cvfeatureselect.obj \
    $(OBJPATH)/cvfilter.obj  $(OBJPATH)/cvfloodfill.obj \
    $(OBJPATH)/cvfundam.obj  $(OBJPATH)/cvgeometry.obj \
    $(OBJPATH)/cvhaar.obj    $(OBJPATH)/cvhistogram.obj \
    $(OBJPATH)/cvhough.obj   $(OBJPATH)/cvimgwarp.obj $(OBJPATH)/cvinpaint.obj \
    $(OBJPATH)/cvkalman.obj  $(OBJPATH)/cvlinefit.obj \
    $(OBJPATH)/cvlkpyramid.obj       $(OBJPATH)/cvmatchcontours.obj \
    $(OBJPATH)/cvmoments.obj         $(OBJPATH)/cvmorph.obj \
    $(OBJPATH)/cvmotempl.obj         $(OBJPATH)/cvoptflowbm.obj \
    $(OBJPATH)/cvoptflowhs.obj       $(OBJPATH)/cvoptflowlk.obj \
    $(OBJPATH)/cvpgh.obj     $(OBJPATH)/cvposit.obj \
    $(OBJPATH)/cvpyramids.obj \
    $(OBJPATH)/cvpyrsegmentation.obj $(OBJPATH)/cvrotcalipers.obj \
    $(OBJPATH)/cvsamplers.obj        $(OBJPATH)/cvsegmentation.obj \
    $(OBJPATH)/cvshapedescr.obj      $(OBJPATH)/cvsmooth.obj \
    $(OBJPATH)/cvsnakes.obj  $(OBJPATH)/cvsubdivision2d.obj \
    $(OBJPATH)/cvsumpixels.obj       $(OBJPATH)/cvswitcher.obj \
    $(OBJPATH)/cvtables.obj  $(OBJPATH)/cvtemplmatch.obj \
    $(OBJPATH)/cvthresh.obj  $(OBJPATH)/cvundistort.obj \
    $(OBJPATH)/cvutils.obj

INCS = ../include/cv.h ../include/cv.hpp ../include/cvcompat.h ../include/cvtypes.h \
      ./_cv.h ./_cvgeom.h ./_cvimgproc.h ./_cvipp.h ./_cvlist.h ./_cvmatrix.h \
      $(ROOT)/cxcore/include/cxcore.h $(ROOT)/cxcore/include/cxcore.hpp \
      $(ROOT)/cxcore/include/cxerror.h $(ROOT)/cxcore/include/cxmisc.h \
      $(ROOT)/cxcore/include/cxtypes.h $(ROOT)/cxcore/include/cvver.h

CXXFLAGS_PROJ = /I"." /I"../include" /I"$(ROOT)/cxcore/include"
LIBS_PROJ = $(LIBPATH)"$(ROOT)/lib" cxcore$(DBG)$(OUT_P_SUFFIX).lib

!include $(ROOT)/_make/make_module_$(MS).mak
