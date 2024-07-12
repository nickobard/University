#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <wait.h>

using namespace std;

constexpr int BUFFER_SIZE = 10240;
constexpr int TIMEOUT = 60;
constexpr int ROBOT_TIMEOUT = 1;
constexpr int RECHARGING_TIMEOUT = 5;
enum direction {NULL_VALUE, UP, DOWN, RIGHT, LEFT};

#define IN_FUNC std::cout << "\nIn function: " \
                          << __func__  << ": " \
                          << std::endl
#define HERE cout << "\nHERE\n" << endl

const string DELIM = "\a\b";

class CClientConn {
  struct TRobot{
    int m_Dir;
    int m_X;
    int m_Y;
  };
  public:
    CClientConn  ( int socket );
    ~CClientConn ();
    void client_process ();
    void client_timeout (int time );
    int  client_recieve (string & input);
    int  client_send (const string & output) const;

    void authentication ();
    int  client_key_id   ();
    void client_hash (const int id, const string &username);


    bool process_answer (const size_t size,
                          string &output);
    void take_answer (const int timeout,
                      const size_t size,
                      string &output);
    bool digitAnswer (const string & str) const;


    void robot_start ();
    void robot_left ();
    void robot_right ();
    void robot_move ();

    void robot_get_report();
    void robot_secret_msg();
    void robot_recharging();
    void check_recharging();
    void robot_process_answer(const string &answer);

    bool robot_get_coords(const string &str);
    
    void get_orientation ();
    void printOrientation();
    void robot_align_orientation();

    void robot_look_left();
    void robot_look_right();
    void robot_look_up();
    void robot_look_down();


    void move_vertically();
    void move_horizontally();
    void move_corner();
    void move_around();


  private:
    char           m_Buffer [BUFFER_SIZE];
    string         m_BufferData;
    fd_set         m_Sockets;
    int            m_ClientSocket;
    struct timeval m_Timeout;
    vector<pair<int,int>> m_ServerKeys;
    TRobot         m_Robot;
    TRobot         m_OldPos;
};