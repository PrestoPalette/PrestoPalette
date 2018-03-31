
Name:		PrestoPalette
Version:	0.1.31
Release:	1%{dist}
Summary:	An artist's tool for creating harmonious color palettes

Vendor:		John Cboins and Darryl T. Agostinelli
Packager:	Darryl T. Agostinelli <dagostinelli@gmail.com>

License:	MIT
URL:		https://github.com/PrestoPalette
Source:		prestopalette-%{version}.tar.gz

BuildRequires:	qt >= 5.10
BuildRequires:	gcc, make

%description
%{name} is a tool for artists to create harmonious color palettes.

%prep
%setup -q

%build
%qmake -config release PrestoPalette.pro && \
make %{?_smp_mflags} all

%install
cp release/PrestoPalette $RPM_BUILD_ROOT/bin
chmod 755 $RPM_BUILD_ROOT/bin

%changelog
* Thu Mar 29 2018 Darryl T. Agostinelli <dagostinelli@gmail.com> 1.0.0-1
- Created the .spec file for version 1.0.0

