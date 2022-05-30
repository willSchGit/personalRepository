#include <time.h>
#include "jqueue.h"

int priorityFn1(const job_t &job);
int priorityFn2(const job_t &job);
using namespace std;

int priorityFn1(const job_t &job) {
    float pri;

    // 100 (regular user) + 100 (regular group) + job priority
    pri = 200 + job._priority;

    // If special user (7 or 23) add 200
    if (job._user == 7 || job._user == 23) pri += 200;

    // If special group (0 or 11) add 100
    if (job._group == 0 || job._group == 11) pri += 100;

    // Subtract weighted proc, mem, and time
    //   1.0 * proc, 0.01 * mem, (1/3600) * time
    pri = pri - job._proc - 0.01*job._mem - (1.0/3600.0)*job._time;

    return int(pri);
}

int priorityFn2(const job_t&job) {
    return int(job._time);
}

int main() {

    cout << "Large queue Testing: " << endl;

    JQueue skewBig(priorityFn2);
    srand (time(nullptr));

    for (int t = 0; t < 6000; t++) {
        job_t temp("jimboJob",rand() % 100+1,rand() % 100+1,5,rand() % 100+1,rand() % 2000 + 60,rand() % 30000 + 99);
        skewBig.insertJob(temp);
    }

    skewBig.printJobQueue();

    job_t job1("testA", 22, 6, 12,  151, 1000, 20);
    job_t job2("testB", 11, 12,  12, 60,  400, 200);
    job_t job3("testC", 2, 3,  5, 24, 100, 800);
    job_t job4("testD", 16, 4, 1,  19, 90, 202);
    job_t job5("testE", 2, 8, 5,  50, 700, 1);
    job_t job6("testF", 40, 10, 11,  111, 333, 5000);
    job_t job7("testG", 22, 17, 8,  15, 90, 555);
    job_t job8("testH", 7, 19, 14,  2, 999, 88);

    JQueue skew1(priorityFn1);
    JQueue skew2(priorityFn1);
    JQueue skew3(priorityFn1);
    JQueue skew4(priorityFn1);

    skew1.insertJob(job1);
    skew1.insertJob(job2);
    skew1.insertJob(job3);
    skew1.insertJob(job4);
    skew1.insertJob(job8);

    cout << "\nNumber of jobs in Skew 3: " << skew3.numJobs() << endl;

    skew3.insertJob(job4);
    skew3.insertJob(job5);
    skew3.insertJob(job6);
    skew3.insertJob(job7);
    skew3.insertJob(job1);

    cout << "\nTesting Skew 3" << endl;
    cout << "Number of jobs in Skew 3: " << skew3.numJobs() << endl;
    cout << "Dump and print: ";
    skew3.dump();
    skew3.printJobQueue();

    cout << "Empty merge test" << endl;
    skew2.mergeWithQueue(skew4);

    cout << "\nTesting Skew 2" << endl;
    cout << "Number of jobs in Skew 2: " << skew2.numJobs() << endl;
    cout << "Dump and print: ";
    skew2.dump();
    skew2.printJobQueue();

    cout << "Empty merge test with skew 1 and skew4" << endl;
    skew1.mergeWithQueue(skew4);

    cout << "\nTesting Skew 1" << endl;
    cout << "Number of jobs in Skew 1: " << skew1.numJobs() << endl;
    cout << "Dump and print: ";
    skew1.dump();
    skew1.printJobQueue();

    cout << "\nTesting Skew 4" << endl;
    cout << "Number of jobs in Skew 4: " << skew4.numJobs() << endl;
    cout << "Dump and print: ";
    skew4.dump();
    skew4.printJobQueue();

    //here
    cout << "Assignment testing skew 4 w/ deleting skew1" << endl;
    skew4 = skew1;

    cout << "Copy Constructor Testing skew 5 w/ deleting skew3" << endl;
    JQueue skew5(skew3);

    skew1.clear();
    skew3.clear();

    cout << "\nTesting Skew 4" << endl;
    cout << "Number of jobs in Skew 4: " << skew4.numJobs() << endl;
    cout << "Dump and print: ";
    skew4.dump();
    skew4.printJobQueue();

    cout << "\nTesting Skew 5" << endl;
    cout << "Number of jobs in Skew 2: " << skew5.numJobs() << endl;
    cout << "Dump and print: ";
    skew5.dump();
    skew5.printJobQueue();

    cout << "Self Assignment on Skew 4" << endl;
    skew4 = skew4;

    cout << "\nTesting Skew 4" << endl;
    cout << "Number of jobs in Skew 4: " << skew4.numJobs() << endl;
    cout << "Dump and print: ";
    skew4.dump();
    skew4.printJobQueue();

    cout << "Inserting job into skew 4" << endl;
    skew4.insertJob(job6);

    cout << "\nTesting Skew 4" << endl;
    cout << "Number of jobs in Skew 4: " << skew4.numJobs() << endl;
    cout << "Dump and print: ";
    skew4.dump();
    skew4.printJobQueue();

    cout << "Setting new prio function for skew 4" << endl;
    skew4.setPriorityFn(priorityFn2);

    cout << "\nTesting Skew 4" << endl;
    cout << "Number of jobs in Skew 4: " << skew4.numJobs() << endl;
    cout << "Dump and print: ";
    skew4.dump();
    skew4.printJobQueue();


    return 0;
}

