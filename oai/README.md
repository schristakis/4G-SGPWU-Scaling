http://10.64.93.11:32468/graph?g0.expr=rate(container_network_receive_packets_total%7Bcontainer%3D%22POD%22%2C%20interface%3D%22net2%22%2C%20job%3D%22kubelet%22%2C%20pod%3D~%22oai-spgwu.*%22%2Cnamespace%3D%22oai%22%7D%5B1m%5D)&g0.tab=1&g0.stacked=0&g0.show_exemplars=0&g0.range_input=1h

####### USRP ############

curl 10.1.0.67/usrpon


#### Internet Access for spgwu's ###
ip route del default

ip route add default via 10.244.2.1 dev eth0


#### Iperf ###
yum install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm

yum install iperf


#### Tcpdump ####
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/tcpdump-4.9.2-4.el7_7.1.x86_64.rpm

yum install tcpdump-4.9.2-4.el7_7.1.x86_64.rpm

rpm -ivh tcpdump-4.9.2-4.el7_7.1.x86_64.rpm

##### Grafana #####
Create -> New Dashboard -> add an empty panel -> prometheus -> paste the setence below

rate(container_network_receive_packets_total{container="POD", interface="net2", job="kubelet", pod=~"oai-spgwu.*",namespace="oai"}[1m])


http://10.64.93.11:30179/
