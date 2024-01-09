#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int grabNum(const std::string& line, int index){
    int start=0; 
    int end;
    for (int i=index; i>0; i--){
        if (!isdigit(line[i-1])){
            start = i;
            break;
        }
    }
    for (int j=index; j<line.size(); j++){
        if (!isdigit(line[j])){
            end = j-start;
            break;
        }
    }

    return std::stoi(line.substr(start, end));
}

void partScan(std::vector<int> &nums, int line, int ch, const std::vector<std::string> &grid){
    for (int i = line-1; i<=line+1; i++){
        for(int j = ch-1; j<=ch+1; j++){
            if (isdigit(grid[i][j])){
                nums.push_back(grabNum(grid[i], j));
                if (isdigit(grid[i][j+1])){break;}
            }
        }
    }
}

void gearScan(std::vector<int> &nums, int line, int ch, const std::vector<std::string> &grid){
    int count=0;
    int num1, num2=0;
    for (int i = line-1; i<=line+1; i++){
        for(int j = ch-1; j<=ch+1; j++){
            if (isdigit(grid[i][j])){
                switch (count)
                {
                case 0:
                    num1=grabNum(grid[i], j);
                    break;
                case 1:
                    num2=grabNum(grid[i], j);
                    break;
                default:
                    return;
                }
                count++;
                if (isdigit(grid[i][j+1])){break;}
            }
        }
    }

    nums.push_back(num1*num2);
}

int partSums(const std::vector<std::string>& grid){
    std::vector<int> partNums;
    int ln = 0;
    for (std::string line: grid){
        for (int i=1; i<line.size(); i++){
            if (!(isdigit(line[i])||line[i]=='.')){
                partScan(partNums, ln, i, grid);
            }
        }
        ln++;
    }
    int sum = 0;
    for (int x: partNums){sum+=x;}
    return sum;
}

int gearSums(const std::vector<std::string>& grid){
    std::vector<int> gearRatios;
    int ln = 0;
    for (std::string line: grid){
        for (int i=1; i<line.size(); i++){
            if (line[i]=='*'){
                gearScan(gearRatios, ln, i, grid);
            }
        }
        ln++;
    }
    int sum = 0;
    for (int x: gearRatios){sum+=x;}
    return sum;
}

int main(){
    std::ifstream in("d3input.txt");
    std::string line = "";
    std::vector<std::string> full;
    while(in>>line){
        full.push_back(line);
    }
    std::cout<<gearSums(full)<<std::endl;


    in.close();
    return 0;
}