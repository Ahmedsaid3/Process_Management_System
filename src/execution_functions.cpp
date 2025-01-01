#include "execution_functions.h"

#include <iostream> 
using namespace std;

void read_process_file(const char *filename, PROCESS_MANAGER *pm) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Inital processes file can not be opened!\n");
        return; 
    }

    int pid; 
    int priority;
    int isHead;

    initialize_process_manager(pm);

    PROCESS p; 
    PROCESS_QUEUE pq;
    initialize_process_queue(&pq);

    char line[50]; // buffer olarak kullandik 
    while (fgets(line, sizeof(line), file) != NULL) {
        
        if (sscanf(line, "%d, %d, %d", &pid, &priority, &isHead) == 3) {  // ilk satirda 0 donuyor sscanf function, o zaman girmiyor

            initialize_process(&p, pid, priority); 
            
            if (isHead == 1) { // process manager'a yollicam, dongunun basina donucem
                enqueue(&pq, p);

                pq.priority = priority; 

                // bu iki satir process queue'lari process manager'a yolluyor 
                if (priority == 1) insert_front(pm, pq);
                if (priority == 0) insert_rear(pm, pq);

                // process queue'yu 0 lamak icin: 
                initialize_process_queue(&pq);
                continue;
            } 

            enqueue(&pq, p);
        }

    }

    fclose(file);
    
}


void read_insertion_file(const char *filename, INSERTION_QUEUE *eq) {

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Arriving processes file can not be opened!\n");
        return; 
    }

    int iteration;
    int pid; 
    int priority;
    int isHead;

    initialize_execution_queue(eq);
    
    PROCESS p; 
    PROCESS_QUEUE pq;
    initialize_process_queue(&pq);

    char line[50]; // buffer olarak kullandik 
    while (fgets(line, sizeof(line), file) != NULL) {
        
        if (sscanf(line, "%d, %d, %d, %d", &iteration, &pid, &priority, &isHead) == 4) {  // ilk satirda 0 donuyor sscanf function, o zaman girmiyor

            initialize_process(&p, pid, priority); 
            
            if (isHead == 1) { // process manager'a yollicam, dongunun basina donucem
                enqueue(&pq, p);

                pq.priority = priority;
                pq.iteration = iteration;

                // bu satir process queue'lari iteration queue'ya yolluyor: 
                enqueue(eq, pq);

                // process queue'yu 0 lamak icin:   
                initialize_process_queue(&pq);
                continue;
            } 

            enqueue(&pq, p);
        }

    }

    fclose(file);

}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs) {

    initialize_failed_stack(fs);

    int counter = 0;
    int iter = 0; 

    while (pm->size != 0) { // process manager'da bir sey kalmayinca cik 

        PROCESS_QUEUE pq = delete_front(pm);
        
        
        for (int i = pq.front; i <= pq.rear; i++) {

             
            PROCESS tmp = peek(&pq);
            if (tmp.pid % 8 == 0) { // fail durumu:
                push(fs, pq);
                i = pq.rear + 1; // alt kisim bittikten sonra donguden ciksin
            } 

            // dequeue fonksiyonu ile pq'yu guncelliyorum:
            PROCESS p = dequeue(&pq); // p process'i sadece debug icin olusturuldu

            // debug icin:
            if (tmp.pid % 8 != 0) printf("Iter %d: %d is executed\n", iter, p.pid); 
            if (tmp.pid % 8 == 0) printf("Iter %d: %d is failed\n", iter, p.pid);


            // insertion queue kismi: 
            PROCESS_QUEUE pq2 = peek(eq); // insertion queue'daki bastaki process queue
            if (pq2.iteration == iter) {

                // process manager'a insert:
                if (pq2.priority == 1) insert_front(pm, pq2);
                if (pq2.priority == 0) insert_rear(pm, pq2);

                dequeue(eq); 
            }


            // debug icin: 
            cout << endl << "Process Manager Deque:" << endl; 
            for (int i = (pm->front + 1) % MAX_PROCESS, j = 0; j < pm->size; i = (i + 1) % MAX_PROCESS, j++) {
                PROCESS_QUEUE pq = pm->deque[i];
                for (int j = pq.front; j <= pq.rear; j++) {
                    cout << pq.queue[j].pid << " - ";
                }
                cout << endl;
            }


            cout << endl << "Insertion Queue:" << endl; 
            for (int i = eq->front; i <= eq->rear; i++) {
                PROCESS_QUEUE pq = eq->queue[i];
                for (int j = pq.front; j <= pq.rear; j++) {
                    cout << pq.queue[j].pid << " - ";
                }
                cout << endl;
            }
            cout << endl;


            cout << endl << "Failure Stack:" << endl; 
            for (int i = fs->top; i > -1; i--) {
                PROCESS_QUEUE pq = fs->stack[i];
                for (int j = pq.front; j <= pq.rear; j++) {
                    cout << pq.queue[j].pid << " - ";
                }
                cout << endl;
            }
            cout << "----------------" << endl;
            // debug sonu 


            iter++;
        }

    }

}