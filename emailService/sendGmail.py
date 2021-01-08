#!/usr/bin/env python
#-*-coding: utf-8-*-

import vars
import smtplib

from email.mime.text        import MIMEText
from email.mime.multipart   import MIMEMultipart


def sendGmail(from_email, to_email, subscription ,password, message, file_name):
    msg = MIMEMultipart()

    msg['From']     = from_email
    msg['To']       = to_email
    msg['Subject']  = subscription

    attachment = MIMEText(message)
    attachment.add_header('Content-Disposition', 'attachment', filename=file_name)
    msg.attach(attachment)


    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()

    server.login(msg['From'], password)
    server.sendmail(msg['From'], msg['To'], msg.as_string())

    server.quit()
    

