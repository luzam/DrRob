#ifndef BLOBS_H_INCLUDED
#define BLOBS_H_INCLUDED


#include "State.h"
#include "Color.h"
#include "Link.h"

#include <iostream> // temporaire

class Blobs
{
protected :
    size_t _color;
    size_t _state;
    size_t _link;
    int _current;
    int _fallingDepth;
    size_t _fallingCol;
public :
    Blobs(Color color,State state=NO_STATE,Link link=NO_LINK):
        _color(color),_state(state),_link(link),_current(0)
    {
        std::cout<<"Blob(couleur)\n";
    }
    Blobs():_color(BLANK),_state(NO_STATE),_link(NO_LINK),_current(0)
    {
        std::cout<<"Blob(vierge)\n";
    }
    Blobs(const Blobs& blob): _color(blob.color()),_state(blob.state()),_link(blob.link()),_current(0)
    {
        std::cout<<"Blob(Blob copie)\n";
    }
    ~Blobs() {}

    const size_t color()const
    {
        return _color;
    }
    const size_t state()const
    {
        return _state;
    }
    const size_t link()const
    {
        return _link;
    }
    void setColor(size_t color)
    {
        _color=color;
    }
    void setState(size_t state)
    {
        _state =  state;
    }
    void setLink(size_t link)
    {
        _link = link;
    }
    void setBlob(size_t color, size_t state, size_t link)
    {
        _link = link;
        _color = color;
        _state = state;
    }
    void setBlob(const Blobs& blob)
    {
        _link = blob.link();
        _color = blob.color();
        _state = blob.state();
    }
    void setFalling(int falling)
    {
        this->setState(FALLING);
        _current = falling;
    }
    void setComboting(int comboting)
    {
        this->setState(COMBOTING);
        _current = comboting;
    }
    int current()const
    {
        return _current;
    }
    int fallingDepth()const
    {
        return _fallingDepth;
    }
    void setFallingDepth(int depth)
    {
        _fallingDepth=depth;
    }
    int fallingCol()const
    {
        return _fallingCol;
    }
    void setFallingCol(int col)
    {
        _fallingCol=col;
    }
};




#endif
