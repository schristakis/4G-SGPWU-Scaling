http://10.64.93.11:32468/api/v1/query?query=rate(container_network_receive_packets_total%7Bcontainer=%22POD%22,%20interface=%22net2%22,%20job=%22kubelet%22,%20pod=~%22oai-spgwu.*%22,namespace=%22oai%22%7D[1m])

####### USRP ############

curl 10.1.0.67/usrpon


#### Internet Access for spgwu's ###
ip route del default

ip route add default via 10.244.2.1 dev eth0

#### Tcpdump ####

yum install wget

wget http://mirror.centos.org/centos/7/os/x86_64/Packages/tcpdump-4.9.2-4.el7_7.1.x86_64.rpm

yum install tcpdump-4.9.2-4.el7_7.1.x86_64.rpm

#### Iperf ###
yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm

yum install iperf

##### Grafana #####
Create -> New Dashboard -> add an empty panel -> prometheus -> paste the setence below

rate(container_network_receive_packets_total{container="POD", interface="net2", job="kubelet", pod=~"oai-spgwu.*",namespace="oai"}[1m])


route add -host 10.84.3.38 gw 10.64.92.1 (where 10.84.3.38 the ip of host eth1)
http://10.64.93.11:30179/
