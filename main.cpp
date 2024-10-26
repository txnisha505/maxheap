#include <iostream>
#include <vector>

// structure to represent a print job
struct PrintJob {
    std::string name;
    int priority;

    PrintJob (const std::string &name, int priority)
    : name(name), priority(priority) {}
};

// function for turning a sub-array into a max-heap rooted at i based on priority.
void heapify(int arr[], int &n, int i) {
    int largest = i;
    int left, right;
    left = 2 * i + 1;
    right = 2 * i + 2;

    // if left child is greater than parent, and also within bounds, it should also be the 'largest'
    if(arr[largest] < arr[left] && left < n)
        // update largest if true
        largest = left;

    // if right child is greater than parent, and within bounds
    if(arr[largest] < arr[right] && right < n)
        largest = right;

    // the largest should be at index i in order to later move further up the heap
    if(largest != i){
        std::swap(arr[largest], arr[i]);

        // recursively call heapify on the affected subtree to ensure subtree rooted at 'largest' is also a heap
        heapify(arr, n, largest);
    }
}

// function for building a heap from an unsorted array
void buildHeap(int arr[],int &n) {
    // start loop from last non-leaf node, and move towards root
    for(int i = (n - 1) / 2; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// function to display heap
void displayHeap(int arr[], int &n) {
    for(int i=0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
}

// function to restore heap properties after node insertion
void heapifyInsertOperation(std::vector<PrintJob> &jobs, int i) {
    int parent = (i - 1) / 2;       // Note: a decimal gets rounded down if stored as an int

    // check if parent has other parents
    if(parent >= 0) {

        // if parent is smaller than current node, swap to restore heap properties
        if(arr[parent] < arr[i]) {
            std::swap(arr[parent], arr[i]);

            // recursively call the same operation to the new parent node
            heapifyInsertOperation(arr, parent);
        }
        // do nothing if parent is greater than current node
    }
}


void insertNode(std::vector<PrintJob> &jobs, const std::string name, const int priority) {

    // insert new job at bottom of heap
    jobs.push_back(PrintJob(name, priority));           // i struggle here

    // call function with parent of new node in order to move the new node to correct position
    heapifyInsertOperation(jobs, jobs.size() - 1);
}

void heapSort(int arr[], int &n){
    for(int i = n - 1; i >= 0; i--){
        std::swap(arr[i], arr[0]);
        heapify(arr, i, 0);
    }
}

void Interface() {
    std::cout << "This program prints the jobs in their own respective priority." << std::endl;
    std::cout << "You will be prompted to input a job. First, the name of the job, then corresponding priority." << std::endl;
    std::cout << "Priority should be a whole number, and the higher number, the higher priority." << std::endl;
    std::cout << "Some text here." << std::endl;
}

int main(){
    std::vector<PrintJob> PrintQueue;
    std::string job_name;
    int priority;
    char continueInput;

    Interface();

    do {
        std::cout << "Enter name of job: ";
        std::cin >> job_name;

        std::cout << "Enter priority of job: ";
        std::cin >> priority;

        if (std::cin.fail() || priority < 0) {
            throw std::invalid_argument("Priority cannot be a negative number.");
        }

        insertNode()
    }



    /*
    int arr[] = {19,79,54,8,45,4,6,7,8,100};
    int n = sizeof(arr)/sizeof(arr[0]);
    buildHeap(arr,n);
    displayHeap(arr,n);
    insertNode(arr,n,130);
    std::cout << "\nContent of the Max Heap after insertion"<< std::endl;
    displayHeap(arr,n);
    heapSort(arr,n);
    std::cout<<"\nContent of Heap sort"<< std::endl;
    displayHeap(arr,n);
    */
}
