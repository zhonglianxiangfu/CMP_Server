/* posService.h
   Generated by wsdl2h 1.2.7 from http://192.168.20.26:8800/A-Pay/services/posService?wsdl and typemap.dat
   2015-03-24 06:29:57 GMT
   Copyright (C) 2001-2005 Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL or Genivia's license for commercial use.
*/

/* NOTE:

 - Compile this file with soapcpp2 to complete the code generation process.
 - Use soapcpp2 option -I to specify paths for #import
   To build with STL, 'stlvector.h' is imported from 'import' dir in package.
 - Use wsdl2h options -c and -s to generate pure C code or C++ code without STL.
 - Use 'typemap.dat' to control schema namespace bindings and type mappings.
   It is strongly recommended to customize the names of the namespace prefixes
   generated by wsdl2h. To do so, modify the prefix bindings in the Namespaces
   section below and add the modified lines to 'typemap.dat' to rerun wsdl2h.
 - Use Doxygen (www.doxygen.org) to browse this file.
 - Use wsdl2h option -l to view the software license terms.

*/

//gsoapopt cw

/******************************************************************************\
 *                                                                            *
 * com.miteno.ws                                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/


/* NOTE:

It is strongly recommended to customize the names of the namespace prefixes
generated by wsdl2h. To do so, modify the prefix bindings below and add the
modified lines to typemap.dat to rerun wsdl2h:

ns1 = "com.miteno.ws"
ns2 = "http://ws.miteno.com/"

*/

//gsoap ns2   schema namespace:	http://ws.miteno.com/
//gsoap ns2   schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Schema Types                                                               *
 *                                                                            *
\******************************************************************************/



/// "http://ws.miteno.com/":posRequest is a complexType.
struct ns2__posRequest
{
/// Element msg of type xs:string.
    char*                                msg                            0;	///< Optional element.
};

/// "http://ws.miteno.com/":posRequestResponse is a complexType.
struct ns2__posRequestResponse
{
/// Element return of type xs:string.
    char*                                return_                        0;	///< Optional element.
};

/// "http://ws.miteno.com/":posUserRequest is a complexType.
struct ns2__posUserRequest
{
/// Element user of type "http://ws.miteno.com/":userEntity.
    struct ns2__userEntity*              user                           0;	///< Optional element.
};

/// "http://ws.miteno.com/":userEntity is a complexType.
struct ns2__userEntity
{
/// Element userName of type xs:string.
    char*                                userName                       0;	///< Optional element.
/// Element userPwd of type xs:string.
    char*                                userPwd                        0;	///< Optional element.
};

/// "http://ws.miteno.com/":posUserRequestResponse is a complexType.
struct ns2__posUserRequestResponse
{
/// Element return of type "http://ws.miteno.com/":userEntity.
    struct ns2__userEntity*              return_                        0;	///< Optional element.
};

/// Element "http://ws.miteno.com/":posRequest of type "http://ws.miteno.com/":posRequest.
// 'ns2__posRequest' element definition intentionally left blank.

/// Element "http://ws.miteno.com/":posRequestResponse of type "http://ws.miteno.com/":posRequestResponse.
// 'ns2__posRequestResponse' element definition intentionally left blank.

/// Element "http://ws.miteno.com/":posUserRequest of type "http://ws.miteno.com/":posUserRequest.
// 'ns2__posUserRequest' element definition intentionally left blank.

/// Element "http://ws.miteno.com/":posUserRequestResponse of type "http://ws.miteno.com/":posUserRequestResponse.
// 'ns2__posUserRequestResponse' element definition intentionally left blank.

/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns1  service name:	posServiceSoapBinding 
//gsoap ns1  service type:	PosService 
//gsoap ns1  service port:	http://192.168.20.26:8800/A-Pay/services/posService 
//gsoap ns1  service namespace:	com.miteno.ws 
//gsoap ns1  service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage posService Definitions

@section posService_bindings Bindings
  - @ref posServiceSoapBinding

*/

/**

@page posServiceSoapBinding Binding "posServiceSoapBinding"

@section posServiceSoapBinding_operations Operations of Binding  "posServiceSoapBinding"
  - @ref __ns1__posRequest
  - @ref __ns1__posUserRequest

@section posServiceSoapBinding_ports Endpoints of Binding  "posServiceSoapBinding"
  - http://192.168.20.26:8800/A-Pay/services/posService

*/

/******************************************************************************\
 *                                                                            *
 * posServiceSoapBinding                                                      *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * __ns1__posRequest                                                          *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns1__posRequest" of service binding "posServiceSoapBinding"

/**

Operation details:

  - SOAP document/literal style

C stub function (defined in soapClient.c[pp] after running soapcpp2):
@code
  int soap_call___ns1__posRequest(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct ns2__posRequest*             ns2__posRequest,
    // response parameters:
    struct ns2__posRequestResponse*     ns2__posRequestResponse
  );
@endcode

*/

//gsoap ns1  service method-style:	posRequest document
//gsoap ns1  service method-encoding:	posRequest literal
//gsoap ns1  service method-action:	posRequest ""
int __ns1__posRequest(
    struct ns2__posRequest*             ns2__posRequest,	///< Request parameter
    struct ns2__posRequestResponse*     ns2__posRequestResponse	///< Response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns1__posUserRequest                                                      *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns1__posUserRequest" of service binding "posServiceSoapBinding"

/**

Operation details:

  - SOAP document/literal style

C stub function (defined in soapClient.c[pp] after running soapcpp2):
@code
  int soap_call___ns1__posUserRequest(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct ns2__posUserRequest*         ns2__posUserRequest,
    // response parameters:
    struct ns2__posUserRequestResponse* ns2__posUserRequestResponse
  );
@endcode

*/

//gsoap ns1  service method-style:	posUserRequest document
//gsoap ns1  service method-encoding:	posUserRequest literal
//gsoap ns1  service method-action:	posUserRequest ""
int __ns1__posUserRequest(
    struct ns2__posUserRequest*         ns2__posUserRequest,	///< Request parameter
    struct ns2__posUserRequestResponse* ns2__posUserRequestResponse	///< Response parameter
);

/* End of posService.h */
