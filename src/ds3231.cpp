#include <Wire.h>
#include <RTClib.h> 
#include "log.h"
#include "utils.h"
#include "controller.h"

// Instâncias do RTC e Timezone
RTC_DS3231 rtc;

// Definição dos pinos de SDA e SCL
#define SDA_PIN 18
#define SCL_PIN 19

// Função para recuperar o horário do RTC em formato `time_t`
time_t getTime_DS3231()
{
    DateTime now = rtc.now(); // Obtem o horário atual do RTC
    struct tm timeinfo;
    timeinfo.tm_year = now.year() - 1900; // Ano base 1900
    timeinfo.tm_mon = now.month() - 1;    // Mês começa do 0
    timeinfo.tm_mday = now.day();
    timeinfo.tm_hour = now.hour();
    timeinfo.tm_min = now.minute();
    timeinfo.tm_sec = now.second();

    // Converte para time_t (Unix Timestamp)
    return mktime(&timeinfo);
}

void printDate_DS3231()
{

    time_t currentTime = getTime_DS3231();
    logMessage("DS3231", "🕔 ");
    logMessage("", ctime(&currentTime), true);
}

// now deve ser string no formato ISO 8601, como "2025-01-26T15:47:33.123"
void updateRTC(String now)
{
    if (now.length() < 19)
    { // Verifica se o valor é válido
        logMessage("DS3231", "Erro: Data/hora inválida.");
        return;
    }

    // Extrai os componentes do formato "YYYY-MM-DDTHH:MM:SS"
    int year = now.substring(0, 4).toInt();
    int month = now.substring(5, 7).toInt();
    int day = now.substring(8, 10).toInt();
    int hour = now.substring(11, 13).toInt();
    int minute = now.substring(14, 16).toInt();
    int second = now.substring(17, 19).toInt();

    // Atualiza o RTC com os valores extraídos
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

void setupDS3231()
{
    logMessage("DS3231", "Starting... ");
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN); // Inicializa I2C nos pinos definidos

    // Inicializa o RTC
    if (!rtc.begin())
    {
        logMessage("DS3231", "Erro ao inicializar RTC!");
        while (1)
            ; // Para o programa caso o RTC não seja encontrado
    }

    printDate_DS3231();
}

void setupTime_DS3231()
{
 
    String datetime = jsonGET("https://timeapi.io/api/Time/current/zone?timeZone=America/Sao_Paulo", "dateTime");

    if (isValidDateTime(datetime))
    { 
        updateRTC(datetime);
        logMessage("DS3231", "Hora configurada no RTC com base no timezone!");
        printDate_DS3231();
    }
    else
    {
        logMessage("DS3231", "Falha ao obter horário do timezone. Continuando com horário anterior no RTC.");
        logMessage("DS3231", "Foi obtido isso: " + datetime);
    }
}
