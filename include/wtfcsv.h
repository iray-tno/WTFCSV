#ifndef _WTFCSV_H__
#define _WTFCSV_H__
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
typedef std::vector< std::vector<std::string> > StringArray2D;

class WTFCSV{
 protected:
  
  std::fstream fs_;
  unsigned long cols_;
  unsigned long rows_;

  static const char kComma;
  static const char kDoublequote;

  StringArray2D buffer;

  bool   ReadFile(StringArray2D& ret);

  bool ParseLine(const std::string& line,std::vector<std::string>& row);
  void RemoveDoubleQuotes(std::string & str);
  bool IsEndOfElement(const std::string& element);

 public:
  WTFCSV():cols_(0),rows_(0){};
  ~WTFCSV();

  bool Input(const std::string& file_name, StringArray2D& ret);
  bool Output(const std::string& file_name, StringArray2D& data);

};

#endif //_WTFCSV_H__
