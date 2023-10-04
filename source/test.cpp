#include"hash.cpp"

void defaultFileTest()
{
    string filenames[]={
        "1.txt",
        "a.txt",
        "empty.txt",
        "daug.txt",
        "maziau.txt",
        "new.txt",
        "new2.txt"
    };
    for(string& filename:filenames)
    {
   
        ifstream UserFile(filename);
        if(UserFile.is_open())
        {
            stringstream file_str;
            file_str<<UserFile.rdbuf();
            string input=file_str.str();
            string output=computations(input);

            cout<<"File: "<<filename<<"\n";
            cout<<"Output: "<<output<<"\n";
            UserFile.close();
        }
        else{
            cerr<<"Negalima atidaryti failo: "<< filename<<"\n";
        }
        
    }
}

//2
void konstitucijaTest()
{
    string row;
    int num_lines_tohash=1;
    int total_lines=0;
    stringstream konst;
    string filename="konstitucija.txt";
    ifstream konstitucija(filename);
    while(getline(konstitucija,row))
    {
        total_lines++;
    }
    konstitucija.clear();


        while(num_lines_tohash<=total_lines)
        {
         auto start=std::chrono::high_resolution_clock::now();
         for(int i=0;i<num_lines_tohash;++i)
         {
             computations(row);
         }
            auto end=std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> difference = end - start;
        cout <<"hashavimas su " <<num_lines_tohash<<" eiluciu uztruko: " << difference.count() << " s\n";
        num_lines_tohash*=2;
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
   

    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 10;
        string first = randomString(length);
        string second = randomString(length);
        if(computations(first)==computations(second))
        {
            collisions++;
        }
    }
    cout<<"10 simobliu poros "<<collisions<<'\n';
    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 100;
        string first = randomString(length);
        string second = randomString(length);
         if(computations(first)==computations(second))
        {
            collisions++;
        }
    }
 cout<<"100 simobliu poros "<<collisions<<'\n';
    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 500;
        string first = randomString(length);
        string second = randomString(length);
         if(computations(first)==computations(second))
        {
            collisions++;
        }
    }
 cout<<"500 simobliu poros "<<collisions<<'\n';
    for (int i = 0; i < totalPairs / 4; ++i) {
        int length = 1000;
        string first = randomString(length);
        string second = randomString(length);
         if(computations(first)==computations(second))
        {
            collisions++;
        }
    }
     cout<<"1000 simobliu poros "<<collisions<<'\n';

    
    cout<<"Koliziju sk. : "<<collisions<<endl;
    return 0;
}

string hexToBin(string input) {
    string binary = "";
    
    for (char hexDigit : input) {
        char lowercaseHexDigit = tolower(hexDigit);
    
        if (HexToBin.find(lowercaseHexDigit) != HexToBin.end()) {
            binary += HexToBin[lowercaseHexDigit];
        } else {
            return "Invalid input";
        }
    }
    
    return binary;
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

    for (int i = 0; i < totalPairs; ++i) {
        int length = rand() % 1000 + 1; 

        string first = randomString(length);
        string second = first;
        string hexfirst,hexsecond,bitfirst, bitsecond;
        int Bitd=0, HexD=0;
        
        int diffIndex = rand() % length;
        char randomChar = 'a' + rand() % 26;
        second[diffIndex] = randomChar;

        bitfirst=hexToBin(computations(first));
        bitsecond=hexToBin(computations(second)); 

        hexfirst=computations(first);
        hexsecond=computations(second);

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
    double avgBit=(double(bitdifference) / double(256))/100000*100;

    double avgHex=(double(hexdifference) / double(64))/100000*100;
    double percentBitMin = (static_cast<double>(bitMin) / static_cast<double>(256)) * 100;
    double percentBitMax = (static_cast<double>(bitMax) / static_cast<double>(256)) * 100;
    double percentHexMin = (static_cast<double>(hexMin) / static_cast<double>(64)) * 100;
    double percentHexMax = (static_cast<double>(hexMax) / static_cast<double>(64)) * 100;

    cout<<"Minimalus skirtums bitu lygmenyje "<<percentBitMin<<" %"<<endl;
    cout<<"Minimalus skirtumas hexu lygmenyje "<<percentHexMin<<" %"<<endl;
    cout<<"Maksimalus skirtumas bitu lygmenyje "<<percentBitMax<<" %"<<endl;
    cout<<"Maksimalus skirtumas hexu lygmenyje "<<percentHexMax<<" %"<<endl;
    cout<<"Vidutiniskas skirtumas bitu lygmenyje "<<avgBit<<" %"<<endl;
    cout<<"Vidutiniskas skirtumas hexu lygmenyje "<<avgHex<<" %"<<endl;
    return 0; 
}

