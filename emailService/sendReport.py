from sys import argv
import sendGmail as smtp
import parseConfSMTP as parseConf

def readf(fname):
    file    = open(fname)
    report  = file.read()
    
    file.close()

    return report

def sendReport(from_email, to_email, subscription, password, fname):
    report = readf(fname)
    smtp.sendGmail(from_email, to_email, subscription,  password, report, fname)


#sendReport(email, email, "Result_email", "1w2q3r4e", fname)
scriptfname, conffname = argv

