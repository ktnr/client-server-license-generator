#pragma once

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "../dto/DTOs.hpp"

typedef oatpp::web::protocol::http::incoming::Response Response;

class LicenseRequestClientInterface
{
public:
    std::string RequestLicense(std::string authenticationToken, std::string hardwareIdentifier);
};

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class LicenseRequestClient : public oatpp::web::client::ApiClient {

    API_CLIENT_INIT(LicenseRequestClient)

    API_CALL("PUT", "/generateLicense", putLicenseRequest, BODY_DTO(Object<LicenseRequestDto>, licenseRequestDto))
};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)