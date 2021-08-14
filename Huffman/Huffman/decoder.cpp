//
//  main.cpp
//  decoder
//
//  Created by Roselle Milvich on 10/2/13.
//  Copyright (c) 2013 Roselle Milvich. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>

using namespace std;

static char kEOT = (int)3;
static string kmagicNumber = "andalxros";
static int decompressed_count = 0;
static int compressed_count = 0;

string charToBits(char ch)
{
    int num = static_cast<unsigned char>(ch);
    string bits = "";
    
    for (int i = 7; i >= 0; i--){
        if (num - pow(2, i) >= 0) {
            num -= pow(2, i);
            bits += "1";
        }
        else bits += "0";
    }
    return bits;
}

void printBitcodes(map<string, char> mymap){
    for (map<string, char>::iterator it = mymap.begin(); it != mymap.end(); it++) {
        cout<<it->first<<": "<<it->second<<endl;
    }
}

int match(string &stringbuffer, map<string, char> bitcodesToChar){
    int ch = -1;
    for (int i = 0; i < stringbuffer.length(); i++) {
        string str = stringbuffer.substr(0, i+1);
        map<string, char>::iterator it = bitcodesToChar.find(str);
        if (it != bitcodesToChar.end()) {//match founc
            ch = bitcodesToChar[str];
            stringbuffer = stringbuffer.substr(i + 1, stringbuffer.length() - i + 1);
            break;
        }
    }
    return ch;
}

void decode(string fname)
{
    string file = "out_" + fname.substr(0, fname.length()-4);   ///////////////
    ofstream outf(file);                                            //create outfile
    ifstream inf(fname);
    string magicTag = "";
    string originalNameTag = "";
    
	string instring = "";
    unsigned char ch = 0;
    
    //get magicTag
    while(!inf.eof() && ch != '>')
	{
        compressed_count += 8;
		inf >> noskipws >> ch;
        instring += ch;
	}
    magicTag = instring;
    
    if (magicTag != "<" + kmagicNumber + ">"){
        cout<<"can't decode "<<fname<<endl;
    }
    else{
        
        //get filename
        instring = "";
        ch = 0;
        while(inf>>noskipws>>ch && ch !='>')
        {
            compressed_count += 8;
            instring += ch;
        }
        originalNameTag = instring;
        
        //get bitcodes
        map<string, char> myBitcodesToChar;
        string key = "";
        char value=NULL;
        ch = 0;
        while(inf>>noskipws>>ch && ch !='>')
        {
            compressed_count += 8;
            if (ch == '/' && inf.peek() == '/'){
                myBitcodesToChar[key] = value;
                key = "";
                inf>>noskipws>>ch;//    '/'
                inf>>noskipws>>value;//    '0' or a '1' character
                compressed_count += 2*8;
            }
            else if(ch != '0' && ch != '1'){
                myBitcodesToChar[key] = value;
                key = "";
                value = ch;
            }
            else{
                key += ch;
            }
        }
        myBitcodesToChar[key] = value;
        printBitcodes(myBitcodesToChar);////////////////
        
        //get binary
        string stringbuffer = "";
        compressed_count += 8;
        inf >> ch;////// <
        
        ch = 0;
        int c;
        while(!inf.eof() && ch != kEOT)
        {
            compressed_count += 8;
            inf >> noskipws >> ch;
            stringbuffer += charToBits(ch);
            while (stringbuffer.length() > 20) {                //batch of 20 at a time
                c = match(stringbuffer, myBitcodesToChar);
                ch = (char)c;
                if (kEOT == (char)c)
                    break;
                else if (c != -1){
                    decompressed_count += 8;
                    outf<<(char)c;
                }
            }
        }
        inf.close();
        outf.close();
    }
}

int main(int argc, const char * argv[])
{
    //decode(argv[1]);
    decode("test.txt.mcp");
    
    cout<<"original bit count: "<<decompressed_count<<endl;
    cout<<"compressed bit  count: "<<compressed_count<<endl;
    cout<<"percentage: "<<(float)compressed_count/decompressed_count<<endl;
    
    return 0;
}

