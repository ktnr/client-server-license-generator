#include "LicenseRequestClient.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"



std::shared_ptr<oatpp::web::client::RequestExecutor> createOatppExecutor() {
    OATPP_LOGD("App", "Using Oat++ native HttpRequestExecutor.");
    auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({ "localhost", 8000 });
    return oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
}

std::string LicenseRequestClientInterface::RequestLicense(std::string authenticationToken, std::string hardwareIdentifier)
{
    oatpp::base::Environment::init();

    /* Create ObjectMapper for serialization of DTOs  */
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    /* Create RequestExecutor which will execute ApiClient's requests */
    auto requestExecutor = createOatppExecutor();   // <-- Always use oatpp native executor where's possible.
    //auto requestExecutor = createCurlExecutor();  // <-- Curl request executor

    /* DemoApiClient uses DemoRequestExecutor and json::mapping::ObjectMapper */
    /* ObjectMapper passed here is used for serialization of outgoing DTOs */
    auto client = LicenseRequestClient::createShared(requestExecutor, objectMapper);

    auto requestDto = LicenseRequestDto::createShared();
    requestDto->hardwareIdentifier = oatpp::String(hardwareIdentifier.c_str());

    auto responsteDto = client->putLicenseRequest(requestDto);

    auto responseDto = responsteDto->readBodyToDto<oatpp::Object<LicenseResponseDto>>(objectMapper.get());

    std::string licenseAsString = responseDto->licenseFileContent->c_str();

    oatpp::base::Environment::destroy();

    return licenseAsString;
}