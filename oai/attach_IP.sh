#!/bin/bash

dhclient wwan0
ifconfig wwan0 netmask 255.255.255.0 -arp
route add -net 192.168.3.0/24 gw 192.168.20.1
