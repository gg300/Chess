#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
unsigned int board[8][8];

struct pieces {
  char color[6];
  char type;
  int type_int;
  int x,y;
};

void initialize_board(unsigned int board[][8],struct pieces black[],struct pieces white[],int player){
  for(int i=0;i<16;i++){
    strcpy(black[i].color,"black");
    strcpy(white[i].color,"white");
    if(i==0 || i==7){
      black[i].type_int=4;
      white[i].type_int=4;
      black[i].type='r';
      white[i].type='r';
    }
    if(i==1 || i==6){
      black[i].type_int=3;
      white[i].type_int=3;
      black[i].type='h';
      white[i].type='h';      
    }
    if(i==2 || i==5){
      black[i].type_int=2;
      white[i].type_int=2;
      black[i].type='b';
      white[i].type='b';        
    }
    if(i==3){
      black[i].type_int=5;
      white[i].type_int=5;
      black[i].type='q';
      white[i].type='q';        
    }
    if(i==4){
      black[i].type_int=6;
      white[i].type_int=6;
      black[i].type='k';
      white[i].type='k';
    }

    if(i>7){
      black[i].type_int=1;
      white[i].type_int=1;
      black[i].type='p';
      white[i].type='p';
    }
    if(i<8){
    
      if(player==0){
        board[0][i]=black[i].type_int;
        board[7][i]=white[i].type_int;
        black[i].x=0;
        black[i].y=i;
        white[i].x=7;
        white[i].y=i;
      }
      else{
        board[7][i]=black[i].type_int;
        board[0][i]=white[i].type_int;
        black[i].x=7;
        black[i].y=i;
        white[i].x=0;
        white[i].y=i;
      }
    }
    else{
      
        if(player==0){
          board[1][i-8]=black[i].type_int;
          board[6][i-8]=white[i].type_int;
          black[i].x=1;
          black[i].y=i-8;
          white[i].x=6;
          white[i].y=i-8;
        }
      else{
        board[6][i-8]=black[i].type_int;
        board[1][i-8]=white[i].type_int;
        black[i].x=6;
        black[i].y=i-8;
        white[i].x=1;
        white[i].y=i-8;
      }
    }
  }
}

void show(unsigned board[][8],struct pieces black[],struct pieces white[]){
  for(int i=0;i<8;i++){
    printf("\n");
    for(int j=0;j<8;j++){
      int is_piece = 0;
      for(int k=0;k<16;k++){
        if((i==black[k].x) && (black[k].y==j)){
          is_piece=1;
          printf("%c ",black[k].type);
          break;  
        }
        else{
          if((i==white[k].x) && (white[k].y==j))
          {
            printf("%c ",white[k].type);
            is_piece=1;
              break;
          }  
        }
      }
        if(is_piece==0){

          if((i+j)%2==0)
            printf("%c ", ' ');
          else
            printf("%c ", '#');
          }
    }
  }
}

void show_int_board(unsigned board[][8]){
  for(int i=0;i<8;i++){
    printf("\n");
    for(int j=0;j<8;j++){
      printf("%d ",board[i][j]);
    }
  }
 }
int is_valid_move(struct pieces piece,int x, int y,unsigned board[][8]){ //ocupied spaces not verified yet
  if(x<0||x>7||y<0||y>7)
    return false;


  if(piece.type=='p'){ // 1
    return 1;
  }
  if(piece.type=='b'){  // 2
    for(int i=0;i<8;i++){
      if((piece.x+i==x && piece.y+i==y) || (piece.x-i==x && piece.y-i==y))
          return true;
//      if(piece.x+i==x && piece.y)
    }
    return 2;
  }
  if(piece.type=='h'){ // 3
    if(((piece.x+2==x) && (piece.y+1==y)) || ((piece.x+2==x) && (piece.y-1==y)) || ((piece.x-2==x) && (piece.y-1==y)) || ((piece.x-2==x) && (piece.y+1==y)))
      return true;
    return false;
  }
  if(piece.type=='r'){ // 4
    for(int i=0;i<8;i++)
      if((piece.x+i==x && piece.y==y) || (piece.y+i==y && piece.x==x) || (piece.x-i==x && piece.y==y) || (piece.x==x && piece.y-i==y))
         return true;
//    printf("%d%d ",piece.x,piece.y);
    return false;
  }
  if(piece.type=='q'){ // 5
    return 5;
  }
  if(piece.type=='k'){ // 6
    return 6;
  }

  return false;
}



int main(){
    int player=0;
    struct pieces black[16];
    struct pieces white[16];
    initialize_board(board,black,white,player);
    printf("%d",is_valid_move(white[2],6,1,board));
//    show(board,black,white);
    show_int_board(board);
    return 0;
}