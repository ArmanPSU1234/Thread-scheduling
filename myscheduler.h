/*
 

 myscheduler.h
 Purpose: Contaning the definition of our own data structures and access to our objects
 
 @author: Arman Mannan, Fanzhou Wang
 @version: 03/03/2017
 
 */

#pragma once
//myschedule.h
/* Defining our data structure to contain
 and access objects from 'thread class'. The 'CreateThread()'
 function should insert the threads into the our defined
 data structure after creating them.
 */

#include "scheduler.h"
#include <vector>

////Define your data structure here.

struct myThread {
    ThreadDescriptorBlock *tdb;
    int status;
};

struct threadQ {
    ThreadDescriptorBlock *tdb;
};

struct att {
    int head = 0, num_td = 0;
};

class MyScheduler: public Scheduler {
public:
    
    std::vector<ThreadDescriptorBlock *> vectorPoint;                   //Setting vectors for all threads that comes in

    MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) { }
    
    bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
    void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure
    
    //Declare additional methods(s) below if needed.
    
//    void atSort(myThread *temp);
//    void rtSort(myThread *temp);
//    void insertQ(myThread *Q, myThread *from, int i);
//    void clearQ(myThread *toClear);
    
    int upcoming_thread();
    bool CPU_Thread(ThreadDescriptorBlock *&CPU_thr);
    void arrivalTime();
    void remaingTime();
    void prority();
    
};