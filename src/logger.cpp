#include "algorithm"
#include "iostream"
#include "string"
#include "string_view"
#include "fstream"
#include "string_view"
#include "sstream"
#include "memory"
#include "vector"
#include "chrono"
#include "ctime"









class Logger
{
      std::ostream &_out;
public:

    template < typename T >
    friend Logger & operator<< (Logger & logger, T t);

    Logger(std::ostream &out) : _out{out}{};

};


template < typename T >
Logger & operator<< (Logger & logger, T in){
  logger._out << in;
  return logger;
}



int
main ()
{


  Logger ll (std::cout);
  ll << "we log everything" << " even the fact that we are logging now for "
    << 13 << "times\n";

  std::ofstream fileStreamLog("logTest.txt", std::ofstream::app);
  Logger lf (fileStreamLog);
  lf << "there is example of file log" << " we can use it as same as cout "
    << 99 << "ho ho, so we can see that overloaded endl is what we need\n";



}
