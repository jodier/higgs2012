#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

for pkg in $ROOTCOREDIR `cat $pkgfile`
do
    if test \! -f $pkg/.svn/entries
    then
	echo `basename $pkg` not in SVN
    else
	url=`grep svn+ssh $pkg/.svn/entries | head -n 1 | sed 's/^svn+ssh:\/\/.*svn.cern.ch\/reps\/atlas/atlas/'`
	if test "$url" != ""
	then
	    echo $url
	else
	    echo `basename $pkg` in SVN, but can\'t extract URL
	fi
    fi
done
