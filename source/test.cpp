#include"hash.cpp"
//2
void konstitucijaTest()
{
    string row;
    int i=0;int j=1;
    stringstream konst;
    ifstream konstitucija("konstitucija.txt");

        while(!konstitucija.eof())
        {
            i++;
            getline(konstitucija, row);
            konst<<row<<" ";
            if(i==j)
            {
                auto start=std::chrono::high_resolution_clock::now();
                hashed(row);
                auto end=std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> difference = end - start;
                cout <<"hashavimas su " <<j<<" eiluciu uztruko: " << difference.count() << " s\n";
                j*=2;
            }

        }
}

int randomLength(int min, int max) {
    return rand() % (max - min + 1) + min;
}

string randomString(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charsetSize = sizeof(charset) - 1;
    string result;
    for (int i = 0; i < length; ++i) {
        result += charset[rand() % charsetSize];
    }
    return result;
}

int collision()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int collisions=0, totalPairs = 100000;
    ofstream outputFile("poros.txt");

    if (!outputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo poros.txt" <<endl;
        return 1;
    }

    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 10;
        string first = randomString(length);
        string second = randomString(length);
        outputFile  << first << ", " << second << "\n";
        if(hashed(first)==hashed(second))
        {
            collisions++;
        }
    }

    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 100;
        string first = randomString(length);
        string second = randomString(length);
        outputFile << first << ", " << second <<"\n";
         if(hashed(first)==hashed(second))
        {
            collisions++;
        }
    }

    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 500;
        string first = randomString(length);
        string second = randomString(length);
        outputFile  << first << ", " << second << "\n";
         if(hashed(first)==hashed(second))
        {
            collisions++;
        }
    }

    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 1000;
        string first = randomString(length);
        string second = randomString(length);
        outputFile << first << ", " << second << "\n";
         if(hashed(first)==hashed(second))
        {
            collisions++;
        }
    }

    outputFile.close();
    
    cout <<"Sukurtas failas poros.txt" <<endl;
    cout<<"Koliziju sk. : "<<collisions<<endl;
    return 0;
}

int avalanche_effectTest()
{
    int bitSize=256, hexSize=64;
    int bitMax=0, bitMin=256;
    int bitdifference=0;
    int hexMax=0,hexMin=64;
    int hexdifference=0;
   
    srand(static_cast<unsigned int>(time(nullptr)));

    int totalPairs = 100000;
    ofstream outputFile("6reik_poros.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Nepavyko atidaryti failo 6reik_poros.txt" << std::endl;
        return 1;
    }

    for (int i = 0; i < totalPairs; ++i) {
        int length = rand() % 1000 + 1; 

        string first = randomString(length);
        string second = first;
        string hexfirst,hexsecond,bitfirst, bitsecond;
        int Bitd=0, HexD=0;
        
        int diffIndex = rand() % length;
        char randomChar = 'a' + rand() % 26;
        second[diffIndex] = randomChar;

        
        outputFile << first << ", " << second << "\n";

        bitfirst=asciiToBin(hashed(first));
        bitsecond=asciiToBin(hashed(second)); 

        hexfirst=hashed(first);
        hexsecond=hashed(second);

       for(int j=0;j<256;j++)
        {
            if(bitfirst[j]!=bitsecond[j])
            {
                Bitd++;
            }
        }
        if(Bitd<bitMin)
        {
            bitMin=Bitd;
        }
        else{
            bitMax=Bitd;
        }

        bitdifference+=Bitd; 

        for(int m=0;m<64;m++)
        {
        if(hexfirst[m]!=hexsecond[m])
            {
                HexD++;
            }
        }
        if(HexD<hexMin)
        {
            hexMin=HexD;
        }
        else{
            hexMax=HexD;
        }
        hexdifference+=HexD; 

    }

 
    cout << "Sukurtas failas 6reik_poros.txt.txt" << std::endl;
    double avgBit=(double(bitdifference) / double(256))/100000*100;

    double avgHex=(double(hexdifference) / double(64))/100000*100;
    cout<<"Min bit"<<bitMin<<endl;
    cout<<"Min hex"<<hexMin<<endl;
    cout<<"Max bit"<<bitMax<<endl;
    cout<<"Max hex"<<hexMax<<endl;
    cout<<"Avg bit p"<<avgBit<<" %"<<endl;
    cout<<"Avg hex p"<<avgHex<<" %"<<endl;
    
    outputFile.close();
    return 0; 
}

