#Purpose: Write our first web request

import requests

url = "http://www.google.com"

response = requests.get(url)

print(f"Your request to {url}")
