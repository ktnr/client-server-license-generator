#include "Request.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) 
{
    RequestHandler requestHandler;

    // get auth token as command line argument
    std::string authenticationToken = "4e99e8c12de7e01535248d2bac85e732";

    std::string licenseFileContent = requestHandler.SendLicenseRequest(authenticationToken);

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