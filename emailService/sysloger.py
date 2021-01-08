#!/usr/bin/env python
#-*-coding: utf-8-*-

import vars as env
from datetime import datetime


def get_time():
    return str(datetime.now())

def log(description):
    with open(env.SYS_LOG_FILE_NAME, mode = 'a') as file:
        file.writelines(get_time() + "\t[" + description + "]\n")


