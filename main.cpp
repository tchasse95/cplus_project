
//
//  Created by TCHASSE ODJAC on 07.12.17.
//  Copyright © 2017 TCHASSE ODJAC. All rights reserved.
//
/



#include <iostream>
#include<fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define min_numb -100
#define max_numb 100
using namespace std;
int inputed(char fileName[],double store[12][31]){ //wrong function
    
    char c;
    int day,month,year=0;
    char escape[500];
    double value;
    ifstream inside;       // input file stream class/structure object
    inside.open(fileName); // opening of the file
    for(int i=0;i<31;i++){
        for(int j=0;j<12;j++){ // initalize  database
            store[j][i]=0;
        }
    }
    if (!inside.is_open()) // check if file could be opened
    {
        cerr << "error opening file " << fileName << endl;
    }
    else
    {
        cout << "input file " << fileName << " opened..." << endl;
        inside >> c;
        int i=0;
        do
        {
            
            for(int a=0;a<100;a++){ // is to clean the escape array
                escape[a]='\0';
            }
            i=0;
            while(c != '.'){
                escape[i]='\0';
                escape[i]=c;  // TAKE YEAR DATA
                inside>>c;
                i++;
            }
            //cout<<escape<<endl;
            day = atoi(escape);
            //            cout<<day;
            
            inside >> c;
            i=0;
            for(int a=0;a<100;a++){
                escape[a]='\0';
            }
            while(c != '.'){  //READ MONTH DATA
                escape[i]=c;
                inside>>c;
                i++;
            }
            //cout<<escape<<endl;
            month = atoi(escape);
            
            
            
            inside >> c;
            i=0;
            for(int a=0;a<100;a++){
                escape[a]='\0';
            }
            while(c != ';'){
                escape[i]=c;   //READ YEAR DATA
                inside>>c;
                i++;
            }
            //cout<<escape<<endl;
            year = atoi(escape);
            
            //            cout<<endl<<year;
            
            inside >> c;
            i=0;
            
            for(int a=0;a<100;a++){
                escape[a]='\0';
            }
            while(c != '\n'){
                escape[i]=c;  // READ THE VALUES
                //cout<<c;
                c=inside.get();
                i++;
            }
            i=0;
            value = atof(escape);
            //cout<<value;
            store[month-1][day-1]=(double)value;
            inside >> c;
        }while(! inside.eof());
        
        inside.close();                   // closing of input file
        cout << endl << "input file closed (see missing white spaces in output)" << endl;
        return year;
    }
    return 0;
}

int output(char fileName1[],double store[12][31],int year)
{
    //fileName2[] = "C:\\tchasse.html"; // file name with path, can also be inputted by the user or given as argument to main in argv
    
    
    // files[12][31]=inputstore1(&a, b);
    
    
    char nextline='\n';
    //   char separator = ';';
    ofstream outFile;       // output file stream structure/object
    outFile.open(fileName1); // opening of the file
    cout << "output file " << fileName1 << " opened..." << endl;
    outFile<<"<!DOCTYPE html>"<< nextline << "<html>"<< nextline << "<head> " << nextline << "<title>Mean Temperatures year lamda</title>" <<  nextline << "<style>"<< nextline << "table {" << nextline <<" width: 100%;"<< nextline<<"}"<< nextline<<"th, td {" << nextline <<" border: 1px solid black;" << nextline << "text-align: center;" << nextline << "}"<< nextline << "tr:nth-child(even) {" << nextline << " background-color: #f2f2f2;"<< nextline << "}"<< nextline << "</style>" << nextline <<"</head>" << nextline <<"<body>"<< nextline << "<h1>Mean Temperatures year lamda (Unit Degree Celsius)</h1>"<< nextline<<"<table>"<< nextline << "<th>DAYS</th><th>JAN</th><th>FEB</th><th>MAR</th><th>APR</th><th>MAY</th><th>JUN</th><th>JUL</th><th>AUG</th><th>SEPT</th><th>OCT</th><th>NOV</th><th>DEC</th></tr>";
    int min[]={0,0},max[]={0,0};
    //(index 0: day and 1: month)
    double sum=0, total=0;
    double mid=0;
    for(int i=0;i<31;i++){
        for(int j=0;j<12;j++){
            if(store[j][i]!=0){
                if(store[min[1]][min[0]]>store[j][i]){
                    min[0] = i;min[1] = j;}
                if(store[max[1]][max[0]]<store[j][i]){
                    max[0] = i;max[1] = j;}
                sum+=store[j][i];
                total++;
            }
        }
    }
    mid=sum/total;
    if (outFile.is_open())  // check whether file could be opened
    {
        outFile <<"<!DOCTYPE html>";
        for(int i=1;i<=31;i++){
            outFile<<"<tr><td>"<<i;
            for(int j=0;j<12;j++){
                outFile<<"<td>";
                if(store[j][i-1]!=0){
                    outFile<<store[j][i-1];
                }
                outFile<<"</td>";
            }
            outFile<<"</tr>";
        }
        
        outFile<<"</table>"
        "<p>Minimum Temperature:"<< store[min[1]][min[0]]<< "(" <<min[0]+1 << "." << min[1]+1 << ".)</p>";
        outFile<<"<p>Maximum Temperature:"<< store[max[1]][max[0]]<< "(" <<max[0]+1 << "." << max[1]+1 << ".)</p>";
        
        outFile<<"<p>Average Temperature:"<< mid << "</p>"
        "</body>";
        
        outFile.flush();
        
        outFile.close();      // closing of output file
        cout << "output file " << fileName1 << " closed" << endl;
    }
    else
    {
        cerr << "error: file " << fileName1 << " can not be opened" << endl;
    }
    
    return 0;
}
int main(int argc, const char * argv[]){    // insert code here...
    
    char give[100]={};
    double data[12][31];
    cout<<"please input the file name or directory to be imported :-\n";
    cin>>give;
    char output1[100];
    int i=0;
    while(give[i]!='.'){
        output1[i]=give[i];
        i++;
    }
    strcat(output1, ".html");
    
    int year = inputed(give, data);
    
    output(output1, data, year);
    return 0;
}
