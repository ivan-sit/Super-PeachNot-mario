//
//  Actor.h
//  Actor
//
//  Created by Sit Ming Yin Ivan on 18/2/2022.
//

#ifndef Actor_h
#define Actor_h


#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject {

public:
    Actor(int imageID, int startX, int startY,
          int startDirection , int depth , double size, StudentWorld* world);
    
    
    
    
    int Health();
    virtual void doSomething()=0;
     bool alive();
     void setHealth(int health);
    virtual bool isDamageable();
    virtual void bonk();
    virtual void bonk2();    
    virtual bool blocksth();
    StudentWorld* getWorld();



private:
   
    StudentWorld* m_world;
    int m_health;
    
   

};



class Block: public Actor{
    
public:
    Block(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual bool blocksth();
    virtual void bonk();
    bool bonked();
private:
    int goodie;//0=nothing 1=mushroom  2=flower 3=star
    bool m_bonked;
 
    
//    bool goodiereleased();
//    void releasegoodie();

    
};




class Peach: public Actor{
    
public:
    Peach(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual bool isDamageable();
    bool invin();
    bool superpower();//=star power
    bool jumping();
    bool shooting();
    int get_remaining_jump_distance();
    bool recharge();
    void updateshoot();
    void updatestar();
    void updatetemp();
    void updatejump();
    virtual void bonk();
   
    
private:
    
    bool m_superpwer;
    bool m_temp_inv;
    int star_tick;
    int temp_tick;
    int remaining_jump_distance;
    bool jump_power;
    bool shoot;
    int time_to_recharge_before_next_fire;
    
    
    
};


class Pipe: public Actor{
    
public:
    Pipe(double startX, double startY, StudentWorld* world);
    virtual void doSomething();
    virtual bool blocksth();
    
    
    
//    bool goodiereleased();
//    void releasegoodie();

    
};


class Flag: public Actor{
    
public:
    Flag(double startX, double startY, StudentWorld* world);
    
    virtual void doSomething();
    virtual void bonk();
    bool flagreached();
private:
    bool reach;

    
};



class Mario: public Actor{
    
public:
    Mario(double startX, double startY, StudentWorld* world);
    
    virtual void doSomething();
    virtual void bonk();
    bool marioreached();
private:
    bool reach;

    
};


class Flower: public Actor{
    
public:
    Flower(double startX, double startY, StudentWorld* world,Block* bk);
    virtual void bonk();
    virtual void doSomething();


    
};

class  Mushroom: public Actor{
    
public:
    Mushroom (double startX, double startY, StudentWorld* world,Block* bk);
    
    virtual void doSomething();
//
    virtual void bonk();
    
};





class  Star: public Actor{
    
public:
    Star (double startX, double startY, StudentWorld* world,Block* bk);
    
    virtual void doSomething();
//
    virtual void bonk();
    
};

class Piranha: public Actor{
    
public:
    Piranha(double startX, double startY, StudentWorld* world);
    virtual void bonk();
    virtual void doSomething();
    void updatedelay();
    void bonk2();
private:
    int delay;


    
};



class  Piranha_Fireball: public Actor{
    
public:
    Piranha_Fireball (double startX, double startY, StudentWorld* world,Piranha* m_p );
    
    virtual void doSomething();
//
    virtual void bonk();

    
};


class  Peach_Fireball: public Actor{
    
public:
    Peach_Fireball (double startX, double startY, StudentWorld* world,Peach* m_p );
    
    virtual void doSomething();
//
    

    
};




class Goomba: public Actor{
    
public:
    Goomba(double startX, double startY, StudentWorld* world);
    virtual void bonk();
    void bonk2();
    virtual void doSomething();
    
};



class Koopa: public Actor{
    
public:
    Koopa (double startX, double startY, StudentWorld* world);
    virtual void bonk();
    void bonk2();
    virtual void doSomething();
  };


class Shell: public Actor{
    
public:
    Shell (double startX, double startY, StudentWorld* world, Koopa* bk);
    
    virtual void doSomething();
  };


#endif /* Actor_h */
