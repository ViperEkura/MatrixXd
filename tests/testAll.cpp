#include <iostream>
#include <cassert>
#include "Array.h"
#include "MatrixXd.h"


int main()
{
    std::cout << "=====BEGINGIN TESTING=====\n";

    Array<double> arr = Array<double>::makeArray(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    assert(arr.size() == 10);

    std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    arr = Array<double>(vec);
    assert(arr.size() == 9);
    
    arr = arr.slice(1, 3);
    assert(arr.size() == 2);

    std::cout << "Testing Array PASS\n";
    MatrixXd<double> mat = MatrixXd<double>(arr, View(1, 2));
    MatrixXd<double> mat2 = MatrixXd<double>(5, 5);
    assert(mat.size() == 2);
    assert(mat2.size() == 25);
    std::cout << "Testing MatrixXd PASS\n";


    std::cout << "=====END TESTING=====\n";

}