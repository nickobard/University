#include "CClientConn.h"

CClientConn::CClientConn( int socket )
: m_ClientSocket (socket)
, m_ServerKeys ({ {23019, 32037},   // 0
                  {32037, 29295},   // 1
                  {18789, 13603},   // 2
                  {16443, 29533},   // 3
                  {18189, 21952} }) // 4
, m_Robot({})
, m_OldPos({})
{}

CClientConn::~CClientConn(){
  close (m_ClientSocket);
}

void CClientConn::client_timeout( int time ){
                              
    FD_ZERO(&m_Sockets);
    FD_SET(m_ClientSocket, &m_Sockets);
    m_Timeout.tv_sec = time;
    m_Timeout.tv_usec = 0; 

    int retval = select( m_ClientSocket + 1,
                        &m_Sockets, NULL, NULL,
                        &m_Timeout );

    if ( retval < 0 ){
      IN_FUNC;
      perror ("Server: error with select()");
      throw exception();
    }

    if (!FD_ISSET(m_ClientSocket, &m_Sockets)){
      IN_FUNC;
      throw runtime_error("Server: connection timeout!");
    }
}

void CClientConn::client_process (){
  authentication(); 
  robot_start();
}

int CClientConn::client_recieve(string &input){
  int m_BytesRead = recv (m_ClientSocket,
                          m_Buffer, 
                          BUFFER_SIZE - 1, 0);
  if (m_BytesRead <= 0){
    IN_FUNC;
    perror("Server: error reading from client");
    throw exception();
  }
  m_Buffer[m_BytesRead] = '\0';
  input = string {begin(m_Buffer), (size_t)m_BytesRead};
  }
  return m_BytesRead;
}

int CClientConn::client_send(const string &output) const {
  int bytes = send (m_ClientSocket,
                    output.data(),
                    output.size(),
                    MSG_NOSIGNAL);
  if (bytes <= 0){
    IN_FUNC;
    perror ("Client: couldn't send buffer");
    throw exception();
  }
  return bytes;
}


void CClientConn::authentication(){
  string username;
  take_answer(ROBOT_TIMEOUT, 20, username);
  client_send("107 KEY REQUEST\a\b");

  int key_id = client_key_id();
  client_hash(key_id,username);
}


bool CClientConn::process_answer(const size_t size,
                               string &output ){

  auto pos =  m_BufferData.find (DELIM);
  if ( pos <= (size - 2)){
    output = m_BufferData.substr(0,pos);
    cout << __func__ 
         << ": Processed answer: " + output 
         << " , size: " << output.size()
         << endl;
    m_BufferData = m_BufferData.substr(pos + 2);  
    cout << __func__ 
         << ": Remaining buffer: " + m_BufferData 
         << " , size: " << m_BufferData.size()
         << endl;
    return true;
  }
  else if ( pos > m_BufferData.size()  ){
    if ( m_BufferData.size() >= size ){
      client_send("301 SYNTAX ERROR\a\b");
      IN_FUNC;
      throw runtime_error("Wrong answer, size exceeded: " + m_BufferData);
    }
      
    cout << __func__ 
         << ": delimiter not found, keep recieving: "
         << endl;
    return false;
  }
  else 
  {
    client_send("301 SYNTAX ERROR\a\b");
    IN_FUNC;
    throw runtime_error("Wrong answer, size exceeded: " + m_BufferData);
  }
  return true;
  }



  void CClientConn::take_answer (const int timeout,
                      const size_t size,
                      string &output ){
  string tmp;
  while (true){

  if (timeout != RECHARGING_TIMEOUT)
    check_recharging();
  
  if (! process_answer(size, output)){

  client_timeout(timeout);
      
  cout << endl;
  cout << __func__ << ": Current buffer: " + m_BufferData 
       << " , size: " << m_BufferData.size()
       << endl;

  client_recieve(tmp);
  m_BufferData += tmp;

  cout << __func__ << ": Data recieved: " + tmp 
       << " , size: " << tmp.size()
       << endl;

  cout << __func__ << ": New buffer: " + m_BufferData 
       << " , size: " << m_BufferData.size()
       << endl;
  cout << endl;
  continue;
  }
  else
    return;
  }
}

void CClientConn::check_recharging(){
    auto pos =  m_BufferData.find (DELIM);
    if (pos >= m_BufferData.size())
      return;
    string tmp = m_BufferData.substr(0,pos);
    if ( tmp == "RECHARGING"	|| tmp == "FULL POWER" ){
      if ( tmp == "FULL POWER"){
        IN_FUNC;
        client_send("302 LOGIC ERROR\a\b"	);
        throw runtime_error("Full power before recharging. Exit.");
      }
      m_BufferData = m_BufferData.substr(pos + 2); 
      robot_recharging();
    }
}

void CClientConn::robot_recharging(){
  string msg;
  take_answer(RECHARGING_TIMEOUT,12,msg);
  if ( msg != "FULL POWER" ){
    IN_FUNC;
    client_send("302 LOGIC ERROR\a\b"	);
    throw runtime_error("Logic error: Not full power after recharging");
  }
}


int CClientConn::client_key_id(){
  string answer;
  cout << __func__ << ": Asking for key-id." << endl;
  take_answer(ROBOT_TIMEOUT,5,answer);

  if (!digitAnswer(answer)){
    client_send("301 SYNTAX ERROR\a\b");
    throw exception();
  }
  int id = atoi(answer.data());
  if (id < 0 || id > 4 ){
    IN_FUNC;
    client_send("303 KEY OUT OF RANGE\a\b");
    throw runtime_error("Key out of range.");
  }
  cout << __func__ << "key-id is: " 
       << id << ": "
       << m_ServerKeys[id].first << ", "
       << m_ServerKeys[id].second << endl;
  return id;
}

bool CClientConn::digitAnswer (const string & str) const{
  if (str.at(0) == '0' && str.size() > 1){
    cout << __func__ << ": Error: key-ID: 0 at the beginning." << endl;
    return false;
  }
for ( size_t i = 0; i < str.size(); i++){
    if ( i == 0 && str[i] == '-'){
      continue;
    }
    if (! isdigit(str[i])){
      cout << __func__ << ": Error: key-ID: not digit." << endl;
      return false;
    }
  }
  return true;
}

void CClientConn::client_hash (const int id, const string &username){
  cout << __func__ << ": Making hash from username: " + username
       << endl;
  int hash_base = 0;
  for (const auto &c : username ){
    hash_base += (int) c;
  }
  hash_base = (hash_base * 1000) % 65536;

  int hash_serv = (hash_base + m_ServerKeys[id].first) % 65536;

  stringstream ss;
  ss << hash_serv;
  string msg;
  ss >> msg;
  msg += "\a\b";

  cout << __func__ << ": Sending server hash: " << msg << endl;
  client_send(msg);
  cout << __func__ << ": Asking for hash." << endl;
  take_answer(ROBOT_TIMEOUT,7UL,msg);
  cout << __func__ << ": Recieved hash: " + msg << endl;
  if ( !digitAnswer(msg)){
    client_send("301 SYNTAX ERROR\a\b");
    throw exception();
  }
  
  int hash_client = atoi(msg.data());
  if( hash_client == (hash_base + m_ServerKeys[id].second) % 65536 ){
    client_send("200 OK\a\b");
    cout << __func__ << ": Server OK." << endl;
    return;
  }
  else{
    IN_FUNC;
    client_send("300 LOGIN FAILED\a\b");
    throw runtime_error("Server login failed.");
  }
}

