#ifndef POSITION_H
#define POSITION_H

class Position
{

protected :
    int _x;
    int _y;

public :
    Position(int x, int y): _x(x),_y(y) {}
    Position():_x(0),_y(0) {}
    ~Position() {};
    const int x()const
    {
        return _x;
    }
    const int y()const
    {
        return _y;
    }
    void setX(int x){_x=x;}
    void setY(int y){_y=y;}


};




#endif
