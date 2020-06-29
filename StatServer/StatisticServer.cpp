#include "StatisticServer.h"
#include "StatisticServantImp.h"

using namespace std;


namespace {

//notice we should use full path of each configure
const std::string STATISTIC_CONF =  "statistic.yaml";

}


/////////////////////////////////////////////////////////////////
void
StatisticServer::initialize() {
	addConfig(STATISTIC_CONF.c_str());

	string servantPath = ServerConfig::Application + "." + ServerConfig::ServerName + ".StatisticServantHttpObj";
	addServant<StatisticServantImp>(servantPath);
	addServantProtocol(servantPath, &TC_NetWorkBuffer::parseHttp);
	

   
}

/////////////////////////////////////////////////////////////////
void StatisticServer::destroyApp() {
	//destroy application here:
	//...
}

/////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	try {
        StatisticServer server;

		server.main(argc, argv);

		server.waitForShutdown();
	} catch (std::exception& e) {
		cerr << "std::exception:" << e.what() << std::endl;
	} catch (...) {
		cerr << "unknown exception." << std::endl;
	}
	return -1;
}
/////////////////////////////////////////////////////////////////
