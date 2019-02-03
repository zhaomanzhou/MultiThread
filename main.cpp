#include <iostream>
#include <thread>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <mutex>
#include <condition_variable>
#include "Buffer.h"


using namespace std;

void PartWorker(int);

void ProductWorker(int );

void printArray(string s, int* arr);

Buffer b;

mutex m;

condition_variable data_cond;

int main()
{

    const int m = 8, n = 6; //m : number of Part Worker n: number of Product Workers

    thread partW[m];
    thread prodW[n];
    for (int i = 0; i < n; i++){
        partW[i] = thread(PartWorker, i);
        prodW[i] = thread(ProductWorker, i);
    }
    for (int i = n; i<m; i++) {
        partW[i] = thread(PartWorker, i);
    }
/* Join the threads to the main threads */
    for (int i = 0; i < n; i++) {
        partW[i].join();
        prodW[i].join();
    }
    for (int i = n; i<m; i++) {
        partW[i].join();
    }
    cout << "Finish!" << endl;
    getchar();
    getchar();

    return 0;

}


void PartWorker(int id)
{
    srand((unsigned) time(nullptr));
    for (int j = 0; j < 3; j++)
    {
        int placePart[4]{0};
        int remain[4]{0};
        int cnt = 4;
        while (cnt > 3)
        {
            cnt = 0;
            for (int i = 0; i < 4; i++)
                placePart[i] = 0;
            for (int i = 0; i < 4; i++)
            {
                int index = rand() % 4;
                if (placePart[index] == 0)
                    cnt++;
                placePart[index]++;
            }
        }
        bool success = false;


        while(!success)
        {
            unique_lock<mutex> lockGuard(m);
            if(b.removeTerminate() || !b.canAdd(placePart))
            {
                cout<<"Deadlock Detected\n"
                      "Aborted Iteration: "<<j<<endl<<endl;
                data_cond.notify_all();
                break;
            }
            cout << endl;
            cout << "Part Worker ID: " << id << endl;
            cout << "Iteration: " << j << endl;
            b.bufferState();
            printArray("Place Request: ", placePart);

            success = b.add(placePart, remain);
            cout << "Updated ";
            b.bufferState();
            printArray("Updated Place Request: ", remain);

            data_cond.notify_all();

            if (!success)
            {
                for(int i = 0; i < 4; i++)
                {
                    placePart[i] = remain[i];
                    remain[i] = 0;
                }
                data_cond.wait_for(lockGuard, std::chrono::milliseconds(30),[]
                { return !b.hasAdded(); });
            }
        }
    }
}




void ProductWorker(int id)
{
    srand((unsigned) time(nullptr));
    for(int j = 0; j < 3; j++)
    {
        int pickupPart[4]{0};
        int remain[4]{0};
        int cnt = 4;
        while (cnt != 3)
        {
            cnt = 0;
            for (int i = 0; i < 4; i++)
                pickupPart[i] = 0;
            for (int i = 0; i < 5; i++)
            {
                int index = rand() % 4;
                if (pickupPart[index] == 0)
                    cnt++;
                pickupPart[index]++;
            }
        }

        bool success = false;
        while(!success)
        {
            unique_lock<mutex> lockGuard(m);
            if(b.addTerminate() || !b.canRemove(pickupPart))
            {
                cout<<"Deadlock Detected\n"
                      "Aborted Iteration: "<<j<<endl;
                data_cond.notify_all();
                break;
            }
            cout << endl;
            cout << "Product Worker ID: " << id << endl;
            cout << "Iteration: " << j << endl;
            b.bufferState();
            printArray("Pickup Request: ", pickupPart);
            success = b.remove(pickupPart, remain);
            cout << "Updated ";
            b.bufferState();
            printArray("Updated Pickup Request: ", remain);


            data_cond.notify_all();


            if(!success)
            {
                for(int i = 0; i < 4; i++)
                {
                    pickupPart[i] = remain[i];
                    remain[i] = 0;
                }

                data_cond.wait_for(lockGuard, std::chrono::milliseconds(30) ,[]{ return b.hasAdded();});
            }
        }

    }

}




void printArray(string s, int* arr)
{
    cout<<s<<"(";
    for(int i = 0 ; i < 3; i++)
    {
        cout<<arr[i]<<",";
    }
    cout<<arr[3]<<")"<<endl;
}