#!/usr/bin/env python 
#-*-coding: utf-8-*-

import vars as env
import subprocess as sproc

def execTask(task):
    return sproc.check_output(task)    


def execTaskAndWriteResultToFile(task, fname):
    result = execTask(task)
    result_fn = env.REPORT_DIR_PATH + fname
    with open(result_fn, 'aw') as file:
        file.write(result)
    





