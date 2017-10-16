#include "alg-modelevaluate.h"

ModelEvaluator::ModelEvaluator()
{

}
bool ModelEvaluator::setData(vector<vector<double>> &testData,vector<double> &y_prediction)
{
      // testData 的最后一列应当是真实的 label
      TestDataMatrix=testData;
       sampleNums=TestDataMatrix.size();
       if(sampleNums>0) {
              FeatureNums=TestDataMatrix[0].size()-1;
       }else{
             cout<< "Test Data is empty!"<<endl;
            return false;
       }
       y_Prediction=y_prediction;
       return true;

}
void ModelEvaluator:: Evaluate()
{      // O(n)
    //  此函数有问题
        Labels.clear();
        ConfusionMatrix.clear();

         int labelnums=-1;
         for(int i=0;i< sampleNums;++i )
         {
                int label= TestDataMatrix[i][FeatureNums];
                 if(Labels.find(label) ==Labels.end() )
                        Labels[label]=++labelnums;
         }
         ConfusionMatrix.resize(labelnums+1,vector<int>(labelnums+1,0));

         for(int i=0;i< sampleNums;++i )
         {
                 int y= TestDataMatrix[i][FeatureNums];
                 int y_pred=y_Prediction[i];
                 ++ ConfusionMatrix[Labels[y] ][  Labels[y_pred]  ];
         }

}
