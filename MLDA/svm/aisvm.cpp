#include "AiSvm.h"

void AiSVM::freeMemory()
{
    if (svmModel)  svm_free_and_destroy_model(&svmModel);
    if (svmParams)  svm_destroy_param(svmParams);
    if(svmProb)
    {
        if(svmProb->y) delete [] svmProb->y;
        if(svmProb->x)  delete [] svmProb->x;
        delete svmProb;
    }
}

void  AiSVM:: train()
{
    if(  (ModelStatus  & TRAINDATA_SET)  &&(ModelStatus  &  PARAM_SET )   )     /// everything is ok then to run!
          svmModel= svm_train(svmProb,svmParams);
    else
         emit ShowMsgRequest(AiMsg(Error,MSG_TYPE_TEXT,0,QString("Not Ready! ") ));

}
STATUS AiSVM:: ReadDataMatrix(const string &fileName,vector<vector<double>> &Data,int colNums)
{
     ifstream fin(fileName );
     if (!fin)
     {
            cout << "Error in opening file <" << fileName << ">. ABORT!";
            AiMsg msg(Error,MSG_TYPE_TEXT,INT_MIN,QString("Error in opening file <"+  QString::fromStdString(fileName)  +">. ABORT!")) ;
           emit ShowMsgRequest(msg);
           return Error;
      }
       string line;
        while (fin.good() )
        {
            getline(fin, line);
            if( line.size()==0 ||  line =="\n" || line =="\r")
                 break;
            istringstream sin(line);
            string Xi;
            vector<double> row(colNums);
            for (int j=0;j<colNums && !sin.eof() ;++j)
            {
                sin >> Xi;
                row[j]=atof(Xi.c_str() );
            }
             Data.push_back(row);

        }
        fin.close();
}
void AiSVM::predict()
{
     if(predictDataSetPath.size()>0 && svmModel )
     {
          vector<vector<double>> Data;

          ReadDataMatrix(predictDataSetPath.toStdString(),Data, FeatureNums+1);
          vector<double>  y_Prediction(Data.size() );

          svm_node * input=new  svm_node[FeatureNums+1];
          input[FeatureNums].index=-1;
          for(int i =0;i<Data.size();++i)
          {
                   for(int j=0;j<FeatureNums;++j)
                   {
                          input[j].value = Data[i][j];
                          input[j].index=j+1;
                   }
               y_Prediction[i]  = svm_predict(svmModel,input);
          }

          Gadget gadget;
          vector<vector<double>>  Y(y_Prediction.size(),vector<double>(1,0.0) );
          for(int i=0;i<y_Prediction.size();++i){
              Y[i][0]=y_Prediction[i];
          }

          gadget.matrix_to_csv( Y, predictDataSetPath.toStdString()+".y");

          freshProjectManagerTreeRequest();

          QString msg= "Prediction finished ! \n The result has been saved to  <"+ predictDataSetPath+".y>";
          ShowMsgRequest(AiMsg(Ok,MSG_TYPE_TEXT,0,msg)  );
          SendEvalutionData(Data, y_Prediction);


     }else{
          if( predictDataSetPath.size()==0 )  ShowMsgRequest(AiMsg(Error,MSG_TYPE_TEXT,0,"You have not specified input data!") );
          if( !svmModel  )  ShowMsgRequest(AiMsg(Error,MSG_TYPE_TEXT,0,"Empty model! ") );

     }

}

void AiSVM:: setTrainingData()
{
    if(trainingDataSetPath.size()>0)  //如果路径有效
    {
        if( !(ModelStatus & TRAINDATA_SET ) )
        {
            if( Ok== this->setTrainingData(trainingDataSetPath.toStdString() )){
                QString message ="The training data load successfully from<"+trainingDataSetPath+">!";
                ShowMsgRequest(AiMsg(Ok,MSG_TYPE_TEXT,0,message) );
            }else{
                QString message ="The training data load fail from<"+trainingDataSetPath+">!";
                ShowMsgRequest(AiMsg(Error,MSG_TYPE_TEXT,0,message) );
            }
        }
    }else{
         ++trainningAble;
         QString message ="Fail to get file path!";
         ShowMsgRequest(AiMsg(Ok,MSG_TYPE_TEXT,0,message) );
    }
}
void AiSVM::evaluate(){

}

STATUS AiSVM:: setTrainingData(string fileName)
{
    ///////////////////////////////////////////////////////////////////////
    ifstream fin(fileName);
     if (!fin)
     {
            cout << "Error in opening file <" << fileName << ">. ABORT!";
            AiMsg msg(Error,MSG_TYPE_TEXT,INT_MIN,QString("Error in opening file <"+  QString::fromStdString(fileName)  +">. ABORT!")) ;
           emit ShowMsgRequest(msg);
            return Error;
      }
       string line;

       vector<vector<double>> Data;
        while (fin.good() )
        {
            getline(fin, line);
            istringstream sin(line);
            string Xi;
            vector<double> row;
            while (!sin.eof())
            {
                sin >> Xi;
                row.push_back(atof(Xi.c_str()));
            }
            if (Data.size()==0 || Data[0].size()==row.size() )  Data.push_back(row);
        }
        if(Data.size() <2  )
        {
            QString message ="The rows of file  <"+trainingDataSetPath+">  is less than 1! please check file .";
            ShowMsgRequest(AiMsg(Error,MSG_TYPE_TEXT,0,message) );
             return Error;
        }

        fin.close();
        /////////////////////////////////////////
        int M = Data.size();  sampleNums=M;
        int n = Data[0].size();FeatureNums=n-1;
        svmProb->l = M;
        svmProb->y = new double[svmProb->l];
        svmProb->x = new svm_node*[svmProb->l];
        for (int i = 0; i < svmProb->l; ++i){
            svmProb->x[i] = new svm_node[n];
        }
        for (int i = 0, j; i < M; ++i)
        {
            for (j = 0; j < Data[i].size() - 1; ++j)
            {
                svmProb->x[i][j].index = j+1;
                svmProb->x[i][j].value = Data[i][j];
            }
            svmProb->x[i][j].index = -1;//不知为何要多分配一个单元
            svmProb->y[i] = Data[i][j];
        }


        ModelStatus=ModelStatus | TRAINDATA_SET;
    return Ok;
}
void AiSVM::initDefaultParams()
{
      //参数初始化，参数调整部分在这里修改即可
        // 默认参数
        svmParams->svm_type = C_SVC;        //算法类型
        svmParams->kernel_type = LINEAR;    //核函数类型
        svmParams->degree = 3;    //多项式核函数的参数degree
        svmParams->coef0 = 0;    //多项式核函数的参数coef0
        svmParams->gamma = 0.5;    //1/num_features，rbf核函数参数
        svmParams->nu = 0.5;        // nu-svc的参数
        svmParams->C = 10;        //正则项的惩罚系数
        svmParams->eps = 1e-3;    //收敛精度
        svmParams->cache_size = 100;    //求解的内存缓冲 100MB
        svmParams->p = 0.1;
        svmParams->shrinking = 1;
        svmParams->probability = 1;    //1表示训练时生成概率模型，0表示训练时不生成概率模型，用于预测样本的所属类别的概率
        svmParams->nr_weight = 0;    //类别权重
        svmParams->weight = NULL;    //样本权重
        svmParams->weight_label = NULL;    //类别权重

}
