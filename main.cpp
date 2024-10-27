#include <iostream>
#include <vector>
#include <limits> // for std::numeric_limits: provides information about properties of a data type



// structure to represent a print job
struct PrintJob {
    std::string name;
    int priority;

    PrintJob (std::string name, int priority)
    : name(std::move(name)), priority(priority) {}
};


// function for restoring max-heap properties on a subtree rooted at i based on priority.
void heapify(std::vector<PrintJob> &jobs, int &n, int parent)  {
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
}           // QQQ should int n/&n


// function for building a heap from an unsorted vector of PrintJob objects
void buildHeap(std::vector<PrintJob> &jobs, int &n) {

    // start loop from last non-leaf node, and move towards root
    for(int i = (n - 1) / 2; i >= 0; i--) {
        heapify(jobs, n, i);
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




bool insertNode(std::vector<PrintJob> &jobs, const std::string &name, const int priority) {

    // insert new job at bottom of heap
    jobs.emplace_back(name, priority);
    jobNames.emplace_back(name)

    // call function to restore heap properties, starting from newly inserted node at index = jobs.size() - 1
    heapifyInsertOperation(jobs, static_cast<int>(jobs.size() - 1));
}


void processHighestPriorityJob(std::vector<PrintJob> &jobs) {
    if (jobs.empty()) {
        std::cout << "No jobs to process." << std::endl;
        return;
    }

    PrintJob highestPriorityJob = jobs.front();
    std::cout << "Processing job: " << highestPriorityJob.name << "Priority: " << highestPriorityJob.priority << std::endl;
}




// function to display jobs
void displayJobs(std::vector<PrintJob> &jobs) {
    if (jobs.empty()) {
        std::cout << "There are no jobs." << std::endl;
        return;
    }
    std::cout << "Current jobs: " << std::endl;
    for(const auto &job : jobs) {
        std::cout << "Job name: " << job.name << ", Job priority: " << job.priority << std::endl;
    }
}



void heapSort(std::vector<PrintJob> &jobs, int &n) {
    for(int i = n - 1; i >= 0; i--){
        std::swap(jobs[i], jobs[0]);
        heapify(jobs, i, 0);
    }
}




void displayMenu() {
    std::cout << "This program prints the jobs in their own respective priority." << std::endl;
    std::cout << "You will be prompted to input a job. First, the name of the job, then corresponding priority." << std::endl;
    std::cout << "Priority should be a whole number, and the higher number, the higher priority." << std::endl;
    std::cout << "Some text here." << std::endl;
}



int main(){
    std::vector<PrintJob> jobs;
    std::unordered_set<std::string> jobNames; // why an unordered set
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string name;
                int priority;

                std::cout << "Enter job name: ";
                std::getline(std::cin, name);

                std::cout << "Enter job priority: ";
                std::cin >> priority;
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (insertNode(jobs, name, priority))

            }
        }
    }


    return 0;
}
