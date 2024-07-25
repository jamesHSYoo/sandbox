import urllib3
import json

http = urllib3.PoolManager()

data = json.dumps({'ip' : '127.0.0.1'})

url = 'http://localhost:8080/startup'

response = http.request(
    'POST' 
    ,url
    ,body=data
    ,headers={'Content-Type' : 'application/json'})

dic = json.loads(response.data)

print(dic)