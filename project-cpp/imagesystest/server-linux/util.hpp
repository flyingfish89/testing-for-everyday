#ifndef _MY_UTIL_
#define _MY_UTIL_ 
#include<iostream>
#include<fstream>
#include<sstream>
#include<jsoncpp/json/json.h>

namespace imagesys
{
  class FileUtil
  {
    private:
      std::string _filename;
    public:
      FileUtil(const std::string &filename):_filename(filename){}
      bool Read(std::string *body)
      {
        std::ifstream ifs;
        ifs.open(_filename,std::ios::binary);
        if(ifs.is_open()==false)
        {
          perror("open is false");
          return false;
        }
        ifs.seekg(0,std::ios::end);
        size_t fsize=ifs.tellg();
        ifs.seekg(0,std::ios::beg);
        body->resize(fsize);
        ifs.read(&(*body)[0],fsize);
        if(ifs.good()==false)
        {
          std::cout<<"read file false"<<std::endl;
          ifs.close();
          return false;
        }
        ifs.close();
        return true;
      }
     
      
      bool Write(const std::string &body)
      {
         std::ofstream ofs;
           
        ofs.open(_filename,std::ios::binary);
        if(ofs.is_open()==false)
        {
          perror("open is false");
          return false;
        }
        ofs.write(body.c_str(),body.size());
        if(ofs.good()==false)
        {
          std::cout<<"write false"<<std::endl;
          ofs.close();
          return false;
        }
        ofs.close();
        return true;
      }
   };
  class JsonUtil
  {
   public:
      static bool Serialize(Json::Value &root,std::string *body)
     {
      Json::StreamWriterBuilder swb;
      Json::StreamWriter *sw=swb.newStreamWriter();
      std::stringstream ss;
      int ret=sw->write(root,&ss);
      if(ret!=0)
      {
        std::cout<<"json write filed"<<std::endl;
        return false;
      }
      *body=ss.str();
      return true;
     }
     static bool UnSerialize(const std::string &body,Json::Value *root)
     {
        std::string err;
        Json::CharReaderBuilder crb;
        Json::CharReader *pcr=crb.newCharReader();
        bool ret=pcr->parse(body.c_str(),body.c_str()+body.size(),root,&err);
        if(ret==false)
         {
           std::cout<<err;
            return -1;
         }
       return true;    
     }
  };
};
#endif
