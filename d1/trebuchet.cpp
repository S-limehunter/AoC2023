#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, int> schmable {
    {"one",1},
    {"two",2},
    {"three",3},
    {"four",4},
    {"five",5},
    {"six",6},
    {"seven",7},
    {"eight",8},
    {"nine",9},
};

int numExtract(std::string s){
    int first, twost;
    std::string sub;

    for (size_t i = 0; i<= s.size(); i++){
        if (isdigit(s[i])){
            first = (s[i]-'0');
            goto got1;
        } else {
            for (int j=3; j<6; j++){
                sub = s.substr(i, j);
                //std::cout<<sub<<' ';
                auto thing = schmable.find(sub);
                if (thing!=schmable.end()){
                    first = thing->second;
                    //std::cout<<"gotcha bitch"<<std::endl;
                    goto got1;
                }
            }
        }
    }
    got1:
    for (size_t i = s.size(); i>=0; i--){
        if (isdigit(s[i])){
            twost = (s[i]-'0');
            goto got2;
        } else {
            for (int j=3; j<6; j++){
                sub = s.substr(i, j);
                auto thing = schmable.find(sub);
                if (thing!=schmable.end()){
                    twost = thing->second;
                    goto got2;
                }
            }
        }
    }
    got2:
    return (first*10)+twost;
}

int main(){
    int solution = 0;
    std::ifstream in("d1input.txt");
    std::string spling;
    while (std::getline(in, spling)){
        std::cout<<numExtract(spling)<<std::endl;
        solution+=numExtract(spling);
    }

    std::cout<<solution<<std::endl;
    return 0;
}