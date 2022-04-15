> git clone https://github.com/prometheus-operator/kube-prometheus.git

> cd kube-prometheus

> kubectl apply --server-side -f manifests/setup

> until kubectl get servicemonitors --all-namespaces ; do date; sleep 1; echo ""; done

> kubectl apply -f manifests/
