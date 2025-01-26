#include "html.h"
#include "log.h"

void setupHtml()
{
    logMessage("HTML", "Starting...");
}

String getControlPage()
{
    return R"(
        <!DOCTYPE html>
        <html>
            <head>
                <title>POOL HEATING</title>
                <meta name="viewport" content="width=device-width, initial-scale=1">
                <style>
                    html { font-family: sans-serif; text-align: center; }
                    body { display: inline-flex; flex-direction: column; }
                    h1 { margin-bottom: 1.2em; } 
                    h2 { margin: 0; }
                    button { height: 45px; }
                    div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
                </style>
            </head>
            <body>
                <h1>POOL HEATING</h1>
                <div>  
                    <button onclick="sendPostRequest('motor', 'toggle');">MOTOR</button>
                </div>
                <script>

                    function sendPostRequest(name, value) { 
                        var xhr = new XMLHttpRequest();
                        xhr.open("POST", "/post", true);
                        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
                        xhr.onreadystatechange = function() {
                            if (xhr.readyState == 4 && xhr.status == 200) {
                                console.log("Resposta do servidor: " + xhr.responseText);
                            }
                        };
                        // Envia os parâmetros name e value no formato x-www-form-urlencoded
                        xhr.send("name=" + encodeURIComponent(name) + "&value=" + encodeURIComponent(value));
                    }

                </script>
            </body>
        </html>
    )";
}
