#!/bin/bash

pat_include=`echo $ROOTCOREBIN/include/ | sed 's/\//\\\\\//g'`

for pkg in `cat $ROOTCOREBIN/packages`
do
    if test "`ls $pkg/obj 2>/dev/null | grep -E \\.d$`" != ""
    then
	name=`basename $pkg`
	reldep=`cat $pkg/obj/*.d | sed 's/  */\
/g' | grep "^$ROOTCOREBIN/include/" | sed "s/^$pat_include//" | sed 's/\/.*//' | grep -v "^$name$" | sort | uniq`
	fuldep="`$ROOTCOREDIR/scripts/get_dependency.sh $reldep` $name"
	pkgdep="`$ROOTCOREDIR/scripts/get_dependency.sh $name`"
	miss=""
	for dep in $reldep
	do
	    if test "`echo " $pkgdep " | grep " $dep "`" == ""
	    then
		miss="$miss $dep"
	    fi
	done
	extra=""
	for dep in `$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_DEP` `$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_TRYDEP`
	do
	    if test "`echo " $fuldep " | grep " $dep "`" == "" -a "`grep "/$dep$" $ROOTCOREBIN/packages`" != "" 
	    then
		extra="$extra $dep"
	    fi
	done
	pedantic=`$ROOTCOREDIR/scripts/get_field.sh $pkg/cmt/Makefile.RootCore PACKAGE_PEDANTIC`
	if test "$miss" != "" -o "$extra" != "" -o "$pedantic" != "1"
	then
	    echo $pkg:
	    echo "   miss  = $miss"
	    echo "   extra = $extra"
	    echo "   pedantic = $pedantic"
	fi
    fi
done
true
