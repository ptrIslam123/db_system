#!/usr/bin/env python
#-*-coding: utf-8-*-

import main as m
import parseConfSMTP as p
import vars as v


temail_addr = "ptrislam123@gmail.com"
tpassword = "1w2q3r4e"
tdata = p.readf(v.MAIN_CONFIG_FILE_PATH)



def sendTestConf(email_from, email_to, password):
    confData = p.readf(v.MAIN_CONFIG_FILE_PATH)
    m.sendConfData(email_from, email_to, password, confData, v.MAIN_CONFIG_FILE_PATH)



#sendTestConf(temail_addr,temail_addr, tpassword)
#fname = "../config/tables/small_init.txt"

#data = p.readf(fname)

#m.sendData(temail_addr, temail_addr, tpassword, data, fname)

#m.sendConfData(temail_addr, temail_addr, tpassword, tdata, "testConf.json")
#m.sendData(temail_addr, temail_addr, tpassword, "hello world!", "testData.txt")
#m.sendReport()


#strData = m.getData(temail_addr, tpassword)
#print (strData)

#jsonConfStruct = m.getConfData(temail_addr, tpassword)
#print (jsonConfStruct.get_email_from())
#print (jsonConfStruct.get_data_fname())
#print (jsonConfStruct.get_result_fname())
#print (jsonConfStruct.get_scripts())


#emailStruct = m.getReport(temail_addr, tpassword)
#print (emailStruct.get_body())
#print (emailStruct.get_date())
#print (emailStruct.get_id())
#print (emailStruct.get_addr_from())