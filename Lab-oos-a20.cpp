using namespace std;
#include <iostream>
#include <string>

class AuthenticationResult {
    const bool _authenticated;
    const string _username;

   public:
    // constructor for Auth result. needs at least a boolean input, if no
    // username is given a default is used
    AuthenticationResult(bool authenticated,
                         string username = "unauthenticated_user")
        : _authenticated(authenticated), _username(username) {}
    // get parameter _authenticated
    bool get_is_authenticated() const { return _authenticated; }
    // get parameter _username
    string get_username() const { return _username; }
};

// interface. has no direct usecase. its used to structure othere clases better
// structured
class IAuthenticationProcedure {
   public:
    // virtual class that is overridden by all child-classes
    virtual AuthenticationResult authenticate() const = 0;
};

// Mockup class (integrating interface). every auth try succeeds
class MockAuthentication : public IAuthenticationProcedure {
   public:
    // return a successfull auth every time with name Default
    AuthenticationResult authenticate() const override {
        return AuthenticationResult(true, "Default");
    }
};

// standart login class (integrating interface). only succeeds if username and
// password are the same
class UsernamePassword : public IAuthenticationProcedure {
   public:
    // return a successfull auth if name == password
    AuthenticationResult authenticate() const override {
        string user, pswd;
        cout << "Username:" << endl;
        cin >> user;
        cout << "Password:" << endl;
        cin >> pswd;

        return AuthenticationResult((user.compare(pswd) == 0), user);
    }
};

// certificate login class (integrating interface). succeeds if a valid
// certificate is used
class Certificate : public IAuthenticationProcedure {
   public:
    // return a successfull auth if certificate == hs-esslingen
    AuthenticationResult authenticate() const override {
        string cert;
        cout << "Zertifikatsaussteller:" << endl;
        cin >> cert;

        return AuthenticationResult((cert.compare("hs-esslingen") == 0),
                                    "certificate.owner");
    }
};

// client class. can use every form of authentication that is implemented
// through the interface. this makes changes to the authentification easier
class Client {
    const IAuthenticationProcedure* _auth;

   public:
    // set the auth process used by the client
    void set_authentication_procedure(const IAuthenticationProcedure* Iauth) {
        _auth = Iauth;
    }
    // tries to authenticate with the defined authentification method
    void execute() {
        AuthenticationResult AuthResult = _auth->authenticate();
        if (AuthResult.get_is_authenticated()) {
            cout << "Das Programm wird ausgeführt für "
                 << AuthResult.get_username() << "." << endl;
        } else {
            cout << "Das Programm konnte nicht ausgeführt werden." << endl;
        }
    }
};

int main(void) {
    Client client;

    cout << "Authentifizierung über das Authentifizierungsverfahren Mock "
            "Authentication"
         << endl;
    IAuthenticationProcedure* mock_authentication = new MockAuthentication();
    client.set_authentication_procedure(mock_authentication);
    client.execute();

    cout << "Authentifizierung über das Authentifizierungsverfahren Username "
            "Password"
         << endl;
    IAuthenticationProcedure* username_password = new UsernamePassword();
    client.set_authentication_procedure(username_password);
    client.execute();

    cout << "Authentifizierung über das Authentifizierungsverfahren Zertifikat"
         << endl;
    IAuthenticationProcedure* certificate = new Certificate();
    client.set_authentication_procedure(certificate);
    client.execute();
    return 0;
}
