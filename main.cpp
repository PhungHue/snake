#include<bits/stdc++.h>
#include<SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "snake.h"
#include "ball.h"
using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* background;
Mix_Music* eatsound;
const int width = 800;
const int hight = 600;
const int step = 20;

int main(int argc, char* argv[]) {
     // mở sdl
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
         cout << "khong mo duoc thu vien sdl" << SDL_GetError() << endl;
         SDL_Quit();
         return -1;
     }
      // Khởi tạo SDL_image
     if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
         cout << "Không khởi tạo SDL_image: " << IMG_GetError() << endl;
         return -1;
     }
     // Khởi tạo SDL_mixer
     if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
         cout << "Không thể khởi tạo âm thanh: " << Mix_GetError() << endl;
         SDL_Quit();
         return -1;
     }
     // Tải âm thanh MP3
     eatsound = Mix_LoadMUS("eatsound.mp3");
     if (eatsound == NULL) {
         cout << "Không thể tải âm thanh: " << Mix_GetError() << endl;
         return -1;
     }
      // mở cửa sổ win
     window = SDL_CreateWindow("rắn săn mồi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, hight, SDL_WINDOW_SHOWN);
     if (window == NULL) {
         cout << "khong mo duoc cua so win" << SDL_GetError() << endl;
         SDL_Quit();
     }
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
     if (!renderer) {
         cout << "Không tạo được renderer: " << SDL_GetError() << endl;
         return -1;
     }
       // Tải background image
     background = IMG_LoadTexture(renderer, "background.png"); // Đảm bảo bạn có tệp background.png
     if (background == NULL) {
         cout << "Không thể tải background: " << IMG_GetError() << endl;
         SDL_Quit();
         return -1;
     }
     SDL_Surface* tempSurface = IMG_Load("background.png");
     if (!tempSurface) {
         cout << "Không load được ảnh nền: " << IMG_GetError() << endl;
         return -1;
     }

     background = SDL_CreateTextureFromSurface(renderer, tempSurface);
     SDL_FreeSurface(tempSurface);
     if (!background) {
         cout << "Không tạo được texture từ ảnh nền: " << SDL_GetError() << endl;
         return -1;
     }

     // bắt sự kiện ttuwf bàn phím
     SDL_Event e;
     bool quit = false;//rời sdl
     bool check1 = true;//kiểm tra nếu rán đâm vào tường
     char kitu = 'r';

     toado(width, hight);
     snake.push_back({0, hight / 2 - 10, 20, 20}); // Thêm đốt ban đầu vào con rắn
    // Tạo đốt ban đầu cho con rắn
     snake.push_back({0, hight / 2 - 10, 20, 20});
     snake.push_back({0, hight / 2, 20, 20});
     snake.push_back({0, hight / 2 + 10, 20, 20});


     //ve qua bong
     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
     SDL_RenderFillRect(renderer, &ball);
     SDL_RenderPresent(renderer);

     // vòng lặp tắt cửa sổ
     while (!quit) {
         while (SDL_PollEvent(&e) != 0) {
             if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Q)) {
                 quit = true;
             }
             // xử lý sự kiện phím
             if (e.type == SDL_KEYDOWN) {
                 switch (e.key.keysym.sym) {
                     case SDLK_LEFT:
                         kitu = 'l';
                         break;
                     case SDLK_RIGHT:
                         kitu = 'r';
                         break;
                     case SDLK_UP:
                         kitu = 'u';
                         break;
                     case SDLK_DOWN:
                         kitu = 'd';
                         break;
                 }
                 if (!check1) break;
             }
         }
         bool check2 = test_out2(kitu);
         bool check3 = test_out3();
         if (!check1 || !check2 || !check3) {
             cout << "game over!\n";
             break;
         }
         //di chuyển con rắn
         if (kitu == 'r') {
             if (snake.front().x >= width - 20) check1 = false;
             else {
                 for (int i = snake.size() - 1; i > 0; --i) {
                     snake[i].x = snake[i - 1].x;
                     snake[i].y = snake[i - 1].y;
                 }
                 snake.front().x += step; // Di chuyển phần đầu của con rắn
             }
         }
         else if (kitu == 'l') {
             if (snake.front().x <= 0) check1 = false;
             else {
                 for (int i = snake.size() - 1; i > 0; --i) {
                     snake[i].x = snake[i - 1].x;
                     snake[i].y = snake[i - 1].y;
                 }
                 snake.front().x -= step; // Di chuyển phần đầu của con rắn
             }
         }
         else if (kitu == 'u') {
             if (snake.front().y <= 0) check1 = false;
             else {
                 for (int i = snake.size() - 1; i > 0; --i) {
                     snake[i].x = snake[i - 1].x;
                     snake[i].y = snake[i - 1].y;
                 }
                 snake.front().y -= step; // Di chuyển phần đầu của con rắn
             }
         }
         else {
             if (snake.front().y >= hight - 20) check1 = false;
             else {
                 for (int i = snake.size() - 1; i > 0; --i) {
                     snake[i].x = snake[i - 1].x;
                     snake[i].y = snake[i - 1].y;
                 }
                 snake.front().y += step; // Di chuyển phần đầu của con rắn
             }
         }

         // Kiểm tra nếu con rắn ăn được quả bóng
         if ((snake.front().x >= ball.x - 20 && snake.front().x <= ball.x + 20) &&
             (snake.front().y >= ball.y - 20 && snake.front().y <= ball.y + 20)) {
             toado(width, hight);
             themdot(); // Thêm một đốt mới vào con rắn
             // Phát âm thanh khi con rắn ăn bóng
             Mix_PlayMusic(eatsound, 1);  // 1 có nghĩa là phát nhạc chỉ một lần
         }

         SDL_Delay(150);
         velai(renderer, background); // Vẽ con rắn
     }
     // Giải phóng tài nguyên
     Mix_FreeMusic(eatsound);
     Mix_CloseAudio();
     SDL_DestroyTexture(background);
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();
     return 0;
 }
