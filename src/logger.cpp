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





//delete this
class ILogger
{
protected:
	ILogger(){};
public:
	virtual ~ILogger() =0;



};


ILogger::~ILogger(){
	;
}

class Logger : public ILogger
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
};

template < typename T >
Logger & operator<< (Logger & logger, T in){
  logger.out_ << in;
  return logger;
}





//
//
//class CompositLogger : public ILogger
//{
//  std::vector < std::shared_ptr < Logger >> loggers;
//
//public:
//
//  void addLogger (std::shared_ptr < Logger > logger)
//  {
//    loggers.push_back (logger);
//  }
//
//  CompositLogger& withTimestamp(){
//	  for (auto i : loggers){
//	  		i->withTimestamp();
//	  	}
//	  	return *this;
//  }
//
// template <typename T>
// friend CompositLogger& operator<<(CompositLogger &cLogger, T in);
//
//
//
// CompositLogger& operator <<(std::ostream& (*os)(std::ostream&))
//  {
//	  for (auto i : loggers){
//		  		i->operator <<(os);
//		  	}
//      return *this;
//  }
//
//};
//
//
//template <typename T>
//CompositLogger & operator<<(CompositLogger &cLogger, T in){
//	for (auto i : cLogger.loggers){
//		*i<<in;
//	}
//	return cLogger;
//}






class CompositLogger : public ILogger
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
	  //check is not in list to avoid loops?
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
	 std::ofstream loggerFile;
public:
  enum class loggerType:int
  {
    FILE,
    SOUT,
    COMPOSIT,
  };


  ~LoggerFactory(){
	  if (loggerFile.is_open()){
		  loggerFile.close();
	  }
  }


  std::shared_ptr < CompositLogger > Create (std::initializer_list<loggerType> loggers)
  {
    std::shared_ptr < CompositLogger > loggerPtr = std::make_shared < CompositLogger > ();
    for (auto & i:loggers) {
	switch (i) {
	  case loggerType::FILE:
	    {
	    	loggerFile.open("log.txt", std::fstream::app);
	      loggerPtr->addLogger(std::make_shared < Logger > (loggerFile));
	      break;
	    }
	  case loggerType::SOUT:
	    {
	      loggerPtr->addLogger(std::make_shared < Logger > (std::cout));
	      break;
	    }
	  default:
	    {
	    	 //TODO:make null object logger;
	    }
	  }
      }
    return loggerPtr;
  }


};





int
main ()
{



	std::shared_ptr<CompositLogger> clp = std::make_shared<CompositLogger>();

  std::ofstream fileComp("composite.log");
  clp->addLogger(std::make_shared<Logger>(fileComp));

  std::ofstream anotherFileComp("another.log");
  clp->addLogger(std::make_shared<Logger>(anotherFileComp));

  clp->addLogger(std::make_shared<Logger>(std::cout));
  *clp<<"composite log here";
  clp->withTimestamp()<<"timestamped log"<<"with endline"<<std::endl;
  clp->withTimestamp()<<"happy logging"<<std::endl;


}
