#include "UserService.hpp"


bool UserService::createUser(const oatpp::Object<UserDto>& dto) {

    auto dbResult = m_database->createUser(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto userId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    OATPP_LOGD("AAA", "new userId=%d", userId);

    return true;
}

oatpp::Object<UserDto> UserService::getUserByToken(const oatpp::String& tokenString, const std::shared_ptr<oatpp::orm::Connection>& connection) {

    auto dbResult = m_database->getUserByToken(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}