#Purpose: Output Dad Jokes using API from icanhazdadjoke.com

import requests
from random import choice
import pyfiglet
from termcolor import colored

header = pyfiglet.figlet_format("DAD JOKE 3000!")
header = colored(header, color="magenta")
print(header)

search_term = input("Let me tell you a joke! Give me a topic: ")
url = "https://icanhazdadjoke.com/search"
response = requests.get(
        url, 
        headers={"Accept": "application/json"},
        params={"term": search_term})

data = response.json()
results_count = data["total_jokes"]

if results_count == 0:
    print(f"Sorry, I don't have any joke about {search_term}. Please try again.")
elif results_count == 1:
    print(f"I've got one joke about {search_term}. Here it is: ")
    print(choice(data["results"])["joke"])
else:
    print(f"I've got {results_count} jokes about {search_term}. Here's one: ")
    print(choice(data["results"])["joke"])

#print(data["results"])
#print(f"The amount of jokes with this cat is {resultscount}")
#print(data["joke"])
#print(f"status: {data['joke']}")
