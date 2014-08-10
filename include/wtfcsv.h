#ifndef _WTFCSV_H__
#define _WTFCSV_H__
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

typedef std::vector< std::vector<std::string> > StringArray2D;

class WTFCSV{
 protected:
  
  std::fstream fs_;
  unsigned long cols_;
  unsigned long rows_;

  static const char kComma;
  static const char kDoublequote;
  static const char kLineFeed;
  static const std::string kDoublequoteStr;

  StringArray2D buffer;

  bool  ReadFile(StringArray2D& ret);

  bool  ParseLine(std::vector<std::string>& row);
  bool  GetLine(std::string& line);
  bool  SplitIntoElements(const std::string& line, 
                          std::vector<std::string>& elements);
  int   CountDoublequotes(const std::string& str);
  void  UnescapeElement(std::string& element);

  bool  WriteFile(const StringArray2D& data);

  int   CountRows(const StringArray2D& data);
  void  EscapeElement(std::string& element);
  bool  IsNeededEscape(const std::string& element);
 
 public:
  WTFCSV():cols_(0),rows_(0){};
  ~WTFCSV();

  bool Input(const std::string& file_name, StringArray2D& ret);
  bool Output(const std::string& file_name, const StringArray2D& data);

};

#endif //_WTFCSV_H__
