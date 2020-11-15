#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <string>
#include <fstream>
#include <sstream>

#include <filesystem>
#include <iostream>

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class LicenseGenerationController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  LicenseGenerationController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT("PUT", "/generateLicense", generateLicense,
      BODY_DTO(Object<LicenseRequestDto>, requestDto))
  {
      std::string hardwareId = std::string(requestDto->hardwareIdentifier->c_str());
      std::string authenticationToken = "X";
      std::string licenseFileName = "tmp-" + authenticationToken + ".lic";

      std::string lccCall = "C:/Users/Leo/Source/Repos/ktnr/client-server-license-generator/out/build/x64-Debug/extern/open-license-manager/extern/license-generator/src/license_generator/lccgen license issue --primary-key C:/Users/Leo/Source/Repos/ktnr/client-server-license-generator/projects/DEFAULT/private_key.rsa --client-signature " + hardwareId + " -o " + licenseFileName.c_str();

      system(lccCall.c_str());

      std::string licenseFileContent;

      {
          std::ifstream t(licenseFileName.c_str());
          std::stringstream buffer;
          buffer << t.rdbuf();

          licenseFileContent = buffer.str();
      }

      try {
          if (std::filesystem::remove(licenseFileName))
              std::cout << "file " << licenseFileName << " deleted.\n";
          else
              std::cout << "file " << licenseFileName << " not found.\n";
      }
      catch (const std::filesystem::filesystem_error& err) {
          std::cout << "filesystem error: " << err.what() << '\n';
      }

      Object<LicenseResponseDto> packingResponseDto = LicenseResponseDto::createShared();
      packingResponseDto->licenseFileContent = oatpp::String(licenseFileContent.c_str());

      return createDtoResponse(Status::CODE_200, packingResponseDto);
  }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
