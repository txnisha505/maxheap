#include <iostream>                     // Assignment Group 34
#include <vector>
#include <limits> // for std::numeric_limits
#include <unordered_set>
#include <algorithm> // for std::reverse



// structure to represent a print job
struct PrintJob {
    std::string name;
    int priority;

    PrintJob (std::string name, int priority)
    : name(std::move(name)), priority(priority) {}
};



// init an unordered set to ensure unique names and O(1) lookup time
// this set will be used to avoid duplicate print jobs
std::unordered_set<std::string> jobNames;



// function for restoring max-heap properties on a subtree rooted at i based on priority.
void heapify(std::vector<PrintJob> &jobs, int n, int parent)  {
    // start by assuming the parent has the highest priority
    int largest = parent;
    int left, right;

    // in a heap, children can be found at this index:
    left = 2 * parent + 1;
    right = 2 * parent + 2;

    // if left child is greater than parent, and also within bounds, it should also be the 'largest'
    if(left < n && jobs[left].priority > jobs[largest].priority)
        // update largest if true
        largest = left;

    // if right child is greater than parent, and within bounds
    if(right < n && jobs[right].priority > jobs[largest].priority)
        largest = right;

    // the largest should be at index i
    if(largest != parent){
        std::swap(jobs[largest], jobs[parent]);

        // recursively heapify the affected subtree to ensure subtree rooted at 'largest' is also a heap
        heapify(jobs, n, largest);
    }
}




// function to restore heap properties after inserting a new node
void heapifyInsertOperation(std::vector<PrintJob> &jobs, int i) {
    int parent = (i - 1) / 2;       // Note: a decimal gets rounded down if stored as an int

    // check if parent is not root node
    if(parent >= 0 && jobs[parent].priority < jobs[i].priority) {

        // if priority of parent is smaller than new node's priority, swap to restore heap properties
        std::swap(jobs[parent], jobs[i]);

        // recursively call the same operation to the new parent node.
        heapifyInsertOperation(jobs, parent);
    }
    // do nothing if parent has greater or equal priority than new node
}



// function to insert a node to max-heap
bool insertNode(std::vector<PrintJob> &jobs, const std::string &name, const int priority) {
    if (jobNames.find(name) != jobNames.end()) {
        std::cout << "Error: A job with the name \"" << name << "\" already exists." << std::endl;
        return false;
    }

    // insert new job at bottom of heap
    jobs.emplace_back(name, priority);
    jobNames.insert(name);

    // call function to restore heap properties, starting from newly inserted node at index = jobs.size() - 1
    heapifyInsertOperation(jobs, static_cast<int>(jobs.size() - 1));
    return true;
}



// function to process job with the highest priority, and restore heap properties afterward
void processHighestPriorityJob(std::vector<PrintJob> &jobs) {

    if (jobs.empty()) {
        std::cout << "No jobs to process." << std::endl;
        return;
    }
    // retrieve the highest-priority job
    PrintJob highestPriorityJob = jobs.front();
    std::cout << "Printing job: " << highestPriorityJob.name <<
    " (Priority: " << highestPriorityJob.priority << ")" << std::endl;

    // move last job in heap to root position, and delete highestPriorityJob from heap
    jobs[0] = jobs.back();

    // remove the old last job
    jobs.pop_back();

    // remove the name of highestPriorityJob, to make room to create a new job with identical name
    jobNames.erase(highestPriorityJob.name);

    // call heapify on root node to restore max-heap properties.
    heapify(jobs, static_cast<int>(jobs.size()), 0);
}



// function for editing an existing job's priority
void updateJobPriority(std::vector<PrintJob> &jobs, const std::string &name, int new_priority) {
    // set index to a position that I define as not found
    int index = -1;
    for (int i = 0; i < jobs.size(); i++) {
        if (jobs[i].name == name) {

            // if found, set index to position of job object to edit
            index = i;
            break;
        }
    }
    if (index == -1) {
        std::cout << "Error: No job found with name \"" << name << "\"." << std::endl;
        return;
    }

    int old_priority = jobs[index].priority;
    jobs[index].priority = new_priority;

    if (new_priority > old_priority) {
        heapifyInsertOperation(jobs, index);
    } else {
        heapify(jobs, static_cast<int>(jobs.size()), index);
    }
    std::cout << "Priority of \"" << name << "\" is updated to " << new_priority << "." << std::endl;
}


// function to perform heap sort on the jobs vector.
void heapSort(std::vector<PrintJob> &jobs, int n) {
    // loop from last element to first
    for(int i = n - 1; i >= 0; i--){
        // swap root node (largest element) with the current unsorted node.
        // root node is moved to the back of the list and considered sorted
        std::swap(jobs[i], jobs[0]);

        // call heapify to restore max-heap properties for the remaining unsorted nodes
        heapify(jobs, i, 0);
    }
}



// function to display jobs in priority order
void displayJobs(std::vector<PrintJob> &jobs) {
    if (jobs.empty()) {
        std::cout << "There are no jobs." << std::endl;
        return;
    }

    // since only root node is guaranteed to be sorted
    // we need to call heapSort to sort the other jobs as well
    heapSort(jobs, static_cast<int>(jobs.size()));

    // reverse the sorted jobs to display in descending order
    std::reverse(jobs.begin(), jobs.end());

    std::cout << "\nJobs in priority order (highest to lowest): " << std::endl;
    for(const auto &job : jobs) {
        std::cout << "Job name: " << job.name << ", Job priority: " << job.priority << std::endl;
    }
}



// helper function for getting valid integers
bool getValidInteger(int &number) {
    std::cin >> number;

    if (std::cin.fail()) {
        // remove error flag
        std::cin.clear();

        // clear input until encountering newline char
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}



void displayMenu() {
    std::cout << "\nPrint Job Scheduling System\n" << std::endl;
    std::cout << "Choose one of the options:" << std::endl;
    std::cout << "1. Insert print job" << std::endl;
    std::cout << "2. Display next print job (print job with highest priority)" << std::endl;
    std::cout << "3. Process next print job" << std::endl;
    std::cout << "4. Update print job priority" << std::endl;
    std::cout << "5. Display all print jobs" << std::endl;
    std::cout << "6. Exit program" << std::endl;
}



int main() {
    std::vector<PrintJob> jobs;
    int choice;

    do {
        displayMenu();
        std::cout << "Your choice: ";
        std::cin >> choice;

        // handle invalid input for choices
        if (std::cin.fail()) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice." << std::endl;
        }

        switch (choice) {
            case 1: {
                std::string name;
                int priority;

                std::cout << "Enter job name (only single words are allowed): ";

                // get name, and clear rest of input
                std::cin >> name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter job priority: ";

                // get a valid integer
                while (!getValidInteger(priority)) {
                    std::cout << "Invalid input. Please enter a valid integer for priority: ";
                }

                // try to insert node
                if (insertNode(jobs, name, priority)) {
                    std::cout << "Job \"" << name << "\" successfully added." << std::endl;

                    if (!jobs.empty()) {
                        // display next print job with highest priority
                        std::cout << "Highest priority: " << jobs.front().name <<
                                  " (Priority: " << jobs.front().priority << ")" << std::endl;
                    } else {
                        std::cout << "Print queue is now empty." << std::endl;
                    }
                }
                break;
            }
            case 2: {
                if (!jobs.empty()) {
                    std::cout << jobs.front().name
                              << " (Priority: " << jobs.front().priority << ")" << std::endl;
                } else {
                    std::cout << "No jobs in queue." << std::endl;
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

                std::cout << "Enter name of job you want to update: ";
                std::cin >> name;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter new priority: ";

                while (!getValidInteger(priority)) {
                    std::cout << "Invalid input. Please enter a valid integer for priority: ";
                }
                updateJobPriority(jobs, name, priority);

                // display the updated order of the print jobs after priority change
                displayJobs(jobs);

                break;
            }
            case 5: {
                displayJobs(jobs);
                break;
            }
            case 6: {
                std::cout << "Exiting program.." << std::endl;
                break;
            }
            default:
                std::cout << "Try choosing one of the options 1-6." << std::endl;
        }
    } while (choice != 6);

    return 0;
}