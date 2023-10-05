//md5
//sha256
//sha1
#include <iostream>
using namespace std;
#include <Windows.h>
#include <fstream>
#include <bitset>
#include <functional>
#include <string>
#include <sstream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<numeric>
#include<algorithm>
#include <map>
#include<random>
#include<unordered_set>
#include<chrono>
#include "md5.cpp"
#include"sha1.h"
#include"sha256.cpp"

const int hash_size=8;

string computations(string &input)
{
    uint64_t length = input.length() * hash_size;
    input += char((length >> 56) & 0xFF);
    input += char((length >> 48) & 0xFF);
    input += char((length >> 40) & 0xFF);
    input += char((length >> 32) & 0xFF);
    input += char((length >> 24) & 0xFF);
    input += char((length >> 16) & 0xFF);
    input += char((length >> 8) & 0xFF);
    input += char(length & 0xFF);
 
    for (int i = 7; i >= 0; i--) {
        uint8_t byte = static_cast<uint8_t>((length >> (i * 8)) & 0xFF);
        input += static_cast<char>(byte);
    }

    int  code_local=46886,var=7;
    int secret_rand;
    uint32_t hash[hash_size]={0};
    for(char c:input)
    {
        for(int i=0;i<hash_size;i++)
        {
            secret_rand=(code_local/var)-(var%10);

            hash[i]=(hash[i]^c)+secret_rand*(i+1);
            hash[i] ^= (hash[i] << 15) | (hash[i] >> 21);
            hash[i] = (hash[i] + 0x85ebca6b) ^ 0xc2b2ae35;

            var++;
        }
    }
    
    stringstream ss;
    for(int i =0;i<hash_size;i++)
    {
        ss<<hex<<setw(8)<<setfill('0')<<hash[i];
    }

    return ss.str();
}

string sha1(string inpt)
{
    SHA1 sha1;
    sha1.update(inpt);
    string output=sha1.final();
    return output;
}

void testAlgorithms()
{
    string row;
    int num_lines_tohash=1;
    int total_lines=0;
    stringstream vald;
    string filename="valdovas.txt";
    ifstream valdovas(filename);
    while(getline(valdovas,row))
    {
        total_lines++;
    }
    valdovas.clear();

        //custom
        while(num_lines_tohash<=total_lines)
        {
         auto start=std::chrono::high_resolution_clock::now();
         for(int i=0;i<num_lines_tohash;++i)
         {
             computations(row);
         }
            auto end=std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> difference = end - start;
        cout <<"custom hashavimas su " <<num_lines_tohash<<" eiluciu uztruko: " << difference.count() << " s\n";
        cout<<endl;
        //md5
        start=std::chrono::high_resolution_clock::now();
         for(int i=0;i<num_lines_tohash;++i)
         {
             md5(row);
         }
         end=std::chrono::high_resolution_clock::now();

         difference = end - start;
        cout <<"md5 hashavimas su " <<num_lines_tohash<<" eiluciu uztruko: " << difference.count() << " s\n";
       cout<<endl;
       //sha1
        start=std::chrono::high_resolution_clock::now();
         for(int i=0;i<num_lines_tohash;++i)
         {
             sha1(row);
         }
        end=std::chrono::high_resolution_clock::now();

         difference = end - start;
        cout <<"sha1 hashavimas su " <<num_lines_tohash<<" eiluciu uztruko: " << difference.count() << " s\n";
       cout<<endl;
        //sha256
        start=std::chrono::high_resolution_clock::now();
         for(int i=0;i<num_lines_tohash;++i)
         {
             sha256(row);
         }
        end=std::chrono::high_resolution_clock::now();

        difference = end - start;
        cout <<"sha 256 hashavimas su " <<num_lines_tohash<<" eiluciu uztruko: " << difference.count() << " s\n";
        cout<<endl;
        cout<<"*******************************"<<endl;
        num_lines_tohash*=2;

        }
}


int main()
{
   
      testAlgorithms(); 

}