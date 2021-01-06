#!/usr/bin/env python 2.7
#-*-coding: utf-8-*-

import json


class JsonConfStruct:
    def __init__(self, email_to, email_from, password, \
                data_fname, result_fname,scripts):
                self.__email_to     = email_to
                self.__email_from   = email_from
                self.__password     = password
                self.__data_fname   = data_fname
                self.__result_fname = result_fname
                self.__scripts      = scripts

 
        
    def get_email_to(self):
            return self.__email_to

    def get_email_from(self):
            return self.__email_from

    def get_password(self):
            return self.__password

    def get_data_fname(self):
            return self.__data_fname

    def get_result_fname(self):
            return self.__result_fname

    def get_scripts(self):
            return self.__scripts





def makeJsonConfStruct(json_obj):
    # json_obj -> type(dict)
    if not (isinstance(json_obj, dict)):
            return -1

    em_to       = json_obj['email_to'],
    em_from     = json_obj['email_from'],
    passwd      = json_obj['password'],
    data_fn     = json_obj['data_fname'],
    result_fn   = json_obj['result_fname'],
    scripts     = []

    for i in json_obj['scripts']:
        scripts.append(i.encode('UTF-8'))

    return JsonConfStruct(
        em_to,
        em_from,
        passwd,
        data_fn,
        result_fn,
        scripts
    )


def getJsonDict(jsonConfStruct):
    # jsonConfStruct -> type(JsonConfStruct)
    if not (isinstance(jsonConfStruct, JsonConfStruct)):
            return -1

    jdict = {}

    jdict['email_to']       = jsonConfStruct.get_email_to()
    jdict['email_from']     = jsonConfStruct.get_email_from()
    jdict['password']       = jsonConfStruct.get_password()
    jdict['data_fname']     = jsonConfStruct.get_data_fname()
    jdict['result_fname']   = jsonConfStruct.get_result_fname()
    jdict['scripts']        = jsonConfStruct.get_scripts()

    return jdict



def write_json_obj(fname, obj):
    with open(fname, 'w') as file:
        json.dump(obj, file, indent=4)



def read_json_obj(fname):
    with open(fname, 'r') as file:
        return json.load(file)


def getConf(fname):
        json_o = read_json_obj(fname)
        return makeJsonConfStruct(json_o)