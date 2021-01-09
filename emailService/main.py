#!/usr/bin/env python 
#-*-coding: utf-8-*-

import vars as env
import sendGmail as sGmail
import sendReport as sReport
import readGmail as rGmail
import parseConfSMTP as pConf
import execTasks as execT
import sysloger 


def createWorkFile(wordData):
    pConf.writef(env.WORD_FILE_NAME, wordData)
    sysloger.log(env.EVENT_CREATE_WORD_SPACE)


def clearWordSpace(fname):
    pConf.removef(fname)
    sysloger.log(env.EVENT_CLEAR_WORK_SPACE + fname)


def runTasks(task_list, data, result_fn):
    if not (isinstance(task_list, list)):
        return -1

    createWorkFile(data)

    for task in task_list:
        taskFileName = env.SCRIPTS_DIR_PATH + task

        execT.execTaskAndWriteResultToFile([taskFileName], result_fn)

    sysloger.log(env.EVENT_RUN_TASK + taskFileName)



def sendReport():
    sReport.sendReport(env.MAIN_CONFIG_FILE_PATH)
    sysloger.log(env.EVENT_SEND_REPORT)


def sendData(email_from, email_to, password, data, fname):
    sGmail.sendGmail(email_from, email_to, env.DBS_DATA_SUBJECT_TYPE,\
                     password, data, fname)
    sysloger.log(env.EVENT_SEND_DATA)



def sendConfData(email_from, email_to, password, confData, confName):
    sGmail.sendGmail(email_from, email_to, env.DBS_CONF_SUBJECT_TYPE, \
                    password, confData, confName)
    sysloger.log(env.EVENT_SEND_CONF)




def getReport(email_addr, password):
    emailS = rGmail.readGmail(email_addr, password, \
                                 env.DBS_REPORT_SUBJECT_TYPE)

    sysloger.log(env.EVENT_GET_REPORT)
    return emailS



def getData(email_addr, password):
    emailS = rGmail.readGmail(email_addr, password, \
                            env.DBS_DATA_SUBJECT_TYPE)
    sysloger.log(env.EVENT_GET_DATA)
    return emailS.get_body()


def getConfData(email_addr, password):
    emailS = rGmail.readGmail(email_addr, password, \
                            env.DBS_CONF_SUBJECT_TYPE)
    strJson = emailS.get_body()
    sysloger.log(env.EVENT_GET_CONF)
    return pConf.strToJsonConfStruct(strJson)


def main():
    email_addr  = "ptrislam123@gmail.com"
    passwd      = "1w2q3r4e"

    emailS      = getConfData(email_addr, passwd)
    targetData  = getData(email_addr, passwd)

    email_from  = emailS.get_email_from()
    email_to    = emailS.get_email_to()
    password    = emailS.get_password()

    task_list   = emailS.get_scripts()
    data_fn     = emailS.get_data_fname()
    result_fn   = emailS.get_result_fname()

    # execute set tasks! 
    runTasks(task_list, targetData, result_fn)


    # send report to email server!
    reportData = pConf.readf(env.REPORT_DIR_PATH + result_fn)

    sGmail.sendGmail(email_from, email_to, env.DBS_REPORT_SUBJECT_TYPE, \
                password, reportData, result_fn)

    clearWordSpace(env.REPORT_DIR_PATH + result_fn)





if __name__ == "__main__":
    main()