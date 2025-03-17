#include <stdio.h>
#include <stdlib.h>

unsigned int board[8][8];

struct pieces {
  char color[6];
  char type;
  int type_int;
  int x,y;
};

int initialize_board(int board[][8],struct pieces black[],struct pieces white[]){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++);
    //don't like the implementation
      
  
}
}

int main(){
    struct pieces black[16];
    struct pieces white[16];

    black[0].x=0;
    black[0].y=0;
    black[0].type='r';
    black[0].type_int=1;
  
    board[black[0].x][black[0].y]=black[0].type_int;

    for(int i=0;i<8;i++){
      printf("\n");
      for(int j=0;j<8;j++){
        printf("%d ",board[i][j]);
      }
    }

    return 0;
}