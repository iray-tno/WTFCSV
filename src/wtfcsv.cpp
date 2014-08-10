#include "WTFCSV.h"

const char WTFCSV::kComma = ',';
const char WTFCSV::kDoublequote = '\"';
const char WTFCSV::kLineFeed = '\n';

WTFCSV::~WTFCSV(){
};

bool WTFCSV::Input(const std::string& file_name, StringArray2D& ret){
  fs_.open(file_name.c_str(), std::ios::in);
  
  ReadFile(ret);

  fs_.close();
  return true;
}

bool WTFCSV::ReadFile(StringArray2D& ret){

  std::vector<std::string> row;
  while(ParseLine(row)){
    ret.push_back(row);
  }
  return true;
}

bool WTFCSV::ParseLine(std::vector<std::string>& row){
  row.clear();
  std::string line;
  if(!GetLine(line)){
    return false;
  }
  
  SplitIntoElements(line, row);
  return true;
}

inline bool WTFCSV::SplitIntoElements(const std::string& line,
                                      std::vector<std::string>& elements){
  elements.clear();
  std::string element, token;
  int sum_of_dqs = 0;
  std::istringstream iss(line);
  
  while(getline(iss, element, kComma)){
    if(element[0] == kDoublequote){

      sum_of_dqs = CountDoublequotes(element);

      while( (sum_of_dqs%2) == 1){
        getline(iss, token, kComma);
        sum_of_dqs += CountDoublequotes(token);
        element.append(kComma+token);
      }

      UnescapeElement(element);
    }

    elements.push_back(element);
  }
  return true;
}

inline bool WTFCSV::GetLine(std::string& line){
  /*
    行に含まれるダブルクオートが奇数の場合
    次の行も読み込んで連結する
  */
  line.clear();
  std::string buf;

  if(!getline(fs_,buf)){ return false; }
  int sum_of_dqs = CountDoublequotes(buf);
  line.append(buf);
  
  while( (sum_of_dqs%2) == 1){ 
    if(!getline(fs_,buf)){ return false; }
    sum_of_dqs += CountDoublequotes(buf);
    line.append(kLineFeed+buf);
  }
  return true;
}

inline int WTFCSV::CountDoublequotes(const std::string& str){
  return std::count(str.begin(), str.end(), kDoublequote);
}

inline void WTFCSV::UnescapeElement(std::string& element){
  size_t first = element.find_first_of(kDoublequote);
  size_t last = element.find_last_of(kDoublequote);
  if(first == std::string::npos||last == std::string::npos){
    return ;
  }
  element = element.substr(first+1, last-(first+1));
  
  size_t pos = element.find(kDoublequote,0);
  while(pos != std::string::npos){
    element.erase(pos,1);
    pos = element.find(kDoublequote,pos+1);
  }
  return ;
}

