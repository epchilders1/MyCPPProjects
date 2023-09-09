#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    ofstream loginInfo;
    ifstream userCheck;
    loginInfo.open("test.txt");
    string variable;
    string userName;
    string password;
    string userLine;
    string temp;
    string truePass;
    bool trig = true;

    cout << "Welcome! Are you a new or returning user? (Enter either new or returning)" << endl;
    cin >> variable;
    
    if(variable == "new"){
        cout << "Enter a valid username" << endl;
        cin >> userName;
        userCheck.open("test.txt");
        while(!userCheck.eof()){
            getline(userCheck, userLine);
            stringstream ss(userLine);
            ss >> temp;
            if(temp == userName){
                cout << "Invalid username, already taken" << endl;
                userCheck.close();
                loginInfo.close();
                return 0;
            }
        }
        cout << "Great! Now enter a password" << endl;
        cin >> password;
        loginInfo << userName << " " << password << endl;
        loginInfo << endl;
        cout << "You have successfully created your account" << endl;
        //needs to enter username and password into test file without it overwriting itself
    }
    else if(variable == "returning"){
        cout << "Welcome back! Please enter your username" << endl;
        cin >> userName;
        userCheck.open("test.txt");
        while(!userCheck.eof()){
            getline(userCheck, userLine);
            stringstream ss(userLine);
            ss >> temp;
            if(temp == userName){
                ss >> truePass;
                trig = false;
                break;
            }
        }
        if(trig){
            cout << "Not a username in our database, try again" << endl;
            userCheck.close();
            loginInfo.close();
            return 0;
        }
        cout << "Now enter your password" << endl;
        cin >> password;
        if(password == truePass){
            cout << "Welcome Back!" << endl;
        }
        else{
            cout << "Invalid Password" << endl;
            userCheck.close();
            loginInfo.close();
            return 0;
        }
    }
    else{
        cout << "Invalid input" << endl;
    }
    userCheck.close();
    loginInfo.close();
    return 0;
}