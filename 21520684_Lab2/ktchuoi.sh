#!/bin/sh

string=$1
folder=$2
file_result=$3
count=0

if [ -d $folder ];then
	for file in $(ls *);do
		if grep -q $string $file;then
			count=$(($count+1))
		fi
	done
	if [ $count = 0 ];then
		echo "Trong thu muc $folder khong co tap tin nao chua chuoi $string">$file_result
	else 
		echo "Trong thu muc $folder co $count tap tin chua chuoi $string">$file_result
	fi
else
	echo "Thu muc $folder khong ton tai">$file_result
fi

exit 0


