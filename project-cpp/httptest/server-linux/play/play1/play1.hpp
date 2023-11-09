#include <iostream>
#include <string>
using namespace std;

namespace player1
{
	class play
	{
	private:
		int iv[3][3];

	public:
		play()
		{
			memset(iv, 0, sizeof(iv));
		}
        void init()
        {
            memset(iv, 0, sizeof(iv));
        }
		bool update(int x, int y, int val)
		{
            if(x>=3 || x<0 || y>=3 || y<0)
            {
                return false;
            }
			if (iv[x][y] == 0)
			{
				iv[x][y] = val;
				return true;
			}
			else return false;
		}
		void clear()
		{
			memset(iv, 0, sizeof(iv));
		}
		bool iswin(int val)
		{
			for (int x = 0; x < 3; x++)
			{
				if ((iv[x][0] == iv[x][1]) && (iv[x][1] == iv[x][2]) && (iv[x][0] == val))
				{
					return true;
				}
                if ((iv[0][x] == iv[1][x]) && (iv[1][x] == iv[2][x]) && (iv[0][x] == val))
				{
					return true;
				}
			}
			if (iv[0][0] == iv[1][1] && iv[1][1] == iv[2][2] && iv[1][1] == val)
			{
				return true;
			}
			if (iv[0][2] == iv[1][1] && iv[2][0] == iv[1][1] && iv[1][1] == val)
			{
				return true;
			}
			return false;
		}
		void getstr(string &s)
		{
			s.clear();
			s += "-------\n";
			for (int i = 0; i < 3; i++)
			{
				s += "|";
				for (int j = 0; j < 3; j++)
				{
					s += '0' + iv[i][j];
					s += "|";
				}
				s += "\n";
				s += "-------\n";
			}
		}
	};
	static play play1;
	play* getplayer1()
	{
		return &play1;
	}
};


