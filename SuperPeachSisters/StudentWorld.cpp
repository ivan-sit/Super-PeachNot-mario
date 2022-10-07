#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
    
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_mario=nullptr;
    m_flag=nullptr;
    
}

string StudentWorld::fileexist()
{
 Level lev(assetPath());
    int level = getLevel();
    ostringstream oss;
    oss.fill('0');
    oss <<"level"<<setw(2)<<level<<".txt";
    string level_file = oss.str();;
 Level::LoadResult result = lev.loadLevel(level_file);
 if (result == Level::load_fail_file_not_found)
 {
     return "dummy";
 }
 
 else if (result == Level::load_fail_bad_format)
 {
     return "dummy";
 }
 
 else
 {
     return level_file;
 }
     
}

int StudentWorld::init()
{
   
    if (fileexist() == "dummy")
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    Level lev(assetPath());
    lev.loadLevel(fileexist());
    Level::GridEntry ge;
    int x,y;
    
    
    for (x=0;x<GRID_WIDTH;x++)
    {
        for (y=0;y<GRID_HEIGHT;y++)
        {
            
                ge=lev.getContentsOf(x,y);
                switch (ge)
                
                 {
                 case Level::empty:
                         break;
                case Level::peach:
                         m_peach = new Peach(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                         m_actors.push_back(m_peach);
                         break;
                case Level::block:
                         m_actors.push_back(new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                         break;
                     case Level::star_goodie_block:
                              m_actors.push_back(new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                              break;
                     case Level::mushroom_goodie_block:
                              m_actors.push_back(new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                              break;
                     case Level::flower_goodie_block:
                              m_actors.push_back(new Block(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                              break;
                         
                    
                case Level::pipe:
                         m_actors.push_back(new Pipe(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                         break;
                case Level::flag:
                         m_flag=new Flag(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                         m_actors.push_back(m_flag);
                         break;
             case Level::mario:
                      m_mario=new Mario(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                      m_actors.push_back(m_mario);
                      break;
                     case Level::piranha:
                              m_actors.push_back(new Piranha(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                              break;
                     case Level::goomba:
                         m_actors.push_back(new Goomba(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                         break;
                     case Level::koopa:
                         m_actors.push_back(new Koopa(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this));
                         break;
                         
                   
                 }
                
            
        }
    }
    
    
    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        if (getLives()==0)
        {
            return GWSTATUS_PLAYER_DIED;
        }
        if(m_peach->Health()==0)
        {
            decLives();
            playSound(SOUND_PLAYER_DIE);
            return GWSTATUS_PLAYER_DIED;
        }
    
    
    
    //dosth
    if(m_flag!=nullptr)
    {
        if(m_flag->flagreached())
        {
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
   
    if(m_mario!=nullptr)
    {
        if(m_mario->marioreached())
        {
            playSound(SOUND_GAME_OVER);
            return GWSTATUS_PLAYER_WON;
        }
    }
   
    
  
    
    list<Actor*>::iterator it = m_actors.begin();
       for (; it!= m_actors.end();  it++)
       {
           (*it)->doSomething();

                 
       }
    list<Actor*>::iterator it1 = m_actors.begin();
       while (it1!= m_actors.end())
       {
           if(!(*it1)->alive())
           {
               delete (*it1);
               m_actors.erase(it1++);
               
           } else {
               it1++;
           }

                
       }
    
    Level lev(assetPath());
       int level = getLevel();
       ostringstream oss;
       oss.fill('0');
    oss <<"Lives: "<<setw(1)<<getLives()<<"  Level: "<<setw(2)<<level<<"  Points: "<<setw(6)<<getScore();
    
    if(m_peach->superpower())
    {
        oss<<" StarPower!";
    }
    if(m_peach->shooting())
    {
        oss<<" ShootPower!";
    }
    if (m_peach->jumping())
    {
        oss<<" JumpPower!";
    }
    
    
    
    string display=oss.str();
    
    setGameStatText(display);
    
    return GWSTATUS_CONTINUE_GAME;
    
    
    
    
}

void StudentWorld::cleanUp()
{
    
    list<Actor*>::iterator it1 = m_actors.begin();
       while (it1!= m_actors.end())
       {
          
               delete (*it1);
           m_actors.erase(it1++);

                
       }
}






StudentWorld::~StudentWorld() {
    cleanUp();
}



bool StudentWorld::isBlockingObjectAt(int x,int y)
{
    Level lev(assetPath());
    Level::GridEntry ge;
    lev.loadLevel(fileexist());

    ge=lev.getContentsOf((x/SPRITE_WIDTH),y/SPRITE_HEIGHT);
    if(ge==Level::block||ge==Level::pipe||ge==Level::star_goodie_block||ge==Level::flower_goodie_block||ge==Level::mushroom_goodie_block)
    {
        return true;
    }
    return false;
}


//bool StudentWorld::isBlockingObjectAt(int x,int y,Level::GridEntry& ge)
//{
//    Level lev(assetPath());
//    
//    lev.loadLevel(fileexist());
//
//    ge=lev.getContentsOf((x/SPRITE_WIDTH),y/SPRITE_HEIGHT);
//    if(ge==Level::block||ge==Level::pipe||ge==Level::star_goodie_block||ge==Level::flower_goodie_block||ge==Level::mushroom_goodie_block)
//    {
//        return true;
//    }
//    return false;
//}

void StudentWorld::overlap(Actor* object)
{
    list<Actor*> :: iterator it;
    it=m_actors.begin();
    for(;it!=m_actors.end();it++)
    {
        if(object!=(*it))
        {
            if((*it)->getX()>=object->getX()-(SPRITE_WIDTH/2)&&(*it)->getX()<=object->getX()+(SPRITE_WIDTH/2)&&(*it)->getY()>=object->getY()-(SPRITE_HEIGHT/2)&&(*it)->getY()<=object->getY()+(SPRITE_HEIGHT/2))
            {
    //            Level::GridEntry ge;
    //            Level lev(assetPath());
    //
    //            lev.loadLevel(fileexist());
    //
    //            ge=lev.getContentsOf(((*it)->getX()/SPRITE_WIDTH),(*it)->getY()/SPRITE_HEIGHT);
    //
    //            if(ge!=Level::piranha&&ge!=Level::koopa&&ge!=Level::goomba)
    //            {
    //                (*it)->bonk();
    //            }
    //            if(m_peach->invin())
    //            {
                if((*it)->alive())
                {
                    (*it)->bonk();
                }
                       
                    
    //            }
            }
        }
        
    }
}void StudentWorld::overlap_pf (Actor* object,bool& die)
{
        
    die=false;
    list<Actor*> :: iterator it;
    it=m_actors.begin();
    for(;it!=m_actors.end();it++)
    {
        if(object!=(*it)&&(*it)!=m_peach&&(*it)->getX()>=object->getX()-(SPRITE_WIDTH/2)&&(*it)->getX()<=object->getX()+(SPRITE_WIDTH/2)&&(*it)->getY()>=object->getY()-(SPRITE_HEIGHT/2)&&(*it)->getY()<=object->getY()+(SPRITE_HEIGHT/2))
        {
            if((*it)->alive())
            {
                (*it)->bonk2();
            die=true;
            }
//            Level::GridEntry ge;
//            Level lev(assetPath());
//
//            lev.loadLevel(fileexist());
//
//            ge=lev.getContentsOf(((*it)->getX()/SPRITE_WIDTH),(*it)->getY()/SPRITE_HEIGHT);
//
//            if(ge==Level::piranha||ge==Level::koopa||ge==Level::goomba)
//            {
                
                
//            }
        }
    }
   
}

void StudentWorld::jumpbonk(Actor* object)
{
    list<Actor*> :: iterator it;
    it=m_actors.begin();
    for(;it!=m_actors.end();it++)
    {
        if(object!=(*it)&&(*it)->getX()==object->getX()&&(*it)->getY()==object->getY()+4)
        {
            (*it)->bonk();
        }
    }
}





Peach* StudentWorld::getPeach()
{
    return m_peach;
}


void StudentWorld::push(int x, int y, int i,Block* bk)
{
    if (i==1)
    {
        m_actors.push_back(new Mushroom(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this,bk));
    }
    if (i==2)
    {
        m_actors.push_back(new Flower(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this,bk));
    }
    if (i==3)
    {
        m_actors.push_back(new Star(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this,bk));
    }
    
}

void StudentWorld::push1(int x, int y,Piranha* bk)
{
    m_actors.push_back(new Piranha_Fireball(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this,bk));
}

void StudentWorld::push2(int x, int y,Peach* bk)
{
    m_actors.push_back(new Peach_Fireball(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this,bk));
}

void StudentWorld::push3(int x, int y,Koopa* bk)
{
    m_actors.push_back(new Shell(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this,bk));
}
