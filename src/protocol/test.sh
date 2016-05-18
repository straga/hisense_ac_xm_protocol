#!/bin/bash
export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
port=$1
i=1
addres=1
start=`date +%s`
echo "smart_${start}.log" >error.log
while [ -f runing ]
do
if [ $i -ge 4096 ]; then
i=1
fi
echo $i
rm -rf ~/log/*
start=`date +%s`
./smart 1 127.0.0.1 8787 4 1024 2048 $i 5 AT+KTZD=TESTID,?,1 AT+KTGN=TESTID,?,1 >smart_${start}.log
checklog=`cat smart_${start}.log`
if [ -z "${checklog}"];then
echo "smart_${start}.log" >>error.log
fi
stop=`date +%s`
tar cvzf smart_log_$stop.tgz  ~/log
rm -rf ~/log/*
start=`date +%s`
./smart_all 1 127.0.0.1 8787 4 1024 2048 $i 5  >smart_${start}.log
checklog=`cat smart_${start}.log`
if [ -z "${checklog}"];then
echo "smart_${start}.log" >>error.log
fi
stop=`date +%s`
tar cvzf smart_all_log_$stop.tgz  ~/log
rm -rf ~/log/*
i=$(($i + 1))
done
