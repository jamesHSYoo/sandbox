#!/bin/bash

ARR=($( cat ./ip_list.txt ))

for ip in "${ARR[@]}"; 
do
    curl -X POST -H "Content-Type: application/json" -d '{"ip":"localhost"}' http://$ip/startup
done
