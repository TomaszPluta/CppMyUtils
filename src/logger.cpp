#include "algorithm"
#include "iostream"
#include "string"
#include "string_view"
#include "fstream"
#include "string_view"
#include  "sstream"
#include "memory"


class Logger{
public :
	virtual void writeInfo(std::string_view info) =0;
	virtual void writeWarn(std::string_view warn) =0;
	virtual void writeError(std::string_view error) =0;
};


class FilesystemLogger : public Logger{
	void writeInfo(std::string_view info){
		std::cout<<info<<'\n';
	}
	void writeWarn(std::string_view warn){
		std::cout<<warn<<'\n';
	}
	void writeError(std::string_view error){
		std::cout<<error<<'\n';
	}
};


class StdOutLogger : public Logger{
	void writeInfo(std::string_view info){
			std::cout<<info<<'\n';
		}
		void writeWarn(std::string_view warn){
			std::cout<<warn<<'\n';
		}
		void writeError(std::string_view error){
			std::cout<<error<<'\n';
		}
};


class LoggerFactory{
	std::string configFileName;
	 enum class logginOutput : int{
		 FILE,
		 SOUT
	 };

public:
	 LoggerFactory(std::string_view cfgFileName) : configFileName{cfgFileName}{};




	 std::string readCfg()const{
		 std::fstream cfgFileStream(configFileName);
		 std::stringstream ss;
		 ss << cfgFileStream.rdbuf();
		 return std::string(ss.str());
	 }

	 std::string readCfgShort()const{
			 std::fstream cfgFileStream(configFileName);
			 return std::string  (std::istreambuf_iterator<char>(cfgFileStream), std::istreambuf_iterator<char>());
		 }

	 logginOutput evalueateCnfiguration(std::string_view configuration) const{

		 if (configuration.find("SOUT") !=  std::string::npos){
			 return logginOutput::SOUT;
		 }

		 if (configuration.find("FILE") !=  std::string::npos){
			 return logginOutput::FILE;
		 }

		 return logginOutput::SOUT;
	 }


	 std::shared_ptr<Logger> create () const {
		 std::string cfgContent = readCfgShort();
		 logginOutput outputTarget = evalueateCnfiguration(cfgContent);
		 return createLogger(outputTarget);
	 }


	 std::shared_ptr<Logger> createLogger(logginOutput outputTarget) const {
		 switch (outputTarget){
		 case logginOutput::FILE:{
			 return std::make_shared<FilesystemLogger>();
			 break;
		 }
		 case logginOutput::SOUT:
		 default: {
			 return  std::make_shared<StdOutLogger>();
			 break;
		 }
		 }
	 }

};



int main(){
	LoggerFactory loggerFactory("logger.cfg");
	std::shared_ptr<Logger>  logger = loggerFactory.create();
	logger->writeWarn("here is example warn");
}
