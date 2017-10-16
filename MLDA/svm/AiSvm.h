#ifndef AISVM_H
#define AISVM_H
#include"svm/alg_svm.h"
#include "CplusHeader.h"
#include <QThread>
#include "baseWgt/BASE-Util.hpp"
#include "baseWgt/BASE-Gadget.h"

#include "baseWgt/BASE-Type.hpp"
#include "Solvers/Learner.h"
#define TRAINDATA_SET  1
#define  PARAM_SET 2
#define  SOLVED  4

using namespace libsvm;
class AiSVM:public Learner
{
  Q_OBJECT
 public:
    AiSVM()
    {
        ModelStatus=0;
        svmProb=new svm_problem;
        svmParams=new svm_parameter;
        svmModel=nullptr;
        trainningAble=0;
        libsvm::svm_Reportor=new svmReportor;
    }
    ~AiSVM(){
        freeMemory();
    }
    STATUS  setTrainingData(string fileName);
    void initDefaultParams();
    void freeMemory();
    STATUS  ReadDataMatrix(const string &fileName,vector<vector<double>> &Data,int colNums);
    //*****************************
    void train();
    void  setTrainingData();
    //*****************************
    void   predict();
    void evaluate();
    void    startUp()
    {
           start();
    }
    void run()
    {
        task=&AiSVM::train;
          (this->*task) ();
        task= &AiSVM::predict;
         (this->*task) ();
    }
signals:

       void freshProjectManagerTreeRequest();
       void  SendEvalutionData(vector<vector<double> >,vector<double>);

public:

    int ModelStatus;
    int sampleNums;
    int FeatureNums;

    QString trainingDataSetPath;
    QString predictDataSetPath;

    svm_problem *svmProb;
    svm_parameter *svmParams;
    svm_model *svmModel;

private:
      void (AiSVM::*task) ();  ///function pointer

};


#endif // AISVM_H
