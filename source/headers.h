#include <iostream>
using namespace std;
#include "Windows.h"
#include <fstream>
#include <bitset>
#include <string>
#include <sstream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include <map>
#include<random>

map<string,string> hex_map{
    {"0000","0"},
    {"0001","1"},
    {"0010","2"},
    {"0011","3"}, 
    {"0100","4"},
    {"0101","5"},
    {"0110","6"},
    {"0111","7"},
    {"1000","8"},
    {"1001","9"},
    {"1010","a"},
    {"1011","b"},
    {"1100","c"},
    {"1101","d"},
    {"1110","e"},
    {"1111","f"}
};

const char symbols[]="0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!@$%^&*_+-=|;,./<>?";


class RandInt{
    public:
    RandInt(int low,int high): mt{rd()},dist{low,high}{}
    int operator()(){return dist(mt);}
    private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};