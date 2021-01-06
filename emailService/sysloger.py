#!/usr/bin/env python 2.7
#-*-coding: utf-8-*-

SYS_LOG_FILE_NAME = "../config/log/sys_log.txt"

def get_time():
    return "[12.12.12]"

def log(fname, description):
    with open(fname, mode = 'a') as file:
        file.writelines(get_time() + "\t[" + description + "]\n")

