import requests

url = "https://icanhazdadjoke.com/search"

response = requests.get(
        url, 
        headers={"Accept": "application/json"},
        params={"term": "cat", "limit": 20})

data = response.json()
resultscount = len(data["results"])
#print(data["results"])
print(f"The amount of jokes with this cat is {resultscount}")
#print(data["joke"])
#print(f"status: {data['joke']}")
