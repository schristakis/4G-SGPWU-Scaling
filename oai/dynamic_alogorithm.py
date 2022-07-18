import time
import requests
import json
import os

limitA = 180
limitB = 220
limitC = 300
limitD = 430

url = "http://10.64.93.11:32468/api/v1/query?query=rate(container_network_receive_packets_total%7Bcontainer=%22POD%22,%20interface=%22net2%22,%20job=%22kubelet%22,%20pod=~%22oai-spgwu.*%22,namespace=%22oai%22%7D%5B1m%5D)"

while(1):
    resp = requests.get(url)
    data = resp.json()
    #value = float(data["data"]["result"][0]["value"][1])
    value = int(input())
    print(value)

    time.sleep(1)

    # 1 interface
    if (value < limitA):
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu2-devel.yaml")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu3-devel.yaml")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu4-devel.yaml")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu5-devel.yaml")

    # 2 interfaces
    elif (limitA < value < limitB):
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu2-devel.yaml --validate=false")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu3-devel.yaml")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu4-devel.yaml")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu5-devel.yaml")

    # 3 interfaces
    elif (limitB < value < limitC):
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu2-devel.yaml --validate=false")
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu3-devel.yaml --validate=false")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu4-devel.yaml")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu5-devel.yaml")

    # 4 interfaces
    elif (limitC < value < limitD):
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu2-devel.yaml --validate=false")
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu3-devel.yaml --validate=false")
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu4-devel.yaml --validate=false")
        os.system("kubectl delete -f oai-deployment-files/oai-spgwu5-devel.yaml")

    # 5 interfaces
    elif (value > limitD):
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu2-devel.yaml --validate=false")
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu3-devel.yaml --validate=false")
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu4-devel.yaml --validate=false")
        os.system("kubectl apply -f oai-deployment-files/oai-spgwu5-devel.yaml --validate=false")
