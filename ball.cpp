#include "ball.h"
#include "snake.h"
#include <cstdlib>
#include <ctime>

SDL_Rect ball = {200, 200, 20, 20};

void toado(int width, int hight) {
     srand(time(0));
     bool trungvoithan = true;
     while (trungvoithan) {
         int u = rand() % (width - 20);
         int v = rand() % (hight - 20);
         // Gán vào quả bóng
         ball.x = u;
         ball.y = v;
         // Mặc định chưa trùng
         trungvoithan = false;
         // Kiểm tra từng đốt của rắn
         for (int i = 0; i < snake.size(); i++) {
             if (ball.x == snake[i].x && ball.y == snake[i].y) {
                 trungvoithan = true;
                 break; // Thoát khỏi vòng lặp kiểm tra
             }
         }
     }
 }

// vẽ quả bóng hình tròn
 void vebong(SDL_Renderer* renderer, SDL_Rect ball) {
     SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
     int bankinh = 10;
     // Vẽ hình tròn bằng cách lặp qua các điểm trên đường tròn
     for (int w = 0; w < bankinh * 2; w++) {
         for (int h = 0; h < bankinh * 2; h++) {
             int dx = bankinh - w; // Di chuyển theo trục x
             int dy = bankinh - h; // Di chuyển theo trục y
             if ((dx * dx + dy * dy) <= (bankinh * bankinh)) {
                 SDL_RenderDrawPoint(renderer, ball.x + dx, ball.y + dy);
             }
         }
     }
 }
