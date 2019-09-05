#include <iostream>
#include <string.h>
#include <fstream>
#include <malloc.h>

using  namespace std;

//setting the constant values
const int MAXDATA = 100;
const int NIL = -1;

//a  class to save database data 
class DB_data{
    public: 
        int dID; //ID 
        string dName; //data name
        string sequence; // data
        void setDID(int n){ dID=n; } // function to set ID
        //function to set data name
        void setDName(string dname){
            //removing the first "<" from  the name 
            dname.replace(0,1,"");
            dName = dname; 
        }
        //function to set the sequence
        void setSequence(string seq){ sequence = seq; }
        //function to set the data in a object
        void setDBData(int n,string dname,string seq){
            setDName(dname);
            setSequence(seq);
            setDID(n);
        }
        int getDID(){return dID;} //function to get the ID
        string getDName(){return dName;} //function to get data name
        string getSequence(){return sequence;} //funciton to get the sequence
        //function to displpay details in a object
        void displayData(){
            cout << "ID: " << getDID() << endl;
            cout << getDName() << endl << 
                    getSequence() << endl;
            cout << "*************" << endl;
        }

};

//a class to save query data
class Query_Data{
    public:
        string qName; // query name
        string query; // query
        int result[MAXDATA]; // array to save the calculated queries
        int qID; // query ID
        void setQID(int n){ qID=n; } //function to set the QID
        //function to set the query name
        void setQName(string qname){ 
            qname.replace(0,1,"");
            qName = qname; 
        }
        void setQuery(string q){ query = q; } //function to set query
        string getQName(){ return qName; } //function to get the query name
        //initializing the array
        void initArray(){
            for(int i=0;i<MAXDATA;i++)
                result[i] = NIL;
        }
        int getQID(){ return qID; } //function to get the query ID
        string getQuery(){ return query; } //function to get the query
        //function to set the query data in an object
        void setQData(string qname,string q,int n){
            setQID(n);
            setQuery(q);
            setQName(qname);
        }
};

DB_data dbarray[MAXDATA]; //an array to save the data base data 
int dbCount = 0; //to keep the count of data base data
Query_Data querryarray[MAXDATA]; // an array to save the query data
int qcount = 0; // to keep the count of queries

/*Knuth-Morris-Pratt (KMP) Algorithm has been used in the string matching
prior to calculation of the matches a pi table as created in the 
preprocessing phase
this displays the pi table
*/
void printPi(int Pi[],int len){
    int m = len;
    for(int i=0;i<m;i++)
        cout << Pi[i] << "\t";
    cout << endl;
}

//KMP algorithm
int KMP(string P,string T){
    int m = P.length();
    int n = T.length();
    /*if in case of a pattern's length > text length
    or if either pattern's length or text's length is 
    equal to 0 there is no point of matching the strings as there is 
    no match
    */
    if(m>n || m == 0 || n == 0)
        return NIL;
    int Pi[m];
    int k = 0;
    int pos = 0;
    //creating the pi table
    for (int a=1;a<m;a++){
        if(P[pos] == P[a]){
            k = k+1;
            Pi[a] = k;
            pos += 1;
        }
        else{
            k = 0;
            Pi[a] = 0;
            pos = 0;
        }
    }
    Pi[0] = 0;
    //printPi(Pi,m);
    int j = 0;
    int count= 0;
    int match=NIL;
    //matching the text with pattern
    for(int i=0;i<n;i++){
        while(P[j]!=T[i] && j>0){
            j = j-1;
            int temp = Pi[j];
            j = temp;
        }
        if(j<0)
            j = 0;
        if(P[j]==T[i]){
            j = j+1;
        }
        if(j==m){
            match = i-m+1;
            j = 0;
            break;
        }
    }
    return match;
}

//function to get data from database file
int inputDBData(){
    ifstream inFile;
    inFile.open("DNA Database.txt");
    if(inFile.fail()){
        cerr << "Error opening file";
        exit(1);
    }
    string dataName,sequence;
    string temp;
    int n = 0;
    sequence = "";
    getline(inFile,temp);
    while(temp!=">EOF"){
        if(temp[0] == '>'){
            if(dataName!=""){
                dbarray[n].setDBData(n,dataName,sequence);
                //dbarray[n].displayData();
                dbCount += 1;
                if(dbCount == MAXDATA){
                    cout << "Maximum number of data has been entered\n";
                    return 1;
                }
                n=n+1;
            }
            dataName = "";
            dataName = temp;
            sequence = "";
            getline(inFile,temp);
        }
        //if data are in new lines data will be appended to a single line    
        while(temp[0]!= '>'){
            sequence.append(temp);
            getline(inFile,temp);
        }
    }
    inFile.close();
    if(dataName!=""){
        dbarray[n].setDBData(n,dataName,sequence);
        //dbarray[n].displayData();
        dbCount += 1;
        if(dbCount == MAXDATA){
            cout << "Maximum number of data has been entered\n";
            return 1;
        }
        n=n+1;
    }
    return 0;
}

//function to get data from query file
int inputQuery(){
    ifstream inQFile;
    inQFile.open("querybase.txt");
    if(inQFile.fail()){
        cerr << "Error opening file";
        exit(1);
    }
    string queryName,query;
    string temp;
    int n = 0;
    query = "";
    getline(inQFile,temp);
    while(temp!=">EOF"){
        if(temp[0] == '>'){
            if(queryName != ""){
                querryarray[n].setQData(queryName,query,n);
                //querryarray[n].displayQuery();
                qcount += 1;
                if(qcount == MAXDATA){
                    cout << "Maximum number of queries has been entered\n";
                    return 1;
                }
                n=n+1;
            }
            queryName = "";
            queryName = temp;
            query = "";
            getline(inQFile,temp);
        }    
        while(temp[0]!= '>'){
            query.append(temp);
            getline(inQFile,temp);
        }
    }
    if(queryName != ""){
        querryarray[n].setQData(queryName,query,n);
        //querryarray[n].displayQuery();
        qcount +=1;
        if(qcount == MAXDATA){
            cout << "Maximum number of queries has been entered\n";
            return 1;
        }
        n=n+1;
    }
    inQFile.close();
    return 0;
}

//after inputing the data into obejects query array's objects will be updated with KMP
void updateQuery(){
    for(int i=0;i<qcount;i++){
        for(int j=0;j<dbCount;j++){
            int occ;
            occ = KMP(querryarray[i].getQuery(),dbarray[j].getSequence());
            querryarray[i].result[j] = occ;
        }
    }
}

//function to display the query results
void displayQResults(){
    for(int i=0;i<qcount;i++){
        cout << endl << querryarray[i].getQName() << endl;
        int qcount = 0;
        for(int j=0;j<dbCount;j++){
            if(querryarray[i].result[j] != NIL){
                cout << "[" << dbarray[j].getDName() << "]";
                cout << " at offset " << querryarray[i].result[j] << endl;
                qcount += 1;
            }        
        }
        if(qcount == 0){
            cout <<"NO DATA HAS BEEN MATCHED" << endl;
        }
    }
}
//function to write a file with the query results
void saveQueryResults(){
    ofstream myfile("output.txt");
    if(myfile.is_open()){
        for(int i=0;i<qcount;i++){
            myfile << querryarray[i].getQName() << endl; 
            int qcount = 0;
            for(int j=0;j<dbCount;j++){
                if(querryarray[i].result[j] != NIL){
                    myfile << "[" << dbarray[j].getDName() << "]";
                    myfile << " at offset " << querryarray[i].result[j] << endl;
                    qcount += 1;
                }        
            }
            if(qcount == 0){
                myfile <<"NO DATA HAS BEEN MATCHED" << endl;
            }
            myfile << endl;
        }    
    }
    else cerr << "Unable to open the file" << endl;    
}

int main(){
    inputDBData();
    inputQuery();
    updateQuery();
    displayQResults();
    saveQueryResults();
    return 0;
}
