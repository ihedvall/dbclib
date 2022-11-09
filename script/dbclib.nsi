# Copyright 2022 Ingemar Hedvall
# SPDX-License-Identifier: MIT 

!include MUI2.nsh
!include x64.nsh
!include FileFunc.nsh
 
Name "Util Applications and Libraries"
OutFile "..\cmake-build-release\utillib.exe"
Unicode True

RequestExecutionLevel admin

Var StartMenuFolder

InstallDir "$LOCALAPPDATA\UtilLib"
InstallDirRegKey HKLM "Software\UtilLib" ""


!define MUI_ABORTWARNING
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\UtilLib"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Util Apps & Libs"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM" 
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\UtilLib"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
   
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH
  
!insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section  "Applications" App
  SectionIn RO
  SetRegView 64	
  SetShellVarContext all

  SetOutPath "$INSTDIR\bin"
  File "..\cmake-build-release\listend\*.exe"
  File "..\cmake-build-release\listenviewer\*.exe"
  File "..\cmake-build-release\serviced\serviced.exe"
  File "..\cmake-build-release\serviceexplorer\serviceexplorer.exe"
  
  SetOutPath "$INSTDIR\img"
  File "..\img\*.*"
  
  ;Store installation folder
  WriteRegStr HKLM "Software\ReportServer" "" $INSTDIR
  
  WriteUninstaller "$INSTDIR\Uninstall.exe"  
  
  ; Add /Remove Programs
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0


  WriteRegNone HKLM "${ARP}" "" 
  WriteRegStr HKLM "${ARP}" "InstallLocation" $INSTDIR
  WriteRegStr HKLM "${ARP}" "DisplayIcon" "$INSTDIR\img\utillib.ico"
  WriteRegStr HKLM "${ARP}" "DisplayName" "Util Apps & Libs 1.0"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "1.0.0"
  WriteRegStr HKLM "${ARP}" "Publisher" "Ingemar Hedvall" 
  WriteRegDWORD HKLM "${ARP}" "NoModify" 1 
  WriteRegDWORD HKLM "${ARP}" "NoRepair" 1 
  WriteRegDWORD HKLM "${ARP}" "VersionMajor" 1 
  WriteRegDWORD HKLM "${ARP}" "VersionMinor" 0 	  
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"			 
  WriteRegStr HKLM "${ARP}"  "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""
				 
  ;Create uninstaller

  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Listen Viewer.lnk" "$INSTDIR\bin\listenviewer.exe"
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Service Explorer.lnk" "$INSTDIR\bin\serviceexplorer.exe"
  !insertmacro MUI_STARTMENU_WRITE_END 

SectionEnd

Section /o "Util Library" Util
  SetRegView 64
  
  SetOutPath "$INSTDIR\lib"
  File "..\cmake-build-release\util.lib"
  File "..\cmake-build-debug\utild.lib"
  
  SetOutPath "$INSTDIR\include\util"
  File "..\include\util\*.*"
  
  SetOutPath "$INSTDIR\doc\util"
  File /r "..\docs\manual\html\*.*"
  
  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\Util Library Documentation.lnk" \
	"$INSTDIR\doc\util\index.html" "" "$INSTDIR\img\document.ico" \
	0 SW_SHOWNORMAL
	
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"
SectionEnd

;Section /o "MDF Library" MDF
;  SetRegView 64

;  SetOutPath "$INSTDIR\lib"
;  File "..\cmake-build-release\mdflib\libmdf.a"
;  File "..\cmake-build-debug\mdflib\libmdfd.a"
  
;  SetOutPath "$INSTDIR\include\mdf"
;  File "..\mdflib\include\mdf\*.*"
  
;  SetOutPath "$INSTDIR\doc\mdf"
;  File /r "..\cmake-build-release\mdflib\html\*.*"
  
;  CreateShortcut "$SMPROGRAMS\$StartMenuFolder\MDF Library Documentation.lnk" \
;	"$INSTDIR\doc\mdf\index.html" "" "$INSTDIR\img\document.ico" \
;	0 SW_SHOWNORMAL

;  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
;  IntFmt $0 "0x%08X" $0
;  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"
;SectionEnd


LangString DESC_App ${LANG_ENGLISH} "All executables."
LangString DESC_Util ${LANG_ENGLISH} "Util Library"
;LangString DESC_MDF ${LANG_ENGLISH} "MDF Library"


!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${App} $(DESC_App)
  !insertmacro MUI_DESCRIPTION_TEXT ${Util} $(DESC_Util)
;  !insertmacro MUI_DESCRIPTION_TEXT ${MDF} $(DESC_MDF)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  SetRegView 64	  
  SetShellVarContext all
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  
  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r "$INSTDIR"  
  RMDir /r "$SMPROGRAMS\$StartMenuFolder"
  
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\UtilLib"
  DeleteRegKey HKLM "Software\UtilLib"

SectionEnd