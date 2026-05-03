import json
import matplotlib.pyplot as plt


def parse_name(name):
    parts = name.split("/")
    vertices = int(parts[1].split(":")[1])
    edges = int(parts[2].split(":")[1])
    return vertices, edges


with open("benchmark.json", "r", encoding="utf-8") as file:
    data = json.load(file)

vertices_values = []
time_values_ms = []

for item in data["benchmarks"]:
    vertices, edges = parse_name(item["name"])
    cpu_time_ms = item["cpu_time"] / 1000000

    vertices_values.append(vertices)
    time_values_ms.append(cpu_time_ms)

    print(f"V = {vertices}, E = {edges}, time = {cpu_time_ms:.4f} ms")

plt.figure(figsize=(9, 5))
plt.plot(vertices_values, time_values_ms, marker="o")
plt.title("Время работы Дейкстры")
plt.xlabel("Кол-во вершин")
plt.ylabel("Время, мс")
plt.grid(True)
plt.tight_layout()
plt.show()
