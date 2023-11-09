g++ main.cpp -o main -lpthread
echo "hello"

#--------------------------------------------------
# 1. install nginx
#--------------------------------------------------
# sudo apt install wget gcc pcre-devel zlib-devel
# wget http://nginx.org/download/nginx-1.16.0.tar.gz ./nginx-1.16.0.tar.gz
# tar xf nginx-1.16.0.tar.gz
# cd nginx-1.16.0
# ./configure --prefix=/usr/local
# make -j 4
# make install
# rm -r ./nginx-1.16.0.tar.gz
# rm -r ./nginx-1.16.0
echo "end 1"
echo 

#--------------------------------------------------
#2. shell 特殊字符
#--------------------------------------------------
# cd ~   #返回根目录
# cd /   #返回家目录
# cd -   #返回上一级目录
# # sleep 1ms
# expr 3 \* 3
# pwd
# name=5
# echo $name + 1
# cd /mnt/e/myproject/else/lala/server
# cat ./main.cpp | grep "server"
# echo -e "ded \c"
# echo "123"
echo "end 2"
echo 

#--------------------------------------------------
#3. shell 颜色
#--------------------------------------------------
# echo -e "\033[39;37m 大家好 \033[0m"

echo "end 3"
echo 

#--------------------------------------------------
#4. shell 输入
#--------------------------------------------------
#read uniname
#echo uniname: $uniname
#read -s -t50 -n6 write
#echo write: $write
#echo "end 3"
#echo 
#clear

#--------------------------------------------------
#4. 变量
#--------------------------------------------------
