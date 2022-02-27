; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "DTO PHP Class Generator"
#define MyAppVersion "3.0.4.1"
#define MyAppPublisher "Andrey Lamzin"
#define MyAppURL "https://andryuxa.ru/"
#define MyAppExeName "DTOGen.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{61F4D2C0-0668-4DBA-B0A7-3008AB12DE5A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={sd}\RedCafe
DisableDirPage=yes
DefaultGroupName=RedCafePE
OutputDir=C:\dev
OutputBaseFilename=installRedCafePdfExporter
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\dev\v3-r9\hw.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\phonon4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\QtWebKit4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\dev\v3-r9\QtXmlPatterns4.dll"; DestDir: "{app}"; Flags: ignoreversion


Source: "C:\dev\v3-r9\default\*"; DestDir: "{app}\default"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\dev\v3-r9\help\*"; DestDir: "{app}\help"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\dev\v3-r9\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\dev\v3-r9\tmp\*"; DestDir: "{app}\tmp"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}"; Flags: nowait postinstall skipifsilent

