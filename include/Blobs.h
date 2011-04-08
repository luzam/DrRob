#ifndef BLOBS_H_INCLUDED
#define BLOBS_H_INCLUDED


#include "State.h"
#include "Color.h"
#include "Link.h"


class Blobs
{
protected :
    Color _color;
    State _state;
    Link _link;
public :
    Blobs(Color color,State state=CURRENT,Link link=NO_LINK):
        _color(color),_state(state),_link(link) {}
    Blobs(int zero):_color(BLANK),_state(NO_STATE),_link(NO_LINK){}
    Blobs(const Blobs& blob): _color(blob.color()),_state(blob.state()),_link(blob.link()){}
    Blobs(){}
    ~Blobs() {}

    const Color color()const
    {
        return _color;
    }
    const State state()const
    {
        return _state;
    }
    const Link link()const
    {
        return _link;
    }
    void setColor(Color color)
    {
        _color=color;
    }
    void setState(State state)
    {
        _state =  state;
    }
    void setLink(Link link)
    {
        _link = link;
    }
    void setBlob(Color color, State state, Link link){
    _link = link;
    _color = color;
    _state = state;
    }
};




#endif
