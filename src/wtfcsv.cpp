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

  //getline(fs, line)　ファイルで1行読み込む
  //getline(iss, token, constComma.c_str()[0])  一行の中でカンマまで読み込む

  while(getline(fs_, line)){//1行読み込む 
    ParseLine(line);
  }
  return true;
}

bool WTFCSV::ParseLine(const std::string& line){
  std::string::const_iterator cit = line.begin();

  


  std::string token;
  std::istringstream iss(line);
  unsigned long current_rows = 0;
  cols_++;
  while(getline(iss, token, kComma)){//
    std::string element("");
    element.append(token);
    if(token[0] == kDoublequote){
      do{
        getline(iss, token, kComma);
        element.append(kComma+token);
      }while(IsEndOfElement(element));
      RemoveDoubleQuotes(element);
    }
    std::cout << element << std::endl;
    current_rows++;
  }
  return true;
}

inline bool SplitIntoTokens(const std::string& line, std::vector<string>& tokens ){
  std::string::const_iterator cit = line.begin();
  return boost::spirit::qi::parse(cit, line.end(), boost::spirit::*char_ % ',', tokens) && cit==line.end();
}

inline void WTFCSV::RemoveDoubleQuotes(std::string& str){
  std::string::size_type pos = 0;
  while((pos = str.find(kDoublequote)),(pos != std::string::npos)){
    str.erase(pos,1);
  }
  return ;
}

inline bool IsEndOfElement(const std::string& token){
  int token_length = token.length();
  if(token[token_length] == kDoublequote){
    if(token_length==1){
      return true;
    }else{}
  }else{
    return false;
  }
}
