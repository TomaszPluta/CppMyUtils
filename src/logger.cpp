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
protected:
      std::ostream &out_;
public:
      std::string id = "this_is_is";
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

    Logger& withTimestamp(){
    	auto timeRaw = std::chrono::system_clock::now();
    	time_t timeT = std::chrono::system_clock::to_time_t(timeRaw);
    	std::string timeHuman{std::ctime(&timeT)};
    	timeHuman.pop_back();
    	*this<<"["<<timeHuman<<"]";
    	return *this;
    }

    Logger& info(){
    	*this<<"[INFO]";
    	return *this;
    }

    Logger& warn(){
    	*this<<"[WARN]";
    	return *this;
    }

    Logger& error(){
    	*this<<"[ERROR]";
    	return *this;
    }
};



template < typename T >
Logger & operator<< (Logger & logger, T in){
  logger.out_ << in;
  return logger;
}


class NullBuff: public std::streambuf{
public:
	int overflow(int c){return c;};
};


class NullStream : public std::ostream {
    class NullBuffer : public std::streambuf {
    public:
        int overflow( int c ) { return c; }
    } m_nb;
public:
    NullStream() : std::ostream( &m_nb ) {}
};


std::streambuf * sb;

class NullLogger : public Logger
{
	NullStream nullStream;
public:
	NullLogger(): Logger::Logger(NullLogger::nullStream){};
};


class CompositLogger
{
  std::vector < std::shared_ptr < Logger >> loggers;
std::vector<std::shared_ptr<CompositLogger>>compositeLoggers;
public:

  void addLogger (std::shared_ptr < Logger > logger)
  {
    loggers.push_back (logger);
  }

  void addLogger (std::shared_ptr < CompositLogger > compositLogger)
  {
	  compositeLoggers.push_back (compositLogger);
  }

  CompositLogger& withTimestamp(){
	  for (auto i : loggers){
	  		i->withTimestamp();
	  	}
	  for (auto i : compositeLoggers){
			i->withTimestamp();
		}
	  	return *this;
  }

  CompositLogger& info(){
	  for (auto i : loggers){
		  i->info();
	  }
	  for (auto i : compositeLoggers){
		  i->info();
	  }
	  return *this;
  }

  CompositLogger& warn(){
	  for (auto i : loggers){
		  i->warn();
	  }
	  for (auto i : compositeLoggers){
		  i->warn();
	  }
	  return *this;
  }

  CompositLogger& error(){
	  for (auto i : loggers){
		  i->error();
	  }
	  for (auto i : compositeLoggers){
		  i->error();
	  }
	  return *this;
  }

 template <typename T>
 friend CompositLogger& operator<<(CompositLogger &cLogger, T in);



 CompositLogger& operator <<(std::ostream& (*os)(std::ostream&))
  {
	  for (auto i : loggers){
		  		i->operator <<(os);
		  	}
	  for (auto i : compositeLoggers){
			i->operator <<(os);
			  	}
      return *this;
  }


};


template <typename T>
CompositLogger & operator<<(CompositLogger &cLogger, T in){
	for (auto i : cLogger.loggers){
		*i<<in;
	}
	for (auto i : cLogger.compositeLoggers){
		*i<<in;
	}
	return cLogger;
}



class LoggerFactory
{
	std::string logFilename_;
	std::unique_ptr<std::ofstream> loggerFilePtr_;
	std::shared_ptr<std::ostringstream> ossPtr_;

public:
  enum loggerType
  {
    FILE,
    COUT,
	OSS,
    COMPOSIT,
	LNULL,
  };


  LoggerFactory(std::string logFilename = "log.txt", std::shared_ptr<std::ostringstream> variableToLog = std::make_unique<std::ostringstream>()){
	  logFilename_ = logFilename;
 	  loggerFilePtr_ = std::make_unique<std::ofstream>();
 	  ossPtr_ = variableToLog;
   }


  ~LoggerFactory(){
	  if (loggerFilePtr_->is_open()){
		  loggerFilePtr_->close();
	  }
  }



  std::shared_ptr < CompositLogger > Create (std::initializer_list<loggerType> loggers)
  {
    std::shared_ptr < CompositLogger > loggerPtr = std::make_shared < CompositLogger > ();
    for (auto & i:loggers) {
	switch (i) {
	  case loggerType::FILE:
	    {
	      loggerFilePtr_->open(logFilename_, std::ostream::app);
	      loggerPtr->addLogger(std::make_shared < Logger > (*loggerFilePtr_));
	      break;
	    }
	  case loggerType::COUT:
	    {
	      loggerPtr->addLogger(std::make_shared < Logger > (std::cout));
	      break;
	    }
	  case loggerType::OSS:
		{
		  loggerPtr->addLogger(std::make_shared < Logger > (*ossPtr_));
		  break;
		}
	  default:
	    {
	    	loggerPtr->addLogger(std::make_shared<NullLogger> ());
	    	break;
	    }
	  }
      }
    return loggerPtr;
  }
};




int
main ()
{
	LoggerFactory lf;
	std::shared_ptr<CompositLogger> logger = lf.Create({LoggerFactory::loggerType::COUT, LoggerFactory::loggerType::FILE});
	std::stringstream ss;
	logger->addLogger(std::make_shared<Logger>(ss));


	logger->withTimestamp()<<"timestamped log"<<"with endline"<<std::endl;
	auto richLogger = logger->withTimestamp();
	richLogger<<"happy logging!"<<std::endl;
	logger->withTimestamp().info()<<"example info log"<<std::endl;
	auto evenRicherErrorLogger = logger->withTimestamp().error();
	evenRicherErrorLogger<<"All fur coat, and no knickers"<<std::endl;
}
