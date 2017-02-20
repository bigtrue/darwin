#define DARWIN_FORCE_BUILTIN
#include "./headers/darwin.hpp"
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
int s=10;
int x=1;
int y=1;
int x1=0;
int x2=0;
int yy1=0;
int y2=0;
std::vector<int> board(s*s);
bool pd2(long xx1,long yy1,long xx2,long yy2){
	if(xx1==xx2 and yy1==yy2) return true;
	else if(xx1==xx2){
		for(long ls2=std::min(yy1,yy2)+1;ls2<std::max(yy1,yy2);ls2++){
			if(board[(ls2-1)*s+xx1-1]!=0) return false;
		}
		return true;
	}
	else if(yy1==yy2){
		for(long ls2=std::min(xx1,xx2)+1;ls2<std::max(xx1,xx2);ls2++){
			if(board[(yy1-1)*s+ls2-1]!=0) return false;
		}
		return true;
	}
	else return (pd2(xx1,yy1,xx1,yy2) and pd2(xx1,yy2,xx2,yy2) and board[(yy2-1)*s+xx1-1]==0) or (pd2(xx1,yy1,xx2,yy1) and pd2(xx2,yy2,xx2,yy1) and board[(yy1-1)*s+xx2-1]==0);
}
bool pd3(long xx1,long yy1,long xx2,long yy2){
	if(xx1==xx2 or yy1==yy2){
		return pd2(xx1,yy1,xx2,yy2);
	}
	for(long ls=0;ls<s;ls++){
		if(pd2(ls,yy1,xx2,yy2) and pd2(ls,yy1,xx1,yy1)){
			if(ls==xx2){
				return pd2(xx1,yy1,xx2,yy2);
			}
			return true;
		}
		else if(pd2(xx1,ls,xx2,yy2) and pd2(xx1,ls,xx1,yy1)){
			if(ls==yy2){
				return pd2(xx1,yy1,xx2,yy2);
			}
			return true;
		}
	}
	return false;
}
void pd(){
	if(pd3(x1,yy1,x2,y2) and !(x1==x2 and yy1==y2) and board[(yy1-1)*s+x1-1]==board[(y2-1)*s+x2-1]){
		board[(yy1-1)*s+x1-1]=0;
		board[(y2-1)*s+x2-1]=0;
	}
}
darwin::colors tocolor(int ls){
	switch(ls){
		case 0:return darwin::colors::black;
		case 1:return darwin::colors::blue;
		case 2:return darwin::colors::red;
		case 3:return darwin::colors::green;
		case 4:return darwin::colors::cyan;
		case 5:return darwin::colors::pink;
		case 6:return darwin::colors::yellow;
	}
}
void newa(){
	std::default_random_engine e1(time(nullptr));
	std::default_random_engine e2(time(nullptr)+100);
	std::vector<int> board2(s*s);
	board=board2;
	int ls=s*s;
	int lscolor=1;
	x=1;
	y=1;
	x1=0;
	x2=0;
	yy1=0;
	y2=0;
	std::uniform_int_distribution<int> ra(1,s);
	while(ls>1){
		int lsx=ra(e1);
		int lsy=ra(e2);
		if(board[(lsy-1)*s+lsx-1]==0){
			int lsx2=ra(e1);
			int lsy2=ra(e2);
			if(board[(lsy2-1)*s+lsx2-1]==0 and !(lsx2==lsx and lsy2==lsy)){
				board[(lsy-1)*s+lsx-1]=lscolor;
				board[(lsy2-1)*s+lsx2-1]=lscolor;
				ls=ls-2;
				if(lscolor==6) lscolor=1;
				else lscolor++;
			}
		}
	}
}
int main()
{
	darwin::runtime.load("./darwin.module");
	auto adapter=darwin::runtime.get_adapter();
	auto pic=darwin::runtime.get_drawable();
	pic->resize(s*2+4,s*2+4);
	darwin::sync_clock clock(20);
	while(true) {
		clock.reset();
		{
			if(adapter->is_kb_hit()) {
				switch(adapter->get_kb_hit()) {
				case 'w':
					if(y>1) y=y-1;
					break;
				case 's':
					if(y<s) y=y+1;
					break;
				case 'a':
					if(x>1) x=x-1;
					break;
				case 'd':
					if(x<s) x=x+1;
					break;
				case 'n':
					board[(y-1)*s+x-1]=1;
					break;
				case 'r':
					newa();
					break;
				case 'l':
					if(yy1==0){
						x1=x;
						yy1=y;
					}
					else if(y2==0){
						x2=x;
						y2=y;
						pd();
						x1=0;
						x2=0;
						yy1=0;
						y2=0;
					}
					break;
				}
			}
			for(int ls1=1;ls1<s+1;ls1++){
				for(int ls2=1;ls2<s+1;ls2++){
					pic->draw_pixel(ls2*2,ls1,darwin::pixel(' ',false,false,darwin::colors::white,tocolor(board[(ls1-1)*s+ls2-1])));
					pic->draw_pixel(ls2*2+1,ls1,darwin::pixel(' ',false,false,darwin::colors::white,tocolor(board[(ls1-1)*s+ls2-1])));
				}
			}
			if(yy1>0){
				pic->draw_pixel(x1*2,yy1,darwin::pixel('#',false,false,darwin::colors::white,tocolor(board[(yy1-1)*s+x1-1])));
				pic->draw_pixel(x1*2+1,yy1,darwin::pixel('#',false,false,darwin::colors::white,tocolor(board[(yy1-1)*s+x1-1])));
			}
			pic->draw_pixel(x*2,y,darwin::pixel('@',false,false,darwin::colors::white,tocolor(board[(y-1)*s+x-1])));
			pic->draw_pixel(x*2+1,y,darwin::pixel('@',false,false,darwin::colors::white,tocolor(board[(y-1)*s+x-1])));
		}
		darwin::runtime.update_drawable();
		clock.sync();
	}
	return 0;
}
/*
pic->draw_pixel(x,y,pix);
pic->draw_line(x1,y1,x2,y2,pix);
pic->draw_picture(x,y,picture);
darwin::pixel pix('',light_bool,down_line_bool,back_color_darwin::colors::look_next_line,front_color_darwin::colors::look_next_line)
look_next_line:black,white,blue,red,green,cyan,pink,yellow
*/
