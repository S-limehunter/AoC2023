#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int score(std::string ticket){
    int hit=0;
    int bruh;
    while (ticket.substr(8)>>bruh){}
}

int main(){
    std::ifstream in("d4input.txt");
    std::string ln="";
    int sum=0;
    while (std::getline(in, ln)){
        sum+=score(ln);
    }

    in.close();
    return 0;
}