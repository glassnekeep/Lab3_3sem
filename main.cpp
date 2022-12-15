#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream file;
    file.open("C:\\Users\\-\\CLionProjects\\Lab3_3sem\\Entry");
    if (file.is_open()) {
        file << "4\n";
        file << "1\32Ivan32\32Petrov\n";
        file << "2\32Sergey\32Ivanov\n";
        file << "3\32Artem\32Kirillov\n";
        file << "4\32Alexander\32Matveev\n";
    }
    file.close();
    return 0;
}
