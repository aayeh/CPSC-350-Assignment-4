#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>
#include "Simulation.h"

using namespace std;

Simulation::Simulation() {
    type = 1;
    entryTime = 0;
    timeAtWindow = 0;

    NSECT = 0;
    MAEC = 0;
    IAEC = 0;

    totalWindows = 0;
    totalStudents = 0;

    windowArray = NULL;
    idleArray = NULL;
    medianArrary = NULL;
}

Simulation::~Simulation() {
    if (windowArray != NULL){
      delete[] windowArray;
    }
    if (idleArray != NULL){
      delete[] idleArray;

    }
    if (medianArrary != NULL){
      delete[] medianArrary;

    }
}

bool Simulation::importFile(string file) {
    string line;
    int lineNum = 1;

    ifstream inputStream;
    inputStream.open(file.c_str());

    try {
        getline(inputStream, line);
        totalWindows = atoi(line.c_str());

        windowArray = new Students*[totalWindows];

        for(int i = 0; i < totalWindows; ++i) {
            Students* student = new Students();
            windowArray[i] = student;
        }

        lineNum++;
    }
    catch(exception e) {
        cout << "ERROR" << endl;
        return false;
    }

    while(getline(inputStream, line)) {
        switch(type) {
            //Clock Ticks
            case(1): {
                try {
                    entryTime = atoi(line.c_str());
                    type++;
                    lineNum++;
                }
                catch(exception e) {
                    cout << "ERROR" << endl;
                    return false;
                }
                break;
            }
            //Number of Students
            case(2): {
                try {
                    if(line != "") {
                        NSECT = atoi(line.c_str());

                        for(int i = 0; i < NSECT; ++i) {
                            getline(inputStream, line);
                            lineNum++;

                            try {
                                timeAtWindow = atoi(line.c_str());
                            }
                            catch(exception e) {
                                cout << "ERROR" << endl;
                                return false;
                            }

                            totalStudents++;

                            Students* student = new Students(timeAtWindow, entryTime);

                            studentQueue.enqueue(student);
                        }
                        type--;
                    }
                }
                catch(exception e) {
                    cout << "ERROR" << endl;
                    return false;
                }

                break;
            }
            default:
                break;
        }
    }
    return true;
}

bool Simulation::timeTracker(int t) {
    for(int i = 0; i < totalWindows; ++i) {
        if(windowArray[i]->windowTime > 0) {
            //Decreases when Student at Window
            windowArray[i]->windowTime--;
        }
        else {
            //Increases when Student NOT at Window
            windowArray[i]->idleTime++;
        }
        cout << windowArray[i]->idleTime << endl;
    }

    if(!studentQueue.isEmpty()) {
        ListNode<Students*> *curr = studentQueue.front;

        while(curr != NULL) {
            if(curr->data->entryTime < t) {
                curr->data->queueTime += 1;
            }
            curr = curr->next;
        }
    }
    return true;
}

double Simulation::meanTime() {
    ListNode<int> *curr = waitStats.front;

    double mnWait = 0;
    double sum = 0;
    double counter = 0;

    while(curr != NULL) {
        sum += curr->data;
        curr = curr->next;
        counter++;
    }
    if(counter == 0) {
        return 0;
    }
    mnWait = sum / counter;
    return mnWait;
}

double Simulation::medianTime() {
    ListNode<int> *curr = waitStats.front;

    double medWait = 0;
    MAEC = 0;

    while(curr != NULL) {
        curr = curr->next;
        MAEC++;
    }

    if(MAEC == 0) {
        return 0;
    }
    else {
        medianArrary = new int[MAEC];
        curr = waitStats.front;

        for(int i = 0; i < MAEC; ++i) {
            medianArrary[i] = curr->data;
            curr = curr->next;
        }

        //Function from ALGORITHM Library - puts values into ASCENDING order
        sort(medianArrary, medianArrary + MAEC);
        //For one in Array
        if(MAEC == 1) {
            return medianArrary[0];
        }
        //For Odd Numbers
        else if(MAEC % 2 == 1) {
            double d = 0;
            int r = 0;

            r = (MAEC/2);
            d = medianArrary[r];

            return d;
        }
        else {
            double d = 0;
            int a = 0;
            int z = 0;

            a = MAEC/2;
            z = (MAEC/2) + 1;

            if(medianArrary[z] == 0) {
                return 0;
            }

            d = double(medianArrary[a])/double(medianArrary[z]);

            return d;
        }
    }
}

int Simulation::longestTime() {
    if(MAEC == 0) {
        return 0;
    }
    else {
        return medianArrary[MAEC - 1];
    }
}

int Simulation::overTenTime() {
    if(MAEC == 0) {
        return 0;
    }
    else {
        int temp = 0;

        for(int i = 0; i < MAEC; ++i) {
            if(medianArrary[i] > 10) {
                ++temp;
            }
        }
        return temp;
    }
}

double Simulation::meanIdleTime() {
    ListNode<int> *curr = idleStats.front;

    double mnIdle = 0;
    double sum = 0;
    double counter = 0;

    while(curr != NULL) {
        sum += curr->data;
        curr = curr->next;

        counter++;
    }

    if(counter == 0) {
        return 0;
    }

    mnIdle = sum / counter;
    return mnIdle;
}

int Simulation::longestIdleTime() {
    ListNode<int> *curr = idleStats.front;

    IAEC = 0;

    while(curr != NULL) {
        curr = curr->next;
        IAEC++;
    }

    idleArray = new int[IAEC];

    curr = idleStats.front;

    for(int i = 0; i < IAEC; ++i) {
        idleArray[i] = curr->data;
        curr = curr->next;
    }

    sort(idleArray, idleArray + IAEC);

    return(idleArray[IAEC - 1]);
}

int Simulation::idleOverFiveTime() {
    int temp = 0;

    for(int i = 0; i < IAEC; ++i) {
        if(idleArray[i] > 5) {
            ++temp;
        }
    }

    return temp;
}
