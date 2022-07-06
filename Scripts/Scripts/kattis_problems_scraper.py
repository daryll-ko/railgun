# Generates text for a Markdown file that contains checklists for each chapter of CP 4.

from collections import defaultdict
from bs4 import BeautifulSoup
import requests


def get_chapter_checklist(chapter: int) -> str:
    html_as_text = requests.get(
        f"https://cpbook.net/methodstosolve?oj=kattis&topic=ch{chapter}&quality=all"
    ).text
    soup = BeautifulSoup(html_as_text, "lxml")

    problems = soup.find_all("tr")[1:]
    problem_lists = defaultdict(list)

    for problem in problems:
        name, image, category, _, _, _ = problem.find_all("td")

        name = name.text
        section, title = category.text.split(", ", 1)
        link = image.a["href"]

        category = f"{section} • {title}"
        checklist_item = f"- [{name}]({link}) [[{name}]]"

        problem_lists[category].append(checklist_item)

    output = f"# Chapter {chapter} Problems\n"

    for category, problems in problem_lists.items():
        output += f"\n## {category}\n\n"
        for problem in problems:
            output += f"{problem}\n"

    output += '\n'

    return output


with open("output.txt", "a") as output_file:
    for chapter in range(1, 10):
        output_file.write(get_chapter_checklist(chapter))
