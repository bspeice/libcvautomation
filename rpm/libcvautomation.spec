#Specfile for Libcvautomation
#This specfile builds the library and headers for Libcvautomation
%global VERSION 1.2
%global PATCHLEVEL 0

Summary: GUI Automation and Testing tool based on OpenCV and XTest
Name: libcvautomation
Version: %{VERSION}
Release: %{PATCHLEVEL}
Source: https://github.com/DjBushido/libcvautomation/%{name}-%{VERSION}.tar.gz
URL: http://djbushido.github.com/libcvautomation/
Vendor: MOSAIC at University of North Carolina at Charlotte
Packager: Bradlee Speice <bspeice@uncc.edu>
License: BSD 2-clause
Group: Development/Tools

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%description
Libcvautomation is a GUI automation and testing tool based on image recognition and response. This program was designed as a direct replacement for Sikuli and Xpresser. Each solution had large problems with crashing, and both refused to function on Red Hat Linux and Ubuntu 12.04. The author really liked the way each of these programs approached GUI automation, but they simply didn't work. As such, a simple library was designed to integrate OpenCV and XTest, which can be used by BASH to drive GUI testing and automation, and works on both new and old Linux distributions.

%prep
%setup -q

%build
%configure \
	--without-examples
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
#The following section is a hack to get the RPM to build
rm -rf $RPM_BUILD_ROOT/usr/share/* $RPM_BUILD_ROOT/usr/bin/*

%clean
rm -rf $RPM_BUILD_ROOT

%files
/etc/*
/usr/include/*
/usr/lib64/*
