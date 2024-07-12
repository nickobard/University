#include<iostream>
using namespace std;

class CSinglyLinkedList {
    struct CNode {
      int val;
      CNode * next;
    };
  public:
    CSinglyLinkedList();
    ~CSinglyLinkedList();
    CSinglyLinkedList &insert_front(int val);
    bool remove_front();
    CSinglyLinkedList &insert_back(int val);
    bool removeDuplicates();
    bool remove_back();
    bool insert_before(const size_t pos, const int val);
    const CNode * return_pos(const size_t pos) const;
    bool remove_pos(const size_t pos) ;

    //bool insert_before(const CNode * pos, const int val);
    bool empty() const;
    void display() const;
    size_t size_through() const;
    size_t size() const;
  private:
  CNode * m_head;
  size_t m_size;
  
};
CSinglyLinkedList::CSinglyLinkedList()
: m_head (nullptr),
  m_size (0)
{}
CSinglyLinkedList::~CSinglyLinkedList()
{
    CNode * current = m_head;
    while (current){ //if current is nullptr, then do nothing
    // else assign current to the next, ant delete this one
      current = current->next;
      delete m_head;
      m_head = current;
  }
}



CSinglyLinkedList &CSinglyLinkedList::insert_front(int val){
  CNode * new_node = new CNode;
  //overflow condition
  if (empty()){
    new_node->next = nullptr;
  }
  else{
    CNode * tmp = m_head;
    new_node->next = tmp;
  }
  m_head = new_node;
  new_node->val = val;
  m_size++;
  return *this;
}

CSinglyLinkedList &CSinglyLinkedList::insert_back(int val){
  CNode * new_node = new CNode;
  //overflow condition
  if (empty()){
    m_head = new_node;
    new_node->val = val;
  }
  else{
    CNode * current = m_head;
    while (current->next){
      current = current->next;
    }
    current->next = new_node;
  }
    new_node->next = nullptr;
    new_node->val = val;
    m_size++;
  return *this;
}

bool CSinglyLinkedList::remove_front(){
  //underflow condition
if (!empty()){
  CNode * tmp = m_head;
  m_head = m_head->next;
  delete tmp;
  m_size--;
  return true;
}
return false;
}
bool CSinglyLinkedList::remove_back(){
  //underflow condition
if (!empty()){

  CNode * precurrent, * current = m_head;
  if (!current->next){
    delete current;
    m_head = nullptr;
    return true;
  }
  while(current->next){
    precurrent = current;
    current = current->next;
  }
  precurrent->next = nullptr;
  delete current;
  m_size--;
  return true;
}
return false;
}


bool CSinglyLinkedList::empty() const{
  return m_head ? false : true ;
} 

size_t CSinglyLinkedList::size_through() const{
  if (!empty()){
    size_t size = 0;
    CNode * current = m_head;
    while (current){
      current = current->next;
      size++;
    }
    return size;
  }
  return 0;
}

size_t CSinglyLinkedList::size() const{
  return m_size;
}


void CSinglyLinkedList::display() const{
  if (!empty()){
    cout << m_head->val;
    CNode * current = m_head->next;
    while (current){
      cout << " -> " << current->val ;
      current = current->next;
    }
    cout << endl;
    return;
  }
  cout << "List is empty." << endl;
}

bool CSinglyLinkedList::removeDuplicates(){
  //underflow condition
  if (!empty()){
    size_t used = 0, cap = 0;
    int * data = nullptr;

    CNode * ptr = m_head;
    CNode * preptr = nullptr;

    while (ptr){
      for ( size_t i = 0; i < used; i++ ){
        if ( data[i] == ptr->val)
        {
          preptr->next = ptr->next;
          delete ptr;
          m_size--;
          ptr = nullptr;
          break;
        }
      }
      if (ptr)
      {
        if (used >= cap){
          cap = 10 + 2 * cap;
          int * tmp = new int [cap];
          for (size_t i = 0; i < used; i++){
            tmp[i] = data[i];
          }
          delete [] data;
          data = tmp;
        }
        data[used] = ptr->val;
        used ++;
        preptr = ptr;
        ptr = ptr->next;
      }
      else{
        ptr = preptr->next;
      }
    }
  delete [] data;
  return true;
  }
  return false;
}

bool CSinglyLinkedList::insert_before(const size_t pos, const int val){
  //overflow condition
  if ( pos < m_size){
    CNode * ptr = m_head;
    CNode * tmp = nullptr;
    CNode * new_node = new CNode;

    for ( size_t i = 0; i < pos; i++ ){
      tmp = ptr;
      ptr = ptr->next;
    }
    if (tmp){
    tmp->next = new_node;
    }
    else{
      m_head = new_node;
    }
    new_node->next = ptr;
    new_node->val = val;
    m_size++;
    return true;
  }
  return false;
}

const CSinglyLinkedList::CNode * CSinglyLinkedList::return_pos(const size_t pos) const{
  //overflow condition
  if ( pos < m_size ){
    CNode *ptr = m_head;
    for ( size_t i = 0; i < pos; i++)
    {
      ptr = ptr->next;
    }
    return ptr;
  }
  return nullptr;
}

bool CSinglyLinkedList::remove_pos(const size_t pos) {
  //overflow and underflow condition
  if ( pos < m_size){
    CNode * ptr = m_head;
    CNode * preptr = nullptr;
    for ( size_t i = 0; i < pos; i++){
      preptr = ptr;
      ptr = ptr->next;
    }
    if (preptr){
      preptr->next = ptr->next;
    }
    else{
      m_head = ptr->next;
    }
    delete ptr;
    m_size--;
    return true;
  }
  return false;
}


int main(){
  CSinglyLinkedList a;
  a.insert_front(10).insert_front(20).insert_front(30)
   .insert_front(40).insert_front(50).insert_front(60);
  a.display();
  cout << "size_through: " << a.size_through() << endl;
  cout << "size: " << a.size() << endl;

  a.insert_back(20);
  a.insert_back(30);
  a.insert_back(40);
  a.insert_back(50);
  a.insert_back(60);

  a.display();
  cout << "size_through: " << a.size_through() << endl;
  cout << "size: " << a.size() << endl;

  a.remove_back();
  a.remove_back();
  a.remove_back();
  a.remove_front();
  a.remove_front();
  a.remove_front();
  a.display();
  cout << "size_through: " << a.size_through() << endl;
  cout << "size: " << a.size() << endl;
  a.removeDuplicates();
  a.display();
  cout << "size: " << a.size() << endl;

  

  a.insert_back(10);
  a.insert_back(10);
  a.insert_back(10);
  a.insert_back(10);
  a.insert_back(10);
  a.display();
  cout << "size: " << a.size() << endl;
  a.removeDuplicates();
  a.display();
  cout << "size: " << a.size() << endl;
  a.insert_before(0,50);
  a.insert_before(2,50);
  a.insert_before(4,50);
  a.insert_before(6,50);
  a.display();
  a.remove_pos(0);
  a.display();
  a.remove_pos(4);
  a.remove_pos(4);
  a.display();
  cout << "size_through: " << a.size_through() << endl;
  cout << "size: " << a.size() << endl;

  a.remove_back();
  a.remove_back();
  a.remove_back();
  a.remove_back();
  a.remove_back();
  a.display();
  a.insert_back(10);
  a.insert_back(10);
  a.insert_back(10);
  a.insert_back(10);
  a.display();

  a.remove_front();
  a.remove_front();
  a.remove_front();
  a.remove_front();
  a.display();
  a.insert_back(10);
  a.display();

  return 0;
}