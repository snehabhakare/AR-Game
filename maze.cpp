#pragma once
#include "cs775_assigment1.hpp"
extern float B,L,W;
extern std::vector<rectangle*> maze_list;
void maze(){
    rectangle* r;
    //base
    
    r=new rectangle(L,B,0,0,false,0.5*height_of_each_elem);
    maze_list.push_back(r);
    

    //vertical
    int Bs=B/8;
    int Ls=L/10;
    //1
    r=new rectangle(W,8*Bs,-5*Ls,0);
    maze_list.push_back(r);
    //2
    r=new rectangle(W,3*Bs,-4*Ls,1.5*Bs);
    maze_list.push_back(r);
    //3
    r=new rectangle(W,2*Bs,-4*Ls,-1.5*Bs);
    maze_list.push_back(r);
    //4
    r=new rectangle(W,2*Bs,-3*Ls,Bs);
    maze_list.push_back(r);
    //5
    r=new rectangle(W,Bs,-3*Ls,-1.5*Bs);
    maze_list.push_back(r);
    //6
    r=new rectangle(W,2*Bs,-2*Ls,0);
    maze_list.push_back(r);
    //7
    r=new rectangle(W,Bs,-2*Ls,-2.5*Bs);
    maze_list.push_back(r);
    //8
    r=new rectangle(W,2*Bs,-Ls,-Bs);
    maze_list.push_back(r);
    //9
    r=new rectangle(W,2*Bs,0,Bs);
    maze_list.push_back(r);
    //10
    r=new rectangle(W,Bs,0,-1.5*Bs);
    maze_list.push_back(r);
    //11
    r=new rectangle(W,Bs,Ls,2.5*Bs);
    maze_list.push_back(r);
    //12
    r=new rectangle(W,Bs,Ls,-2.5*Bs);
    maze_list.push_back(r);
    //13
    r=new rectangle(W,2*Bs,2*Ls,3*Bs);
    maze_list.push_back(r);
    //14
    r=new rectangle(W,Bs,2*Ls,0.5*Bs);
    maze_list.push_back(r);
    //15
    r=new rectangle(W,Bs,2*Ls,-1.5*Bs);
    maze_list.push_back(r);
    //16
    r=new rectangle(W,Bs,2*Ls,-3.5*Bs);
    maze_list.push_back(r);
    //17
    r=new rectangle(W,Bs,3*Ls,-0.5*Bs);
    maze_list.push_back(r);
    //18
    r=new rectangle(W,Bs,3*Ls,-2.5*Bs);
    maze_list.push_back(r);
    //19
    r=new rectangle(W,3*Bs,4*Ls,1.5*Bs);
    maze_list.push_back(r);
    //20
    r=new rectangle(W,2*Bs,4*Ls,-2*Bs);
    maze_list.push_back(r);
    //21
    r=new rectangle(W,8*Bs,5*Ls,0);
    maze_list.push_back(r);
    //horizontal

    //1
    r=new rectangle(10*Ls,W,0,4*Bs);
    maze_list.push_back(r);
    //2
    r=new rectangle(5*Ls,W,-1.5*Ls,3*Bs);
    maze_list.push_back(r);
    //3
    r=new rectangle(Ls,W,3.5*Ls,3*Bs);
    maze_list.push_back(r);
    //4
    r=new rectangle(2*Ls,W,-1*Ls,2*Bs);
    maze_list.push_back(r);
    //5
    r=new rectangle(Ls,W,2.5*Ls,2*Bs);
    maze_list.push_back(r);
    //6
    r=new rectangle(Ls,W,-1.5*Ls,Bs);
    maze_list.push_back(r);
    //7
    r=new rectangle(Ls,W,1.5*Ls,Bs);
    maze_list.push_back(r);
    //8
    r=new rectangle(Ls,W,3.5*Ls,Bs);
    maze_list.push_back(r);
    //9
    r=new rectangle(Ls,W,-3.5*Ls,0);
    maze_list.push_back(r);
    //10
    r=new rectangle(2*Ls,W,0,0);
    maze_list.push_back(r);
    //11
    r=new rectangle(Ls,W,2.5*Ls,0);
    maze_list.push_back(r);
    //12
    r=new rectangle(Ls,W,4.5*Ls,0);
    maze_list.push_back(r);
    //13
    r=new rectangle(Ls,W,-2.5*Ls,-1*Bs);
    maze_list.push_back(r);
    //14
    r=new rectangle(2*Ls,W,Ls,-Bs);
    maze_list.push_back(r);
    //15
    r=new rectangle(Ls,W,3.5*Ls,-1*Bs);
    maze_list.push_back(r);
    //16
    r=new rectangle(2*Ls,W,2*Ls,-2*Bs);
    maze_list.push_back(r);
    //17
    r=new rectangle(5*Ls,W,-1.5*Ls,-3*Bs);
    maze_list.push_back(r);
    //18
    r=new rectangle(Ls,W,3.5*Ls,-3*Bs);
    maze_list.push_back(r);
    //19
    r=new rectangle(10*Ls,W,0,-4*Bs);
    maze_list.push_back(r);
}