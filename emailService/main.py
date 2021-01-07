#!/usr/bin/env python 2.7
#-*-coding: utf-8-*-


import vars as env
import sendGmail as sGmail
import sendReport as sReport
import readGmail as rGmail
import parseConfSMTP as pConf
import sysloger 


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

