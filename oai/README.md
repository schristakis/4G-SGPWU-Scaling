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
