#include "LicenseGenerationControllerTest.hpp"

#include "server/LicenseGenerationController.hpp"

#include "app/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp-test/web/ClientServerTestRunner.hpp"

#include "client/LicenseRequestClient.hpp"

#include "license\Request.hpp"

void LicenseGenerationControllerTest::onRun() {

  /* Register test components */
  TestComponent component;

  /* Create client-server test runner */
  oatpp::test::web::ClientServerTestRunner runner;

  /* Add LicenseGenerationController endpoints to the router of the test server */
  runner.addController(std::make_shared<LicenseGenerationController>());

  /* Run test */
  runner.run([this, &runner] {

    /* Get client connection provider for Api Client */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

    /* Get object mapper component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

    /* Create http request executor for Api Client */
    auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

    /* Create Test API client */
    auto client = LicenseRequestClient::createShared(requestExecutor, objectMapper);

    auto requestDto = LicenseRequestDto::createShared();

    RequestHandler requestHandler;
    std::optional<std::string> machineIdentifier = requestHandler.RetrieveMachineIdentifier();

    requestDto->hardwareIdentifier = machineIdentifier.value().c_str(); // call olm::identify_pc()

    std::string authenticationToken = "X";

    /* Call server API */
    /* Call root endpoint of LicenseGenerationController */
    auto response = client->putLicenseRequest(requestDto);

    /* Assert that server responds with 200 */
    OATPP_ASSERT(response->getStatusCode() == 200);

    /* Read response body as MessageDto */
    auto message = response->readBodyToDto<oatpp::Object<LicenseResponseDto>>(objectMapper.get());

    /* Assert that received message is as expected */
    OATPP_ASSERT(message);
    OATPP_LOGD("License file content", message->licenseFileContent->c_str());

    std::string licenseFileContent = message->licenseFileContent->c_str();

    OATPP_ASSERT(licenseFileContent.find(machineIdentifier.value()) != std::string::npos); // Hardware identifiert matches the request.

    std::ofstream out("client-" + authenticationToken + ".lic");
    out << licenseFileContent;
    out.close();

  }, std::chrono::minutes(10) /* test timeout */);

  /* wait all server threads finished */
  std::this_thread::sleep_for(std::chrono::seconds(1));

}
