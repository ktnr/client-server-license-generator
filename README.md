# Preqreuqisites
## Oat++
- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## open-license-manager

- [Open License Manager Documentation](http://open-license-manager.github.io/open-license-manager/)
- [Open License Manager Github Repository](https://github.com/open-license-manager/open-license-manager)




# Overview

This project is based on the [starter project of oat++ (AKA oatpp)](https://github.com/oatpp/oatpp-starter) application.

## Project layout

```
|- CMakeLists.txt							// projects CMakeLists.txt
|- src/
|    |
|    |- client/								// wants to request a license
|    |- dto/								// data transfer object containing hardware identifiers and license file content
|    |- license/							// client-side main(). Issues a license request to the server. Transfers the hardware identifier.
|    |- server/								// issues a license given the client's hardware identifier
|    |- AppComponent.hpp					// service config
|    |- App.cpp								// server-side main(). Starts the server and listens for requests.
|
|- test/                                 
|	 |- app/								// local simulation of client-server network. Similar to AppComponent.hpp.
|	 |- LicenseGenerationControllerTest.cpp // client-server communication test wirh locally simulated network.
|- utility/install-oatpp-modules.sh			// utility script to install required oatpp-modules.  
```


## Build and Run

Currently only works in Debug

- Follow instructions on [Oat++ Github Repository](https://github.com/oatpp/oatpp).
- Consult the Open License Manager [Repository](https://github.com/open-license-manager/open-license-manager) and [Documentation](http://open-license-manager.github.io/open-license-manager/) the [submodule example of Open License Manager](https://github.com/open-license-manager/examples/tree/develop/submodule).
- Adjust any hardcoded paths (sorry)
- Run `tests.cpp` to simulate client-server communication locally to generate a licnese

## TODO
- Add [authentication/authorization](https://oatpp.io/docs/components/api-controller/#authorization-bearer)