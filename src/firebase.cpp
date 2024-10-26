#include "firebase.h"
#include "log.h"
#include "ds18b20.h"
#include "controller.h"
#include "wifi_manager.h"
#include "firebase_config.h"

#define FIREBASE_DISABLE_DEBUG_PRINT
#include <addons/TokenHelper.h> // Don't move this include from here
#include <addons/RTDBHelper.h>  // Don't move this include from here

FirebaseData fbDataObj;
FirebaseAuth fbAuth;
FirebaseConfig fbConfig;

void setupFirebase()
{

    logMessage("Firebase", "Starting...");

    Firebase.reconnectNetwork(true);
    // Firebase.setIdToken(&fbConfig, "", 3600, "<Refresh Token>");

    fbConfig.api_key = FIREBASE_API_KEY;
    fbConfig.database_url = FIREBASE_URL;
    fbConfig.token_status_callback = tokenStatusCallback;
    // fbConfig.signer.preRefreshSeconds = 5 * 60;

    fbAuth.user.email = FIREBASE_USER_NAME;
    fbAuth.user.password = FIREBASE_USER_PASS;

    fbDataObj.setBSSLBufferSize(2048, 1024);
    fbDataObj.keepAlive(10, 10, 1);
}

void updateHistory(time_t timestamp,
                   bool force_motor,              //
                   bool pulling_water,            //
                   float pool_temperature,        //
                   float roof_temperature,        //
                   time_t last_pulling_water_hit, //
                   bool test_mode,                //
                   String ip_address              //
)
{
    if (!checkInternetConnection())
    {
        logMessage("Firebase", "Sem internet!");
        return;
    }

    if (!Firebase.ready())
    {
        logMessage("Firebase", "Autenticando...");
        Firebase.begin(&fbConfig, &fbAuth);
        Firebase.setDoubleDigits(2);
        logMessage("Firebase", "Autenticação OK!");
    }

    String regLogMessage = String("Registrando History ");
    regLogMessage += String(timestamp);
    regLogMessage += " at ";
    regLogMessage += timestampToDateTime(timestamp);
    regLogMessage += "...";
    logMessage("Firebase", regLogMessage);

    FirebaseJson json;
    json.set("datetime", timestampToDateTime(timestamp));
    json.set("temperature_pool", pool_temperature);
    json.set("temperature_roof", roof_temperature);
    json.set("pulling_water", pulling_water);
    json.set("pulling_Water_last", timestampToDateTime(last_pulling_water_hit));
    json.set("force_motor", force_motor);
    json.set("test_mode", test_mode);
    json.set("ip_address", ip_address);

    bool result = Firebase.push(fbDataObj, "/history", json);
    logMessage("Firebase", String(result ? "History registrado!" : "Erro ao registrar history!"));
    logSkipLine();
}
