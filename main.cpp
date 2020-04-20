#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;

int main(int argc, char** argv) {
    Simulation s;

    //If no file specified when running a.out
    if(argc < 2) {
        cout << "ERROR: Please Enter Valid File Input\n" << endl;

    }

    //If file is specified when running a.out
    else if(argc >= 2) {
        string file = argv[1];

        int currTime = 0;
        int openWindows = 0;

        bool running = true;

        //Run file import is valid
        if(s.importFile(file)) {
            while(running) {
                //If Student Queue is Empty
                if(s.studentQueue.isEmpty()) {
                    int temp = 0;

                    for(int i = 0; i < s.totalWindows; ++i) {
                        if((s.windowArray[i]->windowTime) < 1) {
                            temp++;
                        }
                    }
                    if(temp == s.totalWindows) {
                        running = false;
                    }
                }
                //Check for all Windows --> Moves Students to Window if Applicable
                for(int i = 0; i < s.totalWindows; ++i) {
                    if(s.windowArray[i]->windowTime < 1) {
                        if(!s.studentQueue.isEmpty()) {
                            Students* student = s.studentQueue.vFront();

                            if(student->entryTime <= currTime) {
                                if(s.windowArray[i]->idleTime > 0) {
                                    s.idleStats.enqueue(s.windowArray[i]->idleTime);
                                }
                                //Move from Queue to Window Array
                                s.windowArray[i] = s.studentQueue.dequeue();
                                s.waitStats.enqueue(s.windowArray[i]->queueTime);
                            }
                        }
                    }
                }
                //Time Tracker (per "tick") in the Simulation
                currTime++;
                s.timeTracker(currTime);
            }
            //Windows that are not filled during Simulation (remain idle entire time)
            for(int i = 0; i < s.totalWindows; ++i) {
                if(s.windowArray[i]->idleTime > 0) {
                    s.idleStats.enqueue(s.windowArray[i]->idleTime);
                }
            }

            //Data to be Printed
            cout << "\nMean Student Wait Time: " << s.meanTime() << endl;
            cout << "Median Student Wait Time: " << s.medianTime() << endl;
            cout << "Longest Student Wait Time: " << s.longestTime() << endl;
            cout << "Students Waiting Over Ten Minutes: " << s.overTenTime() << endl;
            cout << "Mean Window Idle Time: " << s.meanIdleTime() << endl;
            cout << "Longest Window Idle Time: " << s.longestIdleTime() << endl;
            cout << "Idle Time Over Five Minutes: " << s.idleOverFiveTime() << "\n" << endl;
        }
    }
    return 0;
}
