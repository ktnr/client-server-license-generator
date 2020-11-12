#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

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
      std::string licenseFileContent = "z"; // call "lccgen license issue --client-signature <hardwareId> -o licenses/{license-file-name}.lic". Must we invoke the .exe here or can we get it via an interface?

      Object<LicenseResponseDto> packingResponseDto = LicenseResponseDto::createShared();
      packingResponseDto->licenseFileContent = oatpp::String(licenseFileContent.c_str());

      return createDtoResponse(Status::CODE_200, packingResponseDto);
  }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
