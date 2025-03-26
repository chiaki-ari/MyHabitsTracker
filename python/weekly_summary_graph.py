import os
import json
import matplotlib.pyplot as plt
import random


DATA_PATH = '../data/'
OUTPUT_PATH = '../data/'


def select_user_folder():
    folders = [f for f in os.listdir(DATA_PATH) if os.path.isdir(os.path.join(DATA_PATH, f))]
    print("Select a user folder:")
    for i, folder in enumerate(folders):
        print(f"{i + 1}. {folder}")
    choice = int(input("Enter the number of the folder: ")) - 1
    return folders[choice]


def generate_random_color():
    return "#%06x" % random.randint(0, 0xFFFFFF)


def load_data(folder_name):
    file_path = os.path.join(DATA_PATH, folder_name, 'weekly_summary.json')
    with open(file_path, 'r') as file:
        data = json.load(file)
    return data['weeks']


def plot_weekly_summary(weeks, folder_name):
    week_numbers = [week['weekNumber'] for week in weeks]
    total_counts = [week['totalCount'] for week in weeks]
    habit_names = list({habit['name'] for week in weeks for habit in week['habits']})
    habit_colors = {habit: generate_random_color() for habit in habit_names}

    plt.figure(figsize=(10, 6))
    plt.bar(week_numbers, total_counts, color='gray', alpha=0.7, label='Total Execution')

    for habit in habit_names:
        habit_counts = []
        for week in weeks:
            count = next((h['count'] for h in week['habits'] if h['name'] == habit), 0)
            habit_counts.append(count)
        plt.plot(week_numbers, habit_counts, marker='o', color=habit_colors[habit], label=habit)

    plt.title("Weekly Habit Summary")
    plt.xlabel("Week Number")
    plt.ylabel("Execution Count")
    plt.legend()

    output_file = os.path.join(OUTPUT_PATH, folder_name, 'weekly_summary.png')
    plt.savefig(output_file)
    print(f"Graph saved to {output_file}")
    plt.show()


if __name__ == "__main__":
    folder_name = select_user_folder()
    weeks = load_data(folder_name)
    plot_weekly_summary(weeks, folder_name)
