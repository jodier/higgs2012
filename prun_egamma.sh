#!/bin/sh

OUTDS=user.etiouchi.l_analysis.data12_periodA_egamma_p1044_v1

INDS=\
data12_8TeV.periodA.physics_Egamma.PhysCont.NTUP_HSG2.grp13_v01_p1044/

cp core/include/data12_THiggsD3PD.h core/include/THiggsD3PD.h

prun --exec "l_analysis --grid=prun --enable-ER -o output.root \ %IN" --bexec "make ALL" \
--athenaTag 17.0.4 \
--writeInputToTxt "IN:input.txt" \
--outDS $OUTDS \
--inDS $INDS \
--extFile tools/ilumicalc_2012_period_AllYear_All_Good.root,tools/MC12a.prw.root \
--outputs output.root \
#--excludedSite ANALY_GLASGOW

