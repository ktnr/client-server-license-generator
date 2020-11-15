#include "Request.hpp"

#include <fstream>

int main(int argc, char* argv[]) 
{
    RequestHandler requestHandler;

    std::string authenticationToken = "a";

    std::string licenseFileContent = requestHandler.SendLicenseRequest(authenticationToken);

    if (licenseFileContent != "")
    {
        std::ofstream out("project-name.lic");
        out << licenseFileContent;
        out.close();
    }

    return 0;
}