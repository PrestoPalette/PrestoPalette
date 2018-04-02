; PrestoPalette Installer Script
#define AppExeName "PrestoPalette.exe"
#define ProductName "PrestoPalette"

#define FileVersion GetFileVersion(AddBackslash(CustomBinaryLocation) + AppExeName)
#define CompanyName GetFileCompany(AddBackslash(CustomBinaryLocation) + AppExeName)
#define ProductVersion GetFileProductVersion(AddBackslash(CustomBinaryLocation) + AppExeName)
#define Copyright GetFileCopyright(AddBackslash(CustomBinaryLocation) + AppExeName)
#define Description GetFileDescription(AddBackslash(CustomBinaryLocation) + AppExeName)

#define AppURL "https://github.com/PrestoPalette/PrestoPalette"

#define FormattedBuildSuffix
#ifdef Configuration
	#define FormattedBuildSuffix " (" + Str(Configuration) + ")"
#endif

[Setup]
; This is the registry key name for the Uninstall area (Software\Microsoft\Windows\CurrentVersion\Uninstall\{AppId}_is1\)
AppId=PrestoPalette

AppName={#ProductName}{#FormattedBuildSuffix}

; Info for the control panel's Add/Remove Programs
AppVersion={#FileVersion}
AppVerName={#ProductName}{#FormattedBuildSuffix} {#FileVersion}
AppPublisher={#CompanyName}
AppPublisherURL={#AppURL}
AppSupportURL={#AppURL}
AppUpdatesURL={#AppURL}
AppCopyright={#Copyright}

VersionInfoVersion={#FileVersion}
VersionInfoTextVersion={#FileVersion}
VersionInfoProductTextVersion={#ProductVersion}
UninstallDisplayIcon={app}\{#AppExeName}
UninstallDisplayName={#ProductName}{#FormattedBuildSuffix}

; Name of installer exe (default is setup.exe)
OutputBaseFilename={#ProductName}-{#FileVersion}{#FormattedBuildSuffix}

; Name of folder in Program Files
DefaultDirName={pf}\{#ProductName}

; Start Menu name
DefaultGroupName={#ProductName}

; Display software license during install
;LicenseFile="path\to\License.txt"

; Release Notes
;InfoBeforeFile="path\to\ReleaseNotes.txt"

; Type of compression to use
;Compression=lzma2

; This is appropriate because the app is relatively small
SolidCompression=yes

; Where to place the resulting installer
OutputDir=installer

; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
ArchitecturesInstallIn64BitMode=x64

; Must be an admin to install
PrivilegesRequired=admin

; Minimum windows version (Vista and higher)
MinVersion=6.0

; Don't warn if directory user picks already exists
DirExistsWarning=no

; Specifies the name of the bitmap file to display in the upper right corner of the wizard window
; The maximum size of the bitmap is 55x58 pixels.
WizardSmallImageFile=icon.bmp

; Makes sure that the app is not already running
AppMutex=PRESTOPALETTE

; Can't install on a network drive (Windows Services don't work like that)
AllowNetworkDrive=no
AllowUNCPath=no

DisableWelcomePage = No
DisableDirPage = Yes
DisableReadyPage = Yes
DisableProgramGroupPage = Yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "{#CustomBinaryLocation}\*"; DestDir: {app}; Flags: recursesubdirs overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
#ifndef Configuration
	Source: "{#CustomBinaryLocation}\vc_redist.x64.exe"; DestDir: {tmp}; Flags: deleteafterinstall
#endif



[Icons]
Name: "{commonprograms}\{#ProductName}"; Filename: "{app}\{#AppExeName}"
Name: "{commondesktop}\{#ProductName}"; Filename: "{app}\{#AppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#ProductName}"; Filename: "{app}\{#AppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{tmp}\vc_redist.x64.exe"; Parameters: "/passive /quiet /norestart"; StatusMsg: Installing 64-bit Microsoft Visual C++ RunTime...; Check: IsNotDebug
Filename: "{app}\{#AppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(ProductName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
function IsNotDebug: Boolean;
begin
#ifdef Configuration
	Result := False
#else
	Result := True
#endif
end;
