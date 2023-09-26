#include "hash.cpp"

int user_input_request(){
    int ans;
    char yn, ni;
    SetConsoleOutputCP(CP_UTF8);
    cout<<"-----Hash generatorius-----\n";
    cout<<endl;
    cout<<"Pasirinkite norimą opciją:   \n";
    cout<<endl;
    cout<<"1. Generuoti hash'ą jūsų tekstui.\n";
    cout<<"2. Testavimas.\n";
    cin>>ans;
    cout<<"Pasirinkote opciją: "<<ans<<"\n";
    cout<<"Ar norite tęsti?(y/n)  \n";
    cin>>yn;
    while(true){
    if(yn=='y')
    {
       return ans;
    }
    else if(yn=='n'){
        cout<<"Paleist programą iš naujo(n) ar išeti(i)?(n/i)";
        cin>>ni;
        if(ni=='n')
        user_input_request();
        else {
            cout<<"Išeinama iš programos...";
            exit(0);
        }
    } 
}
}

int openf_or_manual()
{
    char ans;
    string ans2;
    SetConsoleOutputCP(CP_UTF8);
    cout<<"Generuoti hash'ą iš failo(f) ar norite įvesti tekstą rankiniu būdu?(r)?(f/r) \n";
    cin>>ans;
    if(ans=='f')
    {
        cout<<"Parašykite failo pavadinimą (.txt formatu):  \n";
        cin>>ans2;
        stringstream file_str;
        ifstream UserFile(ans2);
        file_str<<UserFile.rdbuf();
        string input=file_str.str();
        string output=hashed(input);
        cout<<output<<endl;    
    }
    else if(ans=='r')
    {
        cout<<"Parašykite tekstą:  ";
        cin>>ans2;
        string output=hashed(ans2);
        cout<<output<<endl;
    }
} 


void generateF(string filename, int num)
{  
    srand(static_cast<unsigned int>(time(NULL)));
    RandInt rnd(0, num);
    ofstream genr(filename); 
  
    if (!genr.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    string str="";
   for(int i=0;i<num;i++)
    {
        int randIndx=rnd();
        str.push_back(symbols[randIndx%(sizeof(symbols)-1)]);
        randIndx++;
    } 

    genr<<str;
    genr.close();

}

