#include <iostream>
#include <fstreamExtension.h>
#include <algorithm>
#include <vector>
#ifndef CNM_H
#define CNM_H


class CNM
{
    public:
        struct heapNode{
            int i, j;
            double deltaQ;

            bool operator < (const heapNode& arg) const{
                return this -> deltaQ < arg.deltaQ;
            }
        }; typedef heapNode heapNode;

        size_t N;
        long twiceM;

        std::vector<std::vector<int>> adjacencyMatrix;
        std::vector<std::vector<double>> deltaQ;
        std::vector<double> aValues;

        std::vector<heapNode> maxHeap;
        std::vector<int> activeNodeIndices;

    public:

        CNM(std::vector<int>, const size_t& vertices);
        void AlgorithmCNM();
        void populateDeltaQ();
        void populateA_valueMatrix();
        unsigned long getDegree(int);
        double maxDeltaQ_InRow(int rowIndex, int& j);
        void updateAValuesArray(int j, int i);
        void updateDeltaQMartix(int j, int i);
        void displayCommunities();

        std::vector<std::vector<int>> communities;
};

#endif // CNM_H
