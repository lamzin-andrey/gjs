; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Qt4.6 WebView Desktop API"
#define MyAppVersion "3.1.2-prelease"
#define MyAppPublisher "Andrey Lamzin"
#define MyAppURL "https://andryuxa.ru/portfolio/desktop/qt_javascript_desktop/"
#define MyAppExeName "qdjs.exe"

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
DefaultDirName={sd}\qdjs
DisableDirPage=yes
DefaultGroupName=FreeDevelopers
OutputDir=C:\dev
OutputBaseFilename=installQt4.6WebViewDesktopAPI
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "F:\dev-11-2014\qt\qdjs\release\qdjs.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\phonon4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\QtWebKit4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "F:\dev-11-2014\qt\qdjs\release\QtXmlPatterns4.dll"; DestDir: "{app}"; Flags: ignoreversion


Source: "F:\dev-11-2014\qt\qdjs\release\default\*"; DestDir: "{app}\default"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "F:\dev-11-2014\qt\qdjs\release\lib\*"; DestDir: "{app}\lib"; Flags: ignoreversion recursesubdirs createallsubdirs
; Source: "F:\dev-11-2014\qt\qdjs\release\help\*"; DestDir: "{app}\help"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "F:\dev-11-2014\qt\qdjs\release\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs createallsubdirs
; Source: "F:\dev-11-2014\qt\qdjs\release\tmp\*"; DestDir: "{app}\tmp"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}"; Flags: nowait postinstall skipifsilent

