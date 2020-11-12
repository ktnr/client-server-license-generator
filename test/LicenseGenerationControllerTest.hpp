#ifndef MyControllerTest_hpp
#define MyControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class LicenseGenerationControllerTest : public oatpp::test::UnitTest {
public:

    LicenseGenerationControllerTest() : UnitTest("TEST[LicenseGenerationControllerTest]"){}
  void onRun() override;

};

#endif // MyControllerTest_hpp
