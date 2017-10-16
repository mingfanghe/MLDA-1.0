#include "BASE-Gadget.h"
Gadget::Gadget()
{

}
 void Gadget::matrix_to_csv(const vector<vector<double>> &matrix, string file)
{
    ofstream output_file(file);
    if (output_file.is_open())
    {
        for (auto i = matrix.begin(); i != matrix.end();++i)
        {
            for (auto j = (*i).begin(); j != (*i).end(); ++j)
            {
                output_file <<  (*j)  << "\t";//使用制表符分隔数据
            }
            output_file << "\n";
        }
    }else
    {
        cout << "fail to create file!" << endl;
    }
}



