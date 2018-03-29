; PrestoPalette Installer Script

#define AppVersion "1.0"
#define CompanyName "John Cboins and Darryl T. Agostinelli"
#define ProductName "PrestoPalette"
#define ProductVersion "1.0"
#define Copyright "Copyright 2010 John Cboins and Darryl T. Agostinelli"
#define Description "PrestoPalette"
#define BuildConfiguration 
#define AppURL "https://github.com/PrestoPalette/PrestoPalette"
#define AppExeName "PrestoPalette.exe"

#define FormattedBuildSuffix
#if Len(BuildConfiguration) > 0
	#define FormattedBuildSuffix " (" + Str(BuildConfiguration) + ")"
#endif

[Setup]
AppName={#ProductName}{#FormattedBuildSuffix}

; This is the registry key name for the Uninstall area (Software\Microsoft\Windows\CurrentVersion\Uninstall\{AppId}_is1\)
AppId=PrestoPalette

; Name of installer exe (default is setup.exe)
OutputBaseFilename={#ProductName}-{#AppVersion}{#FormattedBuildSuffix}

; Name of folder in Program Files
DefaultDirName={pf}\{#ProductName}

; Start Menu name
DefaultGroupName={#ProductName}

; Info for the control panel's Add/Remove Programs
AppVersion={#AppVersion}
AppVerName={#ProductName}{#FormattedBuildSuffix} {#AppVersion}
AppPublisher={#CompanyName}
AppPublisherURL={#AppURL}
AppSupportURL={#AppURL}
AppUpdatesURL={#AppURL}
AppCopyright={#Copyright}

VersionInfoVersion={#AppVersion}
VersionInfoTextVersion={#AppVersion}
VersionInfoProductTextVersion={#ProductVersion}
UninstallDisplayIcon={app}\{#ProductName}
UninstallDisplayName={#ProductName}{#FormattedBuildSuffix}

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
Source: "{#AppExeName}"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "libEGL.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "libGLESv2.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "Qt5Core.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "Qt5Gui.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "Qt5Multimedia.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "Qt5Network.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
Source: "Qt5Widgets.dll"; DestDir: "{app}"; Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;
; NOTE: Don't use "Flags: overwritereadonly ignoreversion replacesameversion restartreplace uninsrestartdelete;" on any shared system files

[Icons]
Name: "{commonprograms}\{#ProductName}"; Filename: "{app}\{#AppExeName}"
Name: "{commondesktop}\{#ProductName}"; Filename: "{app}\{#AppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#ProductName}"; Filename: "{app}\{#AppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#AppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(ProductName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

