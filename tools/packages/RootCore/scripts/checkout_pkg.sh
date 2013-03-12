#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

test "$1" = "" && echo $0: no package specified && exit 1
package=$1

if test "`basename $package`" = "trunk"
then
    name=`dirname $package | xargs basename`
elif test "`basename $package`" = "tags"
then
    name=`dirname $package | xargs basename`
elif test "`dirname $package | xargs basename`" = "tags"
then
    name=`dirname $package | xargs dirname | xargs basename`
elif test "`dirname $package | xargs basename`" = "branches"
then
    name=`dirname $package | xargs dirname | xargs basename`
else
    name=`basename $package`
fi

if test \! -d $name
then
    package=`$ROOTCOREDIR/scripts/svn_get_url.sh $package`
    echo svn co $package $name
    svn co $package $name || exit $?
fi
true
