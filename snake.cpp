#include "snake.h"
#include "ball.h"

std::vector<SDL_Rect> snake;

//kiểm tra khi rắn quay đâuf
 bool test_out2(char kitu)
 {
     bool check = true;
     if(kitu == 'r'&&snake[0].x < snake[1].x && snake[0].y == snake[1].y) check = false;
     else if(kitu == 'l' && snake[0].x > snake[1].x && snake[0].y == snake[1].y) check = false;
     else if(kitu == 'u' && snake[0].x == snake[1].x && snake[0].y > snake[1].y) check = false;
     else if(kitu == 'd' && snake[0].x == snake[1].x && snake[0].y < snake[1].y) check = false;
     return check;
 }

//kiểm tra nếu rắn đâm vào thân
 bool test_out3()
 {
     bool check = true;
     int x = snake.size();
     for(int i = 2; i < x; i++)
     {
         if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) check = false;
     }
     return check;
 }

void velai(SDL_Renderer* renderer, SDL_Texture* background) {
     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
     SDL_RenderClear(renderer);
     // Vẽ background
     SDL_RenderCopy(renderer, background, NULL, NULL);

     vebong(renderer, ball); // Gọi hàm vẽ quả bóng hình tròn

     // Vẽ đầu con rắn
     SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
     SDL_RenderFillRect(renderer, &snake[0]);

     //ve thân rắn
     SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
     for(auto i=1;i<snake.size();i++)
     {
         SDL_RenderFillRect(renderer, &snake[i]);
     }

     SDL_RenderPresent(renderer);
 }

void themdot() {
     // Tạo một đốt mới và thêm vào phía đầu con rắn
     SDL_Rect newSegment = {snake.front().x, snake.front().y, 20, 20};
     snake.insert(snake.begin(), newSegment);
 }
