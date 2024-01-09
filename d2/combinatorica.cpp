#include <fstream>
#include <vector>
#include <string>
#include <iostream>

struct gameRound {
    int r, g, b;
    int power(){return r*g*b;}
};

struct game{
    int gameno;
    std::vector<gameRound> rounds;
};

gameRound getRound(std::string rstring){
    gameRound out = {0,0,0};
    int bp=0;
    for (int i=0; i<=rstring.size(); i++){
        if (!(rstring[i]==','||i==rstring.size())){continue;}
        int num = std::stoi(rstring.substr(bp, i-bp));
        switch (rstring[i-1]){
            case 'e':{out.b=num; break;}
            case 'n':{out.g=num; break;}
            case 'd':{out.r=num; break;}
        }
        bp=i+1;
    }

    return out;
}

game* getGame(std::string line){
    game* gameOut = new game;
    std::string ident;
    std::vector<std::string> roundstrings;
    int bp=0;
    for (int i = 0; i<=line.size(); i++){
        if (line[i]==':'){
            ident = line.substr(bp+4, i-bp); //BEWARE: magic number 4 makes it so stoi doesn't scream at me later
            bp=i+2;
        } else if (line[i]==';' || i==line.size()){
            roundstrings.push_back(line.substr(bp, i-bp));
            bp=i+2;
        }
    }

    gameOut->gameno = std::stoi(ident);
    for (std::string rs: roundstrings){
        gameOut->rounds.push_back(getRound(rs));
    }


    return gameOut;
}

bool possibleGame(game* g, gameRound max){
    for (gameRound r: g->rounds){
        if (r.r>max.r||r.g>max.g||r.b>max.b){return false;}
    } return true;
}

int power(game* g){
    gameRound max = {0,0,0};
    for (gameRound r: g->rounds){
        if (r.r>max.r){max.r = r.r;}
        if (r.g>max.g){max.g = r.g;}
        if (r.b>max.b){max.b = r.b;}
    }

    return max.power();
}

int main(){
    std::ifstream in("d2input.txt");
    std::string line;
    int sum = 0;
    gameRound mr;
    mr.r=12; mr.g=13, mr.b=14;
    while (std::getline(in, line)){
        game* tc = getGame(line);
        std::cout<<
        tc->gameno<<" "<<std::endl;
        for (gameRound gr: tc->rounds){        
            std::cout<<gr.r<<" "<<
            gr.g<<" "<<
            gr.b<<" "<<std::endl;
        }

        sum += power(tc);

        delete tc;
    }

    in.close();
    std::cout<<sum<<std::endl;
    return 0;
}