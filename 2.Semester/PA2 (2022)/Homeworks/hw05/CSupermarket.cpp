// #EX_BEGIN
#include "CSupermarket.h"
// #EX_END

CSupermarket &CSupermarket::store (const string &name,
                                   const CDate  &date,
                                   const int count ){
  if (auto outerTrade = m_Trade.find(name); 
           outerTrade != m_Trade.end()){ // exists
    if ( auto innerTrade 
            = outerTrade->second.insert({date, make_shared<int>(count)});
            innerTrade.second){ // date does not exist under this name
      if ( auto outerExpire = m_Expire.find(date); 
                outerExpire != m_Expire.end()) {
                  // such date exists under other names
                  outerExpire->second.insert({name,innerTrade.first->second});
      }
      else{
        // no such date at all
        auto innerExpier = m_Expire.insert({date,{}});
        innerExpier.first->second.insert({name,innerTrade.first->second});
      } 
    }
    else  // date exists under this name
            *innerTrade.first->second += count;
    }
  else {
    auto ret = m_Names.insert({name.size(),{}});
    ret.first->second.emplace(name);
    auto insertTrade = m_Trade.insert({name,{}});
    auto innerInsertTrade = 
         insertTrade.first->second.insert({date, make_shared<int>(count)});
    if( auto outerExpire = m_Expire.find(date); 
             outerExpire != m_Expire.end()){
               // such date exists but under other names
               outerExpire->second.insert({name,innerInsertTrade.first->second});
             }
    else{ // no such date at all
    auto insertExpire = m_Expire.insert({date, {}});
    insertExpire.first->second.insert({name,innerInsertTrade.first->second});
    }
    
  }
  return *this;
}

void CSupermarket::catCounters ( list<pair<string,int>> &expired ) const{

  expired.sort ([] (const pair<string,int> &lhs, 
                    const pair<string,int> &rhs)
                   {return lhs.first < rhs.first; });
  expired.unique([]( pair<string,int> &lhs, 
                     pair<string,int> &rhs) 
                   {if ( lhs.first == rhs.first ){
                      lhs.second += rhs.second;
                      return true;
                   } 
                   return false;});
}


list<pair<string,int>> CSupermarket::expired ( const CDate &date ) const{

list<pair<string,int>> expired;

  auto ret = m_Expire.lower_bound(date);

  for ( auto start = m_Expire.begin(); start != ret; ++start ){
    for ( auto in_start = start->second.begin(),
               in_end   = start->second.end();
          in_start != in_end; ++in_start ){
            expired.emplace_back(in_start->first,*in_start->second);
          }
  }

  catCounters(expired);

  expired.sort ([] (const pair<string,int> &lhs, 
                    const pair<string,int> &rhs)
                   {return lhs.second > rhs.second; });
        
  return expired;
}
// true if matched even with one char mistake
bool CSupermarket::notExactMatch(const string &lhs,
                                 const string &rhs ){
  if (lhs.size() != rhs.size())
    return false;

  int cnt = 0;
  for (size_t i = 0; i < lhs.size(); i++ ){
    if (cnt > 1)
      return false;
    if ( lhs[i] != rhs[i])
      cnt ++;
  }
  return true;
}


pair<string, bool> CSupermarket::notExactSearch (const string &str) const{

  string matchedStr;
  bool   firstMatch = false;
  auto ret = m_Names.find(str.size());
  if (ret == m_Names.end())
    return {"", false};
  

  for ( auto it = ret->second.begin(); it != ret->second.end(); ++it){
    if (firstMatch && notExactMatch(*it,str)){
      return {"",false};
    }
    else if ( notExactMatch(*it,str)){
      firstMatch = true;
      matchedStr = *it;
    }
  }
  if (firstMatch)
    return {matchedStr, true};
  return {"", false};
}

void CSupermarket::processTransaction(list<pair<string,int>> &orders,
                                      list<pair<string,int>>::
                                      iterator &order,
                                      const string &key)  
                                      {
  
  auto available = m_Trade.find(key);
  if (available == m_Trade.end())
    return;
  for ( auto date = available->second.begin(),
             end  = available->second.end();
             date != end; )
             {
               if ( order->second < *date->second){
                 *date->second -= order->second;
                 orders.erase(order);
                 return;
               }
               else if ( order->second == *date->second){
                 
                 auto exp_Date = m_Expire.find(date->first);
                 exp_Date->second.erase(key);
                 if (exp_Date->second.empty())
                    m_Expire.erase(exp_Date);

                 available->second.erase(date);
                 if ( available->second.empty())
                  m_Trade.erase(available);

                 orders.erase(order);

                 auto ret = m_Names.find(key.size());
                 ret ->second.erase(key);
                 return;
               }
               else{
                 order->second -= *date->second;

                 auto exp_Date = m_Expire.find(date->first);
                 exp_Date->second.erase(key);
                 if (exp_Date->second.empty())
                    m_Expire.erase(exp_Date);

                 auto ret = m_Names.find(key.size());
                 ret ->second.erase(key);

                 auto tmp = next(date);
                 available->second.erase(date);
                 if (available->second.empty()){
                   m_Trade.erase(available);

                   return;
                 }
                 date = tmp;
               }
              
             }
}
/*
 */


CSupermarket &CSupermarket::sell  (list<pair<string,int>> &orders){

  vector<pair<list<pair<string,int>>::iterator, string>> transactions;

  for ( auto order = orders.begin(); order != orders.end(); ++order){
    if (m_Trade.find(order->first) != m_Trade.end()){
        transactions.push_back({order,order->first});
    }
    else if ( auto result = notExactSearch(order->first); result.second )
        transactions.push_back({order,result.first});
  }
  for ( auto order : transactions ){
    processTransaction(orders, order.first, order.second);
  }
  return *this;
}


