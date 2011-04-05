#ifndef BLOB_B
#define BLOB_H

#include "State.h"
#include "Color.h"
#include "Link.h"

class Blob
{
protected :
    Color _color;
    State _state;
    Link _link;
public :
    Blob(Color color,State state=CURRENT,Link link=NO_LINK):
        _color(color),_state(state),_link(link) {}
    ~Blob() {}

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
};



#endif
