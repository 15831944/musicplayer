#ifndef LIST
#define LIST

#include <iostream>
#include <QString>
using namespace std;

class User
{
public:
    User( QString n="", QString c="", bool re=false )
    {
        name=n;
        code=c;
        rem=re;
    }
    ~User(){}
    QString name;
    QString code;
    bool rem;
};

class ListNode
{
public:
    ListNode()
        :pbefore(NULL),
        pnext(NULL),
        pdata(NULL) { delete pdata; }
    ~ListNode() {}
    void* pdata;
    ListNode* pbefore;
    ListNode* pnext;
};

template<class T>
class List;

template<class T>
class Listiter
{
public:
    Listiter()
        :ptr( NULL ) {}
    ~Listiter() { delete ptr; }
    void listRewind( List<T>* list )
    {
        ptr=list->getpheader();
    }
    ListNode* listRewindTail( List<T>* list )
    {
        ptr=list->getprear();
        return ptr;
    }
    ListNode* listBefore()
    {
        ptr=ptr->pbefore;
        return ptr;
    }
    void listNext()
    {
        ptr=ptr->pnext;
    }
    ListNode* operator++()
    {
        listNext();
        return ptr;
    }
    ListNode* operator--()
    {
        listBefore();
        return ptr;
    }
    ListNode* operator+=( int number )
    {
        for( int i=0;i<number;i++ )
            listNext();
        return ptr;
    }
    ListNode* operator-=( int number )
    {
        for( int i=0;i<number;i++ )
            listBefore();
        return ptr;
    }
    ListNode* listSearchKey( List<T>*, void* );
    ListNode* listIndex( List<T>*, int );
    ListNode* ptr;
};


template<class T>
ListNode* Listiter<T>::listSearchKey( List<T>* list, void* key )
{
    this->listRewind( list );
    for( ;ptr != 0; )
    {
        if( ptr->pdata == (*static_cast<T*>( key )) )
            return ptr;
        else
            listNext();
    }
}

template<class T>
ListNode* Listiter<T>::listIndex( List<T>* list, int index )
{
    if( index<0 )
    {
        listRewindTail( list );
        for( int i=0;i>index+1;i-- )
            listBefore();
        return ptr;
    }
    else
    {
        listRewind( list );
        for( int i=0;i<index-1;i++ )
            listNext();
        return ptr;
    }
}

template<class T>
class List
{
public:
    List();
    List( List& );
    ~List();
    void insertAtFront( T& );
    void insertAt( T&, int );
    void insertAtBack( T& );
    void appendAtFront( List<T>& );
    void appendAt( List<T>&, int );
    void appendAtBack( List<T>& );
    void swap( int, int );
    void listRotate();
    int getsize() const;
    bool removeFromFront();
    bool removeFrom( int );
    bool removeFromBack();
    bool isEmpty() const;
    T& operator[]( int );
    T operator[]( int ) const;
    ListNode* getpheader() const;
    ListNode* getprear() const;
    Listiter<T>* listGetIterator();
    List &operator=( List& );
private:
    int size;
    ListNode* pheader;
    ListNode* prear;
};

template<class T>
List<T>::List()
{
    pheader=prear=NULL;
    size=0;
}

template<class T>
List<T>::List( List& port )
{
    size=port.size;
    if( port.isEmpty() )
        pheader=prear=NULL;
    else
    {
        pheader=new ListNode;
        pheader->pdata=port.pheader->pdata;
        ListNode* currentptr=pheader;
        ListNode* acurrentptr=port.pheader;
        for( int i=1;i<size;i++ )
        {
            acurrentptr=acurrentptr->pnext;
            currentptr=currentptr->pnext=new ListNode;
            currentptr->pdata=acurrentptr->pdata;
        }
        prear=currentptr;
        currentptr=pheader;
        for( int i=1;i<size;i++ )
        {
            currentptr->pnext->pbefore=currentptr;
            currentptr=currentptr->pnext;
        }
    }
}

template<class T>
List<T>::~List()
{
    if( !isEmpty() )
    {
        ListNode* currentptr=pheader;
        ListNode* tempptr;
        while( currentptr != 0 )
        {
            tempptr=currentptr;
            currentptr=currentptr->pnext;
            delete tempptr;
        }
    }
}

template<class T>
void List<T>::insertAtFront( T& port )
{
    T* portable=new T(port);
    ListNode* poi=new ListNode;
    poi->pdata=portable;
    if( isEmpty() )
    {
        pheader=prear=poi;
    }
    else
    {
        poi->pnext=pheader;
        pheader->pbefore=poi;
        pheader=poi;
    }
    size++;
}

template<class T>
void List<T>::insertAt( T& port, int number )
{
    if( number == size )
    {
        T* portable=new T(port);
        ListNode* poi=new ListNode;
        poi->pdata=portable;
        prear->pnext=poi;
        poi->pbefore=prear;
        prear=poi;
        size++;
    }
    else if( number == 0 )
    {
        T* portable=new T(port);
        ListNode* poi=new ListNode;
        poi->pdata=portable;
        pheader->pbefore=poi;
        poi->pnext=pheader;
        pheader=poi;
        size++;
    }
    else
    {
        T* portable=new T(port);
        ListNode* poi=new ListNode;
        poi->pdata=portable;
        ListNode* currentptr=pheader;
        for( int i=0;i<number-1;i++ )
            currentptr=currentptr->pnext;
        ListNode* acurrentptr=currentptr->pnext;
        currentptr->pnext=poi;
        poi->pnext=acurrentptr;
        poi->pbefore=currentptr;
        acurrentptr->pbefore=poi;
        size++;
    }
}

template<class T>
void List<T>::insertAtBack( T& port )
{
    T* portable=new T(port);
    ListNode* poi=new ListNode;
    poi->pdata=portable;
    if( isEmpty() )
    {
        pheader=prear=poi;
    }
    else
    {
        prear->pnext=poi;
        poi->pbefore=prear;
        prear=poi;
    }
    size++;
}

template<class T>
void List<T>::appendAtFront( List<T>& port )
{
    ListNode* currentptr=pheader;
    ListNode* acurrentptr=port.prear;
    for( int i=0;i<port.size;i++ )
    {
        currentptr=currentptr->pbefore=new ListNode;
        T* port=new T(*static_cast<T*>( acurrentptr->pdata ));
        currentptr->pdata=port;
        acurrentptr=acurrentptr->pbefore;
    }
    currentptr=pheader;
    for( int i=0;i<port.size;i++ )
    {
        currentptr->pbefore->pnext=currentptr;
        currentptr=currentptr->pbefore;
    }
    pheader=currentptr;
    size+=port.size;
}

template<class T>
void List<T>::appendAt( List<T>& port, int number )
{
    if( number == size )
    {
        ListNode* currentptr=prear;
        ListNode* acurrentptr=port.pheader;
        for( int i=0;i<port.size;i++ )
        {
            currentptr=currentptr->pnext=new ListNode;
            T* port=new T(*static_cast<T*>( acurrentptr->pdata ));
            currentptr->pdata=port;
            acurrentptr=acurrentptr->pnext;
        }
        currentptr=prear;
        for( int i=0;i<port.size;i++ )
        {
            currentptr->pnext->pbefore=currentptr;
            currentptr=currentptr->pnext;
        }
        prear=currentptr;
        size+=port.size;
    }
    else if( size == 0 )
    {
        ListNode* currentptr=pheader;
        ListNode* acurrentptr=port.prear;
        for( int i=0;i<port.size;i++ )
        {
            currentptr=currentptr->pbefore=new ListNode;
            T* port=new T(*static_cast<T*>( acurrentptr->pdata ));
            currentptr->pdata=port;
            acurrentptr=acurrentptr->pbefore;
        }
        currentptr=pheader;
        for( int i=0;i<port.size;i++ )
        {
            currentptr->pbefore->pnext=currentptr;
            currentptr=currentptr->pbefore;
        }
        pheader=currentptr;
        size+=port.size;
    }
    else
    {
        ListNode* currentptr=pheader;
        for( int i=0;i<number-1;i++ )
            currentptr=currentptr->pnext;
        ListNode* acurrentptr=port.pheader;
        ListNode* aacurrentptr=currentptr->pnext;
        for( int i=0;i<port.size;i++ )
        {
            currentptr=currentptr->pnext=new ListNode;
            T* port=new T(*static_cast<T*>( acurrentptr->pdata ));
            currentptr->pdata=port;
            acurrentptr=acurrentptr->pnext;
        }
        currentptr=aacurrentptr->pbefore;
        for( int i=0;i<port.size;i++ )
        {
            currentptr->pnext->pbefore=currentptr;
            currentptr=currentptr->pnext;
        }
        currentptr->pnext=aacurrentptr;
        aacurrentptr->pbefore=currentptr;
        size+=port.size;
    }
}

template<class T>
void List<T>::appendAtBack( List<T>& port )
{
    ListNode* currentptr=prear;
    ListNode* acurrentptr=port.pheader;
    for( int i=0;i<port.size;i++ )
    {
        currentptr=currentptr->pnext=new ListNode;
        T* port=new T(*static_cast<T*>( acurrentptr->pdata ));
        currentptr->pdata=port;
        acurrentptr=acurrentptr->pnext;
    }
    currentptr=prear;
    for( int i=0;i<port.size;i++ )
    {
        currentptr->pnext->pbefore=currentptr;
        currentptr=currentptr->pnext;
    }
    prear=currentptr;
    size+=port.size;
}

template<class T>
void List<T>::swap( int number1, int number2 )
{
    Listiter<T>* port1=this->listGetIterator();
    Listiter<T>* port2=this->listGetIterator();
    port1->listIndex( this, number1 );
    port2->listIndex( this, number2 );
    void* port=port1->ptr->pdata;
    port1->ptr->pdata=port2->ptr->pdata;
    port2->ptr->pdata=port;
}

template<class T>
void List<T>::listRotate()
{
    ListNode* currentptr=pheader;
    ListNode* acurrentptr=prear;
    for( int i=0;i<=( size-1 )/2;i++ )
    {
        void* port=currentptr->pdata;
        currentptr->pdata=acurrentptr->pdata;
        acurrentptr->pdata=port;
        currentptr=currentptr->pnext;
        acurrentptr=acurrentptr->pbefore;
    }
}

template<class T>
int List<T>::getsize() const
{
    return size;
}

template<class T>
bool List<T>::removeFromFront()
{
    if( isEmpty() )
    {
        return false;
    }
    else
    {
        ListNode* currentptr=pheader;
        pheader=pheader->pnext;
        pheader->pbefore=NULL;
        delete currentptr;
        size--;
        return true;
    }
}

template<class T>
bool List<T>::removeFrom( int number )
{
    if( isEmpty() )
    {
        return false;
    }
    else if( number == size )
    {
        ListNode* currentptr=prear;
        prear=prear->pbefore;
        prear->pnext=NULL;
        delete currentptr;
        return true;
    }
    else if( number == 1)
    {
        ListNode* currentptr=pheader;
        pheader=pheader->pnext;
        pheader->pbefore=NULL;
        delete currentptr;
        return true;
    }
    else
    {
        ListNode* currentptr=pheader;
        for( int i=0;i<number-1;i++ )
            currentptr=currentptr->pnext;
        ListNode* acurrentptr=currentptr->pnext;
        currentptr->pbefore->pnext=acurrentptr;
        acurrentptr->pbefore=currentptr->pbefore;
        delete currentptr;
        size--;
        return true;
    }
}

template<class T>
bool List<T>::removeFromBack()
{
    if( isEmpty() )
    {
        return false;
    }
    else
    {
        ListNode* currentptr=prear;
        prear=prear->pbefore;
        prear->pnext=NULL;
        delete currentptr;
        size--;
        return true;
    }
}

template<class T>
bool List<T>::isEmpty() const
{
    return pheader == NULL;
}

template<class T>
T& List<T>::operator[]( int number )
{
    ListNode* currentptr=pheader;
    for( int i=0;i<number;i++ )
        currentptr=currentptr->pnext;
    return *static_cast<T*>(currentptr->pdata);
}

template<class T>
T List<T>::operator[]( int number ) const
{
    ListNode* currentptr=pheader;
    for( int i=0;i<number;i++ )
        currentptr=currentptr->pnext;
    return *static_cast<T*>(currentptr->pdata);
}

template<class T>
ListNode* List<T>::getpheader() const
{
    return pheader;
}

template<class T>
ListNode* List<T>::getprear() const
{
    return prear;
}

template<class T>
Listiter<T>* List<T>::listGetIterator()
{
    Listiter<T>* port=new Listiter<T>;
    port->ptr=pheader;
    return port;
}

template<class T>
List<T>& List<T>::operator=( List& port )
{
    size=port.size;
    if( port.isEmpty() )
        pheader=prear=NULL;
    else
    {
        ListNode* currentptr=pheader;
        ListNode* tempptr;
        while( currentptr != 0 )
        {
            tempptr=currentptr;
            currentptr=currentptr->pnext;
            delete tempptr;
        }
        pheader=new ListNode;
        pheader->pdata=port.pheader->pdata;
        currentptr=pheader;
        ListNode* acurrentptr=port.pheader;
        for( int i=1;i<size;i++ )
        {
            acurrentptr=acurrentptr->pnext;
            currentptr=currentptr->pnext=new ListNode;
            currentptr->pdata=acurrentptr->pdata;
        }
        prear=currentptr;
        currentptr=pheader;
        for( int i=1;i<size;i++ )
        {
            currentptr->pnext->pbefore=currentptr;
            currentptr=currentptr->pnext;
        }
    }
    return *this;
}

#endif // LIST
