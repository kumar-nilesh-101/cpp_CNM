#include <boost/tokenizer.hpp>
#include <vector>
#include <iostream>
#include "fstreamExtension.h"
#include "CNM.h"
#include <string>
#include <math.h>

using namespace std;

void tokenizeToInt(string& intString, const char* seperators, vector<int>& container)
{
    boost::char_separator<char> delims(seperators);
    boost::tokenizer<boost::char_separator<char>> tokens(intString, delims);

    for (const auto& t : tokens) {
        container.push_back(atoi(t.c_str()));
    }
}

vector<int> makeAdjacencyMatrix(string dataFilePath)
{
    fstreamExtension fe(dataFilePath, ios::in|ios::binary);
    string s;
    vector<int> temp;

    while(!fe.eof())
    {
        getline(fe, s);
        tokenizeToInt(s, ",\n", temp);
    }

    return temp;
}

bool isPerfectSquare(vector<int> arg)
{
    unsigned int s = arg.size();
    float t1 = sqrt(s);
    int t2 = static_cast<int> (t1);

    if((t1 - t2) == 0)
        return true;
    else
        false;

}

int main()
{
    string adjMatrixFile;
    size_t vertices;
    cout << " Enter path of .csv file having data for adjacency matrix : ";
    cin >> adjMatrixFile;
    //cout << "\n Enter number of nodes in network : ";
    //cin >> vertices;
    cout << "\n";

    vector<int> matVec = makeAdjacencyMatrix(adjMatrixFile.c_str());

    if(isPerfectSquare(matVec))
    {
        vertices = static_cast<size_t> (sqrt(matVec.size()));
        CNM cnm (matVec, vertices);
        cnm.AlgorithmCNM();
        std::cout << "\n Metadata for communities is written in file : D:\\communityDetection\\communities.csv\n";
    }

    else
    {
        cout << "Invalid dimensions for an adjacency matrix";
    }

}
