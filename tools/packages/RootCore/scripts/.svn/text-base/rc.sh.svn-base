#!/bin/bash

if test "$ROOTCOREDIR" == ""
then
    echo ROOTCOREDIR not set, please source RootCore/scripts/setup.sh
    exit 1
fi

cmd=$1
script=$ROOTCOREDIR/scripts/$cmd.sh
shift

if test \! -x "$script"
then
    /bin/echo -n command $cmd not found, know commands:
    for file in $ROOTCOREDIR/scripts/*.sh
    do
	if test -x $file
	then
	    /bin/echo -n " `basename $file | sed 's/.sh$//'`"
	fi
    done
    echo
fi

$script "$@"
