#ifndef SIMULATIONS_SAVIOR_H 
#define SIMULATIONS_SAVIOR_H 

#include <iostream>
#include <string>
#include <map>

#include <pqxx/pqxx>

class SimulationsSavior{
    public:
        SimulationsSavior(std::string dbname, std::string user = "", std::string password = "", std::string host = "");
        void New(std::map<std::string, std::string> parameters, std::string table);
        void Insert(std::vector<double> values, std::string table);
        ~SimulationsSavior();
    private:
        pqxx::lazyconnection* conn;
        int id;
        //Preventing Copy
        SimulationsSavior(const SimulationsSavior&);
        SimulationsSavior& operator=(const SimulationsSavior&);

        int GetID();
};

#endif /* SIMULATIONS_SAVIOR_H */
