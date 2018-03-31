
Name:		PrestoPalette
Version:	1.0
Release:	1%{dist}
Summary:	An artist's tool for creating harmonious color palettes

Vendor:         John Cboins and Darryl T. Agostinelli
Packager:	Darryl T. Agostinelli <dagostinelli@gmail.com>

License:        MIT
URL:		https://github.com/PrestoPalette
Source0:        https://github.com/%{name}/%{name}/archive/1.0-RC-1.tar.gz

BuildRequires:  cmake >= 3.0
BuildRequires:	gcc, make
BuildRequires:  doxygen, graphviz, doxygen-latex

%description
%{name} is a pure-C math library. It is almost 100% C89/C90 compliant.
This library is intended for use in 2d/3d graphics program (such as games).
Since it is not a general purpose math library, but a library meant for 3D
graphics, certain opinions have been expressed in its design. One of those
design choices, intended to help with speed, is that all objects (matrix, 
vector, quaternion) are mutable. (That means that the objects change their
values.)

%prep
%setup -q
#%setup -q -n %{name}-%{version}

%build
%qmake -config release PrestoPalette.pro && \
ctest -V %{?_smp_mflags} && \
make %{?_smp_mflags} all

%install
make install DESTDIR=$RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{_docdir}/%{name}/html

%check
ctest -V %{?_smp_mflags}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%license %{_licensedir}/lib%{name}/LICENSE
%{_libdir}/libhypatia*.so.*

%changelog
* Thu Mar 29 2018 Darryl T. Agostinelli <dagostinelli@gmail.com> 1.0.0-1
- Created the .spec file for version 1.0.0

