#include <iostream>
#include <climits>
#include <string>
#include <cctype>
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
  m_Root = createNode("Летает?",
    createNode("птица",nullptr,nullptr),
    createNode("рыба",nullptr,nullptr));
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
  //cin.clear();
  while(cin >> ans){
    if (ans == "Да" 
    ||  ans == "да"
    ||  ans == "ДА")
      return true;
    else if (ans == "Нет" 
         ||  ans == "нет"
         ||  ans == "НЕТ")
      return false;
    else{
      cout << "Не понимаю. Скажи еще раз. (Да/Нет)" << endl;
      cin.ignore(INT_MAX,'\n');
      continue;
    }
  }
    throw invalid_argument("Ошибка: неправильный или пустой вступ.");
    return false;
}

bool CGuessAnimal::isLeaf (const TNode * n ) const {
  return !n->m_Yes && !n->m_No;
}

void CGuessAnimal::updateKnowledge(TNode *n){
  string newA, newQ;
  cout << "Я не угадал. "
          "Прошу дополнить мои знания:" << endl;
  cout << "Какое животное ты загадал/а?" << endl;
  //cin.clear();
  cin.ignore(INT_MAX,'\n');
  if (!getline(cin,newA))
    throw invalid_argument("Ошибка: неправильный или пустой вступ.");
  cout << "Вопрос, который выражает разницу между " + newA + " и " + n->str + "?" << endl;
  //cin.clear();
  if (!getline(cin,newQ))
    throw invalid_argument("Ошибка: неправильный или пустой вступ.");
  cout << "Какой ответ про " + newA + "?" << endl;
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
  cout << "Загадай животное. Я его угадаю." << endl;
  TNode * n = m_Root;
    while (!isLeaf(n)){
      cout << n->str << endl;
      if ( positiveAnswer())
        n = n->m_Yes;
      else
        n = n->m_No;
    }
    cout << "Это " + n->str + "?" << endl;
    if (!positiveAnswer())
      updateKnowledge(n);
    else
      cout << "Я угадал!" << endl;
    cout << "Хочешь продолжить?" << endl;
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