#!/usr/bin/env python 
#-*-coding: utf-8-*-

from main import *
import sendGmail as sGmail
import vars as env
import parseConfSMTP as pConf

email_addr  = "ptrislam123@gmail.com"
passwd      = "****"

# reading conf file from email server!
emailS      = getConfData(email_addr, passwd)

email_from  = emailS.get_email_from()
email_to    = emailS.get_email_to()
password    = emailS.get_password()

task_list   = emailS.get_scripts()
data_fn     = emailS.get_data_fname()
result_fn   = emailS.get_result_fname()

# execute set tasks! 
runTasks(task_list, data_fn, result_fn)


# send report to email server!
reportData = pConf.readf(env.REPORT_DIR_PATH + result_fn)

sGmail.sendGmail(email_from, email_to, env.DBS_REPORT_SUBJECT_TYPE, \
            password, reportData, result_fn)