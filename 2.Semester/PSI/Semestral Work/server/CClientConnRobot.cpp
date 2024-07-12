#include "CClientConn.h"

void CClientConn::robot_start (){
  robot_move();
  string answer;
  bool nextPhase = false;
  while (true){

    /* take_answer(ROBOT_TIMEOUT,12,answer);
    robot_process_answer(answer); */
    if ( m_Robot.m_X == 0 && m_Robot.m_Y == 0){
      robot_secret_msg();
      return;
    }
    
    if (m_Robot.m_Dir == NULL_VALUE){
      get_orientation();
      printOrientation();
      robot_align_orientation();
    }
    
    if (m_Robot.m_Y != 0 && !nextPhase){
      move_vertically();
      continue;
    }

    if ( !nextPhase ){
      robot_align_orientation();
      nextPhase = true;
    }
    move_horizontally();
  }
}

void CClientConn::robot_get_report(){
    string tmp;
    take_answer(ROBOT_TIMEOUT,12,tmp);
    robot_process_answer(tmp);
}


void CClientConn::robot_left (){
  client_send("103 TURN LEFT\a\b"	);
  cout << "\n" << __func__ << "\n" << endl;
  robot_get_report();
}
void CClientConn::robot_right (){
  client_send("104 TURN RIGHT\a\b"	);
  cout << "\n" << __func__ << "\n" << endl;
  robot_get_report();

}
void CClientConn::robot_move (){
  client_send("102 MOVE\a\b"	);
  cout << "\n" << __func__ << "\n" << endl;
  m_OldPos = m_Robot;
  robot_get_report();
  cout << __func__ << ": Old coords: " 
       << "{ " << m_OldPos.m_X << ", " << m_OldPos.m_Y << " }" 
       << endl;
  cout << __func__ << ": New coords: " 
       << "{ " << m_Robot.m_X << ", " << m_Robot.m_Y << " }" 
       << endl;
}

bool CClientConn::robot_get_coords(const string &str){
  stringstream ss (str);
  string dummy;
  int x, y;

  if ( ! (ss >> dummy >> x >> y )
          || dummy != "OK"
          || !ss.eof())
    return false;
  m_Robot.m_X = x;
  m_Robot.m_Y = y;
  cout << __func__ << ": Get coordinates: " << x << ", " << y << endl;
  return true;
}

void CClientConn::robot_secret_msg(){
  cout << __func__ << ": Get secret message." << endl;
  client_send("105 GET MESSAGE\a\b") ;
  string msg;
  take_answer(ROBOT_TIMEOUT,100,msg);
  cout << __func__ << ": Secret message:\n\t" + msg << endl;
  client_send("106 LOGOUT\a\b");
}

void CClientConn::robot_process_answer(const string &answer){
  
  if ( ! robot_get_coords(answer) ){
    client_send("301 SYNTAX ERROR\a\b");
    throw exception();
  }
}

void CClientConn::get_orientation (){
  cout << __func__ << ": Getting orientation." << endl;
  string answer;
  robot_move();
  if ( m_OldPos.m_X != m_Robot.m_X){
    if ( m_OldPos.m_X < m_Robot.m_X )
      m_Robot.m_Dir = RIGHT;
    else
      m_Robot.m_Dir = LEFT;
    return;
  }
  else if (m_OldPos.m_Y != m_Robot.m_Y){
    if (m_OldPos.m_Y < m_Robot.m_Y)
      m_Robot.m_Dir = UP;
    else
      m_Robot.m_Dir = DOWN;
    return;
  }
  else{
    robot_right();
    get_orientation();
  }
}

void CClientConn::printOrientation(){
  cout << __func__ << ": orientations is: ";
  switch (m_Robot.m_Dir){
    case UP: cout << "UP"; break;
    case DOWN: cout << "DOWN"; break;
    case RIGHT: cout << "RIGHT"; break;
    case LEFT: cout << "LEFT"; break;
    default: cout << "NULL"; break;
  }
  cout << " at coords: " << "{ " << m_Robot.m_X
                         << ", " << m_Robot.m_Y 
                         << " }" << endl;
}

void CClientConn::robot_align_orientation(){
  cout << __func__ << ": aligning orientation." << endl;
  if ( m_Robot.m_Y == 0){
    if (m_Robot.m_Dir == UP){
      if (m_Robot.m_X > 0)
        robot_look_left();
      else
        robot_look_right();
    }
    else {
      if (m_Robot.m_X > 0)
        robot_look_right();
      else
        robot_look_left();
    }
  }
  else if (m_Robot.m_Y > 0)
    robot_look_down();
  else
    robot_look_up();
  printOrientation();
}


void CClientConn::robot_look_left(){
  int d = m_Robot.m_Dir;
  if (d == LEFT)
    return;
  if (d == UP)
    robot_left();
  if (d == DOWN)
    robot_left();
  if (d == RIGHT){
    robot_left();
    robot_left();
  }
  m_Robot.m_Dir = LEFT;
}

void CClientConn::robot_look_right(){
  int d = m_Robot.m_Dir;
  if (d == RIGHT)
    return;
  if (d == DOWN)
    robot_right();
  if (d == UP)
    robot_right();
  if (d == LEFT){
    robot_left();
    robot_left();
  }
  m_Robot.m_Dir = RIGHT;
}

void CClientConn::robot_look_up(){
  int d = m_Robot.m_Dir;
  if (d == UP)
    return;
  if (d == RIGHT)
    robot_left();
  if (d == LEFT)
    robot_right();
  if (d == DOWN){
    robot_left();
    robot_left();
  }
  m_Robot.m_Dir = UP;
}

void CClientConn::robot_look_down(){
  int d = m_Robot.m_Dir;
  if (d == DOWN)
    return;
  if (d == LEFT)
    robot_left();
  if (d == RIGHT)
    robot_right();
  if (d == UP){
    robot_left();
    robot_left();
  }
  m_Robot.m_Dir = DOWN;
}

void CClientConn::move_vertically(){
  cout << __func__ << ": Moving vertically." << endl;
  robot_move();
  if (m_Robot.m_Y == m_OldPos.m_Y){
    move_corner();
  }
}

void CClientConn::move_around(){
    cout << __func__ << ": get blocked! Moving around at:" << endl;
    printOrientation();
    robot_left();
    robot_move();
    robot_right();
    robot_move();
    robot_move();
    robot_right();
    robot_move();
    robot_left();
}

void CClientConn::move_corner(){
  cout << __func__ << ": get blocked! Moving around the corner at:" << endl;
  printOrientation();
  if (m_Robot.m_Dir == UP){
    if ( m_Robot.m_X > 0){
      robot_left();
      robot_move();
      robot_right();
      robot_move();
    }
    else{
      robot_right();
      robot_move();
      robot_left();
      robot_move();
    }
  }
  else{
    if ( m_Robot.m_X > 0){
      robot_right();
      robot_move();
      robot_left();
      robot_move();
    }
    else{
      robot_left();
      robot_move();
      robot_right();
      robot_move();
    }
  }
}

void CClientConn::move_horizontally(){
  cout << __func__ << ": Moving horizontally." << endl;
  robot_move();
  if (m_Robot.m_X == m_OldPos.m_X){
    move_around();
  }

}
