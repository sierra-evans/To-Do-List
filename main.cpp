// Including these libraries allows the usage of input and output to the console, reading and writing to a file, vectors (which are dynamic arrays), and strings.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Including the std namespace here allows for simplified code throughout the program.
using namespace std;

// This is the file which will be read from and written to. It is a constant for simplification purposes and to avoid changes to it in the code.
const string FILE_NAME = "todo_list.txt";

// Task structure, which contains a string for the description of the task and a boolean, which tells if the task is completed or not.
struct Task
{
    string description;
    bool completed;
};

// Declares a vector called tasks that will hold all Task structures created by the user.
vector<Task> tasks;

// Function that loads tasks from the file.
void loadTasks()
{
    // Ifstream allows the program to read from a file.
    ifstream taskFile(FILE_NAME);

    // Checks to see if the file is open, and proceeds if it is.
    if (taskFile.is_open())
    {
        tasks.clear();                  // Clears the tasks vector to make way for what is loaded from the file.
        string description;             // Stores the description of the task.
        bool completed;                 // Stores whether the task is completed.

        // Read the file to see if there is a completed Boolean, and if there is, executes the code within.
        while (taskFile >> completed)
        {
            getline(taskFile, description);                 // Reads the rest of the line, which contains the description.
            tasks.push_back({description, completed});    // Adds the description and Boolean to the back of the vector.
        }
        taskFile.close();               // Closes the file.
    }
}

// Function that saves tasks to a file.
void saveTasks()
{
    // Ofstream allows the program to write to a file.
    ofstream taskFile(FILE_NAME);

    // Checks that the file is opened, and if it is, executes the following code.
    if (taskFile.is_open()) {
        for (const Task& task : tasks)
        {
            taskFile << task.completed << " " << task.description << endl;
        }
        taskFile.close();
    }
}

// Function that adds a task to the to-do list.
void addTask()
{
    cout << "Enter a new task: ";           // Prompts user to enter a new task.
    string task;
    getline(cin, task);               // Puts the user input into the task string.
    tasks.push_back({task, false});     // Pushes new task to tasks vector.
    saveTasks();                            // Saves tasks to the file.
    cout << "Task added successfully.\n";
}

// Function that removes a task from the to-do list.
void removeTask()
{
    if (tasks.empty())                  // If the tasks vector is empty, program will let the user know there are no tasks to remove.
    {
        cout << "No tasks to remove.\n";
        return;
    }

    cout << "Enter task number to remove (1-" << tasks.size() << "): ";     // Asks the user which task to remove from 1 to the size of the vector.
    int index;
    cin >> index;
    cin.ignore();       // Ignores white space.

    if (index < 1 || index > tasks.size())      // If input is outside of range, then error is displayed.
    {
        cout << "Invalid task number.\n";
        return;
    }
    tasks.erase(tasks.begin() + index - 1);     // Removes the task at the designated index.
    saveTasks();        // Saves tasks to the file.
    cout << "Task removed successfully.\n";
}

// Function that marks a task from the to-do list as complete.
void markTaskComplete()
{
    if (tasks.empty())      // Throws error if there are no tasks in the vector.
    {
        cout << "No tasks to mark as complete.\n";
        return;
    }

    cout << "Enter task number to mark as complete (1-" << tasks.size() << "): ";       // Asks user for the task to mark complete.
    int index;
    cin >> index;
    cin.ignore();       // Ignores white space.

    if (index < 1 || index > tasks.size())      // If input is outside of range, then error is displayed.
    {
        cout << "Invalid task number.\n";
        return;
    }
    tasks[index - 1].completed = true;      // Changes the completed Boolean to true in the designated task.
    saveTasks();        // Saves tasks to the file.
    cout << "Task marked as complete.\n";
}

// Function that displays the tasks in the to-do list.
void displayTasks()
{
    if (tasks.empty())      // If the tasks vector is empty, program will let the user know there are no tasks to display.
    {
        cout << "No tasks in the list.\n";
        return;
    }

    cout << "To-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i)       // For loop that iterates through the entire tasks vector.
    {
        // To the console, it prints the number of the task, then whether it is completed, then the description of the task.
        cout << i + 1 << ". [" << (tasks[i].completed ? "x" : " ") << "] " << tasks[i].description << endl;
    }
}

// Main function that runs the program.
int main()
{
    loadTasks();        // Loads tasks from the file.

    while (true)        // While loop that executes while the Boolean is true.
    {
        // Displays to the console a list of options for the user.
        cout << "\nTo-Do List Manager\n";
        cout << "1. View tasks\n";
        cout << "2. Add task\n";
        cout << "3. Remove task\n";
        cout << "4. Mark task as complete\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";

        int choice;     // Creates an integer which stores the user input.
        cin >> choice;
        cin.ignore();

        // Switch case that handles each number and calls the corresponding function.
        // If the user inputs '5', then the Boolean changed to false and the program ends.
        switch (choice)
        {
            case 1:
                displayTasks();
                break;
            case 2:
                addTask();
                break;
            case 3:
                removeTask();
                break;
            case 4:
                markTaskComplete();
                break;
            case 5:
                cout << "Thank you for using the program! Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
}
