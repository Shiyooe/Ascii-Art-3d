#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24
#define TRAILS 20

typedef struct {
    int x;
    int y;
    int speed;
    int length;
} Drop;

int main() {
    srand(time(NULL));
    Drop drops[TRAILS];
    char screen[HEIGHT][WIDTH];
      
    for (int i = 0; i < TRAILS; i++) {
        drops[i].x = rand() % WIDTH;
        drops[i].y = -(rand() % HEIGHT);
        drops[i].speed = 1 + rand() % 3;
        drops[i].length = 5 + rand() % 10;
    }
    
    printf("\x1b[2J\x1b[?25l"); 
    
    while (1) {
       
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                screen[i][j] = ' ';
            }
        }
        
        
        for (int i = 0; i < TRAILS; i++) {
            drops[i].y += drops[i].speed;
            
            
            if (drops[i].y - drops[i].length > HEIGHT) {
                drops[i].y = -(rand() % 10);
                drops[i].x = rand() % WIDTH;
                drops[i].speed = 1 + rand() % 3;
            }
            
           
            for (int j = 0; j < drops[i].length; j++) {
                int y = drops[i].y - j;
                if (y >= 0 && y < HEIGHT) {
                    
                    char chars[] = "01!@#$%^&*()_+-=[]{}|;:,.<>?ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                    char c = chars[rand() % (sizeof(chars) - 1)];
                    
                    
                    if (j == 0) {
                        screen[y][drops[i].x] = c; 
                    } else if (j < drops[i].length / 2) {
                        screen[y][drops[i].x] = c; 
                    } else {
                        screen[y][drops[i].x] = '.'; 
                    }
                }
            }
        }
      
        printf("\x1b[H");
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (screen[i][j] != ' ') {
                    printf("\x1b[32m%c\x1b[0m", screen[i][j]); // Green
                } else {
                    putchar(' ');
                }
            }
            putchar('\n');
        }
        
        usleep(50000); 
    
    printf("\x1b[?25h"); 
    return 0;
}
