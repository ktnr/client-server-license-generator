#pragma once

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UserService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:

    bool createUser(const oatpp::Object<UserDto>& dto);
    oatpp::Object<UserDto> getUserByToken(const oatpp::String& tokenString, const std::shared_ptr<oatpp::orm::Connection>& connection = nullptr);

};
