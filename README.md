# Prerequisites
## Oat++
- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)

## open-license-manager

- [Open License Manager Documentation](http://open-license-manager.github.io/open-license-manager/)
- [Open License Manager Github Repository](https://github.com/open-license-manager/open-license-manager)




# Overview

A client wants to retrieve a license from the server. 

1. The client issues a license request by transmitting hardware identifiers from its machine to the server via a put-request. 
1. On the server-side the license is generated: `system("lccgen license issue --client-signature " + clientMachineId)`
1. The license is transmitted back to the client in the response of the put-request.

## Project layout

This project is based on the [starter project of oat++ (AKA oatpp)](https://github.com/oatpp/oatpp-starter).

```
|- CMakeLists.txt							// projects CMakeLists.txt
|- src/
|    |
|    |- client/            // wants to request a license
|    |- dto/               // data transfer object containing hardware identifiers and license file content
|    |- license/           // client-side main(). Issues a license request to the server. Transfers the hardware identifier.
|    |- server/            // issues a license given the client's hardware identifier
|    |- AppComponent.hpp   // service config
|    |- App.cpp            // server-side main(). Starts the server and listens for requests.
|
|- test/                                 
|	 |- app/                 // local simulation of client-server network. Similar to AppComponent.hpp.
|	 |- LicenseGenerationControllerTest.cpp // client-server communication test wirh locally simulated network.
|- utility/install-oatpp-modules.sh       // utility script to install required oatpp-modules.  
```


## Build and Run

Currently only works in Debug

- Follow instructions on [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- Consult the Open License Manager [Repository](https://github.com/open-license-manager/open-license-manager) and [Documentation](http://open-license-manager.github.io/open-license-manager/), as well as the [submodule example](https://github.com/open-license-manager/examples/tree/develop/submodule)
- Adjust any hardcoded paths (sorry)
- Run `tests.cpp` to simulate client-server communication locally to generate a licnese

## TODO

The server must know if a license request is valid (the client requesting a license is eligible to receive one) and which kind of license to issue (expiration by date, bound to certain machine...). 

For example, a customer requests a license from the issuers website. The client receives an authentication token. This token must be transmitted during the client's license request to the server so that the server can match the token to its database in order to, if eligible, generate the corresponding license.
- Add [authentication/authorization](https://oatpp.io/docs/components/api-controller/#authorization-bearer)
