import csv
import numpy as np
import matplotlib.pyplot as plt


mean_p_times = []
std_p_times = []
mean_s_times = []
std_s_times = []
with open('success.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)

    for row in reader:
        if(row['Success_P'] != '0' or row['Success_S'] != '0'):
            print(row)
            raise ValueError("A failure in the successes!")

        mean_p_times.append(float(row["Avg_Time_P"]))
        std_p_times.append(float(row["Std_Time_P"]))
        mean_s_times.append(float(row["Avg_Time_S"]))
        std_s_times.append(float(row["Std_Time_S"]))

mean_p_times = np.array(mean_p_times)
std_p_times = np.array(std_p_times)
mean_s_times = np.array(mean_s_times)
std_s_times = np.array(std_s_times)

indices = [i for i in range(1, len(mean_p_times) + 1)]
plt.plot(indices, mean_p_times, label="Postfix")
plt.fill_between(
    indices,
    mean_p_times - std_p_times,
    mean_p_times + std_p_times,
    alpha=0.2
)
plt.plot(indices, mean_s_times, label="Syntax Tree")
plt.fill_between(
    indices,
    mean_s_times - std_s_times,
    mean_s_times + std_s_times,
    alpha=0.2
)
plt.ylabel("Running time (ns)")
plt.xlabel("# Operations")
plt.legend()
plt.tight_layout()
plt.show()
