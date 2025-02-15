#include<bits/stdc++.h>
using namespace std;


#define MAX 100
bool checkDigit(string c){
    for(char ch : c){
        if(!isdigit(ch)){
            return false;
        }
    }
    return true;
}


int randomNumber(){
    srand(time(0));
    return rand() % MAX + 1;
}

int number(){
    string n;
    int guess;
    while(true){
        cout<<"Enter the number You Guessed: "<<endl;
        cin>>n;
        if(checkDigit(n)){
            guess = stoi(n);
            if(guess > 0) break;
            else cout<<"Guessing must be greater than 0."<<endl;
        }
        else{
            cout<<"Please Enter a number";
        }
    }     
    return guess;
}

void checkGuess(int Actual){
    int attempts = 0;
    int guess;
    do{
        guess = number();
        attempts++;
    
        if(guess > Actual){
            cout<<"Too high,Try again."<<endl;
        }
        else if(guess < Actual){
            cout<<"Too Low,Tryagain."<<endl;
        }
        else{
            cout << "Congratulations! You guessed the number in " << attempts << " attempts." << endl;
        }
    }while(guess!=Actual);
}

int main(){
    int ActualNum = randomNumber();

    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I have chosen a number between 1 and "<< MAX<<". Try to guess it!" << endl;
    
    checkGuess(ActualNum);

}