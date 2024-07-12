#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <climits>
#include <sstream>
using namespace std;

class CGuessAnimal{
    struct TNode{
      TNode * m_Yes;
      TNode * m_No;
      string str;
    };
  public:
    CGuessAnimal();
    ~CGuessAnimal();
    void startGame() ;
  private:
    TNode * createNode (const string &str, TNode * yes, TNode * no);
    bool delTree(TNode * n);
    bool positiveAnswer() const;
    bool isLeaf (const TNode * n ) const ;
    bool strcmpare(const string &a, const string &b ) const;
    void updateKnowledge(TNode *n);
    TNode * m_Root;
};

CGuessAnimal::CGuessAnimal ()
: m_Root (nullptr)
{
  m_Root = createNode("Leta?",
    createNode("ptak",nullptr,nullptr),
    createNode("ryba",nullptr,nullptr));
}

CGuessAnimal::~CGuessAnimal (){
  delTree(m_Root);
}

bool CGuessAnimal::delTree(TNode * n){
  if (!n)
    return false;
  delTree(n->m_No);
  delTree(n->m_Yes);
  delete n;
  return true;
}

CGuessAnimal::TNode * CGuessAnimal::createNode (const string &str, TNode * yes, TNode * no){
  return new TNode {yes,no,str};
}

bool CGuessAnimal::strcmpare(const string &a, const string &b ) const{
  size_t minSize;
  if ( a.size() < b.size())
    minSize = a.size();
  else
    minSize = b.size();
for ( size_t i = 0; i < minSize; i++ ){
  if ( tolower(a[i]) != tolower(b[i]) )
    return false;
}
return true;
}

bool CGuessAnimal::positiveAnswer() const{
  string ans;
  while(cin >> ans){
    if (strcmpare(ans,"Ano"))
      return true;
    else if(strcmpare(ans,"Ne"))
      return false;
    else{
      cout << "Nerozumim. Rekni jeste jednou. (Ano/Ne)" << endl;
      cin.ignore(INT_MAX,'\n');
      continue;
    }
  }
    throw invalid_argument("Chyba: zadny nebo nevalidni vstup.");
    return false;
}

bool CGuessAnimal::isLeaf (const TNode * n ) const {
  return !n->m_Yes && !n->m_No;
}

void CGuessAnimal::updateKnowledge(TNode *n){
  string newA, newQ;
  cout << "Neuhadl jsem "
          "Prosim o doplneni mych znalosti:" << endl;
  cout << "Jake zvire jsi myslel/a?" << endl;
  cin.ignore(INT_MAX,'\n');
  if (!getline(cin,newA))
    throw invalid_argument("Chyba: zadny nebo nevalidni vstup.");
  cout << "Otazka vystihujici rozdil mezi " + newA + " a " + n->str + "?" << endl;
  if (!getline(cin, newQ))
    throw invalid_argument("Chyba: zadny nebo nevalidni vstup.");
  cout << "Jaka odpoved je pro " + newA + "?" << endl;
    if (positiveAnswer()){
      n->m_Yes = createNode(newA,nullptr,nullptr);
      n->m_No = createNode(n->str,nullptr,nullptr);
    } else {
      n->m_Yes = createNode(n->str,nullptr,nullptr);
      n->m_No = createNode(newA,nullptr,nullptr);
    }
    n->str = newQ;
}

void CGuessAnimal::startGame() {
  do{
  cout << "Vyber si nejake zvire. Ja to uhodnu." << endl;
  cout << "Jsi pripraven?" << endl;
  if (!positiveAnswer())
    return;
  TNode * n = m_Root;
    while (!isLeaf(n)){
      cout << n->str << endl;
      if ( positiveAnswer())
        n = n->m_Yes;
      else
        n = n->m_No;
    }
    cout << "Je to " + n->str + "?" << endl;
    if (!positiveAnswer())
      updateKnowledge(n);
    else
      cout << "Uhadl jsem!" << endl;
    cout << "Chces pokracovat?" << endl;
  } while (positiveAnswer());
}


int main (){
  CGuessAnimal a;
  a.startGame();
  /*
  string str;
  cin >> str;
  cout << str << endl;
  */
  return 0;
}