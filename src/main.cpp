//#include "wtfcsv.h"
#include <string>
#include <iostream>
#include <vector>
#include <boost/spirit/include/qi.hpp>

inline bool SplitIntoTokens(const std::string& line, std::vector<std::string>& tokens ){
  std::string::const_iterator cit = line.begin();
  return boost::spirit::qi::parse(cit, line.end(), boost::spirit::*char_ % ',', tokens) && cit==line.end();
}

int main(int ,char *[]){
	//WTFCSV wcsv;
	//StringArray2D output;
	std::vector<std::string> vec;
	vec.push_back("3");
	vec.push_back("4");
	SplitIntoTokens("5,6,7", vec);
	for(int i = 0;i < vec.size(); i++){
		std::cout << vec[i] << std::endl;
	}
	//wcsv.Input("./input.csv",output);
	return 0;
}