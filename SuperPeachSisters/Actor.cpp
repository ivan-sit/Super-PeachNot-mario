#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp



//Actor
Actor::Actor(int imageID, int startX, int startY,
      int startDirection , int depth , double size, StudentWorld* world)
: GraphObject(imageID, startX, startY, startDirection , depth , size)
{
    m_world = world;
    
    
}


bool Actor::alive() {
    return m_health > 0;
}

int Actor::Health() {
    return m_health;
}


void Actor::setHealth(int health) {
    m_health = health;
}

 bool Actor::isDamageable()
{
    return false;
}
void Actor::bonk()
{
    return ;
}

void Actor::bonk2()
{
    return ;
}


bool Actor::blocksth()
{
    return false;
}


StudentWorld* Actor::getWorld() {
    return m_world;
}

//block
Block::Block(double startX, double startY, StudentWorld* world)
: Actor( IID_BLOCK, startX, startY, 0, 2, 1, world)
{
    setHealth(1);
    m_bonked=false;
   
    
    Level::GridEntry ge;
    Level lev(getWorld()->assetPath());
    
    lev.loadLevel(getWorld()->fileexist());

    ge=lev.getContentsOf((startX/SPRITE_WIDTH),startY/SPRITE_HEIGHT);
    switch (ge)
    {
            case Level::block:
            goodie=0;
                     break;
                 case Level::star_goodie_block:
                        goodie=3;
                          break;
                 case Level::mushroom_goodie_block:
                        goodie=1;
                          break;
                 case Level::flower_goodie_block:
                        goodie=2;
                          break;
    }
}

void Block::doSomething()
{
    return;
   
}

bool Block::blocksth()
{
    return true;
}

bool Block::bonked()
{
    return m_bonked;
}

void Block::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
    if(goodie==0)
    {
        return;
    }
    if(goodie==1)
    {
        if(!bonked())
        {
            getWorld()->push(getX(), getY(), 1,this);
            m_bonked=true;
        }
       
    }
    if(goodie==2)
    {
        if(!bonked())
        {
            getWorld()->push(getX(), getY(), 2,this);
            m_bonked=true;
        }
       
    }
    if(goodie==3)
    {
        if(!bonked())
        {
            getWorld()->push(getX(), getY(), 3,this);
            m_bonked=true;
        }
       
    }
}


//void releasegoodie();


//Peach







Peach::Peach(double startX, double startY, StudentWorld* world)
: Actor( IID_PEACH, startX, startY, 0, 0, 1, world)
{
    setHealth(1);
    
    m_superpwer=false;
    m_temp_inv=false;
    jump_power=false;
    shoot=false;
    star_tick=0;
    temp_tick=0;
    time_to_recharge_before_next_fire=0;
    remaining_jump_distance=0;
    
    
    
}

bool Peach::isDamageable()
{
    return true;
}
void Peach::updateshoot()
{
    shoot = true;
}

bool Peach::superpower()
{
    return m_superpwer;
}

void Peach::doSomething()
{
    if (!alive())
    {
        return;
    }
    
    if (m_superpwer)
    {
        star_tick--;
        if(star_tick==0)
        {
            m_superpwer=false;
        }
    }
    if(m_temp_inv)
    {
        temp_tick--;
        if(temp_tick==0)
        {
            m_temp_inv=false;
        }
    }
    if(recharge())
    {
        if(time_to_recharge_before_next_fire>0)
        {
            time_to_recharge_before_next_fire--;
        }
        if(time_to_recharge_before_next_fire==0)
        {
            updateshoot();//implment it later
        }
    }
    
   
    getWorld()->overlap(this);//bonk all the overlapped stuff
    
    
    if(remaining_jump_distance>0)
    {
        
        if(getWorld()->isBlockingObjectAt(getX(), getY()+4)||getWorld()->isBlockingObjectAt(getX()+4, getY()+4))
        {
            getWorld()->jumpbonk(this);//change with all the switch
            remaining_jump_distance=0;
        }
        else{
            moveTo(getX(), getY()+4);
            remaining_jump_distance--;
        }
    } else
   
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-4)&&!getWorld()->isBlockingObjectAt(getX()+4, getY()-4))
    {
        moveTo(getX(), getY()-4);
    }
    
    
    int ch;
     if (getWorld()->getKey(ch))
     {
     // user hit a key during this tick!
     switch (ch)
     {
     case KEY_PRESS_LEFT:
        setDirection(180);

             if (!getWorld()->isBlockingObjectAt(getX()-4, getY()))
             {
                 moveTo(getX()-4, getY());
             }
             
       
     break;
     case KEY_PRESS_RIGHT:
             setDirection(0);
              
                  if (!getWorld()->isBlockingObjectAt(getX()+8, getY()))
                  {
                      moveTo(getX()+4, getY());
                  }
     break;
             
    case KEY_PRESS_UP:
             if(getWorld()->isBlockingObjectAt(getX(),getY()-1)||getWorld()->isBlockingObjectAt(getX()+4,getY()-1))
             {
                 if(jump_power)
                 {
                     remaining_jump_distance=12;
                 }
                 else
                 {
                     remaining_jump_distance=8;
                 }
                 getWorld()->playSound(SOUND_PLAYER_JUMP);
                 
             }
             
             break;
         case KEY_PRESS_SPACE:
             if(shoot)
             {
                 if(time_to_recharge_before_next_fire==0)
                 {
                     getWorld()->playSound(SOUND_PLAYER_FIRE);
                     time_to_recharge_before_next_fire=8;
                     getWorld()->push2(getX()+4,getY(),this);
                     
                 }
             }
             break;
             
//
     }
     }
}


bool Peach::invin()
{
    if (m_temp_inv||m_superpwer)
        return true;
    else
        return false;
}

int Peach::get_remaining_jump_distance()
{
    return remaining_jump_distance;
}




bool Peach::recharge()
{
    return time_to_recharge_before_next_fire>0;
}



void Peach::updatejump()
{
    jump_power=true;
}
 
void Peach::updatestar()
{
    star_tick=150;
    m_superpwer=true;
}



void Peach::bonk()
{
    if(!m_superpwer&&!m_temp_inv)
    {
        setHealth(Health()-1);
        getWorld()->playSound(SOUND_PLAYER_HURT);
        shoot=false;
        jump_power=false;
        m_temp_inv=true;
        temp_tick=10;
       
        

    }
    
}

bool Peach::jumping()
{
    return jump_power;
}
bool Peach::shooting()
{
    return shoot;
}

//pipe
Pipe::Pipe(double startX, double startY, StudentWorld* world)
: Actor(IID_PIPE, startX, startY, 0, 2, 1, world)
{
    setHealth(1);
}

void Pipe::doSomething()
{
    return;
}

bool Pipe::blocksth()
{
    return true;
}



//flag

Flag::Flag(double startX, double startY, StudentWorld* world)
: Actor(IID_FLAG, startX, startY, 0, 1, 1, world)
{
    setHealth(1);
    reach=false;
}

void Flag::doSomething()
{
    if(!alive())
    {
        return;
    }
    //overlap
}
void Flag::bonk()
{
    getWorld()->increaseScore(1000);
    setHealth(0);
    reach=true;
    
}

bool Flag::flagreached()
{
    return reach;
}


//mario

Mario::Mario(double startX, double startY, StudentWorld* world)
: Actor(IID_MARIO, startX, startY, 0, 1, 1, world)
{
    reach=false;
    setHealth(1);
}

void Mario::doSomething()
{
    if(!alive())
    {
        return;
    }
    //overlap
}

void Mario::bonk()
{
    getWorld()->increaseScore(1000);
    setHealth(0);
    reach=true;
    
}

bool Mario::marioreached()
{
    return reach;
}
//flower

Flower::Flower(double startX, double startY, StudentWorld* world,Block* bk)
: Actor(IID_FLOWER, bk->getX(), bk->getY()+8, 0, 1, 1, world)
{
    setHealth(1);
}

void Flower::doSomething()
{
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+6, getY()))
        {
            setDirection(180);
            return;
            
        }
        else{
            moveTo(getX()+2, getY());
        }
        
    }
    if(getDirection()==180)
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()))
        {
            setDirection(0);
            return;
            
        }
        else{
            moveTo(getX()-2, getY());
        }
        
    }
    //overlap

}

void Flower::bonk()
{
    getWorld()->increaseScore(50);
    getWorld()->getPeach()->updateshoot();
    getWorld()->getPeach()-> setHealth(2);
    setHealth(0);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    return;
}


//mushroom

Mushroom::Mushroom (double startX, double startY, StudentWorld* world,Block* bk)
: Actor(IID_MUSHROOM, bk->getX(), bk->getY()+8, 0, 1, 1, world)
{
    setHealth(1);
}

void Mushroom::bonk()
{
    getWorld()->increaseScore(75);
    getWorld()->getPeach()->updatejump();
    getWorld()->getPeach()->setHealth(2);
    setHealth(0);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    return;
}

void Mushroom::doSomething()
{
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+6, getY()))
        {
            setDirection(180);
            return;
            
        }
        else{
            moveTo(getX()+2, getY());
        }
        
    }
    if(getDirection()==180)
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()))
        {
            setDirection(0);
            return;
            
        }
        else{
            moveTo(getX()-2, getY());
        }
        
    }
}
//star




Star::Star(double startX, double startY, StudentWorld* world,Block* bk)
: Actor(IID_STAR, bk->getX(), bk->getY()+8, 0, 1, 1, world)
{
    setHealth(1);
}

void Star::bonk()
{
    getWorld()->increaseScore(100);
    getWorld()->getPeach()->updatestar();
   
    setHealth(0);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    return;
}


void Star::doSomething()
{
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+6, getY()))
        {
            setDirection(180);
            return;
            
        }
        else{
            moveTo(getX()+2, getY());
        }
        
    }
    if(getDirection()==180)
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()))
        {
            setDirection(0);
            return;
            
        }
        else{
            moveTo(getX()-2, getY());
        }
        
    }
}




//Piranha

Piranha::Piranha(double startX, double startY, StudentWorld* world)
: Actor(IID_PIRANHA, startX, startY, randInt(0,180), 1, 0, world)
{
    setHealth(1);
    delay=0;
}



void Piranha::doSomething()
{
    if (!alive())
    {
        return;
    }
    increaseAnimationNumber();
    if( getWorld()->getPeach()->getY()<=1.5*SPRITE_HEIGHT+getY()||getWorld()->getPeach()->getY()>=getY()-1.5*SPRITE_HEIGHT)
    {
        if(getWorld()->getPeach()->getX()<=getX())
        {
            setDirection(180);
        }
        if(getWorld()->getPeach()->getX()>=getX())
        {
            setDirection(0);
        }
        if (delay>0)
        {
            delay--;
            return;
        }
        if(delay==0)
        {
           if(getWorld()->getPeach()->getX()<=getX()+1.5*SPRITE_WIDTH&&getWorld()->getPeach()->getX()>=getX()-1.5*SPRITE_WIDTH&&getWorld()->getPeach()->getY()<=getY()+1.5*SPRITE_HEIGHT&&getWorld()->getPeach()->getY()>=getY()-1.5*SPRITE_HEIGHT)
           {
               getWorld()->push1(getX(), getY(),this);
               getWorld()->playSound( SOUND_PIRANHA_FIRE);
               delay=40;
           }
        }
        
    }
    else{
        return;
    }

}
void Piranha::bonk()
{
    getWorld()->getPeach()->bonk();
    if(getWorld()->getPeach()->superpower())
    {
        setHealth(0);
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getWorld()->increaseScore(100);
    }
}

void Piranha::bonk2()//fireball
{
   
        setHealth(0);
    
}

//Piranha Fireball
Piranha_Fireball::Piranha_Fireball(double startX, double startY, StudentWorld* world,Piranha* m_p)
: Actor(IID_PIRANHA_FIRE, m_p->getX(), m_p->getY(), m_p->getDirection(), 1, 1, world)

{
    setHealth(1);
}

void Piranha_Fireball::bonk()
{
    
    if(!getWorld()->getPeach()->invin())
    {
        getWorld()->getPeach()->bonk();
        setHealth(0);
    }
   
    return;
}


void Piranha_Fireball::doSomething()
{
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+2, getY()))
        {
            setHealth(0);
            return;
            
        }
        else{
            moveTo(getX()+2, getY());
        }
        
    }
    if(getDirection()==180)
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()))
        {
            setHealth(0);
            return;
            
        }
        else{
            moveTo(getX()-2, getY());
        }
        
    }
}


//peach fire

Peach_Fireball::Peach_Fireball (double startX, double startY, StudentWorld* world,Peach* m_p )
: Actor(IID_PEACH_FIRE, m_p->getX(), m_p->getY(), m_p->getDirection(), 1, 1, world)

{
    setHealth(1);
}

void Peach_Fireball::doSomething()
{
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    bool die;
    getWorld()->overlap_pf(this,die);////////////////////////////////////////////////////////////////////////////////////
    if(die==true)
    {
        setHealth(0);
        return;
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+2, getY()))
        {
            setHealth(0);
            return;
            
        }
        else{
            moveTo(getX()+2, getY());
        }
        
    }
    if(getDirection()==180)
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()))
        {
            setHealth(0);
            return;
            
        }
        else{
            moveTo(getX()-2, getY());
        }
        
    }
}



//goomba

Goomba::Goomba(double startX, double startY, StudentWorld* world)
: Actor(IID_GOOMBA,startX, startY, randInt(0,1)*180, 1, 0, world)

{
    setHealth(1);
}


void Goomba::doSomething()
{
    if(!alive())
    {
        return;
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+8, getY())||!getWorld()->isBlockingObjectAt(getX()+8, getY()-1))
        {
            setDirection(180);
        }
        else
        moveTo(getX()+1, getY());
        
    }
   
    else
    {
        if (getWorld()->isBlockingObjectAt(getX()-1, getY())||!getWorld()->isBlockingObjectAt(getX()-4, getY()-1))
        {
            setDirection(0);
        }
        else
        moveTo(getX()-1, getY());
    }
   
    
}

void Goomba::bonk()//peach
{   
    getWorld()->getPeach()->bonk();
    if(getWorld()->getPeach()->superpower())
    {
        setHealth(0);
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getWorld()->increaseScore(100);
    }
}

void Goomba::bonk2()//fireball
{
   
    setHealth(0);
getWorld()->playSound(SOUND_PLAYER_KICK);
getWorld()->increaseScore(100);

    
}



//koopa

Koopa::Koopa (double startX, double startY, StudentWorld* world)
: Actor(IID_KOOPA,startX, startY, randInt(0,1)*180, 1, 0, world)

{
    setHealth(1);
}
void Koopa::doSomething()
{
    if(!alive())
    {
        return;
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+8, getY())||!getWorld()->isBlockingObjectAt(getX()+8, getY()-1))
        {
            setDirection(180);
        }
        else
        moveTo(getX()+1, getY());
        
    }
   
    else
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY())||!getWorld()->isBlockingObjectAt(getX()-4, getY()-1))
        {
            setDirection(0);
        }
        else
        moveTo(getX()-1, getY());
    }
   
    
}


void Koopa::bonk()//peach
{
    getWorld()->getPeach()->bonk();
    if(getWorld()->getPeach()->superpower())
    {
        setHealth(0);
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getWorld()->increaseScore(100);
        
        getWorld()->push3(getX(), getY(), this);
    }
}

void Koopa::bonk2()//fireball
{
   
        setHealth(0);
    getWorld()->playSound(SOUND_PLAYER_KICK);
    getWorld()->increaseScore(100);
    getWorld()->push3(getX(), getY(), this);
    
    
}



//shell

Shell::Shell (double startX, double startY, StudentWorld* world, Koopa* bk)
: Actor(IID_SHELL,bk->getX(), bk->getY(), bk->getDirection(), 1, 1, world)

{
    setHealth(1);
}






void Shell::doSomething()
{
    bool die;
    getWorld()->overlap_pf(this,die);
    if(die==true)
    {
        setHealth(0);
        return;
    }
    
    
    if(!getWorld()->isBlockingObjectAt(getX(), getY()-2))
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if (getWorld()->isBlockingObjectAt(getX()+2, getY()))
        {
            setHealth(0);
            return;
            
        }
        else{
            moveTo(getX()+2, getY());
        }
        
    }
    if(getDirection()==180)
    {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()))
        {
            setHealth(0);
            return;
            
        }
        else{
            moveTo(getX()-2, getY());
        }
        
    }
}
