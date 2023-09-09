#include <string>
#include <deque>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char symb;
    bool flag = true;
    deque<char> waitList;

    string inputString = argv[1];
    deque<char> temp;
    for (int i = 0; i < inputString.length() + 1; i++)
    {
        cout << "Stack:";
        temp = waitList;
        for (int x = 0; x < waitList.size(); x++)
        {
            if (temp.size() > 0)
            {
                cout << " " << temp.front();
                temp.pop_front();
            }
        }
        cout << endl;
        if (inputString[i] == NULL)
        {
            break;
        }
        cout << "Character: " << inputString[i] << endl;
        if ((inputString[i] == '(') || (inputString[i] == '[') || (inputString[i] == '{') || (inputString[i] == '<'))
        {
            cout << "Push" << endl;
            waitList.push_back(inputString[i]);
        }

        else if (inputString[i] == ')' || inputString[i] == ']' || inputString[i] == '}' || inputString[i] == '>')
        {
            if (!waitList.empty())
            {
               temp = waitList;
                if ((temp.back() == '(') && (inputString[i] == ')'))
                {
                    symb = temp.back();
                    cout << "Matching " << symb << " and " << inputString[i] << endl;
                    cout << "Pop" << endl;
                    waitList.pop_back();
                }
                if ((temp.back() != '(') && (inputString[i] == ')'))
                {
                    cout << "Error: mismatched pair" << waitList.back() << " and " << inputString[i] << endl;
                    return 0;
                }
                if ((temp.back() == '[') && (inputString[i] == ']'))
                {
                    symb = temp.back();
                    cout << "Matching " << symb << " and " << inputString[i] << endl;
                    cout << "Pop" << endl;
                    waitList.pop_back();
                }
                if ((temp.back() != '[') && (inputString[i] == ']'))
                {
                    cout << "Error: mismatched pair" << waitList.back() << " and " << inputString[i] << endl;
                    return 0;
                }
                if ((temp.back() == '{') && (inputString[i] == '}'))
                {
                    symb = temp.back();
                    cout << "Matching " << symb << " and " << inputString[i] << endl;
                    cout << "Pop" << endl;
                    waitList.pop_back();
                }
                if ((temp.back() != '{') && (inputString[i] == '}'))
                {
                    cout << "Error: mismatched pair" << waitList.back() << " and " << inputString[i] << endl;
                    return 0;
                }
                if ((temp.back() == '<') && (inputString[i] == '>'))
                {
                    symb = temp.back();
                    cout << "Matching " << symb << " and " << inputString[i] << endl;
                    cout << "Pop" << endl;
                    waitList.pop_back();
                }
                if ((temp.back() != '<') && (inputString[i] == '>'))
                {
                    cout << "Error: mismatched pair " << waitList.back() << " and " << inputString[i] << endl;
                    return 0;
                }
            }
            else{
                waitList.push_front(inputString[i]);
                flag = false;
                break;
            }
        }
        else
        {
            cout << "Error: invalid character " << inputString[i] << endl;
            return 0;
        }
    }
    if(flag){
    cout << "Reached end of string" << endl;
    }
    if (waitList.empty())
    {
        cout << "String is properly balanced" << endl;
    }
    else if (waitList.front() == ')' || waitList.front() == ']' || waitList.front() == '}' || waitList.front() == '>')
    {
        cout << "Error: unmatched right symbol " << waitList.front() << endl;
        return 0;
    }
    else if (waitList.back() == '(' || waitList.back() == '[' || waitList.back() == '{' || waitList.back() == '<')
    {
        cout << "Error: unmatched left symbol " << waitList.back() << endl;
        return 0;
    }
    return 0;
}
