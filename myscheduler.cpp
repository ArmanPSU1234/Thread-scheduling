/*
 

 myscheduler.cpp
 Purpose: Thread-based schedulers for an n-processor architecture, n > 1, using the following scheduling policies:
 
    First Come, First Served (FCFS).
    Shortest Remaining Time First (SRTF), without preemption.
    SRTF, with preemption.
    Priority Based Scheduling (PBS), with preemption.
 
 @author: Arman Mannan, Fanzhou Wang
 @version: 03/03/2017
 
*/

//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"


myThread threadArray[5000];                 //Declearing space for an array to hold no more than 5000 arrays
myThread threadQ[5000];                     //Declearing space for an array to hold no more than 5000 arrays in queue
att td;                                     //Declearing global variable for threads from header threads

unsigned int cnt;
int q_head = 0, q_tail = 0;                 //Intialization

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
    //Function to Create Thread(s) and insert them in the student
    //defined data structure
    ThreadDescriptorBlock *newThread = new ThreadDescriptorBlock();
    
    //First approach: Assigning thread info for all new threads that comes into our array
    
    threadArray[td.num_td].tdb = newThread;
    threadArray[td.num_td].tdb->arriving_time = arriving_time;
    threadArray[td.num_td].tdb->remaining_time = remaining_time;
    threadArray[td.num_td].tdb->priority = priority;
    threadArray[td.num_td].tdb->tid = tid;
    threadArray[td.num_td].status = 1;
    td.num_td++;                            //For ever new thread that comes in
    
    //Debugging purposes
  //cout << "td.head = " << td.head << " td.num_td" << td.num_td << endl;
    
    //Second approach: Assigning thread info for all new threads that comes into our vector
    
    ThreadDescriptorBlock *newThread2 = new ThreadDescriptorBlock();
    
    newThread2->tid = tid;
    newThread2->remaining_time = remaining_time;
    newThread2->arriving_time = arriving_time;
    newThread2->priority = priority;
    
    vectorPoint.push_back(newThread2);      //Into the vecotr
    
}
 
//First approach: Sorting threads in our array by arriving times
void atSort(myThread *temp)
{
    int i, j, flag = 1;
    myThread swap[1];
    for (i = td.head; i < td.num_td; i++)
    {
        flag = 0;
        for (j = td.head; j < td.num_td - 1; j++)
        {
            if (temp[j + 1].tdb->arriving_time < temp[j].tdb->arriving_time)
            {
                swap[0].tdb = temp[j].tdb;
                swap[0].tdb->arriving_time = temp[j].tdb->arriving_time;
                swap[0].tdb->remaining_time = temp[j].tdb->remaining_time;
                swap[0].tdb->priority = temp[j].tdb->priority;
                swap[0].tdb->tid = temp[j].tdb->tid;
                swap[0].status = temp[j].status;
                
                temp[j].tdb = temp[j + 1].tdb;
                temp[j].tdb->arriving_time = temp[j + 1].tdb->arriving_time;
                temp[j].tdb->remaining_time = temp[j + 1].tdb->remaining_time;
                temp[j].tdb->priority = temp[j + 1].tdb->priority;
                temp[j].tdb->tid = temp[j + 1].tdb->tid;
                temp[j].status = temp[j + 1].status;
                
                temp[j+1].tdb = swap[0].tdb;
                temp[j + 1].tdb->arriving_time = swap[0].tdb->arriving_time;
                temp[j + 1].tdb->remaining_time = swap[0].tdb->remaining_time;
                temp[j + 1].tdb->priority = swap[0].tdb->priority;
                temp[j + 1].tdb->tid = swap[0].tdb->tid;
                temp[j + 1].status = swap[0].status;
                
                flag = 1;
            }
        }
    }
    return;
}

//First approach: Sorting threads in our array by remaing times
void rtSort(myThread *temp)
{
    int i, j, flag = 1;
    myThread swap[1];
    for (i = q_head; i < q_tail; i++)
    {
        flag = 0;
        for (j = q_head; j < q_tail - 1; j++)
        {
            if (temp[j + 1].tdb->remaining_time < temp[j].tdb->remaining_time)
            {
                swap[0].tdb = temp[j].tdb;
                swap[0].tdb->arriving_time = temp[j].tdb->arriving_time;
                swap[0].tdb->remaining_time = temp[j].tdb->remaining_time;
                swap[0].tdb->priority = temp[j].tdb->priority;
                swap[0].tdb->tid = temp[j].tdb->tid;
                swap[0].status = temp[j].status;
                
                temp[j].tdb = temp[j + 1].tdb;
                temp[j].tdb->arriving_time = temp[j + 1].tdb->arriving_time;
                temp[j].tdb->remaining_time = temp[j + 1].tdb->remaining_time;
                temp[j].tdb->priority = temp[j + 1].tdb->priority;
                temp[j].tdb->tid = temp[j + 1].tdb->tid;
                temp[j].status = temp[j + 1].status;
                
                temp[j + 1].tdb = swap[0].tdb;
                temp[j + 1].tdb->arriving_time = swap[0].tdb->arriving_time;
                temp[j + 1].tdb->remaining_time = swap[0].tdb->remaining_time;
                temp[j + 1].tdb->priority = swap[0].tdb->priority;
                temp[j + 1].tdb->tid = swap[0].tdb->tid;
                temp[j + 1].status = swap[0].status;
                
                flag = 1;
            }
        }
    }
    return;
}

//First approach: Inserting threads in our array into a queue for waiting to enter an CPU
void insertQ(myThread *Q, myThread *from, int i)
{
    Q[q_tail].tdb = from[i].tdb;
    Q[q_tail].tdb->arriving_time = from[i].tdb->arriving_time;
    Q[q_tail].tdb->remaining_time = from[i].tdb->remaining_time;
    Q[q_tail].tdb->priority = from[i].tdb->priority;
    Q[q_tail].tdb->tid = from[i].tdb->tid;
    from[i].tdb = NULL;
    q_tail++;
    rtSort(threadQ);
}

//First approach: Clear the array for new inputs
void clearQ(myThread *toClear)
{
    for (int i = 0; i < td.num_td; i++)
    {
        toClear[i].tdb = NULL;
    }
    td.head = 0;
    td.num_td = 0;
}

//Second approach: Sorting threads in our vectors by remaining times
void MyScheduler:: remaingTime()
{
    int i = 0;                                      //Local variable intialzation

    while(i < vectorPoint.size())                   //Going through all of the threads into our vector
    {
        int j = i - 1;                              //Local variable intialzation
        ThreadDescriptorBlock *pointer = vectorPoint.at(i);
        
        while (j >= 0 && pointer->remaining_time < vectorPoint.at(j)->remaining_time)       //Checking the remaning times of threads
        {
            vectorPoint.at(j+1) = vectorPoint.at(j);        //Sort
            j = j - 1;
        }
        vectorPoint.at(j +1) = pointer;
        
        i = i + 1;
    }
}

//Second approach: Sorting threads in our vectors by its prority
void MyScheduler:: prority()
{
    int i = 0;                                      //Local variable intialzation
    
    while(i < vectorPoint.size())                   //Going through all of the threads into our vector
    {
        int j = i - 1;                              //Local variable intialzation
        ThreadDescriptorBlock *pointer = vectorPoint.at(i);
        
        while ((j >= 0) && ((pointer->priority < vectorPoint.at(j)->priority)
               || (pointer->priority == vectorPoint.at(j)->priority))
               && (pointer->arriving_time < vectorPoint.at(j)->arriving_time))              //Checking the prority of threads
        {
            vectorPoint.at(j+1) = vectorPoint.at(j);        //Sort
            j = j - 1;
        }
        vectorPoint.at(j +1) = pointer;
        
        i = i + 1;
    }
}

//Second approach: Check to see any threads that are waiting to enter CPUs
int MyScheduler:: upcoming_thread()
{
    int i = 0;                                      //Local variable intialzation
    
    while(i < vectorPoint.size())
    {
        int threadExist = 0;                        //Local variable intialzation
        int j = 0;                                  //Local variable intialzation
        
        while(j < num_cpu && !threadExist)
        {
            if (CPUs[j] == vectorPoint.at(i))
            {
                threadExist = 1;
            }
            
            j = j + 1;
        }
        
        if (!threadExist && timer >= vectorPoint.at(i)->arriving_time)          //Check the time against the threads arriving times
        {
            return i;
        }
        
        i = i + 1;
    }
    return (-1);
}

//Second approach: Check to see any threads that are already in CPUs
bool MyScheduler:: CPU_Thread(ThreadDescriptorBlock *&CPU_thr)
{
    int thread_position = upcoming_thread();       //The next thread to come in
    
    if (thread_position != -1)
    {
        CPU_thr = vectorPoint.at(thread_position);
    }
    else
    {
        return 0;
    }
    
    return 1;
}

bool MyScheduler::Dispatch()
{
    int x = 0;                                      //Local variable intialzation
    
    while(x < vectorPoint.size())                   //Keep schdueling for all threads in our vector
    {
        if (vectorPoint.at(x)->remaining_time < 1)
        {
            vectorPoint.erase(vectorPoint.begin() + x);         //Deleting completed threads
        }
        
        x = x + 1;
    }
    
    if (vectorPoint.size() < 1)
    {
        return 0;
    }
    
    //Todo: Check and remove finished threads
    //Todo: Check if all the threads are finished; if so, return false
    switch(policy)
    {
        case FCFS:		//First Come First Serve

            atSort(threadArray);                                //Sort threads in our arrays by its ariving times
           
            cnt = 0;                                            //Local variable intialzation
            for (unsigned int i = 0; i < num_cpu; i++)          //For all threads in our array
            {
                if (CPUs[i] == NULL && threadArray[td.head].tdb != NULL)    //Insert the first coming thread
                {
                    if (threadArray[td.head].tdb->arriving_time <= timer)
                    {
                        CPUs[i] = threadArray[td.head].tdb;             //Insert into cpu
                        td.head++;                                      //Update
                    }
                }
            }
            for (int i = 0; i < td.num_td; i++)
            {
                if (threadArray[i].tdb->remaining_time == 0)
                {
                    threadArray[i].status = 0;
                    cnt++;                                              //Update position
                }
                else
                    cnt = 0;
            }
            if (cnt == td.num_td)
            {
                clearQ(threadArray);                                    //Clear the array for new inputs
                return false;
            }
            
            break;
        case STRFwoP:	//Shortest Time Remaining First, without preemption
            
            cnt = 0;
            for (int i = 0; i < td.num_td; i++)
            {
                if (threadArray[i].tdb != NULL)
                {
                    if (threadArray[i].tdb->arriving_time <= timer)
                    {
                        insertQ(threadQ, threadArray, i);
                    }
                }
            }
            for (unsigned int i = 0; i < num_cpu; i++)
            {
                if (CPUs[i] == NULL && threadQ[q_head].tdb != NULL)
                {
                    CPUs[i] = threadQ[q_head].tdb;                      //Taking threads from waiitng array
                    q_head++;                                           //Update position
                }
            }
            
            if (q_tail == td.num_td)
            {
                for (int i = 0; i < q_tail; i++)
                {
                    if (threadQ[i].tdb->remaining_time == 0)
                    {
                        cnt++;
                    }
                    else
                        cnt = 0;
                }
            }
            if (cnt == td.num_td)
            {
                clearQ(threadQ);                        //Clear the array for new inputs
                q_head = 0;                             //Intializing the local head to zero
                q_tail = 0;                             //Intializing the local tail to zero
                return false;
            }
            
            break;
        case STRFwP:	//Shortest Time Remaining First, with preemption
            
            remaingTime();              //Sorting threads by its remaing times
            
            break;
        case PBS:		//Priority Based Scheduling, with preemption
            
            prority();                  //Sorting threads by its prority
            
            break;
        default :
            cout<<"Invalid policy!";
            throw 0;
    }
    
    int threads = 1;                    //Local variable intialzation
    int j = 0;                          //Local variable intialzation
    
    while( j < num_cpu && threads)      //Keep doing it for all threads in our vector
    {
        if (policy == STRFwP)           //Schedule by its shortest time remaing with preemption
        {
            ThreadDescriptorBlock *position;        //Pointing to threads
            threads = CPU_Thread(position);
        
            if (threads)                            //For threads in CPU
            {
                if (CPUs[j] == NULL)
                {
                    threads = CPU_Thread(CPUs[j]);      //Schedule
                }
                else
                {
                    if (position->remaining_time < CPUs[j]->remaining_time)
                    {
                        threads = CPU_Thread(CPUs[j]);  //Schedule
                    }
                }
            }
        }
        else if (policy == PBS)         //Schedule by threads Priority with preemption
        {
            ThreadDescriptorBlock *position;        //Pointing to threads
            threads = CPU_Thread(position);
            
            if (threads)                             //For threads in CPU
            {
                if (CPUs[j] == NULL)
                {
                    threads = CPU_Thread(CPUs[j]);   //Schedule
                }
                else
                {
                    if (position->priority < CPUs[j]->priority)
                    {
                        threads = CPU_Thread(CPUs[j]);  //Schedule
                    }
                }
            }
        }
        
        j = j + 1;                      //Next threads to schedule
    }
    
    return true;
}