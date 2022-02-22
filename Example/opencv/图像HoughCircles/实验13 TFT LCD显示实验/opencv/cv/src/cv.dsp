# Microsoft Developer Studio Project File - Name="cv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=cv - Win32 Debug64 Itanium
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cv.mak" CFG="cv - Win32 Debug64 Itanium"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cv - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cv - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cv - Win32 Release64" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cv - Win32 Debug64" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cv - Win32 Release64 Itanium" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "cv - Win32 Debug64 Itanium" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\CV_Rls"
# PROP Intermediate_Dir "..\..\_temp\CV_Rls"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W4 /Zi /O2 /Ob2 /I "..\..\cxcore\include" /I "." /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "CVAPI_EXPORTS" /FR /Yu"_cv.h" /FD /Zm200 /Qopenmp /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib cxcore.lib /nologo /subsystem:windows /dll /pdb:"..\..\bin/cv100.pdb" /debug /machine:I386 /nodefaultlib:"libmmd.lib" /out:"..\..\bin\cv100.dll" /implib:"../../lib/cv.lib" /libpath:"..\..\lib"
# SUBTRACT LINK32 /profile /pdb:none /map

!ELSEIF  "$(CFG)" == "cv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\CV_Dbg"
# PROP Intermediate_Dir "..\..\_temp\CV_Dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W4 /Gm /Zi /Od /I "..\..\cxcore\include" /I "." /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "CVAPI_EXPORTS" /FR /Yu"_cv.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib cxcored.lib /nologo /subsystem:windows /dll /pdb:"..\..\bin/cv100d.pdb" /debug /machine:I386 /nodefaultlib:"libmmdd.lib" /out:"..\..\bin\cv100d.dll" /implib:"../../lib/cvd.lib" /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "cv - Win32 Release64"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "cv___Win32_Release64"
# PROP BASE Intermediate_Dir "cv___Win32_Release64"
# PROP BASE Ignore_Export_Lib 1
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\cv_Rls64"
# PROP Intermediate_Dir "..\..\_temp\cv_Rls64"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /G6 /MD /W4 /Zi /O2 /Ob2 /I "..\..\cxcore\include" /I "." /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "CVAPI_EXPORTS" /FR /Yu"_cv.h" /FD /Zm200 /c
# ADD CPP /nologo /MD /W4 /Zi /O2 /Ob2 /I "..\..\cxcore\include" /I "." /I "..\include" /D "_WINDOWS" /D "CVAPI_EXPORTS" /D "NDEBUG" /D "WIN32" /D "WIN64" /D "EM64T" /FR /Yu"_cv.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib cxcore.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /nodefaultlib:"libmmd.lib" /out:"..\..\bin\cv100.dll" /implib:"../../lib/cv.lib" /libpath:"..\..\lib" /machine:AMD64
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 kernel32.lib user32.lib gdi32.lib cxcore_64.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /nodefaultlib:"libmmd.lib" /out:"..\..\bin\cv100_64.dll" /implib:"../../lib/cv_64.lib" /libpath:"..\..\lib" /machine:AMD64
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "cv - Win32 Debug64"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cv___Win32_Debug64"
# PROP BASE Intermediate_Dir "cv___Win32_Debug64"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\cv_Dbg64"
# PROP Intermediate_Dir "..\..\_temp\cv_Dbg64"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /G6 /MDd /W4 /Gm /Zi /Od /I "..\..\cxcore\include" /I "." /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "CVAPI_EXPORTS" /FR /Yu"_cv.h" /FD /GZ /Zm200 /c
# ADD CPP /nologo /MDd /W4 /Gm /Zi /Od /I "..\..\cxcore\include" /I "." /I "..\include" /D "_WINDOWS" /D "CVAPI_EXPORTS" /D "_DEBUG" /D "WIN32" /D "WIN64" /D "EM64T" /FR /Yu"_cv.h" /FD /Zm200 /Wp64 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib cxcored.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /nodefaultlib:"libmmdd.lib" /out:"..\..\bin\cv100d.dll" /implib:"../../lib/cvd.lib" /libpath:"..\..\lib" /machine:AMD64
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib cxcored_64.lib /nologo /subsystem:windows /dll /pdb:"..\..\bin/cv100d_64.pdb" /debug /machine:IX86 /nodefaultlib:"libmmdd.lib" /out:"..\..\bin\cv100d_64.dll" /implib:"../../lib/cvd_64.lib" /libpath:"..\..\lib" /machine:AMD64
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "cv - Win32 Release64 Itanium"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "cv___Win32_Release64_Itanium"
# PROP BASE Intermediate_Dir "cv___Win32_Release64_Itanium"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\_temp\cv_RlsI7"
# PROP Intermediate_Dir "..\..\_temp\cv_RlsI7"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MD /W4 /Zi /O2 /Ob2 /I "..\..\cxcore\include" /I "." /I "..\include" /D "_WINDOWS" /D "CVAPI_EXPORTS" /D "NDEBUG" /D "WIN32" /D "WIN64" /FR /Yu"_cv.h" /FD /Zm200 /c
# ADD CPP /nologo /MD /w /W0 /Zi /O2 /Ob2 /I "..\..\cxcore\include" /I "." /I "..\include" /D "_WINDOWS" /D "CVAPI_EXPORTS" /D "NDEBUG" /D "WIN32" /D "WIN64" /FR /Yu"_cv.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib cxcore_i7.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /nodefaultlib:"libmmd.lib" /out:"..\..\bin\cv100_i7.dll" /implib:"../../lib/cv_i7.lib" /libpath:"..\..\lib" /machine:IA64
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib cxcore_i7.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"..\..\bin\cv100_i7.dll" /implib:"../../lib/cv_i7.lib" /libpath:"..\..\lib" /machine:IA64
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "cv - Win32 Debug64 Itanium"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cv___Win32_Debug64_Itanium"
# PROP BASE Intermediate_Dir "cv___Win32_Debug64_Itanium"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\_temp\cv_DbgI7"
# PROP Intermediate_Dir "..\..\_temp\cv_DbgI7"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MDd /W4 /Gm /Zi /Od /I "..\..\cxcore\include" /I "." /I "..\include" /D "_WINDOWS" /D "CVAPI_EXPORTS" /D "_DEBUG" /D "WIN32" /D "WIN64" /D "EM64T" /FR /Yu"_cv.h" /FD /Zm200 /Wp64 /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /I "..\..\cxcore\include" /I "." /I "..\include" /D "_WINDOWS" /D "CVAPI_EXPORTS" /D "_DEBUG" /D "WIN32" /D "WIN64" /FR /Yu"_cv.h" /FD /Zm200 /Qwd167 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib cxcored_i7.lib /nologo /subsystem:windows /dll /pdb:"..\..\bin/cv100d_i7.pdb" /debug /machine:IX86 /nodefaultlib:"libmmdd.lib" /out:"..\..\bin\cv100d_i7.dll" /implib:"../../lib/cvd_i7.lib" /libpath:"..\..\lib" /machine:IA64
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib cxcored_i7.lib /nologo /subsystem:windows /dll /pdb:"..\..\bin/cv100d_i7.pdb" /debug /machine:IX86 /out:"..\..\bin\cv100d_i7.dll" /implib:"../../lib/cvd_i7.lib" /libpath:"..\..\lib" /machine:IA64
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "cv - Win32 Release"
# Name "cv - Win32 Debug"
# Name "cv - Win32 Release64"
# Name "cv - Win32 Debug64"
# Name "cv - Win32 Release64 Itanium"
# Name "cv - Win32 Debug64 Itanium"
# Begin Group "Src"

# PROP Default_Filter ""
# Begin Group "ImageProcessing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cvadapthresh.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcalccontrasthistogram.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcanny.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcolor.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcontours.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcorner.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcornersubpix.cpp
# End Source File
# Begin Source File

SOURCE=.\cvderiv.cpp
# End Source File
# Begin Source File

SOURCE=.\cvfeatureselect.cpp
# End Source File
# Begin Source File

SOURCE=.\cvfilter.cpp
# End Source File
# Begin Source File

SOURCE=.\cvfloodfill.cpp
# End Source File
# Begin Source File

SOURCE=.\cvhistogram.cpp
# End Source File
# Begin Source File

SOURCE=.\cvimgwarp.cpp
# End Source File
# Begin Source File

SOURCE=.\cvinpaint.cpp
# End Source File
# Begin Source File

SOURCE=.\cvmoments.cpp
# End Source File
# Begin Source File

SOURCE=.\cvmorph.cpp
# End Source File
# Begin Source File

SOURCE=.\cvpyramids.cpp
# End Source File
# Begin Source File

SOURCE=.\cvsamplers.cpp
# End Source File
# Begin Source File

SOURCE=.\cvsegmentation.cpp
# End Source File
# Begin Source File

SOURCE=.\cvsmooth.cpp
# End Source File
# Begin Source File

SOURCE=.\cvtemplmatch.cpp
# End Source File
# Begin Source File

SOURCE=.\cvthresh.cpp
# End Source File
# End Group
# Begin Group "StructuralAnalysis"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cvapprox.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcontourtree.cpp
# End Source File
# Begin Source File

SOURCE=.\cvconvhull.cpp
# End Source File
# Begin Source File

SOURCE=.\cvdistransform.cpp
# End Source File
# Begin Source File

SOURCE=.\cvdominants.cpp
# End Source File
# Begin Source File

SOURCE=.\cvemd.cpp
# End Source File
# Begin Source File

SOURCE=.\cvgeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\cvhough.cpp
# End Source File
# Begin Source File

SOURCE=.\cvlinefit.cpp
# End Source File
# Begin Source File

SOURCE=.\cvmatchcontours.cpp
# End Source File
# Begin Source File

SOURCE=.\cvpgh.cpp
# End Source File
# Begin Source File

SOURCE=.\cvpyrsegmentation.cpp
# End Source File
# Begin Source File

SOURCE=.\cvrotcalipers.cpp
# End Source File
# Begin Source File

SOURCE=.\cvshapedescr.cpp
# End Source File
# Begin Source File

SOURCE=.\cvsubdivision2d.cpp
# End Source File
# End Group
# Begin Group "MotionAndTracking"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cvcamshift.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcondens.cpp
# End Source File
# Begin Source File

SOURCE=.\cvkalman.cpp
# End Source File
# Begin Source File

SOURCE=.\cvlkpyramid.cpp
# End Source File
# Begin Source File

SOURCE=.\cvmotempl.cpp
# End Source File
# Begin Source File

SOURCE=.\cvoptflowbm.cpp
# End Source File
# Begin Source File

SOURCE=.\cvoptflowhs.cpp
# End Source File
# Begin Source File

SOURCE=.\cvoptflowlk.cpp
# End Source File
# Begin Source File

SOURCE=.\cvsnakes.cpp
# End Source File
# End Group
# Begin Group "3D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cvcalcimagehomography.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcalibinit.cpp
# End Source File
# Begin Source File

SOURCE=.\cvcalibration.cpp
# End Source File
# Begin Source File

SOURCE=.\cvfundam.cpp
# End Source File
# Begin Source File

SOURCE=.\cvposit.cpp
# End Source File
# Begin Source File

SOURCE=.\cvundistort.cpp
# End Source File
# End Group
# Begin Group "PatternRecognition"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cvhaar.cpp
# End Source File
# End Group
# Begin Group "CoreEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cvaccum.cpp
# End Source File
# Begin Source File

SOURCE=.\cvsumpixels.cpp
# End Source File
# Begin Source File

SOURCE=.\cvswitcher.cpp
# End Source File
# Begin Source File

SOURCE=.\cvtables.cpp
# End Source File
# Begin Source File

SOURCE=.\cvutils.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cv.rc
# End Source File
# Begin Source File

SOURCE=.\cvprecomp.cpp
# ADD CPP /Yc"_cv.h"
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Group "External"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\cv.h
# End Source File
# Begin Source File

SOURCE=..\include\cv.hpp
# End Source File
# Begin Source File

SOURCE=..\include\cvcompat.h
# End Source File
# Begin Source File

SOURCE=..\include\cvtypes.h
# End Source File
# End Group
# Begin Group "Internal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_cv.h
# End Source File
# Begin Source File

SOURCE=.\_cvgeom.h
# End Source File
# Begin Source File

SOURCE=.\_cvimgproc.h
# End Source File
# Begin Source File

SOURCE=.\_cvipp.h
# End Source File
# Begin Source File

SOURCE=.\_cvlist.h
# End Source File
# Begin Source File

SOURCE=.\_cvmatrix.h
# End Source File
# End Group
# End Group
# End Target
# End Project
