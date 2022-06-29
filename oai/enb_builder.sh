cd openairinterface5g
source oaienv
cd cmake_targets/
./build_oai -I -w USRP --eNB 
cd ../targets/bin
container_id=$(sudo docker ps | grep k8s_enb | awk {'print $1'})
str=":/opt/oai-enb/bin/."
sudo docker cp lte-softmodem.Rel14 $container_id$str
sudo docker exec -ti $container_id bash -c 'pid_to_kill=$(ps aux | grep SLl | grep softmodem);set -- $pid_to_kill;echo $2; sleep 2; kill -9 $2; /opt/oai-enb/bin/lte-softmodem.Rel14 -O /opt/oai-enb/etc/enb-monolithic.conf'
