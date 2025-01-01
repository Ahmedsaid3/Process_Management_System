#include <iostream>
using namespace std; 
#include "execution_functions.h" // sadece bunu almak yeterli, tum headerlar gelmis oluyor zaten, ic ice 

int main() {

    // * Process Queue denemelerim 
    // PROCESS_QUEUE pq;
    // initialize_process_queue(&pq);
    // PROCESS data;
    // initialize_process(&data, 120, 1);
    // enqueue(&pq, data);
    // cout << dequeue(&pq).pid << endl;
    // cout << isFull(&pq) << endl;
    // cout << isEmpty(&pq) << endl;


    // * Process Manager dogru olustu mu kontrol ettim
    PROCESS_MANAGER pm; 
    read_process_file("/workspaces/hw2/initial_processes.txt", &pm); 
    // cout << endl << "Process Manager Deque:" << endl; 
    // for (int i = pm.front + 1; i < pm.rear ; i++) {
    //     PROCESS_QUEUE pq = pm.deque[i];
    //     for (int j = pq.front; j <= pq.rear; j++) {
    //         cout << pq.queue[j].pid << " - ";
    //     }
    //     cout << endl;
    // }

    // * Insertion Queue dogru olustu mu kontrol ettim 
    INSERTION_QUEUE eq; 
    read_insertion_file("/workspaces/hw2/arriving_processes.txt", &eq);
    // cout << endl << "Insertion Queue:" << endl; 
    // for (int i = eq.front; i <= eq.rear; i++) {
    //     PROCESS_QUEUE pq = eq.queue[i];
    //     for (int j = pq.front; j <= pq.rear; j++) {
    //         cout << pq.queue[j].pid << " - ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // * Failure stack dogru olustu mu kontrol ettim 
    FAILURE_STACK fs;
    execution_loop(&pm, &eq, &fs);
    // cout << endl << "Failure Stack:" << endl; 
    // for (int i = fs.top; i > -1; i--) {
    //     PROCESS_QUEUE pq = fs.stack[i];
    //     for (int j = pq.front; j <= pq.rear; j++) {
    //         cout << pq.queue[j].pid << " - ";
    //     }
    //     cout << endl;
    // }
    

    return 0;
}