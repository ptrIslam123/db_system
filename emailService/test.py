#!/usr/bin/env python 2.7
#-*-coding: utf-8-*-

import parseConfSMTP as p
import json

with open("confSMTP/mainConf.json", 'r') as file:
    data = json.load(file)

    print (type(data['email_from']))
    print (data['email_from'])


