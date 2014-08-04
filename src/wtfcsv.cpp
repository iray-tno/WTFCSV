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
    if(ParseLine(line, row)==false){//行の終わりでないとき次の行も合わせてパースを試みる
      std::cout << "parseline false"<<std::endl;
      std::string buf_line("");
      do{
        buf_line.append(line);
        if(!getline(fs_, line)){return false;}
        buf_line.append(line);
      }while(ParseLine(buf_line, row)==false);
    }else{}
    ret.push_back(row);
  }
  return true;
}

bool WTFCSV::ParseLine(const std::string& line,std::vector<std::string>& row){
  //std::string::const_iterator cit = line.begin();
  std::string token;
  std::istringstream iss(line);
  unsigned long current_rows = 0;
  while(getline(iss, token, kComma)){//
    std::string element("");
    element.append(token);
    //FIXME 最初の文字がﾀﾞﾌﾞｸｵだったときに最後がダブクオ又はダブクオ＋改行で終わってるか調べる
    //      さらに最後のダブクオを数えて奇数だったら要素の終わりだからやめる
    if(element[0] == kDoublequote){
      if(element[element.size()-1] != kDoublequote)
      do{
        //std::cout << (token[0] == kDoublequote) << std::endl <<(token[token.size()-1] != kDoublequote);
        if(!getline(iss, token, kComma)){
          return false;
        }
        element.append(kComma+token);
      }while(IsEndOfElement(element));
      RemoveDoubleQuotes(element);
    }
    //FIXME 途中で中断する可能性あるからpushbackは後で
    row.push_back(element);
    current_rows++;
  }
  cols_++;
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
