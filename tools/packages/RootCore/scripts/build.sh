#!/bin/bash

if test "x$ROOTCOREDIR" = "x"
then
    dir=$0
    if test "`echo $dir | grep ^/`" = ""
    then
	dir=`pwd`/$dir
    fi
    while test "`echo $dir | grep '/\./'`" != ""
    do
	dir=`echo $dir | sed 's/\/\.\//\//'`
    done
    dir=`dirname $dir | xargs dirname`
    (cd $dir && ./configure) || exit $?
    source $dir/scripts/setup.sh || exit $?
fi

if test "x$1" != "x"
then
    $ROOTCOREDIR/scripts/checkout.sh $1 || exit $?
    $ROOTCOREDIR/scripts/update.sh $1 || exit $?
fi

$ROOTCOREDIR/scripts/find_packages.sh || exit $?
if test "x$1" != "x"
then
    # if we updated from SVN the safest thing to do is to remove all
    # dependency files in order to avoid problems with disappearing
    # files.
    $ROOTCOREDIR/scripts/clean_dep.sh || exit $?
fi
$ROOTCOREDIR/scripts/compile.sh || exit $?
$ROOTCOREDIR/scripts/make_par.sh || exit $?
