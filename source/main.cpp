#include "test.cpp" 
#include "additional.cpp"
int user_input_request()
{
    SetConsoleOutputCP(CP_UTF8);
    int ans;
    char yn, ni;
    cout<<"--------------------------\n";
    cout<<"-----Hash generatorius-----\n";
    cout<<"--------------------------\n";
    cout<<endl;
    cout<<"Pasirinkite norimą opciją:   \n";
    cout<<endl;
    cout<<"1. Generuoti hash'ą jūsų tekstui.\n";
    cout<<"2. Testavimas.\n";
    cin>>ans;
    cout<<"Pasirinkote opciją: "<<ans<<"\n";
    cout<<"Ar norite tęsti?(y/n)  \n";
    cin>>yn;
    while(true)
    {
        if(yn=='y')
        {
          return ans;
        }
        else{
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

void openf_or_manual()
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
        string output=computations(input);
        cout<<output<<endl;    
    }
    else if(ans=='r')
    {
        cout<<"Parašykite tekstą:  ";
        cin>>ans2;
        string output=computations(ans2);
        cout<<output<<endl;
    }
} 

void test_option()
{
   int pageidavimas;
    cout<<"Pasirinkote testavimo opciją \n";
    cout<<"Ką pageidaujate testuoti? \n 2 default failai \n 3 konstitucija.txt(efektyvumas) \n 4 lavinos efektas \n 5 atsparumas kolizijai  \n ";
    cin>>pageidavimas;
    switch(pageidavimas){
      case 2:
        defaultFileTest(); 
        break;
      case 3:
        konstitucijaTest();
        break;
      case 4:
        avalanche_effectTest();
        break;
      case 5:
        collision();
        break;
     
      default:
        cout<<"Netinkama pasirinkimo reikšmė\n";
    } 
}

int main()
{
  int user_answer=user_input_request();
  if(user_answer==1)
  {
    openf_or_manual();
  }
  else{
    test_option();
}
}