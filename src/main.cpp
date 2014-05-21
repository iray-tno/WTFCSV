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
	for(int i = 0; i < output.size(); i++){
		for(int j = 0; j < output[0].size(); j++){
			std::cout << output[i][j] << std::endl;
		}
	}
	return 0;
}

