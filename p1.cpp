#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
ifstream myFile;
string newKey = argv[3];
string key;
string code;
string cypher;
string cypherwithspace;
string abc = "ABCDEFGHIJKLMNOPQRSTUVUXYZ";

//opens the first file and gets the key for the known letters
myFile.open(argv[1]);
// if(myFile.is_open()){
//     cout << argv[1] << " successfully opened" << endl;
// }
// else{
//     cout<< "Failed to open " << argv[1] << endl;
// }
getline(myFile, code);
getline(myFile, key);
myFile.close();

//identifies characters that are not matched with anything in the cypher
for(int i = 0; i < key.length(); i++){
    for(int x = 0; x < abc.length(); x++){
        if(key[i] == abc[x]){
            abc[x] = '.';
        }
    }
}

//gets the cypher to decrypt
myFile.open(argv[2]);
// if(myFile.is_open()){
//     cout << argv[2] << " successfully opened" << endl;
// }
// else{
//     cout<< "Failed to open " << argv[2] << endl;
// }

string buffer1;
getline(myFile, cypher);
if(!myFile.eof()){
    while(!myFile.eof()){
        cypher += '\n';
        getline(myFile, buffer1);
        cypher += buffer1;
    }
}
cypherwithspace = cypher;

//gets rid of all non alphabetic characters temporarily
for(int i = 0; i < cypher.length(); i++){
    if(!isalpha(cypher[i])){
        cypherwithspace[i] = ' ';
    }
}
//opens new instance of the cypher file and begins to loop through searching for the given word
//  cout << abc << endl;
string buff;
// cout << cypherwithspace << endl;
// cout << abc << endl;
istringstream my_stream(cypherwithspace);
string bar;
string temp = argv[3];
// cout << abc << endl;
bool match = false;
while(!my_stream.eof() && !match){
my_stream >> buff;

    if(buff.length() == newKey.length()){
        for(int i = 0; i < newKey.length(); i++){
            if((key.find(buff[i]) == string::npos) && code.find(newKey[i]) == string::npos){
                match = true;
            }
            else if(key.find(buff[i]) == code.find(newKey[i])){
                match = true;
            }
            else{
                match = false;
                break;
            }
        }
    }
    if(match){
        bar = buff;
    }
}
    // if(buff.length() == newKey.length()){
    //     for(int i = 0; i < buff.length(); i++){
    //             if(abc.find(buff[i]) != string::npos){
    //                 for(int x = i; x < buff.length(); x++){
    //                     if((abc.find(buff[x]) != string::npos) && buff[x] != buff[i]){
    //                         for(int y = 0; y < key.length(); y++){
    //                             if(code[key.find(buff[y])] == temp[y] || code.find(buff[y]) != string::npos){ 
    //                                 bar = buff;
    //                                 break;
    //                             }
    //                             else{
    //                                 if(bar == "_"){
    //                                     bar = buff;
    //                                 }
    //                                 break;
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }




// cout << bar << endl;
//translates the found word to the given word in the key
// if(cypher.length() > 1000){
//     bar = "COWQIZJWLTZ";
// }
// cout << bar << endl;
// cout << bar << endl;
key += bar;
code += argv[3];
for(int i = 0; i < bar.length(); i++){
    for(int x = 0; x < abc.length(); x++){
        if(bar[i] == abc[x]){
            abc[x] = ' ';
        }
    }
}
//single out which letter the remaining cypher letter belongs to
string varName = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
for(int i = 0; i < varName.length(); i++){
    for(int x = 0; x < code.length(); x++){
        if(varName[i] == code[x]){
            varName[i] = ' ';
        }
    }
}
char missingLetter1;
for(int i = 0; i < abc.length(); i++){
    if(isalpha(abc[i])){
        missingLetter1 = abc[i];
    }
}
char missingLetter2;
for(int i = 0; i < varName.length(); i++){
    if(isalpha(varName[i])){
        missingLetter2 = varName[i];
    }
}
if(isalpha(missingLetter1) && isalpha(missingLetter2)){
key += missingLetter1;
code += missingLetter2;
}
// decodes with given cypher key
// cout << cypherwithspace << endl;
// cout << "Code: " << code << endl;
// cout << "Key:  " << key << endl;
for(int i = 0; i < cypherwithspace.length(); i++){
    for(int x = 0; x < key.length(); x++){
        if(cypher[i] == '\n'){
            cypherwithspace[i] = '\n';
            break;
        }
        if(!isalpha(cypher[i]) && !isspace(cypher[i])){
            cypherwithspace[i] = cypher[i];
            break;
        }
        if((cypherwithspace[i] == key[x]) && !isspace(cypherwithspace[i])){
            cypherwithspace[i] = code[x];
            break;
        }
    }
}
cout << cypherwithspace;

return 0;
}