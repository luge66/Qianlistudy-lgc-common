#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

mutex mtx;
condition_variable cv_hydrogen, cv_carbon;
queue<char> hydrogenQueue, carbonQueue;
int hydrogen_count = 0;
int carbon_count = 0;

void releaseHydrogen()
{
    cout << "H";
}

void releaseCarbon()
{
    cout << "C";
}

void hydrogen()
{
    while (!hydrogenQueue.empty())
    {
        unique_lock<mutex> lock(mtx);
        cv_hydrogen.wait(lock, [] { return hydrogen_count < 4 && carbon_count == 1; });

        hydrogenQueue.pop();
        hydrogen_count++;
        releaseHydrogen();

        if(hydrogen_count == 4 && carbon_count == 1)
        {
            hydrogen_count = 0;
            carbon_count = 0;
            cv_carbon.notify_one();
        }
        else
        {
            cv_hydrogen.notify_one();
        }
    }
}

void carbon()
{
    while (!carbonQueue.empty()) {
        unique_lock<mutex> lock(mtx);
        cv_carbon.wait(lock, [] { return carbon_count == 0 && hydrogen_count < 4; });

        carbonQueue.pop();
        carbon_count++;
        releaseCarbon();

        if (hydrogen_count == 4 && carbon_count == 1)
        {
            hydrogen_count = 0;
            carbon_count = 0;
            cv_carbon.notify_one();
        }
        else
        {
            cv_hydrogen.notify_one();
        }
    }
}

void processInput(const string& input_sequence)
{
    for (char atom : input_sequence)
    {
        if
        (atom == 'H')
        {
            hydrogenQueue.push(atom);
        }
        else if(atom == 'C')
        {
            carbonQueue.push(atom);
        }
    }
}

int main()
{
    string input_sequence;
    cout << "请输入碳和氢的顺序: ";
    cin >> input_sequence;

    processInput(input_sequence);

    thread hydrogenThread(hydrogen);
    thread carbonThread(carbon);

    hydrogenThread.join();
    carbonThread.join();

    return 0;
}
