#ifndef SECRETS_H
#define SECRETS_H

const char AWS_IOT_ENDPOINT[] = " ";        //replace your endpoint


//Amazon root CA1                                            //replace for your rootCA1 certificate
const char AWS_CERT_CA[] PROGMEM = R"EOF(                  

)EOF";

// Device Certificate                                        //replace your Device certificate
const char AWS_CERT_CRT[] PROGMEM = R"KEY(                         


)KEY";

// Device Private Key                                         //replace your private key
const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(


)KEY";

#endif