#pragma once
#include <iostream>
#include <string>
#include <dirent.h>

using namespace std;


namespace photo1
{
    struct photonode
    {
        photonode *next;
        string path;
        string filename;
    };
    
    class photomanage
    {
        private:
        photonode *root;

        public:
        photomanage()
        {
            this->root = (photonode*)malloc(sizeof(photonode));
            this->root->next     = nullptr;
            this->root->path     = "/mnt/e/lala/server/photo/";
            this->root->filename = "hello";
        }
        photomanage(string filename)
        {
            this->root = (photonode*)malloc(sizeof(photonode));
            this->root->next     = nullptr;
            this->root->path     = "/mnt/e/lala/server/photo/";
            this->root->filename = filename;
        }
        void Initphotomanage()
        {
            DIR *dir;
            struct dirent *ptr;
            photonode* next;
            photonode* prev = root;

            if ((dir = opendir("/mnt/e/myproject/else/lala/server/photo")) == NULL) 
            {
                perror("Open dir error...\n");
                return;
            }

            while ((ptr = readdir(dir)) != nullptr) 
            {
                if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    //current dir OR parrent dir
                    continue;
                else                                                                    //file
                {
                    next = (photonode*)malloc(sizeof(photonode));
                    next->filename = ptr->d_name;
                    next->next = nullptr;
                    next->path = "/mnt/e/myproject/else/lala/server/photo";
                    prev->next = next;
                    prev = next;
                } 
            }

            closedir(dir);
        }
        //判断单个文件是否存在，返回路径
        bool getonefile(string &s)
        {
            photonode *val = root;
            while(val != nullptr)
            {
                if(val->filename.compare(s) == 0)
                {
                    s = val->path + val->filename;
                    return true;
                }
                val = val->next;
            }
            cout<<"not found photo: "<<s<<endl;
            return false;
        }
        //获得menu表格
        void getallfile(string &s)
        {
            photonode *val = root;
            s = "------------photomenu-----------------\n";
            while(val != nullptr)
            {
                if(val->filename.compare("hello") == 0)
                {
                    val = val->next;
                    continue;
                }
                s += val->filename;
                s += "\n";
                val = val->next;
            }
            s += "------------photomenu-----------------\n";
        }
        void clearmanage()
        {
            photonode *next;
            while(root != nullptr)
            {
                next = root->next;
                delete(root);
                root = next;
            }
        }
        void dbgmanage()
        {
            photonode *val = root;
            while(val != nullptr)
            {
                cout<<val->filename<<endl;
                val = val->next;
            }
        }
    };
    photomanage photoman;

    photomanage* getphotomanage()
    {
        return &photoman;
    }
};