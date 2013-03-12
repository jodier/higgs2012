#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

DIR=`pwd`
echo looking for packages in $DIR
PACKAGES=
for file in `find -L $DIR -type f -name Makefile.RootCore | grep cmt/Makefile.RootCore$ | sort -r`
do
    pkg=`dirname $file | xargs dirname`
    PACKAGES="$pkg $PACKAGES"
    name1=`basename $pkg`
    name2=`$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE`
    if test "$name2" == ""
    then
	echo failed to read package name from $pkg/cmt/Makefile.RootCore
	exit 1
    fi
    if test "$name1" != "$name2"
    then
	echo package $pkg should have name $name2
	echo please rename it to `dirname $pkg`/$name2 by typing
	echo   mv \"$pkg\" \"`dirname $pkg`/$name2\"
	exit 1
    fi
done

PKGFILE=$ROOTCOREBIN/packages
rm -f $PKGFILE
touch $PKGFILE

for pkg in $PACKAGES
do
    name=`basename $pkg`
    pkg2=`grep /$name$ $PKGFILE`
    if test "$pkg2" != ""
    then
	echo duplicate packages, please remove one of them:
	echo "  $pkg"
	echo "  $pkg2"
	rm -f $PKGFILE
	exit 1
    fi
    echo $pkg >>$PKGFILE
done

echo packages found:
cat $PKGFILE

echo
echo sorted packages:
if list=`sed 's/.*\///' < $PKGFILE`
then
    true
else
    result=$?
    rm -f $PKGFILE
    exit $result
fi
if list=`$ROOTCOREDIR/scripts/get_dependency.sh $list`
then
    true
else
    result=$?
    rm -f $PKGFILE
    exit $result
fi
if list=`$ROOTCOREDIR/scripts/get_location.sh $list`
then
    true
else
    result=$?
    rm -f $PKGFILE
    exit $result
fi
rm -f $PKGFILE
touch $PKGFILE
for pkg in $list
do
    echo $pkg >>$PKGFILE
done
cat $PKGFILE
