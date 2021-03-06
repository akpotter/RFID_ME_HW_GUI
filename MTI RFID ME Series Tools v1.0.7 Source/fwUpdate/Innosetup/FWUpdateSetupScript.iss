; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "MTI RFID ME Series FW Update"
#define MyAppVersion "v1.0.3"
#define MyAppPublisher "Microelectronic Technology Inc."
#define MyAppURL "http://www.mti.com/"
#define MyAppExeName "MTI RFID ME Series FW Update.exe"
#define APPPATH "MTI"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{B69AF5D2-6325-4A70-8FD3-BF8665D8EC56}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\\MTI\{#MyAppName}
DefaultGroupName={#APPPATH}\{#MyAppName}
AllowNoIcons=yes
OutputDir=.\output
OutputBaseFilename={#MyAppName} setup  {#MyAppVersion}
SetupIconFile=.\icons\USBControl.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "..\Release\MTI RFID ME Series FW Update.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\Release\Transfer.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\icons\classic-uninstall.ico"; DestDir: "{app}\icons"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: {group}\{cm:UninstallProgram,{#MyAppName}}; Filename: {uninstallexe};  IconFilename: {app}\icons\classic-uninstall.ico 
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, "&", "&&")}}"; Flags: nowait postinstall skipifsilent

