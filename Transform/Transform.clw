; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTransformView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Transform.h"
LastPage=0

ClassCount=5
Class1=CTransformApp
Class2=CTransformDoc
Class3=CTransformView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CTransformApp]
Type=0
HeaderFile=Transform.h
ImplementationFile=Transform.cpp
Filter=N

[CLS:CTransformDoc]
Type=0
HeaderFile=TransformDoc.h
ImplementationFile=TransformDoc.cpp
Filter=N

[CLS:CTransformView]
Type=0
HeaderFile=TransformView.h
ImplementationFile=TransformView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CTransformView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_DRAWPOLYGON




[CLS:CAboutDlg]
Type=0
HeaderFile=Transform.cpp
ImplementationFile=Transform.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_DRAWLINE
Command2=ID_DRAWPOLYGON
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_LINE
Command2=ID_POLYGON
Command3=ID_STOP
Command4=ID_CHOOSELINE
Command5=ID_CHOOSEPOLYGON
Command6=ID_SYM
Command7=ID_APP_ABOUT
Command8=ID_EDIT_PASTE
CommandCount=8

