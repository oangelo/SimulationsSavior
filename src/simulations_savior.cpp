#include "simulations_savior.h"

SimulationsSavior::SimulationsSavior(std::string dbname, std::string user, std::string password, std::string host):conn(), id()
{
    try{
        std::string connection_parameters;
        if(dbname != "") connection_parameters += "dbname=" + dbname;
        if(user != "") connection_parameters += " user=" + user;
        if(password != "") connection_parameters += " password=" + password;
        if(host != "") connection_parameters += " host=" + host;
        conn = new pqxx::lazyconnection(connection_parameters);
    }catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

int SimulationsSavior::GetID()
{
    std::string get("select currval('parameters_id_seq');");
    pqxx::nontransaction N(*conn);
    pqxx::result R(N.exec(get));
    id = R.begin()[0].as<int>();
    return id;
}

//Add a new simulation to the parameters table
void SimulationsSavior::New(std::map<std::string, std::string> parameters, std::string table){

    //Insert
    std::string values;
    std::string columns;
    std::map<std::string, std::string>::iterator it;
    for(it = parameters.begin(); it != --parameters.end(); ++it){
        columns += it->first + ",";
        values +="'"+it->second+"',";
    }
    columns +=""+it->first+"";
    values +="'"+it->second+"'";

    pqxx::work cursor(*conn);
    std::string insert("insert into " + table + " (" + columns + ") values (" + values + ");");

    cursor.exec(insert);
    cursor.commit();
    //Get id

    id = GetID(); 

    conn->deactivate(); //simulations can take time, and it is not good to wait connected to the db
}

void SimulationsSavior::Insert(std::vector<double> values, std::string table){
    conn->activate();

    pqxx::work cursor(*conn);
    std::string insert("insert into "+table+" values (");
    insert += " " + std::to_string(id) + ",";
    for(size_t i(0); i < values.size() - 1; ++i)
        insert += " " + std::to_string(values[i]) + ",";
    insert += " " + std::to_string(values.back());
    insert += ");";
    cursor.exec(insert);
    cursor.commit();

    conn->deactivate(); //simulations can take time, and it is not good to wait connected to the db
}

SimulationsSavior::~SimulationsSavior(){
    if(conn){
        conn->disconnect();
        delete conn;
    }
}
