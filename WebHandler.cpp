#include "WebHandler.h"
#include "NetworkHandler.h"
#include <Update.h>

// TODO: Replace this empty string with your base64 encoded image string.
// Example: "iVBORw0KGgoAAAANSUhEUgAA..."
const char* DEVICE_LOGO_BASE64 = "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";

WebServer WebHandler::server(80);

void WebHandler::setup() {
    const char * headerkeys[] = {"Cookie"};
    server.collectHeaders(headerkeys, 1);

    server.on("/", HTTP_GET, handleStatus);
    server.on("/login", HTTP_GET, handleLogin);
    server.on("/auth", HTTP_POST, handleAuth);
    server.on("/settings", HTTP_GET, handleRoot);
    server.on("/save", HTTP_POST, handleSave);
    server.on("/ota", HTTP_GET, handleOTA);
    server.on("/ota/save", HTTP_POST, handleOTASave);
    server.on("/update", HTTP_POST, handleUpdate, handleUpdateUpload);
    server.onNotFound(captivePortalRedirect);

    server.begin();
    Serial.println("Web server started");
}

void WebHandler::loop() {
    server.handleClient();
}

bool WebHandler::checkAuth() {
    if (server.hasHeader("Cookie")) {
        String cookie = server.header("Cookie");
        if (cookie.indexOf("auth=1") != -1) return true;
    }
    return false;
}

void WebHandler::captivePortalRedirect() {
    if (SettingsHandler::settings.wifi_mode == 1) { // AP Mode
        String host = server.hostHeader();
        String ip = WiFi.softAPIP().toString();
        if (host != ip) {
            server.sendHeader("Location", "http://" + ip + "/login", true);
            server.send(302, "text/plain", "");
            return;
        }
    }
    server.send(404, "text/plain", "Not found");
}

void WebHandler::handleStatus() {
    if (NetworkHandler::forceOTA) {
        server.sendHeader("Location", "/ota", true);
        server.send(302, "text/plain", "");
        return;
    }

    // In AP mode, require login before showing any page
    if (SettingsHandler::settings.wifi_mode == 1 && !checkAuth()) {
        server.sendHeader("Location", "/login", true);
        server.send(302, "text/plain", "");
        return;
    }

    String html = "<html><body>";
    if (strlen(DEVICE_LOGO_BASE64) > 0) {
        html += "<div style='text-align: center;'><img src='" + String(DEVICE_LOGO_BASE64) + "' alt='Logo' style='max-height: 100px;'></div><hr>";
    }
    html += "<h1>Device Status</h1>";
    html += "<p><b>Company:</b> " + String(SettingsHandler::settings.company) + "</p>";
    html += "<p><b>Firmware:</b> " + String(SettingsHandler::settings.firmwareStr) + "</p>";
    html += "<p><b>WiFi Status:</b> " + String(SettingsHandler::settings.wifi_mode == 1 ? "AP Mode" : "STA Mode") + "</p>";
    html += "<p><a href='/settings'>Go to Settings</a></p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void WebHandler::handleLogin() {
    String html = "<html><body>";
    if (strlen(DEVICE_LOGO_BASE64) > 0) {
        html += "<div style='text-align: center;'><img src='" + String(DEVICE_LOGO_BASE64) + "' alt='Logo' style='max-height: 100px;'></div><hr>";
    }
    html += "<h2>Login to Settings</h2>";
    html += "<form action='/auth' method='POST'>";
    html += "Password: <input type='password' name='password'><br><br>";
    html += "<input type='submit' value='Login'>";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
}

void WebHandler::handleAuth() {
    if (server.hasArg("password")) {
        if (server.arg("password") == SettingsHandler::settings.web_pass) {
            String target = NetworkHandler::forceOTA ? "/ota" : "/settings";
            server.sendHeader("Location", target, true);
            server.sendHeader("Set-Cookie", "auth=1; Path=/; Max-Age=3600");
            server.send(302, "text/plain", "Login Successful");
            return;
        }
    }
    server.send(401, "text/html", "<html><body><h2>Incorrect Password</h2><a href='/login'>Try Again</a></body></html>");
}

void WebHandler::handleRoot() {
    if (!checkAuth()) {
        server.sendHeader("Location", "/login", true);
        server.send(302, "text/plain", "");
        return;
    }

    String html = "<html><body>";
    if (strlen(DEVICE_LOGO_BASE64) > 0) {
        html += "<div style='text-align: center;'><img src='" + String(DEVICE_LOGO_BASE64) + "' alt='Logo' style='max-height: 100px;'></div><hr>";
    }
    html += "<h1>Device Configuration</h1>";

    html += "<h2>System Details</h2>";
    html += "<ul><li>Company: " + String(SettingsHandler::settings.company) + "</li>";
    html += "<li>Firmware: " + String(SettingsHandler::settings.firmwareStr) + "</li></ul>";

    html += "<form action='/save' method='POST'>";
    
    html += "<h3>Company Info</h3>";
    html += "Name: <input type='text' name='company' value='" + String(SettingsHandler::settings.company) + "'><br>";
    
    html += "<h3>WiFi Config</h3>";
    html += "Mode: <select name='wifi_mode'>";
    html += "<option value='0' " + String(SettingsHandler::settings.wifi_mode==0?"selected":"") + ">STA (Connect to Router)</option>";
    html += "<option value='1' " + String(SettingsHandler::settings.wifi_mode==1?"selected":"") + ">AP (Access Point)</option>";
    html += "</select><br>";
    html += "SSID: <input type='text' name='wifi_ssid' value='" + String(SettingsHandler::settings.wifi_ssid) + "'><br>";
    html += "PASS: <input type='text' name='wifi_pass' value='" + String(SettingsHandler::settings.wifi_pass) + "'><br>";
    
    html += "<h3>Ethernet Config</h3>";
    html += "IP Assignment: <select name='eth_dhcp'>";
    html += "<option value='1' " + String(SettingsHandler::settings.eth_dhcp==1?"selected":"") + ">DHCP</option>";
    html += "<option value='0' " + String(SettingsHandler::settings.eth_dhcp==0?"selected":"") + ">Static</option>";
    html += "</select><br>";
    html += "IP: <input type='text' name='eth_ip' value='" + String(SettingsHandler::settings.eth_ip) + "'><br>";
    html += "Gateway: <input type='text' name='eth_gw' value='" + String(SettingsHandler::settings.eth_gw) + "'><br>";
    html += "Subnet: <input type='text' name='eth_mask' value='" + String(SettingsHandler::settings.eth_mask) + "'><br>";
    
    html += "<h3>UART Config (Port 2)</h3>";
    html += "Baudrate: <input type='text' name='uart_baud' value='" + String(SettingsHandler::settings.uart.baudrate) + "'><br>";
    
    html += "<h3>Web Security</h3>";
    html += "Admin Password: <input type='text' name='web_pass' value='" + String(SettingsHandler::settings.web_pass) + "'><br>";
    
    html += "<br><input type='submit' value='Save & Reboot'>";
    html += "</form>";
    html += "<hr><p><a href='/ota' style='color: #007bff; text-decoration: none; font-weight: bold;'>Go to Firmware Update (OTA)</a></p>";
    html += "</body></html>";

    server.send(200, "text/html", html);
}

void WebHandler::handleSave() {
    if (!checkAuth()) {
        server.sendHeader("Location", "/login", true);
        server.send(302, "text/plain", "");
        return;
    }

    if (server.hasArg("company")) {
        strncpy(SettingsHandler::settings.company, server.arg("company").c_str(), sizeof(SettingsHandler::settings.company) - 1);
    }
    
    if (server.hasArg("web_pass")) {
        strncpy(SettingsHandler::settings.web_pass, server.arg("web_pass").c_str(), sizeof(SettingsHandler::settings.web_pass) - 1);
    }
    
    if (server.hasArg("wifi_mode")) SettingsHandler::settings.wifi_mode = server.arg("wifi_mode").toInt();
    if (server.hasArg("wifi_ssid")) strncpy(SettingsHandler::settings.wifi_ssid, server.arg("wifi_ssid").c_str(), sizeof(SettingsHandler::settings.wifi_ssid) - 1);
    if (server.hasArg("wifi_pass")) strncpy(SettingsHandler::settings.wifi_pass, server.arg("wifi_pass").c_str(), sizeof(SettingsHandler::settings.wifi_pass) - 1);
    
    if (server.hasArg("eth_dhcp")) SettingsHandler::settings.eth_dhcp = server.arg("eth_dhcp").toInt();
    if (server.hasArg("eth_ip")) strncpy(SettingsHandler::settings.eth_ip, server.arg("eth_ip").c_str(), sizeof(SettingsHandler::settings.eth_ip) - 1);
    if (server.hasArg("eth_gw")) strncpy(SettingsHandler::settings.eth_gw, server.arg("eth_gw").c_str(), sizeof(SettingsHandler::settings.eth_gw) - 1);
    if (server.hasArg("eth_mask")) strncpy(SettingsHandler::settings.eth_mask, server.arg("eth_mask").c_str(), sizeof(SettingsHandler::settings.eth_mask) - 1);
    
    if (server.hasArg("uart_baud")) SettingsHandler::settings.uart.baudrate = server.arg("uart_baud").toInt();
    
    SettingsHandler::saveSettings();
    
    String html = "<html><body>";
    if (strlen(DEVICE_LOGO_BASE64) > 0) {
        html += "<div style='text-align: center;'><img src='" + String(DEVICE_LOGO_BASE64) + "' alt='Logo' style='max-height: 100px;'></div><hr>";
    }
    html += "<h2>Settings Saved! Rebooting...</h2></body></html>";
    
    server.send(200, "text/html", html);
    delay(1000);
    ESP.restart();
}

void WebHandler::handleOTA() {
    if (!checkAuth()) {
        server.sendHeader("Location", "/login", true);
        server.send(302, "text/plain", "");
        return;
    }

    String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<style>";
    html += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: linear-gradient(135deg, #1a1a2e 0%, #16213e 100%); color: #fff; margin: 0; display: flex; align-items: center; justify-content: center; height: 100vh; overflow: hidden; }";
    html += ".container { background: rgba(255, 255, 255, 0.05); backdrop-filter: blur(10px); border-radius: 20px; padding: 40px; box-shadow: 0 15px 35px rgba(0,0,0,0.5); border: 1px solid rgba(255,255,255,0.1); width: 90%; max-width: 400px; text-align: center; }";
    html += "h1 { margin-bottom: 20px; font-weight: 300; letter-spacing: 2px; color: #4ecca3; }";
    html += "p { color: #8e8e8e; margin-bottom: 30px; }";
    html += ".upload-area { border: 2px dashed rgba(255,255,255,0.2); padding: 30px; border-radius: 15px; cursor: pointer; transition: 0.3s; position: relative; }";
    html += ".upload-area:hover { border-color: #4ecca3; background: rgba(78, 204, 163, 0.05); }";
    html += "input[type='file'] { position: absolute; left: 0; top: 0; width: 100%; height: 100%; opacity: 0; cursor: pointer; }";
    html += ".btn { background: #4ecca3; color: #1a1a2e; border: none; padding: 12px 25px; border-radius: 50px; font-weight: bold; cursor: pointer; transition: 0.3s; margin-top: 20px; width: 100%; text-transform: uppercase; letter-spacing: 1px; }";
    html += ".btn:hover { background: #45b291; transform: translateY(-2px); box-shadow: 0 5px 15px rgba(78, 204, 163, 0.4); }";
    html += ".progress-container { width: 100%; background: rgba(255,255,255,0.1); border-radius: 10px; margin-top: 20px; display: none; }";
    html += ".progress-bar { height: 10px; width: 0%; background: #4ecca3; border-radius: 10px; transition: 0.1s; }";
    html += ".status-text { margin-top: 10px; font-size: 0.9em; display: none; }";
    html += "</style>";
    html += "<script>";
    html += "function startUpdate() {";
    html += "  var fileInput = document.getElementById('file');";
    html += "  if (fileInput.files.length === 0) { alert('Please select a file'); return; }";
    html += "  var formData = new FormData();";
    html += "  formData.append('update', fileInput.files[0]);";
    html += "  document.getElementById('upload-ui').style.display = 'none';";
    html += "  document.getElementById('progress-container').style.display = 'block';";
    html += "  document.getElementById('status-text').style.display = 'block';";
    html += "  var xhr = new XMLHttpRequest();";
    html += "  xhr.open('POST', '/update', true);";
    html += "  xhr.upload.onprogress = function(e) {";
    html += "    if (e.lengthComputable) {";
    html += "      var percent = (e.loaded / e.total) * 100;";
    html += "      document.getElementById('progress-bar').style.width = percent + '%';";
    html += "      document.getElementById('status-text').innerHTML = 'Uploading: ' + Math.round(percent) + '%';";
    html += "    }";
    html += "  };";
    html += "  xhr.onload = function() {";
    html += "    if (xhr.status == 200) {";
    html += "      document.getElementById('status-text').innerHTML = 'Update Successful! Rebooting...';";
    html += "      setTimeout(function() { window.location.href = '/'; }, 5000);";
    html += "    } else {";
    html += "      document.getElementById('status-text').innerHTML = 'Error: ' + xhr.responseText;";
    html += "      document.getElementById('upload-ui').style.display = 'block';";
    html += "    }";
    html += "  };";
    html += "  xhr.send(formData);";
    html += "}";
    html += "</script></head><body>";
    html += "<div class='container'>";
    html += "<h1>OTA Update</h1>";
    html += "<p>Upload new firmware binary</p>";
    html += "<div id='upload-ui'>";
    html += "  <div class='upload-area'>";
    html += "    <p id='file-name'>Drop or Click to select .bin</p>";
    html += "    <input type='file' id='file' accept='.bin' onchange=\"document.getElementById('file-name').innerHTML = this.files[0].name\">";
    html += "  </div>";
    html += "  <button class='btn' onclick='startUpdate()'>Flash Firmware</button>";
    html += "</div>";
    
    html += "<div id='password-config' style='margin-top: 30px; padding-top: 20px; border-top: 1px solid rgba(255,255,255,0.1);'>";
    html += "  <h3 style='font-size: 1.1em; color: #4ecca3; margin-bottom: 15px;'>Manage Password</h3>";
    html += "  <form action='/ota/save' method='POST'>";
    html += "    <div style='display: flex; gap: 10px;'>";
    html += "      <input type='password' name='new_pass' placeholder='New Password' style='flex: 1; padding: 10px; border-radius: 5px; border: 1px solid rgba(255,255,255,0.2); background: rgba(0,0,0,0.2); color: #fff;'>";
    html += "      <button type='submit' style='background: #4ecca3; color: #1a1a2e; border: none; padding: 10px 15px; border-radius: 5px; cursor: pointer; font-weight: bold;'>Save</button>";
    html += "    </div>";
    html += "  </form>";
    html += "</div>";

    html += "<div class='progress-container' id='progress-container'><div class='progress-bar' id='progress-bar'></div></div>";
    html += "<div class='status-text' id='status-text'>Initializing...</div>";
    html += "<p style='margin-top: 20px;'><a href='/settings' style='color: #4ecca3; text-decoration: none;'>&larr; Back to Settings</a></p>";
    html += "</div></body></html>";

    server.send(200, "text/html", html);
}

void WebHandler::handleUpdate() {
    server.sendHeader("Connection", "close");
    server.send(Update.hasError() ? 500 : 200, "text/plain", (Update.hasError()) ? Update.errorString() : "OK");
    ESP.restart();
}

void WebHandler::handleUpdateUpload() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { // start with max available size
            Update.printError(Serial);
        }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
            Update.printError(Serial);
        }
    } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { // true to set the size to the current progress
            Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
            Update.printError(Serial);
        }
    }
}

void WebHandler::handleOTASave() {
    if (!checkAuth()) {
        server.sendHeader("Location", "/login", true);
        server.send(302, "text/plain", "");
        return;
    }

    if (server.hasArg("new_pass")) {
        String newPass = server.arg("new_pass");
        if (newPass.length() > 0) {
            strncpy(SettingsHandler::settings.web_pass, newPass.c_str(), sizeof(SettingsHandler::settings.web_pass) - 1);
            SettingsHandler::saveSettings();
            
            String html = "<html><head><meta http-equiv='refresh' content='2;url=/ota'></head>";
            html += "<body style='background: #1a1a2e; color: #fff; display: flex; align-items: center; justify-content: center; height: 100vh; font-family: sans-serif;'>";
            html += "<div style='text-align: center;'><h2>Password Updated Successfully!</h2><p>Returning to OTA page...</p></div>";
            html += "</body></html>";
            server.send(200, "text/html", html);
            return;
        }
    }
    server.sendHeader("Location", "/ota", true);
    server.send(302, "text/plain", "");
}
