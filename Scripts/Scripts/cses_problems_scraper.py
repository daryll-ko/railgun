# Generates text for a Markdown file that contains checklists for each category of the CSES problemset.

from bs4 import BeautifulSoup
import requests

html_as_text = requests.get("https://cses.fi/problemset/").text
soup = BeautifulSoup(html_as_text, "lxml")

categories = soup.find_all("h2")[1:]
problem_lists = soup.find_all("ul", {"class": "task-list"})[1:]

output = "# CSES Problems\n"

for category, problem_list in zip(categories, problem_lists):
    category = category.text
    output += f"\n## {category}\n\n"

    problems = problem_list.find_all("li")

    for problem in problems:
        name, link = problem.a.text, problem.a["href"]
        output += f"- [{name}](https://cses.fi{link}) [[{name}]]\n"

print(output)
