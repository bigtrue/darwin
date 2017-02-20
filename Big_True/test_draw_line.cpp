#define DARWIN_FORCE_BUILTIN
#include "./my.hpp"
#include <ctime>
int main()
{
	darwin::runtime.load("./darwin.module");
	auto pic=darwin::runtime.get_drawable();
	auto adapter=darwin::runtime.get_adapter();
	darwin::sync_clock clock(30);
	darwin::runtime.fit_drawable();
	bigtrue::picture img;
	img.resize(pic->get_width(),pic->get_height());
	int x0(0),y0(0),x1(1),yy1(1);
	long long ttime=time(nullptr);
	while(true) {
		if(adapter->is_kb_hit()) {
			switch(adapter->get_kb_hit()) {
			case 'w':
				--y0;
				break;
			case 's':
				++y0;
				break;
			case 'a':
				--x0;
				break;
			case 'd':
				++x0;
				break;
			case 'i':
				--yy1;
				break;
			case 'k':
				++yy1;
				break;
			case 'j':
				--x1;
				break;
			case 'l':
				++x1;
				break;
			case 'c':
				darwin::print_screen();
				break;
			}
		}
		clock.reset();
		darwin::runtime.fit_drawable();
		img.clear();
		img.draw_line(x0,y0,x1,yy1,darwin::pixel('@',true,false,darwin::colors::blue,darwin::colors::white));
		pic->draw_picture(0,0,img);
		darwin::runtime.update_drawable();
		if(time(nullptr)-ttime>60){
			darwin::runtime.exit();
		}
		clock.sync();
	}
	return 0;
}
