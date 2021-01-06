#! /bin/bash

reportDirPath="../config/reports/"
filePath=$1

allReportPath="$reportDirPath$filePath"

cd ../../build/


./dbs ../scripts/dbsScripts/statistics.dbs > $allReportPath


