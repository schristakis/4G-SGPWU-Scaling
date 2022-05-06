> git clone https://github.com/prometheus-operator/kube-prometheus.git

> cd kube-prometheus

> kubectl apply --server-side -f manifests/setup

> kubectl apply -f manifests/

> kubectl edit svc grafana -n monitoring (change from Cluster IP to NodePort)

> dhclient eth1

> route add -net 10.64.44.0/23 gw 10.64.92.1
