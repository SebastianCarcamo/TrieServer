#include "crow.h"
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

#include "./TrieSingleton/singleton.h"

using namespace std;

int main(){

    crow::SimpleApp app;
    crow::mustache::set_base(".");

    loadFileSingleton("./TrieSingleton/english.txt");


    CROW_ROUTE(app,"/suggest").methods("POST"_method)
	    ([](const crow::request& req)
	     {
		auto q = crow::json::load(req.body);
		std::string query = q["query"].s();
		std::cout<<query<<std::endl;

		crow::json::wvalue ans;

		std::vector<std::string> suggestions = nFirstSuggestionsSingleton(query, 5);

		crow::json::wvalue data;

		for(auto x: suggestions) {
			data[x] = "";
		}

		ans["data"] = std::move(data);
		return ans;
		//return crow::response{{"ans":"hola"}};
	     });

    CROW_ROUTE(app,"/correct").methods("POST"_method)
	    ([](const crow::request& req)
	     {
		auto q = crow::json::load(req.body);
		std::string query = q["query"].s();
		std::cout<<query<<std::endl;

		crow::json::wvalue ans;

		std::vector<std::string> suggestions = correctSingleton(query);
		if(suggestions.size()>10){
			suggestions.resize(10);
		}

		crow::json::wvalue data;

		for(auto x: suggestions) {
			data[x] = "";
		}

		ans["data"] = std::move(data);
		return ans;
		//return crow::response{{"ans":"hola"}};
	     });

    CROW_ROUTE(app,"/complete").methods("POST"_method)
	    ([](const crow::request& req)
	     {
		auto q = crow::json::load(req.body);
		std::string query = q["query"].s();
		std::cout<<query<<std::endl;

		crow::json::wvalue ans;

		std::vector<std::string> suggestions = SuggestThenCorrectSingleton(query);

		crow::json::wvalue data;

		for(auto x: suggestions) {
			data[x] = "";
		}

		ans["data"] = std::move(data);
		return ans;
		//return crow::response{{"ans":"hola"}};
	     });

    app.port(41080)

        //.multithreaded()
        .run();
}
