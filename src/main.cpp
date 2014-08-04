#include "wtfcsv.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
//#include <boost/spirit/include/qi.hpp>

int main(int ,char *[]){
	WTFCSV wcsv;
	StringArray2D output;
	wcsv.Input("./input.csv",output);
	std::cout << "rows : " << output.size() << " cols : " << output[0].size() << std::endl;
	for(unsigned int i = 0; i < output.size(); i++){
		for(unsigned int j = 0; j < output[0].size(); j++){
			std::cout << i<<","<<j<<":"<<std::endl << output[i][j] << std::endl;
		}
	}
	return 0;
}

