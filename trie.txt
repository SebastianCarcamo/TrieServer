#include "crow.h"
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

int main(){

    crow::SimpleApp app;
    crow::mustache::set_base(".");

    CROW_ROUTE(app,"/trie").methods("POST"_method)
	    ([](const crow::request& req)
	     {
		std::cout<<"ENTRO A SEARCH ..."<<std::endl;
		auto q = crow::json::load(req.body);
		std::string query = q["query"].s();
		std::cout<<query<<std::endl;

		std::cout<<"SALE A SEARCH ..."<<std::endl;
		crow::json::wvalue ans;
		ans["0"] = "203.34";
		return ans;
		//return crow::response{{"ans":"hola"}};
	     });

		    

    app.port(41080)
        //.multithreaded()
        .run();
}
