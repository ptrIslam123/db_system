#!/usr/bin/env python
#-*-coding: utf-8-*-

MAIN_CONFIG_FILE_PATH   = "confSMTP/mainConf.json"
REPORT_DIR_PATH         = "../config/reports/" 
SCRIPTS_DIR_PATH        = "../scripts/bashScripts/"
SYS_LOG_FILE_NAME       = "../config/log/sys_log.txt"
WORD_FILE_NAME          = "../config/tables/init.txt"

DBS_CONF_SUBJECT_TYPE   = "DBS_CONF"
DBS_DATA_SUBJECT_TYPE   = "DBS_DATA"
DBS_REPORT_SUBJECT_TYPE = "DBS_REPORT"
MAIN_CONF_FILE_NAME     = "mainConf.json" 

EVENT_SEND_REPORT   = "WARNING: send a report by mail"
EVENT_SEND_DATA     = "WARNING: send a data by mail"
EVENT_SEND_CONF     = "WARNING: send a configuration data by mail"
EVENT_GET_REPORT    = "WARNING: receiving a report by mail"
EVENT_GET_DATA      = "WARNING: receiving a data by mail"
EVENT_GET_CONF      = "WARNING: receiving a configuration data by mail"
EVENT_RUN_TASK      = "WARNING: run task ==> "

EVENT_CLEAR_WORK_SPACE  = "WARNING: clear work space [file] ==> "
EVENT_CREATE_WORD_SPACE = "WARNING: create word space [OK]"