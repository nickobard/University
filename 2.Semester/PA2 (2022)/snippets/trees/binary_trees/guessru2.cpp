#include <iostream>
#include <climits>
#include <string>
#include <cctype>
#include <locale>
#include <codecvt>

using namespace std;

class CGuessAnimal{
    struct TNode{
      TNode * m_Yes;
      TNode * m_No;
      wstring str;
    };
  public:
    CGuessAnimal();
    ~CGuessAnimal();
    void startGame() ;
  private:
    TNode * createNode (const wstring &str, TNode * yes, TNode * no);
    bool delTree(TNode * n);
    bool positiveAnswer() const;
    bool isLeaf (const TNode * n ) const ;
    bool strcmpare(const wstring &a, const wstring &b ) const;
    void updateKnowledge(TNode *n);
    TNode * m_Root;
};

CGuessAnimal::CGuessAnimal ()
: m_Root (nullptr)
{
  m_Root = createNode(L"Летает?",
    createNode(L"птица",nullptr,nullptr),
    createNode(L"рыба",nullptr,nullptr));
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

CGuessAnimal::TNode * CGuessAnimal::createNode (const wstring &str, TNode * yes, TNode * no){
  return new TNode {yes,no,str};
}

bool CGuessAnimal::strcmpare(const wstring &a, const wstring &b ) const{
  size_t minSize;
  if ( a.size() < b.size())
    minSize = a.size();
  else
    minSize = b.size();
for ( size_t i = 0; i < minSize; i++ ){
  if ( towlower(a[i]) != towlower(b[i]) )
    return false;
}
return true;
}

bool CGuessAnimal::positiveAnswer() const{
  wstring ans;
  //wcin.clear();
  while(wcin >> ans){
    if (strcmpare(ans, L"Да"))
      return true;
    else if (strcmpare(ans, L"Нет"))
      return false;
    else{
      wcout << L"Не понимаю. Скажи еще раз. (Да/Нет)" << endl;
      wcin.ignore(INT_MAX,'\n');
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
  wstring newA, newQ;
  wcout << L"Я не угадал. "
          L"Прошу дополнить мои знания:" << endl;
  wcout << L"Какое животное ты загадал/а?" << endl;
  //wcin.clear();
  wcin.ignore(INT_MAX,'\n');
  if (!getline(wcin,newA))
    throw invalid_argument("Ошибка: неправильный или пустой вступ.");
  wcout << L"Вопрос, который выражает разницу между " + newA + L" и " + n->str + L"?" << endl;
  //wcin.clear();
  if (!getline(wcin,newQ))
    throw invalid_argument("Ошибка: неправильный или пустой вступ.");
  wcout << L"Какой ответ про " + newA + L"?" << endl;
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
  wcout << L"Загадай животное. Я его угадаю." << endl;
  TNode * n = m_Root;
    while (!isLeaf(n)){
      wcout << n->str << endl;
      if ( positiveAnswer())
        n = n->m_Yes;
      else
        n = n->m_No;
    }
    wcout << L"Это " + n->str + L"?" << endl;
    if (!positiveAnswer())
      updateKnowledge(n);
    else
      wcout << L"Я угадал!" << endl;
    wcout << L"Хочешь продолжить?" << endl;
  } while (positiveAnswer());
}


int main (){
  ios_base::sync_with_stdio(false);

  locale utf8( locale(), new codecvt_utf8_utf16<wchar_t> );
  wcout.imbue(utf8);
  CGuessAnimal a;
  a.startGame();
  /*
  wstring str;
  wcin >> str;
  cout << str << endl;
  */
  return 0;
}