#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

dependency=`$ROOTCOREDIR/scripts/get_dependency.sh $*` || exit $?

preflags="-L$ROOTCOREBIN/lib"
flags=""
for dep in $dependency
do
    if pkg=`grep -E /$dep\$ $pkgfile`
    then
	true
    else
	error=$?
	echo failed to find package $dep
	exit $error
    fi

    link=`$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_LIBFLAGS`
    preflags="$preflags $link"

    lib=`$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_BINFLAGS`
    flags="$lib $flags"

    for preload in `$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_PRELOAD`
    do
	flags="-l$preload $flags"
    done

    name=`basename $pkg`
    test "`$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_NOCC`" != "1" && \
	flags="-l$name $flags"
done
echo $preflags $flags
