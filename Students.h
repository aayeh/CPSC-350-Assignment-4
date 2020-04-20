#include <iostream>

using namespace std;

class Students {
    private:

    public:
        Students();
        Students(int t, int e);
        ~Students();

        int windowTime;
        int entryTime;
        int queueTime;
        int idleTime;
};
