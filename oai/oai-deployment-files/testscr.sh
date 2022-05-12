#/bin/sh

echo starting;
IP=`nslookup 5g-control  | grep -v "#" | awk "/Address/ {print $2}"`;
echo ip is $IP;

