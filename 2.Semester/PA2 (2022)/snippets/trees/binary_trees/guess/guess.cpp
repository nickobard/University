#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <climits>
#include <sstream>
#include <filesystem>
#include <list>
#include <algorithm>
#include <set>
using namespace std;

const string SAVE_KEY = " _TREE_LEAF_ ";

class CGuessAnimal{
    struct TNode{
      TNode * m_Yes; // right
      TNode * m_No; // left
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
    void saveGame() const;
    void saveTree(const TNode * n, ofstream &ofs) const;
    void loadGame();
    void loadTree(TNode * &n, ifstream &ifs) ;
    set<string> filesInDir (const string &dir_name) const ;
    
    TNode * m_Root;
};

CGuessAnimal::CGuessAnimal ()
: m_Root (nullptr)
{}

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
  cout << "Ahoj, muzes zacit uplne novou hru,"
          " anebo nahrat drive ulozenou." << endl;
  cout << "Chces nahrat drive ulozenou?" << endl;
  if (positiveAnswer()){
    loadGame();
    cout << "Super, ted jdeme hrat!" << endl;
  }
  else{
    cout << "Tak zacneme novou hru!" << endl;
    m_Root = createNode("Leta?",
    createNode("ptak",nullptr,nullptr),
    createNode("ryba",nullptr,nullptr));
  }

  do{
  cout << "Vyber si nejake zvire. Ja to uhodnu." << endl;
  cout << "Jsi pripraven?" << endl;
  if (!positiveAnswer()){
    cout << "Chces ulozit hru?" << endl;
    if (positiveAnswer()){
      saveGame();
    }
    return;
  }
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

  cout << "Chces ulozit svou hru?" << endl;
  if (positiveAnswer()){
    saveGame();
  }
}


void CGuessAnimal::saveGame() const {
  cout << "Vyber slot kam ulozit hru (1, 2 or 3):" << endl;
  cout << "1. slot" << endl;
  cout << "2. slot" << endl;
  cout << "3. slot" << endl;

  int answer = 0;
  while (cin >> answer){
    if ( answer  > 0 && answer < 4)
      break;
    else
    cout << "Spatne cislo, zkus znovu." << endl;
  }

  stringstream converter;
  converter << answer;
  char slot;
  converter >> slot;
  string saveSlot = "saves/save";
  saveSlot += slot;
  saveSlot += ".txt";

  ofstream ofs;
  ofs.open(saveSlot);

  saveTree(m_Root,ofs);

}

void CGuessAnimal::saveTree(const TNode * n, ofstream &ofs) const{
  if (!n){
    ofs << SAVE_KEY << endl;
    return;
  }
  ofs << n->str << endl;
  saveTree(n->m_No, ofs);
  saveTree(n->m_Yes, ofs);
}


void CGuessAnimal::loadGame(){
  cout << "Vyber si slot ulozene hry:" << endl;
  cout << "1. slot" << endl;
  cout << "2. slot" << endl;
  cout << "3. slot" << endl;

  
  int answer = 0;
  while (cin >> answer){
    if ( answer  > 0 && answer < 4)
      break;
    else
    cout << "Spatne cislo, zkus znovu." << endl;
  }

  stringstream converter;
  converter << answer;
  char slot;
  converter >> slot;
  string saveSlot = "saves/save";
  saveSlot += slot;
  saveSlot += ".txt";

  ifstream ifs (saveSlot);
  loadTree(m_Root, ifs);
}

void CGuessAnimal::loadTree(TNode * &n, ifstream &ifs){
  string line;
  getline(ifs,line);
  if (line == SAVE_KEY)
    return;
  n = createNode ( line, nullptr, nullptr);
  loadTree(n->m_No, ifs);
  loadTree(n->m_Yes, ifs);
  
}

set<string> CGuessAnimal::filesInDir (const string &dir_name) const{
  /*
  using dir_name = filesystem::directory_entry;
  using dir_iter = filesystem::directory_iterator;
  using dir_path = filesystem::path;
*/
  set<string> entries;

  filesystem::path p(dir_name);
  filesystem::directory_iterator start (p);
  filesystem::directory_iterator end;

  for_each (start, end, 
            [&]
            (const filesystem::directory_entry &entry)
            {entries.emplace(entry.path().filename());});
  return entries;
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