#include "WTFCSV.h"

const char WTFCSV::kComma = ',';
const char WTFCSV::kDoublequote = '\"';

WTFCSV::~WTFCSV(){
};

bool WTFCSV::Input(const std::string& file_name, StringArray2D& ret){
  fs_.open(file_name.c_str(), std::ios::in);
  
  ReadFile(ret);

  fs_.close();
  return true;
}

bool WTFCSV::ReadFile(StringArray2D& ret){

  std::string line;

  while(getline(fs_, line)){//1行読み込む
    std::vector<std::string> row;
    ParseLine(line, row);
    ret.push_back(row);
  }
  return true;
}

bool WTFCSV::ParseLine(const std::string& line,std::vector<std::string>& row){
  //std::string::const_iterator cit = line.begin();
  std::string token;
  std::istringstream iss(line);
  unsigned long current_rows = 0;
  cols_++;
  while(getline(iss, token, kComma)){//
    std::string element(token);
    if(token[0] == kDoublequote){
      do{
        getline(iss, token, kComma);
        element.append(kComma+token);
      }while(IsEndOfElement(element));
      RemoveDoubleQuotes(element);
    }
    row.push_back(element);
    current_rows++;
  }
  return true;
}
/*
inline bool SplitIntoTokens(const std::string& line, std::vector<string>& tokens ){
  std::string::const_iterator cit = line.begin();
  return boost::spirit::qi::parse(cit, line.end(), boost::spirit::*char_ % ',', tokens) && cit==line.end();
}*/

inline void WTFCSV::RemoveDoubleQuotes(std::string& str){//ダブルクオートを
  std::string::size_type pos = 0;
  while((pos = str.find(kDoublequote)),(pos != std::string::npos)){
    str.erase(pos,1);
  }
  return ;
}

inline bool WTFCSV::IsEndOfElement(const std::string& element){
  int element_length = element.length();
  if(element[element_length] == kDoublequote){
    if((std::count(element.begin(), element.end(), kDoublequote)%2)==0){
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
}
