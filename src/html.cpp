#include "html.h"

String getControlPage()
{
    return R"(
        <!DOCTYPE html>
        <html>
            <head>
                <title>ESP32 Web Server Demo</title>
                <meta name="viewport" content="width=device-width, initial-scale=1">
                <style>
                    html { font-family: sans-serif; text-align: center; }
                    body { display: inline-flex; flex-direction: column; }
                    h1 { margin-bottom: 1.2em; } 
                    h2 { margin: 0; }
                    div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
                    .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em; font-size: 2em; text-decoration: none }
                    .btn.OFF { background-color: #333; }
                </style>
            </head>
            <body>
                <h1>ESP32 Web Server</h1>
                <div>
                    <h2>LED 1</h2>
                    <a href="?toggle=1" class="btn LED1_TEXT">LED1_TEXT</a>
                    <h2>LED 2</h2>
                    <a href="?toggle=2" class="btn LED2_TEXT">LED2_TEXT</a>
                    
                    <button onclick="sendPostRequest();">Enviar POST</button>
                </div>
                <script>
                    function sendPostRequest() {
                        var message = "Mensagem que você deseja enviar no POST";
                        var xhr = new XMLHttpRequest();
                        xhr.open("POST", "/post", true);
                        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
                        xhr.onreadystatechange = function() {
                            if (xhr.readyState == 4 && xhr.status == 200) {
                                console.log("Resposta do servidor: " + xhr.responseText);
                            }
                        };
                        xhr.send("message=" + message);
                    }
                </script>
            </body>
        </html>
    )";
}
