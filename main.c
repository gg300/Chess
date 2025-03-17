#include <stdio.h>
#include <stdlib.h>

unsigned int board[8][8];

struct pieces {
  char type;
  char color[6];
};

int main(){
    struct pieces black[2][8];
    struct pieces white[2][8];
    for(int i=0;i<8;i++){
      printf("\n");
      for(int j=0;j<8;j++){
        printf("%d ",board[i][j]);
      }
    }

    return 0;
}