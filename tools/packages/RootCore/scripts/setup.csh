if $?ROOTSYS then
    true
else
    setenv ROOTSYS `root-config --prefix`
    test $? -ne 0 && echo no valid root version found, please set up root && return 1
endif

test "x$ROOTSYS" != "x/cern/root/root_v5.32.00_64" && echo ROOTSYS=$ROOTSYS not /cern/root/root_v5.32.00_64 && echo please set up correct root version or follow the instructions at && echo \ \ https://twiki.cern.ch/twiki/bin/viewauth/Atlas/RootCore#If_Something_Goes_Wrong && return 1

setenv ROOTCOREDIR /atlas/tiouchi/testarea/AtlasOffline-17.2.X/1.higgs/higgs2012/tools/packages/RootCore
if $?ROOTCOREBIN then
    true
else
    setenv ROOTCOREBIN /atlas/tiouchi/testarea/AtlasOffline-17.2.X/1.higgs/higgs2012/tools/packages/RootCore
endif
test \! -d "$ROOTCOREBIN" && echo output directory not found, please create it && echo "  mkdir $ROOTCOREBIN" && return 1

setenv PATH $ROOTCOREBIN/bin:$PATH
if $?LD_LIBRARY_PATH then
    setenv LD_LIBRARY_PATH $ROOTCOREBIN/lib:$LD_LIBRARY_PATH
endif
if $?DYLD_LIBRARY_PATH then
    setenv DYLD_LIBRARY_PATH $ROOTCOREBIN/lib:$DYLD_LIBRARY_PATH
endif
if $?PYTHONPATH then
    setenv PYTHONPATH $ROOTCOREBIN/python:$PYTHONPATH
else
    setenv PYTHONPATH $ROOTCOREBIN/python
endif

mkdir -p $ROOTCOREBIN/bin
test -f $ROOTCOREBIN/bin/rc || ln -s $ROOTCOREDIR/scripts/rc.sh $ROOTCOREBIN/bin/rc
true
