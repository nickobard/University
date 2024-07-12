#include <ncurses.h>
#include <unistd.h>
#include <vector>

using namespace std;


class CBall {
  public:
    CBall(int x_start, int y_start, int dirX = 1, int dirY = 1)
    : xDir(dirX)
    , yDir(dirY)
    , x(x_start)
    , y(y_start)
    {
      x %= max_x;
      y %= max_y;
    }

    static void setDisplayMax(){
      getmaxyx(stdscr, max_y, max_x);
    }

    void UpdatePhysics(){

      int next_x = 0, next_y = 0;

      next_x = x + xDir;
      next_y = y + yDir;

      if (next_x >= max_x || next_x < 0)
        xDir *= -1;
      else
        x += xDir;

      if (next_y >= max_y || next_y < 0)
        yDir *= -1;
      else
        y += yDir;
  
    }

    void DisplayCoords(){
      mvprintw(3,0,"x: %d, y: %d", x, y);
    }
    void Draw(){
      mvprintw(y,x,"o");
    }
    static int Max_x (){return max_x;};
    static int Max_y (){return max_y;};

  private:
    int xDir, yDir;
    int x, y;
    static int max_y, max_x;
};

int CBall::max_x, CBall::max_y;

#define DELAY 30000
// #define RENDER_DELAY 10000

int main(int argc, char *argv[]) {
 int x = 0, y = 0;
 int max_y = 0, max_x = 0;
 int next_x = 0;
 int next_y = 0;
 int xDirection = 1;
 int yDirection = 1;


 float seconds = 0;
 float deltaTime = ((float) DELAY) / 1000000;

 initscr();
 noecho();
 curs_set(FALSE);

 // Global var `stdscr` is created by the call to `initscr()`
 getmaxyx(stdscr, max_y, max_x);
 CBall::setDisplayMax();
 vector<CBall> balls;
  balls.emplace_back(10,10);
  balls.emplace_back(5,20, 2);
  balls.emplace_back(3,10,1, 2);
  balls.emplace_back(2,50,2,2);


 while(1) {

 getmaxyx(stdscr,max_y,max_x);
 CBall::setDisplayMax();

 clear();
 mvprintw(y, x, "o");
 mvprintw(0,0,"r: %d, c: %d , dT: %.2f, time: %.2f ", max_x, max_y, deltaTime, 
 seconds);
//  mvprintw(1,0,"%d, %d", CBall::Max_x(),CBall::Max_y());
 for ( auto& b : balls)
  b.Draw();
 refresh();
 
 usleep(DELAY);

for (auto& b : balls)
  b.UpdatePhysics();

 seconds += deltaTime;

 next_x = x + xDirection;
 next_y = y + yDirection;

 if (next_x >= max_x || next_x < 0) {
 xDirection *= -1;
 } else {
 x+= xDirection;
 }

 if (next_y >= max_y || next_y < 0)
  yDirection *= -1;
else
  y += yDirection;
 }

 endwin();
}