//
//  main.cpp
//  Multithread
//
//
//


#include <iostream>
#include <thread>
#include <mutex>

class MyThread {

    private:
        std::thread workerThread;
        std::mutex mtx;
        bool stopFlag = false;

        void run() {
            while (true) {
                std::unique_lock<std::mutex> lock(mtx);
                if (stopFlag) {
                    break; // Exit the loop if stop is requested
                }
                lock.unlock(); // Release lock before performing work

                // Simulate work
                std::cout << "Thread is working..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
            std::cout << "Thread stopped." << std::endl;
        }

    public:
        void start() {
            std::lock_guard<std::mutex> lock(mtx);
            stopFlag = false;
            workerThread = std::thread(&MyThread::run, this);
            std::cout << "Thread started." << std::endl;
        }

        void stop() {
            std::unique_lock<std::mutex> lock(mtx);
            stopFlag = true; // Request the thread to stop
            lock.unlock(); // Release lock to allow thread to check flag

            if (workerThread.joinable()) {
                workerThread.join(); // Wait for the thread to finish
            }
            std::cout << "Stop method completed." << std::endl;
        }
};

int main(int argc, const char * argv[]) {
    
 MyThread t;
 t.start();

 // Let the thread run for a few seconds
 std::this_thread::sleep_for(std::chrono::seconds(3));

 t.stop(); // Request the thread to stop and wait for it

 return EXIT_SUCCESS;
}

