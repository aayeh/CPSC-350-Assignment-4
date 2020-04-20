#include <iostream>
#include <string>
#include "Students.h"
#include "GenQueue.h"

using namespace std;

class Simulation {
    private:
        int type; //Imported File Line Type (Student/Time/Clock)
        int entryTime;
        int timeAtWindow;
        int NSECT; //Number of Students at Each Clock Tick
        int MAEC; //Median Array Element Count
        int IAEC; //Idle Array Element Count

    public:
        //Constructor
        Simulation();
        //Destructor
        ~Simulation();

        //Read File
        bool importFile(string file);

        //Keep Track of Global Time
        bool timeTracker(int t);

        //Mathematical Operations for Students
        double meanTime();
        double medianTime();
        int longestTime();
        int overTenTime();
        //Mathematical Operations for Window/Registrar
        double meanIdleTime();
        int longestIdleTime();
        int idleOverFiveTime();

        //Set Arrays
        //Students at Window
        Students* *windowArray;
        //Student Queue
        GenQueue<Students*> studentQueue;

        GenQueue<int> waitStats;
        GenQueue<int> idleStats;

        int *medianArrary;
        int *idleArray;

        int totalWindows;
        int totalStudents;
};
