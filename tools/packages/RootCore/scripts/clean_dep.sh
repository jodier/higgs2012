#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

rm -f $ROOTCOREDIR/scripts/load_packages_C.*
for pkg in `cat $pkgfile`
do
    echo cleaning dependencies in $pkg
    cd $pkg
    rm -rf obj/*.d
done

if test "$ROOTCOREOBJ" != ""
then
    rm -rf $ROOTCOREOBJ/*/obj/*.d
fi

true
