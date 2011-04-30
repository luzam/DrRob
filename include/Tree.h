#ifndef TREE_H
#define TREE_H

template <typename X>

class Tree {
protected :
    X _data;
    Tree* _fils_gauche;
    Tree* _fils_droit;
public :
    Tree(X data):_data(data){
    _fils_droit = NULL;
    _fils_gauche = NULL;
    }
    ~Tree(){
    if(_fils_droit!=NULL)
        ~(*_fils_droit)();
    if(_fils_gauche!=NULL)
        ~(*_fils_gauche)();
    }



};


#endif
