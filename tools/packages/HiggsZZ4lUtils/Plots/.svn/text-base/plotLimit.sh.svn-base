#!/bin/bash

function doCmp(){
root -l -b <<EOF
.L makeplotLimit.c
limit("Limit_v2/NoZMassConstraintHugeErrorZZ_limit.txt","NoZMassConstraintHugeErrorZZ",true,"freeZZ")
.q
EOF

root -l -b <<EOF
.L makeplotLimit.c
limit("Limit_v2/NoZMassConstraintHugeErrorZjetZbbtt_limit.txt","NoZMassConstraintHugeErrorZjetZbbtt",true,"freeNonZZ")
.q
EOF

root -l -b <<EOF
.L makeplotLimit.c
limit("Limit_v2/NoZMassConstraintHugeErrorBkg_limit.txt","NoZMassConstraintHugeErrorBkg",true,"freeBkg")
.q
EOF
}
#doCmp
#root -l -b <<EOF
#.L makeplotLimit.c
#limit("limit_toys6.txt","NoZMassConstraint", true, "Pub")
#.q
#EOF
#cp NoZMassConstraint* ~/Documents/

root -l -b <<EOF
.L makeplotLimit.c
limit("limit/FirstTry2012HugeqqZZError_limit.txt","FirstTry2012HugeqqZZError", true, "freeZZ")
.q
EOF
