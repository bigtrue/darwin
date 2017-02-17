#include "../headers/darwin.hpp"
namespace bigtrue
{
	class picture:public darwin::picture
	{
		public:
		using darwin::picture::picture;
		virtual void draw_line(int p0x,int p0y,int p1x,int p1y,const darwin::pixel& pix) override {
		}
	};
}