#include "Request.hpp"

#include <CLI11.hpp>

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) 
{
    CLI::App app;

    std::string token = "default";
    app.add_option("-t,--token", token, "The token for license retrieval.")->required();
    ////app.add_option("-o,--outdir", outdir, "The output directory")->required();

    CLI11_PARSE(app, argc, argv);

    if (token == "")
    {
        throw CLI::ConversionError("-t token is empty");
    }

    RequestHandler requestHandler;

    // get auth token as command line argument

    std::string licenseFileContent = requestHandler.SendLicenseRequest(token); // 4e99e8c12de7e01535248d2bac85e732

    if (licenseFileContent != "")
    {
        std::ofstream out("project-name.lic");
        out << licenseFileContent;
        out.close();
    }
    else
    {
        std::cout << "License request failed\n";
    }

    return 0;
}