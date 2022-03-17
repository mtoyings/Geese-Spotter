#include <iostream>
#include "geesespotter_lib.h"


char * createBoard(std::size_t xdim, std::size_t ydim){
   
    char* makeboard{new char[xdim*ydim]{}};
    for (unsigned int i{0}; i < (xdim*ydim); ++i){
        makeboard[i] = 0;
    }
    
    
    return makeboard;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){

    for (unsigned int point{}; point < xdim*ydim; ++point){
        int xloc{};
        int yloc{};

        xloc = point % xdim;
        yloc = point / xdim;

        if (board[point] == 9){
            
            for (int y{-1}; y <= 1; ++y ){
                for (int x{-1}; x <= 1; ++x){
                    if ( ((xloc + x) >= 0) && ( (xloc+ x) < xdim) ){
                        if ((yloc + y)>=0 && (yloc + y) < ydim){
                            if (board[point + xdim*y + x] != 9){
                                ++board[point + xdim*y +x ];
                            }
                        }
                    }
                }
            }
        }


    }
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){

    for (unsigned int j{}; j < xdim*ydim; ++j){
        board[j] |= hiddenBit();
    }


}

void cleanBoard(char * board){
    delete[] board;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim){


    for (unsigned int count {}; count < xdim*ydim; ++count){
        if (count % xdim == 0){
            std::cout << std::endl;
        }

        if ((board[count]&markedBit())  == markedBit()){
            std::cout << "M"; 
        } else if ((board[count]&hiddenBit()) == hiddenBit()){
            std::cout << "*";
        } else {
            std::cout << (board[count]&valueMask());
        }

    }
    std::cout << std::endl;

}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    int index{};

    index = yloc*xdim + xloc;

    if ((board[index]^markedBit()) == board[index]){ //if the field is marked
        return 1;
    } else if ((board[index]&hiddenBit()) == 0){ // already revealed
        return 2;
    } else if ((board[index]&valueMask()) == 9){ //contain goose
        board[index] &= valueMask();
        return 9;
    } else if ((board[index]&valueMask()) == 0){ //if the value is 0
        board[index]&=valueMask(); //reveal the 0
        //for (int point{}; point < xdim*ydim; ++point){
        for (int y{-1}; y <= 1; ++y ){
            for (int x{-1}; x <= 1; ++x){
                if ( ((xloc + x) >= 0) && ( (xloc+ x) < xdim) ){
                    if ((yloc + y)>=0 && (yloc + y) < ydim){
                        if ((board[index + xdim*y + x]&valueMask()) != 9){
                                (board[index + xdim*y +x ]&=valueMask());
                            }
                        }
                    }
                }
            }
        //}
        return 0;

    } else { //pass
        board[index]&=valueMask();
        return 0;
    }

}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){


    if (board[yloc*xdim + xloc] < markedBit()){
        
        board[yloc*xdim + xloc] |= markedBit();

        return 2;
    } else {
        board[yloc*xdim + xloc] ^= markedBit();

        return 0;
    }
    
    
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){

    for (unsigned int i{}; i < (xdim*ydim); ++i){
        if (hiddenBit()==(board[i]&hiddenBit()) && (board[i]&valueMask())!=9){
            return false;
        }

        


    }

    return true;
}