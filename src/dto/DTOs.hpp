#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class LicenseRequestDto : public oatpp::DTO {
  
  DTO_INIT(LicenseRequestDto, DTO)
  
  DTO_FIELD(String, hardwareIdentifier);
  
};


class LicenseResponseDto : public oatpp::DTO {

    DTO_INIT(LicenseResponseDto, DTO)

    DTO_FIELD(String, licenseFileContent);

};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */
