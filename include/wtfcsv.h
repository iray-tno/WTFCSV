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
  std::fstream   fs;
  unsigned long  row_size;
  unsigned long  col_size;

  static const std::string constComma;

  std::vector< std::vector<std::string> > buffer;

  bool         ValidCSV();
  bool         ValidBuffer();
  bool         ReadData();
  bool         NoBuffer(){ return buffer.empty() == true; };

 public:
  WTFCSV();
  ~WTFCSV();

  bool  InputBuffer(const std::string file_name);
  bool  OutputBuffer(const std::string file_name);

  bool  InputBuffer(const std::string file_name, StringArray2D& buffer){
    bool ret;
    ret = InputBuffer(file_name);
    buffer = this->buffer;
    return ret;
  }

  bool  OutputBuffer(const std::string file_name, const StringArray2D buffer){
    this->buffer = buffer;
    return OutputBuffer(file_name);
  }

  void      Initialize();

  StringArray2D&  GetBufferRef(){ return buffer; };
  StringArray2D  GetBuffer(){ return buffer; };
  unsigned long  GetRowSize(){ return row_size; };
  unsigned long  GetColSize(){ return col_size; };
};

#endif //_WTFCSV_H__
