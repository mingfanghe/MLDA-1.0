#include "xgboostTest.h"

int main_test(int argc, char* argv[])
{
	XGBoostDemo();
    return 0;
}
int XGBoostDemo()
{

	printf("XGBoostDemo start... \n");
	// create the train data
    const size_t cols = 10, rows = 50000;
	//float train[rows][cols];
	float *train = new float[cols * rows];
	for (size_t i = 0; i < rows; i++)
	for (size_t j = 0; j < cols; j++)
		train[i * cols + j] = std::log(i + 1) * (j + 1);

	float train_labels[rows];
	for (size_t i = 0; i < rows; i++)
		train_labels[i] = std::log(1 + std::sqrt(i) * i);

	// convert to DMatrix
	DMatrixHandle h_train[1];
	XGDMatrixCreateFromMat(train, rows, cols, -1, &h_train[0]);

	// load the labels
	XGDMatrixSetFloatInfo(h_train[0], "label", train_labels, rows);

	// read back the labels, just a sanity check
	bst_ulong out_len;
	const float *out_floats;
	XGDMatrixGetFloatInfo(h_train[0], "label", &out_len, &out_floats);

	// create the booster and load some parameters
	BoosterHandle h_booster;
	XGBoosterCreate(h_train, 1, &h_booster);
	XGBoosterSetParam(h_booster, "booster", "gbtree");
	XGBoosterSetParam(h_booster, "objective", "reg:linear");
	XGBoosterSetParam(h_booster, "max_depth", "6");
	XGBoosterSetParam(h_booster, "eta", "0.3");
	XGBoosterSetParam(h_booster, "min_child_weight", "1");
	XGBoosterSetParam(h_booster, "subsample", "0.5");
	XGBoosterSetParam(h_booster, "colsample_bytree", "1");
	XGBoosterSetParam(h_booster, "num_parallel_tree", "1");

	// learning iterations (tried from 3 to 500)
	for (int iter = 0; iter < 70; iter++)
		XGBoosterUpdateOneIter(h_booster, iter, h_train[0]);

	// predict
	const size_t sample_rows = 5;
	float test[sample_rows][cols];
	for (size_t i = 0; i < sample_rows; i++)
	for (size_t j = 0; j < cols; j++)
		test[i][j] = std::log(1 + std::sqrt(i) * i);
	DMatrixHandle h_test;
	XGDMatrixCreateFromMat((float *)test, sample_rows, cols, -1, &h_test);
	const float *f;
	XGBoosterPredict(h_booster, h_test, 0, 0, &out_len, &f);

    for (unsigned int i = 0; i < 5; i++)
        std::cout << "label[" << i << "]=" << out_floats[i] << std::endl;
	for (unsigned int i = 0; i < out_len; i++)
		std::cout << "prediction[" << i << "]=" << f[i] << std::endl;

	// free xgboost internal structures
	XGDMatrixFree(h_train[0]);
	XGDMatrixFree(h_test);
	XGBoosterFree(h_booster);

	delete[] train;

	printf("XGBoostDemo over !\n");
	return 0;

}
int fuck(){

	int cols = 3, rows = 5;
	float *train = new float[rows*cols];

	for (int i = 0; i<rows; i++)
	for (int j = 0; j<cols; j++)
		train[i*rows + j] = (i + 1) * (j + 1);

	float *train_labels = new float[rows];
	for (int i = 0; i<rows; i++)
		train_labels[i] = 1 + i*i*i;

	// convert to DMatrix
	DMatrixHandle h_train[1], train_h;

	XGDMatrixCreateFromMat(train, rows, cols, 0, &h_train[0]);

	// load the labels
	XGDMatrixSetFloatInfo(h_train[0], "label", train_labels, rows);
	printf("runing...");
	// read back the labels, just a sanity check
	bst_ulong bst_result;
	const float *out_floats;
	XGDMatrixGetFloatInfo(h_train[0], "label", &bst_result, &out_floats);

	// create the booster and load some parameters
	BoosterHandle h_booster;
	XGBoosterCreate(h_train, 1, &h_booster);
	XGBoosterSetParam(h_booster, "booster", "gbtree");
	XGBoosterSetParam(h_booster, "objective", "reg:linear");
	XGBoosterSetParam(h_booster, "max_depth", "5");
	XGBoosterSetParam(h_booster, "eta", "0.1");
	XGBoosterSetParam(h_booster, "min_child_weight", "1");
	XGBoosterSetParam(h_booster, "subsample", "0.5");
	XGBoosterSetParam(h_booster, "colsample_bytree", "1");
	XGBoosterSetParam(h_booster, "num_parallel_tree", "1");

	// perform 200 learning iterations
	for (int iter = 0; iter<200; iter++)
		XGBoosterUpdateOneIter(h_booster, iter, h_train[0]);

	// predict
	const int sample_rows = 5;


	float **test = new float*[sample_rows];
	for (int i = 0; i < sample_rows; ++i)
		test[i] = new float[cols];


	for (int i = 0; i<sample_rows; i++)
	for (int j = 0; j<cols; j++)
		test[i][j] = (i + 1) * (j + 1);
	DMatrixHandle h_test;
	XGDMatrixCreateFromMat((float *)test, sample_rows, cols, -1, &h_test);
	bst_ulong out_len;
	const float *f;
	XGBoosterPredict(h_booster, h_test, 0, 0, &out_len, &f);
    for (unsigned int i = 0; i<bst_result; i++)
        std::cout << "label[" << i << "]=" << out_floats[i] << std::endl;
	for (unsigned int i = 0; i<out_len; i++)
		std::cout << "prediction[" << i << "]=" << f[i] << std::endl;

	// free xgboost internal structures
	XGDMatrixFree(h_train[0]);
	XGDMatrixFree(h_test);
	XGBoosterFree(h_booster);
	return 0;
}
