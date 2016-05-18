#!/bin/bash
export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
port=$1
i=1
addres=1
while [ -f runing ]
do
if [ $i -ge 2048 ]; then
i=1
fi
echo $i
rm -rf ~/log/*
start=`date +%s`
./smart32 $addres $i $port AT+KTKJ=TESTID,? AT+KTSM=TESTID,? AT+KTYX=TESTID,? AT+KTFX=TESTID,? AT+KTSD=TESTID,? AT+KTWD=TESTID,? AT+KTGT=TESTID,? AT+KTDR=TESTID,?
stop=`date +%s`
echo "smart程序执行时间$[ stop - start ]秒"
tar cvzf smart_log_$stop.tgz  ~/log
rm -rf ~/log/*
start=`date +%s`
./smart_all32 $addres $i $port 
stop=`date +%s`
echo "smart_all程序执行时间$[ stop - start ]秒"
tar cvzf smart_all_log_$stop.tgz  ~/log
rm -rf ~/log/*
i=$(($i + 1))
done
