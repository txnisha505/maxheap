#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <limits>



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
