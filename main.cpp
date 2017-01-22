//
//  main.cpp
//  Assignment 9
//
//  Created by Aman Lohia on 1/20/17.
//  Copyright © 2017 Aman Lohia. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

int num_books(ifstream &fin,string title[],int sim[][50])
{
    int num;
    fin >> num;
    for (int i=0; i<num; i++)
    {
        fin >> title[i] >> sim[i][0] >> sim[i][1] >> sim[i][2];
    }
    return num;
}

void output(ofstream &fout,int &num, string title[], int sim[][50])
{
    for (int i=0; i<num;i++)
    {
        fout << setw(20) <<left << title[i];
        
        for (int j=0;j<num;j++)
            fout << setw(10)<< sim[j][i];
        
        fout<<endl;
    }
}

void new_novel(string new_title, int newSimilarity[], string title[],int sim[][50],int &num)
{
    title[num]=new_title;
    
    for (int i=0;i<num;i++)
    {
        sim[i][num]=newSimilarity[i];
        sim[num][i]=newSimilarity[i];
    }
    sim[num][num]=0;
    
    num++;
}

void index(string novel, int num,string title[],int sim[][50], int &bmatch,
           int &lmatch)
{
    int num1=10,num2=0;
    for (int i=0; i<num; i++)
    {
        if(title[i]==novel)
        {
            for (int j=0; j<num; j++)
            {
                if (sim[i][j]<num1 && sim[i][j]!=0)
                {
                    num1=sim[i][j];
                    bmatch=j;
                }
                
                if (sim[i][j]>num2 && sim[i][j]!=0)
                {
                    num2=sim[i][j];
                    lmatch=j;
                }
            }
            
        }
    }
}

int main()
{
    ifstream fin("/Users/user/Desktop/Assignment 9/similar.txt");
    ofstream fout("/Users/user/Desktop/Assignment 9/outputfile.txt");
    ifstream newN("/Users/user/Desktop/Assignment 9/newNovels.txt");
    
    if(!fin)
    {
        cout << "File not found";
        return -1;
    }
    
    int num, bmatch, lmatch, sim[50][50], newSimilarity[50];
    string title[50], new_title, novel;
    num = num_books(fin, title, sim);
    
    while(newN >> new_title)
    {
        for (int i=0;i<num;i++)
            newN >> newSimilarity[i];
        
        new_novel(new_title, newSimilarity, title, sim, num);
    }
    
    output(fout, num, title, sim);
    
    while(true)
    {
        cout <<"Please enter name of the novel: ";
        cin >> novel;
        
        if (novel =="Done")
        {
            system ("PAUSE");
            return 0;
        }
        
        index(novel, num, title, sim, bmatch, lmatch);
        cout << "The most similar novel is " <<title[bmatch]
        <<endl<< "The least similar is "<<title[lmatch]<<endl<<endl;
    }
    
}

/*
 Please enter name of the novel: Enders_Game
 The most similar novel is Dune
 The least similar is Da_Vinci_Code
 
 Please enter name of the novel: Done
 */
