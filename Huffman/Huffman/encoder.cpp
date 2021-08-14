//
//  main.cpp
//  encoder
//
//  Created by Roselle Milvich on 9/16/13.
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <math.h>

using namespace std;

const int kNumChar = 127;
static char kEOT = (int)3;
static string kmagicNumber = "andalxros";

struct node {
    int character;
    int value;
    node *left;
    node *right;
};
struct compareNodes                                                      //used by priority queue
{
    bool operator()(const node* l, const node* r) {return l->value > r->value;}
};
typedef priority_queue<node*, vector<node*>, compareNodes> value_queue;  //value_queue shortcut


char charFromBits(string str){
	char ch = 0;
	int i = 7;
	for(i = 7; i>=0; i--)
	{
        if (str[i] == '1')
        {
            ch+=pow(2,(double)(7-i));
        }
			
	}
	return ch;
}

void countCharacters(int charCounts[], string fname){
    ifstream inf(fname);
    char a;
    while (!inf.eof()) {
        inf>>noskipws>>a;
        charCounts[a]++;
    }
    charCounts[3] += 1;             //eot
    inf.close();
}

node* makeNode(int character, int value,  node* left, node* right){     //makes a node
    node *newNode = new node;
    newNode->character = character;
    newNode->value = value;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void nodesIntoQueue(int charCounts[], int sizeCharCounts, value_queue &queue){//creates nodes, put in queue
    for (int i = 0; i < sizeCharCounts; i++) {
        if (charCounts[i] != 0) {
            node *newNode = makeNode(i, charCounts[i], NULL, NULL);
            queue.push(newNode);
        }
    }
}

void helperCreateHuffmanTree(value_queue &queue){
    if (queue.size() > 1) {
        node *thisNode = queue.top();                           //get first node in the queue
        queue.pop();
        node *nextNode = queue.top();                           //get the second node in the queue
        queue.pop();
                                                                //connect 2 nodes w/ new parent and push
        node *newNode = makeNode(-1, thisNode->value + nextNode->value, thisNode, nextNode);
        queue.push(newNode);
        helperCreateHuffmanTree(queue);
    }
}

node* createHuffmanTree(value_queue &queue){
    helperCreateHuffmanTree(queue);////////changed back
    return queue.top();
}


void helperCreateBitcode(node *node, map<char, string> &charToBitcodes, map<string, char> &bitcodesToChar, string acc){
    if (!node->left && !node->right){                        //if a leaf, enter bitcode for character
        char c = (char)node->character;
        charToBitcodes[c] = acc;
        bitcodesToChar[acc] = c;
    }
    else{                                                   //if not a leaf, add a bit and keep going
        if (node->left){
            string str = acc + "0";
            helperCreateBitcode(node->left, charToBitcodes, bitcodesToChar, str);
            
        }
        if (node->right){
            string str = acc + "1";
            helperCreateBitcode(node->right, charToBitcodes, bitcodesToChar, str);
        }
    }
}

void createBitcode(node *node, map<char, string> &charToBitcodes, map<string, char> &bitcodesToChar){
    helperCreateBitcode(node, charToBitcodes, bitcodesToChar, "");
}

void initIntArray(int arr[kNumChar]){
    for (int i = 0; i < kNumChar; i++){
        arr[i] = 0;
    }
}

void printArray(int arr[], int size){
    for (int i = 0; i < size; i++) {
        cout<<i<<": "<<(char)i<<"         "<<arr[i]<<": "<<(char)arr[i]<<endl;
    }
}

void parent(int x)
{
    --x;
    while (x != 0)
    {
        x--;
        cout << "---|";
    }
}


void printPostOrder(node* n){
    if(n!= NULL){
        printPostOrder (n->left);
        printPostOrder (n->right);
        cout<<"char: "<<n->character<<": "<<(char)n->character<<"     value: "<< n->value<<endl;
    }
}

void printPreOrder(node* n){
    if(n!= NULL){
        cout<<"char: "<<n->character<<": "<<(char)n->character<<"     value: "<< n->value<<endl;
        printPreOrder (n->left);
        printPreOrder (n->right);
    }
}

void printInOrder(node* n, int level = 0){
    if(n!= NULL){
        level++;

        printInOrder(n->left, level);
        parent(level);
        cout<<"char: "<<n->character<<": "<<(char)n->character<<"     value: "<< n->value<<endl;
        printInOrder(n->right, level);
    }
}

void printBitcode(map<char, string> mymap){
    for (map<char, string>::iterator it = mymap.begin(); it != mymap.end(); it++) {
        cout<<it->first<<": "<<it->second<<endl;
    }
}

void encode(string fname, map<char, string> charToBitcodes, map<string, char> &bitcodesToChar){
    string file = fname + ".mcp";
    ofstream outf(file);                                            //create outfile
    outf<<'<'<<kmagicNumber<<'>'                                    //magic number
    <<'<'<<fname<<'>'                                           //file name
    <<'<';                                                      //bitcodes
    for (map<char, string>::iterator it = charToBitcodes.begin(); it != charToBitcodes.end(); it++) {
        string str;
        if (it->first =='0' || it->first == '1') str += "//";
        str += it->first + it->second;
        outf<<str;
    }
    outf<<'>'<<'<';                                                 //encoded text
    ifstream inf(fname);
    char c;
    string stringbuffer = "";
    string eight;
    while (inf>>noskipws>>c) {
        stringbuffer += charToBitcodes[c];
        while (stringbuffer.length() >= 8) {
            eight = stringbuffer.substr(0, 8);
            stringbuffer = stringbuffer.substr(8, stringbuffer.length()-8);
            outf<<charFromBits(eight);
        }
    }
    
    //eot eof
    stringbuffer += charToBitcodes[kEOT];
    while (stringbuffer.length()%8)
        stringbuffer += '0';
    while (stringbuffer.length() >= 8) {
        eight = stringbuffer.substr(0, 8);
        stringbuffer = stringbuffer.substr(8, stringbuffer.length()-8);
        outf<<charFromBits(eight);
    }
    char eof = (int)26;
    outf<<'>'<<'<'<<eof<<'>';
    
    inf.close();
    outf.close();

    cout << "file encode to " << file << endl; system("pause");

}

int main(int argc, const char * argv[])//argv[1], run from command line
{
    //get count of characters
    int charCounts[kNumChar];                               //create charCounts, char by index holding counts
    initIntArray(charCounts);                              //initialize character counts array
    //string fname = argv[1];                             //get the file  -temp-
    string fname = "USConstitution.txt";
    countCharacters(charCounts, fname);                 //puts count of characters from file in array
    printArray(charCounts, kNumChar);                   //print array -debug-

    // create nodes and put in queue
    value_queue queue;                                  //create a priority queue
    nodesIntoQueue(charCounts, kNumChar, queue);        //puts nodes into the queue

    //create huffman tree
    node *root = createHuffmanTree(queue);                           //create huffman tree with queue of nodes

    //cout<<"*********** Pre-Order **********"<<endl;     //print tree -debug-
    //printPreOrder(root);
    cout << "*********** In-Order **********" << endl; system("pause");
    printInOrder(root);
    system("pause");

    //cout<<"*********** Post-Order **********"<<endl;
    //printPostOrder(root);

    //create table of bit codes
    map<char, string> charToBitcodes;                         //create char to bitcodes map
    map<string, char> bitcodesToChar;                         //create bitcodes to char map

    createBitcode(root, charToBitcodes, bitcodesToChar);      //fill values for bitcodes
    printBitcode(charToBitcodes);                             //print bitcodes -debug-
    
    
    //encode
    encode(fname, charToBitcodes, bitcodesToChar);

    return 0;
}

/*
references:
class lecture
wikipedia for huffman encoding
C++ reference for map, queue
stackoverflow for !inf.eof()
*/
