#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

class FileUtil
{
private:
	std::string filepath;
public:
	FileUtil(const std::string &filename) :filepath(filename) {}
	bool Read(std::string *body)
	{
		std::ifstream ifs;
		ifs.open(filepath, std::ios::binary);
		if (ifs.is_open() == false)
		{
			perror("open is false\n");
			return false;
		}
		ifs.seekg(0, std::ios::end);
		size_t fsize = ifs.tellg();
		ifs.seekg(0, std::ios::beg);
		body->resize(fsize);
		ifs.read(&(*body)[0], fsize);
		if (ifs.good() == false)
		{
			std::cout << "read file false\n" << std::endl;
			ifs.close();
			return false;
		}
		ifs.close();
		return true;
	}


	bool Write(const std::string &body)
	{
		std::ofstream ofs;

		ofs.open(filepath, std::ios::binary);
		if (ofs.is_open() == false)
		{
			perror("open is false\n");
			return false;
		}
		ofs.write(body.c_str(), body.size());
		if (ofs.good() == false)
		{
			std::cout << "write false\n" << std::endl;
			ofs.close();
			return false;
		}
		ofs.close();
		return true;
	}
};