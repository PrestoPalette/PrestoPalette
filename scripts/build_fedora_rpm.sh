# https://fedoraproject.org/wiki/How_to_create_a_GNU_Hello_RPM_package

rpmdev-setuptree
cd ~/rpmbuild/SOURCES

# https://stackoverflow.com/questions/33177450/how-do-i-get-rpmbuild-to-download-all-of-the-sources-for-a-particular-spec
rpmbuild --undefine=_disable_source_fetch -ba PrestoPalette.spec

rpmlint PrestoPalette.spec
