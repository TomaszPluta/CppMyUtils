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
//      std::ostream _out;

public:virtual void writeInfo (const std::string_view info) = 0;
  virtual void writeWarn (const std::string_view warn) = 0;
  virtual void writeError (const std::string_view error) = 0;

    template < typename T > friend Logger & operator<< (Logger & logger, T t);
};



class CompositLogger:public Logger
{
  std::vector < std::shared_ptr < Logger >> loggers;

public:void addLogger (std::shared_ptr < Logger > logger)
  {
    loggers.push_back (logger);
  }

  void writeInfo (const std::string_view info) override
  {
  for (auto & i:loggers)
      {
	i->writeInfo (info);
      }
  }

  void writeWarn (const std::string_view warn) override
  {
  for (auto & i:loggers)
      {
	i->writeWarn (warn);
      }
  }

  void writeError (const std::string_view error) override
  {
  for (auto & i:loggers)
      {
	i->writeError (error);
      }
  }

};




class FileLogger:public Logger
{
  std::ofstream loggerFile;

  void writeInfo (const std::string_view info)
  {
    loggerFile << "[info]" << info << '\n';
  }
  void writeWarn (const std::string_view warn)
  {
    loggerFile << "[info]" << warn << '\n';
  }
  void writeError (const std::string_view error)
  {
    loggerFile << "[error]" << error << '\n';
  }

public:
  FileLogger ()
  {
    loggerFile.open ("logFile1.log", std::ofstream::app);
  }

  ~FileLogger ()
  {
    loggerFile << "[endSession]\n";
  }

};






class FileInfoLogger:public Logger
{

  std::ofstream loggerFile;
public:



  FileInfoLogger ()
  {
    loggerFile.open ("default_log_file.log", std::ofstream::app);
  }

  FileInfoLogger (std::string filename)
  {
    loggerFile.open (filename.c_str (), std::ofstream::app);
  }


  ~FileInfoLogger ()
  {
    loggerFile << "\n[endSession]\n\n";
  }


  template < typename T >
    friend FileInfoLogger & operator<< (FileInfoLogger & fl, T in);


  FileInfoLogger & withTimestamp ()
  {
    auto rawTimeNow = std::chrono::system_clock::now ();
    time_t timeNow = std::chrono::system_clock::to_time_t (rawTimeNow);
    std::string timeStr = ctime (&timeNow);
    timeStr.pop_back ();
    loggerFile << "[" << timeStr << "]";

    return *this;
  }


  void writeInfo (std::string_view info)
  {
    (void) info;
  }
  void writeWarn (std::string_view warn)
  {
    (void) warn;
  }
  void writeError (std::string_view error)
  {
    (void) error;
  }

};



template < typename T >
  FileInfoLogger & operator<< (FileInfoLogger & fl, T in){
  fl.loggerFile << in;
  return fl;
}




class FileLoggerTimestamped :public FileInfoLogger
{
public:
  template < typename T >
    friend FileLoggerTimestamped & operator<< (FileLoggerTimestamped & flt,
					       T in);
};

  template < typename T >
FileLoggerTimestamped& operator<< (FileLoggerTimestamped & flt, T in)
{
  auto rawTimeNow = std::chrono::system_clock::now();
  std::time_t timeNowTmp = std::chrono::system_clock::to_time_t (rawTimeNow);
  std::string timeNow (timeNowTmp);
  timeNow.pop_back ();
  return flt;
}


class StdOutLogger:public Logger
{

public:
  void writeInfo (std::string_view info)
  {
    std::cout << info << '\n';
  }
  void writeWarn (std::string_view warn)
  {
    std::cout << warn << '\n';
  }
  void writeError (std::string_view error)
  {
    std::cout << error << '\n';
  }
};



class RemoteLogger:public Logger
{

public:
  void writeInfo (std::string_view info)
  {
    std::cout << info << '\n';
  }
  void writeWarn (std::string_view warn)
  {
    std::cout << warn << '\n';
  }
  void writeError (std::string_view error)
  {
    std::cout << error << '\n';
  }
};


class NullLogger:public Logger
{

public:
  void writeInfo (std::string_view info)
  {
    (void) info;
  }
  void writeWarn (std::string_view warn)
  {
    (void) warn;
  }
  void writeError (std::string_view error)
  {
    (void) error;
  }
};



class LoggerFactory
{
public:
  enum class loggerType:int
  {
    FILE,
    SOUT,
    REMOTE,
  };

    LoggerFactory (std::string_view cfgFileName):configFileName
  {
  cfgFileName}
  {
  };

  std::shared_ptr < Logger > createFromCfg ()const
  {
    std::string cfgContent = readCfgShort ();
    std::vector < loggerType > loggersToCreate =
      evalueateCnfiguration (cfgContent);
    return createLogger (loggersToCreate);
  }


  std::shared_ptr < Logger > createLogger (std::vector < loggerType >
					   typesToCreate) const
  {
    std::shared_ptr < CompositLogger > loggerPtr =
      std::make_shared < CompositLogger > ();
    for (auto & i:typesToCreate)
      {
	switch (i)
	  {
	  case loggerType::FILE:
	    {
	      loggerPtr->addLogger (std::make_shared < FileLogger > ());
	      break;
	    }
	    case loggerType::REMOTE:
	    {
	      loggerPtr->addLogger (std::make_shared < RemoteLogger > ());
	      break;
	    }
	  case loggerType::SOUT:
	    {
	      loggerPtr->addLogger (std::make_shared < StdOutLogger > ());
	      break;
	    }
	  default:
	    {
	      loggerPtr->addLogger (std::make_shared < NullLogger > ());
	    }
	  }
      }

    return std::static_pointer_cast < Logger > (loggerPtr);
  }

private:
  std::string configFileName;


  std::string readCfg ()const;

  std::string readCfgShort ()const;


  std::vector < loggerType >
    evalueateCnfiguration (std::string_view configuration) const;

};


std::string LoggerFactory::readCfg () const
{
  std::fstream cfgFileStream (configFileName);
  std::stringstream ss;
  ss << cfgFileStream.rdbuf ();
  return std::string (ss.str ());
}

std::string LoggerFactory::readCfgShort () const
{
  std::fstream cfgFileStream (configFileName);
  return std::string (std::istreambuf_iterator < char >(cfgFileStream),
		      std::istreambuf_iterator < char >());
}


std::vector < LoggerFactory::loggerType >
  LoggerFactory::
evalueateCnfiguration (std::string_view configuration) const
{
  std::vector < loggerType > usedLoggers;
  if (configuration.find ("SOUT") != std::string::npos)
    {
      usedLoggers.push_back (loggerType::SOUT);
    }

  if (configuration.find ("FILE") != std::string::npos)
    {
      usedLoggers.push_back (loggerType::FILE);
    }

  if (configuration.find ("REMOTE") != std::string::npos)
    {
      usedLoggers.push_back (loggerType::REMOTE);
    }

  return usedLoggers;
}


void
fun (std::shared_ptr < int >x)
{
  //*x = 50;
  x.reset ();
}





int
main ()
{
//      LoggerFactory loggerFactory("logger.cfg");
//      std::shared_ptr<Logger>  logger = loggerFactory.createLogger({{LoggerFactory::loggerType::FILE}});
//      logger->writeWarn("here is example warn");
//      logger->writeInfo("this is info");


//      std::shared_ptr<Logger> log = std::make_shared<FileLogger> ();
//      log->writeError("here are example errrrror");



  FileInfoLogger ll ("fileLOG.txt");
  ll << "we log everything" << " even the fact that we are logging now for "
    << 13 << "times\n";
  ll.withTimestamp () << "and here we go!" << " That is log with timestamp";




}
