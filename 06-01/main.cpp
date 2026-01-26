#include <iostream>
#include <thread>
#include <mutex>

std::mutex g_coutMutex;

void PrintLine(const char* s) {
    std::lock_guard<std::mutex> lock(g_coutMutex);
    std::cout << s << '\n';
}

void Thread3() {
    PrintLine("    thread3");
}

void Thread2() {
    PrintLine("  thread2");

    std::thread t3(Thread3);
    t3.join(); // thread3 を必ず thread2 の後に出す
}

void Thread1() {
    PrintLine("thread1");

    std::thread t2(Thread2);
    t2.join(); // thread2 を必ず thread1 の後に出す
}

int main() {
    std::thread t1(Thread1);
    t1.join(); // thread1 を必ず main の終了前に完了させる
    return 0;
}
