cd multus-cni
cat ./deployments/multus-daemonset-thick-plugin.yml | kubectl apply -f -
cd ~
kubectl create namespace oai
kubectl create secret docker-registry regcred --docker-server=194.177.207.79 --docker-username=admin --docker-password=password
kubectl create secret docker-registry regcred --docker-server=194.177.207.79 --docker-username=admin --docker-password=password -n oai
#git clone https://repo.nitlab.inf.uth.gr/oai-k8s/oai-deployment-files.git
kubectl label nodes soc-master usb=usrp
kubectl label nodes soc-worker1 usb=usrp
kubectl label nodes soc-worker2 usb=usrp
kubectl label nodes soc-worker3 usb=usrp
cd ~/oai-deployment-files
kubectl apply -f cassandra.yaml --validate=false
sleep 30
kubectl apply -f oai-hss-devel.yaml --validate=false
sleep 30
kubectl apply -f oai-mme-devel.yaml --validate=false
sleep 30
kubectl apply -f oai-spgwc-devel.yaml --validate=false
sleep 30
kubectl apply -f oai-spgwu-devel.yaml --validate=false
sleep 30
kubectl apply -f oai-enb-devel.yaml --validate=false
sleep 20
kubectl get pods -n oai

git clone https://github.com/prometheus-operator/kube-prometheus.git
cd kube-prometheus
git checkout release-0.9
kubectl apply --server-side -f manifests/setup
kubectl apply -f manifests/
kubectl patch svc grafana --type='json' -p '[{"op":"replace","path":"/spec/type","value":"NodePort"}]' -n monitoring
kubectl patch svc grafana --type='json' -p '[{"op":"replace","path":"/spec/ports/0/nodePort","value":30179}]' -n monitoring
dhclient eth1
route add -net 10.64.44.0/23 gw 10.64.92.1
ip4=$(/sbin/ip -o -4 addr list eth1 | awk '{print $4}' | cut -d/ -f1)
VAR2=":30179"
VAR3="Grafana on port -> "
VAR4="$VAR3$ip4$VAR2"
echo $VAR4
sleep 20
