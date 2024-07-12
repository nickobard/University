//  #EX_BEGIN
#include "CEFaceMask.h"
//  #EX_END

CEFaceMask &CEFaceMask::addContact( const CContact &contact ){
  if ( !contact.eqNums() )
    m_Contacts.push_back(contact);
  return *this;
}

map<int,int> CEFaceMask::getSpreaders (vector<CContact> &src) const{
  map <int,int> spreaders;
  for_each(src.cbegin(),src.cend(),
  [&](const CContact &contact)
  {
    if (auto res = spreaders.insert({contact.phones.first, 1}); !res.second)
      ++res.first->second;
    if (auto res = spreaders.insert({contact.phones.second, 1}); !res.second)
      ++res.first->second;
  });
  return spreaders;
}


vector<CContact> CEFaceMask::getContactsFromRange(const CTimeStamp &from,
                                                  const CTimeStamp &to ) const{
  vector<CContact> possibleContacts;

  copy_if(m_Contacts.cbegin(),m_Contacts.cend(),
          back_inserter(possibleContacts),
          [&](const CContact &contact)
          { return contact.m_Timestamp >= from && 
                   contact.m_Timestamp <= to;});
  return possibleContacts;
}
void CEFaceMask::getSorted (vector<CContact> &src) const{
  for_each(src.begin(),src.end(),[](CContact &el){
     if (el.phones.first > el.phones.second)
      swap(el.phones.first,el.phones.second);
     });

  sort(src.begin(),src.end(),
        [](const CContact &lhs, const CContact &rhs){
          return lhs.phones < rhs.phones;
        });
}


void CEFaceMask::getUnique(vector<CContact> &src) const{
  
  auto end_unique = unique(src.begin(), src.end(),
                            [](const CContact &lhs, const CContact &rhs)
                            { return lhs.phones == rhs.phones;  });

  src.erase(end_unique, src.end());
}

vector<int> CEFaceMask::getSuperSpreaders( const CTimeStamp &from,
                                           const CTimeStamp &to )
{

  vector<CContact> possibleContacts = getContactsFromRange(from, to);
  getSorted(possibleContacts);
  getUnique(possibleContacts);
  map<int,int> spreaders = getSpreaders(possibleContacts);

   const int max = max_element(spreaders.cbegin(),spreaders.cend(),
   [](const map<int,int>::value_type &lhs,
      const map<int,int>::value_type &rhs )
  {
    return lhs.second < rhs.second;
  }) -> second;

  vector<int> superSpreaders;
  for_each (spreaders.cbegin(), spreaders.cend(),[&](const map<int,int>::value_type &src)
  {
    if ( src.second == max ){
      superSpreaders.push_back(src.first);
    }
  });

  return superSpreaders;
}

