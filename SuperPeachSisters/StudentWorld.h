#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include<list>
#include"Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    bool isBlockingObjectAt(int x,int y);
    std::string fileexist();
    void overlap(Actor* object);
    void overlap_pf (Actor* object,bool& die);
    void jumpbonk(Actor* object);
    Peach* getPeach();
    void push(int x, int y,int i,Block* bk);
    void push1(int x, int y,Piranha* bk);
    void push2(int x, int y,Peach* bk);
    void push3(int x, int y,Koopa* bk);
    
    
private:
    std::list<Actor*> m_actors;
    Peach* m_peach;
    Flag* m_flag;
    Mario* m_mario;
};

#endif // STUDENTWORLD_H_




// 1 prihana firing range
