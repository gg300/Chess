#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BACKGROUND_WHITE "\x1b[47m"   /////define colors
#define BACKGROUND_BLACK "\x1b[40m"
#define RESET_ALL "\x1b[0m"
#define TEXT_COLOR  "\x1b[39m"
#define STYLE_BOLD "\x1b[1m"
int board[8][8];

/// setup 0 = > white is down
/// setup 1 = > black is down

struct pieces {
  char color[6];
  char type;
  int type_int;
  int x,y;
  bool is_onboard;
};
struct pieces no_piece={  /// used as an error 
  .color="no",
  .type='n',
  .type_int=-1,
  .x=-1,
  .y=-1,
  .is_onboard=false
};

void initialize_board(int board[][8],struct pieces black[],struct pieces white[],int setup){ // done
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
    
      if(setup==0){
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
      
        if(setup==0){
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

void show(int board[][8],struct pieces black[],struct pieces white[]){ //rudimentary done
  printf("   ");
  for(int i=0;i<9;i++)
  printf("= ");
  for(int i=0;i<8;i++){
    printf("\n %d |",i+1); // draw left margin
    for(int j=0;j<8;j++){
      int is_piece = 0;
      for(int k=0;k<16;k++){
        printf(TEXT_COLOR STYLE_BOLD);
        if((i+j)%2==0)
        {
          printf(BACKGROUND_BLACK);
        }
        else
        {
          printf(BACKGROUND_WHITE);
        }
        if((i==black[k].x) && (black[k].y==j)){
          is_piece=1;
          printf("%c ",black[k].type);
          break;  
        }
        else{
          if((i==white[k].x) && (white[k].y==j))
          {
            printf("%c ",white[k].type-32);  /// white is upper yet
            is_piece=1;
              break;
          }  
        }
      }
        if(is_piece==0){
          if((i+j)%2==0)
            printf(BACKGROUND_BLACK"  ");
          else
            printf(BACKGROUND_WHITE"  ");
          }
        printf(RESET_ALL);
    }
    
    printf("|");  // draw right margin
  }
  printf("\n");
  printf("   ");
  for(int i=0;i<9;i++) printf("= "); // draw down margin
  printf("\n");

  printf("    ");
  for(int i=0;i<8;i++)  //draw x axis
    printf("%c ",'a'+i);
}

struct pieces* find_piece (int x, int y, int board[][8],struct pieces black[],struct pieces white[]){
  for(int i=0;i<16;i++){
    if(x==black[i].x && y==black[i].y)
      return &black[i];
    if(x==white[i].x && y==white[i].y)
      return &white[i];
  }
    printf("Piece Not Found");
    return &no_piece;
}

void show_int_board(int board[][8]){ //done
  for(int i=0;i<8;i++){
    printf("\n");
    for(int j=0;j<8;j++){
      printf("%d ",board[i][j]);
    }
  }
 }

bool is_clear_path(struct pieces piece,int x, int y,int board[][8]){ // to do

  return true;
}

bool is_same_color(struct pieces my_piece,struct pieces found_piece){ // to do
  if (strcmp(my_piece.color,found_piece.color)==0)
    return true;
  return false;
}

void out_of_board(struct pieces* piece){
  board[piece->x][piece->y]=0;
  piece->is_onboard = false;
  piece->x=-1;
  piece->y=-1;

}

bool is_valid_path(){
  // path isn't valid if path isn't clear or the piece is the same color;
  return true;
}
bool is_valid_move(struct pieces piece,int x, int y,int board[][8],int setup){ //ocupied spaces not verified yet
  if(x<0||x>7||y<0||y>7)
    return false;

  if(piece.type=='p'){ // 1
    if(setup==0){
      if(piece.color[0]=='w'){
        if(piece.x-1==x && piece.y==y)
          return true;
        else
          if(piece.x==6 && piece.y==y)
            if(piece.x-2==x && piece.y==y)
              return true;
      }
      else{
        if(piece.x+1==x && piece.y==y)
          return true;
        else
          if(piece.x==1 && piece.y==y)
            if(piece.x+2==x && piece.y==y)
              return true;
}
    }
    else{
        if(piece.color[0]=='w'){
          if(piece.x+1==x)
            return true;
          else
            if(piece.x==1)
              if(piece.x+2==x)
                return true;
        }
        else{
          if(piece.x-1==x)
            return true;
          else
            if(piece.x==6)
              if(piece.x-2==x)
                return true;
        }
      }
      return false;

  }
  if(piece.type=='b'){  // 2
    for(int i=0;i<8;i++){
      if((piece.x+i==x && piece.y+i==y) || (piece.x-i==x && piece.y-i==y))
          return true;
      if ((piece.x + i == x && piece.y - i == y) || (piece.x - i == x && piece.y + i == y))
        return true;
    }
    return false;
  }
  if(piece.type=='h'){ // 3
    if(((piece.x+2==x) && (piece.y+1==y)) || ((piece.x+2==x) && (piece.y-1==y)) || ((piece.x-2==x) && (piece.y-1==y)) || ((piece.x-2==x) && (piece.y+1==y)))
      return true;
    if(((piece.x+1==x) && (piece.y+2==y)) || ((piece.x+1==x) && (piece.y-2==y)) || ((piece.x-1==x) && (piece.y-2==y)) || ((piece.x-1==x) && (piece.y+2==y)))
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
  if(piece.type=='q'){ // 5   rook + bishop
    for(int i=0;i<8;i++){
      if((piece.x+i==x && piece.y+i==y) || (piece.x-i==x && piece.y-i==y))
        return true;
      if ((piece.x + i == x && piece.y - i == y) || (piece.x - i == x && piece.y + i == y))
        return true;
      if((piece.x+i==x && piece.y==y) || (piece.y+i==y && piece.x==x) || (piece.x-i==x && piece.y==y) || (piece.x==x && piece.y-i==y))
        return true;
    }
    return false;
  }
  if(piece.type=='k'){ // 6 to do
    if((piece.x+1==x && piece.y+1==y) || ((piece.x+1==x) && (piece.y-1==y)) || ((piece.x+1==x) && (piece.y==y)))
      return true;
    if((piece.x-1==x && piece.y+1==y) ||((piece.x-1==x) && (piece.y-1==y)) || ((piece.x-1==x) && (piece.y==y)))
      return true;
    if((piece.x==x && piece.y-1==y) || (piece.x==x && piece.y+1==y))
      return true;
    return false;
  }
  printf("%d %d",piece.x,piece.y);
  return false;
}

int convert_to_tablemove(char input){
  if(isalpha(input))
    return toupper(input)-'A';
  if(isdigit(input))
    return input-'0'-1;
  return -1;
}

void parse_move(char move[],int *x, int *y){
  *x=convert_to_tablemove(move[1]);    /// move[1] in chess represents the x axis
  *y=convert_to_tablemove(move[0]);    /// move[0] for y axis
  return;
}

int main(){
    int setup=0;
   int x=2,y=5;
  //  int p=6;
    struct pieces black[16];
    struct pieces white[16];
    initialize_board(board,black,white,setup);
    show(board,black,white);
    printf("\nWrite moves like <piece> <position> \"ex\" to exit\n");

    printf("\n");
    while(true){
      char piece_selector[3],move[3];   
     
      scanf("%s %s",piece_selector,move);
      
      if((strcmp(piece_selector,"ex")==0) ||  (strcmp(move,"ex")==0))
        break;
      parse_move(piece_selector,&x,&y);
      struct pieces *piece= find_piece(x,y,board,black,white),*found_piece=NULL;
      // printf("%d%d",piece->x,piece->y);
      parse_move(move,&x,&y);
        if(board[x][y]!=0)
          {
            found_piece = find_piece(x,y,board,black,white);
          }
      /// TO DO !!!

      // find if space is clear then do is move clear
      
      //otherwise 
      // find other piece first  find(piece)

      // if is_valid_move && !is_same_color => out of the board with the other piece first

      if(is_valid_move(*piece,x,y,board,setup)){   /// test
        if(board[x][y]!=0){
          out_of_board(found_piece);
        }

        board[piece->x][piece->y]=board[x][y];
        board[x][y]=piece->type_int;
        piece->x=x;
        piece->y=y;


        show(board,black,white);
        printf("\n");
        printf("Write moves like <piece> <position> or \"ex\" to exit\n");
       //  show_int_board(board);
      } 
      else{
        printf("Invalid move\n");
      }
    }

    return 0;
}