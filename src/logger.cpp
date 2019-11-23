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
      std::ostream &out_;
public:
    Logger(std::ostream &out) : out_{out}{};

    template < typename T >
    friend Logger & operator<< (Logger& logger, T t);

    template <typename T>
    friend Logger & endl (Logger & logger, T in);

    Logger &operator <<(std::ostream& (*os)(std::ostream&))
     {
         (*this).out_ << os;
         return *this;
     }

    template<typename T>
    Logger& withTimestamp(T in){
    	auto timeRaw = std::chrono::system_clock::now();
    	time_t timeT = std::chrono::system_clock::to_time_t(timeRaw);
    	std::string timeHuman{std::ctime(&timeT)};
    	timeHuman.pop_back();
    	*this<<"["<<timeHuman<<"]"<<in;
    	return *this;
    }
};




template < typename T >
Logger & operator<< (Logger & logger, T in){
  logger.out_ << in;
  return logger;
}








class CompositLogger:public Logger
{
  std::vector < std::shared_ptr < Logger >> loggers;

public:
  void addLogger (std::shared_ptr < Logger > logger)
  {
    loggers.push_back (logger);
  }

 template <typename T>
 friend CompositLogger& operator<<(CompositLogger &cLogger, T in);

};


template <typename T>
CompositLogger & operator<<(CompositLogger &cLogger, T in){
	for (auto i : cLogger.loggers){
		i << in;
	}
	return cLogger;
}

//class LoggerFactory
//{
//public:
//  enum class loggerType:int
//  {
//    FILE,
//    SOUT,
//    REMOTE,
//  };
//
//    LoggerFactory (std::string_view cfgFileName):configFileName
//  {
//  cfgFileName}
//  {
//  };
//
//  std::shared_ptr < Logger > createFromCfg ()const
//  {
//    std::string cfgContent = readCfgShort ();
//    std::vector < loggerType > loggersToCreate =
//      evalueateCnfiguration (cfgContent);
//    return createLogger (loggersToCreate);
//  }
//
//
//  std::shared_ptr < Logger > createLogger (std::vector < loggerType >
//					   typesToCreate) const
//  {
//    std::shared_ptr < CompositLogger > loggerPtr =
//      std::make_shared < CompositLogger > ();
//    for (auto & i:typesToCreate)
//      {
//	switch (i)
//	  {
//	  case loggerType::FILE:
//	    {
//	      loggerPtr->addLogger (std::make_shared < FileLogger > ());
//	      break;
//	    }
//	    case loggerType::REMOTE:
//	    {
//	      loggerPtr->addLogger (std::make_shared < RemoteLogger > ());
//	      break;
//	    }
//	  case loggerType::SOUT:
//	    {
//	      loggerPtr->addLogger (std::make_shared < StdOutLogger > ());
//	      break;
//	    }
//	  default:
//	    {
//	      loggerPtr->addLogger (std::make_shared < NullLogger > ());
//	    }
//	  }
//      }
//
//    return std::static_pointer_cast < Logger > (loggerPtr);
//  }
//
//private:
//  std::string configFileName;
//
//
//  std::string readCfg ()const;
//
//  std::string readCfgShort ()const;
//
//
//  std::vector < loggerType >
//    evalueateCnfiguration (std::string_view configuration) const;
//
//};
//
//
//std::string LoggerFactory::readCfg () const
//{
//  std::fstream cfgFileStream (configFileName);
//  std::stringstream ss;
//  ss << cfgFileStream.rdbuf ();
//  return std::string (ss.str ());
//}
//
//std::string LoggerFactory::readCfgShort () const
//{
//  std::fstream cfgFileStream (configFileName);
//  return std::string (std::istreambuf_iterator < char >(cfgFileStream),
//		      std::istreambuf_iterator < char >());
//}
//
//
//std::vector < LoggerFactory::loggerType >
//  LoggerFactory::
//evalueateCnfiguration (std::string_view configuration) const
//{
//  std::vector < loggerType > usedLoggers;
//  if (configuration.find ("SOUT") != std::string::npos)
//    {
//      usedLoggers.push_back (loggerType::SOUT);
//    }
//
//  if (configuration.find ("FILE") != std::string::npos)
//    {
//      usedLoggers.push_back (loggerType::FILE);
//    }
//
//  if (configuration.find ("REMOTE") != std::string::npos)
//    {
//      usedLoggers.push_back (loggerType::REMOTE);
//    }
//
//  return usedLoggers;
//}
//
//




int
main ()
{


  Logger ll (std::cout);
  ll << "we log everything" << " even the fact that we are logging now for "
    << 13 << "times"<<std::endl;
  ll<<"and new line after endl"<<std::endl;;
  ll.withTimestamp("timestamps are useful")<<" - indeed, they are"<<std::endl;



  std::ofstream fileStreamLog("logTest.txt", std::ofstream::app);
  Logger lf (fileStreamLog);
  lf << "there is example of file log" << " we can use it as same as cout "
    << 99 << std::endl<<"blah blah, so we can see that overloaded endl is what we need\n";


}
