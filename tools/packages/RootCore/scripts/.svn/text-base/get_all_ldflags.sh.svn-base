#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

packages=""
for pkg in `cat $pkgfile`
do
    packages="$packages `basename $pkg`"
done
$ROOTCOREDIR/scripts/get_ldflags.sh $packages
