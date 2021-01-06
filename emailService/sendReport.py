#!/usr/bin/env python 2.7
#-*-coding: utf-8-*-

from sys import argv
import sendGmail as smtp
import parseConfSMTP as parseConf
import sysloger as sysloger

#import test as t

MAIN_CONFIGURE_FILE = "./confSMTP/mainConf.json"

def readf(fname):
    with open(fname, mode = 'r') as file:
        return file.read()

    

def runTasks(task_list, data_fname, result_fname):
    if not (isinstance(task_list, list)):
        return -1
    # !main function for executing tasks
    pass


def sendReport(fname):
    # READ AND PARSE MAIN CONFIGURATION FILE 
    confObj = parseConf.getConf(fname)


    #email_to        = confObj().get_email_to()
    #email_from      = confObj().get_email_from
    #password        = confObj.get_password()
    #data_fname      = confObj.get_data_fname()
    #result_fname    = confObj.get_result_fname()
    #tasks           = confObj.get_scripts()

    subscription    = "DBS_REPORT"
    descript_event  = "WARNING: The report was sent to work mail"
    report_dir_path = "../config/reports/" 

    resultFilePath = report_dir_path + confObj.get_result_fname()


    # EXECUTE TASKS

    for taskfname in confObj.get_scripts():
            runTasks(taskfname, confObj.get_data_fname(), \
                    confObj.get_result_fname())

    reportData = readf(resultFilePath)



    # SEND REPORT TO MAIL

    smtp.sendGmail(
            confObj.get_email_to(),
            confObj.get_email_from(),
            subscription,
            confObj.get_password(),
            reportData,
            confObj.get_result_fname()
    )
    
    # WRITE SYSTEM LOG TO LOG FILE
    sysloger.log(sysloger.SYS_LOG_FILE_NAME , descript_event)



#sendReport(MAIN_CONFIGURE_FILE)



