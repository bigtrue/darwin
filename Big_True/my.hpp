#include "../headers/darwin.hpp"
#include <algorithm>
namespace bigtrue
{
	class picture:public darwin::picture
	{
		public:
		picture():darwin::picture(){}
		virtual void draw_line(int x1,int y1,int x2,int y2,const darwin::pixel& pix) override {
			long double k=(y1-y2)/(x1-x2+1e-10);
			long double b=(x1*y2-x2*y1)/(x1-x2+1e-10);
			if(k>=-1 and k<=1){
				for(int x=std::min(x1,x2);x<=std::max(x1,x2);x++){
					int y=k*x+b;
					this->draw_pixel(x,y,pix);
				}
			}
			else{
				for(int y=std::min(y1,y2);y<=std::max(y1,y2);y++){
					int x=(y-b)/k;
					this->draw_pixel(x,y,pix);
				}
			}
		}
	};
}
