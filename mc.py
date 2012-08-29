#!/usr/bin/env python

#############################################################################

import time, getpass, commands

#############################################################################

L = [
	'mc12_8TeV.107650.AlpgenJimmy_AUET2CTEQ6L1_ZeeNp0.merge.NTUP_HSG2.e1218_s1469_s1470_r3542_r3549_p1044/'
	'mc12_8TeV.107660.AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp0.merge.NTUP_HSG2.e1218_s1469_s1470_r3542_r3549_p1044/'
]

#############################################################################

VERSION = int(time.time())

#############################################################################

for in_ds in L:

	out_ds = 'user.e%s.%s.%s-%d_%s' % (getpass.getuser(), in_ds.split('.')[+1], in_ds.split('.')[+2], VERSION, in_ds.split('.')[-1])

	print('Running \'%s\' -> \'%s\'...' % (in_ds, out_ds))

	status, output = commands.getstatusoutput('./run_mc.sh %s %s' % (in_ds, out_ds))

	if status == 0:
		print('[ \033[32m Ok. \033[0m ]')
	else:
		print('[ \033[31mError\033[0m ]')

		print('\033[31m%s\033[0m' % output)

#############################################################################

