#include <iostream>
#include <string.h>
#include <fstream>
#include <malloc.h>

using namespace std;

//declaring Text and Pattern as global variables so any function can access these variables easily
string Text,Pattern;

//naive string matching algorithm
int naive(string P,string T){
    int m,n;
    m = T.length();
    n = P.length();
    /*if Pattern's length is greater than Text length there won't be a match 
    also if either Pattern or Text is an empty string there won't be a match*/
    if(m<n || m==0 || n==0){
        return 0;
    }
    else{
        /*flag has been created to detect the mismatches
        if any mismatch is found flag would set to 1
        and inner loop will be broken*/
        int flag = 0; 
        /*outer loop will be loop through the Text*/
        for(int i=0;i<m-n+1;i++){
            int k = i;
            //when starting a new inner loop flag is set to 0
            flag =  0;
            int count=0;
            /*inner loop go through the charcters in Pattern
            when there is a mismatch with the Text characters inner loop will
            be broken and outer loop will be shifed by 1 charcter*/
            for(int j=0;j<n;j++){
                /*in case of a mismatch and the character is not a wild card*/
                if(P[j]!=T[k] && P[j]!='_'){
                    flag = 1;
                }
                else{
                    k += 1;
                    count += 1;
                }
                if(flag ==  1){
                    flag = 0;
                    count = 0;
                    break;
                }
            }
            /*count will only be equal to length of pattern if there is no mismatch*/
            if(count == n){
                cout << "\nmatch found after " << i << " shifts" << endl;
                count = 0;
            }
        }
        return 1;
    }
}

/*work same as the int naive(string P,string T)
except output is written in a file after creating a file
*/ 
void saveMatches(string P,string T){
    //creating a file
    ofstream myfile("patternmatch1.output.txt"); //output file
    if(myfile.is_open()){
        myfile << "Pattern: " << P << endl;
        myfile << "\nText: " << T << endl;
        int m,n;
        m = T.length();
        n = P.length();
        if(m<n || m==0 || n==0){
            myfile << "\nno match" << endl;
        }
        else{
            int flag = 0; 
            for(int i=0;i<m-n+1;i++){
                int k = i;
                flag =  0;
                int count=0;
                for(int j=0;j<n;j++){
                    if(P[j]!=T[k] && P[j]!='_'){
                        flag = 1;
                    }
                    else{
                        k += 1;
                        count += 1;
                    }
                    if(flag ==  1){
                        flag = 0;
                        count = 0;
                        break;
                    }
                }
                if(count == n){
                    myfile << "\nmatch found after " << i << " shifts" << endl;
                    count = 0;
                }
            }
        }

    }
    else cerr << "Unable to open the file";
}

/*inserting data from files
here p is refered to pattern file's name
and t is refered to text file's name*/
void inputData(char *p,char *t){
    ifstream inFile;
    //opening the Text file
    inFile.open(t);
    if(inFile.fail()){
        cerr << "Error in opening the file";
        exit(1);
    }
    string temp;
    Text = "";
    string space = " ";
    getline(inFile,temp);
    while(!inFile.eof()){
        Text.append(temp);
        Text.append(space);
        getline(inFile,temp);
    }
    Text.append(space);
    Text.append(temp);
    //setting data in Text file to Text variable
    cout << "Text: " <<Text << endl;
    inFile.close();
    ifstream inPFile;
    //opening the Pattern file
    inPFile.open(p);
    if(inPFile.fail()){
        cerr << "Error in opening the  file";
        exit(1);
    }
    string temp1;
    getline(inPFile,temp1);
    /*while(!inFile.eof()){
        Pattern.append(temp1);
        Pattern.append(space);
        getline(inPFile,temp1);
    }
    Pattern.append(space);
    Pattern.append(temp1);*/
    Pattern = temp1;
    //setting data in Pattern file to Pattern variable
    inPFile.close();
    cout << "Pattern: " << Pattern << endl ;
}


int main(){
    char *p,*t;
    /*
    //To get user input 
    cout << "ENTER THE PATTERN FILE NAME: ";
    cin >> p;
    cout << "\nENTER THE TEXT FILE NAME: ";
    cin >> t;
    inputData(p,t);*/
    char P[] = "pattern1.txt"; // pattern file
    char T[] = "text1.txt"; // text file
    //getting data
    inputData(P,T);
    int n;
    //displaying data
    n = naive(Pattern,Text);
    if(n == 0){
        cout << "no match" << endl;
    }
    //writing the file 
    saveMatches(Pattern,Text);
    return 0;
}

