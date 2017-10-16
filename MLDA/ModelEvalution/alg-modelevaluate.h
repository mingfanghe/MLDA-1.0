#ifndef ALGMODELEVALUATE_H
#define ALGMODELEVALUATE_H
#include "Common.h"

class ModelEvaluator
{
public:
    ModelEvaluator();
    bool setData(vector<vector<double>> &testData,vector<double> &y_prediction);
    void Evaluate();


protected:
    int sampleNums,FeatureNums;

    map<int,int> Labels;
    vector<vector<double>> TestDataMatrix;
    vector<double>  y_Prediction;
    vector<vector<int>>  ConfusionMatrix;

};

#endif // ALGMODELEVALUATE_H
