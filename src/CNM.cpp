#include "CNM.h"

template<class T>
std::vector<T> generateInitVecs(size_t N)
{
    std::vector<T> V;

    for(int i = 0; i < N; i++)
        V.push_back(0);

    return V;
}

std::vector<int> blankVecs(size_t N)
{
    std::vector<int> V;
    return V;
}

CNM::CNM(std::vector<int> adjacency, const size_t& vertices)
{
    N = vertices;

    for(int i = 0; i < N; i++)
        adjacencyMatrix.push_back(generateInitVecs<int>(N));
    for(int i = 0; i < N; i++)
        deltaQ.push_back(generateInitVecs<double>(N));
    for(int i = 0; i < N; i++)
        communities.push_back(blankVecs(N));
    for(int i = 0; i < N; i++)
        aValues.push_back(0);

    for(long i = 0; i < N; i++)
        for(long j = 0; j < N; j++)
            adjacencyMatrix[i][j] = adjacency[i * N + j];

    twiceM = 0;
    for(long i = 0; i < N; i++)
        for(long j = 0; j < N; j++)
            twiceM += adjacencyMatrix[i][j];
    twiceM = twiceM * 2;

    for(int i = 0; i < N; i++)
        communities[i].push_back(i);

    for(int i = 0; i < N; i++)
       activeNodeIndices.push_back(i);
}

unsigned long CNM::getDegree(int index)
{
    long x = 0;

    for(long i = 0; i < N; i++)
        x += adjacencyMatrix[index][i];

    return x;
}

void CNM::populateDeltaQ()
{
    heapNode maxValues;
    maxValues.deltaQ = 0.00;
    maxValues.i = 0;
    maxValues.j = 0;

    for(long i = 0; i < N; i++)
    {
       maxValues.deltaQ = INT_MIN;
       maxValues.i = 0;
       maxValues.j = 0;

        for(long j = 0; j < N; j++)
        {
            if(adjacencyMatrix[i][j] == 0)
                deltaQ[i][j] = 0;
            else
                {
                    deltaQ[i][j] = ((static_cast<double> (1) / static_cast<double> (twiceM)) - ((static_cast<double> (getDegree(i)) * static_cast<double>(getDegree(j))) / static_cast<double> (twiceM * twiceM)));
                }
            if(maxValues.deltaQ <= deltaQ[i][j])
            {
                maxValues.deltaQ = deltaQ[i][j]; maxValues.i = i; maxValues.j = j;
            }

        }
        maxHeap.push_back(maxValues);
    }
    make_heap(maxHeap.begin(), maxHeap.end());
}

void CNM::populateA_valueMatrix()
{
    for(long i = 0; i < N; i++)
        aValues[i] = static_cast<double> (getDegree(i)) / static_cast<double> (twiceM);
}

double CNM::maxDeltaQ_InRow(int rowIndex, int& j)
{
    double maxDeltaQ = deltaQ[rowIndex][0];

    for(int k = 1; k < N; k++)
    {
        if(maxDeltaQ < deltaQ[rowIndex][k])
        {
            maxDeltaQ = deltaQ[rowIndex][k];
            j = k;
        }
    }

    return maxDeltaQ;
}

void CNM::updateDeltaQMartix(int j, int i)
{
    int k = 0;

    for(k = 0; k < N; k++)
    {
        if((deltaQ[i][k] != 0) && (deltaQ[j][k] != 0))
            deltaQ[j][k] += deltaQ[i][k];
        else if((deltaQ[j][k] == 0) && (deltaQ[i][k] != 0))
            deltaQ[j][k] = deltaQ[i][k] - (2 * aValues[j] * aValues[k]);
        else if((deltaQ[j][k] != 0) &&(deltaQ[i][k] == 0))
            deltaQ[j][k] = deltaQ[j][k] - (2 * aValues[i] * aValues[k]);
    }

    for(k = 0; k < N; k++)
    {
        deltaQ[i][k] = static_cast<double> (INT_MIN);
        deltaQ[k][i] = static_cast<double> (INT_MIN);
    }
}

void CNM::updateAValuesArray(int j, int i)
{
    aValues[j] += aValues[i]; aValues[i] = 0;
}

void CNM::AlgorithmCNM()
{
    populateDeltaQ();
    populateA_valueMatrix();

    heapNode maxDeltaQ;
    std::vector<int>::iterator val1, val2;

    maxDeltaQ = maxHeap.front();
    maxHeap.clear();

    int x = 0, temp;
    int iterator = 0;

    do
    {
        updateDeltaQMartix(maxDeltaQ.j, maxDeltaQ.i);
        updateAValuesArray(maxDeltaQ.j, maxDeltaQ.i);

        for(val1 = communities[maxDeltaQ.i].begin(); val1 != communities[maxDeltaQ.i].end(); val1++){
            communities[maxDeltaQ.j].push_back((*val1));}

            communities[maxDeltaQ.i].clear();

        activeNodeIndices.erase(remove(activeNodeIndices.begin(),  activeNodeIndices.end(), maxDeltaQ.i), activeNodeIndices.end());

        //Re construction of maxHeap
        for(val2 = activeNodeIndices.begin(); val2 != activeNodeIndices.end(); val2++)
        {
            maxDeltaQ.i = *val2;
            maxDeltaQ.deltaQ = maxDeltaQ_InRow(*val2, maxDeltaQ.j);
            maxHeap.push_back(maxDeltaQ);
        }

        maxDeltaQ = maxHeap.front();
        maxHeap.clear();
        x += 1;
    }
    while(x < ((76 * N) / 100));

    displayCommunities();
}

void CNM::displayCommunities()
{
    std::vector<int>::iterator i;
    std::vector<int>::iterator k;

    fstreamExtension writeCommunities("communities.csv", std::ios::out);

    for(i = activeNodeIndices.begin(); i != activeNodeIndices.end(); i++)
    {
        for(k = communities[*i].begin(); k != communities[*i].end(); k++)
        {
             if(*k == communities[*i].back())
                writeCommunities << *k;
             else
                writeCommunities << *k << ",";
        }
        if(!(*i == activeNodeIndices.back()))
        writeCommunities << "\n";
    }
}
