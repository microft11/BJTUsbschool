void Swait(S1, S2,..., S3) {
    while (true)
    {
        if (S1 >= 1 && ... && S3 >= 1)
        {
            for (i = 1; i <= n; i ++) Si --;
            break；
        }
        else {
            place the process in the waiting queue asscoated with the first Si found with
        Si < 1, and set the program count of this process to begging of Swait operation
        }
        
    }
    
}

void Ssignal(S1, S2,..., S3) {
    while (TRUE) {
        for (i = 1; i <= n; i ++) {
            Si ++;
            remove all the process waiting in the queue associated with Si into the ready queue
        }
    }

}


struct Semaphore {
    int value; 
    QueueType queue; 
};


void initSemaphores(Semaphore *S1, Semaphore *S2, ..., Semaphore *S3) {
    S1->value = 0;
    S2->value = 0;
   


void Swait(Semaphore *S1, Semaphore *S2, ..., Semaphore *S3) {
    while (true) {
        if (S1->value >= 1 && S2->value >= 1 && ... && S3->value >= 1) {
            for (int i = 1; i <= n; i++) {
                S1->value--;
                S2->value--;
                
            }
            break; 
        } else {
            
            Semaphore *waitingSemaphore = findFirstSemaphore(S1, S2, ..., S3);
                   
            enqueue(waitingSemaphore->queue, getCurrentProcess());
                        
            setProgramCounter(getCurrentProcess(), Swait);
        }
    }
}


void Ssignal(Semaphore *S1, Semaphore *S2, ..., Semaphore *S3) {
    while (true) {
        for (int i = 1; i <= n; i++) {
            S1->value++;
            S2->value++;
            
            while (!isEmpty(S1->queue)) {
                Process *waitingProcess = dequeue(S1->queue);
                enqueue(readyQueue, waitingProcess);
            }
        }
    }
}
