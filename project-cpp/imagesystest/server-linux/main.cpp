#include"data.hpp"
#include"util.hpp"
#include<string>
#include<iostream>
#include"httplib.h"
void datatest()
{
  image_sys::ImageTable *image=new image_sys::ImageTable();
  Json::Value val;
  val["info"]="傻狗";
  val["url"]="/image/cat.png";
  val["realpath"]="./www.root/image/cat.png";
  //image->Insert(val);
  Json::Value root;
  image->Getall(&root);
  //image->Getone(2,&root);
  std::string s;
  imagesys::JsonUtil::Serialize(root,&s);
  std::cout<<s<<std::endl;

  image->Delete(2);

  Json::Value root1;
  image->Getall(&root1);
  //image->Getone(2,&root);
  imagesys::JsonUtil::Serialize(root1,&s);
  std::cout<<s<<std::endl;
}
void Jsontest()
{
  Json::Value root;
  root["姓名"]="张三";
  root["年龄"]=18;
  root["成绩"].append(77);
  root["成绩"].append(77);
  root["成绩"].append(77);
  std::string body;
  imagesys::JsonUtil::Serialize(root,&body);
  std::cout<<body<<std::endl;


  Json::Value val;
  imagesys::JsonUtil::UnSerialize(body,&val);
  std::cout<<val["姓名"].asString()<<std::endl;
  std::cout<<val["年龄"].asInt()<<std::endl;
  size_t size=val["成绩"].size();
  for(int i=0;i<size;i++)
  {
  std::cout<<val["成绩"][i].asFloat()<<std::endl;
  }
}
static image_sys::ImageTable *g_image=NULL; 
void DeleteImage(const httplib::Request &req,httplib::Response &rsp)
{
  int image_id=std::stoi(req.matches[1]);//匹配规则中匹配到的数字
  Json::Value image;
  bool ret=g_image->Getone(image_id,&image);
  if(ret==false)
  {
    Json::Value err;
    err["result"]=false;
    err["reason"]="Failed to get the one information from the database";
    imagesys::JsonUtil::Serialize(err,&rsp.body);
    rsp.set_header("Content-Type","application/json");
    rsp.status=500;
    return;
  }
  //获取图片的实际储存路径，删除图片
  std::string realpath=image["realpath"].asString();
  remove(realpath.c_str());
  ret=g_image->Delete(image_id);
  if(ret==false)
  {
    Json::Value err;
    err["result"]=false;
    err["reason"]="Failed to delete information from the database";
    imagesys::JsonUtil::Serialize(err,&rsp.body);
    rsp.set_header("Content-Type","application/json");
    rsp.status=500;
    return;
  }
  rsp.status=200;
}
void UpdateImage(const httplib::Request &req,httplib::Response &rsp)
{
 int image_id =std::stoi(req.matches[1]);
 Json::Value image;
 bool ret=imagesys::JsonUtil::UnSerialize(req.body,&image);
 if(ret==false)
 {
    Json::Value err;
    err["result"]=false;
    err["reason"]="text information paring failed";
    imagesys::JsonUtil::Serialize(err,&rsp.body);
    rsp.set_header("Content-Type","application/json");
    rsp.status=400;
    return;
 }
 ret=g_image->Update(image_id,image);
 if(ret==false)
 {
    Json::Value err;
    err["result"]=false;
    err["reason"]="feiled to update from database";
    imagesys::JsonUtil::Serialize(err,&rsp.body);
    rsp.set_header("Content-Type","application/json");
    rsp.status=500;
    return;
 }
rsp.status=200;

}
void GetoneImage(const httplib::Request &req,httplib::Response &rsp)
{
 int image_id=std::stoi(req.matches[1]);//获取图片id
 Json::Value image;
 bool ret=g_image->Getone(image_id,&image);
 if(ret==false)
 {
    Json::Value err;
    err["result"]=false;
    err["reason"]="feiled to get one information from database";
    imagesys::JsonUtil::Serialize(err,&rsp.body);
    rsp.set_header("Content-Type","application/json");
    rsp.status=500;
    return;
 }
 imagesys::JsonUtil::Serialize(image,&rsp.body);
 rsp.status=200;
 rsp.set_header("Content-Type","application/json");
 return;
}
void GetAllImage(const httplib::Request &req,httplib::Response &rsp)
{
  Json::Value image;
  bool ret=g_image->Getall(&image);
  if(ret==false)
  {
    Json::Value err;
    err["result"]=false;
    err["reason"]="feiled to get all information from database";
    imagesys::JsonUtil::Serialize(err,&rsp.body);
    rsp.set_header("Content-Type","application/json");
    rsp.status=500;
    return;
  }
 imagesys::JsonUtil::Serialize(image,&rsp.body);
 rsp.status=200;
 rsp.set_header("Content-Type","application/json");
 return;
  
}
void InsertImage(const httplib::Request &req,httplib::Response &rsp)
{
    const httplib::MultipartFormData &image=req.get_file_value("image_file");
    const httplib::MultipartFormData &info=req.get_file_value("image_info");

    std::cout<<image.filename<<std::endl;
    //std::cout<<image.content<<std::endl;
    std::string name=image.filename;
    if(name.find("png")==std::string::npos&&name.find("jpg")==std::string::npos)
    {
        Json::Value err;                                                                                                                                                   
        err["result"]=false;                                                                                                                                               
        err["reason"]="it is not a image";                                                                                                            
        imagesys::JsonUtil::Serialize(err,&rsp.body);                                                                                                                      
        rsp.set_header("Content-Type","application/json");                                                                                                                 
        rsp.status=500;                                                                                                                                                    
        return;     
    }
    std::string realpath="./wwwroot/images/"+image.filename;
    bool ret=imagesys::FileUtil(realpath).Write(image.content);
    if(ret==false)
    {
        Json::Value err;
        err["result"]=false;
        err["reason"]="feiled to write information for /image";
        imagesys::JsonUtil::Serialize(err,&rsp.body);
        rsp.set_header("Content-Type","application/json");
        rsp.status=500;
        return;
    }
    Json::Value json_image;
    json_image["info"]=info.content;
    json_image["url"]="/images/"+image.filename;
    json_image["realpath"]=realpath;
    ret=g_image->Insert(json_image);
    if(ret==false)
    {
        Json::Value err;
        err["result"]=false;
        err["reason"]="feiled to insert information to database";
        imagesys::JsonUtil::Serialize(err,&rsp.body);
        rsp.set_header("Content-Type","application/json");
        rsp.status=500;
        return;
    }
    rsp.status=200;
}

int main()
{
   g_image=new image_sys::ImageTable();
   httplib::Server server;                                         
    //设置静态资源根目录                                            
   server.set_mount_point("/","./wwwroot/");                      
   
   server.Delete("/image/(\\d+)",DeleteImage);
   server.Put("/image/(\\d+)",UpdateImage);
   server.Get("/image/(\\d+)",GetoneImage);
   server.Get("/image",GetAllImage);
   server.Post("/image",InsertImage);

   server.listen("0.0.0.0",9090); 
  //Jsontest();
  //datatest();
  //imagesys::FileUtil("./text.txt").Write("hello");
  //std::string body;
  //imagesys::FileUtil("./text.txt").Read(&body);
  //std::cout<<body<<std::endl;
  return 0;
}

