#include "Request.hpp"

#include "../../extern/open-license-manager/include/licensecc/licensecc.h"

#include "../client/LicenseRequestClient.hpp"

std::string RequestHandler::SendLicenseRequest(std::string authenticationCode)
{
    std::optional<std::string> machineIdentifier = RetrieveMachineIdentifier();

    if (!machineIdentifier.has_value())
    {
        // Return;
    }

    LicenseRequestClientInterface client;
    auto licenseFileContent = client.RequestLicense(authenticationCode, machineIdentifier.value());

    // fill string
    return std::string();
}

std::optional<std::string> RequestHandler::RetrieveMachineIdentifier()
{
    size_t pc_id_sz = LCC_API_PC_IDENTIFIER_SIZE + 1;
    char pc_identifier[LCC_API_PC_IDENTIFIER_SIZE + 1];

    bool success = identify_pc(LCC_API_HW_IDENTIFICATION_STRATEGY::STRATEGY_DEFAULT, pc_identifier, &pc_id_sz, nullptr);

    if (!success)
    {
        // Log
        // throw exception?
    }

    return std::string(pc_identifier);
}
