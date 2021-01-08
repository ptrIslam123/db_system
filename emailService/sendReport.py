#!/usr/bin/env python
#-*-coding: utf-8-*-

from sys import argv
import sendGmail as smtp
import parseConfSMTP as parseConf
import sysloger as sysloger
import vars

    


def sendReport(fname):
    # READ AND PARSE MAIN CONFIGURATION FILE 
    confObj = parseConf.getConf(fname)


    subscription    = vars.DBS_REPORT_SUBJECT_TYPE
    report_dir_path = vars.REPORT_DIR_PATH 

    resultFilePath = report_dir_path + confObj.get_result_fname()


    reportData = parseConf.readf(resultFilePath)



    # SEND REPORT TO MAIL

    smtp.sendGmail(
            confObj.get_email_to(),
            confObj.get_email_from(),
            subscription,
            confObj.get_password(),
            reportData,
            confObj.get_result_fname()
    )







