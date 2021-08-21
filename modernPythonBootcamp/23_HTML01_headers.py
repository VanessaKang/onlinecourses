import requests
url = "https://icanhazdadjoke.com/"

response = requests.get(url, headers={"Accept": "application/json"})
#response = requests.get(url, headers ={"Accept": "text/plain"})
data = response.json()
print(data["joke"])

