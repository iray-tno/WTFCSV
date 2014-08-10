#include "wtfcsv.h"
#include <string>
#include <iostream>
#include <vector>
//#include <boost/spirit/include/qi.hpp>

int main(int ,char *[]){
	WTFCSV wcsv;
	StringArray2D output;
	wcsv.Input("./input.csv",output);
	std::cout << output.size() << std::endl << output[0].size() << std::endl;
	for(unsigned int i = 0; i < output.size(); i++){
		for(unsigned int j = 0; j < output[0].size(); j++){
			std::cout << "--- (i,j)= ("<< i << "," << j<<") ---"<< std::endl;
			std::cout << output[i][j] <<std::endl;
			std::cout << "--- end ---"<< std::endl<< std::endl;
		}
	}
	return 0;
}

