#include "WTFCSV.h"

const char WTFCSV::kComma = ',';
const char WTFCSV::kDoublequote = '\"';
const char WTFCSV::kLineFeed = '\n';
const std::string WTFCSV::kDoublequoteStr("\"");

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

bool WTFCSV::Output(const std::string& file_name, const StringArray2D& data){
  fs_.open(file_name.c_str(), std::ios::out | std::ios::trunc);
  
  WriteFile(data);

  fs_.close();
  return true;
}

bool WTFCSV::WriteFile(const StringArray2D& data){
  std::ostringstream osstream;
  int rows = CountRows(data);

  int data_cols = data.size();
  for(int i = 0; i < data_cols; ++i){
    int data_i_rows = data[i].size();
    osstream << data[i][0];
    //1から
    for(int j = 1; j < data_i_rows; ++j){
      std::string element(data[i][j]);
      EscapeElement(element);
      osstream << kComma;
      osstream << element;
    }
    for(int j = 0; j < (rows-data_i_rows);++j){
      osstream << kComma;
    }
    osstream << std::endl;
  }
  fs_ << osstream.str();
  return true;
}

inline int WTFCSV::CountRows(const StringArray2D& data){
  int rows = 0, buf_rows = 0, cols = data.size();
  for(int i = 0; i < cols; ++i){
    buf_rows = data[i].size();
    if(rows < buf_rows){
      rows = buf_rows;
    }
  }
  return rows;
}

inline void WTFCSV::EscapeElement(std::string& element){
  if(IsNeededEscape(element)){
    size_t pos = element.find(kDoublequote,0);
    while(pos != std::string::npos){
      element.insert(pos,kDoublequoteStr);
      pos = element.find(kDoublequote,pos+2);
    }
    element = kDoublequote + element + kDoublequote;
  }
  return ;
}

inline bool WTFCSV::IsNeededEscape(const std::string& element){
  if(element.find(kDoublequote) != std::string::npos){
    return true;
  }
  if(element.find(kComma) != std::string::npos){
    return true;
  }
  if(element.find(kLineFeed) != std::string::npos){
    return true;
  }

  return false;
}