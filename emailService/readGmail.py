#!/usr/bin/env python
#-*-coding: utf-8-*-

import imaplib
import email
import vars

class EmailStruct:

        def __init__(self, email_to, email_from, email_subject, \
                        email_id, email_date, email_body):
                        self.__email_to           = email_to
                        self.__email_from         = email_from
                        self.__email_subject      = email_subject
                        self.__email_id           = email_id
                        self.__email_date         = email_date
                        self.__email_body         = email_body.encode("UTF-8")
			# email_body.encode - encode unicode from usuali string utf-8

        def get_addr_to(self):
                return self.__email_to

        def get_addr_from(self):
                return self.__email_from

        def get_id(self):
                return self.__email_id

        def get_subject(self):
                return self.__email_subject


        def get_date(self):
                return self.__email_date

        def get_body(self):
                return self.__email_body


#EmailStruct_END


def readEmailBody(email_message):
        if email_message.is_multipart():
                for payload in email_message.get_payload():
                        body = payload.get_payload(decode=True).decode('utf-8')
                        return body
        else:
                body = payload.get_payload(decode=True).decode('utf-8')
                return body



def parseGmail(email_message):
        email_to                = email_message['To']
        email_from              = email_message['From']
        email_subject           = email_message['Subject']
        email_id                = email_message['Message-Id']
        email_date              = email_message['Date']
        email_body              = readEmailBody(email_message)


        emailStruct = EmailStruct(email_to, email_from, email_subject, email_id, email_date, email_body)
        return emailStruct





def searchGmail(id_list, mail, data, emailSubjectType):
        for id in reversed(id_list):
                # for id in id_list:
                id_num          = int(id)
                email_id        = id_list[id_num - 1]

                result, data    = mail.fetch(email_id, '(RFC822)')

                raw_email       = data[0][1]
		
                email_message   = email.message_from_string(raw_email)

                email_subject   = email_message['Subject']

                if (email_subject == emailSubjectType):
                        return email_message


        return -1








def readGmail(email_addr, password, emailSubjectType):
    mail = imaplib.IMAP4_SSL('imap.gmail.com')
    mail.login(email_addr, password)

    mail.list()
    mail.select('INBOX')

    result, data = mail.search(None, "ALL")

    ids = data[0]
    id_list = ids.split()   

    email_message = searchGmail(id_list, mail, data, emailSubjectType)

    return parseGmail(email_message)
    


def getConfGmail():
        pass

def getDataGmail():
        pass

   

    



