#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <limits>



std::unordered_set<std::string> jobNames;



bool insertNode(std::vector<PrintJob>& jobs, const std::string& name, const int priority) {
    if (jobNames.find(name) != jobNames.end()) {
        std::cout << "Error: A job with the name \"" << name << "\" already exists." << std::endl;
        return false;
    }

    jobs.emplace_back(name, priority);
    jobNames.insert(name);
    heapifyInsertOperation(jobs, static_cast<int>(jobs.size() - 1));
    return true;
}




void processHighestPriorityJob(std::vector<PrintJob>& jobs) {
    if (jobs.empty()) {
        std::cout << "No jobs to process." << std::endl;
        return;
    }

    PrintJob highestPriorityJob = jobs.front();
    std::cout << "Processing job: " << highestPriorityJob.name << " (Priority: " << highestPriorityJob.priority << ")" << std::endl;

    jobs[0] = jobs.back();
    jobs.pop_back();
    jobNames.erase(highestPriorityJob.name);

    heapify(jobs, jobs.size(), 0);
}

void updateJobPriority(std::vector<PrintJob>& jobs, const std::string& name, int newPriority) {
    int index = -1;
    for (int i = 0; i < jobs.size(); ++i) {
        if (jobs[i].name == name) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cout << "Error: No job found with the name \"" << name << "\"." << std::endl;
        return;
    }

    int oldPriority = jobs[index].priority;
    jobs[index].priority = newPriority;

    if (newPriority > oldPriority) {
        heapifyInsertOperation(jobs, index);
    } else {
        heapify(jobs, jobs.size(), index);
    }
    std::cout << "Priority of job \"" << name << "\" updated to " << newPriority << "." << std::endl;
}

void displayMenu() {
    std::cout << "\nPrint Job Scheduler Menu:\n";
    std::cout << "1. Insert Print Job\n";
    std::cout << "2. Display Next Print Job\n";
    std::cout << "3. Process Next Print Job\n";
    std::cout << "4. Update Print Job Priority\n";
    std::cout << "5. Display All Print Jobs\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::vector<PrintJob> jobs;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string name;
                int priority;
                std::cout << "Enter job name: ";
                std::getline(std::cin, name);
                std::cout << "Enter job priority: ";
                std::cin >> priority;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (insertNode(jobs, name, priority)) {
                    std::cout << "Job \"" << name << "\" added successfully.\n";
                    if (!jobs.empty()) {
                        std::cout << "Next job to process: " << jobs.front().name << " (Priority: " << jobs.front().priority << ")\n";
                    }
                }
                break;
            }
            case 2: {
                if (!jobs.empty()) {
                    std::cout << "Next job to process: " << jobs.front().name << " (Priority: " << jobs.front().priority << ")\n";
                } else {
                    std::cout << "No jobs in the queue.\n";
                }
                break;
            }
            case 3: {
                processHighestPriorityJob(jobs);
                break;
            }
            case 4: {
                std::string name;
                int priority;
                std::cout << "Enter job name to update: ";
                std::getline(std::cin, name);
                std::cout << "Enter new priority: ";
                std::cin >> priority;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                updateJobPriority(jobs, name, priority);
                break;
            }
            case 5: {
                displayJobs(jobs);
                break;
            }
            case 6:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
