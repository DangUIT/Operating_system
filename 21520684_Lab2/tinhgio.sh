#!/bin/sh

hour=$1
minute=$2
time=$3
file=$4

if [ $hour -ge 24 ];then
	echo "Gio khong hop le">$file
elif [ $minute -ge 60 ];then
	echo "Phut khong hop le">$file
elif [ $time -gt 480 ];then
	echo "Thoi gian lam viec khong hop le">$file
else
	sum_minute=$(($hour*60+$minute+$time))
	hour=$((($sum_minute/60)%24))
	minute=$(($sum_minute%60))
	echo "$hour $minute">$file
fi
exit 0	
