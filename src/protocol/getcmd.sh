#!/bin/bash
str=`cat air-cleansing_msg.c | grep $1= `
if [ -n "$str" ]; then
 str=${str##*/}
 echo $str
fi
str=`cat air-condition_msg.c | grep $1= `
if [ -n "$str" ]; then
 str=${str##*/}
 echo $str
fi
str=`cat air-dehumidifier_msg.c | grep $1= `
if [ -n "$str" ]; then
 str=${str##*/}
 echo $str
fi
str=`cat air-exchang_msg.c | grep $1= `
if [ -n "$str" ]; then
 str=${str##*/}
 echo $str
fi
str=`cat message.c | grep $1= `
if [ -n "$str" ]; then
 str=${str##*/}
 echo $str
fi
str=`cat cmdanalysis.c | grep $1= `
if [ -n "$str" ]; then
 str=${str##*/}
 echo $str
fi