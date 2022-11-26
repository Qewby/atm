#include <httplib.h>
#include "nlohmann/json.hpp"

#include "NumberDecoder.h"

using json = nlohmann::json;
using namespace httplib;

int main()
{
	Server svr;
	if (!svr.is_valid())
		return -1;

	svr.Post("/validate", [&](const Request& req, Response& res)
	{
		json req_json = json::parse(req.body);
		string number = req_json["number"];
		const static NumberDecoder decoder;
		json result = decoder.decode(number);
		//result["valid"] = decoder.validate(req_json["number"]);
		res.set_content(result.dump(), "application/json");
	});

	svr.listen("localhost", 8080);
	return 0;
}
