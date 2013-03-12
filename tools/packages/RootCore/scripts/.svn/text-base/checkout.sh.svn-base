#!/bin/bash

source "`dirname $0`/preamble.sh" "$0"

test \! -f "$1" && echo could not find list file $1 && exit 1

for package in `grep -v '^#' $1`
do
    $ROOTCOREDIR/scripts/checkout_pkg.sh $package || exit $?
done
true
