#include "headers.h"

string code="00111001 00111001";
string asciiToBin( string input_EX)
{
    string binRes="";
    binRes.reserve(input_EX.size() * 8);
    for(char c:input_EX)
    {
        int asciiVal=static_cast<int>(c);
        binRes += bitset<8>(asciiVal).to_string();
    }
    
    return binRes;
}

string shiftR(string& input, int positions)
{
    string shifted=input;    
    int length = input.length();
    if (positions <= 0) {
        return shifted;
    }
    int possibleShift=positions%length;
    if(possibleShift<=0)
    {
        return shifted;
    }

    for (int i = 0; i < possibleShift; i++) {
        char lastChar = shifted[length - 1];
        for (int j = length - 1; j > 0; j--) {
            shifted[j] = shifted[j - 1];
        }
        shifted[0] = lastChar;
    }

return shifted;
}

string binToHex(string input)
{
    string hexed="";
    for(int i=0;i<input.size();i+=4)
    {
        hexed.append(hex_map[input.substr(i,4)]);
    }
    return hexed;
}

string addition_OR(string input1, string input2)
{
    string added_input = "";
    for (int i = 0; i < input1.length(); i++)
    {
        if (input1[i] == '1' || input2[i] == '1')
            added_input.push_back('1');
        else
            added_input.push_back('0');
    }
    return added_input;
}


string padding_of_bin(string& binRes_EX)
{

    string binRes_padded=binRes_EX+'1';
  
    int k = 0;
    size_t length=binRes_EX.length();
    while ((length + 1 + k) % 256 != 192) {
        k++;
    }

    binRes_padded+=string(k,'0');
    string lengthBin=bitset<64> (length).to_string(); 
    string binRes_padded_withLength=binRes_padded+(shiftR(lengthBin,1));
     for (int i = 64; i < binRes_padded_withLength.length(); i += 65) {
        binRes_padded_withLength.insert(i, "\n");
    }
    return binRes_padded_withLength;
}  

string computations(string &div_padded_bin_str)
{
    unsigned int hash=154568778, code_local=46886, secret=7531,a=7;

    for (char c : div_padded_bin_str) {
        hash = ((hash<<5) * a + static_cast<unsigned int>(c)+div_padded_bin_str.at(c)+div_padded_bin_str.front())-((hash>>2)%10)+c;
        a++;
    }
  
    string final=to_string(hash);
    int var=64;
    int var2=128;
    do
    {
        int secret_rand=(code_local/var)-(var%10);
        final+=to_string((secret_rand>>1)%10+var%3);
        var++; 
    }while(final.size()!=32);

    string computed=asciiToBin(final);
    string n=shiftR(computed,7); 
    return n;
}



string hashed(string &input_EX)
{
    string ascii_toBin=asciiToBin(input_EX); 
    string padded=padding_of_bin(ascii_toBin); 
    string computed_together=computations(padded);
    string hex_string=binToHex(computed_together); 
    return hex_string;
} 

