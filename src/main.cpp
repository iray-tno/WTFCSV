#include "wtfcsv.h"
#include <string>
#include <iostream>
#include <vector>
//#include <boost/spirit/include/qi.hpp>

int main(int ,char *[]){
	WTFCSV wcsv;
	StringArray2D ret,output;
	/*
	wcsv.Input("./input.csv",ret);
	std::cout << ret.size() << std::endl << ret[0].size() << std::endl;
	for(unsigned int i = 0; i < ret.size(); i++){
		for(unsigned int j = 0; j < ret[0].size(); j++){
			std::cout << "--- (i,j)= ("<< i << "," << j<<") ---"<< std::endl;
			std::cout << ret[i][j] <<std::endl;
			std::cout << "--- end ---"<< std::endl<< std::endl;
		}
	}*/
	std::vector< std::string > buf;
	buf.push_back("あいうえお");
	output.push_back(buf);
	buf.push_back("あい1\n\nうえお\"\"");
	output.push_back(buf);
	buf.push_back("あい\"\"うえお,,\n");
	output.push_back(buf);
	for(unsigned int i = 0; i < output.size(); i++){
		for(unsigned int j = 0; j < output[i].size(); j++){
			std::cout << "--- (i,j)= ("<< i << "," << j<<") ---"<< std::endl;
			std::cout << output[i][j] <<std::endl;
			std::cout << "--- end ---"<< std::endl<< std::endl;
		}
	}
	wcsv.Output("./output.csv",output);
	return 0;
}

