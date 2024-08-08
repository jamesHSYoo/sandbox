#!/bin/bash

ips=("127.0.0.1:8080" "127.0.0.1:8080" "127.0.0.1:8080")

for ip in "${ips[@]}"; 
do
    curl -X POST -H "Content-Type: application/json" -d '{"ip":"localhost"}' http://$ip/startup
done
