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

  printf("\n");
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

bool is_same_color(struct pieces* my_piece,struct pieces* found_piece){
  if(found_piece==NULL)
    return false;
  if (strcmp(my_piece->color,found_piece->color)==0)
    return true;
  return false;
}

void out_of_board(struct pieces* piece){
  board[piece->x][piece->y]=0;
  piece->is_onboard = false;
  piece->x=-1;
  piece->y=-1;

}

bool is_space_clear(int x,int y,int board[][8]){
  if(board[x][y]==0)
    return true;
  return false;
}

bool rook_valid_path(struct pieces piece,int x, int y,int board[][8]){
  int px=piece.x,py=piece.y;
    if(piece.x!=x && piece.y==y){
      if(px<x)
      while(px!=x-1){
        px++;
        if(!is_space_clear(px,py,board))
          return false;
      }
      else
      while(px!=x+1){
        px--;
        if(!is_space_clear(px,py,board))
          return false;
      }
    }
    if(py!=y && piece.x==x){
      if(py<y)
      while(py!=y-1){
        py++;
        if(!is_space_clear(px,py,board))
          return false;
      }
      else
      while(py!=y+1){
        py--;
        if(!is_space_clear(px,py,board))
          return false;
      }
    
  }
  return true;
}
bool bishop_valid_path(struct pieces piece,int x, int y,int board[][8]){
  int px=piece.x,py=piece.y;
  if((px<x) && (py<y)){ // move down the principal diagonal
    while(px!=x-1 || py!=y-1){
      px++;
      py++;
      if(!is_space_clear(px,py,board))
        return false;
    }
    if(px!=x-1 || py!=y-1)
      return false;
  }

  if((px>x) && (py>y)){ // move up the principal diagonal
    while(px!=x+1 || py!=y+1){
      px--;
      py--;
      if(!is_space_clear(px,py,board))
        return false;
    }
    if(px!=x+1 || py!=y+1)
      return false;
  }

  if((px<x) && (py>y)){// move down the second diagonal
    while(px!=x-1 || py!=y+1){
      px++;
      py--;
      if(!is_space_clear(px,py,board))
        return false;
    }
    if(px!=x-1 || py!=y+1)
      return false;
  }
  if((px>x) && (py<y)){// move down the second diagonal
    while(px!=x+1 || py!=y-1){
      px--;
      py++;
      if(!is_space_clear(px,py,board))
        return false;
    }
    if(px!=x+1 || py!=y-1)
      return false;
  }


  return true;
}

bool is_valid_path(struct pieces piece,int x, int y,int board[][8],int setup){ ///king moves to do

  // int px=piece.x,py=piece.y;
  
  if(piece.type=='r'){
    return rook_valid_path(piece,x,y,board);
  }
  if(piece.type=='b'){
    return bishop_valid_path(piece,x,y,board);    
  }
  if(piece.type=='q'){
    return bishop_valid_path(piece,x,y,board) && rook_valid_path(piece,x,y,board);
  }
  if(piece.type=='p'){
    return rook_valid_path(piece,x,y,board);
  }

  return true;
}
bool is_valid_space(struct pieces piece,int x, int y,int board[][8],int setup){ //ocupied spaces not verified yet
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
bool is_valid_move(struct pieces piece,int x, int y,int board[][8],int setup){
  if(is_valid_path(piece,x,y,board,setup) && is_valid_space(piece,x,y,board,setup))
    return true;
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

bool check(struct pieces king, struct pieces black[], struct pieces white[], int board[][8], int setup) {
  struct pieces *enemy_pieces;
  int enemy_count = 16;
  
  if (strcmp(king.color, "white") == 0) {
      enemy_pieces = black;
  } else {
      enemy_pieces = white;
  }
  
  for (int i = 0; i < enemy_count; i++) {
      if (enemy_pieces[i].is_onboard) {
          if (is_valid_move(enemy_pieces[i], king.x, king.y, board, setup)) {
              return true; // King is in check
          }
      }
  }
  return false; // King is safe
}

struct pieces* find_king(struct pieces pieces[]) {
  for (int i = 0; i < 16; i++) {
      if (pieces[i].type == 'k') {
          return &pieces[i];
      }
  }
  return NULL;
}

bool is_king_in_check(struct pieces black[], struct pieces white[], int board[][8], int setup) {
  struct pieces *white_king = find_king(white);
  struct pieces *black_king = find_king(black);
  
  if (white_king && check(*white_king, black, white, board, setup)) {
      printf("White king is in check!\n");
      return true;
  }
  if (black_king && check(*black_king, black, white, board, setup)) {
      printf("Black king is in check!\n");
      return true;
  }
  return false;
}
bool is_stalemate(struct pieces player[], struct pieces enemy[], int board[][8], int setup) { //might not work 
  for (int i = 0; i < 16; i++) {
      if (player[i].is_onboard) {
          for (int x = 0; x < 8; x++) {
              for (int y = 0; y < 8; y++) {
                  if (is_valid_move(player[i], x, y, board, setup)) {
                      return false; // There is at least one legal move
                  }
              }
          }
      }
  }
  return true;
}

bool is_checkmate(struct pieces player[], struct pieces enemy[], int board[][8], int setup) { /// might not work
  struct pieces* king = NULL;
  for (int i = 0; i < 16; i++) {
      if (player[i].is_onboard && player[i].type == 'k') {
          king = &player[i];
          break;
      }
  }
  if (king == NULL || !check(*king, enemy, player, board, setup)) {
      return false; // No check => no checkmate
  }
  for (int i = 0; i < 16; i++) {
      if (player[i].is_onboard) {
          for (int x = 0; x < 8; x++) {
              for (int y = 0; y < 8; y++) {
                  if (is_valid_move(player[i], x, y, board, setup)) {
                      return false; // There is at least one move to escape check
                  }
              }
          }
      }
  }
  return true;
}
void save(int board[][8], int player,char *path) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
      printf("Couldn't open save file.\n");
      return;
  }

  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
          fprintf(file, "%d ", board[i][j]);
      }
      fprintf(file, "\n");
  }

  fprintf(file, "%d\n", player);

  fclose(file);
}

void load(int board[][8], int *player, char* path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
      printf("Couldn't open load file.\n");
      return;
  }

  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (fscanf(file, "%d", &board[i][j]) != 1) {
          printf("Error reading at (%d, %d)\n", i, j);
      } 
        }
  }
  fscanf(file,"\n");
  fscanf(file, "%d", player);

  fclose(file);
}


void play(){
  int setup=0;
  int x=2,y=5;
  //  int p=6;
  struct pieces black[16];
  struct pieces white[16];
  initialize_board(board,black,white,setup);
  show(board,black,white);
  printf("\nWrite moves like <piece> <position> \"ex\" to exit\n");
  printf("\n");
  int player=0;
  // even player = white 
  printf("Player 1 to move\n");
  while(true){
    char piece_selector[3],move[3];   
    
    scanf("%s %s",piece_selector,move);
    
    if((strcmp(piece_selector,"ex")==0) ||  (strcmp(move,"ex")==0))
      break;
    if(piece_selector[0]=='s' || move[0]=='s'){
      save(board,player,"save.txt");
      show(board,black,white);
      printf("\nPlayer %d to move\n",(((player)%2)+1));
      continue;
    }
    if(piece_selector[0]=='l' || move[0]=='l'){
      load(board,&player,"save.txt");
      show(board,black,white);
      printf("\nPlayer %d to move\n",(((player)%2)+1));
      continue;
    }
    parse_move(piece_selector,&x,&y);
    struct pieces *piece= find_piece(x,y,board,black,white),*found_piece=NULL;
    // printf("%d%d",piece->x,piece->y);
    
    
    parse_move(move,&x,&y);
      if(board[x][y]!=0)
        {
          found_piece = find_piece(x,y,board,black,white);
        }
    /// check if playercolor is good
    // player 1 = > white, player 2 = > black
        if(player%2==0){
          while(!is_same_color(piece,&white[0])){
            printf("\nWrong piece set\n");
            show(board,black,white);
            scanf("%s %s",piece_selector,move);
            if((strcmp(piece_selector,"ex")==0) ||  (strcmp(move,"ex")==0))
            break;
            parse_move(piece_selector,&x,&y);
            piece= find_piece(x,y,board,black,white);
            // printf("%d%d",piece->x,piece->y);
            parse_move(move,&x,&y);
          }
        }
        else{
          while(!is_same_color(piece,&black[0])){
            printf("\nWrong piece set\n");
            show(board,black,white);
            scanf("%s %s",piece_selector,move);
            if((strcmp(piece_selector,"ex")==0) ||  (strcmp(move,"ex")==0))
            break;
            parse_move(piece_selector,&x,&y);
            piece= find_piece(x,y,board,black,white);
            // printf("%d%d",piece->x,piece->y);
            parse_move(move,&x,&y);
          }
        }
         
    /// TO DO !!!
  
    // find if space is clear then do is move clear
    
    //otherwise 
    // find other piece first  find(piece)
  
    // if is_valid_space && !is_same_color => out of the board with the other piece first
      if(is_king_in_check(black,white,board,setup)){
        show(board,black,white);
        continue;
      }

    if(is_valid_move(*piece,x,y,board,setup)){   /// test
      bool same_color = is_same_color(piece,found_piece); 
      if(board[x][y]!=0 && !same_color){
        out_of_board(found_piece);
      }
      if(!same_color){
        board[piece->x][piece->y]=board[x][y];
        board[x][y]=piece->type_int;
        piece->x=x;
        piece->y=y;          
        found_piece=NULL;
      }
      else{
        printf("Same color!!");
        found_piece=NULL;
      }
      show(board,black,white);
      is_king_in_check(black,white,board,setup);
      if(piece->color[0]=='w'){
        if(is_checkmate(piece,black,board,setup)){
          printf("\nPlayer %d WON\n",(((player+1)%2)+1));
          break;
        }
        if(is_stalemate(piece,black,board,setup)){
          printf("DRAW");
          break;
        }

      }
      else{
        if(is_checkmate(piece,white,board,setup)){
          printf("\nPlayer %d WON\n",(((player+1)%2)+1));
          break;
        }
        if(is_stalemate(piece,white,board,setup)){
          printf("DRAW");
          break;
        }
      }
      printf("\n");
      printf("Write moves like \"piece position\" or \"ex\" to exit\n");
      printf("\nPlayer %d to move\n",(((player+1)%2)+1));
     //  show_int_board(board);
    } 
    else{
      printf("Invalid move\n");
    }
    ++player;
  }

}



int main(){ // to implement winning condition and stalemate
  play();
    return 0;
}