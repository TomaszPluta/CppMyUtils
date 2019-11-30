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
public:
	virtual Logger& operator<<( std::ostream& (*pf)(std::ostream&)) =0;
	virtual Logger & operator<< (std::string msg) =0;
	virtual Logger & withTimestamp() =0;
	virtual Logger& withInfo() =0;
	virtual Logger& warn() =0;
	virtual Logger& withError() = 0;
	virtual ~Logger(){};
};


class StreamLogger : public Logger{
	std::ostream &out_;
public:
	StreamLogger (std::ostream &out): out_{out}{};

	StreamLogger & operator<< (std::string msg) override{
		out_<<msg;
		return *this;
	}

	StreamLogger& operator<<( std::ostream& (*pf)(std::ostream&))override{
		*this<<"\n";
		out_.flush();
		return *this;
	}

	StreamLogger & endl (StreamLogger & logger);

	StreamLogger & withTimestamp() override{
		auto timeRaw = std::chrono::system_clock::now();
		time_t timeTmp = std::chrono::system_clock::to_time_t(timeRaw);
		std::string timeStr(ctime(&timeTmp));
		timeStr.pop_back();
		*this<<"["<<timeStr<<"]";
		return *this;
	}

	StreamLogger& withInfo() override{
		*this<<"[INFO]";
		return *this;
	}

	StreamLogger& warn() override{
		*this<<"[WARN]";
		return *this;
	}

	StreamLogger& withError() override{
		*this<<"[ERROR]";
		return *this;
	}
};




class CompositLogger : public Logger{
	std::vector<std::shared_ptr<Logger>> loggers;

public:
	void addLogger(std::shared_ptr<Logger> logger){
		loggers.push_back(logger);
	}

	CompositLogger & operator<< (std::string msg) override{
		 for (auto i : loggers){
				  		*i<<msg;
				  	}
		return *this;
	}

	CompositLogger & endl (CompositLogger & logger);


	 CompositLogger& operator <<(std::ostream& (*os)(std::ostream&))
	  {
		  for (auto i : loggers){
			  		i->operator <<(os);
			  	}
	      return *this;
	  }


	CompositLogger& withTimestamp() override{
		  for (auto i : loggers){
		  		i->withTimestamp();
		  	}
		  	return *this;
	  }

	  CompositLogger& withInfo() override{
		  for (auto i : loggers){
			  i->withInfo();
		  }
		  return *this;
	  }

	  CompositLogger& warn()  override{
		  for (auto i : loggers){
			  i->warn();
		  }
		  return *this;
	  }

	  CompositLogger& withError() override{
		  for (auto i : loggers){
			  i->withError();
		  }
		  return *this;
	  }

};




class NullLogger : public Logger{
public:
	NullLogger & operator<< (std::string msg) override{
			return *this;
		}

	NullLogger & endl (CompositLogger & logger);


	NullLogger& operator <<(std::ostream& (*os)(std::ostream&)){
	 	return *this;
	}

	NullLogger& withTimestamp() override{
		  	return *this;
	  }

	NullLogger& withInfo() override{
		  return *this;
	  }

	NullLogger& warn() override{
		  return *this;
	  }

	NullLogger& withError() override{
		  return *this;
	  }
};




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
	OSTRSTREAM,
    COMPOSIT,
  };


  LoggerFactory(std::string logFilename = "log.txt", std::shared_ptr<std::ostringstream> varToLog = std::make_unique<std::ostringstream>()){
	  logFilename_ = logFilename;
 	  loggerFilePtr_ = std::make_unique<std::ofstream>();
 	  ossPtr_ = varToLog;
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
			  loggerPtr->addLogger(std::make_unique < StreamLogger > (*loggerFilePtr_));
			  break;
		  }
		  case loggerType::COUT:
		  {
			  loggerPtr->addLogger(std::make_unique < StreamLogger > (std::cout));
			  break;
		  }
		  case loggerType::OSTRSTREAM:
		  {
			  loggerPtr->addLogger(std::make_unique < StreamLogger > (*ossPtr_));
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
		std::shared_ptr<CompositLogger> compositeMultiLevelLogger = std::make_unique<CompositLogger>();
		compositeMultiLevelLogger->addLogger(logger);
		std::stringstream ss;
		compositeMultiLevelLogger->addLogger(std::make_shared<StreamLogger>(ss));

		compositeMultiLevelLogger->withTimestamp()<<"timestamped log"<<" with endline"<<std::endl;
		auto richLogger = logger->withTimestamp();
		richLogger<<"happy logging!"<<std::endl;
		logger->withTimestamp().withInfo()<<"example info log"<<std::endl;
		auto erorLog = logger->withTimestamp().withError();
		erorLog<<"All fur coat, and no knickers"<<std::endl;

}
