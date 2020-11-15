#pragma once

#include <string>
#include <optional>

class RequestHandler
{
public:
    std::string SendLicenseRequest(std::string authenticationCode);
    std::optional<std::string> RetrieveMachineIdentifier();
};
