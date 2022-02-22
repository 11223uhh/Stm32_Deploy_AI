TARGET = cvaux
BINTYPE = DLL
ROOT = ..\..
PCH = _cvaux.h
PCH_STARTER = precomp

OBJS = \
    $(OBJPATH)/camshift.obj    $(OBJPATH)/cv3dtracker.obj $(OBJPATH)/cvaux.obj \
    $(OBJPATH)/cvauxutils.obj  $(OBJPATH)/cvbgfg_acmmm2003.obj     $(OBJPATH)/cvbgfg_common.obj \
    $(OBJPATH)/cvbgfg_gaussmix.obj      $(OBJPATH)/cvcalibfilter.obj        $(OBJPATH)/cvclique.obj \
    $(OBJPATH)/cvcorrespond.obj         $(OBJPATH)/cvcorrimages.obj         $(OBJPATH)/cvcreatehandmask.obj \
    $(OBJPATH)/cvdpstereo.obj  $(OBJPATH)/cveigenobjects.obj       $(OBJPATH)/cvepilines.obj \
    $(OBJPATH)/cvface.obj      $(OBJPATH)/cvfacedetection.obj      $(OBJPATH)/cvfacetemplate.obj \
    $(OBJPATH)/cvfindface.obj  $(OBJPATH)/cvfindhandregion.obj     $(OBJPATH)/cvhmm.obj \
    $(OBJPATH)/cvhmm1d.obj     $(OBJPATH)/cvhmmobs.obj    $(OBJPATH)/cvlcm.obj \
    $(OBJPATH)/cvlee.obj       $(OBJPATH)/cvlevmar.obj    $(OBJPATH)/cvlevmarprojbandle.obj \
    $(OBJPATH)/cvlevmartrif.obj         $(OBJPATH)/cvlines.obj     $(OBJPATH)/cvlmeds.obj \
    $(OBJPATH)/cvmat.obj       $(OBJPATH)/cvmorphcontours.obj      $(OBJPATH)/cvmorphing.obj \
    $(OBJPATH)/cvprewarp.obj   $(OBJPATH)/cvscanlines.obj $(OBJPATH)/cvsegment.obj \
    $(OBJPATH)/cvsubdiv2.obj   $(OBJPATH)/cvtexture.obj   $(OBJPATH)/cvtrifocal.obj \
    $(OBJPATH)/cvvecfacetracking.obj    $(OBJPATH)/cvvideo.obj     $(OBJPATH)/decomppoly.obj \
    $(OBJPATH)/enmin.obj       $(OBJPATH)/extendededges.obj \
    $(OBJPATH)/bgfg_estimation.obj     $(OBJPATH)/blobtrackanalysis.obj \
    $(OBJPATH)/blobtrackanalysishist.obj        $(OBJPATH)/blobtrackanalysisior.obj \
    $(OBJPATH)/blobtrackanalysistrackdist.obj   $(OBJPATH)/blobtrackgen1.obj \
    $(OBJPATH)/blobtrackgenyml.obj     $(OBJPATH)/blobtrackingauto.obj \
    $(OBJPATH)/blobtrackingcc.obj      $(OBJPATH)/blobtrackingccwithcr.obj \
    $(OBJPATH)/blobtrackingkalman.obj  $(OBJPATH)/blobtrackinglist.obj \
    $(OBJPATH)/blobtrackingmsfg.obj    $(OBJPATH)/blobtrackingmsfgs.obj \
    $(OBJPATH)/blobtrackpostprockalman.obj      $(OBJPATH)/blobtrackpostproclinear.obj \
    $(OBJPATH)/blobtrackpostproclist.obj        $(OBJPATH)/enteringblobdetection.obj \
    $(OBJPATH)/enteringblobdetectionreal.obj    $(OBJPATH)/testseq.obj

INCS = ../include/cvaux.h ../include/cvaux.hpp ../include/cvmat.hpp \
      ../include/cvvidsurv.hpp ./cvface.h ./cvfacedetection.h  \
      ./cvfacetemplate.h ./_cvaux.h ./_cvfacedetection.h \
      ./_cvvectrack.h ./_cvvm.h $(ROOT)/cv/include/cv.h \
      $(ROOT)/cv/include/cv.hpp $(ROOT)/cv/include/cvcompat.h \
      $(ROOT)/cv/include/cvtypes.h $(ROOT)/cv/src/_cvmatrix.h \
      $(ROOT)/cxcore/include/cxcore.h $(ROOT)/cxcore/include/cxcore.hpp \
      $(ROOT)/cxcore/include/cxerror.h $(ROOT)/cxcore/include/cxmisc.h \
      $(ROOT)/cxcore/include/cxtypes.h $(ROOT)/cxcore/include/cvver.h

CXXFLAGS_PROJ = /I"." /I"../include" /I"$(ROOT)/cv/include" /I"$(ROOT)/cv/src" /I"$(ROOT)/cxcore/include"
LIBS_PROJ = $(LIBPATH)"$(ROOT)/lib" cxcore$(DBG)$(OUT_P_SUFFIX).lib cv$(DBG)$(OUT_P_SUFFIX).lib

!if "$(MS)" == "bc"
SRCPATH = .;.\vs
!endif

!include $(ROOT)/_make/make_module_$(MS).mak

!if "$(MS)"=="ms"

# Hack: include all the files from vs subdirectory as well
{.\vs}.cpp{$(OBJPATH)}.obj:
    @-mkdir $(OBJPATH) 2> nul
    @$(CXX) $(CXXFLAGS)$@ $<

!endif
